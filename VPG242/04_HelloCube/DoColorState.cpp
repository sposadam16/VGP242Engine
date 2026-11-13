#include "DoColorState.h"

using namespace VGP242Engine::Graphics;
using namespace VGP242Engine::Input;

void DoColorState::Initialize()
{
    //setup camera
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
    // Cube centered at the local origin: 6 faces, 2 clockwise triangles per face.
    mVertices.clear();

    // Front (-Z)
    mVertices.push_back({ { -0.5f, -0.5f, -0.5f }, Colors::Red });
    mVertices.push_back({ { -0.5f, 0.5f, -0.5f }, Colors::Red });
    mVertices.push_back({ { 0.5f, 0.5f, -0.5f }, Colors::Red });
    mVertices.push_back({ { -0.5f, -0.5f, -0.5f }, Colors::Red });
    mVertices.push_back({ { 0.5f, 0.5f, -0.5f }, Colors::Red });
    mVertices.push_back({ { 0.5f, -0.5f, -0.5f }, Colors::Red });

    // Back (+Z)
    mVertices.push_back({ { 0.5f, -0.5f, 0.5f }, Colors::Cyan });
    mVertices.push_back({ { 0.5f, 0.5f, 0.5f }, Colors::Cyan });
    mVertices.push_back({ { -0.5f, 0.5f, 0.5f }, Colors::Cyan });
    mVertices.push_back({ { 0.5f, -0.5f, 0.5f }, Colors::Cyan });
    mVertices.push_back({ { -0.5f, 0.5f, 0.5f }, Colors::Cyan });
    mVertices.push_back({ { -0.5f, -0.5f, 0.5f }, Colors::Cyan });

    // Left (-X)
    mVertices.push_back({ { -0.5f, -0.5f, 0.5f }, Colors::Lime });
    mVertices.push_back({ { -0.5f, 0.5f, 0.5f }, Colors::Lime });
    mVertices.push_back({ { -0.5f, 0.5f, -0.5f }, Colors::Lime });
    mVertices.push_back({ { -0.5f, -0.5f, 0.5f }, Colors::Lime });
    mVertices.push_back({ { -0.5f, 0.5f, -0.5f }, Colors::Lime });
    mVertices.push_back({ { -0.5f, -0.5f, -0.5f }, Colors::Lime });

    // Right (+X)
    mVertices.push_back({ { 0.5f, -0.5f, -0.5f }, Colors::Magenta });
    mVertices.push_back({ { 0.5f, 0.5f, -0.5f }, Colors::Magenta });
    mVertices.push_back({ { 0.5f, 0.5f, 0.5f }, Colors::Magenta });
    mVertices.push_back({ { 0.5f, -0.5f, -0.5f }, Colors::Magenta });
    mVertices.push_back({ { 0.5f, 0.5f, 0.5f }, Colors::Magenta });
    mVertices.push_back({ { 0.5f, -0.5f, 0.5f }, Colors::Magenta });

    // Top (+Y)
    mVertices.push_back({ { -0.5f, 0.5f, -0.5f }, Colors::Blue });
    mVertices.push_back({ { -0.5f, 0.5f, 0.5f }, Colors::Blue });
    mVertices.push_back({ { 0.5f, 0.5f, 0.5f }, Colors::Blue });
    mVertices.push_back({ { -0.5f, 0.5f, -0.5f }, Colors::Blue });
    mVertices.push_back({ { 0.5f, 0.5f, 0.5f }, Colors::Blue });
    mVertices.push_back({ { 0.5f, 0.5f, -0.5f }, Colors::Blue });

    // Bottom (-Y)
    mVertices.push_back({ { -0.5f, -0.5f, 0.5f }, Colors::Yellow });
    mVertices.push_back({ { -0.5f, -0.5f, -0.5f }, Colors::Yellow });
    mVertices.push_back({ { 0.5f, -0.5f, -0.5f }, Colors::Yellow });
    mVertices.push_back({ { -0.5f, -0.5f, 0.5f }, Colors::Yellow });
    mVertices.push_back({ { 0.5f, -0.5f, -0.5f }, Colors::Yellow });
    mVertices.push_back({ { 0.5f, -0.5f, 0.5f }, Colors::Yellow });

    mMeshBuffer.Initialize(mVertices.data(), sizeof(VertexPC), static_cast<uint32_t>(mVertices.size()));
    std::filesystem::path shaderPath = L"../../Assets/Shaders/DoTransform.fx";
    mVertexShader.Initialize<VertexPC>(shaderPath);
    mPixelShader.Initialize(shaderPath);

	mTransformBuffer.Initialize(sizeof(Math::Matrix4));
}
void DoColorState::Update(float deltaTime)
{
    InputSystem* input = InputSystem::Get();

    const float moveSpeed = (input->IsKeyDown(KeyCode::LSHIFT)) ? 10.0f : 1.0f;
    const float turnSpeed = 0.1f;

    if (input->IsKeyDown(KeyCode::W))
    {
        mCamera.Walk(moveSpeed * deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::S))
    {
        mCamera.Walk(-moveSpeed * deltaTime);
    }

    if (input->IsKeyDown(KeyCode::D))
    {
        mCamera.Strafe(moveSpeed * deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::A))
    {
        mCamera.Strafe(-moveSpeed * deltaTime);
    }
    if (input->IsKeyDown(KeyCode::E))
    {
        mCamera.Rise(moveSpeed * deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::Q))
    {
        mCamera.Rise(-moveSpeed * deltaTime);
    }
    if (input->IsMouseDown(MouseButton::RBUTTON))
    {
        mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
        mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}

void DoColorState::Render()
{
    mVertexShader.Bind();
    mPixelShader.Bind();
	mTransformBuffer.BindVS(0);

    // Update buffer data.
    Math::Matrix4 matWorld = Math::Matrix4::Identity;
    Math::Matrix4 matView = mCamera.GetViewMatrix();
    Math::Matrix4 matProj = mCamera.GetProjectionMatrix();
    Math::Matrix4 matFinal = matWorld * matView * matProj;
    Math::Matrix4 wvp = Math::Transpose(matFinal);
    mTransformBuffer.Update(&wvp);

    mMeshBuffer.Render();
}

void DoColorState::Terminate()
{
    mVertices.clear();
	mTransformBuffer.Terminate();
	mMeshBuffer.Terminate();
    mVertexShader.Terminate();
	mPixelShader.Terminate();   
}
