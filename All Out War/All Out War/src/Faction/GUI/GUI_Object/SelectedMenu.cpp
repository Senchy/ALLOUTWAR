#include "Faction\GUI\GUI_Object\SelectedMenu.h"

SelectedMenu::SelectedMenu(Ogre::String Name, Ogre::String materialname,Ogre::Vector2 screensize)
	:	Table(Name
				,materialname
				,Ogre::Vector2(1.0f - (float((screensize.x/32) * 27) / screensize.x), 1.0f - (float((screensize.y/18) * 3) / screensize.y))
				,Ogre::Vector2(((screensize.x/32) * 21), ((screensize.y/18) * 3))
				,screensize)
{
}
SelectedMenu::~SelectedMenu()
{	
}
void SelectedMenu::Update()
{
}
bool SelectedMenu::Clicked(Ogre::Vector2 Pos)
{
	return Table::Clicked( Pos);
}
void SelectedMenu::Release()
{
}