#include "Physics\Shape_Cylinder.h"

Cylinder::Cylinder(Physics::Vector pos, float height, float radius,Entity_Name Entity_Type, int entnumber)
	:	Base_Shape(pos, 1,Entity_Type,entnumber),
		mHeight(height),
		mRadius(radius)
{
	/**< Get all the points on the cylinder by using the position and size passed */
	mVertices[0] = Physics::Vector(mPosition.x,height/2 + mPosition.y,mPosition.z);												/* Find the top and both points on this cylinder using the height of the cylinder */
	mVertices[1] = Physics::Vector(mPosition.x,-height/2 + mPosition.y,mPosition.z);
	mBoundingRadius = mPosition.distance(Physics::Vector(mVertices[0].x + mRadius, mVertices[0].y,mVertices[0].z + mRadius));	/* Find the radius of a circle that encapsulats the whole Shape */
}
Cylinder::~Cylinder()
{
	Base_Shape::~Base_Shape();
}

float Cylinder::GetRadius()
{
	return mRadius;
}
Physics::Vector Cylinder::GetVertex(int index)
{
	return mVertices[index];
}

void Cylinder::SetPosition(Physics::Vector Pos)
{
	/**< Translate all points by the same amount we translate the Position */
	Physics::Vector translation = (Pos - mPosition);																			/* Get the translation of the position to out new position */
	mFormula->Translate_Body(translation,mVertices,2);																			/* Translate the body of our Cylinder */
	mPosition = Pos;																											/* Translate the position of our Cylinder */
}
void Cylinder::Scale(Physics::Vector size)
{
	mRadius = size.x;
	mHeight = size.y;
	/**< Get all points on the Cylinder by using the position and new size passed, then rotate to the current direction */
	mVertices[0] = Physics::Vector(mPosition.x,size.y/2 + mPosition.y,mPosition.z);												
	mVertices[1] = Physics::Vector(mPosition.x,-size.y/2 + mPosition.y,mPosition.z);
	mBoundingRadius = mPosition.distance(Physics::Vector(mVertices[0].x + mRadius, mVertices[0].y,mVertices[0].z + mRadius));	
	Physics::Matrix rot = mFormula->Get_Rotate_To_Direction(Physics::Vector(1,0,0),mDirection);
	if(rot == Physics::Matrix(0))	{ return; }
	mFormula->Translate_Body(-GetPosition(),mVertices, 2);
	mFormula->Rotate_Body(rot,mVertices,2);
	mFormula->Translate_Body(GetPosition(),mVertices,2);
}
void Cylinder::Translate(Physics::Vector Pos)
{
	mFormula->Translate_Body(Pos,mVertices,2);		
	mPosition += Pos;
}
void Cylinder::Rotate(Physics::Vector axis, float angle,bool IsLocal)
{
	/**< Translate to center for accurate rotation about the center of the Square then rotate all Points then translate back */
	mFormula->Translate_Body(-GetPosition(),mVertices,2);																		/* Translate to the point(0,0,0) for accurate rotation about the center of the Cylinder */
	mFormula->Rotate_Body(axis,angle,mVertices,2);																				/* Rotate the Cylinder around the axis by the set angle */
	mFormula->Translate_Body(GetPosition(),mVertices,2);																		/* Translate back to original position */
	Base_Shape::Rotate(axis,angle,IsLocal);																						/* Call the base function */
}
void Cylinder::Rotate(Physics::Matrix matrix)
{
	/**< Translate to center for accurate rotation about the center of the Square then rotate all Points then translate back */
	if(matrix == Physics::Matrix(0))	{ return; }
	mFormula->Translate_Body(-GetPosition(),mVertices, 2);
	mFormula->Rotate_Body(matrix,mVertices,2);
	mFormula->Translate_Body(GetPosition(),mVertices,2);	
	Base_Shape::Rotate(matrix);
}
void Cylinder::RotatetoNormal(Physics::Vector Normal)
{
	/**< Check if we need to rotate */
	if(Normal == mUp)
	{
		return;
	}
	/**< Translate to center for accurate rotation about the center of the cylinder then rotate all Points */
	/**< by the difference of up and normal Vector then translate back */
	mFormula->Translate_Body(-GetPosition(),mVertices,2);
	mFormula->Rotate_Body_To_Direction(mUp,Normal,mVertices,2);	
	mFormula->Translate_Body(GetPosition(),mVertices,2);
	Base_Shape::RotatetoNormal(Normal);	
}
void Cylinder::Rotate_To_Direction(Physics::Vector Target_Direction,bool IsLocal)
{
	/**< Check if we need to rotate */
	if(Target_Direction == mDirection)
	{
		return;
	}
	/**< Translate to center for accurate rotation about the center of the cylinder then rotate all Points */
	/**< by the difference of the Direction and the direction passed then translate back */
	mFormula->Translate_Body(-GetPosition(),mVertices,2);																		/* Translate to the point(0,0,0) for accurate rotation about the center of the Cylinder */
	mFormula->Rotate_Body_To_Direction(mDirection,Target_Direction,mVertices,2);												/* Rotate the Cylinder to the desired direction */
	mFormula->Translate_Body(GetPosition(),mVertices,2);																		/* Translate back to original position */
	Base_Shape::Rotate_To_Direction(Target_Direction,IsLocal);																	/* Call the base function */
}

Physics::Vector Cylinder::Farthest_Point_In_Direction(Physics::Vector Dir)
{								
	/**< Get Normal of the cylinders Top and Bot surfaces and the Line that goes throught the center of the Cylinder */
	Physics::Vector Cylinder_Line = (mVertices[0] - GetPosition());																
	Physics::Vector Normal = Cylinder_Line.Normalise_copy();																	
	float maxdisfromcenter = Cylinder_Line.length();																		
	float distanceonline = mFormula->LINE_GetDistancePerpFromPoint_OnLine(GetPosition(), Normal,Dir,mRadius);			
	/**< Check is the point is in the curved body of the Cylinder */
	if(distanceonline < maxdisfromcenter && distanceonline > -maxdisfromcenter)
	{
		/**< Get the point on the curved body of the cylinder */
		return mFormula->LINE_GetPointByDistance(GetPosition(),Normal,Dir,mRadius);
	}
	/**< If its not the check does it hit the top plane */
	if(distanceonline > maxdisfromcenter)
	{
		/**< Get where it hits the top plane and return */
		return mFormula->PLANE_GetLineIntersection(mVertices[0],Normal,GetPosition(),Dir);
	}
	/**< Get where it hits the bottom plane and return */
	return mFormula->PLANE_GetLineIntersection(mVertices[1],-Normal,GetPosition(),Dir);
}
Physics::Vector Cylinder::Farthest_Point(Physics::Vector Dir)
{	
	Physics::Vector Normal = (mVertices[0] - GetPosition()).Normalise_copy();														/* Get direction and magnitude of the center of the cylinder to the top */
	Physics::Vector cross = Normal.cross(Dir);																						/* Get direction perpendicular to both direction and the cylinder */
	Physics::Vector perp = cross.cross(Normal);																						/* Get direction perpendicular to the cylinder in the direction of the given direction */
	/**< Check which plane the direction is pointing closer too */
	/**< Get a point on the edge of the plane that is closer to the direction given */
	if(Dir.dot(Normal) > Dir.dot(-Normal))
	{
		return mFormula->LINE_GetPoint(mVertices[0], perp, mRadius);
	}
	else
	{
		return mFormula->LINE_GetPoint(mVertices[1], perp, mRadius);
	}
	
}

void Cylinder::Update(float timesincelastframe)
{
	Base_Shape::Update(timesincelastframe);
	/**< Translate body the the distance we translated the position */
	mFormula->Translate_Body(mLastTranslation,mVertices,2);
	mPosition += mLastTranslation;
}
bool Cylinder::CheckPoint(Physics::Vector point)
{
	Physics::Vector normals = (GetPosition() - mVertices[0]).Normalise_copy();				
	/**< Check is the point behind the top plane if is return false */
	if(mFormula->PLANE_IsOnDifference(normals,mVertices[1], point) > 0.01)															
	{
		return false;
	}
	/**< Check is the point behind the bottom plane if is return false */
	if(mFormula->PLANE_IsOnDifference(-normals,mVertices[0], point) > 0.01)
	{
		return false;
	}
	/**< Check is the point is close enough to the center line of the cylinder to be inside the cylinder if not return false */
	if(mFormula->LINE_GetDistanceFrom(GetPosition(),normals, point) > GetRadius() + 0.01)
	{
		return false;
	}
	return true;
}
float Cylinder::CheckRay(Ray ray)
{	
	/**< Check is the point behind the top plane or bot plane if is return that nothing was hit */
	if(mPosition.distance(ray.mStartPosition) > (ray.mDistance + mBoundingRadius) ||
		mFormula->PLANE_IsOnDifference(ray.mDirection,ray.mStartPosition,mPosition) <= 0)
	{
		return 1.0f;
	}
	/**< Check is the point is close enough to the center line of */
	/**< the cylinder to be inside the cylinder if not return that nothing was hit */
	float DisFromLine = mFormula->LINE_GetDistanceFrom(ray.mStartPosition,ray.mDirection,mPosition);
	if(mBoundingRadius < DisFromLine)
	{
		return 1.0f;
	}/**< Find the Point of Collision on the Cylinder */
	else
	{
		Physics::Vector CollisionPos;
		Physics::Vector CylinderUp = (GetVertex(0) - GetVertex(1)).Normalise_copy();
		Physics::Vector RayStart = ray.mStartPosition - mPosition;
		Physics::Vector RayDir = ray.mDirection;
		/**< Check if the Cylinder is pointing up if its not then rotate to up */
		if(CylinderUp != Physics::Vector(0,1,0))
		{
			Physics::Matrix Rotation = mFormula->Get_Rotate_To_Direction(CylinderUp,Physics::Vector(0,1,0));
			RayDir = (ray.mStartPosition + ray.mDirection) - mPosition;
			RayStart = RayStart * Rotation;
			RayDir = ((RayDir * Rotation) - RayStart).Normalise_copy();
		}
		/**< Get variables for Quadratic Equation */
		float A = (RayDir.x * RayDir.x) + (RayDir.z * RayDir.z);
		float B = (2 * RayStart.x * RayDir.x) + (2 * RayStart.z * RayDir.z);
		float C = (RayStart.x * RayStart.x) + (RayStart.z * RayStart.z) - (mRadius * mRadius);
		float MainContact = (-B - std::sqrt((B * B) - (4 * A * C))) / (2 * A);
		float secontcontact = (-B + std::sqrt((B * B) - (4 * A * C))) / (2 * A);
		/**< Check if The contact is a Usable variable if not the the ray doesnt hit the surface */
		if (MainContact != MainContact)
		{
			return 1.0f;
		}
		/**< Get the contact that is closer to the ray as it was the first one that entered */
		if(MainContact > secontcontact)
		{
			MainContact = secontcontact;
		}
		/**< Get the position of contact and then check if it is on the Cylinder */
		CollisionPos = ray.mStartPosition + (ray.mDirection * MainContact);
		if(CheckPoint(CollisionPos))
		{
			return (CollisionPos.distance(ray.mStartPosition)/ ray.mDistance);
		}
		/**< Check if the Ray hits the top of the Cylinder */
		if(CylinderUp.dot(ray.mDirection) <= 0)
		{
			/**< Get the position of contact and then check if it is on the Cylinder */
			CollisionPos = mFormula->PLANE_GetLineIntersection(GetVertex(0),CylinderUp,ray.mStartPosition,ray.mDirection);
			if(CheckPoint(CollisionPos))
			{
				return (CollisionPos.distance(ray.mStartPosition)/ ray.mDistance);
			}
		}/**< Check if the Ray hits the Bottom of the Cylinder */
		else
		{
			/**< Get the position of contact and then check if it is on the Cylinder */
			CollisionPos = mFormula->PLANE_GetLineIntersection(GetVertex(1),-CylinderUp,ray.mStartPosition,ray.mDirection);
			if(CheckPoint(CollisionPos))
			{
				return (CollisionPos.distance(ray.mStartPosition)/ ray.mDistance);
			}
		}
		return 1.0f;
	}
}
