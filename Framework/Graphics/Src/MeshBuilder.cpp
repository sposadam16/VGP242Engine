#include"Precompiled.h"
#include"MeshBuilder.h"

using namespace VGP242Engine;
using namespace VGP242Engine::Graphics;

namespace
{
    Color GetNextColor(int& index)
    {
        static const Color colorTable[] = {
            Colors::Red,
            Colors::Green,
            Colors::Blue,
            Colors::Yellow,
            Colors::Cyan,
            Colors::Magenta,
            Colors::Orange,
            Colors::Purple,
            Colors::Pink,
            Colors::Brown,
            Colors::Gray,
            Colors::White
        };
        index = (index + 1) % std::size(colorTable);
        return colorTable[index];
    }
    void CreateCubeVertices(std::vector<uint32_t>& indices)
    {
        indices = {
            // Front
            0, 1, 2,
            0, 2, 3,

            // Back
            7, 5, 4,
            7, 6, 5,

            // Right
            3, 2, 6,
            3, 6, 7,

            // Left
            4, 5, 1,
            4, 1, 0,

            // Top
            1, 5, 6,
            1, 6, 2,

            // Bottom
            0, 3, 7,
            0, 7, 4,
        };
	}
    void CreatePlaneIndices(
        std::vector<uint32_t>& indices, int numRows, int numColumns)
    {
        for (int r = 0; r < numRows; ++r)
        {
            for (int c = 0; c < numColumns; ++c)
            {
                int i = (r * (numColumns + 1)) + c;

                // Triangle 0
                indices.push_back(i);
                indices.push_back(i + numColumns + 1);
                indices.push_back(i + numColumns + 2);

                // Triangle 1
                indices.push_back(i);
                indices.push_back(i + numColumns + 2);
                indices.push_back(i + 1);
            }
        }
    }
}

MeshPC MeshBuilder::CreateCubePC(float size, const Color& color)
{
    MeshPC mesh;

    const float hs = size * 0.5f;

    // Front
    mesh.vertices.push_back({ { -hs, -hs, -hs }, color });
    mesh.vertices.push_back({ { -hs,  hs, -hs }, color });
    mesh.vertices.push_back({ {  hs,  hs, -hs }, color });
    mesh.vertices.push_back({ {  hs, -hs, -hs }, color });

    // Back
    mesh.vertices.push_back({ { -hs, -hs,  hs }, color });
    mesh.vertices.push_back({ { -hs,  hs,  hs }, color });
    mesh.vertices.push_back({ {  hs,  hs,  hs }, color });
    mesh.vertices.push_back({ {  hs, -hs,  hs }, color });
  
    CreateCubeVertices(mesh.indices);   

    return mesh;
}
MeshPC MeshBuilder::CreateCubePC(float size)
{
    MeshPC mesh;
    int index = rand() & 37;
	const float hs = size * 0.5f;

    // Front
    mesh.vertices.push_back({ { -hs, -hs, -hs }, GetNextColor(index) });
    mesh.vertices.push_back({ { -hs,  hs, -hs }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hs,  hs, -hs }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hs, -hs, -hs }, GetNextColor(index) });

    // Back
    mesh.vertices.push_back({ { -hs, -hs,  hs }, GetNextColor(index)});
    mesh.vertices.push_back({ { -hs,  hs,  hs }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hs,  hs,  hs }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hs, -hs,  hs }, GetNextColor(index) });
    CreateCubeVertices(mesh.indices);

    return mesh;
}
MeshPC MeshBuilder::CreatePyramidPC(float size, float height)
{
    MeshPC mesh;
    const float hs = size * 0.5f;
    const float hh = height * 0.5f;
    int index = rand() % 12;

    mesh.vertices.push_back({ { -hs, -hh, -hs }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hs, -hh, -hs }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hs, -hh,  hs }, GetNextColor(index) });
    mesh.vertices.push_back({ { -hs, -hh,  hs }, GetNextColor(index) });
    mesh.vertices.push_back({ { 0.0f, hh, 0.0f }, GetNextColor(index) });

    // Four sides and a closed square base, clockwise from outside.
    mesh.indices = {
        0, 4, 1,
        1, 4, 2,
        2, 4, 3,
        3, 4, 0,
        0, 1, 2,
        0, 2, 3
    };
    return mesh;
}
MeshPC MeshBuilder::CreateRectanglePC(float width, float height, float depth)
{
    MeshPC mesh;

	int index = rand() & 37;
    const float hw = width * 0.5f;
    const float hh = height * 0.5f;
    const float hd = depth * 0.5f;

    mesh.vertices.push_back({ { -hw, -hh, -hd }, GetNextColor(index) });
    mesh.vertices.push_back({ { -hw,  hh, -hd }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hw,  hh, -hd }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hw, -hh, -hd }, GetNextColor(index) });

    mesh.vertices.push_back({ { -hw, -hh,  hd }, GetNextColor(index) });
    mesh.vertices.push_back({ { -hw,  hh,  hd }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hw,  hh,  hd }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hw, -hh,  hd }, GetNextColor(index) });

    CreateCubeVertices(mesh.indices);
    return mesh;
}

MeshPC MeshBuilder::CreatePlanePC(int numRows, int numColumns, float spacing, bool horizontal)
{
    MeshPC mesh;

    int index = rand() % 40;

    const float hpw = static_cast<float>(numColumns) * spacing * 0.5f;
    const float hph = static_cast<float>(numRows) * spacing * 0.5f;

    float w = -hpw;
    float h = -hph;

    for (int r = 0; r <= numRows; ++r)
    {
        for (int c = 0; c <= numColumns; ++c)
        {
            Math::Vector3 pos = (horizontal) ? Math::Vector3(w, 0.0f, h): Math::Vector3(w, h, 0.0f);

            mesh.vertices.push_back({ pos, GetNextColor(index) });
            w += spacing;
        }

        w = -hpw;
        h += spacing;
    }

    CreatePlaneIndices(mesh.indices, numRows, numColumns);
    return mesh;


}
MeshPX MeshBuilder::CreatePlanePX(
    int numRows, int numColumns, float spacing, bool horizontal)
{
    MeshPX mesh;

    int index = rand() % 40;

    const float hpw = static_cast<float>(numColumns) * spacing * 0.5f;
    const float hph = static_cast<float>(numRows) * spacing * 0.5f;
    const float uInc = 1.0f / static_cast<float>(numColumns);
    const float vInc = -1.0f / static_cast<float>(numRows);

    float w = -hpw;
    float h = -hph;
    float u = 0.0f;
    float v = 1.0f;

    for (int r = 0; r <= numRows; ++r)
    {
        for (int c = 0; c <= numColumns; ++c)
        {
            Math::Vector3 pos = (horizontal)
                ? Math::Vector3(w, 0.0f, h)
                : Math::Vector3(w, h, 0.0f);

            mesh.vertices.push_back({ pos, { u, v } });
            w += spacing;
            u += uInc;
        }

        w = -hpw;
        h += spacing;
        u = 0.0f;
        v += vInc;
    }

    CreatePlaneIndices(mesh.indices, numRows, numColumns);
    return mesh;
}


MeshPC MeshBuilder::CreateCylinderPC(int slices, int rings)
{
    MeshPC mesh;

    int index = rand() % 39;
    const float hh = static_cast<float>(rings) * 0.5f;
    const float fSlices = static_cast<float>(slices);

    for (int r = 0; r <= rings; ++r)
    {
        float ring = static_cast<float>(r);

        for (int s = 0; s <= slices; ++s)
        {
            float slice = static_cast<float>(s);
            float rotation = (slice / fSlices) * Math::Constants::TwoPi;

            mesh.vertices.push_back({
                {
                    sin(rotation),
                    ring - hh,
                    -cos(rotation)
                },
                GetNextColor(index)
                });
        }
    }
	CreatePlaneIndices(mesh.indices, rings, slices);
    // Top center
    mesh.vertices.push_back({ { 0.0f, hh, 0.0f }, GetNextColor(index) });

    // Bottom center
    mesh.vertices.push_back({ { 0.0f, -hh, 0.0f }, GetNextColor(index) });

    int topIndex = mesh.vertices.size() - 2;
    int bottomIndex = mesh.vertices.size() - 1;

    for (int s = 0; s < slices; ++s)
    {
        // Bottom triangle
        mesh.indices.push_back(bottomIndex);
        mesh.indices.push_back(s);
        mesh.indices.push_back(s + 1);

        // Top triangle
        int topRowIndex = topIndex - slices - 1 + s;
        mesh.indices.push_back(topIndex);
        mesh.indices.push_back(topRowIndex + 1);
        mesh.indices.push_back(topRowIndex);
    }
    return mesh;
}

MeshPC MeshBuilder::CreateSpherePC(int slices, int rings, float radius)
{
    MeshPC mesh;

    int index = rand() % 42;

    const float vertRotation =(Math::Constants::Pi / static_cast<float>(rings));
    const float horzRotation =(Math::Constants::TwoPi / static_cast<float>(slices));

    for (int r = 0; r <= rings; ++r)
    {
        float ring = static_cast<float>(r);
        float phi = ring * vertRotation;

        for (int s = 0; s <= slices; ++s)
        {
            float slice = static_cast<float>(s);
            float rotation = slice * horzRotation;

            mesh.vertices.push_back({
                {
                    radius * sin(rotation) * sin(phi),
                    radius * cos(phi),
                    radius * cos(rotation) * sin(phi)
                },
                GetNextColor(index)
                });
        }
    }

    CreatePlaneIndices(mesh.indices, rings, slices);

    return mesh;
}
MeshPX MeshBuilder::CreateSpherePX(int slices, int rings, float radius)
{
    MeshPX mesh;

    const float uInc = 1.0f / static_cast<float>(slices);
    const float vInc = 1.0f / static_cast<float>(rings);

    const float vertRotation =(Math::Constants::Pi / static_cast<float>(rings));
    const float horzRotation =(Math::Constants::TwoPi / static_cast<float>(slices));

    for (int r = 0; r <= rings; ++r)
    {
        float ring = static_cast<float>(r);
        float phi = ring * vertRotation;

        for (int s = 0; s <= slices; ++s)
        {
            float slice = static_cast<float>(s);
            float rotation = slice * horzRotation;

            mesh.vertices.push_back({
                {
                    radius * sin(rotation) * sin(phi),
                    radius * cos(phi),
                    radius * cos(rotation) * sin(phi)
                },
                { slice * uInc, ring * vInc }
                });
        }
    }

    CreatePlaneIndices(mesh.indices, rings, slices);

    return mesh;
}
MeshPX MeshBuilder::CreateSkySpherePX(int rings, int slices, float radius)
{
    MeshPX mesh;
    int index = rand() % 69;
    const float vertRotation = (Math::Constants::Pi / static_cast<float>(rings));
    const float horzRotation = (Math::Constants::TwoPi / static_cast<float>(slices));

    const float uStep = 1.0f / static_cast<float>(slices);
    const float vStep = 1.0f / static_cast<float>(rings);

    for (int r = 0; r <= rings; ++r)
    {
        float ring = static_cast<float>(r);
        float phi = ring * vertRotation;
        for (int s = 0; s <= slices; ++s)
        {
            float slice = static_cast<float>(s);
            float rotation = slice * horzRotation;
            float u = uStep * slice;
            float v = vStep * ring;
            mesh.vertices.push_back({ {
                    radius * cos(rotation) * sin(phi),
                    radius * cos(phi),
                    radius * sin(rotation) * sin(phi)
                    }, {u,v} });

        }
    }
    CreatePlaneIndices(mesh.indices, rings, slices);
    return mesh;
}