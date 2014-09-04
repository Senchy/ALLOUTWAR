#ifndef BASE_ANIMATION_H
#define BASE_ANIMATION_H

#include "BaseApplication.h"
#include "Physics\Physics_Formulas.h"

class Base_Animation
{
private:
	/// <value>The unique number for the Entity</value>
	const unsigned				mEntNumber;
	/// <value>Pointer to Ogre scene Manager</value>
	Ogre::SceneManager*			mManager;
	/// <value>Pointer to an Ogre scene Node</value>
	Ogre::SceneNode*			mOGRE_Node;
	/// <value>Pointer to an Ogre Entity</value>
	Ogre::Entity*				mOGRE_Object;
protected:
	///<summary> 
	///Set the Position of the Entity
	///</summary>
	///<param name="Pos">New Position</param>
	void SetPosition(Physics::Vector Pos);
	///<summary> 
	///Rotate Entity around an axis by an angle
	///</summary>
	///<param name="axis">Axis of Rotation</param>
	///<param name="angle">Angle used to Rotate</param>
	void SetOrientation(Physics::Vector axis, float angle);
	///<summary> 
	///Rotate the Entity by a given quaternion
	///</summary>
	///<param name="quat">Rotation quaternion</param>
	void SetOrientation(Ogre::Quaternion quat);
	///<summary> 
	///Set the Size of the Entity
	///</summary>
	///<param name="size">New sclae</param>
	void Scale(Physics::Vector size);
	///<summary> 
	///Change the material of the Entity
	///</summary>
	///<param name="nameofmat">Name of the new material</param>
	void SetMaterial(Ogre::String nameofmat);
public:
	///<summary> 
	///Constructor
	///</summary>
	///<param name="position">Position of the Entity</param>
	///<param name="manager">Pointer to the Ogre Scene Manager</param>
	///<param name="meshname">Name of the Material for this Entity</param>
	///<param name="size">The size of this Entity</param>
	Base_Animation(Ogre::Vector3 position, Ogre::SceneManager* manager, std::string meshname, Ogre::Vector3 size);
	///<summary> 
	///Destructor
	///</summary>
	virtual ~Base_Animation();
	///<summary> 
	///Method called on each frame of the Programe.
	///</summary>
	virtual void Update();
	///<summary> 
	///Get the unique number for this entity
	///</summary>
	///<returns>Entity Number</returns>
	int GetAnimationEntNumber();
};
/// <value>Counter incremented each time a Entity is created and used to set the Entity Number</value>
static int Entity_Number = 0;
#endif