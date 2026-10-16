#include <VGP242Engine/Inc/VGP242Engine.h>

using namespace VGP242Engine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"HelloWindow";
	App myApp;
	myApp.Run(config);
		return 0;
}