#include "Entities\Static Entities\Town_Center.h"

Town_Center::Town_Center(Physics::Vector position, Ogre::SceneManager* manager,HM_Node* Node,Graph_Node** graph_nodes)
	:	Base_Animation( Ogre::Vector3(position.x, position.y, position.z)
						, manager
						, "cube.mesh"
						, Ogre::Vector3(40, 20, 40))
	,	Square(	position
				, Physics::Vector(40, 20, 40)
				, Entity_Name::town_center
				, GetAnimationEntNumber())
	,	Static_Ent(GetAnimationEntNumber())
{
	/**< reset the Y position to the Ground Y position */
	Base_Shape::SetCornerNodes(graph_nodes);
	Base_Animation::SetMaterial("Examples/Rockwall");
	SetHM_Node(Node);
	HM_Plane* plane = mHeightMap_Node->GetTriangle(mPosition);
	float newYpos = mFormula->PLANE_GetHeight(plane->GetNormal(), plane->GetVertices(0), mPosition) + 6;
	Square::SetPosition(Physics::Vector(GetPosition().x ,newYpos, GetPosition().z));
}
Town_Center::~Town_Center()
{
}
void Town_Center::Update(float timesincelastframe)
{
	Square::Update(timesincelastframe);
	Base_Animation::SetPosition(mPosition);
	mCollidionObject = 0;
}
void Town_Center::Rotate(Physics::Vector axis, float angle,bool IsLocal)
{
	Base_Animation::SetOrientation(axis,angle);
	Square::Rotate(axis,angle);
}
void Town_Center::Rotate_To_Direction(Physics::Vector Target_Direction,bool IsLocal)
{
	/**< Convert to quaternion to rotate the Ogre Mesh */
	Ogre::Vector3 Ogre_currentdir = Ogre::Vector3(mDirection.x,mDirection.y, mDirection.z);
	Ogre::Vector3 Ogre_Targetdir = Ogre::Vector3(Target_Direction.x,Target_Direction.y,Target_Direction.z);
	Ogre::Quaternion quat = Ogre_currentdir.getRotationTo(Ogre_Targetdir);
	Base_Animation::SetOrientation(quat);
	Square::Rotate_To_Direction(Target_Direction);
}
void Town_Center::Kill()
{
	mDead = true;
}
Physics::Vector Town_Center::GetPosition()
{
	return Square::GetPosition();
}