#ifndef STATIC_ENT_H
#define STATIC_ENT_H

#include "Entities\Base_Ent.h"
#include "AI\Graph.h"

class Static_Ent : public Base_Ent
{
private:
protected:
public:
	///<summary> 
	///Constructor
	///</summary>
	///<param name="entnumber">Unique Enity number</param>
	Static_Ent(int entnumber);
	///<summary> 
	///Destructor
	///</summary>
	virtual ~Static_Ent();
	///<summary> 
	///Mark this Entity to be Delete.
	///Execute code used when this entity Dies.
	///</summary>
	virtual void Kill() = 0;
	///<summary> 
	///Interface Method for getting the position of the physics object of this Entity
	///</summary>
	///<returns>position of the Entity</returns>
	virtual Physics::Vector GetPosition() = 0;
};

#endif