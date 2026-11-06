#include <VGP242Engine/Inc/VGP242Engine.h>
#include "DoSomethingState.h"
#include "DoColorState.h"
#include "ThirdShapeState.h"
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    VGP242Engine::AppConfig config;
    config.appName = L"Hello Shapes";
    config.winWidth = 720;
    config.winHeight = 720;

    VGP242Engine::App& myApp = VGP242Engine::MainApp();
	myApp.AddState<DoSomethingState>("DoSomethingState");
    myApp.AddState<DoColorState>("DoColorState");
    myApp.AddState<ThirdShapeState>("ThirdShapeState");
	myApp.Run(config);
    return 0;
}
