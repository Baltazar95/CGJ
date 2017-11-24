#include "MathAux.h"

////////////////////////////////////////////////////
////											////
////				  VECTOR2					////
////											////
////////////////////////////////////////////////////

Vector2::Vector2()
{ 
	x = y = 0; 
}

Vector2::Vector2(float constant)
{
	x = y = constant;
}

Vector2::Vector2(float nx, float ny)
{
	x = nx;
	y = ny;
}

void Vector2::operator += (const float s)
{
	x += s;
	y += s;
}

void Vector2::operator += (const Vector2 &v)
{
	x += v.x;
	y += v.y;
}

void Vector2::operator -= (const float s)
{
	x -= s;
	y -= s;
}

void Vector2::operator -= (const Vector2 &v)
{
	x -= v.x;
	y -= v.y;
}

void Vector2::operator *= (const float s)
{
	x *= s;
	y *= s;
}

void Vector2::operator /= (const float s)
{
	x /= s;
	y /= s;
}

void Vector2::normalize()
{
	if (x == 0.0f && y == 0.0f)
	{
		throw std::overflow_error("Normalizing a null vector");
	}
	float squareRoot = norm(*this);
	x /= squareRoot;
	y /= squareRoot;
}

void Vector2::clean()
{
	x = (floorf(x * CLEAN_VALUE) / CLEAN_VALUE);
	y = (floorf(y * CLEAN_VALUE) / CLEAN_VALUE);
}

Vector2 operator + (const Vector2 &v, const float &num)
{
	return Vector2(v.x + num, v.y + num);
}

Vector2 operator + (const Vector2 &v, const Vector2 &u)
{
	return Vector2(v.x + u.x, v.y + u.y);
}

Vector2 operator - (const Vector2 &v)
{
	return Vector2(-v.x, -v.y);
}

Vector2 operator - (const Vector2 &v, const float &num)
{
	return Vector2(v.x - num, v.y - num);
}

Vector2 operator - (const Vector2 &v, const Vector2 &u)
{
	return Vector2(v.x - u.x, v.y - u.y);
}

Vector2 operator * (const Vector2 &v, const float &num)
{
	return Vector2(v.x * num, v.y * num);
}

Vector2 operator * (const float &num, const Vector2 &v)
{
	return Vector2(num * v.x, num * v.y);
}

Vector2 operator / (const Vector2 &v, const float &num)
{
	return Vector2(v.x / num, v.y / num);
}

bool operator == (const Vector2 &v, const Vector2 &u)
{
	return (fabs(v.x - u.x) <= EPSILON && fabs(v.y - u.y) <= EPSILON);
}

float quadrance(const Vector2 &v)
{
	return v.x*v.x + v.y*v.y;
}

float norm(const Vector2 &v)
{
	return sqrt(quadrance(v));
}

float dot(const Vector2 &v, const Vector2 &u)
{
	return v.x*u.x + v.y*u.y;
}

Vector2 normalized(const Vector2 &v)
{
	if (v.x == 0.0f && v.y == 0.0f)
	{
		throw std::overflow_error("Normalizing a null vector");
	}
	return Vector2(v.x / norm(v), v.y / norm(v));
}

std::ostream &operator << (std::ostream &os, Vector2 &v)
{
	os << "(" << v.x << ", " << v.y << ")";
	return os;
}

std::istream &operator >> (std::istream &is, Vector2 &v)
{
	is.ignore(1, ' ');
	is >> v.x;
	is.ignore(1, ' ');
	is >> v.y;
	is.ignore(1, ' ');
	return is;
}


////////////////////////////////////////////////////
////											////
////				  VECTOR3					////
////											////
////////////////////////////////////////////////////

Vector3::Vector3()
{ 
	x = y = z = 0; 
}

Vector3::Vector3(float constant)
{
	x = y = z = constant;
}

Vector3::Vector3(float nx, float ny, float nz)
{
	x = nx;
	y = ny;
	z = nz;
}

//Non-normal constructors (ARE THEY REALLY NEEDED?)
Vector3::Vector3(Vector2 vec)
{
	x = vec.x;
	y = vec.y;
	z = 0;
}

Vector3::Vector3(Vector2 vec, float nz)
{
	x = vec.x;
	y = vec.y;
	z = nz;
}
////////////////////////////

void Vector3::operator += (const float s)
{
	x += s;
	y += s;
	z += s;
}

void Vector3::operator += (const Vector3 &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

void Vector3::operator -= (const float s)
{
	x -= s;
	y -= s;
	z -= s;
}

void Vector3::operator -= (const Vector3 &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

void Vector3::operator *= (const float s)
{
	x *= s;
	y *= s;
	z *= s;
}

void Vector3::operator /= (const float s)
{
	x /= s;
	y /= s;
	z /= s;
}

void Vector3::normalize()
{
	if (x == 0.0f && y == 0.0f && z == 0.0f)
	{
		throw std::overflow_error("Normalizing a null vector");
	}
	float squareRoot = norm(*this);
	x /= squareRoot;
	y /= squareRoot;
	z /= squareRoot;
}

void Vector3::clean()
{
	x = (floorf(x * CLEAN_VALUE) / CLEAN_VALUE);
	y = (floorf(y * CLEAN_VALUE) / CLEAN_VALUE);
	z = (floorf(z * CLEAN_VALUE) / CLEAN_VALUE);
}

Vector3 operator + (const Vector3 &v, const float &num)
{
	return Vector3(v.x + num, v.y + num, v.z + num);
}

Vector3 operator + (const Vector3 &v, const Vector3 &u)
{
	return Vector3(v.x + u.x, v.y + u.y, v.z + u.z);
}

Vector3 operator - (const Vector3 &v)
{
	return Vector3(-v.x, -v.y, -v.z);
}

Vector3 operator - (const Vector3 &v, const float &num)
{
	return Vector3(v.x - num, v.y - num, v.z - num);
}

Vector3 operator - (const Vector3 &v, const Vector3 &u)
{
	return Vector3(v.x - u.x, v.y - u.y, v.z - u.z);
}

Vector3 operator * (const Vector3 &v, const float &num)
{
	return Vector3(v.x * num, v.y * num, v.z * num);
}

Vector3 operator * (const float &num, const Vector3 &v)
{
	return Vector3(num * v.x, num * v.y, num * v.z);
}

Vector3 operator / (const Vector3 &v, const float &num)
{
	return Vector3(v.x / num, v.y / num, v.z / num);
}

bool operator == (const Vector3 &v, const Vector3 &u)
{
	return ((fabs(v.x - u.x) <= EPSILON && fabs(v.y - u.y) <= EPSILON && fabs(v.z - u.z) <= EPSILON));
}

float quadrance(const Vector3 &v)
{
	return v.x*v.x + v.y*v.y + v.z*v.z;
}

float norm(const Vector3 &v)
{
	return sqrt(quadrance(v));
}

float dot(const Vector3 &v, const Vector3 &u)
{
	return v.x*u.x + v.y*u.y + v.z*u.z;
}

Vector3 normalized(const Vector3 &v)
{
	if (v.x == 0.0f && v.y == 0.0f && v.z == 0.0f)
	{
		throw std::overflow_error("Normalizing a null vector");
	}
	return Vector3(v.x / norm(v), v.y / norm(v), v.z / norm(v));
}

Vector3 cross(const Vector3 &v, const Vector3 &u)
{
	return Vector3(v.y*u.z - v.z*u.y, v.z*u.x - v.x*u.z, v.x*u.y - v.y*u.x);
}

std::ostream &operator << (std::ostream &os, Vector3 &v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}

std::istream &operator >> (std::istream &is, Vector3 &v)
{
	is.ignore(1, ' ');
	is >> v.x;
	is.ignore(1, ' ');
	is >> v.y;
	is.ignore(1, ' ');
	is >> v.z;
	is.ignore(1, ' ');
	return is;
}


////////////////////////////////////////////////////
////											////
////				  VECTOR4					////
////											////
////////////////////////////////////////////////////

Vector4::Vector4()
{ 
	x = y = z = w = 0; 
}

Vector4::Vector4(float constant)
{
	x = y = z = w = constant;
}

Vector4::Vector4(float nx, float ny, float nz, float nw)
{
	x = nx;
	y = ny;
	z = nz;
	w = nw;
}

Vector4::Vector4(Vector3 vec, float nw)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = nw;
}

void Vector4::operator += (const float s)
{
	x += s;
	y += s;
	z += s;
	w += s;
}

void Vector4::operator += (const Vector4 &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
}

void Vector4::operator -= (const float s)
{
	x -= s;
	y -= s;
	z -= s;
	w -= s;
}

void Vector4::operator -= (const Vector4 &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
}

void Vector4::operator *= (const float s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;
}

void Vector4::operator /= (const float s)
{
	x /= s;
	y /= s;
	z /= s;
	w /= s;
}

void Vector4::normalize()
{
	if (x == 0.0f && y == 0.0f && z == 0.0f && w == 0.0f)
	{
		throw std::overflow_error("Normalizing a null vector");
	}
	float squareRoot = norm(*this);
	x /= squareRoot;
	y /= squareRoot;
	z /= squareRoot;
	w /= squareRoot;
}

void Vector4::clean()
{
	x = (floorf(x * CLEAN_VALUE) / CLEAN_VALUE);
	y = (floorf(y * CLEAN_VALUE) / CLEAN_VALUE);
	z = (floorf(z * CLEAN_VALUE) / CLEAN_VALUE);
	w = (floorf(w * CLEAN_VALUE) / CLEAN_VALUE);
}

Vector4 operator + (const Vector4 &v, const float &num)
{
	return Vector4(v.x + num, v.y + num, v.z + num, v.w + num);
}

Vector4 operator + (const Vector4 &v, const Vector4 &u)
{
	return Vector4(v.x + u.x, v.y + u.y, v.z + u.z, v.w + u.w);
}

Vector4 operator - (const Vector4 &v)
{
	return Vector4(-v.x, -v.y, -v.z, -v.w);
}

Vector4 operator - (const Vector4 &v, const float &num)
{
	return Vector4(v.x - num, v.y - num, v.z - num, v.w - num);
}

Vector4 operator - (const Vector4 &v, const Vector4 &u)
{
	return Vector4(v.x - u.x, v.y - u.y, v.z - u.z, v.w - u.w);
}

Vector4 operator * (const Vector4 &v, const float &num)
{
	return Vector4(v.x * num, v.y * num, v.z * num, v.w * num);
}

Vector4 operator * (const float &num, const Vector4 &v)
{
	return Vector4(num * v.x, num * v.y, num * v.z, num * v.w);
}

Vector4 operator / (const Vector4 &v, const float &num)
{
	return Vector4(v.x / num, v.y / num, v.z / num, v.w / num);
}

bool operator == (const Vector4 &v, const Vector4 &u)
{
	return ((fabs(v.x - u.x) <= EPSILON && fabs(v.y - u.y) <= EPSILON && fabs(v.z - u.z) <= EPSILON && fabs(v.w - u.w) <= EPSILON));
}

float quadrance(const Vector4 &v)
{
	return v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w;
}

float norm(const Vector4 &v)
{
	return sqrt(quadrance(v));
}

float dot(const Vector4 &v, const Vector4 &u)
{
	return v.x*u.x + v.y*u.y + v.z*u.z + v.w*u.w;
}

Vector4 normalized(const Vector4 &v)
{
	if (v.x == 0.0f && v.y == 0.0f && v.z == 0.0f && v.w == 0.0f)
	{
		throw std::overflow_error("Normalizing a null vector");
	}
	return Vector4(v.x / norm(v), v.y / norm(v), v.z / norm(v), v.w / norm(v));
}

//do i need cross for Vector4??
//Vector4 cross(const Vector4 &v, const Vector4 &u)
//{
//	return Vector4(v.y*u.z - v.z*u.y, v.z*u.x - v.x*u.z, v.x*u.y - v.y*u.x);
//}

std::ostream &operator << (std::ostream &os, Vector4 &v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return os;
}

std::istream &operator >> (std::istream &is, Vector4 &v)
{
	is.ignore(1, ' ');
	is >> v.x;
	is.ignore(1, ' ');
	is >> v.y;
	is.ignore(1, ' ');
	is >> v.z;
	is.ignore(1, ' ');
	is >> v.w;
	is.ignore(1, ' ');
	return is;
}

////////////////////////////////////////////////////
////											////
////				   MATRIX2					////
////											////
////////////////////////////////////////////////////

Matrix2::Matrix2()
{
	for(int i = 0; i < SIZE2X2; i++)
	{
		matrix[i] = 0.0f;
	}
}

Matrix2::Matrix2(float constant)
{
	for (int i = 0; i < SIZE2X2; i++)
	{
		matrix[i] = constant;
	}
}

Matrix2::Matrix2(float m[SIZE2X2])
{
	matrix[0] = m[0];
	matrix[1] = m[2];
	matrix[2] = m[1];
	matrix[3] = m[3];
}

Matrix2::Matrix2(float xx, float xy, float yx, float yy)
{
	matrix[0] = xx;
	matrix[1] = yx;
	matrix[2] = xy;
	matrix[3] = yy;
}

Matrix2::Matrix2(const Vector2 &v, const Vector2 &u)
{
	matrix[0] = v.x;
	matrix[1] = u.x;
	matrix[2] = v.y;
	matrix[3] = u.y;
}

void Matrix2::operator += (const Matrix2 &m)
{
	for (int i = 0; i < SIZE2X2; i++)
	{
		matrix[i] += m.matrix[i];
	}
}

void Matrix2::operator -= (const Matrix2 &m)
{
	for (int i = 0; i < SIZE2X2; i++)
	{
		matrix[i] -= m.matrix[i];
	}
}

void Matrix2::operator *= (const float num)
{
	for (int i = 0; i < SIZE2X2; i++)
	{
		matrix[i] *= num;
	}
}

void Matrix2::operator *= (const Matrix2 &m)
{
	Matrix2 n = Matrix2(matrix);

	for (int i = 0; i < RCSIZE2X2; i++)
	{
		for (int j = 0; j < RCSIZE2X2; j++)
		{
			matrix[j * RCSIZE2X2 + i] = 0;

			for (int k = 0; k < RCSIZE2X2; k++)
			{
				matrix[j * RCSIZE2X2 + i] += n.matrix[k * RCSIZE2X2 + i] * m.matrix[j * RCSIZE2X2 + k];
			}
		}
	}
}

void Matrix2::operator /= (const float num)
{
	for (int i = 0; i < SIZE2X2; i++)
	{
		matrix[i] /= num;
	}
}

void Matrix2::clean()
{
	for(int i = 0; i < SIZE2X2; i++)
	{
		matrix[i] = floorf(matrix[i] * CLEAN_VALUE) / CLEAN_VALUE;
	}
}

Matrix2 operator + (const Matrix2 &m, const Matrix2 &n)
{
	Matrix2 newM = Matrix2();

	for (int i = 0; i < SIZE2X2; i++)
	{
		newM.matrix[i] = m.matrix[i] + n.matrix[i];
	}

	return newM;
}

Matrix2 operator - (const Matrix2 &m, const Matrix2 &n)
{
	Matrix2 newM = Matrix2();

	for (int i = 0; i < SIZE2X2; i++)
	{
		newM.matrix[i] = m.matrix[i] - n.matrix[i];
	}

	return newM;
}

Matrix2 operator * (const Matrix2 &m, const Matrix2 &n)
{
	Matrix2 newM = Matrix2();

	for (int i = 0; i < RCSIZE2X2; i++)
	{
		for (int j = 0; j < RCSIZE2X2; j++)
		{
			newM.matrix[j * RCSIZE2X2 + i] = 0;

			for (int k = 0; k < RCSIZE2X2; k++)
			{
				newM.matrix[j * RCSIZE2X2 + i] += m.matrix[k * RCSIZE2X2 + i] * n.matrix[j * RCSIZE2X2 + k];
			}
		}
	}

	return newM;
}

Matrix2 operator * (const Matrix2 &m, const float num)
{
	Matrix2 newM = Matrix2();

	for (int i = 0; i < SIZE2X2; i++)
	{
		newM.matrix[i] = m.matrix[i] * num;
	}

	return newM;
}

Matrix2 operator * (const float num, const Matrix2 &m)
{
	Matrix2 newM = Matrix2();

	for (int i = 0; i < SIZE2X2; i++)
	{
		newM.matrix[i] = num * m.matrix[i];
	}

	return newM;
}

Vector2 operator * (const Matrix2 &m, const Vector2 &v)
{
	Vector2 u = Vector2();

	u.x = m.matrix[0] * v.x + m.matrix[2] * v.y;
	u.y = m.matrix[1] * v.x + m.matrix[3] * v.y;

	return u;
}

Vector2 operator * (const Vector2 &v, const Matrix2 &m)
{
	Vector2 u = Vector2();

	u.x = v.x * m.matrix[0] + v.y * m.matrix[1];
	u.y = v.x * m.matrix[2] + v.y * m.matrix[3];

	return u;
}

Matrix2 operator / (const Matrix2 &m, const float num)
{
	Matrix2 newM = Matrix2();

	for (int i = 0; i < SIZE2X2; i++)
	{
		newM.matrix[i] = m.matrix[i] / num;
	}

	return newM;
}

bool operator == (const Matrix2 &m, const Matrix2 &n)
{
	for (int i = 0; i < SIZE2X2; i++)
	{
		if (fabs(m.matrix[i] - n.matrix[i]) > EPSILON)
		{
			return false;
		}
	}
	return true;
}

Matrix2 transpose(const Matrix2 &m)
{
	return Matrix2(m.matrix[0], m.matrix[1], m.matrix[2], m.matrix[3]);
}

Matrix2 inverse(const Matrix2 &m)
{
	float value = determinant(m);
	if (value == 0)
	{
		throw new std::overflow_error("Divided by zero");
	}
	return (1 / value)*Matrix2(m.matrix[3], -m.matrix[2],  -m.matrix[1], m.matrix[0]);
}

float determinant(const Matrix2 &m)
{
	return m.matrix[0] * m.matrix[3] - m.matrix[1] * m.matrix[2];
}

std::ostream &operator << (std::ostream &os, Matrix2 &m)
{
	os << "|" << m.matrix[0] << " " << m.matrix[2] << "|\n|" << m.matrix[1] << " " << m.matrix[3] << "|";
	return os;
}

std::istream &operator >> (std::istream &is, Matrix2 &m)
{
	is.ignore(1, ' ');
	is >> m.matrix[0];
	is.ignore(1, ' ');
	is >> m.matrix[2];
	is.ignore(3, ' ');
	is >> m.matrix[1];
	is.ignore(1, ' ');
	is >> m.matrix[3];
	is.ignore(1, ' ');
	return is;
}


////////////////////////////////////////////////////
////											////
////				   MATRIX3					////
////											////
////////////////////////////////////////////////////

Matrix3::Matrix3()
{
	for (int i = 0; i < SIZE3X3; i++)
	{
		matrix[i] = 0.0f;
	}
}

Matrix3::Matrix3(float constant)
{
	for (int i = 0; i < SIZE3X3; i++)
	{
		matrix[i] = constant;
	}
}

Matrix3::Matrix3(float m[SIZE3X3])
{
	matrix[0] = m[0];
	matrix[1] = m[3];
	matrix[2] = m[6];
	matrix[3] = m[1];
	matrix[4] = m[4];
	matrix[5] = m[7];
	matrix[6] = m[2];
	matrix[7] = m[5];
	matrix[8] = m[8];
}

Matrix3::Matrix3(float xx, float xy, float xz, float yx, float yy, float yz, float zx, float zy, float zz)
{
	matrix[0] = xx;
	matrix[1] = yx;
	matrix[2] = zx;
	matrix[3] = xy;
	matrix[4] = yy;
	matrix[5] = zy;
	matrix[6] = xz;
	matrix[7] = yz;
	matrix[8] = zz;
}

Matrix3::Matrix3(const Vector3 &v, const Vector3 &u, const Vector3 &w)
{
	matrix[0] = v.x;
	matrix[1] = u.x;
	matrix[2] = w.x;
	matrix[3] = v.y;
	matrix[4] = u.y;
	matrix[5] = w.y;
	matrix[6] = v.z;
	matrix[7] = u.z;
	matrix[8] = w.z;
}

void Matrix3::operator += (const Matrix3 &m)
{
	for (int i = 0; i < SIZE3X3; i++)
	{
		matrix[i] += m.matrix[i];
	}
}

void Matrix3::operator -= (const Matrix3 &m)
{
	for (int i = 0; i < SIZE3X3; i++)
	{
		matrix[i] -= m.matrix[i];
	}
}

void Matrix3::operator *= (const float num)
{
	for (int i = 0; i < SIZE3X3; i++)
	{
		matrix[i] *= num;
	}
}

void Matrix3::operator *= (const Matrix3 &m)
{
	Matrix3 n = Matrix3(matrix);

	for (int i = 0; i < RCSIZE3X3; i++)
	{
		for (int j = 0; j < RCSIZE3X3; j++)
		{
			matrix[j * RCSIZE3X3 + i] = 0;

			for (int k = 0; k < RCSIZE3X3; k++)
			{
				matrix[j * RCSIZE3X3 + i] += n.matrix[k * RCSIZE3X3 + i] * m.matrix[j * RCSIZE3X3 + k];
			}
		}
	}
}

void Matrix3::operator /= (const float num)
{
	for (int i = 0; i < SIZE3X3; i++)
	{
		matrix[i] /= num;
	}
}

void Matrix3::clean()
{
	for (int i = 0; i < SIZE3X3; i++)
	{
		matrix[i] = floorf(matrix[i] * CLEAN_VALUE) / CLEAN_VALUE;
	}
}

Matrix3 operator + (const Matrix3 &m, const Matrix3 &n)
{
	Matrix3 newM = Matrix3();

	for (int i = 0; i < SIZE3X3; i++)
	{
		newM.matrix[i] = m.matrix[i] + n.matrix[i];
	}

	return newM;
}

Matrix3 operator - (const Matrix3 &m, const Matrix3 &n)
{
	Matrix3 newM = Matrix3();

	for (int i = 0; i < SIZE3X3; i++)
	{
		newM.matrix[i] = m.matrix[i] - n.matrix[i];
	}

	return newM;
}

Matrix3 operator * (const Matrix3 &m, const Matrix3 &n)
{
	Matrix3 newM = Matrix3();

	for (int i = 0; i < RCSIZE3X3; i++)
	{
		for (int j = 0; j < RCSIZE3X3; j++)
		{
			newM.matrix[j * RCSIZE3X3 + i] = 0;

			for (int k = 0; k < RCSIZE3X3; k++)
			{
				newM.matrix[j * RCSIZE3X3 + i] += m.matrix[k * RCSIZE3X3 + i] * n.matrix[j * RCSIZE3X3 + k];
			}
		}
	}

	return newM;
}

Matrix3 operator * (const Matrix3 &m, const float num)
{
	Matrix3 newM = Matrix3();

	for (int i = 0; i < SIZE3X3; i++)
	{
		newM.matrix[i] = m.matrix[i] * num;
	}

	return newM;
}

Matrix3 operator * (const float num, const Matrix3 &m)
{
	Matrix3 newM = Matrix3();

	for (int i = 0; i < SIZE3X3; i++)
	{
		newM.matrix[i] = num * m.matrix[i];
	}

	return newM;
}

Vector3 operator * (const Matrix3 &m, const Vector3 &v)
{
	Vector3 u = Vector3();

	u.x = m.matrix[0] * v.x + m.matrix[3] * v.y + m.matrix[6] * v.z;
	u.y = m.matrix[1] * v.x + m.matrix[4] * v.y + m.matrix[7] * v.z;
	u.z = m.matrix[2] * v.x + m.matrix[5] * v.y + m.matrix[8] * v.z;

	return u;
}

Vector3 operator * (const Vector3 &v, const Matrix3 &m)
{
	Vector3 u = Vector3();

	u.x = v.x * m.matrix[0] + v.y * m.matrix[1] + v.z * m.matrix[2];
	u.y = v.x * m.matrix[3] + v.y * m.matrix[4] + v.z * m.matrix[5];
	u.z = v.x * m.matrix[6] + v.y * m.matrix[7] + v.z * m.matrix[8];

	return u;
}

Matrix3 operator / (const Matrix3 &m, const float num)
{
	Matrix3 newM = Matrix3();

	for (int i = 0; i < SIZE3X3; i++)
	{
		newM.matrix[i] = m.matrix[i] / num;
	}

	return newM;
}

bool operator == (const Matrix3 &m, const Matrix3 &n)
{
	for (int i = 0; i < SIZE3X3; i++)
	{
		if (fabs(m.matrix[i] - n.matrix[i]) > EPSILON)
		{
			return false;
		}
	}
	return true;
}

Matrix3 transpose(const Matrix3 &m)
{
	return Matrix3(m.matrix[0], m.matrix[1], m.matrix[2],
					m.matrix[3], m.matrix[4], m.matrix[5],
					m.matrix[6], m.matrix[7], m.matrix[8]);
}

Matrix3 inverse(const Matrix3 &m)
{
	Matrix3 newM =  Matrix3();

	//Matrix of Minors and Co-Factors
	newM.matrix[0] = determinant(Matrix2(m.matrix[4], m.matrix[7], m.matrix[5], m.matrix[8]));
	newM.matrix[1] = determinant(Matrix2(m.matrix[3], m.matrix[6], m.matrix[5], m.matrix[8]));
	newM.matrix[2] = determinant(Matrix2(m.matrix[3], m.matrix[6], m.matrix[4], m.matrix[7]));
	newM.matrix[3] = determinant(Matrix2(m.matrix[1], m.matrix[7], m.matrix[2], m.matrix[8]));
	newM.matrix[4] = determinant(Matrix2(m.matrix[0], m.matrix[6], m.matrix[2], m.matrix[8]));
	newM.matrix[5] = determinant(Matrix2(m.matrix[0], m.matrix[6], m.matrix[1], m.matrix[7]));
	newM.matrix[6] = determinant(Matrix2(m.matrix[1], m.matrix[4], m.matrix[2], m.matrix[5]));
	newM.matrix[7] = determinant(Matrix2(m.matrix[0], m.matrix[3], m.matrix[2], m.matrix[5]));
	newM.matrix[8] = determinant(Matrix2(m.matrix[0], m.matrix[3], m.matrix[1], m.matrix[4]));

	//Matrix of Co-Factors
	newM.matrix[1] = -newM.matrix[1];
	newM.matrix[3] = -newM.matrix[3];
	newM.matrix[5] = -newM.matrix[5];
	newM.matrix[7] = -newM.matrix[7];

	//Adjoint matrix
	newM = transpose(newM);

	float value = determinant(m);
	if (value == 0)
	{
		throw new std::overflow_error("Divided by zero");
	}
	return (1/value) * newM;
}

float determinant(const Matrix3 &m)
{
	return m.matrix[0] * (m.matrix[4] * m.matrix[8] - m.matrix[5] * m.matrix[7]) 
		- m.matrix[1] * (m.matrix[3] * m.matrix[8] - m.matrix[5] * m.matrix[6])
		+ m.matrix[2] * (m.matrix[3] * m.matrix[7] - m.matrix[4] * m.matrix[6]);
}

std::ostream &operator << (std::ostream &os, Matrix3 &m)
{
	os << "|" << m.matrix[0] << " " << m.matrix[3] << " " << m.matrix[6] << "|\n" 
		<< "|" << m.matrix[1] << " " << m.matrix[4] << " " << m.matrix[7] << "|\n" 
		<< "|" << m.matrix[2] << " " << m.matrix[5] << " " << m.matrix[8] << "|";
	return os;
}

std::istream &operator >> (std::istream &is, Matrix3 &m)
{
	is.ignore(1, ' ');
	is >> m.matrix[0];
	is.ignore(1, ' ');
	is >> m.matrix[3];
	is.ignore(1, ' ');
	is >> m.matrix[6];
	is.ignore(3, ' ');
	is >> m.matrix[1];
	is.ignore(1, ' ');
	is >> m.matrix[4];
	is.ignore(1, ' ');
	is >> m.matrix[7];
	is.ignore(3, ' ');
	is >> m.matrix[2];
	is.ignore(1, ' ');
	is >> m.matrix[5];
	is.ignore(1, ' ');
	is >> m.matrix[8];
	is.ignore(3, ' ');
	return is;
}


////////////////////////////////////////////////////
////											////
////				   MATRIX4					////
////											////
////////////////////////////////////////////////////

Matrix4::Matrix4()
{
	for (int i = 0; i < SIZE4X4; i++)
	{
		matrix[i] = 0.0f;
	}
}

Matrix4::Matrix4(float constant)
{
	for (int i = 0; i < SIZE4X4; i++)
	{
		matrix[i] = constant;
	}
}

Matrix4::Matrix4(float m[SIZE4X4])
{
	matrix[0] = m[0];
	matrix[1] = m[4];
	matrix[2] = m[8];
	matrix[3] = m[12];

	matrix[4] = m[1];
	matrix[5] = m[5];
	matrix[6] = m[9];
	matrix[7] = m[13];

	matrix[8] = m[2];
	matrix[9] = m[6];
	matrix[10] = m[10];
	matrix[11] = m[14];

	matrix[12] = m[3];
	matrix[13] = m[7];
	matrix[14] = m[11];
	matrix[15] = m[15];
}

Matrix4::Matrix4(float xx, float xy, float xz, float xw,
					float yx, float yy, float yz, float yw,
					float zx, float zy, float zz, float zw,
					float wx, float wy, float wz, float ww)
{
	matrix[0] = xx;
	matrix[1] = yx;
	matrix[2] = zx;
	matrix[3] = wx;

	matrix[4] = xy;
	matrix[5] = yy;
	matrix[6] = zy;
	matrix[7] = wy;

	matrix[8] = xz;
	matrix[9] = yz;
	matrix[10] = zz;
	matrix[11] = wz;

	matrix[12] = xw;
	matrix[13] = yw;
	matrix[14] = zw;
	matrix[15] = ww;
}

Matrix4::Matrix4(const Matrix3 &m)
{
	matrix[0] = m.matrix[0];
	matrix[1] = m.matrix[1];
	matrix[2] = m.matrix[2];
	matrix[3] = 0.0f;

	matrix[4] = m.matrix[4];
	matrix[5] = m.matrix[5];
	matrix[6] = m.matrix[6];
	matrix[7] = 0.0f;

	matrix[8] = m.matrix[8];
	matrix[9] = m.matrix[9];
	matrix[10] = m.matrix[10];
	matrix[11] = 0.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;
}

Matrix4::Matrix4(const Vector4 &v, const Vector4 &u, const Vector4 &w, const Vector4 &n)
{
	matrix[0] = v.x;
	matrix[1] = u.x;
	matrix[2] = w.x;
	matrix[3] = n.x;

	matrix[4] = v.y;
	matrix[5] = u.y;
	matrix[6] = w.y;
	matrix[7] = n.y;

	matrix[8] = v.z;
	matrix[9] = u.z;
	matrix[10] = w.z;
	matrix[11] = n.z;

	matrix[12] = v.w;
	matrix[13] = u.w;
	matrix[14] = w.w;
	matrix[15] = n.w;
}

void Matrix4::operator += (const Matrix4 &m)
{
	for (int i = 0; i < SIZE4X4; i++)
	{
		matrix[i] += m.matrix[i];
	}
}

void Matrix4::operator -= (const Matrix4 &m)
{
	for (int i = 0; i < SIZE4X4; i++)
	{
		matrix[i] -= m.matrix[i];
	}
}

void Matrix4::operator *= (const float num)
{
	for (int i = 0; i < SIZE4X4; i++)
	{
		matrix[i] *= num;
	}
}

void Matrix4::operator *= (const Matrix4 &m)
{
	Matrix4 n = Matrix4(matrix);

	for (int i = 0; i < RCSIZE4X4; i++)
	{
		for (int j = 0; j < RCSIZE4X4; j++)
		{
			matrix[j * RCSIZE4X4 + i] = 0;

			for (int k = 0; k < RCSIZE4X4; k++)
			{
				matrix[j * RCSIZE4X4 + i] += n.matrix[k * RCSIZE4X4 + i] * m.matrix[j * RCSIZE4X4 + k];
			}
		}
	}
}

void Matrix4::operator /= (const float num)
{
	for (int i = 0; i < SIZE4X4; i++)
	{
		matrix[i] /= num;
	}
}

void Matrix4::clean()
{
	for (int i = 0; i < SIZE4X4; i++)
	{
		matrix[i] = floorf(matrix[i] * CLEAN_VALUE) / CLEAN_VALUE;
	}
}

Matrix4 operator + (const Matrix4 &m, const Matrix4 &n)
{
	Matrix4 newM = Matrix4();

	for (int i = 0; i < SIZE4X4; i++)
	{
		newM.matrix[i] = m.matrix[i] + n.matrix[i];
	}

	return newM;
}

Matrix4 operator - (const Matrix4 &m, const Matrix4 &n)
{
	Matrix4 newM = Matrix4();

	for (int i = 0; i < SIZE4X4; i++)
	{
		newM.matrix[i] = m.matrix[i] - n.matrix[i];
	}

	return newM;
}

Matrix4 operator * (const Matrix4 &m, const Matrix4 &n)
{
	Matrix4 newM = Matrix4();

	for (int i = 0; i < RCSIZE4X4; i++)
	{
		for (int j = 0; j < RCSIZE4X4; j++)
		{
			newM.matrix[j * RCSIZE4X4 + i] = 0;

			for (int k = 0; k < RCSIZE4X4; k++)
			{
				newM.matrix[j * RCSIZE4X4 + i] += m.matrix[k * RCSIZE4X4 + i] * n.matrix[j * RCSIZE4X4 + k];
			}
		}
	}

	return newM;
}

Matrix4 operator * (const Matrix4 &m, const float num)
{
	Matrix4 newM = Matrix4();

	for (int i = 0; i < SIZE4X4; i++)
	{
		newM.matrix[i] = m.matrix[i] * num;
	}

	return newM;
}

Matrix4 operator * (const float num, const Matrix4 &m)
{
	Matrix4 newM = Matrix4();

	for (int i = 0; i < SIZE4X4; i++)
	{
		newM.matrix[i] = num * m.matrix[i];
	}

	return newM;
}

Vector4 operator * (const Matrix4 &m, const Vector4 &v)
{
	Vector4 u = Vector4();

	u.x = m.matrix[0] * v.x + m.matrix[4] * v.y + m.matrix[8] * v.z + m.matrix[12] * v.w;
	u.y = m.matrix[1] * v.x + m.matrix[5] * v.y + m.matrix[9] * v.z + m.matrix[13] * v.w;
	u.z = m.matrix[2] * v.x + m.matrix[6] * v.y + m.matrix[10] * v.z + m.matrix[14] * v.w;
	u.w = m.matrix[3] * v.x + m.matrix[7] * v.y + m.matrix[11] * v.z + m.matrix[15] * v.w;

	return u;
}

Vector4 operator * (const Vector4 &v, const Matrix4 &m)
{
	Vector4 u = Vector4();

	u.x = v.x * m.matrix[0] + v.y * m.matrix[1] + v.z * m.matrix[2] + v.w * m.matrix[3];
	u.y = v.x * m.matrix[4] + v.y * m.matrix[5] + v.z * m.matrix[6] + v.w * m.matrix[7];
	u.z = v.x * m.matrix[8] + v.y * m.matrix[9] + v.z * m.matrix[10] + v.w * m.matrix[11];
	u.w = v.x * m.matrix[12] + v.y * m.matrix[13] + v.z * m.matrix[14] + v.w * m.matrix[15];

	return u;
}

Matrix4 operator / (const Matrix4 &m, const float num)
{
	Matrix4 newM = Matrix4();

	for (int i = 0; i < SIZE4X4; i++)
	{
		newM.matrix[i] = m.matrix[i] / num;
	}

	return newM;
}

bool operator == (const Matrix4 &m, const Matrix4 &n)
{
	for (int i = 0; i < SIZE4X4; i++)
	{
		if (fabs(m.matrix[i] - n.matrix[i]) > EPSILON)
		{
			return false;
		}
	}
	return true;
}

Matrix4 transpose(const Matrix4 &m)
{
	MatrixFactory mf;
	return mf.convert3To4(transpose(mf.convert4To3(m)));
}

Matrix4 inverse(const Matrix4 &m)
{
	MatrixFactory mf;
	return mf.convert3To4(inverse(mf.convert4To3(m)));
}

float determinant(const Matrix4 &m)
{
	return m.matrix[0] * m.matrix[5] * m.matrix[10] * m.matrix[15] + 
			m.matrix[4] * m.matrix[9] * m.matrix[14] * m.matrix[3] +
			m.matrix[8] * m.matrix[13] * m.matrix[2] * m.matrix[7] + 
			m.matrix[12] * m.matrix[1] * m.matrix[6] * m.matrix[11] -
			(m.matrix[3] * m.matrix[6] * m.matrix[9] * m.matrix[12] + 
			m.matrix[7] * m.matrix[10] * m.matrix[13] * m.matrix[0] + 
			m.matrix[11] * m.matrix[14] * m.matrix[1] * m.matrix[4] + 
			m.matrix[15] * m.matrix[2] * m.matrix[5] * m.matrix[8]);
}

std::ostream &operator << (std::ostream &os, Matrix4 &m)
{
	os << "|" << m.matrix[0] << " " << m.matrix[4] << " " << m.matrix[8] << " " << m.matrix[12] << "|\n"
		<< "|" << m.matrix[1] << " " << m.matrix[5] << " " << m.matrix[9] << " " << m.matrix[13] << "|\n"
		<< "|" << m.matrix[2] << " " << m.matrix[6] << " " << m.matrix[10] << " " << m.matrix[14] << "|\n"
		<< "|" << m.matrix[3] << " " << m.matrix[7] << " " << m.matrix[11] << " " << m.matrix[15] << "|";
	return os;
}

std::istream &operator >> (std::istream &is, Matrix4 &m)
{
	is.ignore(1, ' ');
	is >> m.matrix[0];
	is.ignore(1, ' ');
	is >> m.matrix[4];
	is.ignore(1, ' ');
	is >> m.matrix[8];
	is.ignore(1, ' ');
	is >> m.matrix[12];
	is.ignore(3, ' ');
	is >> m.matrix[1];
	is.ignore(1, ' ');
	is >> m.matrix[5];
	is.ignore(1, ' ');
	is >> m.matrix[9];
	is.ignore(1, ' ');
	is >> m.matrix[13];
	is.ignore(3, ' ');
	is >> m.matrix[2];
	is.ignore(1, ' ');
	is >> m.matrix[6];
	is.ignore(1, ' ');
	is >> m.matrix[10];
	is.ignore(1, ' ');
	is >> m.matrix[14];
	is.ignore(3, ' ');
	is >> m.matrix[3];
	is.ignore(1, ' ');
	is >> m.matrix[7];
	is.ignore(1, ' ');
	is >> m.matrix[11];
	is.ignore(1, ' ');
	is >> m.matrix[15];
	is.ignore(1, ' ');
	return is;
}


////////////////////////////////////////////////////
////											////
////				MATRIX FACTORY				////
////											////
////////////////////////////////////////////////////

Matrix2 MatrixFactory::identity2()
{
	return Matrix2(1.0f, 0.0f, 0.0f, 1.0f);
}

Matrix3 MatrixFactory::identity3()
{
	return Matrix3(1.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 1.0f);
}

Matrix4 MatrixFactory::identity4()
{
	return Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix3 MatrixFactory::dual(const Vector3 &v)
{
	return Matrix3(0.0f, -v.z, v.y,
					v.z, 0.0f, -v.x,
					-v.y, v.x, 0.0f);
}

Matrix3 MatrixFactory::normalMatrix(const Matrix3 &m)
{
	return transpose(inverse(m));
}

Matrix4 MatrixFactory::normalMatrix(const Matrix4 &m)
{
	return convert3To4(transpose(inverse(convert4To3(m))));
}

Matrix2 MatrixFactory::rotation(const float angle)
{
	float radian = degreesToRadians(angle);
	return Matrix2(cos(radian), -sin(radian), sin(radian), cos(radian));
}

Matrix3 MatrixFactory::rotation(const Vector3 &axis, const float angle)
{
	Vector3 normalizedAxis = normalized(axis);
	float radian = degreesToRadians(angle);
	Matrix3 m = dual(normalizedAxis);
	return identity3() + sin(radian) * m + (1 - cos(radian)) * (m * m);
}

Matrix4 MatrixFactory::rotation(const Vector4 &axis, const float angle)
{
	return convert3To4(rotation(Vector3(axis.x, axis.y, axis.z), angle));
}

Matrix2 MatrixFactory::scale(const float x, const float y)
{
	return Matrix2(x, 0.0f, 0.0f, y);
}

Matrix3 MatrixFactory::scale(const float x, const float y, const float z)
{
	return Matrix3(x, 0.0f, 0.0f,
					0.0f, y, 0.0f,
					0.0f, 0.0f, z);
}

Matrix4 MatrixFactory::scale(const float x, const float y, const float z, const float w)
{
	return convert3To4(scale(x, y, z));
}

Matrix2 MatrixFactory::shear2x(const float shearFactor)
{
	return Matrix2(1.0f, 0.0f, shearFactor, 1.0f);
}

Matrix2 MatrixFactory::shear2y(const float shearFactor)
{
	return Matrix2(1.0f, shearFactor, 0.0f, 1.0f);
}

Matrix3 MatrixFactory::shear3x(const float shearFactor)
{
	return Matrix3(1.0f, shearFactor, shearFactor,
					0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 1.0f);
}

Matrix3 MatrixFactory::shear3y(const float shearFactor)
{
	return Matrix3(1.0f, 0.0f, 0.0f,
					shearFactor, 1.0f, shearFactor,
					0.0f, 0.0f, 1.0f);
}

Matrix3 MatrixFactory::shear3z(const float shearFactor)
{
	return Matrix3(1.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f,
					shearFactor, shearFactor, 1.0f);
}

Matrix4 MatrixFactory::shear4x(const float shearFactor)
{
	return convert3To4(Matrix3(1.0f, shearFactor, shearFactor,
								0.0f, 1.0f, 0.0f,
								0.0f, 0.0f, 1.0f));
}

Matrix4 MatrixFactory::shear4y(const float shearFactor)
{
	return convert3To4(Matrix3(1.0f, 0.0f, 0.0f,
								shearFactor, 1.0f, shearFactor,
								0.0f, 0.0f, 1.0f));
}

Matrix4 MatrixFactory::shear4z(const float shearFactor)
{
	return convert3To4(Matrix3(1.0f, 0.0f, 0.0f,
								0.0f, 1.0f, 0.0f,
								shearFactor, shearFactor, 1.0f));
}

//This function doesn't make sense for now, investigate further
//Matrix2 translation(const Vector2 &translationFactors)
//{
//
//}

//////////////////////////////////////////////////////////

Matrix4 MatrixFactory::translation(const Vector3 &v)
{
	return Matrix4(1.0f, 0.0f, 0.0f, v.x,
					0.0f, 1.0f, 0.0f, v.y,
					0.0f, 0.0f, 1.0f, v.z,
					0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 MatrixFactory::translation(const float x, const float y, const float z)
{
	return Matrix4(1.0f, 0.0f, 0.0f, x,
					0.0f, 1.0f, 0.0f, y,
					0.0f, 0.0f, 1.0f, z,
					0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 MatrixFactory::viewMatrix(Vector3 eye, Vector3 center, Vector3 up)
{
	Vector3 v, s, u;
	Matrix4 R, T;

	v = center - eye;
	v.normalize();

	s = dual(v) * up;
	s.normalize();

	u = dual(s) * v;

	R = Matrix4(s.x, s.y, s.z, 0.0f,
				u.x, u.y, u.z, 0.0f,
				-v.x, -v.y, -v.z, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);

	T = translation(-eye.x, -eye.y, -eye.z);

	return R*T;
}

Matrix4 MatrixFactory::orthographicMatrix(float left, float right, float bottom, float top, float near, float far)
{
	return Matrix4((2 / (right - left)), 0.0f, 0.0f, ((left + right) / (left - right)),
					0.0f, (2 / (top - bottom)), 0.0f, ((bottom + top) / (bottom - top)),
					0.0f, 0.0f, (2 / (near - far)), ((near + far) / (near - far)),
					0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 MatrixFactory::perspectiveMatrix(float fovy, float aspect, float zNear, float zFar)
{
	fovy = degreesToRadians(fovy);
	float d = 1 / tan(fovy/2);
	return Matrix4((d / aspect), 0.0f, 0.0f, 0.0f,
					0.0f, d, 0.0f, 0.0f,
					0.0f, 0.0f, ((zFar + zNear) / (zNear - zFar)), ((2 * zFar * zNear) / (zNear - zFar)),
					0.0f, 0.0f, -1.0f, 0.0f);
}

Matrix4 MatrixFactory::convert3To4(const Matrix3 &m)
{
	return Matrix4(m.matrix[0], m.matrix[3], m.matrix[6], 0.0f,
					m.matrix[1], m.matrix[4], m.matrix[7], 0.0f,
					m.matrix[2], m.matrix[5], m.matrix[8], 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix3 MatrixFactory::convert4To3(const Matrix4 &m)
{
	return Matrix3(m.matrix[0], m.matrix[4], m.matrix[8],
					m.matrix[1], m.matrix[5], m.matrix[9],
					m.matrix[2], m.matrix[6], m.matrix[10]);
}


////////////////////////////////////////////////////
////											////
////				QUATERNIONS					////
////											////
////////////////////////////////////////////////////

Quaternion::Quaternion()
{
	t = 0.0f;
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Quaternion::Quaternion(float nt, float nx, float ny, float nz)
{
	t = nt;
	x = nx;
	y = ny;
	z = nz;
}

Quaternion::Quaternion(float angle, Vector4 axis)
{
	Vector3 axis3 = Vector3(axis.x, axis.y, axis.z);
	axis3.normalize();

	angle = degreesToRadians(angle);

	t = cos(angle / 2);
	float s = sin(angle / 2);
	x = axis3.x * s;
	y = axis3.y * s;
	z = axis3.z * s;

	//Quaternion::clean();
	Quaternion::normalize();
}

void Quaternion::operator += (const Quaternion &q)
{
	t += q.t;
	x += q.x;
	y += q.y;
	z += q.z;
}

void Quaternion::operator -= (const Quaternion &q)
{
	t -= q.t;
	x -= q.x;
	y -= q.y;
	z -= q.z;
}

void Quaternion::operator *= (const float num)
{
	t *= num;
	x *= num;
	y *= num;
	z *= num;
}

void Quaternion::operator *= (const Quaternion &q)
{
	float nt, nx, ny, nz;

	nt = t * q.t - x * q.x - y * q.y - z * q.z;
	nx = t * q.x + x * q.t + y * q.z - z * q.y;
	ny = t * q.y + y * q.t + z * q.x - x * q.z;
	nz = t * q.z + z * q.t + x * q.y - y * q.x;

	t = nt;
	x = nx;
	y = ny;
	z = nz;
}

void Quaternion::operator /= (const float num)
{
	t /= num;
	x /= num;
	y /= num;
	z /= num;
}

void Quaternion::normalize()
{
	if (t == 0.0f && x == 0.0f && y == 0.0f && z == 0.0f)
	{
		throw std::overflow_error("Normalizing a null vector");
	}

	float s = 1.0f / sqrt(t * t + x * x + y * y + z * z);

	t *= s;
	x *= s;
	y *= s;
	z *= s;
}

void Quaternion::clean()
{
	t = (floorf(t * CLEAN_VALUE) / CLEAN_VALUE);
	x = (floorf(x * CLEAN_VALUE) / CLEAN_VALUE);
	y = (floorf(y * CLEAN_VALUE) / CLEAN_VALUE);
	z = (floorf(z * CLEAN_VALUE) / CLEAN_VALUE);
}

Quaternion operator + (const Quaternion &q, const Quaternion &qt)
{
	Quaternion resQ = Quaternion();

	resQ.t = q.t + qt.t;
	resQ.x = q.x + qt.x;
	resQ.y = q.y + qt.y;
	resQ.z = q.z + qt.z;

	return resQ;
}

Quaternion operator - (const Quaternion &q, const Quaternion &qt)
{
	Quaternion resQ = Quaternion();

	resQ.t = q.t - qt.t;
	resQ.x = q.x - qt.x;
	resQ.y = q.y - qt.y;
	resQ.z = q.z - qt.z;

	return resQ;
}

Quaternion operator * (const Quaternion &q, const Quaternion &qt)
{
	Quaternion resQ = Quaternion();

	resQ.t = q.t * qt.t - q.x * qt.x - q.y * qt.y - q.z * qt.z;
	resQ.x = q.t * qt.x + q.x * qt.t + q.y * qt.z - q.z * qt.y;
	resQ.y = q.t * qt.y + q.y * qt.t + q.z * qt.x - q.x * qt.z;
	resQ.z = q.t * qt.z + q.z * qt.t + q.x * qt.y - q.y * qt.x;

	return resQ;
}

Quaternion operator * (const Quaternion &q, const float num)
{
	Quaternion resQ = Quaternion();

	resQ.t = q.t * num;
	resQ.x = q.x * num;
	resQ.y = q.y * num;
	resQ.z = q.z * num;

	return resQ;
}

Quaternion operator * (const float num, const Quaternion &q)
{
	Quaternion resQ = Quaternion();

	resQ.t = num * q.t;
	resQ.x = num * q.x;
	resQ.y = num * q.y;
	resQ.z = num * q.z;

	return resQ;
}

Quaternion operator / (const Quaternion &q, const float num)
{
	Quaternion resQ = Quaternion();

	resQ.t = q.t / num;
	resQ.x = q.x / num;
	resQ.y = q.y / num;
	resQ.z = q.z / num;

	return resQ;
}

bool operator == (const Quaternion &q, const Quaternion &qt)
{
	return ((fabs(q.t - qt.t) <= EPSILON) && (fabs(q.x - qt.x) <= EPSILON) && (fabs(q.y - qt.y) <= EPSILON) && (fabs(q.z - qt.z) <= EPSILON));
}

float quadrance(const Quaternion &q)
{
	return q.t * q.t + q.x * q.x + q.y * q.y + q.z * q.z;
}

float norm(const Quaternion &q)
{
	return sqrt(quadrance(q));
}

Quaternion normalized(const Quaternion &q)
{
	if (q.t == 0.0f && q.x == 0.0f && q.y == 0.0f && q.z == 0.0f)
	{
		throw std::overflow_error("Normalizing a null vector");
	}
	float s = 1.0f / norm(q);
	return q * s;
}

Quaternion conjugate(const Quaternion &q)
{
	return Quaternion(q.t, -q.x, -q.y, -q.z);
}

Quaternion inverse(const Quaternion &q)
{
	return conjugate(q) * (1.0f / quadrance(q));
}

Quaternion lerp(const Quaternion &q, const Quaternion &qt, float k)
{
	float cos_angle = q.x*qt.x + q.y*qt.y + q.z*qt.z + q.t*qt.t;
	float k1 = (cos_angle > 0) ? k : -k;
	Quaternion resQ = (1 - k) * q + k1 * qt;
	resQ.normalize();

	return resQ;
}

Quaternion slerp(const Quaternion &q, const Quaternion &qt, float k)
{
	float angle = acos(q.x*qt.x + q.y*qt.y + q.z*qt.z + q.t*qt.t);
	float k0 = sin((1 - k)*angle) / sin(angle);
	float k1 = sin(k*angle) / sin(angle);
	Quaternion resQ = k0 * q + k1 * qt;
	resQ.normalize();

	return resQ;
}

Matrix4 toGlMatrix(const Quaternion &q)
{
	Quaternion qt = normalized(q);

	float xx = qt.x * qt.x;
	float xy = qt.x * qt.y;
	float xz = qt.x * qt.z;
	float xt = qt.x * qt.t;
	float yy = qt.y * qt.y;
	float yz = qt.y * qt.z;
	float yt = qt.y * qt.t;
	float zz = qt.z * qt.z;
	float zt = qt.z * qt.t;
	
	return Matrix4(1.0f - 2.0f * (yy + zz), 2.0f * (xy - zt), 2.0f * (xz + yt), 0.0f,
					2.0f * (xy + zt), 1.0f - 2.0f * (xx + zz), 2.0f * (yz - xt), 0.0f,
					2.0f * (xz - yt), 2.0f * (yz + xt), 1.0f - 2.0f * (xx + yy), 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
}

std::ostream &operator << (std::ostream &os, Quaternion &q)
{
	os << "(" << q.t << ", " << q.x << ", " << q.y << ", " << q.z << ")";
	return os;
}

std::istream &operator >> (std::istream &is, Quaternion &q)
{
	is.ignore(1, ' ');
	is >> q.t;
	is.ignore(1, ' ');
	is >> q.x;
	is.ignore(1, ' ');
	is >> q.y;
	is.ignore(1, ' ');
	is >> q.z;
	is.ignore(1, ' ');
	return is;
}

//This function may have some trouble with the quadrant
float radiansToDegrees(const float angle)
{
	return (float) (angle * TURN / PI);
}

float degreesToRadians(const float angle)
{
	return (float) (angle * PI / TURN);
}