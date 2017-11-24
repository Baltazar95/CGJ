#ifndef __VECTORTESTS_H__
#define __VECTORTESTS_H__

#include "catch.hpp"

#include "MathAux.h"

////////////////////////////////////////////////////
////											////
////				VECTOR2 TESTS				////
////											////
////////////////////////////////////////////////////
TEST_CASE( "Vector2 struct Tests", "[Vector2]" ) 
{
	Vector2 v;

	SECTION("Empty Vector under test:")
	{
		v = Vector2();

		SECTION("Getters return the right values")
		{
			REQUIRE(v.x == 0.0f);
			REQUIRE(v.y == 0.0f);
		}

		SECTION("Assignments put new values")
		{
			v.x = 1.5f;
			v.y = 1.2f;

			REQUIRE(v.x == 1.5f);
			REQUIRE(v.y == 1.2f);
		}

		SECTION("Minimum value for each component")
		{
			v.x = v.y = std::numeric_limits<float>::min();

			REQUIRE(v.x == std::numeric_limits<float>::min());
			REQUIRE(v.y == std::numeric_limits<float>::min());
		}

		SECTION("Maximum value for each component")
		{
			v.x = v.y = std::numeric_limits<float>::max();

			REQUIRE(v.x == std::numeric_limits<float>::max());
			REQUIRE(v.y == std::numeric_limits<float>::max());
		}
	}

	SECTION("Vector with constant under test:")
	{
		v = Vector2(2.0f);

		SECTION("Getters return the right values")
		{
			REQUIRE(v.x == 2.0f);
			REQUIRE(v.y == 2.0f);
		}

		SECTION("Result on same vector operations:")
		{
			Vector2 u = Vector2(1.0f);
			int integerNum = 10;

			SECTION("Sum by a int scalar")
			{
				v += integerNum;

				REQUIRE(v.x == 12);
				REQUIRE(v.y == 12);
			}

			SECTION("Subtraction by a int scalar")
			{
				v -= integerNum;

				REQUIRE(v.x == -8);
				REQUIRE(v.y == -8);
			}

			SECTION("Multiplication by a int scalar")
			{
				v *= integerNum;

				REQUIRE(v.x == 20);
				REQUIRE(v.y == 20);
			}

			SECTION("Division by a int scalar")
			{
				v /= integerNum;

				REQUIRE(v.x == 0.2f);
				REQUIRE(v.y == 0.2f);
			}

			SECTION("Sum by Vector2")
			{
				v += u;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 3.0f);
			}

			SECTION("Subtraction by Vector2")
			{
				v -= u;

				REQUIRE(v.x == 1.0f);
				REQUIRE(v.y == 1.0f);
			}

			SECTION("Normalization of the Vector2")
			{
				v.normalize();

				REQUIRE((roundf(v.x * 10000) / 10000) == 0.7071f);
				REQUIRE((roundf(v.y * 10000) / 10000) == 0.7071f);
				
			}

			/*SECTION("Clean values")
			{
				v = Vector2(4.66777676f);
				v.clean();

				REQUIRE_FALSE(v == Vector2(4.66777676f));
			}*/
		}
	}

	SECTION("Vector with specific values for each component under test:")
	{
		v = Vector2(3.0f, 4.0f);

		SECTION("Getters return the right values")
		{
			REQUIRE(v.x == 3.0f);
			REQUIRE(v.y == 4.0f);
		}

		SECTION("Result on new vector operations:")
		{
			Vector2 res;
			Vector2 u = Vector2(1.0f);
			float floatingNum = 0.5;
			float floatingRes = 0;

			SECTION("Sum by a float scalar")
			{
				res = v + floatingNum;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(res == Vector2(3.5f, 4.5f));
			}

			SECTION("Subtraction by a float scalar")
			{
				res = v - floatingNum;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(res == Vector2(2.5f, 3.5f));
			}

			SECTION("Multiplication by a float scalar on the right")
			{
				res = v * floatingNum;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(res == Vector2(1.5f, 2.0f));
			}

			SECTION("Multiplication by a float scalar on the left")
			{
				res = floatingNum * v;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(res == Vector2(1.5f, 2.0f));
			}

			SECTION("Division by a float scalar")
			{
				res = v / floatingNum;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(res == Vector2(6.0f, 8.0f));
			}

			SECTION("Sum by Vector2")
			{
				res = v + u;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(res == Vector2(4.0f, 5.0f));
			}

			SECTION("Subtraction by Vector2")
			{
				res = v - u;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(res == Vector2(2.0f, 3.0f));
			}

			SECTION("Quadrance of the Vector2")
			{
				floatingRes = quadrance(v);

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(floatingRes == 25);
			}

			SECTION("A normalized vector of the Vector2")
			{
				res = normalized(v);

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(res == Vector2(0.6f, 0.8f));
			}

			SECTION("The norm of the Vector2")
			{
				floatingRes = norm(v);

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(floatingRes == 5.0f);
			}

			SECTION("The dot product between two Vector2 with 90�")
			{
				Vector2 w = Vector2(-1.0f, 1.0f);
				floatingRes = dot(w, u);

				REQUIRE(w.x == -1.0f);
				REQUIRE(w.y == 1.0f);
				REQUIRE(u.x == 1.0f);
				REQUIRE(u.y == 1.0f);
				REQUIRE(floatingRes == 0.0f);
			}

			SECTION("The dot product between two Vector2 with 45�")
			{
				Vector2 w = Vector2(0.0f, 1.0f);
				floatingRes = dot(w, u);

				REQUIRE(w.x == 0.0f);
				REQUIRE(w.y == 1.0f);
				REQUIRE(u.x == 1.0f);
				REQUIRE(u.y == 1.0f);
				REQUIRE(floatingRes == 1.0f);
			}

			SECTION("The dot product between two Vector2 with 0�")
			{
				Vector2 w = Vector2(2.0f, 2.0f);
				floatingRes = dot(w, u);

				REQUIRE(w.x == 2.0f);
				REQUIRE(w.y == 2.0f);
				REQUIRE(u.x == 1.0f);
				REQUIRE(u.y == 1.0f);
				REQUIRE(floatingRes == 4.0f);
			}
		}
	}

	SECTION("Input and Output streams under test:")
	{
		std::istringstream iss ("(1.098, 123.98)");
		std::ostringstream oss;

		iss >> v;
		oss << v;

		REQUIRE(v == Vector2(1.098f, 123.98f));
		REQUIRE(oss.str() == "(1.098, 123.98)");
	}
}


////////////////////////////////////////////////////
////											////
////				VECTOR3 TESTS				////
////											////
////////////////////////////////////////////////////

TEST_CASE("Vector3 struct Tests", "[Vector3]")
{
	Vector3 v;

	SECTION("Empty Vector under test:")
	{
		v = Vector3();

		SECTION("Getters return the right values")
		{
			REQUIRE(v.x == 0.0f);
			REQUIRE(v.y == 0.0f);
			REQUIRE(v.z == 0.0f);
		}

		SECTION("Assignments put new values")
		{
			v.x = 1.5f;
			v.y = 1.2f;
			v.z = 2.5f;

			REQUIRE(v.x == 1.5f);
			REQUIRE(v.y == 1.2f);
			REQUIRE(v.z == 2.5f);
		}

		SECTION("Minimum value for each component")
		{
			v.x = v.y = v.z = std::numeric_limits<float>::min();

			REQUIRE(v.x == std::numeric_limits<float>::min());
			REQUIRE(v.y == std::numeric_limits<float>::min());
			REQUIRE(v.z == std::numeric_limits<float>::min());
		}

		SECTION("Maximum value for each component")
		{
			v.x = v.y = v.z = std::numeric_limits<float>::max();

			REQUIRE(v.x == std::numeric_limits<float>::max());
			REQUIRE(v.y == std::numeric_limits<float>::max());
			REQUIRE(v.z == std::numeric_limits<float>::max());
		}
	}

	SECTION("Vector with constant under test:")
	{
		v = Vector3(2.0f);

		SECTION("Getters return the right values")
		{
			REQUIRE(v.x == 2.0f);
			REQUIRE(v.y == 2.0f);
			REQUIRE(v.z == 2.0f);
		}

		SECTION("Result on same vector operations:")
		{
			Vector3 u = Vector3(1.0f);
			int integerNum = 10;

			SECTION("Sum by a int scalar")
			{
				v += integerNum;

				REQUIRE(v.x == 12);
				REQUIRE(v.y == 12);
				REQUIRE(v.z == 12);
			}

			SECTION("Subtraction by a int scalar")
			{
				v -= integerNum;

				REQUIRE(v.x == -8);
				REQUIRE(v.y == -8);
				REQUIRE(v.z == -8);
			}

			SECTION("Multiplication by a int scalar")
			{
				v *= integerNum;

				REQUIRE(v.x == 20);
				REQUIRE(v.y == 20);
				REQUIRE(v.z == 20);
			}

			SECTION("Division by a int scalar")
			{
				v /= integerNum;

				REQUIRE(v.x == 0.2f);
				REQUIRE(v.y == 0.2f);
				REQUIRE(v.z == 0.2f);
			}

			SECTION("Sum by Vector3")
			{
				v += u;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 3.0f);
				REQUIRE(v.z == 3.0f);
			}

			SECTION("Subtraction by Vector3")
			{
				v -= u;

				REQUIRE(v.x == 1.0f);
				REQUIRE(v.y == 1.0f);
				REQUIRE(v.z == 1.0f);
			}

			SECTION("Normalization of the Vector3")
			{
				v.normalize();

				REQUIRE((roundf(v.x * 10000) / 10000) == 0.5774f);
				REQUIRE((roundf(v.y * 10000) / 10000) == 0.5774f);
				REQUIRE((roundf(v.z * 10000) / 10000) == 0.5774f);
			}

			SECTION("Round values")
			{
				v = Vector3(4.66777676f);
				v.clean();

				REQUIRE_FALSE(v == Vector3(4.66777676f));
			}
		}
	}

	SECTION("Vector with specific values for each component under test:")
	{
		v = Vector3(3.0f, 4.0f, 5.0f);

		SECTION("Getters return the right values")
		{
			REQUIRE(v.x == 3.0f);
			REQUIRE(v.y == 4.0f);
			REQUIRE(v.z == 5.0f);
		}

		SECTION("Result on new vector operations:")
		{
			Vector3 res;
			Vector3 u = Vector3(1.0f);
			float floatingNum = 0.5;
			float floatingRes = 0;

			SECTION("Sum by a float scalar")
			{
				res = v + floatingNum;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(v.z == 5.0f);
				REQUIRE(res == Vector3(3.5f, 4.5f, 5.5f));
			}

			SECTION("Subtraction by a float scalar")
			{
				res = v - floatingNum;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(v.z == 5.0f);
				REQUIRE(res == Vector3(2.5f, 3.5f, 4.5f));
			}

			SECTION("Multiplication by a float scalar on the right")
			{
				res = v * floatingNum;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(v.z == 5.0f);
				REQUIRE(res == Vector3(1.5f, 2.0f, 2.5f));
			}

			SECTION("Multiplication by a float scalar on the left")
			{
				res = floatingNum * v;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(v.z == 5.0f);
				REQUIRE(res == Vector3(1.5f, 2.0f, 2.5f));
			}

			SECTION("Division by a float scalar")
			{
				res = v / floatingNum;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(v.z == 5.0f);
				REQUIRE(res == Vector3(6.0f, 8.0f, 10.0f));
			}

			SECTION("Sum by Vector3")
			{
				res = v + u;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(v.z == 5.0f);
				REQUIRE(res == Vector3(4.0f, 5.0f, 6.0f));
			}

			SECTION("Subtraction by Vector3")
			{
				res = v - u;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(v.z == 5.0f);
				REQUIRE(res == Vector3(2.0f, 3.0f, 4.0f));
			}

			SECTION("Quadrance of the Vector3")
			{
				floatingRes = quadrance(v);

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(v.z == 5.0f);
				REQUIRE(floatingRes == 50);
			}

			SECTION("A normalized vector of the Vector3")
			{
				res = normalized(v);

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(v.z == 5.0f);
				REQUIRE(res == Vector3(0.4242640687f, 0.5656854249f, 0.7071067812f));
			}

			SECTION("The norm of the Vector3")
			{
				floatingRes = norm(v);

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(v.z == 5.0f);
				REQUIRE((roundf(floatingRes * 10000) / 10000) == 7.0711f);
			}

			SECTION("The cross product")
			{
				Vector3 w = Vector3(1.0f, 0.0f, 0.0f);
				v = Vector3(0.0f, 1.0f, 0.0f);
				res = cross(w, v);

				REQUIRE(w.x == 1.0f);
				REQUIRE(w.y == 0.0f);
				REQUIRE(w.z == 0.0f);
				REQUIRE(v.x == 0.0f);
				REQUIRE(v.y == 1.0f);
				REQUIRE(v.z == 0.0f);
				REQUIRE(res == Vector3(0.0f, 0.0f, 1.0f));
			}

			SECTION("The dot product between two Vector3 with 90�")
			{
				Vector3 w = Vector3(0.0f, -1.0f, 0.0f);
				v = Vector3(1.0f, 0.0f, 0.0f);
				floatingRes = dot(w, v);

				REQUIRE(w.x == 0.0f);
				REQUIRE(w.y == -1.0f);
				REQUIRE(w.z == 0.0f);
				REQUIRE(v.x == 1.0f);
				REQUIRE(v.y == 0.0f);
				REQUIRE(v.z == 0.0f);
				REQUIRE(floatingRes == 0.0f);
			}

			SECTION("The dot product between two Vector3 with 45�")
			{
				Vector3 w = Vector3(1.0f, 1.0f, 0.0f);
				v = Vector3(1.0f, 0.0f, 0.0f);
				floatingRes = dot(w, v);

				REQUIRE(w.x == 1.0f);
				REQUIRE(w.y == 1.0f);
				REQUIRE(w.z == 0.0f);
				REQUIRE(v.x == 1.0f);
				REQUIRE(v.y == 0.0f);
				REQUIRE(v.z == 0.0f);
				REQUIRE(floatingRes == 1.0f);
			}

			SECTION("The dot product between two Vector3 with 0�")
			{
				Vector3 w = Vector3(2.0f, 2.0f, 2.0f);
				floatingRes = dot(w, u);

				REQUIRE(w.x == 2.0f);
				REQUIRE(w.y == 2.0f);
				REQUIRE(w.z == 2.0f);
				REQUIRE(u.x == 1.0f);
				REQUIRE(u.y == 1.0f);
				REQUIRE(u.z == 1.0f);
				REQUIRE(floatingRes == 6.0f);
			}
		}
	}

	SECTION("Input and Output streams under test:")
	{
		std::istringstream iss("(1.098, 123.98, 4000.1)");
		std::ostringstream oss;

		iss >> v;
		oss << v;

		REQUIRE(v == Vector3(1.098f, 123.98f, 4000.1f));
		REQUIRE(oss.str() == "(1.098, 123.98, 4000.1)");
	}

	SECTION("Vector3 from Vector2")
	{
		v = Vector3(Vector2(1.0f, 700.3f));

		REQUIRE(v.x == 1.0f);
		REQUIRE(v.y == 700.3f);
		REQUIRE(v.z == 0.0f);
	}

	SECTION("Vector3 from Vector2 plus z value")
	{
		v = Vector3(Vector2(-300.2f, 0.3f), 456.9f);

		REQUIRE(v.x == -300.2f);
		REQUIRE(v.y == 0.3f);
		REQUIRE(v.z == 456.9f);
	}
}


////////////////////////////////////////////////////
////											////
////				VECTOR4 TESTS				////
////											////
////////////////////////////////////////////////////

TEST_CASE("Vector4 struct Tests", "[Vector4]")
{
	Vector4 v;

	SECTION("Empty Vector under test:")
	{
		v = Vector4();

		SECTION("Getters return the right values")
		{
			REQUIRE(v.x == 0.0f);
			REQUIRE(v.y == 0.0f);
			REQUIRE(v.z == 0.0f);
			REQUIRE(v.w == 0.0f);
		}

		SECTION("Assignments put new values")
		{
			v.x = 1.5f;
			v.y = 1.2f;
			v.z = 2.5f;
			v.w = 1.0f;

			REQUIRE(v.x == 1.5f);
			REQUIRE(v.y == 1.2f);
			REQUIRE(v.z == 2.5f);
			REQUIRE(v.w == 1.0f);
		}

		SECTION("Minimum value for each component")
		{
			v.x = v.y = v.z = v.w = std::numeric_limits<float>::min();

			REQUIRE(v.x == std::numeric_limits<float>::min());
			REQUIRE(v.y == std::numeric_limits<float>::min());
			REQUIRE(v.z == std::numeric_limits<float>::min());
			REQUIRE(v.w == std::numeric_limits<float>::min());
		}

		SECTION("Maximum value for each component")
		{
			v.x = v.y = v.z = v.w = std::numeric_limits<float>::max();

			REQUIRE(v.x == std::numeric_limits<float>::max());
			REQUIRE(v.y == std::numeric_limits<float>::max());
			REQUIRE(v.z == std::numeric_limits<float>::max());
			REQUIRE(v.w == std::numeric_limits<float>::max());
		}
	}

	SECTION("Vector with constant under test:")
	{
		v = Vector4(2.0f);

		SECTION("Getters return the right values")
		{
			REQUIRE(v.x == 2.0f);
			REQUIRE(v.y == 2.0f);
			REQUIRE(v.z == 2.0f);
			REQUIRE(v.w == 2.0f);
		}

		SECTION("Result on same vector operations:")
		{
			Vector4 u = Vector4(1.0f);
			int integerNum = 10;

			SECTION("Sum by a int scalar")
			{
				v += integerNum;

				REQUIRE(v.x == 12);
				REQUIRE(v.y == 12);
				REQUIRE(v.z == 12);
				REQUIRE(v.w == 12);
			}

			SECTION("Subtraction by a int scalar")
			{
				v -= integerNum;

				REQUIRE(v.x == -8);
				REQUIRE(v.y == -8);
				REQUIRE(v.z == -8);
				REQUIRE(v.w == -8);
			}

			SECTION("Multiplication by a int scalar")
			{
				v *= integerNum;

				REQUIRE(v.x == 20);
				REQUIRE(v.y == 20);
				REQUIRE(v.z == 20);
				REQUIRE(v.w == 20);
			}

			SECTION("Division by a int scalar")
			{
				v /= integerNum;

				REQUIRE(v.x == 0.2f);
				REQUIRE(v.y == 0.2f);
				REQUIRE(v.z == 0.2f);
				REQUIRE(v.w == 0.2f);
			}

			SECTION("Sum by Vector4")
			{
				v += u;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 3.0f);
				REQUIRE(v.z == 3.0f);
				REQUIRE(v.w == 3.0f);
			}

			SECTION("Subtraction by Vector4")
			{
				v -= u;

				REQUIRE(v.x == 1.0f);
				REQUIRE(v.y == 1.0f);
				REQUIRE(v.z == 1.0f);
				REQUIRE(v.w == 1.0f);
			}

			SECTION("Normalization of the Vector4")
			{
				v.normalize();

				REQUIRE((roundf(v.x * 10000) / 10000) == 0.5f);
				REQUIRE((roundf(v.y * 10000) / 10000) == 0.5f);
				REQUIRE((roundf(v.z * 10000) / 10000) == 0.5f);
				REQUIRE((roundf(v.w * 10000) / 10000) == 0.5f);
			}

			SECTION("Round values")
			{
				v = Vector4(4.66777676f);
				v.clean();

				REQUIRE_FALSE(v == Vector4(4.66777676f));
			}
		}
	}

	SECTION("Vector with specific values for each component under test:")
	{
		v = Vector4(3.0f, 4.0f, 5.0f, 1.0f);

		SECTION("Getters return the right values")
		{
			REQUIRE(v.x == 3.0f);
			REQUIRE(v.y == 4.0f);
			REQUIRE(v.z == 5.0f);
			REQUIRE(v.w == 1.0f);
		}

		SECTION("Result on new vector operations:")
		{
			Vector4 res;
			Vector4 u = Vector4(1.0f);
			float floatingNum = 0.5;
			float floatingRes = 0;

			SECTION("Sum by a float scalar")
			{
				res = v + floatingNum;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(v.z == 5.0f);
				REQUIRE(v.w == 1.0f);
				REQUIRE(res == Vector4(3.5f, 4.5f, 5.5f, 1.5f));
			}

			SECTION("Subtraction by a float scalar")
			{
				res = v - floatingNum;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(v.z == 5.0f);
				REQUIRE(v.w == 1.0f);
				REQUIRE(res == Vector4(2.5f, 3.5f, 4.5f, 0.5f));
			}

			SECTION("Multiplication by a float scalar on the right")
			{
				res = v * floatingNum;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(v.z == 5.0f);
				REQUIRE(v.w == 1.0f);
				REQUIRE(res == Vector4(1.5f, 2.0f, 2.5f, 0.5f));
			}

			SECTION("Multiplication by a float scalar on the left")
			{
				res = floatingNum * v;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(v.z == 5.0f);
				REQUIRE(v.w == 1.0f);
				REQUIRE(res == Vector4(1.5f, 2.0f, 2.5f, 0.5f));
			}

			SECTION("Division by a float scalar")
			{
				res = v / floatingNum;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(v.z == 5.0f);
				REQUIRE(v.w == 1.0f);
				REQUIRE(res == Vector4(6.0f, 8.0f, 10.0f, 2.0f));
			}

			SECTION("Sum by Vector4")
			{
				res = v + u;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(v.z == 5.0f);
				REQUIRE(v.w == 1.0f);
				REQUIRE(res == Vector4(4.0f, 5.0f, 6.0f, 2.0f));
			}

			SECTION("Subtraction by Vector4")
			{
				res = v - u;

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(v.z == 5.0f);
				REQUIRE(v.w == 1.0f);
				REQUIRE(res == Vector4(2.0f, 3.0f, 4.0f, 0.0f));
			}

			SECTION("Quadrance of the Vector4")
			{
				floatingRes = quadrance(v);

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(v.z == 5.0f);
				REQUIRE(v.w == 1.0f);
				REQUIRE(floatingRes == 51);
			}

			SECTION("A normalized vector of the Vector4")
			{
				res = normalized(v);

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(v.z == 5.0f);
				REQUIRE(v.w == 1.0f);
				REQUIRE(res == Vector4(0.4200840252f, 0.5601120336f, 0.700140042f, 0.1400280084f));
			}

			SECTION("The norm of the Vector4")
			{
				floatingRes = norm(v);

				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 4.0f);
				REQUIRE(v.z == 5.0f);
				REQUIRE(v.w == 1.0f);
				REQUIRE((roundf(floatingRes * 10000) / 10000) == 7.1414f);
			}

			/*SECTION("The cross product")
			{
				Vector4 w = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
				v = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
				res = cross(w, v);

				REQUIRE(w.x == 1.0f);
				REQUIRE(w.y == 0.0f);
				REQUIRE(w.z == 0.0f);
				REQUIRE(w.w == 0.0f);
				REQUIRE(v.x == 0.0f);
				REQUIRE(v.y == 1.0f);
				REQUIRE(v.z == 0.0f);
				REQUIRE(v.w == 0.0f);
				REQUIRE(res == Vector4(0.0f, 0.0f, 1.0f, 0.0f));
			}*/

			SECTION("The dot product between two Vector4 with 90�")
			{
				Vector4 w = Vector4(0.0f, -1.0f, 0.0f, 0.0f);
				v = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
				floatingRes = dot(w, v);

				REQUIRE(w.x == 0.0f);
				REQUIRE(w.y == -1.0f);
				REQUIRE(w.z == 0.0f);
				REQUIRE(w.w == 0.0f);
				REQUIRE(v.x == 1.0f);
				REQUIRE(v.y == 0.0f);
				REQUIRE(v.z == 0.0f);
				REQUIRE(v.w == 0.0f);
				REQUIRE(floatingRes == 0.0f);
			}

			SECTION("The dot product between two Vector4 with 45�")
			{
				Vector4 w = Vector4(1.0f, 1.0f, 0.0f, 0.0f);
				v = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
				floatingRes = dot(w, v);

				REQUIRE(w.x == 1.0f);
				REQUIRE(w.y == 1.0f);
				REQUIRE(w.z == 0.0f);
				REQUIRE(w.w == 0.0f);
				REQUIRE(v.x == 1.0f);
				REQUIRE(v.y == 0.0f);
				REQUIRE(v.z == 0.0f);
				REQUIRE(v.w == 0.0f);
				REQUIRE(floatingRes == 1.0f);
			}

			SECTION("The dot product between two Vector4 with 0�")
			{
				Vector4 w = Vector4(2.0f, 2.0f, 2.0f, 0.0f);
				floatingRes = dot(w, u);

				REQUIRE(w.x == 2.0f);
				REQUIRE(w.y == 2.0f);
				REQUIRE(w.z == 2.0f);
				REQUIRE(w.w == 0.0f);
				REQUIRE(u.x == 1.0f);
				REQUIRE(u.y == 1.0f);
				REQUIRE(u.z == 1.0f);
				REQUIRE(u.w == 1.0f);
				REQUIRE(floatingRes == 6.0f);
			}
		}
	}

	SECTION("Input and Output streams under test:")
	{
		std::istringstream iss("(1.098, 123.98, 4000.1, 1.0)");
		std::ostringstream oss;

		iss >> v;
		oss << v;

		REQUIRE(v == Vector4(1.098f, 123.98f, 4000.1f, 1.0f));
		REQUIRE(oss.str() == "(1.098, 123.98, 4000.1, 1)");
	}

	SECTION("Vector4 from Vector3 plus w value")
	{
		v = Vector4(Vector3(-300.2f, 0.3f, -98.8f), 1.0f);

		REQUIRE(v.x == -300.2f);
		REQUIRE(v.y == 0.3f);
		REQUIRE(v.z == -98.8f);
		REQUIRE(v.w == 1.0f);
	}
}

////////////////////////////////////////////////////
////											////
////			VECTOR PROPERTIES TESTS			////
////											////
////////////////////////////////////////////////////

TEST_CASE("Test Vector Properties", "[Vector2][Vector3][Vector4]")
{
	Vector2 v2, u2, t2;
	Vector3 v3, u3, t3;
	Vector4 v4, u4, t4;
	float alpha, beta;

	SECTION("Commutativity")
	{
		v2 = Vector2(1.4f);
		u2 = Vector2(4.5666f);
		v3 = Vector3(75.8f);
		u3 = Vector3(1000.8f);
		v4 = Vector4(89.3f);
		u4 = Vector4(956.87f);

		SECTION("Sum")
		{
			REQUIRE((v2 + u2) == (u2 + v2));
			REQUIRE((v3 + u3) == (u3 + v3));
			REQUIRE((v4 + u4) == (u4 + v4));
		}

		SECTION("Dot Product")
		{
			REQUIRE(dot(v2, u2) == dot(u2, v2));
			REQUIRE(dot(v3, u3) == dot(u3, v3));
			REQUIRE(dot(v4, u4) == dot(u4, v4));
		}
	}

	SECTION("Distributivity")
	{
		v2 = u2 = t2 = Vector2(4.566f);
		v3 = u3 = t3 = Vector3(1000.8f);
		v4 = u4 = t4 = Vector4(956.87f);

		SECTION("Sum")
		{
			REQUIRE(((v2 + u2) + t2) == (v2 + (u2 + t2)));
			REQUIRE(((v3 + u3) + t3) == (v3 + (u3 + t3)));
			REQUIRE(((v4 + u4) + t4) == (v4 + (u4 + t4)));
		}

		SECTION("Sum with Multiplication by a Scalar")
		{
			alpha = 34.6f;

			REQUIRE((alpha*(u2 + t2)) == (alpha*u2 + alpha*t2));
			REQUIRE((alpha*(u3 + t3)) == (alpha*u3 + alpha*t3));
			REQUIRE((alpha*(u4 + t4)) == (alpha*u4 + alpha*t4));
		}

		SECTION("Multiplication by a Sum of Scalars")
		{
			alpha = 34.6f;
			beta = 89.9f;

			REQUIRE((v2*(alpha + beta)) == (v2*alpha + v2*beta));
			REQUIRE((v3*(alpha + beta)) == (v3*alpha + v3*beta));
			REQUIRE((v4*(alpha + beta)) == (v4*alpha + v4*beta));
		}

		SECTION("Dot Product")
		{
			REQUIRE(dot(v2, (u2 + t2)) == dot(v2, u2) + dot(v2, t2));
			REQUIRE(dot(v3, (u3 + t3)) == dot(v3, u3) + dot(v3, t3));
			REQUIRE(dot(v4, (u4 + t4)) == dot(v4, u4) + dot(v4, t4));
			REQUIRE(dot(v2, dot(u2, t2)) == dot(dot(v2, u2), t2));
			REQUIRE(dot(v3, dot(u3, t3)) == dot(dot(v3, u3), t3));
			REQUIRE(dot(v4, dot(u4, t4)) == dot(dot(v4, u4), t4));
		}

		SECTION("Dot Product of a Multiplication")
		{
			alpha = 57.89f;

			REQUIRE((dot((alpha*u2), v2)) == (alpha * dot(u2, v2)));
			REQUIRE((dot((alpha*u3), v3)) == (alpha * dot(u3, v3)));
			REQUIRE((dot((alpha*u4), v4)) == (alpha * dot(u4, v4)));
		}
	}

	SECTION("Cancelation")
	{
		v2 = u2 = Vector2(1.4f);
		v3 = u3 = Vector3(75.8f);
		v4 = u4 = Vector4(89.3f);

		REQUIRE((v2 + (-u2)) == 0.0f);
		REQUIRE((v3 + (-u3)) == 0.0f);
		REQUIRE((v4 + (-u4)) == 0.0f);
	}

	SECTION("Identity")
	{
		t2 = Vector2(3.1478f);
		t3 = Vector3(10000.9f);
		t4 = Vector4(0.3f);

		REQUIRE((t2 + 0.0f) == t2);
		REQUIRE((t3 + 0.0f) == t3);
		REQUIRE((t4 + 0.0f) == t4);
	}
}

////////////////////////////////////////////////////
////											////
////		COMPLEX VECTOR OPERATION TESTS		////
////											////
////////////////////////////////////////////////////

TEST_CASE("Complex Combinations of Operations", "[Vector2][Vector3][Vector4]")
{
	Vector2 v2, u2, t2;
	Vector3 v3, u3, t3;
	Vector4 v4, u4, t4;
	float alpha;

	SECTION("Multiplication by Dot Product of a Cross Product")
	{
		alpha = 67.43f;
		v3 = Vector3(1.0f, 0.0f, 0.0f);
		u3 = Vector3(0.0f, 1.0f, 0.0f);
		t3 = Vector3(1.0f, 2.0f, 3.0f);

		REQUIRE(roundf(alpha*dot(t3, cross(v3, u3)) * 1000) / 1000 == 202.29f);
	}

	SECTION("Class Evaluation")
	{
		/*Vector3 v, w, u;
		Vector3 up, view;
		Vector3 list[3];
		Vector3 results[9];
		list[0] = Vector3(1.0f, 0.0f, 0.0f);
		list[1] = Vector3(0.0f, 2.0f, 0.0f);
		list[2] = Vector3(0.0f, 0.0f, 3.0f);

		for (int i = 0; i < 3; i++)
		{
			view = list[i];
			for (int j = 0; j < 3; j++)
			{
				up = list[j];

				std::cout << "View: " << view << std::endl;
				std::cout << "Up: " << up << std::endl;

				try
				{
					v = normalized(view);
					w = normalized(cross(up, v));
					u = cross(v, w);

					v.clean();
					w.clean();
					u.clean();

					std::cout << "v: " << v << std::endl;
					std::cout << "u: " << u << std::endl;
					std::cout << "w: " << w << std::endl;
				}
				catch (std::overflow_error e)
				{
					std::cout << "tried to normalize a null vector" << std::endl;
				}


			}
		}*/

		/*TEST_CASE("Rodrigues Rotation Formula (Vector Form) turno 1")
		{
			Vector3(1,0,0)
			Vector3(0,2,0)
			Vector3(0,0,3)

			angle = 90
		}*/

		/*TEST_CASE("vECTOR tRIPLE pRODUCT turno 2")
		{
			cross(i, cross(j,k) == j*(dot(i,k)) -  k*(dot(i,j))
		}*/



	}

	SECTION("Test normalization of null vector")
	{
		v3 = Vector3(0.0f);

		REQUIRE_THROWS(v3.normalize());
	}
}

#endif // !__VECTORTESTS_H__