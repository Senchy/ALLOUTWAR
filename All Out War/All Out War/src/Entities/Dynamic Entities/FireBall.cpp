#include "Entities\Dynamic Entities\FireBall.h"

FireBall::FireBall(Physics::Vector position, Ogre::SceneManager* manager)
		:	Base_Animation( Ogre::Vector3(position.x,position.y,position.z)
							, manager
							, "sphere.mesh"
							, Ogre::Vector3(6,6,6))
		,	Sphere(	position
					,3
					,Entity_Name::fireball
					,GetAnimationEntNumber())
		,	Dynamic_Ent(GetAnimationEntNumber())
{
}
FireBall::~FireBall()
{
}
void FireBall::Update(float timesincelastframe)
{
	
	/**< Needs to been changed */
	if(mPosition.y <= GetBoundingRadius())
	{
		mVelocity.y = 0;
		mAcceleration.y = 0;
	}
	Sphere::Update(timesincelastframe);
	Base_Animation::SetPosition(mPosition);
	if(mCollidionObject != 0)
	{
		Sphere::SetPosition(GetPosition() - (GetVelocity()/ 4));
		Sphere::SetVelocity(-GetVelocity());
		Sphere::SetAcceleration(-GetAcceleration());
	}
	mCollidionObject = 0;
}
void FireBall::Rotate(Physics::Vector axis, float angle,bool IsLocal)
{
	Sphere::Rotate(axis,angle);
	Base_Animation::SetOrientation(axis,angle);
}
void FireBall::Rotate_To_Direction(Physics::Vector Target_Direction,bool IsLocal)
{
	/**< Convert to quaternion to rotate the Ogre Mesh */
	Ogre::Vector3 Ogre_currentdir = Ogre::Vector3(mDirection.x,mDirection.y, mDirection.z);
	Ogre::Vector3 Ogre_Targetdir = Ogre::Vector3(Target_Direction.x,Target_Direction.y,Target_Direction.z);
	Ogre::Quaternion quat = Ogre_currentdir.getRotationTo(Ogre_Targetdir);
	Base_Animation::SetOrientation(quat);
	Sphere::Rotate_To_Direction(Target_Direction);
}
void FireBall::Kill()
{
	mDead = true;
}
Physics::Vector FireBall::GetPosition()
{
	return Sphere::GetPosition();
}
