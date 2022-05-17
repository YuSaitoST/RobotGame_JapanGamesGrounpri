float4x4 mWVP_;
float4 vEyeDir_;
float4 vLightDir_;

// lights power
float4 l_a = { 0.3f, 0.3f, 0.3f, 0.0f };    // ambient
float4 l_d = { 0.7f, 0.7f, 0.7f, 0.0f };    // diffuse

// reflectance
float4 k_a = { 1.0f, 1.0f, 1.0f, 1.0f };    // ambient
float4 k_d = { 1.0f, 1.0f, 1.0f, 1.0f };    // diffuse

struct VS_OUTPUT {
	float4 Pos : SV_POSITION;
	float4 Color : COLOR0;
	float2 Tex : TEXCOORD0;
};

VS_OUTPUT VS(
	float4 Pos : POSITION,
	float3 Normal : NORMAL,
	float2 Tex : TEXCOORD0
) {
	VS_OUTPUT Out;

	float4 worldPos = mul(Pos, mWVP_);
	Out.Pos = mul(worldPos, vEyeDir_);
	Out.Tex = Tex;

	float3 L = -vLightDir_;
	float3 N = normalize(mul(Normal, (float3x3)mWVP_));
	Out.Color = l_a * k_a + l_d * k_d * max(0, (dot(L, N)));

	return Out;
}

float4 PS(VS_OUTPUT In) : COLOR0 {
	return In.Color;
}

technique TShader {
	pass P0 {
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
}