#include "Physics\Shape_Sphere.h"

Sphere::Sphere(Physics::Vector pos, float Radius,Entity_Name Entity_Type, int entnumber)
	:	Base_Shape(pos,0,Entity_Type,entnumber)
{
	mBoundingRadius = Radius;
}
Sphere::~Sphere()
{
	Base_Shape::~Base_Shape();
}

void Sphere::SetPosition(Physics::Vector Pos)
{
	Base_Shape::SetPosition(Pos);
}
void Sphere::Scale(Physics::Vector size)
{
	mBoundingRadius = size.x;
}
void Sphere::Translate(Physics::Vector Pos)
{
	mPosition += Pos;
}
void Sphere::Rotate(Physics::Vector axis, float angle,bool IsLocal)
{
	Base_Shape::Rotate(axis,angle,IsLocal);
}
void Sphere::Rotate(Physics::Matrix matrix)
{
	Base_Shape::Rotate(matrix);
}

void Sphere::RotatetoNormal(Physics::Vector Normal)
{
	Base_Shape::RotatetoNormal(Normal);	
}
void Sphere::Rotate_To_Direction(Physics::Vector Target_Direction,bool IsLocal)
{
	Base_Shape::Rotate_To_Direction(Target_Direction,IsLocal);
}

Physics::Vector Sphere::Farthest_Point_In_Direction(Physics::Vector Dir)
{
	/**< Return point in a direction by radius  */
	Physics::Vector pos = GetPosition();
	float rad = GetBoundingRadius();
	Physics::Vector returner = pos + (Dir * rad);
	return returner;
}
Physics::Vector Sphere::Farthest_Point(Physics::Vector Dir)
{
	/**< Return point in a direction by radius  */
	return (GetPosition() + (Dir * GetBoundingRadius()));
}


void Sphere::Update(float timesincelastframe)
{
	Base_Shape::Update(timesincelastframe);
	mPosition += mLastTranslation;
}
bool Sphere::CheckPoint(Physics::Vector point)
{
	/**< Check is the point close enough to the center of the sphere to be inside the sphere */
	if((point - GetPosition()).length() < mBoundingRadius)
	{
		return true;
	}
	return false;
}
float Sphere::CheckRay(Ray ray)
{
	/**< Check if ray is shot in direction of Entity */
	if(mPosition.distance(ray.mStartPosition) > (ray.mDistance + mBoundingRadius) || mFormula->PLANE_IsOnDifference(ray.mDirection,ray.mStartPosition,mPosition) >= 0)
	{
		return 1.0f;
	}
	/**< Check if the Ray comes close to the bounding Radius */
	float DisFromLine = mFormula->LINE_GetDistanceFrom(ray.mStartPosition,ray.mDirection,mPosition);
	if(mBoundingRadius < DisFromLine)
	{
		return 1.0f;
	}
	else
	{
		/**< Get where it hits the sphere and return the distance from the ray position to the point of contact */
		Physics::Vector pos = mFormula->LINE_GetPointPerpFromPoint(ray.mStartPosition,ray.mDirection,mPosition);
		float D = std::sqrt((DisFromLine* DisFromLine) + (mBoundingRadius * mBoundingRadius));
		pos = mFormula->LINE_GetPoint(pos,-ray.mDirection,D);
		return (pos.distance(ray.mStartPosition) / ray.mDistance);
	}
}