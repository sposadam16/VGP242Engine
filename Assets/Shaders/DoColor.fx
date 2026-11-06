// Simple shader that takes positions and can add color.

// Need to know what information is in a vertex.
struct VS_INPUT
{
    float3 position : POSITION;
    float4 color : COLOR;
};

// Need a resulting set of data after processing the vertex.
struct VS_OUTPUT
{
    float4 position : SV_Position;
    float4 color : COLOR;
};

// Need a function to apply information to the vertex for every vertex.
// 3D Graphics and Applications: this is the primitives manager.
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = float4(input.position, 1.0f);
    output.color = input.color;
    return output;
}

// Need a function to apply the color of a pixel.
float4 PS(VS_OUTPUT input) : SV_Target
{
    return input.color;
}