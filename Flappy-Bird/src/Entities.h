#pragma once

#include <Nebula.h>
#include "Utils/Collisions.h"
#include "Utils/Random.h"
#include "Utils/Hue.h"

#include <string>

struct PlayerData {
	std::string Name = "Unknown Player";
	int HighScore = 0;
	int CurrentScore = 0;

	PlayerData() = default;
	PlayerData(const PlayerData&) = default;
	PlayerData(const std::string& name, int highScore) : Name(name), HighScore(highScore) { }
};

extern Colour hueColour;
extern PlayerData Score;

struct Transform {
	Nebula::vec2 Position{ 0.0f, 0.0f };
	Nebula::vec2 Size{ 1.0f, 1.0f };
	float Rotation = 0.0f;

	Transform() = default;
	Transform(const Transform&) = default;
	Transform(Nebula::vec2 position, Nebula::vec2 size, float rotation = 0.0f) : Position(position), Size(size), Rotation(rotation) { }

	Nebula::mat4 GetTransform() const { 
		return Nebula::translate(Nebula::vec3(Position, 0.0f)) * Nebula::scale(Nebula::vec3(Size, 1.0f)) * Nebula::rotate(Rotation, { 0.0f, 0.0f, 1.0f });
	}

	 operator Nebula::mat4() const { return GetTransform(); }
};

struct PillarPair {
	Transform PillarT = Transform();
	Transform PillarB = Transform();

	float speed = 4.0f;
	float screenLeft = 0.0f, screenRight = 0.0f;
	float screenTop = 0.0f, screenBottom = 0.0f;

	float playerX = 0.0f;
	bool scoreable = true;

	PillarPair() { Reset(); }
	PillarPair(float left, float right, float top, float bottom, float playerX = 0.0f, float offset = 0.0f) : 
		screenLeft(left), screenRight(right), screenBottom(bottom), screenTop(top) { 
		Reset();
		PillarT.Position.x += offset;
		PillarB.Position.x += offset;
		PillarT.Size.x = 2.0f;
		PillarB.Size.x = 2.0f;
	}

	void Reset() {
		scoreable = true;

		PillarT.Position.x = screenRight;
		PillarB.Position.x = screenRight;

		float size =	Rand(350, 650) / 100.0f;
		float height = (Rand(0, 500) - 250.0f) / 100.0f;

		float halfSize = size / 2;

		PillarT.Size.y = screenTop - halfSize - height;
		PillarB.Size.y = screenBottom - halfSize + height;
		PillarT.Position.y =  (PillarT.Size.y / 2 + halfSize) + height;
		PillarB.Position.y = -(PillarB.Size.y / 2 + halfSize) + height;
	}

	void Update() {
		PillarT.Position.x -= speed * Nebula::Time::DeltaTime();
		PillarB.Position.x -= speed * Nebula::Time::DeltaTime();

		if (PillarT.Position.x <= playerX && scoreable) {
			Score.CurrentScore += 1;
			scoreable = false;
		}
			

		if (PillarT.Position.x < screenLeft)
			Reset();
	}

	void Render() {
		Nebula::Renderer2D::Draw(NB_QUAD, PillarT.GetTransform(), Nebula::vec4(hueColour.GetRGB(), 0.65f));
		Nebula::Renderer2D::Draw(NB_QUAD, PillarB.GetTransform(), Nebula::vec4(hueColour.GetRGB(), 0.65f));
	}

	bool CheckCollision(Transform* Player) {
		Nebula::vec4 playerMin = Player->GetTransform() * Nebula::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
		Nebula::vec4 playerMax = Player->GetTransform() * Nebula::vec4( 0.5f,  0.5f, 0.0f, 1.0f);

		return AABBvsAABB(playerMin, playerMax,
				(Nebula::mat4)PillarT * Nebula::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
				(Nebula::mat4)PillarT * Nebula::vec4( 0.5f,  0.5f, 0.0f, 1.0f)) ||
			AABBvsAABB(playerMin, playerMax,
				(Nebula::mat4)PillarB * Nebula::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
				(Nebula::mat4)PillarB * Nebula::vec4( 0.5f,  0.5f, 0.0f, 1.0f));
	}
};