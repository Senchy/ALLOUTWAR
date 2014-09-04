#include "Faction\GUI\GUI_Object\TownListInfo.h"
TownListInfo::TownListInfo(Ogre::String Name, Ogre::String materialname,Ogre::Vector2 screensize)
	:	SideMenu( Name
				, materialname
				, 0
				, screensize)
{
}
TownListInfo::~TownListInfo()
{
}
void TownListInfo::Update()
{
	SideMenu::Update();
}
bool TownListInfo::Clicked(Ogre::Vector2 Pos)
{
	return SideMenu::Clicked( Pos);
}
void TownListInfo::Release()
{
	SideMenu::Release();
}