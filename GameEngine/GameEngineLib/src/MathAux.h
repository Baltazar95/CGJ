#ifndef __MATHAUX_H__
#define __MATHAUX_H__

#include <iostream>
#include <stdexcept>
#include <cmath>

#define EPSILON 0.0001
#define CLEAN_VALUE 1000
#define SIZE2X2 4
#define RCSIZE2X2 2
#define SIZE3X3 9
#define RCSIZE3X3 3
#define SIZE4X4 16
#define RCSIZE4X4 4
#define PI 3.14159265359
#define TURN 180

//namespace MathAux
//{

	////////////////////////////////////////////////////
	////											////
	////				  VECTOR2					////
	////											////
	////////////////////////////////////////////////////
	struct Vector2
	{
		float x, y;

		Vector2();
		Vector2(float constant);
		Vector2(float nx, float ny);

		void operator += (const float s);
		void operator += (const Vector2 &v);
		void operator -= (const float s);
		void operator -= (const Vector2 &v);
		void operator *= (const float s);
		void operator /= (const float s);
		void normalize();
		void clean();
	};

	Vector2 operator + (const Vector2 &v, const float &num);

	Vector2 operator + (const Vector2 &v, const Vector2 &u);

	Vector2 operator - (const Vector2 &v);
	Vector2 operator - (const Vector2 &v, const float &num);

	Vector2 operator - (const Vector2 &v, const Vector2 &u);

	Vector2 operator * (const Vector2 &v, const float &num);
	Vector2 operator * (const float &num, const Vector2 &v);


	Vector2 operator / (const Vector2 &v, const float &num);

	bool operator == (const Vector2 &v, const Vector2 &u);

	float quadrance(const Vector2 &v);
	float norm(const Vector2 &v);
	float dot(const Vector2 &v, const Vector2 &u);

	Vector2 normalized(const Vector2 &v);

	std::ostream &operator << (std::ostream &os, Vector2 &v);
	std::istream &operator >> (std::istream &is, Vector2 &v);


	////////////////////////////////////////////////////
	////											////
	////				  VECTOR3					////
	////											////
	////////////////////////////////////////////////////
	struct Vector3
	{
		float x, y, z;

		Vector3();
		Vector3(float constant);
		Vector3(float nx, float ny, float nz);

		//Non-normal constructors (ARE THEY REALLY NEEDED?)
		Vector3(Vector2 vec);
		Vector3(Vector2 vec, float nz);
		////////////////////////////

		void operator += (const float s);
		void operator += (const Vector3 &v);
		void operator -= (const float s);
		void operator -= (const Vector3 &v);
		void operator *= (const float s);
		void operator /= (const float s);
		void normalize();
		void clean();
	};

	Vector3 operator + (const Vector3 &v, const float &num);
	Vector3 operator + (const Vector3 &v, const Vector3 &u);

	Vector3 operator - (const Vector3 &v);
	Vector3 operator - (const Vector3 &v, const float &num);
	Vector3 operator - (const Vector3 &v, const Vector3 &u);

	Vector3 operator * (const Vector3 &v, const float &num);
	Vector3 operator * (const float &num, const Vector3 &v);

	Vector3 operator / (const Vector3 &v, const float &num);

	bool operator == (const Vector3 &v, const Vector3 &u);

	float quadrance(const Vector3 &v);
	float norm(const Vector3 &v);
	float dot(const Vector3 &v, const Vector3 &u);

	Vector3 normalized(const Vector3 &v);
	Vector3 cross(const Vector3 &v, const Vector3 &u);

	std::ostream &operator << (std::ostream &os, Vector3 &v);
	std::istream &operator >> (std::istream &is, Vector3 &v);


	////////////////////////////////////////////////////
	////											////
	////				  VECTOR4					////
	////											////
	////////////////////////////////////////////////////
	struct Vector4
	{
		float x, y, z, w;

		Vector4();
		Vector4(float constant);
		Vector4(float nx, float ny, float nz, float nw);
		Vector4(Vector3 vec, float nw);

		void operator += (const float s);
		void operator += (const Vector4 &v);
		void operator -= (const float s);
		void operator -= (const Vector4 &v);
		void operator *= (const float s);
		void operator /= (const float s);
		void normalize();
		void clean();
	};

	Vector4 operator + (const Vector4 &v, const float &num);
	//This migh not much sense (?!)
	//Vector4 operator + (const float &num, const Vector4 &v);
	Vector4 operator + (const Vector4 &v, const Vector4 &u);

	Vector4 operator - (const Vector4 &v);
	Vector4 operator - (const Vector4 &v, const float &num);
	//This migh not much sense (?!)
	//Vector4 operator - (const float &num, const Vector4 &v);
	Vector4 operator - (const Vector4 &v, const Vector4 &u);

	Vector4 operator * (const Vector4 &v, const float &num);
	Vector4 operator * (const float &num, const Vector4 &v);


	Vector4 operator / (const Vector4 &v, const float &num);
	//This migh not much sense (?!)
	//Vector4 operator / (const float &num, const Vector4 &v);

	bool operator == (const Vector4 &v, const Vector4 &u);

	float quadrance(const Vector4 &v);
	float norm(const Vector4 &v);
	float dot(const Vector4 &v, const Vector4 &u);

	Vector4 normalized(const Vector4 &v);

	//Do i need cross for Vector4??
	//Vector4 cross(const Vector4 &v, const Vector4 &u);

	std::ostream &operator << (std::ostream &os, Vector4 &v);
	std::istream &operator >> (std::istream &is, Vector4 &v);


	////////////////////////////////////////////////////
	////											////
	////				   MATRIX2					////
	////											////
	////////////////////////////////////////////////////

	struct Matrix2
	{
		float matrix[SIZE2X2];

		Matrix2();
		Matrix2(float constant);
		Matrix2(float m[SIZE2X2]);
		Matrix2(float xx, float xy,
			float yx, float yy);
		Matrix2(const Vector2 &v, const Vector2 &u);

		void operator += (const Matrix2 &m);
		void operator -= (const Matrix2 &m);
		void operator *= (const float num);
		void operator *= (const Matrix2 &m);
		void operator /= (const float num);
		void clean();
	};

	Matrix2 operator + (const Matrix2 &m, const Matrix2 &n);
	Matrix2 operator - (const Matrix2 &m, const Matrix2 &n);
	Matrix2 operator * (const Matrix2 &m, const Matrix2 &n);
	Matrix2 operator * (const Matrix2 &m, const float num);
	Matrix2 operator * (const float num, const Matrix2 &m);
	Vector2 operator * (const Matrix2 &m, const Vector2 &v);
	Vector2 operator * (const Vector2 &v, const Matrix2 &m);
	Matrix2 operator / (const Matrix2 &m, const float num);

	bool operator == (const Matrix2 &m, const Matrix2 &n);

	Matrix2 transpose(const Matrix2 &m);
	Matrix2 inverse(const Matrix2 &m);

	float determinant(const Matrix2 &m);

	std::ostream &operator << (std::ostream &os, Matrix2 &m);
	std::istream &operator >> (std::istream &is, Matrix2 &m);

	////////////////////////////////////////////////////
	////											////
	////				   MATRIX3					////
	////											////
	////////////////////////////////////////////////////

	struct Matrix3
	{
		float matrix[SIZE3X3];

		Matrix3();
		Matrix3(float constant);
		Matrix3(float m[SIZE3X3]);
		Matrix3(float xx, float xy, float xz,
			float yx, float yy, float yz,
			float zx, float zy, float zz);
		Matrix3(const Vector3 &v, const Vector3 &u, const Vector3 &w);

		void operator += (const Matrix3 &m);
		void operator -= (const Matrix3 &m);
		void operator *= (const float num);
		void operator *= (const Matrix3 &m);
		void operator /= (const float num);
		void clean();
	};

	Matrix3 operator + (const Matrix3 &m, const Matrix3 &n);
	Matrix3 operator - (const Matrix3 &m, const Matrix3 &n);
	Matrix3 operator * (const Matrix3 &m, const Matrix3 &n);
	Matrix3 operator * (const Matrix3 &m, const float num);
	Matrix3 operator * (const float num, const Matrix3 &m);
	Vector3 operator * (const Matrix3 &m, const Vector3 &v);
	Vector3 operator * (const Vector3 &v, const Matrix3 &m);
	Matrix3 operator / (const Matrix3 &m, const float num);

	bool operator == (const Matrix3 &m, const Matrix3 &n);

	Matrix3 transpose(const Matrix3 &m);
	Matrix3 inverse(const Matrix3 &m);

	float determinant(const Matrix3 &m);

	std::ostream &operator << (std::ostream &os, Matrix3 &m);
	std::istream &operator >> (std::istream &is, Matrix3 &m);


	////////////////////////////////////////////////////
	////											////
	////				   MATRIX4					////
	////											////
	////////////////////////////////////////////////////

	struct Matrix4
	{
		float matrix[SIZE4X4];

		Matrix4();
		Matrix4(float constant);
		Matrix4(float m[SIZE4X4]);
		Matrix4(float xx, float xy, float xz, float xw,
			float yx, float yy, float yz, float yw,
			float zx, float zy, float zz, float zw,
			float wx, float wy, float wz, float ww);
		Matrix4(const Matrix3 &m);
		Matrix4(const Vector4 &v, const Vector4 &u, const Vector4 &w, const Vector4 &n);

		void operator += (const Matrix4 &m);
		void operator -= (const Matrix4 &m);
		void operator *= (const float num);
		void operator *= (const Matrix4 &m);
		void operator /= (const float num);
		void clean();
	};

	Matrix4 operator + (const Matrix4 &m, const Matrix4 &n);
	Matrix4 operator - (const Matrix4 &m, const Matrix4 &n);
	Matrix4 operator * (const Matrix4 &m, const Matrix4 &n);
	Matrix4 operator * (const Matrix4 &m, const float num);
	Matrix4 operator * (const float num, const Matrix4 &m);
	Vector4 operator * (const Matrix4 &m, const Vector4 &v);
	Vector4 operator * (const Vector4 &v, const Matrix4 &m);
	Matrix4 operator / (const Matrix4 &m, const float num);

	bool operator == (const Matrix4 &m, const Matrix4 &n);

	Matrix4 transpose(const Matrix4 &m);
	Matrix4 inverse(const Matrix4 &m);

	float determinant(const Matrix4 &m);

	std::ostream &operator << (std::ostream &os, Matrix4 &m);
	std::istream &operator >> (std::istream &is, Matrix4 &m);


	////////////////////////////////////////////////////
	////											////
	////				MATRIX FACTORY				////
	////											////
	////////////////////////////////////////////////////

	struct MatrixFactory
	{
		Matrix2 identity2();
		Matrix3 identity3();
		Matrix4 identity4();

		Matrix3 dual(const Vector3 &v);

		Matrix3 normalMatrix(const Matrix3 &m);
		Matrix4 normalMatrix(const Matrix4 &m);

		Matrix2 rotation(const float angle);
		Matrix3 rotation(const Vector3 &axis, const float angle);
		Matrix4 rotation(const Vector4 &axis, const float angle);

		Matrix2 scale(const float x, const float y);
		Matrix3 scale(const float x, const float y, const float z);
		Matrix4 scale(const float x, const float y, const float z, const float w);

		Matrix2 shear2x(const float shearFactor);
		Matrix2 shear2y(const float shearFactor);
		Matrix3 shear3x(const float shearFactor);
		Matrix3 shear3y(const float shearFactor);
		Matrix3 shear3z(const float shearFactor);
		Matrix4 shear4x(const float shearFactor);
		Matrix4 shear4y(const float shearFactor);
		Matrix4 shear4z(const float shearFactor);

		//This function doesn't make sense for now, investigate further
		//Matrix2 translation(const Vector2 &translationFactors);
		Matrix4 translation(const Vector3 &v);
		Matrix4 translation(const float x, const float y, const float z);

		//////////////////////////////////////////////////////////

		Matrix4 viewMatrix(Vector3 eye, Vector3 center, Vector3 up);
		Matrix4 orthographicMatrix(float left, float right, float top, float bottom, float near, float far);
		Matrix4 perspectiveMatrix(float fovy, float aspect, float zNear, float zFar);

		Matrix4 convert3To4(const Matrix3 &m);
		Matrix3 convert4To3(const Matrix4 &m);
	};

	////////////////////////////////////////////////////
	////											////
	////				QUATERNIONS					////
	////											////
	////////////////////////////////////////////////////


	struct Quaternion
	{
		float t, x, y, z;

		Quaternion();
		Quaternion(float nt, float nx, float ny, float nz);
		Quaternion(float angle, Vector4 axis);

		void operator += (const Quaternion &q);
		void operator -= (const Quaternion &q);
		void operator *= (const float num);
		void operator *= (const Quaternion &q);
		void operator /= (const float num);
		void normalize();
		void clean();
	};

	Quaternion operator + (const Quaternion &q, const Quaternion &qt);
	Quaternion operator - (const Quaternion &q, const Quaternion &qt);
	Quaternion operator * (const Quaternion &q, const Quaternion &qt);
	Quaternion operator * (const Quaternion &q, const float num);
	Quaternion operator * (const float num, const Quaternion &q);
	Quaternion operator / (const Quaternion &q, const float num);

	bool operator == (const Quaternion &q, const Quaternion &qt);

	float quadrance(const Quaternion &q);
	float norm(const Quaternion &q);

	Quaternion normalized(const Quaternion &q);
	Quaternion conjugate(const Quaternion &q);
	Quaternion inverse(const Quaternion &q);
	Quaternion lerp(const Quaternion &q, const Quaternion &qt, float k);
	Quaternion slerp(const Quaternion &q, const Quaternion &qt, float k);

	Matrix4 toGlMatrix(const Quaternion &q);

	std::ostream &operator << (std::ostream &os, Quaternion &q);
	std::istream &operator >> (std::istream &is, Quaternion &q);

	//const void qToAngleAxis(const qtrn& q, float& theta, vec4& axis);
	//const void qPrintAngleAxis(const std::string& s, const qtrn& q);

	float radiansToDegrees(const float angle);
	float degreesToRadians(const float angle);

	float fastInvSqrt(float x);

//}

#endif // !__MATHAUX_H__