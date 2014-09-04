#ifndef DYNAMIC_ENT_H
#define DYNAMIC_ENT_H

#include "Entities\Base_Ent.h"
#include "AI\Graph_Node.h"

class Dynamic_Ent : public Base_Ent
{
private:
protected:
	/// <value>The position that the Entity need to get too</value>
	Physics::Vector mMovePosition;
	/// <value>List of points that when full traversed brings the Entity to the Move Position</value>
	LinkList<Graph_Node* > *mPath;
	/// <value>Does the Entity have a Position to move to</value>
	bool			mMove;
	/// <value>The speed that the Entity moves at</value>
	float			mSpeed;
	/// <value>If the Entity is on the Ground</value>
	bool			mIsOnGround;
public:

	///<summary> 
	///Constructor
	///</summary>
	///<param name="entnumber">Unique Enity number</param>
	Dynamic_Ent(int entnumber);
	///<summary> 
	///Destructor
	///</summary>
	virtual ~Dynamic_Ent();
	///<summary> 
	///Mark this Entity to be Delete.
	///Execute code used when this entity Dies.
	///</summary>
	virtual void Kill() = 0;
	///<summary> 
	///Finds the new velocity based on the position and
	///path that the entity is set to moving to.
	///</summary>
	///<param name="Position">Position of the Entity</param>
	///<returns>New Velocity</returns>
	Physics::Vector Update(Physics::Vector Position);
	///<summary> 
	///Set the Path and Move to Position of this Entity
	///</summary>
	///<param name="Pos">Position that the Entity is Set to Move To</param>
	///<param name="Path">The Path to the Move to Position</param>
	virtual void SetMove(Physics::Vector Pos, LinkList<Graph_Node* > *Path);
	///<summary> 
	///Interface Method for getting the position of the physics object of this Entity
	///</summary>
	///<returns>position of the Entity</returns>
	virtual Physics::Vector GetPosition() = 0;
};

#endif