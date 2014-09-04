#ifndef FACTIONAI_H
#define FACTIONAI_H
#include "Faction\Faction.h"
class FactionAI : public Faction
{
protected:
public:
	///<summary> 
	///Constructor
	///</summary>
	FactionAI();
	///<summary> 
	///Destructor
	///</summary>
	~FactionAI();
	///<summary> 
	///Method called on each frame of the Programe.
	///</summary>
	///<param name="timesincelastframe">Time since last called</param>
	virtual bool Update(float timesincelastframe);
};

#endif