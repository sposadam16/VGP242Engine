#include <VGP242Engine/Inc/VGP242Engine.h>
#include "MainState.h"
#include "GameState.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    VGP242Engine::AppConfig config;
    config.appName = L"Hello App State";

    VGP242Engine::App& myApp = VGP242Engine::MainApp();
    myApp.AddState<MainState>("MainState");
    myApp.AddState<GameState>("GameState");
    myApp.Run(config);

    return 0;
}