#ifndef HM_PLANE_H
#define HM_PLANE_H

#include "Physics\Physics_Formulas.h"


class HM_Plane
{
private:
	/// <value>The direction that is perpendicular to the plane</value>
	Physics::Vector		mNormal;
	/// <value>The three corners of the Plane</value>
	Physics::Vector		mVertices[3];
	/// <value>The Direction objects Slide from</value>
	Physics::Vector		mSlideDirection;
	/// <value>Angle of the Plane</value>
	float				mSlopeAngle;
	/// <value>Pointer to a Physics_Formula instance</value>
	Physics_Formulas*	mFormula;	
public:
	///<summary> 
	///Constructor
	///</summary>
	///<param name="Vetices">Array of points for Vertices</param>
	HM_Plane(Physics::Vector Vetices[]);
	///<summary> 
	///Destructor
	///</summary>
	~HM_Plane();
	///<summary> 
	///Get the Normal of the Plane
	///</summary>
	///<returns>Normal of the Plane</returns>
	Physics::Vector GetNormal();
	///<summary> 
	///Get the Position of a Vertices of the Plane at the index given 
	///</summary>
	///<param name="index">Index to the Array of Points</param>
	///<returns>Position of Vertice</returns>
	Physics::Vector GetVertices(int index);
	///<summary> 
	///Get the Slope slide direction of the Plane
	///</summary>
	///<returns>Slope slide direction</returns>
	Physics::Vector GetSlopeAcceleration();
	///<summary> 
	///Get the Angle of the Slope of the Plane
	///</summary>
	///<returns>Angle of the Slope</returns>
	float GetSlopeAngle();
	///<summary> 
	///Get the new Speed of Entity based on position of Entity in relation to
	///Resistances of each vertice,the slope of the Plane and the direction of the 
	///Entitys movement
	///</summary>
	///<param name="dir">Direction of Entity</param>
	///<param name="Dampener">Dampener of Resistances</param>
	///<param name="speed">Speed of Entity</param>
	///<returns>New Speed of Entity</returns>
	float GetSpeed(Physics::Vector dir,float Dampener, float speed);
};
#endif