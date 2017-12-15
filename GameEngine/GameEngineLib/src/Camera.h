#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "GlUtils.h"
#include "KeyBuffer.h"
#include "MathAux.h"

//// PROJECTION TYPE //////
enum ProjectionType 
{
	ORTHOGRAPHIC,
	PERSPECTIVE
};
//////////////////////////

///// CAMERA TYPE ////////
enum CameraType
{
	ARCBALL,
	FREE
};
//////////////////////////


class Camera
{
	private:
		float speed = 0.05f;
		GLuint UBO_BP;
		GLuint VboId;
		ProjectionType projectionMode = PERSPECTIVE;
		CameraType cameraType = ARCBALL;
		float anglex = 0.0f, angley = 0.0f;
		Vector3 eye = Vector3(0.0f, 0.0f, 3.0f), center = Vector3(0.0f, 0.0f, -1.0f), up = Vector3(0.0f, 1.0f, 0.0f);
		Vector3 view = center - eye, side = cross(center, up);
		Quaternion qtrn = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
		Matrix4 projection, orthographic, perspective;
		Matrix4 viewMatrix;
		Matrix4 translation;
		Matrix4 rx, ry, rotationView;
		float fovy, aspect, zNear, zFar;
		MatrixFactory mf;
		bool updatebool;
		int timeamount = 0;
		const int maxtime = 150;
	public:
		Camera() {};
		Camera(const GLuint &newUBO_BP, Vector3 position);
		~Camera();
		void setOrthographic(const float &left, const float &right, const float &bottom, const float &top, const float &near, const float &far);
		void setPerspective(const float &nfovy, const float &naspect, const float &nzNear, const float &nzFar);
		void switchProjectionMode();
		void switchCameraType();
		void updateView(const float &deltaAnglex, const float &deltaAngley, const float &fov, const int elapsed);
		void setCamera();
		void specialSetCamera();
		Vector3 getFront() { return view; };
		Vector3 getSide() { return side; };
		Vector3 getEye() { return eye; };
};

#endif // !__CAMERA_H__