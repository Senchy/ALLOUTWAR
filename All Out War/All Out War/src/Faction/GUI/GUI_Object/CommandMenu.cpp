#include "Faction\GUI\GUI_Object\CommandMenu.h"

CommandMenu::CommandMenu(Ogre::String Name, Ogre::String materialname,Ogre::Vector2 screensize)
	: Table( Name
			,materialname 
			,Ogre::Vector2(1.0f - (float((screensize.x/16) * 3) / screensize.x), 1.0f - (float((screensize.y/9) * 3) / screensize.y))
			,Ogre::Vector2(((screensize.x/16) * 3), ((screensize.y/9) * 3))
			,screensize)
{
}
CommandMenu::~CommandMenu()
{
}
void CommandMenu::Update()
{
}
bool CommandMenu::Clicked(Ogre::Vector2 Pos)
{
	return Table::Clicked( Pos);
}
void CommandMenu::Release()
{
}