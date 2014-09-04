#include "Entities\Static Entities\Tree.h"

Tree::Tree(Physics::Vector position, Ogre::SceneManager* manager,LinkList<MakeEntity_Node *>* createlist,HM_Node* Node)
	:	Base_Animation(Ogre::Vector3(position.x, position.y, position.z)
						, manager
						, "Barrel.mesh"
						, Ogre::Vector3(0.5,6,0.5))
	,	Cylinder(position
				, 6
				, 0.25
				, Entity_Name::tree
				, GetAnimationEntNumber())
	,	Static_Ent(GetAnimationEntNumber())
	,	mCurrentScale(0.25,6,0.25)
	,	mTimeAlive(1.0f)
	,	mStage(TreeStage::Sapling)
	,	mCreate_List(createlist)
	,	mTreeCreated(false)
{
	/**< reset the Y position to the Ground Y position */
	Base_Animation::SetMaterial("Examples/Chrome");
	mCManager = Collision_Manager::getInstance();
	Base_Shape::SetHM_Node(Node);
	HM_Plane* plane = mHeightMap_Node->GetTriangle(mPosition);
	float newYpos = mFormula->PLANE_GetHeight(plane->GetNormal(), plane->GetVertices(0), mPosition) + 1;
	Cylinder::SetPosition(Physics::Vector(GetPosition().x ,newYpos, GetPosition().z));
	srand(time(0));
}
Tree::~Tree()
{
}
bool Tree::PlantSeed()
{
	/**< Get random position to plant the next seed that is at least 7 units away */
	float xpos = rand() % 15 + 7;
	float zpos = rand() % 15 + 7;
	/**< If X or Y will be Negitive */
	float getposornegX = rand() % 2;
	float getposornegZ = rand() % 2;
	if(getposornegX == 1) { xpos *= -1;}
	if(getposornegZ == 1) { zpos *= -1;}
	Physics::Vector newPosition = GetPosition() + Physics::Vector(xpos, 0, zpos);
	/**< If position is free to create a new Tree */
	/**< Put tree on the list to be created by the Entity Factory */
	if(!mCManager->Check_Proximity(newPosition, 8))
	{
		MakeEntity_Node* node =  new MakeEntity_Node();
		node->mPosition = newPosition;
		node->mType = Entity_Name::tree;
		mCreate_List->Push_Back(node);
		return true;
	}
	return false;
}
bool Tree::Grow(Physics::Vector size, float tall)
{
	/**< If the Tree is as tall as we wan it to be Stop scaling up */
	if(mCurrentScale.y > tall)	{ return true; }
	/**< Scale tree to make it bigger */
	mCurrentScale = Physics::Vector(mCurrentScale.x + size.x,mCurrentScale.y + size.y, mCurrentScale.z + size.z);
	Cylinder::Translate(Physics::Vector(0,size.y/2,0));
	Cylinder::Scale(mCurrentScale);
	Base_Animation::Scale(Physics::Vector(mCurrentScale.x * 2,mCurrentScale.y,mCurrentScale.z * 2));
	return false;
}
void Tree::Update(float timesincelastframe)
{
	mTimeAlive += timesincelastframe;
	int seedtime = mTimeAlive;
	/**< What stage of Life the Tree is at */
	/**< Based on time grow to next stage and create new Trees around this Tree */
	switch(mStage)
	{
	case(TreeStage::Sapling):
		if(mTimeAlive > 120)
		{
			if(Grow(Physics::Vector(0.0025,0.08,0.0025),14))
			{
				mStage = TreeStage::Small;
			}
		}
		break;
	case(TreeStage::Small):
		if(mTimeAlive > 270)
		{
			if(Grow(Physics::Vector(0.0025,0.08,0.0025),20))
			{
				mStage = TreeStage::Normal;
			}
		}
		break;
	case(TreeStage::Normal):
		if(seedtime %  50 == 0)
		{
			if(mTreeCreated == false)
			{
				mTreeCreated = PlantSeed();
			}
		}
		else
		{
			mTreeCreated = false;
		}
		if(mTimeAlive > 720)
		{
			if(Grow(Physics::Vector(0.0015,0.08,0.0015),30))
			{
				mStage = TreeStage::Giant;
			}
		}
		break;
	case(TreeStage::Giant):
		if(seedtime %  50 == 0)
		{
			if(mTreeCreated == false)
			{
				mTreeCreated = PlantSeed();
			}
		}
		else
		{
			mTreeCreated = false;
		}
		break;
	};
	Cylinder::Update(timesincelastframe);
	Base_Animation::SetPosition(mPosition);
	mCollidionObject = 0;
}
void Tree::Rotate(Physics::Vector axis, float angle,bool IsLocal)
{
	Cylinder::Rotate(axis,angle);
	Base_Animation::SetOrientation(axis,angle);
}
void Tree::Rotate_To_Direction(Physics::Vector Target_Direction,bool IsLocal)
{
	/**< Convert to quaternion to rotate the Ogre Mesh */
	Ogre::Vector3 Ogre_currentdir = Ogre::Vector3(mDirection.x, mDirection.y, mDirection.z);
	Ogre::Vector3 Ogre_Targetdir = Ogre::Vector3(Target_Direction.x,Target_Direction.y,Target_Direction.z);
	Ogre::Quaternion quat = Ogre_currentdir.getRotationTo(Ogre_Targetdir);
	Base_Animation::SetOrientation(quat);
	Cylinder::Rotate_To_Direction(Target_Direction);
}
void Tree::Kill()
{
	mDead = true;
}
Physics::Vector Tree::GetPosition()
{
	return Cylinder::GetPosition();
}
