//hlsl 컴파일 대상 X
struct VertexInput
{
    float4 position : POSITION0; //시멘틱 용도
    float4 color : COLOR0;
};
// PI
struct PixelInput
{
    float4 position : SV_POSITION; //화면좌표계 포지션
    float4 color : COLOR0;
};

//오브젝트의 크기 회전 이동
cbuffer VS_WVP : register(b0) //register(b0)
{
    matrix WVP;
}
//상수 버퍼
cbuffer VS_COLOR : register(b1)
{
    //4 개의 4바이트
    float4 color;
}

cbuffer PS_LIGHT : register(b0)
{
	float2 screenPos; //스크린좌표
	float radius; //반지름크기
	float select; //남는값
	float4 lightColor; //조명 색
	float4 outColor; //외곽 색
};

PixelInput VS(VertexInput input)
{
    //공간변환이 있을 예정인 곳
    PixelInput output;
    //카메라,월드 까지 적용된 공간변환
    output.position = mul(input.position, WVP);
    
    //             꼭지점 색깔     0~2 -1     -1~ 1
    output.color = input.color + (color * 2.0f - 1.0f);
    
    
    saturate(output.color);
    
    return output;
}
//->pixel  PS   ->color
//픽셀쉐이더 진입 함수
float4 PS(PixelInput input) : SV_TARGET 
{
	//if (input.position.y > 200.0f)
	//{
	//	return float4(1, 0, 0, 1);
	//}
    
	float4 outputColor;
	outputColor = saturate(input.color);
    
	//float2 Minus = input.position.xy - screenPos;
	//float dis = Minus.x * Minus.x + Minus.y * Minus.y;
	//dis = sqrt(dis);
	//if (select == 0.0f)
	//{
	//	if (dis > radius)
	//	{
	//		outputColor.rgb += (outColor * 2.0f - 1.0f);
	//	}
	//	else
	//	{
	//		outputColor.rgb += (lightColor * 2.0f - 1.0f);
	//	}
	//}
	//else
	//{
	//	float temp2 = pow(saturate(dis / radius), 3.0f);
	//	float temp = 1.0f - temp2;
        
	//	outputColor.rgb =
	//	saturate((outputColor.rgb + (lightColor.rgb * 2.0f - 1.0f)) * temp) +
	//	saturate((outputColor.rgb + (outColor.rgb * 2.0f - 1.0f)) * temp2);
        
	//}
	//outputColor = saturate(outputColor);
    
	return outputColor;
}