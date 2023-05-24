#include "Camera.h"

Camera::Camera() {
	matrix = new Matrix;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			worldMatrix.m[i][j] = 0.0f;
			cameraMatrix.m[i][j] = 0.0f;
			viewMatrix.m[i][j] = 0.0f;
			projectionMatrix.m[i][j] = 0.0f;
			worldViewProjectionMatrix.m[i][j] = 0.0f;
			viewportMatrix.m[i][j] = 0.0f;
		}
	}
	cameraTranslate = { 0.0f,1.9f,-0.49f };
	camerarotate = { 0.20f,0.0f,0.0f };

}

Camera::~Camera() {
	delete matrix;
}


bool Camera::IsFront(const Vector3& cross) {
	if (matrix->Dot(cameraTranslate, cross) < 0) {
		return true;
	}
	return false;
}

Vector3 Camera::TransWorld(const Vector3& rotate, const Vector3& translate,const Vector3& local) {
	Vector3 result{ 0,0,0 };
	worldMatrix = matrix->MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
	cameraMatrix = matrix->MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraTranslate);
	viewMatrix = matrix->Inverce(cameraMatrix);
	projectionMatrix = matrix->MakePerspectiveFovMatrix(0.45f, (1280.0f / 720.0f), 0.1f, 100.0f);
	worldViewProjectionMatrix = matrix->Multiply(worldMatrix, matrix->Multiply(viewMatrix, projectionMatrix));
	viewportMatrix = matrix->MakeViewportMatrix(0, 0, 1280.0f, 720.0f, 0.0f, 1.0f);
	Vector3 ndcVertex = matrix->Transform(local, worldViewProjectionMatrix);
	result = matrix->Transform(ndcVertex, viewportMatrix);
	return result;
}