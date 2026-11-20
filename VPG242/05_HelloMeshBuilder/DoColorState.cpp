#include "DoColorState.h"

using namespace VGP242Engine::Graphics;
using namespace VGP242Engine::Input;

void DoColorState::Initialize()
{
    // srand
    //setup camera
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

    mShapeIndex = 0;
    CreateCurrentMesh();
    std::filesystem::path shaderPath = L"../../Assets/Shaders/DoTransform.fx";
    mVertexShader.Initialize<VertexPC>(shaderPath);
    mPixelShader.Initialize(shaderPath);

	mTransformBuffer.Initialize(sizeof(Math::Matrix4));
}
void DoColorState::CreateCurrentMesh()
{
    MeshPC mesh;
    switch (mShapeIndex)
    {
    case 0: mesh = MeshBuilder::CreateCubePC(1.0f); break;
    case 1: mesh = MeshBuilder::CreateRectanglePC(1.0f, 1.5f, 0.5f); break;
    case 2: mesh = MeshBuilder::CreatePyramidPC(1.5f, 1.5f); break;
    case 3: mesh = MeshBuilder::CreatePlanePC(10, 10, 0.2f, true); break;
    case 4: mesh = MeshBuilder::CreatePlanePC(10, 10, 0.2f, false); break;
    case 5: mesh = MeshBuilder::CreateCylinderPC(32, 2); break;
    case 6: mesh = MeshBuilder::CreateSpherePC(32, 16, 1.0f); break;
    }
    mMeshBuffer.Terminate();
    mMeshBuffer.Initialize(mesh);
    const char* names[] = { "Cube", "Box", "Pyramid", "Horizontal plane",
        "Vertical plane", "Closed cylinder", "Sphere" };
    LOG("Mesh: %s (SPACE to change)", names[mShapeIndex]);
}

void DoColorState::Update(float deltaTime)
{
    InputSystem* input = InputSystem::Get();
    if (input->IsKeyPressed(KeyCode::SPACE))
    {
        mShapeIndex = (mShapeIndex + 1) % 7;
        CreateCurrentMesh();
    }

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
    mTransformBuffer.Terminate();
	mMeshBuffer.Terminate();
    mVertexShader.Terminate();
	mPixelShader.Terminate();   
}
