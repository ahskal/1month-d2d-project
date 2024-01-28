#define Max_Image 4

struct VertexInput
{
    float4 position : POSITION0;
    float2 uv : UV0;
    float4 color : COLOR0; //��������
    float tileMapIdx : INDICES0;
    float tileState : STATE0;
};
// PI
struct PixelInput
{
    float4 position : SV_POSITION; //ȭ����ǥ�� ������
    float2 uv : UV0; //���ε� ��ǥ
    float4 color : COLOR0; //��������
    float tileMapIdx : INDICES0;
    float tileState : STATE0;
};

//������� ũ��� 16byte����� �������Ѵ�.

cbuffer VS_WVP : register(b0)
{
    matrix WVP;
}
//cbuffer VS_COLOR : register(b1)
//{
//    //4 ���� 4����Ʈ
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
    float2 screenPos; //��ũ����ǥ
    float radius; //������ũ��
    float select; //���� Ÿ�� ����
    float4 lightColor; //���� ��
    float4 outColor; //�ܰ� ��
    light P_light[10];
};



//���ؽ� ���̴�
//��ȯ��  �Լ��̸�(�Ű�����)
// VertexInput(in) ->  VS  -> PixelInput (out)
PixelInput VS(VertexInput input)
{
    //������ȯ�� ���� ������ ��
    PixelInput output;
    output.position = mul(input.position, WVP);
    output.color = input.color;
    output.uv = input.uv;
    output.tileMapIdx = input.tileMapIdx;
    output.tileState = input.tileState;
    return output;
}

//�ؽ��� �ڿ�  (srv) ���� ����
Texture2D Texture[Max_Image] : register(t0);
SamplerState Sampler[Max_Image] : register(s0);



//�ȼ����̴� ���� �Լ�
float4 PS(PixelInput input) : SV_TARGET //SV_TARGET �� Ÿ���̵� ���� 
{
    float4 TextureColor;
    // ���ε� ��ǥ�� �ؽ��� �ε�
   
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
    
    //�о�� �׸������� �ȼ������� ���ǹ����� ��
    [flatten]
    if (TextureColor.r == 1.0f &&
        TextureColor.g == 0.0f &&
        TextureColor.b == 1.0f)
    {
        //�ش� �ȼ��� ��������ʴ´�.
        discard;
    }
    
    TextureColor = TextureColor + (input.color * 2.0f - 1.0f);
    
    TextureColor = saturate(TextureColor);

      //����ȿ��
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
  //      //�ܰ����� 0 ����� 1
  //      float temp2 = pow(saturate(dis / radius), 3.0f);
  //      float temp = 1.0f - temp2;
        
  //      TextureColor.rgb =
		//saturate((TextureColor.rgb + (lightColor.rgb * 2.0f - 1.0f)) * temp) +
		//saturate((TextureColor.rgb + (outColor.rgb * 2.0f - 1.0f)) * temp2);
        
		////TextureColor.rgb *= temp;
  //  }
	
   //�����Ϳ����� Ȯ���Ҷ� �߰��Ұ�
    
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