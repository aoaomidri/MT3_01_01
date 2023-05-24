#include "Player.h"
#include<assert.h>
#include<stdint.h>
Player::Player() {
	camera = new Camera;
	matrix = new Matrix;

	rotate = { 0.0f,0.0f,0.0f };
	translate = { 0.0f,0.0f,0.0f };
	kLocalVertices[0] = { 0.0f,1.5f,0.0f, };
	kLocalVertices[1] = { 1.5f,-1.5f,0.0f, };
	kLocalVertices[2] = { -1.5f,-1.5f,0.0f, };

	cross = { 0.0f,0.0f,0.0f };
	screenVectorA = { 0.0f,0.0f,0.0f };
	screenVectorB = { 0.0f,0.0f,0.0f };
	for (int i = 0; i < 3; i++) {
		screenVertices[i] = { 0.0f,0.0f,0.0f };
	}
}

Player::~Player(){
	delete camera;
	delete matrix;
}

void Player::Update() {
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	rotate.y += 0.05f;

	if (keys[DIK_W]) {
		translate.z += 0.3f;
	}
	else  if (keys[DIK_S]) {
		translate.z -= 0.3f;
	}

	if (keys[DIK_A]) {
		translate.x -= 0.1f;
	}
	else if (keys[DIK_D]) {
		translate.x += 0.1f;
	}
	//worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
	//cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition);
	//viewMatrix = Inverce(cameraMatrix);
	//projectionMatrix = MakePerspectiveFovMatrix(0.45f, (1280.0f / 720.0f), 0.1f, 100.0f);
	//worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
	//viewportMatrix = MakeViewportMatrix(0, 0, 1280.0f, 720.0f, 0.0f, 1.0f);
	//for (uint32_t i = 0; i < 3; ++i) {
	//	Vector3 ndcVertex = Transform(kLocalVertices[i], worldViewProjectionMatrix);
	//	screenVertices[i] = Transform(ndcVertex, viewportMatrix);
	//}

	for (uint32_t i = 0; i < 3; ++i) {
		screenVertices[i] = camera->TransWorld(rotate, translate, kLocalVertices[i]);
	}
	screenVectorA = {
		screenVertices[1].x - screenVertices[0].x,
		screenVertices[1].y - screenVertices[0].y,
		screenVertices[1].z - screenVertices[0].z,
	};
	screenVectorB = {
		screenVertices[2].x - screenVertices[1].x,
		screenVertices[2].y - screenVertices[1].y,
		screenVertices[2].z - screenVertices[1].z,
	};
	cross = matrix->Cross(screenVectorA, screenVectorB);

}

void Player::Draw() {
	if (camera->IsFront(cross))
	{
		Novice::DrawTriangle(
			int(screenVertices[0].x), int(screenVertices[0].y),
			int(screenVertices[1].x), int(screenVertices[1].y),
			int(screenVertices[2].x), int(screenVertices[2].y),
			RED, kFillModeSolid
		);
	}

}