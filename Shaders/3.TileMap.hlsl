#define Max_Image 4

struct VertexInput
{
    float4 position : POSITION0;
    float2 uv : UV0;
    float4 color : COLOR0; //섞을색상
    float tileMapIdx : INDICES0;
    float tileState : STATE0;
};
// PI
struct PixelInput
{
    float4 position : SV_POSITION; //화면좌표계 포지션
    float2 uv : UV0; //매핑된 좌표
    float4 color : COLOR0; //섞을색상
    float tileMapIdx : INDICES0;
    float tileState : STATE0;
};

//상수버퍼 크기는 16byte배수로 만들어야한다.

cbuffer VS_WVP : register(b0)
{
    matrix WVP;
}
//cbuffer VS_COLOR : register(b1)
//{
//    //4 개의 4바이트
//	float4 color;
//}
//cbuffer VS_UV : register(b2)
//{
//    float4 uv;
//}


struct light
{
    
};

cbuffer PS_LIGHT : register(b0)
{
    float2 screenPos; //스크린좌표
    float radius; //반지름크기
    float select; //조명 타입 선택
    float4 lightColor; //조명 색
    float4 outColor; //외곽 색
    light P_light[10];
};



//버텍스 쉐이더
//반환형  함수이름(매개변수)
// VertexInput(in) ->  VS  -> PixelInput (out)
PixelInput VS(VertexInput input)
{
    //공간변환이 있을 예정인 곳
    PixelInput output;
    output.position = mul(input.position, WVP);
    output.color = input.color;
    output.uv = input.uv;
    output.tileMapIdx = input.tileMapIdx;
    output.tileState = input.tileState;
    return output;
}

//텍스쳐 자원  (srv) 에서 연결
Texture2D Texture[Max_Image] : register(t0);
SamplerState Sampler[Max_Image] : register(s0);



//픽셀쉐이더 진입 함수
float4 PS(PixelInput input) : SV_TARGET //SV_TARGET 은 타겟이될 색깔 
{
    float4 TextureColor;
    // 매핑된 좌표로 텍스쳐 로드
   
    [branch]
        
    for (int i = 0; i < Max_Image; i++)
    {
        if (input.tileMapIdx == i)
        {
            TextureColor = Texture[i].Sample(Sampler[i], input.uv);
            break;
        }
    }
       
	//return float4(input.tileMapIdx/3.0f.xxx,1);
    
    //읽어온 그림파일의 픽셀색상을 조건문으로 비교
    [flatten]
    if (TextureColor.r == 1.0f &&
        TextureColor.g == 0.0f &&
        TextureColor.b == 1.0f)
    {
        //해당 픽셀은 사용하지않는다.
        discard;
    }
    
    TextureColor = TextureColor + (input.color * 2.0f - 1.0f);
    
    TextureColor = saturate(TextureColor);

      //조명효과
  //  float2 Minus = input.position.xy - screenPos;
  //  float dis = sqrt(Minus.x * Minus.x + Minus.y * Minus.y);
  //  if (select == 0.0f)
  //  {
  //      if (dis > radius)
  //      {
  //          TextureColor.rgb += (outColor.rgb * 2.0f - 1.0f);
  //      }
  //      else
  //      {
  //          TextureColor.rgb += (lightColor.rgb * 2.0f - 1.0f);
  //      }
  //  }
  //  else
  //  {
  //      //외각선이 0 가운데가 1
  //      float temp2 = pow(saturate(dis / radius), 3.0f);
  //      float temp = 1.0f - temp2;
        
  //      TextureColor.rgb =
		//saturate((TextureColor.rgb + (lightColor.rgb * 2.0f - 1.0f)) * temp) +
		//saturate((TextureColor.rgb + (outColor.rgb * 2.0f - 1.0f)) * temp2);
        
		////TextureColor.rgb *= temp;
  //  }
	
   //에디터에서만 확인할때 추가할것
    
  // if (input.tileState == 0.0f)
  // {
  //     return TextureColor + float4(1.0f, 0.0f, 0.0f, 0);
  // }
  // if (input.tileState == 1.0f)
  // {
  //     return TextureColor + float4(0.0f, 1.0f, 0.0f, 0);
  // }
  //  //
  // if (input.tileState == 2.0f)
  // {
  //     return TextureColor + float4(0.0f, 0.0f, 1.f, 0);
  // }
    
   // if (input.tileState == 0.0f)
   // {
   //     return TextureColor + float4(0.3f, 0.5f, 0.1f, 0);
   // }
    if (input.tileState == 1.0f)
    {
        return TextureColor - float4(0.5f, 0.5f, 0.5f, 0);
    }
   ////
   // if (input.tileState == 2.0f)
   // {
   //     return TextureColor + float4(0.0f, 0.0f, 1.f, 0);
   // }
   //
   // if (input.tileState == 3.0f)
   // {
   //     return TextureColor + float4(0.3f, 0.4f, 0.1f, 0);
   // }
    
    
    return saturate(TextureColor);
}