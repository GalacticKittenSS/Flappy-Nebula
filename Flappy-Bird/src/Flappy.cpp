#include "Flappy.h"
#include "Utils/Collisions.h"
#include "Utils/Hue.h"
#include "Utils/File.h"

using namespace Nebula;

extern Colour hueColour = Colour();
extern PlayerData Score = PlayerData();

#define PLAYERNAME "GalacticKittenSS"

Array<PlayerData> Players;

void Flappy::Attach() {
	Score.Name = PLAYERNAME;
	
	ReadfromFile file("best.nbd");
	file.ReadHighScore([](std::string Name, int highScore) {
		if (Name != PLAYERNAME)
			Players.push_back({ Name, highScore });
		else
			Score.HighScore = highScore;
	});
	file.Close();

	Reset();
}

void Flappy::Detach() {
	WritetoFile file("best.nbd");

	for (auto player : Players)
		file.WriteHighScore(player.HighScore, player.Name);

	file.WriteHighScore(Score.HighScore, Score.Name);
	file.Close();
}

void Flappy::OnEvent(Nebula::Event& e) {
	Dispatcher d(e);
	d.Dispatch<KeyPressedEvent>(BIND_EVENT(Flappy::OnKeyPressed));
}

bool Flappy::OnKeyPressed(Nebula::KeyPressedEvent& e) {
	if (e.GetKeyCode() == NB_ESCAPE || (e.GetKeyCode() == NB_SPACE && state == GameState::Paused))
		SwitchState();

	return true;
}

void Flappy::Update(Nebula::Timestep ts) {
	hueColour.Update();

	if (state == GameState::Running) Play();
}

void Flappy::Render() {
	RenderCommand::Clear();
	RenderCommand::SetClearColour({ 0.3f, 0.3f, 0.3f, 1.0f });
	
	Renderer2D::BeginScene(SceneCam, SceneCam.GetViewMatrix());
	Renderer2D::Draw(NB_QUAD, Player.GetTransform(), vec4(1.0f));
	Renderer2D::Draw(NB_QUAD, Transform({ 0.0f,  8.5f }, { 32.0f, 1.0f }), vec4(hueColour.GetRGB(), 0.65f));
	Renderer2D::Draw(NB_QUAD, Transform({ 0.0f, -8.5f }, { 32.0f, 1.0f }), vec4(hueColour.GetRGB(), 0.65f));
	
	for (auto& pair : Pillars)
		pair.Render();
	
	Renderer2D::EndScene();
}

void Flappy::SwitchState() {
	switch (state) {
		case GameState::Paused: state = GameState::Running; break;
		case GameState::Running: state = GameState::Paused; break;
	}
}

void Flappy::OnDeath() {
	if (Score.HighScore < Score.CurrentScore) {
		Score.HighScore = Score.CurrentScore;
		NB_WARN("New High Score: {0}!", Score.HighScore);
	}

	Score.CurrentScore = 0;

	Reset();
}

void Flappy::Reset() {
	state = GameState::Paused;
	Player.Position = { 0.0f, 0.0f };

	Pillars.clear();
	for (uint32_t i = 0; i < 5; i++)
		Pillars.push_back(PillarPair(-17.0f, 17.0f, 8.0f, 8.0f, 0.0f, i * 6.75f));
}

void Flappy::Play() {
	if (Input::IsKeyPressed(NB_SPACE)) {
		Player.Position.y += 9.81f * Time::DeltaTime();
	}
	else {
		Player.Position.y -= 9.81f * Time::DeltaTime();
	}

	for (auto& pair : Pillars)
  		pair.Update();

	vec4 playerMin = Player.GetTransform() * vec4(-0.5f, -0.5f, 0.0f, 1.0f);
	vec4 playerMax = Player.GetTransform() * vec4( 0.5f,  0.5f, 0.0f, 1.0f);

	bool collision = 
		//Top Cube
		AABBvsAABB(playerMin, playerMax,
			(mat4)Transform({ 0.0f,  8.5f }, { 16.0f, 1.0f }) * vec4(-0.5f, -0.5f, 0.0f, 1.0f), 
			(mat4)Transform({ 0.0f,  8.5f }, { 16.0f, 1.0f }) * vec4(0.5f, 0.5f, 0.0f, 1.0f)) ||
		//Bottom Cube
		AABBvsAABB(playerMin, playerMax,
			(mat4)Transform({ 0.0f, -8.5f }, { 16.0f, 1.0f }) * vec4(-0.5f, -0.5f, 0.0f, 1.0f), 
			(mat4)Transform({ 0.0f, -8.5f }, { 16.0f, 1.0f }) * vec4(0.5f, 0.5f, 0.0f, 1.0f));

	if (collision)
		OnDeath();

	for (auto& pair : Pillars) {
		if (pair.CheckCollision(&Player)) {
			OnDeath();
			return;
		}
	}
}