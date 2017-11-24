#ifndef __MATRIXTESTS_H__
#define __MATRIXTESTS_H__

#include "catch.hpp"

#include "MathAux.h"
#include <ctime>

////////////////////////////////////////////////////
////											////
////				MATRIX2 TESTS				////
////											////
////////////////////////////////////////////////////

TEST_CASE("Matrix2 struct Tests", "[Matrix2]")
{
	Matrix2 m;

	SECTION("Empty Matrix under test")
	{
		m = Matrix2();

		SECTION("Getters return the right values")
		{
			for(float pos : m.matrix)
			{
				REQUIRE(pos == 0.0f);
			}
		}

		SECTION("Assignments put new values")
		{
			m.matrix[0] = 1.4f;
			m.matrix[1] = 4.4f;
			m.matrix[2] = 5.4f;
			m.matrix[3] = 6.4f;

			REQUIRE(m.matrix[0] == 1.4f);
			REQUIRE(m.matrix[1] == 4.4f);
			REQUIRE(m.matrix[2] == 5.4f);
			REQUIRE(m.matrix[3] == 6.4f);
		}

		SECTION("Minimum value for each component")
		{
			for (int i = 0; i < 4; i++)
			{
				m.matrix[i] = std::numeric_limits<float>::min();
			}
			
			REQUIRE(m.matrix[0] == std::numeric_limits<float>::min());
			REQUIRE(m.matrix[1] == std::numeric_limits<float>::min());
			REQUIRE(m.matrix[2] == std::numeric_limits<float>::min());
			REQUIRE(m.matrix[3] == std::numeric_limits<float>::min());
		}

		SECTION("Maximum value for each component")
		{
			for (int i = 0; i < 4; i++)
			{
				m.matrix[i] = std::numeric_limits<float>::max();
			}

			REQUIRE(m.matrix[0] == std::numeric_limits<float>::max());
			REQUIRE(m.matrix[1] == std::numeric_limits<float>::max());
			REQUIRE(m.matrix[2] == std::numeric_limits<float>::max());
			REQUIRE(m.matrix[3] == std::numeric_limits<float>::max());
		}
	}

	SECTION("Matrix with constant under test:")
	{
		m = Matrix2(1.0f);

		SECTION("Getters return the right values")
		{
			for(float pos : m.matrix)
			{
				REQUIRE(pos == 1.0f);
			}
		}

		SECTION("Result on same Matrix operations")
		{
			float newMatrix[SIZE2X2] = { 2.9f, 3.4f, 5.6f, 67.8f };
			Matrix2 n = Matrix2(newMatrix);
			Vector2 v = Vector2(4.5, 6.5);
			int integerNum = 40;

			SECTION("Sum by a Matrix2")
			{
				m += n;

				REQUIRE(m.matrix[0] == 3.9f);
				REQUIRE(m.matrix[1] == 6.6f);
				REQUIRE(m.matrix[2] == 4.4f);
				REQUIRE(m.matrix[3] == 68.8f);
			}

			SECTION("Subtraction by a Matrix2")
			{
				m -= n;

				REQUIRE(fabs(m.matrix[0] - (-1.9f)) <= EPSILON);
				REQUIRE(m.matrix[1] == -4.6f);
				REQUIRE(m.matrix[2] == -2.4f);
				REQUIRE(m.matrix[3] == -66.8f);
			}

			SECTION("Multiplication by a Matrix2")
			{
				m *= n;

				REQUIRE(m == Matrix2(8.5f, 71.2f, 8.5f, 71.2f));
			}

			SECTION("Multiplication by a int Scalar")
			{
				m *= integerNum;

				for each(float pos in m.matrix)
				{
					REQUIRE(pos == 40.0f);
				}
			}

			SECTION("Division by a int Scalar")
			{
				m /= integerNum;

				for each(float pos in m.matrix)
				{
					REQUIRE(pos == 0.025f);
				}
			}

			SECTION("Clean values")
			{
				m = Matrix2(4.66777676f, 5.67891f, 7.867554f, 8.46453f);
				m.clean();

				REQUIRE_FALSE(m.matrix[0] == 4.66777676f);
				REQUIRE(m.matrix[0] == 4.667f);
				REQUIRE_FALSE(m.matrix[1] == 7.867554f);
				REQUIRE(m.matrix[1] == 7.867f);
				REQUIRE_FALSE(m.matrix[2] == 5.67891f);
				REQUIRE(m.matrix[2] == 5.678f);
				REQUIRE_FALSE(m.matrix[3] == 8.46453f);
				REQUIRE(m.matrix[3] == 8.464f);
			}
		}
	}

	SECTION("Matrix with specific values for each component under test")
	{
		m = Matrix2(3.4f, 5.7f, 8.9f, 1.2f);

		SECTION("Getters return the right values")
		{
			REQUIRE(m.matrix[0] == 3.4f);
			REQUIRE(m.matrix[1] == 8.9f);
			REQUIRE(m.matrix[2] == 5.7f);
			REQUIRE(m.matrix[3] == 1.2f);
		}

		SECTION("Result on new Matrix operations:")
		{
			Matrix2 res;
			Matrix2 n = Matrix2(Vector2(2.6f, 7.8f), Vector2(1.0f));
			float floatingNum = 98.5;
			float floatingRes = 0;

			SECTION("Sum by a Matrix2")
			{
				res = m + n;

				REQUIRE(m.matrix[0] == 3.4f);
				REQUIRE(m.matrix[1] == 8.9f);
				REQUIRE(m.matrix[2] == 5.7f);
				REQUIRE(m.matrix[3] == 1.2f);
				REQUIRE(n.matrix[0] == 2.6f);
				REQUIRE(n.matrix[1] == 1.0f);
				REQUIRE(n.matrix[2] == 7.8f);
				REQUIRE(n.matrix[3] == 1.0f);

				REQUIRE(res == Matrix2(6.0f, 13.5f, 9.9f, 2.2f));
			}

			SECTION("Subtractions by a Matrix2")
			{
				res = m - n;

				REQUIRE(m.matrix[0] == 3.4f);
				REQUIRE(m.matrix[1] == 8.9f);
				REQUIRE(m.matrix[2] == 5.7f);
				REQUIRE(m.matrix[3] == 1.2f);
				REQUIRE(n.matrix[0] == 2.6f);
				REQUIRE(n.matrix[1] == 1.0f);
				REQUIRE(n.matrix[2] == 7.8f);
				REQUIRE(n.matrix[3] == 1.0f);
				REQUIRE(res == Matrix2(0.8f, -2.1f, 7.9f, 0.2f));
			}

			SECTION("Multiplication by a Matrix2")
			{
				res = m * n;

				REQUIRE(m.matrix[0] == 3.4f);
				REQUIRE(m.matrix[1] == 8.9f);
				REQUIRE(m.matrix[2] == 5.7f);
				REQUIRE(m.matrix[3] == 1.2f);
				REQUIRE(n.matrix[0] == 2.6f);
				REQUIRE(n.matrix[1] == 1.0f);
				REQUIRE(n.matrix[2] == 7.8f);
				REQUIRE(n.matrix[3] == 1.0f);

				REQUIRE(res == Matrix2(14.54f, 32.22f, 24.34f, 70.62f));
			}

			SECTION("Multiplication by a float Scalar on the right")
			{
				res = m * floatingNum;

				REQUIRE(m.matrix[0] == 3.4f);
				REQUIRE(m.matrix[1] == 8.9f);
				REQUIRE(m.matrix[2] == 5.7f);
				REQUIRE(m.matrix[3] == 1.2f);
				REQUIRE(res == Matrix2(334.9f, 561.45f, 876.65f, 118.2f));
			}

			SECTION("Multiplication by a float Scalar on the left")
			{
				res = floatingNum * m;

				REQUIRE(m.matrix[0] == 3.4f);
				REQUIRE(m.matrix[1] == 8.9f);
				REQUIRE(m.matrix[2] == 5.7f);
				REQUIRE(m.matrix[3] == 1.2f);
				REQUIRE(res == Matrix2(334.9f, 561.45f, 876.65f, 118.2f));
			}

			SECTION("division by a float Scalar")
			{
				floatingNum = 0.5f;
				res = m / floatingNum;

				REQUIRE(m.matrix[0] == 3.4f);
				REQUIRE(m.matrix[1] == 8.9f);
				REQUIRE(m.matrix[2] == 5.7f);
				REQUIRE(m.matrix[3] == 1.2f);
				REQUIRE(res == Matrix2(6.8f, 11.4f, 17.8f, 2.4f));
			}

			SECTION("Transpose of the Matrix")
			{
				res = transpose(m);

				REQUIRE(m.matrix[0] == 3.4f);
				REQUIRE(m.matrix[1] == 8.9f);
				REQUIRE(m.matrix[2] == 5.7f);
				REQUIRE(m.matrix[3] == 1.2f);
				REQUIRE(res == Matrix2(3.4f, 8.9f, 5.7f, 1.2f));
			}

			SECTION("Inverse of the Matrix")
			{
				m = Matrix2(2.0f, 1.0f, 2.0f, 3.0f);

				res = inverse(m);

				REQUIRE(m.matrix[0] == 2.0f);
				REQUIRE(m.matrix[1] == 2.0f);
				REQUIRE(m.matrix[2] == 1.0f);
				REQUIRE(m.matrix[3] == 3.0f);
				REQUIRE(res == Matrix2(0.75f, -0.25f, -0.5f, 0.5f));
			}

			SECTION("Determinant of the Matrix")
			{
				floatingRes = determinant(m);

				REQUIRE(m.matrix[0] == 3.4f);
				REQUIRE(m.matrix[1] == 8.9f);
				REQUIRE(m.matrix[2] == 5.7f);
				REQUIRE(m.matrix[3] == 1.2f);
				REQUIRE(roundf(floatingRes*100)/100 == -46.65f);
			}
		}
	}

	SECTION("Input and Output streams under test:")
	{
		std::istringstream iss("|1.8, 12.9|\n|4.5, 7.6|");
		std::ostringstream oss;

		iss >> m;
		oss << m;

		REQUIRE(m == Matrix2(1.8f, 12.9f, 4.5f, 7.6f));
		REQUIRE(oss.str() == "|1.8 12.9|\n|4.5 7.6|");
	}
}


////////////////////////////////////////////////////
////											////
////				MATRIX3 TESTS				////
////											////
////////////////////////////////////////////////////

TEST_CASE("Matrix3 struct Tests", "[Matrix3]")
{
	Matrix3 m;

	SECTION("Empty Matrix under test")
	{
		m = Matrix3();

		SECTION("Getters return the right values")
		{
			for each(float pos in m.matrix)
			{
				REQUIRE(pos == 0.0f);
			}
		}

		SECTION("Assignments put new values")
		{
			m.matrix[0] = 1.4f;
			m.matrix[1] = 2.4f;
			m.matrix[2] = 3.4f;
			m.matrix[3] = 4.4f;
			m.matrix[4] = 5.4f;
			m.matrix[5] = 6.4f;
			m.matrix[6] = 7.4f;
			m.matrix[7] = 8.4f;
			m.matrix[8] = 9.4f;

			REQUIRE(m.matrix[0] == 1.4f);
			REQUIRE(m.matrix[1] == 2.4f);
			REQUIRE(m.matrix[2] == 3.4f);
			REQUIRE(m.matrix[3] == 4.4f);
			REQUIRE(m.matrix[4] == 5.4f);
			REQUIRE(m.matrix[5] == 6.4f);
			REQUIRE(m.matrix[6] == 7.4f);
			REQUIRE(m.matrix[7] == 8.4f);
			REQUIRE(m.matrix[8] == 9.4f);
		}

		SECTION("Minimum value for each component")
		{
			for (int i = 0; i < 9; i++)
			{
				m.matrix[i] = std::numeric_limits<float>::min();
			}

			REQUIRE(m.matrix[0] == std::numeric_limits<float>::min());
			REQUIRE(m.matrix[1] == std::numeric_limits<float>::min());
			REQUIRE(m.matrix[2] == std::numeric_limits<float>::min());
			REQUIRE(m.matrix[3] == std::numeric_limits<float>::min());
			REQUIRE(m.matrix[4] == std::numeric_limits<float>::min());
			REQUIRE(m.matrix[5] == std::numeric_limits<float>::min());
			REQUIRE(m.matrix[6] == std::numeric_limits<float>::min());
			REQUIRE(m.matrix[7] == std::numeric_limits<float>::min());
			REQUIRE(m.matrix[8] == std::numeric_limits<float>::min());
		}

		SECTION("Maximum value for each component")
		{
			for (int i = 0; i < 9; i++)
			{
				m.matrix[i] = std::numeric_limits<float>::max();
			}

			REQUIRE(m.matrix[0] == std::numeric_limits<float>::max());
			REQUIRE(m.matrix[1] == std::numeric_limits<float>::max());
			REQUIRE(m.matrix[2] == std::numeric_limits<float>::max());
			REQUIRE(m.matrix[3] == std::numeric_limits<float>::max());
			REQUIRE(m.matrix[4] == std::numeric_limits<float>::max());
			REQUIRE(m.matrix[5] == std::numeric_limits<float>::max());
			REQUIRE(m.matrix[6] == std::numeric_limits<float>::max());
			REQUIRE(m.matrix[7] == std::numeric_limits<float>::max());
			REQUIRE(m.matrix[8] == std::numeric_limits<float>::max());
		}
	}

	SECTION("Matrix with constant under test:")
	{
		m = Matrix3(1.0f);

		SECTION("Getters return the right values")
		{
			for each(float pos in m.matrix)
			{
				REQUIRE(pos == 1.0f);
			}
		}

		SECTION("Result on same Matrix operations")
		{
			float newMatrix[SIZE3X3] = { 2.9f, 3.4f, 5.6f,
										67.8f, 1.8f, 4.6f,
										18.7f, 6.4f, 9.2f};
			Matrix3 n = Matrix3(newMatrix);
			Vector3 v = Vector3(4.5, 6.5, 5.0f);
			int integerNum = 40;

			SECTION("Sum by a Matrix3")
			{
				m += n;

				REQUIRE(m.matrix[0] == 3.9f);
				REQUIRE(m.matrix[1] == 68.8f);
				REQUIRE(m.matrix[2] == 19.7f);
				REQUIRE(m.matrix[3] == 4.4f);
				REQUIRE(m.matrix[4] == 2.8f);
				REQUIRE(m.matrix[5] == 7.4f);
				REQUIRE(m.matrix[6] == 6.6f);
				REQUIRE(m.matrix[7] == 5.6f);
				REQUIRE(m.matrix[8] == 10.2f);
			}

			SECTION("Subtraction by a Matrix3")
			{
				m -= n;

				REQUIRE(fabs(m.matrix[0] - (-1.9f)) <= EPSILON);
				REQUIRE(m.matrix[1] == -66.8f);
				REQUIRE(m.matrix[2] == -17.7f);
				REQUIRE(m.matrix[3] == -2.4f);
				REQUIRE(fabs(m.matrix[4] - (-0.8f)) <= EPSILON);
				REQUIRE(m.matrix[5] == -5.4f);
				REQUIRE(m.matrix[6] == -4.6f);
				REQUIRE(m.matrix[7] == -3.6f);
				REQUIRE(m.matrix[8] == -8.2f);
			}

			SECTION("Multiplication by a Matrix3")
			{
				m *= n;

				REQUIRE(m == Matrix3(89.4f, 11.6f, 19.4f, 89.4f, 11.6f, 19.4f, 89.4f, 11.6f, 19.4f));
			}

			SECTION("Multiplication by a int Scalar")
			{
				m *= integerNum;

				for each(float pos in m.matrix)
				{
					REQUIRE(pos == 40.0f);
				}
			}

			SECTION("Division by a int Scalar")
			{
				m /= integerNum;

				for each(float pos in m.matrix)
				{
					REQUIRE(pos == 0.025f);
				}
			}

			SECTION("Clean values")
			{
				m = Matrix3(4.66777676f, 8.46453f, 1.0f,
							5.67891f, 10.0f, 1.0f,
							7.867554f, 1.0f, 1.0f);
				m.clean();

				REQUIRE_FALSE(m.matrix[0] == 4.66777676f);
				REQUIRE(m.matrix[0] == 4.667f);
				REQUIRE_FALSE(m.matrix[1] == 5.67891f);
				REQUIRE(m.matrix[1] == 5.678f);
				REQUIRE_FALSE(m.matrix[2] == 7.867554f);
				REQUIRE(m.matrix[2] == 7.867f);
				REQUIRE_FALSE(m.matrix[3] == 8.46453f);
				REQUIRE(m.matrix[3] == 8.464f);
			}
		}
	}

	SECTION("Matrix with specific values for each component under test")
	{
		m = Matrix3(3.4f, 5.7f, 8.9f,
					1.2f, 1.0f, 1.0f,
					1.0f, 1.0f, 1.0f);

		SECTION("Getters return the right values")
		{
			REQUIRE(m.matrix[0] == 3.4f);
			REQUIRE(m.matrix[1] == 1.2f);
			REQUIRE(m.matrix[2] == 1.0f);
			REQUIRE(m.matrix[3] == 5.7f);
			REQUIRE(m.matrix[4] == 1.0f);
			REQUIRE(m.matrix[5] == 1.0f);
			REQUIRE(m.matrix[6] == 8.9f);
			REQUIRE(m.matrix[7] == 1.0f);
			REQUIRE(m.matrix[8] == 1.0f);
		}

		SECTION("Result on new Matrix operations:")
		{
			Matrix3 n = Matrix3(Vector3(1.0f), Vector3(1.0f), Vector3(1.0f));
			Matrix3 res;
			float floatingNum = 0.5;
			float floatingRes = 0;

			SECTION("Sum by a Matrix3")
			{
				res = m + n;

				REQUIRE(m.matrix[0] == 3.4f);
				REQUIRE(m.matrix[1] == 1.2f);
				REQUIRE(m.matrix[2] == 1.0f);
				REQUIRE(m.matrix[3] == 5.7f);
				REQUIRE(m.matrix[4] == 1.0f);
				REQUIRE(m.matrix[5] == 1.0f);
				REQUIRE(m.matrix[6] == 8.9f);
				REQUIRE(m.matrix[7] == 1.0f);
				REQUIRE(m.matrix[8] == 1.0f);
				for each(float pos in n.matrix)
				{
					REQUIRE(pos == 1.0f);
				}
				REQUIRE(res == Matrix3(4.4f, 6.7f, 9.9f, 2.2f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f));
			}

			SECTION("Subtractions by a Matrix3")
			{
				res = m - n;

				REQUIRE(m.matrix[0] == 3.4f);
				REQUIRE(m.matrix[1] == 1.2f);
				REQUIRE(m.matrix[2] == 1.0f);
				REQUIRE(m.matrix[3] == 5.7f);
				REQUIRE(m.matrix[4] == 1.0f);
				REQUIRE(m.matrix[5] == 1.0f);
				REQUIRE(m.matrix[6] == 8.9f);
				REQUIRE(m.matrix[7] == 1.0f);
				REQUIRE(m.matrix[8] == 1.0f);
				for each(float pos in n.matrix)
				{
					REQUIRE(pos == 1.0f);
				}
				REQUIRE(res == Matrix3(2.4f, 4.7f, 7.9f, 0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f));
			}

			SECTION("Multiplication by a Matrix3")
			{
				res = m * n;

				REQUIRE(m.matrix[0] == 3.4f);
				REQUIRE(m.matrix[1] == 1.2f);
				REQUIRE(m.matrix[2] == 1.0f);
				REQUIRE(m.matrix[3] == 5.7f);
				REQUIRE(m.matrix[4] == 1.0f);
				REQUIRE(m.matrix[5] == 1.0f);
				REQUIRE(m.matrix[6] == 8.9f);
				REQUIRE(m.matrix[7] == 1.0f);
				REQUIRE(m.matrix[8] == 1.0f);
				for each(float pos in n.matrix)
				{
					REQUIRE(pos == 1.0f);
				}
				REQUIRE(res == Matrix3(18.0f, 18.0f, 18.0f, 3.2f, 3.2f, 3.2f, 3.0f, 3.0f, 3.0f));
			}

			SECTION("Multiplication by a float Scalar on the right")
			{
				res = m * floatingNum;

				REQUIRE(m.matrix[0] == 3.4f);
				REQUIRE(m.matrix[1] == 1.2f);
				REQUIRE(m.matrix[2] == 1.0f);
				REQUIRE(m.matrix[3] == 5.7f);
				REQUIRE(m.matrix[4] == 1.0f);
				REQUIRE(m.matrix[5] == 1.0f);
				REQUIRE(m.matrix[6] == 8.9f);
				REQUIRE(m.matrix[7] == 1.0f);
				REQUIRE(m.matrix[8] == 1.0f);
				REQUIRE(res == Matrix3(1.7f, 2.85f, 4.45f, 0.6f, 0.5f, 0.5f, 0.5f, 0.5, 0.5f));
			}

			SECTION("Multiplication by a float Scalar on the left")
			{
				res = floatingNum * m;

				REQUIRE(m.matrix[0] == 3.4f);
				REQUIRE(m.matrix[1] == 1.2f);
				REQUIRE(m.matrix[2] == 1.0f);
				REQUIRE(m.matrix[3] == 5.7f);
				REQUIRE(m.matrix[4] == 1.0f);
				REQUIRE(m.matrix[5] == 1.0f);
				REQUIRE(m.matrix[6] == 8.9f);
				REQUIRE(m.matrix[7] == 1.0f);
				REQUIRE(m.matrix[8] == 1.0f);
				REQUIRE(res == Matrix3(1.7f, 2.85f, 4.45f, 0.6f, 0.5f, 0.5f, 0.5f, 0.5, 0.5f));
			}

			SECTION("division by a float Scalar")
			{
				floatingNum = 0.5f;
				res = m / floatingNum;

				REQUIRE(m.matrix[0] == 3.4f);
				REQUIRE(m.matrix[1] == 1.2f);
				REQUIRE(m.matrix[2] == 1.0f);
				REQUIRE(m.matrix[3] == 5.7f);
				REQUIRE(m.matrix[4] == 1.0f);
				REQUIRE(m.matrix[5] == 1.0f);
				REQUIRE(m.matrix[6] == 8.9f);
				REQUIRE(m.matrix[7] == 1.0f);
				REQUIRE(m.matrix[8] == 1.0f);
				REQUIRE(res == Matrix3(6.8f, 11.4f, 17.8f, 2.4f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f));
			}

			SECTION("Transpose of the Matrix")
			{
				res = transpose(m);

				REQUIRE(m.matrix[0] == 3.4f);
				REQUIRE(m.matrix[1] == 1.2f);
				REQUIRE(m.matrix[2] == 1.0f);
				REQUIRE(m.matrix[3] == 5.7f);
				REQUIRE(m.matrix[4] == 1.0f);
				REQUIRE(m.matrix[5] == 1.0f);
				REQUIRE(m.matrix[6] == 8.9f);
				REQUIRE(m.matrix[7] == 1.0f);
				REQUIRE(m.matrix[8] == 1.0f);
				REQUIRE(res == Matrix3(3.4f, 1.2f, 1.0f, 5.7f, 1.0f, 1.0f, 8.9f, 1.0f, 1.0f));
			}

			SECTION("Inverse of the Matrix")
			{
				res = inverse(m);

				REQUIRE(m.matrix[0] == 3.4f);
				REQUIRE(m.matrix[1] == 1.2f);
				REQUIRE(m.matrix[2] == 1.0f);
				REQUIRE(m.matrix[3] == 5.7f);
				REQUIRE(m.matrix[4] == 1.0f);
				REQUIRE(m.matrix[5] == 1.0f);
				REQUIRE(m.matrix[6] == 8.9f);
				REQUIRE(m.matrix[7] == 1.0f);
				REQUIRE(m.matrix[8] == 1.0f);

				REQUIRE(res == Matrix3(0.0f, 5.0f, -5.0f,
										-0.3125f, -8.59375f, 11.375f,
										0.3125f, 3.59375f, -5.375f));
			}

			SECTION("Determinant of the Matrix")
			{
				floatingRes = determinant(m);

				REQUIRE(m.matrix[0] == 3.4f);
				REQUIRE(m.matrix[1] == 1.2f);
				REQUIRE(m.matrix[2] == 1.0f);
				REQUIRE(m.matrix[3] == 5.7f);
				REQUIRE(m.matrix[4] == 1.0f);
				REQUIRE(m.matrix[5] == 1.0f);
				REQUIRE(m.matrix[6] == 8.9f);
				REQUIRE(m.matrix[7] == 1.0f);
				REQUIRE(m.matrix[8] == 1.0f);
				REQUIRE(fabs(floatingRes - 0.64f) <= EPSILON);
			}
		}
	}

	SECTION("Input and Output streams under test:")
	{
		std::istringstream iss("|1.8 12.9 5|\n|4.5 7.6 8.1|\n|3.2 5.6 7.9|");
		std::ostringstream oss;

		iss >> m;
		oss << m;

		REQUIRE(m == Matrix3(1.8f, 12.9f, 5.0f, 4.5f, 7.6f, 8.1f, 3.2f, 5.6f, 7.9f));
		REQUIRE(oss.str() == "|1.8 12.9 5|\n|4.5 7.6 8.1|\n|3.2 5.6 7.9|");
	}
}


////////////////////////////////////////////////////
////											////
////				MATRIX4 TESTS				////
////											////
////////////////////////////////////////////////////

TEST_CASE("Matrix4 struct Tests", "[Matrix4]")
{
	Matrix4 m;

	SECTION("Empty Matrix under test")
	{
		m = Matrix4();

		SECTION("Getters return the right values")
		{
			for each(float pos in m.matrix)
			{
				REQUIRE(pos == 0.0f);
			}
		}

		SECTION("Assignments put new values")
		{
			m.matrix[0] = 1.4f;
			m.matrix[1] = 2.4f;
			m.matrix[2] = 3.4f;
			m.matrix[3] = 4.4f;
			m.matrix[4] = 5.4f;
			m.matrix[5] = 6.4f;
			m.matrix[6] = 7.4f;
			m.matrix[7] = 8.4f;
			m.matrix[8] = 9.4f;

			REQUIRE(m.matrix[0] == 1.4f);
			REQUIRE(m.matrix[1] == 2.4f);
			REQUIRE(m.matrix[2] == 3.4f);
			REQUIRE(m.matrix[3] == 4.4f);
			REQUIRE(m.matrix[4] == 5.4f);
			REQUIRE(m.matrix[5] == 6.4f);
			REQUIRE(m.matrix[6] == 7.4f);
			REQUIRE(m.matrix[7] == 8.4f);
			REQUIRE(m.matrix[8] == 9.4f);
		}

		SECTION("Minimum value for each component")
		{
			for (int i = 0; i < 16; i++)
			{
				m.matrix[i] = std::numeric_limits<float>::min();

				REQUIRE(m.matrix[i] == std::numeric_limits<float>::min());
			}
		}

		SECTION("Maximum value for each component")
		{
			for (int i = 0; i < 16; i++)
			{
				m.matrix[i] = std::numeric_limits<float>::max();

				REQUIRE(m.matrix[i] == std::numeric_limits<float>::max());
			}
		}
	}

	SECTION("Matrix with constant under test:")
	{
		m = Matrix4(1.0f);

		SECTION("Getters return the right values")
		{
			for each(float pos in m.matrix)
			{
				REQUIRE(pos == 1.0f);
			}
		}

		SECTION("Result on same Matrix operations")
		{
			float newMatrix[SIZE4X4] = { 2.0f, 3.0f, 5.0f, 0.0f,
										6.0f, 1.0f, 4.0f, 0.0f,
										8.0f, 6.0f, 9.0f, 0.0f,
										9.5f, 2.0f, 3.0f, 1.0f};
			Matrix4 n = Matrix4(newMatrix);
			Vector4 v = Vector4(4.5, 6.5, 5.0f, 0.0f);
			int integerNum = 40;

			SECTION("Sum by a Matrix4")
			{
				m += n;

				REQUIRE(m.matrix[0] == 3.0f);
				REQUIRE(m.matrix[1] == 7.0f);
				REQUIRE(m.matrix[2] == 9.0f);
				REQUIRE(m.matrix[3] == 10.5f);
				REQUIRE(m.matrix[4] == 4.0f);
				REQUIRE(m.matrix[5] == 2.0f);
				REQUIRE(m.matrix[6] == 7.0f);
				REQUIRE(m.matrix[7] == 3.0f);
				REQUIRE(m.matrix[8] == 6.0f);
				REQUIRE(m.matrix[9] == 5.0f);
				REQUIRE(m.matrix[10] == 10.0f);
				REQUIRE(m.matrix[11] == 4.0f);
				REQUIRE(m.matrix[12] == 1.0f);
				REQUIRE(m.matrix[13] == 1.0f);
				REQUIRE(m.matrix[14] == 1.0f);
				REQUIRE(m.matrix[15] == 2.0f);
			}

			SECTION("Subtraction by a Matrix4")
			{
				m -= n;

				REQUIRE(m.matrix[0] == -1.0f);
				REQUIRE(m.matrix[4] == -2.0f);
				REQUIRE(m.matrix[8] == -4.0f);
				REQUIRE(m.matrix[12] == 1.0f);
				REQUIRE(m.matrix[1] == -5.0f);
				REQUIRE(m.matrix[5] == 0.0f);
				REQUIRE(m.matrix[9] == -3.0f);
				REQUIRE(m.matrix[13] == 1.0f);
				REQUIRE(m.matrix[2] == -7.0f);
				REQUIRE(m.matrix[6] == -5.0f);
				REQUIRE(m.matrix[10] == -8.0f);
				REQUIRE(m.matrix[14] == 1.0f);
				REQUIRE(m.matrix[3] == -8.5f);
				REQUIRE(m.matrix[7] == -1.0f);
				REQUIRE(m.matrix[11] == -2.0f);
				REQUIRE(m.matrix[15] == 0.0f);
			}

			SECTION("Multiplication by a Matrix4")
			{
				m *= n;

				REQUIRE(m == Matrix4(25.5f, 12.0f, 21.0f, 1.0f,
									25.5f, 12.0f, 21.0f, 1.0f,
									25.5f, 12.0f, 21.0f, 1.0f,
									25.5f, 12.0f, 21.0f, 1.0f));
			}

			SECTION("Multiplication by a int Scalar")
			{
				m *= integerNum;

				for each(float pos in m.matrix)
				{
					REQUIRE(pos == 40.0f);
				}
			}

			SECTION("Division by a int Scalar")
			{
				m /= integerNum;

				for each(float pos in m.matrix)
				{
					REQUIRE(pos == 0.025f);
				}
			}

			SECTION("Clean values")
			{
				m = Matrix4(4.66777676f, 5.67891f, 7.867554f, 8.46453f,
							10.0f, 1.0f, 1.0f, 1.0f,
							1.0f, 1.0f, 1.0f, 1.0f,
							0.0f, 0.0f, 0.0f, 0.0f);
				m.clean();

				REQUIRE_FALSE(m.matrix[0] == 4.66777676f);
				REQUIRE(m.matrix[0] == 4.667f);
				REQUIRE_FALSE(m.matrix[4] == 5.67891f);
				REQUIRE(m.matrix[4] == 5.678f);
				REQUIRE_FALSE(m.matrix[8] == 7.867554f);
				REQUIRE(m.matrix[8] == 7.867f);
				REQUIRE_FALSE(m.matrix[12] == 8.46453f);
				REQUIRE(m.matrix[12] == 8.464f);
			}
		}
	}

	SECTION("Matrix with specific values for each component under test")
	{
		m = Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);

		SECTION("Getters return the right values")
		{
			REQUIRE(m.matrix[0] == 1.0f);
			REQUIRE(m.matrix[1] == 0.0f);
			REQUIRE(m.matrix[2] == 0.0f);
			REQUIRE(m.matrix[3] == 0.0f);
			REQUIRE(m.matrix[4] == 0.0f);
			REQUIRE(m.matrix[5] == 1.0f);
			REQUIRE(m.matrix[6] == 0.0f);
			REQUIRE(m.matrix[7] == 0.0f);
			REQUIRE(m.matrix[8] == 0.0f);
			REQUIRE(m.matrix[9] == 0.0f);
			REQUIRE(m.matrix[10] == 1.0f);
			REQUIRE(m.matrix[11] == 0.0f);
			REQUIRE(m.matrix[12] == 0.0f);
			REQUIRE(m.matrix[13] == 0.0f);
			REQUIRE(m.matrix[14] == 0.0f);
			REQUIRE(m.matrix[15] == 1.0f);
		}

		SECTION("Result on new Matrix operations:")
		{
			Matrix4 n = Matrix4(Vector4(1.0f), Vector4(1.0f), Vector4(1.0f), Vector4(1.0f));
			Matrix4 res;
			float floatingNum = 0.5;
			float floatingRes = 0;

			SECTION("Sum by a Matrix4")
			{
				res = m + n;

				REQUIRE(m.matrix[0] == 1.0f);
				REQUIRE(m.matrix[1] == 0.0f);
				REQUIRE(m.matrix[2] == 0.0f);
				REQUIRE(m.matrix[3] == 0.0f);
				REQUIRE(m.matrix[4] == 0.0f);
				REQUIRE(m.matrix[5] == 1.0f);
				REQUIRE(m.matrix[6] == 0.0f);
				REQUIRE(m.matrix[7] == 0.0f);
				REQUIRE(m.matrix[8] == 0.0f);
				REQUIRE(m.matrix[9] == 0.0f);
				REQUIRE(m.matrix[10] == 1.0f);
				REQUIRE(m.matrix[11] == 0.0f);
				REQUIRE(m.matrix[12] == 0.0f);
				REQUIRE(m.matrix[13] == 0.0f);
				REQUIRE(m.matrix[14] == 0.0f);
				REQUIRE(m.matrix[15] == 1.0f);
				for each(float pos in n.matrix)
				{
					REQUIRE(pos == 1.0f);
				}
				REQUIRE(res == Matrix4(2.0f, 1.0f, 1.0f, 1.0f,
										1.0f, 2.0f, 1.0f, 1.0f,
										1.0f, 1.0f, 2.0f, 1.0f,
										1.0f, 1.0f, 1.0f, 2.0f));
			}

			SECTION("Subtractions by a Matrix4")
			{
				res = m - n;

				REQUIRE(m.matrix[0] == 1.0f);
				REQUIRE(m.matrix[1] == 0.0f);
				REQUIRE(m.matrix[2] == 0.0f);
				REQUIRE(m.matrix[3] == 0.0f);
				REQUIRE(m.matrix[4] == 0.0f);
				REQUIRE(m.matrix[5] == 1.0f);
				REQUIRE(m.matrix[6] == 0.0f);
				REQUIRE(m.matrix[7] == 0.0f);
				REQUIRE(m.matrix[8] == 0.0f);
				REQUIRE(m.matrix[9] == 0.0f);
				REQUIRE(m.matrix[10] == 1.0f);
				REQUIRE(m.matrix[11] == 0.0f);
				REQUIRE(m.matrix[12] == 0.0f);
				REQUIRE(m.matrix[13] == 0.0f);
				REQUIRE(m.matrix[14] == 0.0f);
				REQUIRE(m.matrix[15] == 1.0f);
				for each(float pos in n.matrix)
				{
					REQUIRE(pos == 1.0f);
				}
				REQUIRE(res == Matrix4(0.0f, -1.0f, -1.0f, -1.0f,
										-1.0f, 0.0f, -1.0f, -1.0f,
										-1.0f, -1.0f, 0.0f, -1.0f,
										-1.0f, -1.0f, -1.0f, 0.0f));
			}

			SECTION("Multiplication by a Matrix4")
			{
				res = m * n;

				REQUIRE(m.matrix[0] == 1.0f);
				REQUIRE(m.matrix[1] == 0.0f);
				REQUIRE(m.matrix[2] == 0.0f);
				REQUIRE(m.matrix[3] == 0.0f);
				REQUIRE(m.matrix[4] == 0.0f);
				REQUIRE(m.matrix[5] == 1.0f);
				REQUIRE(m.matrix[6] == 0.0f);
				REQUIRE(m.matrix[7] == 0.0f);
				REQUIRE(m.matrix[8] == 0.0f);
				REQUIRE(m.matrix[9] == 0.0f);
				REQUIRE(m.matrix[10] == 1.0f);
				REQUIRE(m.matrix[11] == 0.0f);
				REQUIRE(m.matrix[12] == 0.0f);
				REQUIRE(m.matrix[13] == 0.0f);
				REQUIRE(m.matrix[14] == 0.0f);
				REQUIRE(m.matrix[15] == 1.0f);
				for each(float pos in n.matrix)
				{
					REQUIRE(pos == 1.0f);
				}
				REQUIRE(res == n);
			}

			SECTION("Multiplication by a float Scalar on the right")
			{
				res = m * floatingNum;

				REQUIRE(m.matrix[0] == 1.0f);
				REQUIRE(m.matrix[1] == 0.0f);
				REQUIRE(m.matrix[2] == 0.0f);
				REQUIRE(m.matrix[3] == 0.0f);
				REQUIRE(m.matrix[4] == 0.0f);
				REQUIRE(m.matrix[5] == 1.0f);
				REQUIRE(m.matrix[6] == 0.0f);
				REQUIRE(m.matrix[7] == 0.0f);
				REQUIRE(m.matrix[8] == 0.0f);
				REQUIRE(m.matrix[9] == 0.0f);
				REQUIRE(m.matrix[10] == 1.0f);
				REQUIRE(m.matrix[11] == 0.0f);
				REQUIRE(m.matrix[12] == 0.0f);
				REQUIRE(m.matrix[13] == 0.0f);
				REQUIRE(m.matrix[14] == 0.0f);
				REQUIRE(m.matrix[15] == 1.0f);
				REQUIRE(res == Matrix4(0.5f, 0.0f, 0.0f, 0.0f,
										0.0f, 0.5f, 0.0f, 0.0f,
										0.0f, 0.0f, 0.5f, 0.0f,
										0.0f, 0.0f, 0.0f, 0.5f));
			}

			SECTION("Multiplication by a float Scalar on the left")
			{
				res = floatingNum * m;

				REQUIRE(m.matrix[0] == 1.0f);
				REQUIRE(m.matrix[1] == 0.0f);
				REQUIRE(m.matrix[2] == 0.0f);
				REQUIRE(m.matrix[3] == 0.0f);
				REQUIRE(m.matrix[4] == 0.0f);
				REQUIRE(m.matrix[5] == 1.0f);
				REQUIRE(m.matrix[6] == 0.0f);
				REQUIRE(m.matrix[7] == 0.0f);
				REQUIRE(m.matrix[8] == 0.0f);
				REQUIRE(m.matrix[9] == 0.0f);
				REQUIRE(m.matrix[10] == 1.0f);
				REQUIRE(m.matrix[11] == 0.0f);
				REQUIRE(m.matrix[12] == 0.0f);
				REQUIRE(m.matrix[13] == 0.0f);
				REQUIRE(m.matrix[14] == 0.0f);
				REQUIRE(m.matrix[15] == 1.0f);
				REQUIRE(res == Matrix4(0.5f, 0.0f, 0.0f, 0.0f,
										0.0f, 0.5f, 0.0f, 0.0f,
										0.0f, 0.0f, 0.5f, 0.0f,
										0.0f, 0.0f, 0.0f, 0.5f));
			}

			SECTION("division by a float Scalar")
			{
				res = m / floatingNum;

				REQUIRE(m.matrix[0] == 1.0f);
				REQUIRE(m.matrix[1] == 0.0f);
				REQUIRE(m.matrix[2] == 0.0f);
				REQUIRE(m.matrix[3] == 0.0f);
				REQUIRE(m.matrix[4] == 0.0f);
				REQUIRE(m.matrix[5] == 1.0f);
				REQUIRE(m.matrix[6] == 0.0f);
				REQUIRE(m.matrix[7] == 0.0f);
				REQUIRE(m.matrix[8] == 0.0f);
				REQUIRE(m.matrix[9] == 0.0f);
				REQUIRE(m.matrix[10] == 1.0f);
				REQUIRE(m.matrix[11] == 0.0f);
				REQUIRE(m.matrix[12] == 0.0f);
				REQUIRE(m.matrix[13] == 0.0f);
				REQUIRE(m.matrix[14] == 0.0f);
				REQUIRE(m.matrix[15] == 1.0f);
				REQUIRE(res == Matrix4(2.0f, 0.0f, 0.0f, 0.0f,
										0.0f, 2.0f, 0.0f, 0.0f,
										0.0f, 0.0f, 2.0f, 0.0f,
										0.0f, 0.0f, 0.0f, 2.0f));
			}

			SECTION("Transpose of the Matrix")
			{
				res = transpose(m);

				REQUIRE(m.matrix[0] == 1.0f);
				REQUIRE(m.matrix[1] == 0.0f);
				REQUIRE(m.matrix[2] == 0.0f);
				REQUIRE(m.matrix[3] == 0.0f);
				REQUIRE(m.matrix[4] == 0.0f);
				REQUIRE(m.matrix[5] == 1.0f);
				REQUIRE(m.matrix[6] == 0.0f);
				REQUIRE(m.matrix[7] == 0.0f);
				REQUIRE(m.matrix[8] == 0.0f);
				REQUIRE(m.matrix[9] == 0.0f);
				REQUIRE(m.matrix[10] == 1.0f);
				REQUIRE(m.matrix[11] == 0.0f);
				REQUIRE(m.matrix[12] == 0.0f);
				REQUIRE(m.matrix[13] == 0.0f);
				REQUIRE(m.matrix[14] == 0.0f);
				REQUIRE(m.matrix[15] == 1.0f);
				REQUIRE(res == m);
			}

			//Not implemented
			//SECTION("Inverse of the Matrix")
			//{
			//	/*m = Matrix4(2.0f, 1.0f, 2.0f, 3.0f);

			//	res = inverse(m);

			//	REQUIRE(m.matrix[0] == 2.0f);
			//	REQUIRE(m.matrix[1] == 1.0f);
			//	REQUIRE(m.matrix[2] == 2.0f);
			//	REQUIRE(m.matrix[3] == 3.0f);
			//	REQUIRE(res == Matrix4(0.75f, -0.25f, -0.5f, 0.5f));*/
			//}

			SECTION("Determinant of the Matrix")
			{
				floatingRes = determinant(m);

				REQUIRE(m.matrix[0] == 1.0f);
				REQUIRE(m.matrix[1] == 0.0f);
				REQUIRE(m.matrix[2] == 0.0f);
				REQUIRE(m.matrix[3] == 0.0f);
				REQUIRE(m.matrix[4] == 0.0f);
				REQUIRE(m.matrix[5] == 1.0f);
				REQUIRE(m.matrix[6] == 0.0f);
				REQUIRE(m.matrix[7] == 0.0f);
				REQUIRE(m.matrix[8] == 0.0f);
				REQUIRE(m.matrix[9] == 0.0f);
				REQUIRE(m.matrix[10] == 1.0f);
				REQUIRE(m.matrix[11] == 0.0f);
				REQUIRE(m.matrix[12] == 0.0f);
				REQUIRE(m.matrix[13] == 0.0f);
				REQUIRE(m.matrix[14] == 0.0f);
				REQUIRE(m.matrix[15] == 1.0f);
				REQUIRE(floatingRes == 1.0f);
			}
		}
	}

	SECTION("Input and Output streams under test:")
	{
		std::istringstream iss("|1.8 12.9 5 0.0|\n|4.5 7.6 8.1 0.0|\n|3.2 5.6 7.9 0.0|\n|0.0 0.0 0.0 1.0|");
		std::ostringstream oss;

		iss >> m;
		oss << m;

		REQUIRE(m == Matrix4(1.8f, 12.9f, 5.0f, 0.0f,
							4.5f, 7.6f, 8.1f, 0.0f,
							3.2f, 5.6f, 7.9f, 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f));
		REQUIRE(oss.str() == "|1.8 12.9 5 0|\n|4.5 7.6 8.1 0|\n|3.2 5.6 7.9 0|\n|0 0 0 1|");
	}
}


////////////////////////////////////////////////////
////											////
////			MATRIX FACTORY TESTS			////
////											////
////////////////////////////////////////////////////

TEST_CASE("Matrix Factory Funtions Tests")
{
	MatrixFactory mf;
	Vector3 v = Vector3(1.0f, 0.0f, 0.0f);

	SECTION("Identity Matrix")
	{
		SECTION("2X2")
		{
			REQUIRE(mf.identity2() ==  Matrix2(1.0f, 0.0f, 0.0f, 1.0f));
		}

		SECTION("3X3")
		{
			REQUIRE(mf.identity3() == Matrix3(1.0f, 0.0f, 0.0f,
											0.0f, 1.0f, 0.0f,
											0.0f, 0.0f, 1.0f));
		}

		SECTION("4X4")
		{
			REQUIRE(mf.identity4() == Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
											0.0f, 1.0f, 0.0f, 0.0f,
											0.0f, 0.0f, 1.0f, 0.0f,
											0.0f, 0.0f, 0.0f, 1.0f));
		}
	}

	SECTION("Dual Matrix")
	{
		REQUIRE(mf.dual(v) == Matrix3(0.0f, -v.z, v.y,
									v.z, 0.0f, -v.x,
									-v.y, v.x, 0.0f));
	}

	SECTION("Rotation Matrix")
	{
		float angle = 90.0f;

		SECTION("2X2")
		{
			REQUIRE(mf.rotation(angle) == Matrix2(0.0f, -1.0f, 1.0f, 0.0f));
		}

		SECTION("3X3")
		{
			REQUIRE(mf.rotation(v, angle) == Matrix3(1.0f, 0.0f, 0.0f,
													0.0f, 0.0f, -1.0f,
													0.0f, 1.0f, 0.0f));
		}

		SECTION("4X4")
		{
			Vector4 u = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
			angle = 180.0f;
			REQUIRE(mf.rotation(u, angle) == Matrix4(-1.0f, 0.0f, 0.0f, 0.0f,
													0.0f, 1.0f, 0.0f, 0.0f,
													0.0f, 0.0f, -1.0f, 0.0f,
													0.0f, 0.0f, 0.0f, 1.0f));
		}
	}

	SECTION("Scale Matrix")
	{
		float x = 1.0f, y = 0.5f, z = 2.0f, w = 0.0f;
		SECTION("2X2")
		{
			REQUIRE(mf.scale(x, y) == Matrix2(1.0f, 0.0f, 0.0f, 0.5f));
		}

		SECTION("3X3")
		{
			REQUIRE(mf.scale(x, y, z) == Matrix3(1.0f, 0.0f, 0.0f,
												0.0f, 0.5f, 0.0f,
												0.0f, 0.0f, 2.0f));
		}

		SECTION("4X4")
		{
			REQUIRE(mf.scale(x, y, z, w) == Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
												0.0f, 0.5f, 0.0f, 0.0f,
												0.0f, 0.0f, 2.0f, 0.0f,
												0.0f, 0.0f, 0.0f, 1.0f));
		}
	}

	SECTION("Shear Matrix")
	{
		float a = 0.5;
		SECTION("2X2")
		{
			REQUIRE(mf.shear2x(a) == Matrix2(1.0f, 0.0f, 0.5f, 1.0f));
			REQUIRE(mf.shear2y(a) == Matrix2(1.0f, 0.5f, 0.0f, 1.0f));
		}

		SECTION("3X3")
		{
			REQUIRE(mf.shear3x(a) == Matrix3(1.0f, 0.5f, 0.5f,
											0.0f, 1.0f, 0.0f,
											0.0f, 0.0f, 1.0f));
			REQUIRE(mf.shear3y(a) == Matrix3(1.0f, 0.0f, 0.0f,
											0.5f, 1.0f, 0.5f,
											0.0f, 0.0f, 1.0f));
			REQUIRE(mf.shear3z(a) == Matrix3(1.0f, 0.0f, 0.0f,
											0.0f, 1.0f, 0.0f,
											0.5f, 0.5f, 1.0f));
		}

		SECTION("4X4")
		{
			REQUIRE(mf.shear4x(a) == Matrix4(1.0f, 0.5f, 0.5f, 0.0f,
											0.0f, 1.0f, 0.0f, 0.0f,
											0.0f, 0.0f, 1.0f, 0.0f,
											0.0f, 0.0f, 0.0f, 1.0f));
			REQUIRE(mf.shear4y(a) == Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
											0.5f, 1.0f, 0.5f, 0.0f,
											0.0f, 0.0f, 1.0f, 0.0f,
											0.0f, 0.0f, 0.0f, 1.0f));
			REQUIRE(mf.shear4z(a) == Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
											0.0f, 1.0f, 0.0f, 0.0f,
											0.5f, 0.5f, 1.0f, 0.0f,
											0.0f, 0.0f, 0.0f, 1.0f));
		}
	}

	SECTION("Tranlation Matrix")
	{
		v = Vector3(2.5f, 1.0f, 0.0f);
		float x = 1.0f, y = 0.5f, z = 2.0f;
		//This function doesn't make sense for now, investigate further
		//SECTION("2X2")
		//{
		//	REQUIRE(translation() == Matrix2(1.0f, 0.0f, 1.0f, 0.0f));
		//}

		//SECTION("3X3")
		//{
		//	REQUIRE(translation() == Matrix3(1.0f, 0.0f, 0.0f,
		//		0.0f, 1.0f, 0.0f,
		//		0.0f, 0.0f, 1.0f));
		//}

		SECTION("4X4")
		{
			REQUIRE(mf.translation(v) == Matrix4(1.0f, 0.0f, 0.0f, 2.5f,
												0.0f, 1.0f, 0.0f, 1.0f,
												0.0f, 0.0f, 1.0f, 0.0f,
												0.0f, 0.0f, 0.0f, 1.0f));
			REQUIRE(mf.translation(x, y, z) == Matrix4(1.0f, 0.0f, 0.0f, 1.0f,
												0.0f, 1.0f, 0.0f, 0.5f,
												0.0f, 0.0f, 1.0f, 2.0f,
												0.0f, 0.0f, 0.0f, 1.0f));
		}
	}

	SECTION("View Matrix")
	{

		Vector3 eye = Vector3(5, 5, 5), center = Vector3(0, 0, 0), up = Vector3(0, 1, 0);

		REQUIRE(mf.viewMatrix(eye, center, up) == Matrix4(0.7071f, 0.0f, -0.7071f, 0.0f,
														-0.4082f, 0.8164f, -0.4082f, 0.0f,
														0.5773f, 0.5773f, 0.5773, -8.6602f,
														0.0f, 0.0f, 0.0f, 1.0f));

	}

	SECTION("Projection Matrixes")
	{
		SECTION("Orthographic")
		{
			float l = -2.0f, r = 2.0f, t = 2.0f, b = -2.0f, n = 1.0f, f = 10.0f;

			REQUIRE(mf.orthographicMatrix(l, r, b, t, n, f) == Matrix4(0.50f, 0.0f, 0.0f, 0.0f,
																		0.0f, 0.50f, 0.0f, 0.0f,
																		0.0f, 0.0f, -0.2222f, -1.2222f,
																		0.0f, 0.0f, 0.0f, 1.0f));
		}

		SECTION("Perspective")
		{
			float fov = 30.0f, aspect = 640.0f/480.0f, n = 1, f = 10.0f;

			REQUIRE(mf.perspectiveMatrix(fov, aspect, n, f) ==  Matrix4(2.799f, 0.0f, 0.0f, 0.0f,
																		0.0f, 3.732f, 0.0f, 0.0f,
																		0.0f, 0.0f, -1.2222, -2.2222f,
																		0.0f, 0.0f, -1.0f, 0.0f));
		}
	}

	SECTION("Convertion Matrix")
	{
		Matrix3 m = Matrix3(1.0f);
		Matrix4 n = Matrix4(1.0f);

		SECTION("3X3 to 4X4")
		{
			REQUIRE(mf.convert3To4(m) == Matrix4(1.0f, 1.0f, 1.0f, 0.0f,
												1.0f, 1.0f, 1.0f, 0.0f,
												1.0f, 1.0f, 1.0f, 0.0f,
												0.0f, 0.0f, 0.0f, 1.0f));
		}

		SECTION("4X4 to 3X3")
		{
			REQUIRE(mf.convert4To3(n) == m);
		}
	}
}


////////////////////////////////////////////////////
////											////
////			MATRIX PROPERTIES TESTS			////
////											////
////////////////////////////////////////////////////

TEST_CASE("Test Matrix Properties", "[Matrix2][Matrix3][Matrix4]")
{
	MatrixFactory mf;
	Matrix3 m = Matrix3(1.0f);
	Matrix3 n = Matrix3(1.5f, 3.6f, 1.0f,
						6.7f, 3.6f, 7.0f,
						5.0f, 4.0f, 8.0f);
	Matrix3 l = Matrix3(6.7f);

	SECTION("Commutativity")
	{
		SECTION("on Sum")
		{
			REQUIRE(m+n == n+m);
		}

		SECTION("Not on Multiplication")
		{
			REQUIRE_FALSE(m*n == n*m);
		}
	}

	SECTION("Distributivity")
	{
		SECTION("Multiplication of a Sum on the left")
		{
			REQUIRE(m*(n+l) == m*n + m*l);
		}

		SECTION("Multiplication of a Sum on the right")
		{
			REQUIRE((m + n)*l == m*l + n*l);
		}
	}

	SECTION("Identity")
	{
		SECTION("Multiplication by identity generates the same")
		{
			REQUIRE(m*mf.identity3() == m);
		}

		SECTION("Multiplication of a Matrix by it's inverse, generates Identity")
		{
			REQUIRE(n*inverse(n) == mf.identity3());
		}
	}
}

//TEST_CASE("EVALUATION")
//{
//	srand(static_cast<unsigned> (time(0)));
//	Matrix3 set[10];
//	float matriz[SIZE3X3];
//
//	for (int i = 0; i < 10; i++)
//	{
//		for (int j = 0; j < SIZE3X3; j++)
//		{
//			matriz[j] = static_cast<float> (rand() % 19 - 9);
//		}
//
//		Matrix3 m = Matrix3(matriz);
//		std::cout << "Matriz m:" << std::endl << m << std::endl;
//
//		for (int j = 0; j < SIZE3X3; j++)
//		{
//			matriz[j] = static_cast<float> (rand() % 19 - 9);
//		}
//
//		Matrix3 n = Matrix3(matriz);
//		std::cout << "Matriz n:" << std::endl << n << std::endl;
//
//		std::cout << (inverse(n*m) == inverse(n) * inverse(m)) << std::endl;
//		std::cout << (transpose(n*m) == transpose(m) * transpose(n)) << std::endl;
//	}
//}

#endif // !__MATRIXTESTS_H__