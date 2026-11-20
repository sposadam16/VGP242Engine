#pragma once

#include "MeshTypes.h"

namespace VGP242Engine::Graphics
{
    class MeshBuilder
    {
    public:
        //cube
        static MeshPC CreateCubePC(float size, const Color& color);
        static MeshPC CreateCubePC(float size);
        static MeshPC CreatePyramidPC(float size, float height);

		// rectangle

		static MeshPC CreateRectanglePC(float width, float height, float depth);
        
        //plane
        static MeshPC CreatePlanePC(int numRows, int numCols, float spacing, bool horizontal = true);
        static MeshPX CreatePlanePX(int numRows, int numCols, float spacing, bool horizontal = true);

        //cylinder
        static MeshPC CreateCylinderPC(int slices, int rings);
		//sphere
        static MeshPC CreateSpherePC(int slices, int rings,float radius);
        static MeshPX CreateSpherePX(int slices, int rings,float radius);

		static MeshPX CreateSkySpherePX(int slices, int rings, float radius);
    };
}
