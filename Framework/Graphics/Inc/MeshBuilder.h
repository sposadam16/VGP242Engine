#pragma once

#include "MeshTypes.h"

namespace VGP242Engine::Graphics
{
    class MeshBuilder
    {
    public:
        //cube
        static MeshPC CreateCubePC(float size, const Color& color);
    };
}