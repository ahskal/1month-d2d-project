#pragma once
class Bullet : public ObRect
{
private:
	bool      isFire;

	bool      isLifeTime;
	float	  lifeTime;

	// ½î´Â ¹æÇâ
	Vector2   fireDir;
	// ½î´Â Èû
	float     pressPower;

	bool isGravity;
	Vector2  gravityDir;
	float    gravityForce;

	unique_ptr<ObImage> img;
	bool      hasImage;

	Vector2 startPos;

	float length;
	bool hasLength;



public:
	Bullet();
	Bullet(wstring file, Vector2 pivct = Vector2(), Int2 maxFream = Int2());
	virtual ~Bullet();


	void Fire(GameObject* StartObj, Vector2 scale, float Power, float lifeTime = 0.0f);
	

	void Fire(GameObject* StartObj, Vector2 dir, Vector2 scale, float Power, float lifeTime = 0.0f);
//	void Fire(Vector2 pos, Vector2 dir, Vector2 scale, float Power, float Length);


	void Fire(Vector2 pos, Vector2 dir, float pressPower);
	void Fire(Vector2 pos, Vector2 dir, float Power, float Length);
	void Fire(Vector2 pos, Vector2 dir, Vector2 scale, float Power, float Length = 0);
	void Drop(Vector2 pos);
	void Update() override;
	void Render() override;
	bool Touch(GameObject* target);

	bool GetIsFire() { return isFire; }
	void Release() { isFire = false; }

	void ReflectionY()
	{
		fireDir.x = -fireDir.x;
		/*Vector2 dir =
			Vector2(cosf(rotation.z), sinf(rotation.z));
		rotation.z = atan2f(dir.y, -dir.x);*/
		pressPower *= 0.7f;
		gravityForce *= 0.7f;
	}
	void ReflectionX()
	{
		fireDir.y = -fireDir.y;
		gravityForce = -gravityForce;
		//Vector2 dir =
		//	Vector2(cosf(rotation.z), sinf(rotation.z));
		//rotation.z = atan2f(-dir.y, dir.x);
		pressPower *= 0.7f;
		gravityForce *= 0.7f;
	}
};

