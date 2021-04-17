struct VOut
{
    float4 position : SV_POSITION;
};

VOut VShader(float4 position : POSITION)
{
    VOut output;

    output.position = position;
    return output;
}

float4 PShader(float4 position : SV_POSITION, float4 color : COLOR)  : SV_TARGET
{
    return float4(1.0f, 1.0f, 1.0f, 1.0f);
}