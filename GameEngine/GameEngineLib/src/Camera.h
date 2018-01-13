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
		GLuint UBO_BP;
		GLuint VboId;
		ProjectionType projectionMode = PERSPECTIVE;
		CameraType cameraType = FREE;
		Vector3 position, lookAt, direction, up;
		float fovy, aspect, zNear, zFar, speed;
		Matrix4 projection, orthographic, perspective;
		Matrix4 viewMatrix;
		bool updatebool;
		int timeamount = 0;
		const int maxtime = 150;

	public:
		Camera() {};
		Camera(const GLuint &newUBO_BP);
		~Camera();
		void setPosition(Vector3 pos);
		void setLookAt(Vector3 pos);
		void setOrthographic(const float &left, const float &right, const float &bottom, const float &top, const float &zNear, const float &zFar);
		void setPerspective(const float &nfovy, const float &naspect, const float &nzNear, const float &nzFar);
		void update(const float &deltaAnglex, const float &deltaAngley, const float &fov, const int elapsed);
		void switchProjectionMode();
		void switchCameraType();
		void setCamera();	
		Vector3 getPosition() { return position; };
};

#endif // !__CAMERA_H__