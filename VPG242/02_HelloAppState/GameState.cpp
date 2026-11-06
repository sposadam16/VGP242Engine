#include "GameState.h"

using namespace VGP242Engine::Input;

void GameState::Initialize()
{
    LOG("GAME STATE INITIALIZED");
}

void GameState::Update(float deltaTime)
{
    if (InputSystem::Get()->IsKeyPressed(KeyCode::SPACE))
    {
        VGP242Engine::MainApp().ChangeState("MainState");
    }
}

void GameState::Terminate()
{
    LOG("GAME STATE IS TERMINATED");
}