#include "Faction\GUI\GUI_Object\MiniMap.h"

MiniMap::MiniMap(Ogre::String Name, Ogre::String materialname,Ogre::Vector2 screensize)
	: Table(Name
			,materialname
			,Ogre::Vector2(1.0f - (float((screensize.x/32) * 32) / screensize.x), 1.0f - (float((screensize.y/18) * 5) / screensize.y))
			,Ogre::Vector2(((screensize.x/32) * 5), ((screensize.y/18) * 5))
			,screensize)
{
}
MiniMap::~MiniMap()
{
}
void MiniMap::Update()
{
}
bool MiniMap::Clicked(Ogre::Vector2 Pos)
{
	return Table::Clicked(Pos);
}
void MiniMap::Release()
{
}