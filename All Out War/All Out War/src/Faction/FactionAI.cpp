#include "Faction\FactionAI.h"

FactionAI::FactionAI()
	: Faction()
{
}
FactionAI::~FactionAI()
{
}
bool FactionAI::Update(float timesincelastframe)
{
	Faction::Update(timesincelastframe);
	return true;
}