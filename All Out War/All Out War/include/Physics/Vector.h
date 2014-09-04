#ifndef Vector_H
#define Vector_H

#include <math.h>
#include <algorithm>

namespace Physics
{
	class Matrix
	{
	private:
	public:
		/// <value>3 Sets of 3 float Variables</value>
		float	x,y,z, u,v,w, a,b,c;
		///<summary> 
		///Constructor
		///</summary>
		inline Matrix()
			: x(0),y(0),z(0),
			u(0),v(0),w(0),
			a(0),b(0),c(0)
		{
		}
		///<summary> 
		///Constructor
		///</summary>
		///<param name="X">X value</param>
		///<param name="Y">Y value</param>
		///<param name="Z">Z value</param>
		///<param name="U">U value</param>
		///<param name="V">V value</param>
		///<param name="W">W value</param>
		///<param name="A">A value</param>
		///<param name="B">B value</param>
		///<param name="C">C value</param>
		inline Matrix(float X,float Y,float Z,
					float U,float V,float W,
					float A,float B,float C)
			: x(X),y(Y),z(Z),
			u(U),v(V),w(W),
			a(A),b(B),c(C)
		{}
		///<summary> 
		///Constructor
		///Copy
		///</summary>
		///<param name="copy">Matrix that is being copyed</param>
		inline Matrix(Matrix& copy)
			: x(copy.x),y(copy.y),z(copy.z),
			u(copy.u),v(copy.v),w(copy.w),
			a(copy.a),b(copy.b),c(copy.c)
		{}
		///<summary> 
		///Constructor
		///Set all same value
		///</summary>
		///<param name="Scale">Value that all variables equil</param>
		inline Matrix(float Scale)
			: x(Scale),y(Scale),z(Scale),
			u(Scale),v(Scale),w(Scale),
			a(Scale),b(Scale),c(Scale)
		{}
		///<summary> 
		///Constructor
		///Create Matrix from quaternion
		///</summary>
		///<param name="ux">X part of quaternion</param>
		///<param name="uy">Y part of quaternion</param>
		///<param name="uz">Z part of quaternion</param>
		///<param name="uw">W part of quaternion</param>
		inline Matrix(float ux, float uy, float uz, float uw)
				: x(1 - (2 * (uy*uy)) - (2*(uz*uz))),
					y((2 * ux * uy) + (2 * uw * uz)),
					z((2 * ux * uz) - (2 * uw * uy)),
					u((2 * ux * uy) - (2 * uw * uz)),
					v(1 - (2 * (ux*ux)) - (2*(uz*uz))),
					w((2*uy*uz) + (2*uw*ux)),
					a((2*ux*uz) +(2*uw*uy)),
					b((2*uy*uz) - (2*uw*ux)),
					c(1 - (2*(ux*ux)) - (2*(uy*uy)))
		{
		}

		inline Matrix operator * (Matrix other)
		{
			return Matrix(	(x * other.x) + (y * other.u) + (z * other.a),	(x * other.y) + (y * other.v) + (z * other.b),	(x * other.z) + (y * other.w) + (z * other.c),
							(u * other.x) + (v * other.y) + (w * other.z),	(u * other.y) + (v * other.v) + (w * other.b),	(u * other.z) + (v * other.w) + (w * other.c),
							(a * other.x) + (b * other.u) + (c * other.a),	(a * other.y) + (b * other.v) + (c * other.b),	(a * other.z) + (b * other.w) + (c * other.c));

		}
		inline bool operator == (Matrix& other)
		{
			return ( x == other.x && y == other.y && z == other.z
				&& u == other.u && v == other.v && w == other.w
				&& a == other.a && b == other.b && c == other.c);
		}

		///<summary> 
		///Set to identity matrix
		///</summary>
		inline void Identity_Matrix()
		{
			x = v =c = 1;
			y = z = u = w = a = b = 0;
		}
		///<summary> 
		///Create rotate matrix around X axis by angle
		///</summary>
		///<param name="angle">Angle rotated by</param>
		inline void XAXIS_Matrix(float angle)
		{
			x = 1;
			y = z = u = a = 0;
			v = c = cos(angle);
			b = sin(angle);
			w = -sin(angle);
		}
		///<summary> 
		///Create rotate matrix around Y axis by angle
		///</summary>
		///<param name="angle">Angle rotated by</param>
		inline void YAXIS_Matrix(float angle)
		{
			y = u = w = b = 0;
			v = 1;
			x = c = cos(angle);
			a = -sin(angle);
			z = sin(angle);
		}
		///<summary> 
		///Create rotate matrix around Z axis by angle
		///</summary>
		///<param name="angle">Angle rotated by</param>
		inline void ZAXIS_Matrix(float angle)
		{
			x = v =  cos(angle);
			y = -sin(angle);
			u = sin(angle);
			c = 1;
			z = w = a = b = 0;
		}
		///<summary> 
		///Create rotate matrix around given axis by angle
		///</summary>
		///<param name="ux">X part of Axis</param>
		///<param name="uy">Y part of Axis</param>
		///<param name="uz">Z part of Axis</param>
		///<param name="angle">Angle rotated by</param>
		inline void AXIS_MATRIX(float ux, float uy, float uz, float angle)
		{
			x = cos(angle) + ((ux * ux) * (1- cos(angle)));
			y = (ux * uy * (1 - cos(angle))) - (uz* sin(angle));
			z = (ux * uz *(1 - cos(angle))) + (uy * sin(angle));
			u = (uy * ux * (1 - cos(angle))) + (uz * sin(angle));
			v = (cos(angle)) + (uy * uy * (1 - cos(angle)));
			w = (uy * uz * (1 - cos(angle))) - (ux * sin(angle));
			a = (uz * ux * (1 - cos(angle))) - (uy * sin(angle));
			b = (uz * uy * (1 - cos(angle))) + (ux * sin(angle));
			c = (cos(angle)) + (uz * uz * (1 - cos(angle)));
		}
	};

	class Vector
	{
	private:
	public:
		/// <value>The 3 floats that make a Vector</value>
		float x, y, z;
		///<summary> 
		///Constructor
		///</summary>
		inline Vector()
			:x(0),y(0),z(0)
		{	}
		///<summary> 
		///Constructor
		///</summary>
		///<param name="X">X value</param>
		///<param name="Y">Y value</param>
		///<param name="Z">Z value</param>
		inline Vector(float X,float Y,float Z)
			: x(X), y(Y), z(Z)
		{	}
		///<summary> 
		///Constructor
		///Copy
		///</summary>
		///<param name="copy">Vector that is being copyed</param>
		inline Vector(Vector& other)
			: x(other.x), y(other.y), z(other.z)
		{	}
		///<summary> 
		///Constructor
		///Set all same value
		///</summary>
		///<param name="Scale">Value that all variables equil</param>
		inline Vector(float scale)
			: x(scale), y(scale), z(scale)
		{	}
		
		inline void operator = (Vector& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
		}
		inline void operator = (float scale)
		{
			x = scale;
			y = scale;
			z = scale;
		}
		inline bool operator == (Vector& other)
		{
			return ( x == other.x 
					&& y == other.y 
					&& z == other.z);
		}
		inline bool operator == (float other)
		{
			return ( x == other
					&& y == other 
					&& z == other);
		}
		inline bool operator != (Vector& other)
		{
			return ( x != other.x 
					&& y != other.y 
					&& z != other.z);
		}
		inline bool operator < ( Vector& other)
		{
			float len = sqrt(x * x + y * y + z * z);
			float otherlen = sqrt(other.x * other.x + other.y * other.y + other.z * other.z);
			return ( len < otherlen);
		}
		inline bool operator > ( Vector& other)
		{
			float len = sqrt(x * x + y * y + z * z);
			float otherlen = sqrt(other.x * other.x + other.y * other.y + other.z * other.z);
			return ( len > otherlen);
		}
		inline bool operator <= ( Vector& other)
		{
			float len = sqrt(x * x + y * y + z * z);
			float otherlen = sqrt(other.x * other.x + other.y * other.y + other.z * other.z);
			return ( len <= otherlen);
		}
		inline bool operator >= ( Vector& other)
		{
			float len = sqrt(x * x + y * y + z * z);
			float otherlen = sqrt(other.x * other.x + other.y * other.y + other.z * other.z);
			return ( len >= otherlen);
		}
		inline Vector operator - ()
		{
			return Vector(-x,-y,-z);
		}
		inline Vector operator - (Vector& other)
		{
			return Vector( x - other.x,
						y - other.y,
						z - other.z);
		}
		inline Vector operator - (float scale)
		{
			return Vector( x - scale,
						y - scale,
						z - scale);
		}
		inline void operator -= (Vector& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
		}
		inline void operator -= (float scale)
		{
			x -= scale;
			y -= scale;
			z -= scale;
		}
		inline Vector& operator + ()
		{
			return *this;
		}
		inline Vector operator + (Vector& other)
		{
			return Vector( x + other.x,
						y + other.y,
						z + other.z);
		}
		inline Vector operator + (float scale)
		{
			return Vector( x + scale,
						y + scale,
						z + scale);
		}
		inline void operator += (Vector& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
		}
		inline void operator += (float scale)
		{
			x += scale;
			y += scale;
			z += scale;
		}
		inline Vector operator * (Vector& other)
		{
			return Vector(x * other.x, y * other.y, z * other.z);
		}
		inline Vector operator * (Matrix other)
		{
			Vector Result = Vector();
			Result.x = (x * other.x) + (y * other.y) + (z * other.z);
			Result.y = (x * other.u) + (y * other.v) + (z * other.w);
			Result.z = (x * other.a) + (y * other.b) + (z * other.c);
			return Result;
		}	
		inline Vector operator * (float scale)
		{
			return Vector(x * scale, y * scale, z * scale);
		}
		inline void operator *= (Vector& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
		}
		inline void operator *= (float scale)
		{
			x *= scale;
			y *= scale;
			z *= scale;
		}
		inline Vector operator / (Vector& other)
		{
			return Vector(x / other.x, y / other.y, z / other.z);
		}
		inline Vector operator / (float scale)
		{
			if( scale == 0.0)
			{
				return Vector(x,y,z);
			}
			return Vector(x/scale, y/scale , z/scale);
		}
		inline void operator /= (Vector& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
		}
		inline void operator /= (float scale)
		{
			if (scale == 0.0)
			{
				return;
			}
			x /= scale;
			y /= scale;
			z /= scale;
		}

		///<summary> 
		///Get axis with highest value
		///</summary>
		///<returns>What Axis is main Axis(x:0)(y:1)(z:2)</returns>
		inline int GetMainAxis()
		{
			float biggest = x;
			if(y > biggest){return 1;}
			if(z > biggest){return 2;}
			return 0;

		}
		///<summary> 
		///Get pointer to this Vector
		///</summary>
		///<returns>Pointer to this Vector</returns>
		inline float* ptr()
		{
			return &x;
		}
		///<summary> 
		///clips the end off all the values past for decimals
		///</summary>
		inline void Clip()
		{
			int newvalue = (int)(x * 1000);
			int test = (int)(x * 10);
			if(float(newvalue + 1) / 100 == float(test + 1))
			{ newvalue += 1;}
			x = float(newvalue) / 1000;
			newvalue = (int)(y * 1000);
			test = (int)(y * 10);
			if((float(newvalue + 1) / 100) == float(test + 1))
			{ newvalue += 1;}
			y = float(newvalue) / 1000;
			newvalue = (int)(z * 1000);
			test = (int)(z * 10);
			if((float(newvalue + 1) / 100) == float(test + 1))
			{ newvalue += 1;}
			z = float(newvalue) / 1000;

		}
		///<summary> 
		///Swaps Values in of two Vectors
		///</summary>
		///<param name="other">Vector that is being Swaped</param>
		inline void swap(Vector& other)
		{
			Vector temp = Vector(other);
			other = *this;
			*this = temp;
		}
		///<summary> 
		///Pythagoras theorem for getting hypotenuse of triangle.
		///Hypotenuse is the length of the Vector
		///</summary>
		///<returns>Length of the Vector</returns>
		inline float length()
		{
			return sqrt(x * x + y * y + z * z);
		}
		///<summary> 
		///Pythagoras theorem for getting hypotenuse of triangle.
		///Hypotenuse is the length of the Vector.
		///Only use the X and Z conponent of the Vector
		///</summary>
		///<returns>Length of the XZ 2D Vector</returns>
		inline float lengthxz()
		{
			return sqrt(x * x + z * z);
		}
		///<summary> 
		///Gets Length of Vector but doesnt get the root squared. 
		///Which will return the length squared 
		///</summary>
		///<returns>Squared Length of the Vector</returns>
		inline float sqtlength()
		{
			return (x * x + y * y + z * z);
		}
		///<summary> 
		///Gets the distance of one Point to another
		///</summary>
		///<param name="other">Distance to this Point</param>
		///<returns>Distance of one Point to another</returns>
		inline float distance(Vector& other)
		{
			return( *this - other).length();
		}
		///<summary> 
		///Gets the distance of one Point to another squared
		///</summary>
		///<param name="other">Distance to this Point</param>
		///<returns>Distance of one Point to another squared</returns>
		inline float sqtdistance(Vector& other)
		{
			return (*this - other).sqtlength();
		}
		///<summary> 
		///Amount one vector goes in the direction of another vector
		///Only works if the length of both vectors are unit vectors
		///</summary>
		///<param name="other">Other unit vector</param>
		///<returns>Diffence in the Magnitude of Vectors</returns>
		inline float dot(Vector& other)
		{
			return x * other.x + y * other.y + z * other.z;
		}
		///<summary> 
		///Amount one vector goes in the direction of another vector
		///Only works if the length of both vectors are unit vectors
		///Gives Only positive result
		///</summary>
		///<param name="other">Other unit vector</param>
		///<returns>Diffence in the Magnitude of Vectors</returns>
		inline float absdot(Vector& other)
		{
			return abs(x * other.x) + abs(y * other.y) + abs(z * other.z);
		}
		///<summary> 
		///Set to unit vector
		///</summary>
		///<returns>Length of vector</returns>
		inline float Normalise()
		{
			float len = this->length();
			if( len > 0.0)
			{
				x /= len;
				y /= len;
				z /= len;
			}
			return len;
		}
		///<summary> 
		///Get unit vector of this vector
		///</summary>
		///<returns>Unit vector verson of vector</returns>
		inline Vector Normalise_copy()
		{
			float len = this->length();
			Vector returner = Vector(0);
			if (len > 0.0)
			{
				returner.x = x / len;
				returner.y = y / len;
				returner.z = z / len;
			}
			return returner;
		}
		///<summary> 
		///Get Vector that is perpendicular too both given vectors
		///</summary>
		///<param name="other">Other vector</param>
		///<returns>Perpendicular vector</returns>
		inline Vector cross(Vector& other)
		{
			return Vector( y * other.z - z * other.y,
						z * other.x - x * other.z,
						x * other.y - y * other.x);
		}
		///<summary> 
		///Get point that is inbetween two vectors
		///</summary>
		///<param name="other">Other vector</param>
		///<returns>point that is inbetween two vectors</returns>
		inline Vector midpoint( Vector& other)
		{
			return Vector( (x + other.x) * 0.5,
						(y + other.y) * 0.5,
						(z + other.z) * 0.5);
		}
		///<summary> 
		///Set vectors values to the lowest values of the two vectors
		///</summary>
		///<param name="other">Other vector</param>
		inline void makefloor(Vector& other)
		{
			if(other.x < x) { x = other.x; }
			if(other.y < y)	{ y = other.y; }
			if(other.z < z) { z = other.z; }
		}
		///<summary> 
		///Set vectors values to the Highest values of the two vectors
		///</summary>
		///<param name="other">Other vector</param>
		inline void makeceil(Vector& other)
		{
			if(other.x > x) { x = other.x; }
			if(other.y > y)	{ y = other.y; }
			if(other.z > z) { z = other.z; }
		}
		///<summary> 
		///Get Vector that is perpendicular to this vector
		///Won't work if vectors values are 1,0,0
		///</summary>
		///<returns>perpendicular vectors</returns>
		inline Vector perpendicular()
		{
			float sqt_ZERO = float(1e-06 * 1e-06);
			Vector perp = this->cross(Vector(1,0,0));
			if(perp.sqtlength() < sqt_ZERO)
			{
				perp = this->cross(Vector(0,1,0));
			}
			perp.Normalise();
			return perp;
		}
		///<summary> 
		///Gets angle between to another vectors
		///</summary>
		///<param name="dest">Other vector</param>
		///<returns>Angle between vectors</returns>
		inline float anglebetween(Vector& dest)
		{
			float lenproduct = this->length() * dest.length();
			if(lenproduct < 1e-6f) { lenproduct = 1e-6f; }
			float f = this->dot(dest) / lenproduct;
			f = std::max(std::min(f, 1.0f), -1.0f);
			return acos(f);
		}
		///<summary> 
		///Check if the vector is usable
		///</summary>
		///<returns>If the vector is usable</returns>
		inline bool isNaN()
		{
			return(x == 1e-6f || y == 1e-6f || z - 1e-6f);
		}
		///<summary> 
		///Return vector rotated around X axis by given angle 
		///</summary>
		///<param name="angle">Angle of rotation</param>
		///<returns>New rotated point</returns>
		inline Vector Rotate_Xaxis(float angle)
		{
			angle = angle * (3.141/180);
			Matrix rotation = Matrix();
			rotation.XAXIS_Matrix(angle);
			Vector returner = *this * rotation;
			returner.Clip();
			return returner;
		}
		///<summary> 
		///Return vector rotated around Y axis by given angle 
		///</summary>
		///<param name="angle">Angle of rotation</param>
		///<returns>New rotated point</returns>
		inline Vector Rotate_Yaxis(float angle)
		{
			angle = angle * (3.141/180);
			Matrix rotation = Matrix();
			rotation.YAXIS_Matrix(angle);
			Vector returner = *this * rotation;
			returner.Clip();
			return returner;
		}
		///<summary> 
		///Return vector rotated around Z axis by given angle 
		///</summary>
		///<param name="angle">Angle of rotation</param>
		///<returns>New rotated point</returns>
		inline Vector Rotate_Zaxis(float angle)
		{
			angle = angle * (3.141/180);
			Matrix rotation = Matrix();
			rotation.ZAXIS_Matrix(angle);
			Vector returner = *this * rotation;
			returner.Clip();
			return returner;

		}
		///<summary> 
		///Return vector rotated around given axis by given angle 
		///</summary>
		///<param name="axis">Axis that point is rotated around</param>
		///<param name="angle">Angle of rotation</param>
		///<returns>New rotated point</returns>
		inline Vector Rotate_by_axis(Vector& axis, float angle)
		{
			angle = angle * (3.141/180);
			Matrix rotation = Matrix();
			rotation.AXIS_MATRIX(axis.x , axis.y , axis. z, angle);
			Vector returner = *this * rotation;
			returner.Clip();
			return returner;
		}
		///<summary> 
		///Set the Vector to a Null vector
		///</summary>
		inline void ZERO()
		{
			*this = Vector(0);
		}
		///<summary> 
		///Make vector unusable
		///</summary>
		inline void UNIT_NULL()
		{
			*this = Vector(1e-06,1e-06,1e-06);
		}
		///<summary> 
		///Set the Vector to a X unit vector
		///</summary>
		inline void UNIT_X ()
		{
			*this = Vector(1,0,0);
		}
		///<summary> 
		///Set the Vector to a Y unit vector
		///</summary>
		inline void UNIT_Y()
		{
			*this = Vector(0,1,0);
		}
		///<summary> 
		///Set the Vector to a Z unit vector
		///</summary>
		inline void UNIT_Z()
		{
			*this = Vector(0,0,1);
		}
		///<summary> 
		///Set the Vector to a negitive X unit vector
		///</summary>
		inline void NEGATIVE_UNIT_X()
		{
			*this = Vector(-1,0,0);
		}
		///<summary> 
		///Set the Vector to a negitive Y unit vector
		///</summary>
		inline void NEGATIVE_UNIT_Y()
		{
			*this = Vector(0,-1,0);
		}
		///<summary> 
		///Set the Vector to a negitive Z unit vector
		///</summary>
		inline void NEGATIVE_UNIT_Z()
		{
			*this = Vector(0,0,-1);
		}
		///<summary> 
		///Set the Vectors values all to 1
		///</summary>
		inline void UNIT_SCALE()
		{
			*this = Vector(1);
		}
	};
}
#endif