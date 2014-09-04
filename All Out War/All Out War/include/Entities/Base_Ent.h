#ifndef BASE_ENT_H
#define BASE_ENT_H

#include "Physics\Physics_Formulas.h"

class Base_Ent
{
private:
	/// <value>The unique number for the Entity</value>
	const unsigned mEntNumber;
protected:
public:	
	///<summary> 
	///Constructor
	///</summary>
	///<param name="entnumber">Unique Entity number</param>
	Base_Ent(int entnumber);
	///<summary> 
	///Destructor
	///</summary>
	virtual ~Base_Ent();
	///<summary> 
	///Mark this Entity to be Delete.
	///Execute code used when this entity Dies.
	///</summary>
	virtual void Kill() = 0;
	///<summary> 
	///Get the unique number for this entity
	///</summary>
	///<returns>Entity Number</returns>
	int GetEntityNumber();
	///<summary> 
	///Interface Method for getting the position of the physics object of this Entity
	///</summary>
	///<returns>position of the Entity</returns>
	virtual Physics::Vector GetPosition() = 0;
};
#endif