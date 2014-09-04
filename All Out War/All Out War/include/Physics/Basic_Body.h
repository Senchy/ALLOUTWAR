#ifndef BASIC_BODY_H
#define BASIC_BODY_H

#include "Physics\Physics_Formulas.h"
#include "Physics\Height_Map.h"

class Base_Shape
{
private:
	/// <value>The unique number for the Entity</value>
	const unsigned			mEntNumber;
protected:
	/// <value>pointer to a Physics_Formula instance</value>
	Physics_Formulas*		mFormula;	
	/// <value>Pointer to the Height Map Node that the Entity is on</value>
	HM_Node*				mHeightMap_Node;
	/// <value>List of corner Nodes surounding the Entity</value>
	Graph_Node**			mNodes;
	/// <value>What type of Entity used for casting</value>
	Entity_Name				mEntity_Type; 
	/// <value>If the Entity is marked for deletion</value>
	bool					mDead;
	/// <value>What type of physics Entity</value>
	int						mType;
	/// <value>The current direction this Entity is pointig in</value>
	Physics::Vector			mDirection;
	/// <value>The current up direction the Entity</value>
	Physics::Vector			mUp;
	/// <value>The radius of the bounding circle that incapulats the Entity</value>
	float					mBoundingRadius;
	/// <value>The distance the Entity was translated last frame</value>
	Physics::Vector			mLastTranslation;
	/// <value>Position of the Entity</value>
	Physics::Vector			mPosition;
	/// <value>Velocity of the Entity</value>
	Physics::Vector			mVelocity;
	/// <value>Acceleration of the Entity</value>
	Physics::Vector			mAcceleration;
	/// <value>What the Entity is colliding with</value>
	Base_Shape*				mCollidionObject;
	/// <value>Point of contact with another Entity</value>
	Physics::Vector			mCollisionPoint;
	/// <value>Normal at the point of contact with another Entity</value>
	Physics::Vector			mCollisionNormal;
	
	///<summary> 
	///Rotate the body so the up direction of the Entity is the same as the normal
	///</summary>
	///<param name="Normal">Normal of the Plane we rotate too</param>
	virtual void RotatetoNormal(Physics::Vector Normal);
public:
	///<summary> 
	///Constructor
	///</summary>
	///<param name="pos">Starting position</param>
	///<param name="type">Type of physics body</param>
	///<param name="Entity_Type">Type of Entity</param>
	///<param name="entnumber">Unique number for the Entity</param>
	Base_Shape(Physics::Vector pos, int type,Entity_Name Entity_Type, int entnumber);
	///<summary> 
	///Destructor
	///</summary>
	virtual ~Base_Shape();
	///<summary> 
	///Get the corner Nodes created for moving around the Entity. 
	///</summary>
	///<returns>Corner nodes</returns>
	Graph_Node** GetCornerNodes();
	///<summary> 
	///Set the corner Nodes surounding this Entity
	///</summary>
	///<param name="evt">Corner Nodes surounding this Entity</param>
	void SetCornerNodes(Graph_Node** nodes);
	///<summary> 
	///Get the radius of the bounding sphere
	///</summary>
	///<returns>The size of the sphere that encircles the Entity</returns>
	float GetBoundingRadius();
	///<summary> 
	///Get the type of shape this is
	///</summary>
	///<returns>Type of shape</returns>
	int GetType();
	///<summary> 
	///Get the type of Entity this is
	///</summary>
	///<returns>Type of Entity</returns>
	Entity_Name	GetEntityType();
	///<summary> 
	///Get the position of the Entity 
	///</summary>
	///<returns>Entity position</returns>
	Physics::Vector GetPosition();
	///<summary> 
	///Get the velocity of the Entity
	///</summary>
	///<returns>Velocity of the Entity</returns>
	Physics::Vector GetVelocity();	
	///<summary> 
	///Get the acceleration of the Entity
	///</summary>
	///<returns>Acceleration of the Entity</returns>
	Physics::Vector GetAcceleration();
	///<summary> 
	///Get the direction of the Entity
	///</summary>
	///<returns>Direction of the Entity</returns>
	Physics::Vector GetDirection();
	///<summary> 
	///Get the Unique number for the Entity
	///</summary>
	///<returns>Unique number for the Entity</returns>
	int GetEntityNumber();
	///<summary> 
	///Get if the Entity is marked for deletion
	///</summary>
	///<returns>If the Entity is marked for deletion</returns>
	bool IsDead();
	///<summary> 
	///Mark Entity for deletion
	///</summary>
	void Remove();
	///<summary> 
	///Get the point on the hull of the shape. 
	///The point is the farthest point in a given direction.
	///</summary>
	///<param name="Dir">Direction of Ray</param>
	///<returns>The farthest point on the hull of the shape</returns>
	virtual Physics::Vector Farthest_Point_In_Direction(Physics::Vector Dir) = 0;
	///<summary> 
	///Get the point on the hull of the shape. 
	///The point will be on a edge of the shape in a given direction 
	///</summary>
	///<param name="Dir">Direction of Ray</param>
	///<returns>The farthest point on the hull of the shape</returns>
	virtual Physics::Vector Farthest_Point(Physics::Vector Dir) = 0;
	///<summary> 
	///Set acceleration for this Entity
	///</summary>
	///<param name="Acc">New acceleration</param>
	void SetAcceleration(Physics::Vector Acc);
	///<summary> 
	///Set velocity for this Entity
	///</summary>
	///<param name="Vel">New velocity</param>
	void SetVelocity(Physics::Vector Vel);
	///<summary> 
	///Set position for this Entity
	///</summary>
	///<param name="Pos">New position</param>
	virtual void SetPosition(Physics::Vector Pos);	
	///<summary> 
	///Set size of this Entity
	///</summary>
	///<param name="size">New size</param>
	virtual void Scale(Physics::Vector size) = 0;
	///<summary> 
	///Translate position and vertices for this Entity
	///</summary>
	///<param name="Pos">The distance to the new position</param>
	virtual void Translate(Physics::Vector Pos);
	///<summary> 
	///Set all the Variables that are used when an Entity collides with another Entity
	///</summary>
	///<param name="object">Entity that this Entity is colliding with</param>
	///<param name="point">Point of collision</param>
	///<param name="normal">Normal at the point of collision</param>
	void SetCollisionDetails(Base_Shape* object,Physics::Vector point, Physics::Vector normal);
	///<summary> 
	///Set Height Map Node that this Entity is on
	///</summary>
	///<param name="Node">Height Map Node</param>
	void SetHM_Node(HM_Node* Node);
	///<summary> 
	///Rotates Entity to new rotation given an angle and the axis of rotation
	///</summary>
	///<param name="axis">Axis that the Entity will rotate around</param>
	///<param name="angle">The angle that the Entity will rotate to</param>
	///<param name="IsLocal">If local roation or global rotation (Default : true)</param>
	virtual void Rotate(Physics::Vector axis, float angle,bool IsLocal = true);
	///<summary> 
	///Rotates Entity to new rotation given a Matrix
	///</summary>
	///<param name="matrix">Matrix used to rotate</param>
	virtual void Rotate(Physics::Matrix matrix);
	///<summary> 
	///Rotates Entity to face a direction
	///</summary>
	///<param name="Target_Direction">Entity will rotate to this vector</param>
	///<param name="IsLocal">If local roation or global rotation (Default : true)</param>
	virtual void Rotate_To_Direction(Physics::Vector Target_Direction,bool IsLocal = true);
	///<summary> 
	///Method called on each frame of the Programe.
	///</summary>
	///<param name="timesincelastframe">Time since last called</param>
	virtual void Update(float timesincelastframe);
	///<summary> 
	///Check if a point is inside the Entity
	///</summary>
	///<param name="point">The position of the point that is being checked</param>
	///<returns>If the point is inside the Entity</returns>
	virtual bool CheckPoint(Physics::Vector point) = 0;
	///<summary> 
	///Check if the Ray hits this Entity
	///</summary>
	///<param name="ray">Ray details</param>
	///<returns>New distance of the Ray</returns>
	virtual float CheckRay(Ray ray) = 0;
};

#endif