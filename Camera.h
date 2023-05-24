#pragma once
#include"Matrix.h"
class Camera
{
public:
	Camera();
	~Camera();
private:
	Matrix* matrix;
	Matrix4x4 worldMatrix;
	Matrix4x4 cameraMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 worldViewProjectionMatrix;
	Matrix4x4 viewportMatrix;	
	Vector3 cameraTranslate;
	Vector3 camerarotate;
public:
	//カメラから見て表かどうか判断
	bool IsFront(const Vector3& cross);
	//ローカルからワールドに変換
	Vector3 TransWorld(const Vector3& rotate,const Vector3& translate,const Vector3& local);
};

