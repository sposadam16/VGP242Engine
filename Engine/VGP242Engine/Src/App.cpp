#include "Precompiled.h"
#include "App.h"


using namespace VGP242Engine;
using namespace VGP242Engine::Core;

void App::Run(const AppConfig& config)
{
	LOG("App Started");

	// initialize all singletons

	// initialize starting state
	Window myWindow;
	myWindow.Initialize(
		GetModuleHandle(nullptr),
		config.appName,
		config.winWidth,
		config.winHeight
	);
	//initialize starting state

	// updates
	mIsRunning = true;
	while (mIsRunning)
	{
		myWindow.ProcessMessage();
		// updating all that need updates
		if (!myWindow.IsActive())
		{

			Quit();
			continue;
		}
	}
	LOG("App is Terminating");

	//termite last state

	// terminate all singletons

	myWindow.Terminate();
}
	
void App::Quit()
{
	mIsRunning = false;
}
