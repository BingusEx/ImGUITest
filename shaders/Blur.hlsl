cbuffer BlurBuffer {
    float2 texelSize;
};

Texture2D inputTexture : register(t0);
SamplerState samplerState : register(s0);

float4 HorizontalBlur(float2 texCoord : TEXCOORD) : SV_Target {
    float4 color = float4(0, 0, 0, 0);
    float weights[5] = {0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216};
    for (int i = -4; i <= 4; ++i) {
        color += inputTexture.Sample(samplerState, texCoord + float2(i, 0) * texelSize) * weights[abs(i)];
    }
    return color;
}

float4 VerticalBlur(float2 texCoord : TEXCOORD) : SV_Target {
    float4 color = float4(0, 0, 0, 0);
    float weights[5] = {0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216};
    for (int i = -4; i <= 4; ++i) {
        color += inputTexture.Sample(samplerState, texCoord + float2(0, i) * texelSize) * weights[abs(i)];
    }
    return color;
}