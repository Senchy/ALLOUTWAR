#ifndef PHYSICS_FORMULAS_H
#define PHYSICS_FORMULAS_H

#include "Physics\Vector.h"

class Physics_Formulas
{
private:
	/// <value>Acceleration of gravity</value>
	Physics::Vector				mGravity;
	/// <value>Pointer to a Physics_Formulas instance</value>
	static Physics_Formulas*	mPhysicsInstance;
	///<summary> 
	///Constructor
	///</summary>
	Physics_Formulas();
public:
	///<summary> 
	///Destructor
	///</summary>
	~Physics_Formulas();
	///<summary> 
	///Get instance of the class
	///</summary>
	///<returns>A pointer to the only instance of this class</returns>
	static Physics_Formulas* getInstance();
	///<summary> 
	///Get the value of gravity in this instance if the Entity is not on the ground
	///</summary>
	///<param name="isonground">If on the Ground</param>
	///<returns>Gravity acceleration</returns>
	Physics::Vector GetGravity(bool isonground);
	///<summary> 
	///Set gravity too a different value
	///</summary>
	///<param name="gravity">Gravity acceleration</param>
	void SetGravity(float gravity);
    ///<summary> 
	///Calculate the translation to the new position for the point using euclidean distance formula.
	///Return the translation of the old point to the new point.
	///</summary>
	/// <param name="Position">Point or center point of an Object</param>
	/// <param name="Velocity">Velocity of the point or Object</param>
	/// <param name="Acceleration">The acceleration of the point or Object</param>
	/// <param name="last_update_time">Time since last updated</param>
	/// <returns>The difference of the new point and old point</returns>
	Physics::Vector New_Position(Physics::Vector Position, Physics::Vector Velocity, Physics::Vector Acceleration, float last_update_time);
	///<summary> 
	///Calculate the change in velocity for the point or Object using euclidean velocity formula.
	///Return the change in velocity
	///</summary>
	///<param name="Velocity">The Velocity of the point or Object</param>
	///<param name="Acceleration">The acceleration of the point or Object</param>
	///<param name="time">The time since it has last been updated</param>
	///<returns>The difference of the new velocity and old velocity</returns>
	Physics::Vector New_Velocity(Physics::Vector Velocity, Physics::Vector Acceleration, float time);
	///<summary> 
	///Translate a group of points in the same direction and magnatude
	///</summary>
	///<param name="Translation">Distance and direction that the points will be translated by</param>
	///<param name="Vertices">List of points</param>
	///<param name="number_of_Vertices">Number of points</param>
	void Translate_Body(Physics::Vector Translation, Physics::Vector Vertices[], int number_of_Vertices);
	///<summary> 
	///Create a rotation matrix based on the two directions
	///The rotation matrix will rotate points from 
	///the first direction to the second direction
	///</summary>
	///<param name="CurrectDirection">Direction we are at right now</param>
	///<param name="TargetDirection">Direction we want to rotate to</param>
	///<returns>Rotation matrix</returns>
	Physics::Matrix Get_Rotate_To_Direction(Physics::Vector CurrectDirection, Physics::Vector TargetDirection);
	///<summary> 
	///Rotate a group of points in the same angle and axis based on directions
	///</summary>
	///<param name="Currentdirection">Direction we are at right now</param>
	///<param name="TargetDirection">Direction we want to rotate to</param>
	///<param name="Vertices">List of points</param>
	///<param name="number_of_Vertices">Number of points</param>
	void Rotate_Body_To_Direction(Physics::Vector Currentdirection, Physics::Vector TargetDirection, Physics::Vector Vertices[], int number_of_Vertices);
	///<summary> 
	///Rotate a group of points in the same angle and axis
	///</summary>
	///<param name="axis">Axis we want to rotate around</param>
	///<param name="angle">Angle that we want to rotate by</param>
	///<param name="Vertices">List of points</param>
	///<param name="number_of_Vertices">Number of points</param>
	void Rotate_Body(Physics::Vector axis, float angle, Physics::Vector Vertices[], int number_of_Vertices);
	///<summary> 
	///Rotate a group of points by a Matrix
	///</summary>
	///<param name="rotationmatrix">Matrix we want to rotate by</param>
	///<param name="Vertices">List of points</param>
	///<param name="number_of_Vertices">Number of points</param>
	void Rotate_Body(Physics::Matrix rotationmatrix, Physics::Vector Vertices[], int number_of_Vertices);
	///<summary> 
	///Get the cross of the 3 points to get the normal of the plane
	///</summary>
	///<param name="Point1">Point on the plane</param>
	///<param name="Point2">Point on the plane</param>
	///<param name="Point3">Point on the plane</param>
	///<returns>planes normal</returns>
	Physics::Vector PLANE_GetNormal(Physics::Vector Point1,Physics::Vector Point2,Physics::Vector Point3);
	///<summary> 
	///Check if a point is on a plane by creating a plane using a point and a normal. Then
	///solve the equation if the equation = 0 then it is on the plane
	///</summary>
	///<param name="normal">Normal of the plane</param>
	///<param name="plane_point">Known Point on the plane</param>
	///<param name="point">Point we are checking</param>
	///<returns>If the point is on the plane</returns>
	bool PLANE_ISOn(Physics::Vector normal, Physics::Vector plane_point, Physics::Vector point);
	///<summary> 
	///Check if a point is on a plane by creating a plane using a point and a normal. 
	///solve the equation and return the result as it = the distance away from the plane
	///</summary>
	///<param name="normal">Normal of the plane</param>
	///<param name="plane_point">Known Point on the plane</param>
	///<param name="point">Point we are checking</param>
	///<returns>Distance away from the plane</returns>
	float PLANE_IsOnDifference(Physics::Vector normal, Physics::Vector plane_point, Physics::Vector point);
	///<summary> 
	///Get the Slope of a Plane Using the differnece from the Normal of the Plane
	///</summary>
	///<param name="normal">Normal of Plane</param>
	///<returns>Slope of Plane</returns>
	Physics::Vector PLANE_GetSlope(Physics::Vector normal);
	///<summary> 
	///Get the Y component of point on the plane with the xz of a point
	///</summary>
	///<param name="normal">Normal of Plane</param>
	///<param name="plane_point">Point on the Plane</param>
	///<param name="point">Point we want to fond the Y value for</param>
	///<returns>The y Value of the Point</returns>
	float PLANE_GetHeight(Physics::Vector normal,Physics::Vector plane_point, Physics::Vector point);
	///<summary> 
	///Check were a line intersects the plane by quadratic equation of the Line and plane.
	///</summary>
	///<param name="planepoint">Known Point on the plane</param>
	///<param name="planeNormal">Normal of the plane</param>
	///<param name="linepoint">Known Point on the Line</param>
	///<param name="lineDir">Direction of Line</param>
	///<returns>Point were the line intersects the plane</returns>
	Physics::Vector PLANE_GetLineIntersection(Physics::Vector planepoint, Physics::Vector planeNormal, Physics::Vector linepoint, Physics::Vector lineDir);
	///<summary> 
	///Find a point on the line that is a certain distance away
	///</summary>
	///<param name="point">Known Point on the line</param>
	///<param name="dir">Direction of the line</param>
	///<param name="dist">Distance from the point</param>
	///<returns>Point on the line</returns>
	Physics::Vector LINE_GetPoint(Physics::Vector point,Physics::Vector dir, float dist);
	///<summary> 
	///Find how far away a point is from the line
	///</summary>
	///<param name="linepoint">Known Point on the line</param>
	///<param name="lineDir">Direction of the line</param>
	///<param name="point">Point we are checking</param>
	///<returns>Distance from the line</returns>
	float LINE_GetDistanceFrom(Physics::Vector linepoint, Physics::Vector lineDir, Physics::Vector point);
	///<summary> 
	///Find a point that is a set distance from the line in a direction away from the line
	///</summary>
	///<param name="linepoint">Known Point on the line</param>
	///<param name="lineDir">Direction of the line</param>
	///<param name="DirFromLine">Direction away from line</param>
	///<param name="dist">Distance from line</param>
	///<returns>Point we are trying to find</returns>
	Physics::Vector LINE_GetPointByDistance(Physics::Vector linepoint, Physics::Vector lineDir, Physics::Vector DirFromLine, float dist);
	///<summary> 
	///Find the distance along the line that is perpendicular from a point away from 
	///the line and is a set distance away
	///</summary>
	///<param name="linepoint">Known Point on the line</param>
	///<param name="lineDir">Direction of the line</param>
	///<param name="DirFromLine">Direction away from line</param>
	///<param name="dist">Distance from line</param>
	///<returns>Distance from point along the line</returns>
	float LINE_GetDistancePerpFromPoint_OnLine(Physics::Vector linepoint, Physics::Vector lineDir, Physics::Vector DirFromLine, float dist);
	///<summary> 
	///Find the point along the line that is perpendicular from a point away from 
	///the line and is a set distance away
	///</summary>
	///<param name="linepoint">Known Point on the line</param>
	///<param name="lineDir">Direction of the line</param>
	///<param name="DirFromLine">Direction away from line</param>
	///<param name="dist">Distance from line</param>
	///<returns>Point along the line that is perpedicular to the point away from line</returns>
	Physics::Vector LINE_GetPointPerpFromPoint(Physics::Vector linepoint, Physics::Vector lineDir, Physics::Vector DirFromLine, float dist);
	///<summary> 
	///Find the point along the line that is perpendicular from a point away from the line
	///</summary>
	///<param name="linepoint">Known Point on the line</param>
	///<param name="lineDir">Direction of the line</param>
	///<param name="point">Point away from line</param>
	///<returns>Point along the line that is perpedicular to the point away from line</returns>
	Physics::Vector LINE_GetPointPerpFromPoint(Physics::Vector linepoint, Physics::Vector lineDir, Physics::Vector point);

};
#endif