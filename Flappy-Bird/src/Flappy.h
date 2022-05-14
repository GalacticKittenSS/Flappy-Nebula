#pragma once

#include <Nebula.h>
#include "Entities.h"

class Flappy : public Nebula::Layer {
public:
	Flappy() : Nebula::Layer("Flappy"), SceneCam(-16.0f, 16.0f, -9.0f, 9.0f) { }
	~Flappy() { }

	void Attach() override;
	void Detach() override;

	void OnEvent(Nebula::Event& e) override;

	void Update(Nebula::Timestep ts) override;
	void Render() override;
private:
	bool OnKeyPressed(Nebula::KeyPressedEvent& e);

	void SwitchState();
	void OnDeath();
	
	void Play();
	void Reset();
private:
	Nebula::OrthographicCamera SceneCam;
	Transform Player;

	enum GameState {
		Paused, Running
	};

	GameState state = GameState::Paused;
	Nebula::Array<PillarPair> Pillars;
};