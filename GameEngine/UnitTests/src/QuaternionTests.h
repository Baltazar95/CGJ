#ifndef __QUATERNIONTESTS_H__
#define __QUATERNIONTESTS_H__

#include "catch.hpp"

#include "MathAux.h"

TEST_CASE( "Quaternion Struct Tests", "[Quaternion]")
{
	Quaternion q;

	SECTION("Empty Quaternion Under test:")
	{
		q = Quaternion();

		SECTION("Getters return the right values")
		{
			REQUIRE(q.t == 0.0f);
			REQUIRE(q.x == 0.0f);
			REQUIRE(q.y == 0.0f);
			REQUIRE(q.z == 0.0f);
		}

		SECTION("Assignments put new values")
		{

			q.t = 1.4f;
			q.x = 4.4f;
			q.y = 5.4f;
			q.z = 6.4f;

			REQUIRE(q.t == 1.4f);
			REQUIRE(q.x == 4.4f);
			REQUIRE(q.y == 5.4f);
			REQUIRE(q.z == 6.4f);
		}

		SECTION("Minimum value for each component")
		{
			q.t = std::numeric_limits<float>::min();
			q.x = std::numeric_limits<float>::min();
			q.y = std::numeric_limits<float>::min();
			q.z = std::numeric_limits<float>::min();

			REQUIRE(q.t == std::numeric_limits<float>::min());
			REQUIRE(q.x == std::numeric_limits<float>::min());
			REQUIRE(q.y == std::numeric_limits<float>::min());
			REQUIRE(q.z == std::numeric_limits<float>::min());
		}

		SECTION("Maximum value for each component")
		{
			q.t = std::numeric_limits<float>::max();
			q.x = std::numeric_limits<float>::max();
			q.y = std::numeric_limits<float>::max();
			q.z = std::numeric_limits<float>::max();

			REQUIRE(q.t == std::numeric_limits<float>::max());
			REQUIRE(q.x == std::numeric_limits<float>::max());
			REQUIRE(q.y == std::numeric_limits<float>::max());
			REQUIRE(q.z == std::numeric_limits<float>::max());
		}
	}
	
	SECTION("Quaternion with defined values under test:")
	{
		q = Quaternion(1.5f, 0.0f, 1.0f, 0.0f);

		SECTION("Getters return the right values")
		{
			REQUIRE(q.t == 1.5f);
			REQUIRE(q.x == 0.0f);
			REQUIRE(q.y == 1.0f);
			REQUIRE(q.z == 0.0f);
		}

		SECTION("Result on same Quaternion operations")
		{
			Quaternion qt = Quaternion(1.0f, 1.0f, 0.0f, 0.0f);

			int integerNum = 2;

			SECTION("Sum by a Quaternion")
			{
				q += qt;

				REQUIRE(q.t == 2.5f);
				REQUIRE(q.x == 1.0f);
				REQUIRE(q.y == 1.0f);
				REQUIRE(q.z == 0.0f);
			}

			SECTION("Subtraction by a Quaternion")
			{
				q -= qt;

				REQUIRE(q.t == 0.5f);
				REQUIRE(q.x == -1.0f);
				REQUIRE(q.y == 1.0f);
				REQUIRE(q.z == 0.0f);
			}

			SECTION("Multiplication by a Quaternion")
			{
				q *= qt;

				REQUIRE(q == Quaternion(1.5f, 1.5f, 1.0f, -1.0f));
			}

			SECTION("Multiplication by a int Scalar")
			{
				q *= integerNum;

				REQUIRE(q.t == 3.0f);
				REQUIRE(q.x == 0.0f);
				REQUIRE(q.y == 2.0f);
				REQUIRE(q.z == 0.0f);
			}

			SECTION("Division by a int Scalar")
			{
				q /= integerNum;

				REQUIRE(q.t == 0.75f);
				REQUIRE(q.x == 0.0f);
				REQUIRE(q.y == 0.5f);
				REQUIRE(q.z == 0.0f);
			}

			SECTION("Clean values")
			{
				//TODO - create the apropriate test

				q.clean();

			}
		}
	}

	SECTION("Quaternion from angle and axis under test:")
	{
		float angle = 45.0f;
		Vector4 axis = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		q = Quaternion(angle, axis);

		SECTION("Getters return the right values")
		{
			REQUIRE(fabs(q.t - (0.92388f)) <= EPSILON);
			REQUIRE(fabs(q.x - (0.38268f)) <= EPSILON);
			REQUIRE(q.y == 0.0f);
			REQUIRE(q.z == 0.0f);
		}

		SECTION("Result on new Quaternion operations:")
		{
			Quaternion res;
			Quaternion qt = Quaternion(90.0f, Vector4(0.0f, 1.0f, 0.0f, 1.0f));

			float fres;
			float floatNum = 0.5;

			SECTION("Sum by a Quaternion")
			{
				res = q + qt;

				REQUIRE(fabs(q.t - (0.92388f)) <= EPSILON);
				REQUIRE(fabs(q.x - (0.38268f)) <= EPSILON);
				REQUIRE(q.y == 0.0f);
				REQUIRE(q.z == 0.0f);
				REQUIRE(fabs(qt.t - (0.70711f)) <= EPSILON);
				REQUIRE(qt.x == 0.0f);
				REQUIRE(fabs(qt.y - (0.70711f)) <= EPSILON);
				REQUIRE(qt.z == 0.0f);

				REQUIRE(res == Quaternion(1.63098f, 0.38268f, 0.70710f, 0.0f));
			}

			SECTION("Subtraction by a Quaternion")
			{
				res = q - qt;

				REQUIRE(fabs(q.t - (0.92388f)) <= EPSILON);
				REQUIRE(fabs(q.x - (0.38268f)) <= EPSILON);
				REQUIRE(q.y == 0.0f);
				REQUIRE(q.z == 0.0f);
				REQUIRE(fabs(qt.t - (0.70711f)) <= EPSILON);
				REQUIRE(qt.x == 0.0f);
				REQUIRE(fabs(qt.y - (0.70711f)) <= EPSILON);
				REQUIRE(qt.z == 0.0f);

				REQUIRE(res == Quaternion(0.21677f, 0.38268f, -0.70710f, 0.0f));
			}

			SECTION("Multiplication by a Quaternion")
			{
				res = q * qt;

				REQUIRE(fabs(q.t - (0.92388f)) <= EPSILON);
				REQUIRE(fabs(q.x - (0.38268f)) <= EPSILON);
				REQUIRE(q.y == 0.0f);
				REQUIRE(q.z == 0.0f);
				REQUIRE(fabs(qt.t - (0.70711f)) <= EPSILON);
				REQUIRE(qt.x == 0.0f);
				REQUIRE(fabs(qt.y - (0.70711f)) <= EPSILON);
				REQUIRE(qt.z == 0.0f);

				REQUIRE(res == Quaternion(0.65328f, 0.27059f, 0.65328f, 0.27059f));
			}

			SECTION("Multiplication by a float Scalar on the left")
			{
				res = floatNum * q;

				REQUIRE(fabs(q.t - (0.92388f)) <= EPSILON);
				REQUIRE(fabs(q.x - (0.38268f)) <= EPSILON);
				REQUIRE(q.y == 0.0f);
				REQUIRE(q.z == 0.0f);

				REQUIRE(res == Quaternion(0.46193f, 0.19134f, 0.0f, 0.0f));
			}

			SECTION("Multiplication by a float Scalar on the right")
			{
				res = q * floatNum;

				REQUIRE(fabs(q.t - (0.92388f)) <= EPSILON);
				REQUIRE(fabs(q.x - (0.38268f)) <= EPSILON);
				REQUIRE(q.y == 0.0f);
				REQUIRE(q.z == 0.0f);

				REQUIRE(res == Quaternion(0.46193f, 0.19134f, 0.0f, 0.0f));
			}

			SECTION("Division by a int Scalar")
			{
				res = q / floatNum;

				REQUIRE(fabs(q.t - (0.92388f)) <= EPSILON);
				REQUIRE(fabs(q.x - (0.38268f)) <= EPSILON);
				REQUIRE(q.y == 0.0f);
				REQUIRE(q.z == 0.0f);

				REQUIRE(res == Quaternion(1.84775f, 0.76536f, 0.0f, 0.0f));
			}

			SECTION("Quadrance of a Quaternion")
			{
				fres = quadrance(q);

				REQUIRE(fabs(q.t - (0.92388f)) <= EPSILON);
				REQUIRE(fabs(q.x - (0.38268f)) <= EPSILON);
				REQUIRE(q.y == 0.0f);
				REQUIRE(q.z == 0.0f);

				REQUIRE(fres == 1.0f);
			}

			SECTION("Norm of a Quaternion")
			{
				fres = norm(q);

				REQUIRE(fabs(q.t - (0.92388f)) <= EPSILON);
				REQUIRE(fabs(q.x - (0.38268f)) <= EPSILON);
				REQUIRE(q.y == 0.0f);
				REQUIRE(q.z == 0.0f);

				REQUIRE(fres == 1.0f);
			}

			SECTION("Quaternion Normalized")
			{
				q = Quaternion(2.0f, 1.0f, 0.0f, 0.0f);

				res = normalized(q);

				REQUIRE(q.t == 2.0f);
				REQUIRE(q.x == 1.0f);
				REQUIRE(q.y == 0.0f);
				REQUIRE(q.z == 0.0f);

				REQUIRE(res == Quaternion(0.89442f, 0.44721f, 0.0f, 0.0f));
			}

			SECTION("Conjugate of a Quaternion")
			{
				res = conjugate(q);

				REQUIRE(fabs(q.t - (0.92388f)) <= EPSILON);
				REQUIRE(fabs(q.x - (0.38268f)) <= EPSILON);
				REQUIRE(q.y == 0.0f);
				REQUIRE(q.z == 0.0f);

				REQUIRE(res == Quaternion(0.92388f, -0.38268f, 0.0f, 0.0f));
			}

			SECTION("Inverse of a Quaternion")
			{
				res = inverse(q);

				REQUIRE(fabs(q.t - (0.92388f)) <= EPSILON);
				REQUIRE(fabs(q.x - (0.38268f)) <= EPSILON);
				REQUIRE(q.y == 0.0f);
				REQUIRE(q.z == 0.0f);

				REQUIRE(res == conjugate(q));
			}

			SECTION("LERP between two quaternions")
			{
				q = Quaternion(0.0f, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
				qt = Quaternion(90.0f, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
				Quaternion qe = Quaternion(30.0f, Vector4(0.0f, 1.0f, 0.0f, 1.0f));

				res = lerp(q, qt, 1.0f / 3.0f);

				REQUIRE_FALSE(res == qe);
			}

			SECTION("SLERP between two quaternions")
			{
				q = Quaternion(0.0f, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
				qt = Quaternion(90.0f, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
				Quaternion qe = Quaternion(30.0f, Vector4(0.0f, 1.0f, 0.0f, 1.0f));

				res = slerp(q, qt, 1.0f / 3.0f);

				REQUIRE(res == qe);
			}

			SECTION("Quaternion to Matrix")
			{
				Matrix4 mRes = toGlMatrix(q);

				REQUIRE(fabs(q.t - (0.92388f)) <= EPSILON);
				REQUIRE(fabs(q.x - (0.38268f)) <= EPSILON);
				REQUIRE(q.y == 0.0f);
				REQUIRE(q.z == 0.0f);

				REQUIRE(mRes == Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
										0.0f, 0.70710f, -0.70710f, 0.0f,
										0.0f, 0.70710f, 0.70710f, 0.0f,
										0.0f, 0.0f, 0.0f, 1.0f));
			}
		}
	}

	SECTION("Input and Output streams under test:")
	{
		std::istringstream iss("(1.8, 12.9, 4.5, 7.6)");
		std::ostringstream oss;

		iss >> q;
		oss << q;

		REQUIRE(q == Quaternion(1.8f, 12.9f, 4.5f, 7.6f));
		REQUIRE(oss.str() == "(1.8, 12.9, 4.5, 7.6)");
	}

}

////////////////////////////////////////////////////
////											////
////		QUATERNION PROPERTIES TESTS			////
////											////
////////////////////////////////////////////////////

TEST_CASE("Test Quaternion Properties", "[Quaternion]")
{
	Quaternion q = Quaternion(1.0f, 1.0f, 0.0f, 0.0f);
	Quaternion qt = Quaternion(1.0f, 0.0f, 1.0f, 0.0f);
	Quaternion qe = Quaternion(1.0f, 0.0f, 0.0f, 1.0f);

	SECTION("Commutativity")
	{
		SECTION("on Sum")
		{
			REQUIRE(q + qt == qt + q);
		}

		SECTION("Not on Multiplication")
		{
			REQUIRE_FALSE(q * qt == qt * q);
		}
	}

	SECTION("Distributivity")
	{
		SECTION("On Sum")
		{
			REQUIRE((q + qt) + qe == q + (qt + qe));
		}

		SECTION("On Multiplication")
		{
			REQUIRE((q * qt) * qe == q * (qt * qe));
		}

		SECTION("Multiplication by a Sum on the left")
		{
			REQUIRE(q * (qt + qe) == q * qt + q * qe);
		}

		SECTION("Multiplication of a Sum on the right")
		{
			REQUIRE((q + qt) * qe == q * qe + qt * qe);
		}
	}

	SECTION("Conjugate of the Multiplication equals to the Multiplication of the Conjugates")
	{
		REQUIRE(conjugate(q * qt) ==  conjugate(qt) * conjugate(q));
	}

	SECTION("Scalar part of the Quaternion")
	{
		REQUIRE(((1.0f / 2.0f) * (q + conjugate(q))) == Quaternion(1.0f, 0.0f, 0.0f, 0.0f));
	}

	SECTION("Vector part of the Quaternion")
	{
		REQUIRE(((1.0f / 2.0f) * (q - conjugate(q))) == Quaternion(0.0f, 1.0f, 0.0f, 0.0f));
	}
}

#endif // !__QUATERNIONTESTS_H__