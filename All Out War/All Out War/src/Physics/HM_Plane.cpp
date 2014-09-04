#include "Physics\HM_Plane.h"

HM_Plane::HM_Plane(Physics::Vector Vetices[])
{
	/**< Get the instance of Physics_Formulas and Set all the points passed to the my vertices  */
	mFormula = Physics_Formulas::getInstance();		
	mVertices[0] = Vetices[0];
	mVertices[1] = Vetices[1];
	mVertices[2] = Vetices[2];
	/**< Get the normal of the plane , angle of the Slope and Direction of the slope */
	mNormal = mFormula->PLANE_GetNormal(mVertices[0],mVertices[1],mVertices[2]);	
	mSlopeAngle = mNormal.anglebetween(Physics::Vector(0,1,0));
	mSlideDirection = mFormula->PLANE_GetSlope(mNormal);
}
HM_Plane::~HM_Plane()
{
}
Physics::Vector HM_Plane::GetNormal()
{
	return mNormal;
}	
Physics::Vector HM_Plane::GetVertices(int index)
{
	return mVertices[index];
}
Physics::Vector HM_Plane::GetSlopeAcceleration()
{
	return mSlideDirection;
}
float HM_Plane::GetSpeed(Physics::Vector dir,float Dampener, float speed)
{
	/**< If the Slope Angle is too big then return 0 speed */
	if(mSlopeAngle > 0.9)
	{
		return 0;
	}
	else
	{
		/**< How much the slope will effect the speed */
		float Slope_Elevation_Percent = (((float)((int)((mSlopeAngle * 180)/ 3.141))) / 100);
		/**< How much the direction is pointing the same as the slope */
		float Slope_Direction_Deviation = (((float)((int)((dir.anglebetween(Physics::Vector(mSlideDirection.x, 0, mSlideDirection.z).Normalise_copy()) * 180)/ 3.141) - 90))/ 90);
		return (speed * Dampener * (1 + (Slope_Elevation_Percent * Slope_Direction_Deviation)));
	}
}
float HM_Plane::GetSlopeAngle()
{
	return mSlopeAngle;
}