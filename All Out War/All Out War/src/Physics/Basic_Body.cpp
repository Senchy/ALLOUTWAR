#include "Physics\Basic_Body.h"

///// Initialisation /////
//////////////////////////
Base_Shape::Base_Shape(Physics::Vector pos, int type,Entity_Name Entity_Type ,int entnumber)
	:	mEntity_Type(Entity_Type),
		mPosition(pos), 
		mType(type),
		mAcceleration(Physics::Vector(0)),
		mVelocity(Physics::Vector(0)),
		mDirection(Physics::Vector(1,0,0)),
		mUp(Physics::Vector(0,1,0)),
		mLastTranslation(0),
		mCollidionObject(0),
		mCollisionPoint(0),
		mDead(false),
		mNodes(0),
		mEntNumber(entnumber)
{
	mFormula = Physics_Formulas::getInstance();
}
Base_Shape::~Base_Shape()
{
}

int Base_Shape::GetEntityNumber()
{
	return mEntNumber;
}
void Base_Shape::Remove()
{
	mDead = true;
}
float Base_Shape::GetBoundingRadius()
{
	return mBoundingRadius;
}
int Base_Shape::GetType()
{
	return mType;
}
Entity_Name	Base_Shape::GetEntityType()
{
	return mEntity_Type;
}
Physics::Vector Base_Shape::GetPosition()
{
	return mPosition;
}
Physics::Vector Base_Shape::GetVelocity()
{
	return mVelocity;
}
Physics::Vector Base_Shape::GetAcceleration()
{
	return mAcceleration;
}
Physics::Vector Base_Shape::GetDirection()
{
	return mDirection;
}
bool Base_Shape::IsDead()
{
	return mDead;
}
void Base_Shape::Translate(Physics::Vector Pos)
{
	mPosition = Pos;
}
Graph_Node** Base_Shape::GetCornerNodes()
{
	return mNodes;
}
void Base_Shape::SetCornerNodes(Graph_Node** nodes)
{
	mNodes = nodes;
}

void Base_Shape::SetAcceleration(Physics::Vector Acc)
{
	mAcceleration = Acc;
}
void Base_Shape::SetVelocity(Physics::Vector Vel)
{
	mVelocity = Vel;
}
void Base_Shape::SetPosition(Physics::Vector Pos)
{
	mPosition = Pos;
}
void Base_Shape::SetCollisionDetails(Base_Shape* object,Physics::Vector point, Physics::Vector normal)
{
	mCollidionObject = object;
	mCollisionPoint = point;
	mCollisionNormal = normal;
}
void Base_Shape::SetHM_Node(HM_Node* Node)
{
	mHeightMap_Node = Node;
}
void Base_Shape::Rotate(Physics::Vector axis, float angle,bool IsLocal)
{
	mDirection = mDirection.Rotate_by_axis(axis,angle);
	mUp = mUp.Rotate_by_axis(axis,angle);
}
void Base_Shape::Rotate(Physics::Matrix matrix)
{
	mDirection = mDirection * matrix;
	mUp = mUp * matrix;
}
void Base_Shape::RotatetoNormal(Physics::Vector Normal)
{
	mDirection = mDirection * mFormula->Get_Rotate_To_Direction(mUp,Normal);
	mUp = Normal;
}
void Base_Shape::Rotate_To_Direction(Physics::Vector Target_Direction,bool IsLocal)
{
	mUp = mUp * mFormula->Get_Rotate_To_Direction(mDirection,Target_Direction);
	mDirection = Target_Direction;
}

void Base_Shape::Update(float timesincelastframe)
{
	/**<  call New_Velocity to get new velocity */
	mVelocity += mFormula->New_Velocity(mVelocity,mAcceleration,timesincelastframe);
	/**<  call New_Position to get new positin and the translation to get the amount we need to translate the points of the body */
	mLastTranslation = mFormula->New_Position(mPosition,mVelocity,mAcceleration,timesincelastframe);
}