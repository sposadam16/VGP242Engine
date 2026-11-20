#pragma once

namespace VGP242Engine::Graphics
{
    class Texture
    {
    public:
        // Removes reference of texture in the GPU.
        static void UnbindPS(uint32_t slot);

        Texture() = default;
        virtual ~Texture();

        // Delete copy constructors.
        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        // Allow move with noexcept.
        Texture(Texture&& rhs) noexcept;
        Texture& operator=(Texture&& rhs) noexcept;

        virtual void Initialize(const std::filesystem::path& fileName);
        virtual void Terminate();

        void BindVS(uint32_t slot) const;
        void BindPS(uint32_t slot) const;

        void* GetRawData() const;

    protected:
        ID3D11ShaderResourceView* mShaderResourceView = nullptr;
    };
}