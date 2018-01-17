#include "Camera.h"


Camera::Camera(const GLuint &newUBO_BP)
{
	UBO_BP = newUBO_BP;
	up = Vector3(0.0f, 1.0f, 0.0f);
	invup = Vector3(0.0f, -1.0f, 0.0f);
	speed = 0.025f;

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_UNIFORM_BUFFER, VboId);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(GLfloat[16]) * 2, 0, GL_STREAM_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, UBO_BP, VboId);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	GlUtils::checkOpenGLError("ERROR: Could not create uniform buffer object.");

}

Camera::~Camera()
{
	glDeleteBuffers(1, &VboId);
	GlUtils::checkOpenGLError("ERROR: Could not delete buffer object.");
}

void Camera::setPosition(Vector3 pos)
{
	position = pos;
}

void Camera::setLookAt(Vector3 pos)
{
	lookAt = pos;
}

void Camera::setOrthographic(const float &left, const float &right, const float &bottom, const float &top, const float &zNear, const float &zFar)
{
	MatrixFactory mf;

	orthographic = mf.orthographicMatrix(left, right, bottom, top, zNear, zFar);
}

void Camera::setPerspective(const float &nfovy, const float &naspect,const float &nzNear, const float &nzFar)
{
	MatrixFactory mf;

	fovy = nfovy;
	aspect = naspect;
	zNear = nzNear;
	zFar = nzFar;

	perspective = mf.perspectiveMatrix(fovy, aspect, zNear, zFar);
}

void Camera::update(const float &deltaAnglex, const float &deltaAngley, const float &fov, const int elapsed)
{
	MatrixFactory mf;
	float mSpeed = speed * elapsed;
	Vector3 cameraPositionDelta = Vector3(0.0f);

	timeamount += elapsed;
	if (KeyBuffer::instance()->isPressed('p') || KeyBuffer::instance()->isPressed('P'))
	{
		if (updatebool) {
			switchProjectionMode();
			updatebool = false;
			timeamount = 0;
		}
	}

	if (timeamount >= maxtime) {								//CHECK WHY TIMEAMOUNT IS INITIALIZED AT -INFINITY
		updatebool = true;
	}

	direction = normalized(lookAt - position);

	Vector3 axis = cross(direction, up);
	Quaternion pitchQuaternion = Quaternion(deltaAngley, axis);
	Quaternion headingQuaternion = Quaternion(deltaAnglex, up);
	Quaternion temp = pitchQuaternion * headingQuaternion;
	temp.normalize();
	direction = rotate(temp, direction);
	up = cross(axis, direction);
	up.normalize();

	if (projectionMode == PERSPECTIVE)
	{
		if (fovy >= 1.0f && fovy <= 45.0f)
		{
			fovy += fov;
		}
		if (fovy <= 1.0f)
		{
			fovy = 1.0f;
		}
		if (fovy >= 45.0f)
		{
			fovy = 45.0f;
		}
		perspective = mf.perspectiveMatrix(fovy, aspect, zNear, zFar);
	}

	if (KeyBuffer::instance()->isPressed('w') || KeyBuffer::instance()->isPressed('W'))
	{
		cameraPositionDelta += direction * mSpeed;
	}
	if (KeyBuffer::instance()->isPressed('s') || KeyBuffer::instance()->isPressed('S'))
	{
		cameraPositionDelta -= direction * mSpeed;
	}
	if (KeyBuffer::instance()->isPressed('a') || KeyBuffer::instance()->isPressed('A'))
	{
		cameraPositionDelta -= cross(direction, up) * mSpeed;
	}
	if (KeyBuffer::instance()->isPressed('d') || KeyBuffer::instance()->isPressed('D'))
	{
		cameraPositionDelta += cross(direction, up) * mSpeed;
	}

	//add the camera delta
	position += cameraPositionDelta;
	invposition = position;
	invposition.z = -position.z;

	//set inverted direction
	invdirection = direction;
	invdirection.z = -direction.z;

	//set the look at to be infront of the camera
	lookAt = position + direction;
	invlookAt = invposition + invdirection;

	//set inverted up
	invup = up;
	invup.y = -up.y;

	viewMatrix = mf.viewMatrix(position, lookAt, up);
	invviewMatrix = mf.viewMatrix(invposition, invlookAt, invup);

	if (projectionMode == ORTHOGRAPHIC)
	{
		projection = orthographic;
	}
	else
	{
		projection = perspective;
	}
}

void Camera::switchProjectionMode()
{
	if (projectionMode == PERSPECTIVE)
	{
		projectionMode = ORTHOGRAPHIC;
	}
	else
	{
		projectionMode = PERSPECTIVE;
	}
}

void Camera::switchCameraType()
{
	if (cameraType == FREE)
	{
		cameraType = ARCBALL;
	}
	else
	{
		cameraType = FREE;
	}
}

void Camera::setCamera()
{
	glBindBuffer(GL_UNIFORM_BUFFER, VboId);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(GLfloat[16]), viewMatrix.matrix);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(GLfloat[16]), sizeof(GLfloat[16]), projection.matrix);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Camera::setInvertedCamera()
{
	glBindBuffer(GL_UNIFORM_BUFFER, VboId);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(GLfloat[16]), invviewMatrix.matrix);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(GLfloat[16]), sizeof(GLfloat[16]), projection.matrix);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}