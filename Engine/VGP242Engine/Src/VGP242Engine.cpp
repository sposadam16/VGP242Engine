#include "Precompiled.h"
#include "VGP242Engine.h"

VGP242Engine::App& VGP242Engine::MainApp()
{
    static App sApp;
    return sApp;
}