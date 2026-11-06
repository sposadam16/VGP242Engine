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
    struct Vertex
    {
        VGP242Engine::Math::Vector3 position = VGP242Engine::Math::Vector3::Zero;
		VGP242Engine::Color color = VGP242Engine::Colors::White;
    };
    using Vertices = std::vector<Vertex>;
    Vertices mVertices;

    //shape info
    ID3D11Buffer* mVertexBuffer = nullptr;
    //bind do the VS function
    ID3D11VertexShader* mVertexShader = nullptr;
    //Tell all the configuration of the vertex
	ID3D11InputLayout* mInputLayout = nullptr;
    // bind to the ps funciton
	ID3D11PixelShader* mPixelShader = nullptr;
};
