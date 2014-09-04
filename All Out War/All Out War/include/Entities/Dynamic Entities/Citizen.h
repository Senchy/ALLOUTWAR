#ifndef CITIZEN_H
#define CITIZEN_H

#include "Entities\Dynamic Entities\Dynamic_Ent.h"
#include "Entities\Base_Animation.h"
#include "Physics\Shape_Cylinder.h"

class Citizen : public Base_Animation , public Cylinder, public Dynamic_Ent
{
private:
protected:
public:
	///<summary> 
	///Constructor
	///</summary>
	///<param name="position">Position of the Entity</param>
	///<param name="manager">Ogre scene manager</param>
	Citizen(Physics::Vector position, Ogre::SceneManager* manager);
	///<summary> 
	///Destructor
	///</summary>
	virtual ~Citizen();
	///<summary> 
	///Mark this Entity to be Delete.
	///Execute code used when this entity Dies.
	///</summary>
	virtual void Kill();
	///<summary> 
	///Method called on each frame of the Programe.
	///</summary>
	///<param name="timesincelastframe">Time since last called</param>
	virtual void Update(float timesincelastframe);
	///<summary> 
	///Set the Path and Move to Position of this Entity
	///</summary>
	///<param name="Pos">Position that the Entity is Set to Move To</param>
	///<param name="Path">The Path to the Move to Position</param>
	virtual void SetMove(Physics::Vector Pos, LinkList<Graph_Node* > *Path);
	///<summary> 
	///Get the position of the physics object of this Entity
	///</summary>
	///<returns>position of the Entity</returns>
	virtual Physics::Vector GetPosition();
	///<summary> 
	///Get the position that the Entity is moving to
	///</summary>
	///<returns>The position that this Entity is moving to</returns>
	Physics::Vector GetMoveToPos();
	///<summary> 
	///Rotate the Entity around an axis by a given angle
	///</summary>
	///<param name="axis">Axis of rotation</param>
	///<param name="angle">Angle of rotation</param>
	///<param name="IsLocal">Is it a local rotation(Default : True)</param>
	virtual void Rotate(Physics::Vector axis, float angle,bool IsLocal = true);
	///<summary> 
	///Rotate the Entity to a given direction
	///</summary>
	///<param name="Target_Direction">Direction that the Entity is rotated to</param>
	///<param name="IsLocal">Is it a local rotation(Default : True)</param>
	virtual void Rotate_To_Direction(Physics::Vector Target_Direction,bool IsLocal = true);
};
#endif