#include "Faction\GUI\GUI_Items\Panel.h"

Panel::Panel(Ogre::String Name, Ogre::String materialname,Ogre::Vector2 screensize)
	: Base_GUI( Name
				, materialname
				, 550
				, Ogre::Vector2(0.5,0.5)
				, Ogre::Vector2(100,100)
				, screensize)
{
}
Panel::~Panel()
{
}
void Panel::Update()
{
}
bool Panel::Clicked(Ogre::Vector2 Pos)
{
	return false;
}
void Panel::Release()
{
}