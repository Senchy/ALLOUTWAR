#include "Entities\Dynamic Entities\Citizen.h"

Citizen::Citizen(Physics::Vector position, Ogre::SceneManager* manager)
	:	Base_Animation(	Ogre::Vector3(position.x, position.y, position.z)
						, manager
						, "Barrel.mesh"
						, Ogre::Vector3(4,6,4))
	,	Cylinder(	position
				,	6
				,	2
				,	Entity_Name::citizen
				,	GetAnimationEntNumber())
	,	Dynamic_Ent(GetAnimationEntNumber())
{

}
Citizen::~Citizen()
{
}
void Citizen::SetMove(Physics::Vector Pos, LinkList<Graph_Node* > *Path)
{
	Dynamic_Ent::SetMove(Pos,Path);
}
void Citizen::Update(float timesincelastframe)
{
	/**< Call Base function */
	/**< set the Ogre Mesh position to the position of the Entity */
	/**< Get new velocity from Base Dynamic Entity */
	Cylinder::Update(timesincelastframe);
	Base_Animation::SetPosition(mPosition);
	Physics::Vector newvel = Dynamic_Ent::Update(mPosition);
	mVelocity = Physics::Vector(newvel.x, mVelocity.y, newvel.z);
	/**< Reset variables that need to be reset */
	mIsOnGround = false;
	mAcceleration = Physics::Vector(0,0,0);
	HM_Plane* plane = mHeightMap_Node->GetTriangle(mPosition);
	/**< Get distance from the ground */
	float distfromplane = mFormula->PLANE_IsOnDifference(plane->GetNormal(), plane->GetVertices(0), mPosition);
	/**< If on the Ground make sure the Y value of the Entity isnt underground */
	/**< Get the speed of the Entity from the height map node that the Entity is on */
	/**< Calculate new velocity */
	if(distfromplane < 3)
	{
		mIsOnGround = true;
		float newYpos = mFormula->PLANE_GetHeight(plane->GetNormal(), plane->GetVertices(0), mPosition) + 3;
		Cylinder::SetPosition(Physics::Vector(GetPosition().x ,newYpos, GetPosition().z));
		mSpeed = plane->GetSpeed(mDirection,mHeightMap_Node->GetDampener(mPosition),6);
		if(mSpeed == 0)
		{
			mAcceleration += plane->GetSlopeAcceleration();
			mVelocity = Physics::Vector(plane->GetNormal().x * 6 , mVelocity.y, plane->GetNormal().z * 6);
		}
	}
	/**< If this Entity is colliding with something push it back the opposite way */
	if(mCollidionObject)
	{
		Cylinder::Translate(mCollisionNormal * 6 * timesincelastframe);
	}
	/**< If not on ground add gravity to the acceleration */
	/**< Rotate to the velocity */
	mAcceleration += mFormula->GetGravity(!mIsOnGround);
	Cylinder::Rotate_To_Direction(Physics::Vector(mVelocity.x, 0, mVelocity.z).Normalise_copy());
	mCollidionObject = 0;
}
void Citizen::Rotate(Physics::Vector axis, float angle,bool IsLocal)
{
	Cylinder::Rotate(axis,angle);
	Base_Animation::SetOrientation(axis,angle);
}
void Citizen::Rotate_To_Direction(Physics::Vector Target_Direction,bool IsLocal)
{
	/**< Convert to quaternion to rotate the Ogre Mesh */
	Ogre::Vector3 Ogre_currentdir = Ogre::Vector3(mDirection.x,mDirection.y, mDirection.z);
	Ogre::Vector3 Ogre_Targetdir = Ogre::Vector3(Target_Direction.x,Target_Direction.y,Target_Direction.z);
	Ogre::Quaternion quat = Ogre_currentdir.getRotationTo(Ogre_Targetdir);
	Base_Animation::SetOrientation(quat);
	Cylinder::Rotate_To_Direction(Target_Direction);
}
Physics::Vector Citizen::GetMoveToPos()
{
	/**< If there are Nodes on the path get the first Nodes position*/
	if (mPath->GetSize() > 0)
	{
		return mPath->At(0)->GetPosition();
	}
	return 0;
}
void Citizen::Kill()
{
	mDead = true;
}
Physics::Vector Citizen::GetPosition()
{
	return Cylinder::GetPosition();
}