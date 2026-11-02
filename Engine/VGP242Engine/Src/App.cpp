#include "Precompiled.h"
#include "App.h"
#include "AppState.h"

using namespace VGP242Engine;
using namespace VGP242Engine::Core;
using namespace VGP242Engine::Graphics;

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
	auto handle = myWindow.GetWindowHandle();
	GraphicsSystem::StaticInitialize(handle, false);
	//initialize starting state
	ASSERT(mCurrentState != nullptr, "App: no state is set");
	mCurrentState->Initialize();
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
		if (mNextState != nullptr)
		{
			mCurrentState->Terminate();
			mCurrentState = std::exchange(mNextState, nullptr);
			mCurrentState->Initialize();
		}
		float deltaTime = TimeUtil::GetDeltaTime();

#if defined(_DEBUG)
		if (deltaTime > 0.5f)
		{
			continue;
		}
#endif
		mCurrentState->Update(deltaTime);

		GraphicsSystem* gs = GraphicsSystem::Get();
		gs->BeginRender();
		mCurrentState->Render();
		mCurrentState->DebugUI();
		gs->EndRender();
	}
	LOG("App is Terminating");
	// terminate last state
	mCurrentState->Terminate();

	// terminate all singletons
	GraphicsSystem::StaticTerminate();
	myWindow.Terminate();
}
	
void App::Quit()
{
	mIsRunning = false;
}

void App::ChangeState(const std::string& stateName)
{
	auto iter = mAppStates.find(stateName);
	if (iter != mAppStates.end())
	{
		mNextState = iter->second.get();
	}
}
