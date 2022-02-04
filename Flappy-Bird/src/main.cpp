#include <Nebula.h>
#include <Nebula_EntryPoint.h>

#include "Flappy.h"

class PongApp : public Nebula::Application {
public:
	PongApp(): Nebula::Application("Flappy Nebula") {
		PushLayer(new Flappy);
	}

	~PongApp() { }
};

Nebula::Application* Nebula::CreateApplication(Nebula::ApplicationCommandLineArgs args) {
	return new PongApp;
}