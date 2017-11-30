#include "Camera.h"

//TODO create initial position for the camera
Camera::Camera(const GLuint &newUBO_BP, Vector3 position)
{
	UBO_BP = newUBO_BP;
	
	translation = mf.translation(position);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_UNIFORM_BUFFER, VboId);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(GLfloat[16]) * 2, 0, GL_STREAM_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, UBO_BP, VboId);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	GlUtils::checkOpenGLError("ERROR: Could not buffer object.");
}

Camera::~Camera()
{
	glDeleteBuffers(1, &VboId);
	GlUtils::checkOpenGLError("ERROR: Could not delete buffer object.");
}

void Camera::setOrthographic(const float &left, const float &right, const float &bottom, const float &top, const float &zNear, const float &zFar)
{
	orthographic = mf.orthographicMatrix(left, right, bottom, top, zNear, zFar);
}

void Camera::setPerspective(const float &nfovy, const float &naspect,const float &nzNear, const float &nzFar)
{
	fovy = nfovy;
	aspect = naspect;
	zNear = nzNear;
	zFar = nzFar;

	perspective = mf.perspectiveMatrix(fovy, aspect, zNear, zFar);
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

void Camera::switchGimbalMode()
{
	if (gimbalMode == RODRIGUES)
	{
		gimbalMode = QUATERNIONS;
	}
	else
	{
		gimbalMode = RODRIGUES;
	}
}

void Camera::updateView(const float &deltaAnglex, const float &deltaAngley, const float &fov)
{
	if (KeyBuffer::instance()->isPressed('p') || KeyBuffer::instance()->isPressed('P'))
	{
		switchProjectionMode();
	}
	if (KeyBuffer::instance()->isPressed('g') || KeyBuffer::instance()->isPressed('G'))
	{
		switchGimbalMode();
	}

	Quaternion qx, qy;

	////////////////// EULER ///////////////////////
	view = mf.rotation(up, deltaAnglex) * view;
	view.normalize();
	side = mf.rotation(up, deltaAnglex) * side;
	side.normalize();

	view = mf.rotation(side, deltaAngley) * view;
	view.normalize();
	up = mf.rotation(side, deltaAngley) * up;
	up.normalize();
	////////////////////////////////////////////////

	/////////////////////// RODRIGUES //////////////////////////
	anglex += deltaAnglex;
	angley += deltaAngley;
	
	rx = mf.rotation(Vector4(-1.0f, 0.0f, 0.0f, 1.0f), angley);
	ry = mf.rotation(Vector4(0.0f, -1.0f, 0.0f, 1.0f), anglex);
	////////////////////////////////////////////////////////////

	///////////////////// QUATERNIONS //////////////////////////////
	qx = Quaternion(deltaAngley, Vector4(-1.0f, 0.0f, 0.0f, 1.0f));
	qy = Quaternion(deltaAnglex, Vector4(0.0f, -1.0f, 0.0f, 1.0f));
	qtrn = qx * qy * qtrn;
	////////////////////////////////////////////////////////////////

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



}

void Camera::setCamera()
{
	if (gimbalMode == RODRIGUES)
	{
		rotationView = rx * ry;
	}
	else
	{
		rotationView = toGlMatrix(qtrn);
	}

/*	if (cameraType == ARCBALL && gimbalMode == RODRIGUES)
	{
		viewMatrix = mf.viewMatrix(eye, eye + view, up);
	}
	else */if (cameraType == ARCBALL)
	{
		viewMatrix = translation * rotationView;
	}
	else
	{
		viewMatrix = rotationView * translation;
	}

	if (projectionMode == ORTHOGRAPHIC)
	{
		projection = orthographic;
	}
	else
	{
		projection = perspective;
	}

	glBindBuffer(GL_UNIFORM_BUFFER, VboId);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(GLfloat[16]), viewMatrix.matrix);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(GLfloat[16]), sizeof(GLfloat[16]), projection.matrix);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}