#pragma once
#include <VGP242Engine/Inc/VGP242Engine.h>


class MainState : public VGP242Engine::AppState
{
public:
    void Initialize() override;
    void Update(float deltaTime) override;
    void Terminate() override;
};