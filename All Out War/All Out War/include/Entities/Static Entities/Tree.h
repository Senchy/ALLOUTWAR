#ifndef TREE_H
#define TREE_H

#include "Entities\Static Entities\Static_Ent.h"
#include "Entities\Base_Animation.h"
#include "Physics\Shape_Cylinder.h"
#include "Physics\Collisions_Manager.h"
#include <stdlib.h>
#include <time.h>

class Tree : public Static_Ent,  public Cylinder, public Base_Animation
{
private:
	/// <value>How long the Tree has been around</value>
	float									mTimeAlive;
	/// <value>If we created a Tree recently</value>
	bool									mTreeCreated;
	/// <value>The current size of the Tree</value>
	Physics::Vector							mCurrentScale;
	/// <value>Pointer to the only instance of collision manager</value>
	Collision_Manager*						mCManager;	
	/// <value>Pointer to a link list used to create new Entities</value>
	LinkList<MakeEntity_Node *>*			mCreate_List;
	/// <value>Different types of Trees based on how long the tree has been around</value>
	enum TreeStage
	{
		Sapling,
		Small,
		Normal,
		Giant,
	};
	/// <value>Current Tree Stage</value>
	TreeStage								mStage;
protected:
	///<summary> 
	///Find a place that a tree can be planted.
	///Make sure there are no trees near
	///</summary>
	bool PlantSeed();
	///<summary> 
	///Add to the Y scale of the Entity.
	///If the Entity is a given size return it has grow to full size
	///</summary>
	///<param name="size">The value that is added to the scale each frame</param>
	///<param name="tall">How tall the tree should get</param>
	///<returns>If the tree has grow fully</returns>
	bool Grow(Physics::Vector size, float tall);
public:
	///<summary> 
	///Constructor
	///</summary>
	///<param name="position">Position of the Entity</param>
	///<param name="manager">Ogre scene manager</param>
	///<param name="createlist">List used to create Entities</param>
	///<param name="Node">Height Map Node that this Entities is created on</param>
	Tree(Physics::Vector position, Ogre::SceneManager* manager,LinkList<MakeEntity_Node *>* createlist,HM_Node* Node);
	///<summary> 
	///Destructor
	///</summary>
	virtual ~Tree();
	///<summary> 
	///Mark this Entity to be Delete.
	///Execute code used when this entity Dies.
	///</summary>
	virtual void Kill();
	///<summary> 
	///Method called on each frame of the Programe.
	///</summary>
	///<param name="timesincelastframe">Time since the last called</param>
	virtual void Update(float timesincelastframe);
	///<summary> 
	///Get the position of the physics object of this Entity
	///</summary>
	///<returns>position of the Entity</returns>
	virtual Physics::Vector GetPosition();
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