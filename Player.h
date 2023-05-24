#pragma once
#include"Camera.h"
#include<Novice.h>
class Player
{
public:
	Player();
	~Player();

private:
	Camera* camera;
	Matrix* matrix;

	Vector3 rotate;

	Vector3 translate;

	Vector3 kLocalVertices[3];

	Vector3 cross;
	Vector3 screenVertices[3];

	Vector3 screenVectorA;
	Vector3 screenVectorB;

	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

public:
	void Update();

	void Draw();
};

