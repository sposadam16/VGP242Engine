#include <VGP242Engine/Inc/VGP242Engine.h>
#include "DoColorState.h"
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    VGP242Engine::AppConfig config;
    config.appName = L"Hello MeshBuilder";
    config.winWidth = 720;
    config.winHeight = 720;

    VGP242Engine::App& myApp = VGP242Engine::MainApp();
    myApp.AddState<DoColorState>("DoColorState");
	myApp.Run(config);
    return 0;
}
