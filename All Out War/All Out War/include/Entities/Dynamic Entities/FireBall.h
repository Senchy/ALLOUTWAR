#ifndef FIREBALL_H
#define FIREBALL_H

#include "Entities\Dynamic Entities\Dynamic_Ent.h"
#include "Entities\Base_Animation.h"
#include "Physics\Shape_Sphere.h"

class FireBall : public Dynamic_Ent , public Sphere, public Base_Animation
{
private:
protected:
public:
	///<summary> 
	///Constructor
	///</summary>
	///<param name="position">Position of the Entity</param>
	///<param name="manager">Ogre scene manager</param>
	FireBall(Physics::Vector position, Ogre::SceneManager* manager);
	///<summary> 
	///Destructor
	///</summary>
	virtual ~FireBall();
	///<summary> 
	///Mark this Entity to be Delete.
	///Execute code used when this entity Dies.
	///</summary>
	virtual void Kill();
	///<summary> 
	///Method called on each frame of the Programe.
	///</summary>
	///<param name="timesincelastframe">Time since the last called</param>
	virtual void Update(float timesincelastframe);	///<summary> 
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