#include "MainState.h"

using namespace VGP242Engine::Input;

void MainState::Initialize()
{
    LOG("MAIN STATE INITIALIZED");
}

void MainState::Update(float deltaTime)
{
    if (InputSystem::Get()->IsKeyPressed(KeyCode::SPACE))
    {
        VGP242Engine::MainApp().ChangeState("GameState");   
    }
}

void MainState::Terminate()
{
    LOG("MAIN STATE IS TERMINATED");
}