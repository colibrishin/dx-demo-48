Texture2D shaderTexture : register(t0);
SamplerState SampleType : register(s0);

struct VTX_OUT
{
    float4 vPos : SV_Position;
    float4 vColor : COLOR;
    float2 vTex : TEXCOORD0;
};

float4 PS_Test(VTX_OUT _in) : SV_Target
{
    float4 texColor;
    texColor = shaderTexture.Sample(SampleType, _in.vTex);

    return texColor;
}