
struct VTX_IN
{
    float3 vPos : POSITION;
    float4 vColor : COLOR;
};

struct VTX_OUT
{
    float4 vPos : SV_Position;
    float4 vColor : COLOR;
};

cbuffer TRANSFORM : register(b0)
{
    float3 cbPos;
    int padd1;
    float3 cbScale;
    int padd2;
};

cbuffer PERSPECTIVE : register(b2)
{
    float4x4 cbWorld;
    float4x4 cbView;
    float4x4 cbProj;
};

VTX_OUT VS_Test(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    output.vPos = float4(_in.vPos + cbPos.xyz, 1.f);
    output.vPos.xyz *= cbScale;
    
    output.vPos = mul(output.vPos, cbWorld);
    output.vPos = mul(output.vPos, cbView);
    output.vPos = mul(output.vPos, cbProj);
    output.vColor = _in.vColor;
    
    return output;
}
