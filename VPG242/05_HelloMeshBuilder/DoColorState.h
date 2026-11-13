#pragma once

#include <VGP242Engine/Inc/VGP242Engine.h>

class DoColorState : public VGP242Engine::AppState
{
public:
    void Initialize() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Terminate() override;

private:

	VGP242Engine::Graphics::MeshBuffer mMeshBuffer;
	VGP242Engine::Graphics::VertexShader mVertexShader;
	VGP242Engine::Graphics::PixelShader mPixelShader;
	VGP242Engine::Graphics::Camera mCamera;
	VGP242Engine::Graphics::ConstantBuffer mTransformBuffer;

};
