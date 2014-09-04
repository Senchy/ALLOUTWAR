#ifndef FACTION_H
#define FACTION_H

#include "LinkList.h"
#include "Entity_Factory.h"
#include "ContainerStructs.h"

class Faction
{
protected:
	/// <value>What units this faction is currently controling</value>
	LinkList<Base_Ent *>	mSelectedEntities;
	/// <value>List of Units that this Faction owns</value>
	LinkList<Base_Ent *>	mUnits;
	/// <value>List of buildings that this Faction owns</value>
	LinkList<Base_Ent *>	mBuildings;
	/// <value>Pointer to the entity factory</value>
	Entity_Factory*			mFactory;
public:
	///<summary> 
	///Constructor
	///</summary>
	Faction();
	///<summary> 
	///Destructor
	///</summary>
	~Faction();
	///<summary> 
	///Method called on each frame of the Programe.
	///</summary>
	///<param name="timesincelastframe">Time since last called</param>
	virtual bool Update(float timesincelastframe);
};

#endif