#include "DoSomethingState.h"

using namespace VGP242Engine::Graphics;
using namespace VGP242Engine::Input;

void DoSomethingState::Initialize()
{
    // Arrow: 3 triangles. Clear old vertices when returning to this state.
    mVertices.clear();

    mVertices.push_back({ { -0.75f, -0.20f, 0.0f } });
    mVertices.push_back({ { -0.75f, 0.20f, 0.0f } });
    mVertices.push_back({ { 0.15f, 0.20f, 0.0f } });

    mVertices.push_back({ { -0.75f, -0.20f, 0.0f } });
    mVertices.push_back({ { 0.15f, 0.20f, 0.0f } });
    mVertices.push_back({ { 0.15f, -0.20f, 0.0f } });

    mVertices.push_back({ { 0.15f, -0.55f, 0.0f } });
    mVertices.push_back({ { 0.15f, 0.55f, 0.0f } });
    mVertices.push_back({ { 0.75f, 0.00f, 0.0f } });

    // Start creating the components that communicate with the GPU.
    auto device = GraphicsSystem::Get()->GetDevice();

    // Build the vertex buffer, which stores the vertices to give to the GPU.
    D3D11_BUFFER_DESC bufferDesc{};
    bufferDesc.ByteWidth = static_cast<UINT>(mVertices.size() * sizeof(Vertex));
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.MiscFlags = 0;
    bufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = mVertices.data();

    HRESULT hr = device->CreateBuffer(&bufferDesc, &initData, &mVertexBuffer);
    ASSERT(SUCCEEDED(hr), "Failed to create vertex buffer");

    // ================================================================================

    // Bind to the shader file.
    std::filesystem::path shaderFilePath = L"../../Assets/Shaders/DoSomething.fx";

    DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    ID3DBlob* shaderBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;

    hr = D3DCompileFromFile(
        shaderFilePath.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "VS",
        "vs_5_0",
        shaderFlags,
        0,
        &shaderBlob,
        &errorBlob);

    if (errorBlob != nullptr && errorBlob->GetBufferPointer() != nullptr)
    {
        LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
    }
    

    ASSERT(SUCCEEDED(hr), "Failed to compile vertex shader");

    hr = device->CreateVertexShader(
        shaderBlob->GetBufferPointer(),
        shaderBlob->GetBufferSize(),
        nullptr,
        &mVertexShader);

    ASSERT(SUCCEEDED(hr), "Failed to create vertex shader");
    //================================================================================
    //what is the make up of the vertex
    std::vector<D3D11_INPUT_ELEMENT_DESC> vertexLayout;
    vertexLayout.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
        D3D11_APPEND_ALIGNED_ELEMENT });

    hr = device->CreateInputLayout(
        vertexLayout.data(),
        static_cast<UINT>(vertexLayout.size()),
        shaderBlob->GetBufferPointer(),
        shaderBlob->GetBufferSize(),
        &mInputLayout);

    ASSERT(SUCCEEDED(hr), "Failed to create input layout");

    SafeRelease(shaderBlob);
    SafeRelease(errorBlob);

    //================================================================================
    //bind pixel shader to shader file
    // Bind pixel shader to shader file.
    hr = D3DCompileFromFile(
        shaderFilePath.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "PS",
        "ps_5_0",
        shaderFlags,
        0,
        &shaderBlob,
        &errorBlob);

    if (errorBlob != nullptr && errorBlob->GetBufferPointer() != nullptr)
    {
        LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
    }

    ASSERT(SUCCEEDED(hr), "Failed to compile pixel shader");

    hr = device->CreatePixelShader(
        shaderBlob->GetBufferPointer(),
        shaderBlob->GetBufferSize(),
        nullptr,
        &mPixelShader);

    ASSERT(SUCCEEDED(hr), "Failed to create pixel shader");

    SafeRelease(shaderBlob);
    SafeRelease(errorBlob);
}
void DoSomethingState::Update(float deltaTime)
{
    // Leave for now.
    if (InputSystem::Get()->IsKeyPressed(KeyCode::SPACE))
    {
        VGP242Engine::MainApp().ChangeState("DoColorState");
    }
}

void DoSomethingState::Render()
{
    auto context = GraphicsSystem::Get()->GetContext();

    // Bind all the buffers.
    context->VSSetShader(mVertexShader, nullptr, 0);
    context->IASetInputLayout(mInputLayout);
    context->PSSetShader(mPixelShader, nullptr, 0);

    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Draw.
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
    context->Draw(static_cast<UINT>(mVertices.size()), 0);
}

void DoSomethingState::Terminate()
{
    SafeRelease(mVertexBuffer);
    SafeRelease(mVertexShader);
    SafeRelease(mInputLayout);
    SafeRelease(mPixelShader);
}
