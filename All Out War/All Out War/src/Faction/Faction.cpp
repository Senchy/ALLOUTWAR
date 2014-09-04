#include "Faction\Faction.h"

Faction::Faction()
{
	mFactory = Entity_Factory::getInstance(0,0,0);
}
Faction::~Faction()
{
}
bool Faction::Update(float timesincelastframe)
{
	return true;
}