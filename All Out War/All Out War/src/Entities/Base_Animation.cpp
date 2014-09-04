#include "Entities\Base_Animation.h"

Base_Animation::Base_Animation(Ogre::Vector3 position, Ogre::SceneManager* manager, std::string meshname, Ogre::Vector3 size)
	:	mManager(manager)
	,	mEntNumber(Entity_Number)
{
	/**< Turn unique number into a string */
	std::ostringstream Stream;
	Stream << mEntNumber;
	std::string SceneName = "Object";
	std::string EntityName = "ObjectEntity";
	SceneName += Stream.str();
	EntityName += Stream.str();
	/**< Create new Ogre Entity with unique number */
	mOGRE_Object = mManager->createEntity(EntityName, meshname);
	mOGRE_Object->setCastShadows(false);
	/**< Add Node and Entity to the Scene */
	mOGRE_Node = mManager->getRootSceneNode()->createChildSceneNode(SceneName);
	/**< Scale Entity and set position */
	mOGRE_Node->setScale(size.x / mOGRE_Object->getBoundingBox().getSize().x,
		size.y / mOGRE_Object->getBoundingBox().getSize().y, size.z / mOGRE_Object->getBoundingBox().getSize().z);
	mOGRE_Node->setPosition(position);
	mOGRE_Node->setOrientation(Ogre::Quaternion(Ogre::Radian(0),Ogre::Vector3(0,1,0)));
	mOGRE_Node->attachObject(mOGRE_Object);
	Entity_Number++;
}
Base_Animation::~Base_Animation()
{
	mManager->destroyEntity(mOGRE_Object);
	mManager->destroySceneNode(mOGRE_Node);
}
void Base_Animation::SetPosition(Physics::Vector Pos)
{
	mOGRE_Node->setPosition(Ogre::Vector3(Pos.x,Pos.y,Pos.z));
}
void Base_Animation::SetOrientation(Physics::Vector axis, float angle)
{
	mOGRE_Node->rotate(Ogre::Vector3(axis.x,axis.y,axis.z),Ogre::Radian(Ogre::Degree(angle)),Ogre::Node::TS_WORLD);
}
void Base_Animation::SetOrientation(Ogre::Quaternion quat)
{
	mOGRE_Node->rotate(quat);
}
void Base_Animation::SetMaterial(Ogre::String nameofmat)
{
	mOGRE_Object->setMaterialName(nameofmat);
}
void Base_Animation::Scale(Physics::Vector size)
{
	mOGRE_Node->setScale(size.x / mOGRE_Object->getBoundingBox().getSize().x,
		size.y / mOGRE_Object->getBoundingBox().getSize().y, size.z / mOGRE_Object->getBoundingBox().getSize().z);
}
void Base_Animation::Update()
{
}
int Base_Animation::GetAnimationEntNumber()
{
	return mEntNumber;
}