#ifndef CONTAINERSTRUCTS_H
#define CONTAINERSTRUCTS_H

#include "Physics\Physics_Formulas.h"
#include "LinkList.h"

enum GroundType
{
	Long_Grass,
	Short_Grass,
	Rocky_Grass,
	Mud_Grass,
	Mud,
	Swamp_Grass,
	Swamp,
	Light_Forrest,
	Dense_Forrest,
	Beach_Sand,
	Desert_Sand,
	Desert_Plain,
	Rocky_Sand,
	Sea_Shore,
	Deep_Sea,
	River_Bank,
	Stream,
	River,
	River_Rapids
};
enum Entity_Name
{
	citizen,
	town_center,
	tree,
	fireball,
	None
};
enum ClickType
{
	Move,
	Enemy,
	Friendly,
	GUI,
	Default
};
struct Ray
{
	Physics::Vector mStartPosition;
	Physics::Vector mDirection;
	float			mDistance;
};
struct MakeEntity_Node
{
	Physics::Vector mPosition;
	Entity_Name		mType;
};

#endif