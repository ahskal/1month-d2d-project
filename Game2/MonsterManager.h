#pragma once
class MonsterManager : public Singleton<MonsterManager>
{
private:

public:

	vector<class TypeMonster*> monster;
	Vector2 AttatkPos;
	ObTileMap* Map;



	int giveExp;

	MonsterManager();
	~MonsterManager();

	void Init();
	void Update();
	void LateUpdate();
	void Render();
	void HpRender();
	//void Create(Vector2 Pos);
	void Create(Vector2 Pos, unsigned int Num = 1);


	vector<class TypeMonster*>& GetMonsterVector() { return monster; };
	//Vector2 GetMonsterVectorPos(int i) { return monster[i]->GetCol()->GetWorldPos(); };


	void SelectTarget(Vector2 Pos);

	void GetMap(ObTileMap* Map) { this->Map = Map; };

	void collisionsBetweenUnits();;

	void GiveExp(TypeMonster* tm);

	void ReFindPath();

};

