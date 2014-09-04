#include "Faction\GUI\GUI_Items\ScrollBar.h"

ScrollBar::ScrollBar(Ogre::String Name, Ogre::String materialname,Ogre::Vector2 screensize)
	: Base_GUI( Name
				, materialname
				, 550
				, Ogre::Vector2(0.5,0.5)
				, Ogre::Vector2(100,100)
				, screensize)
{
}
ScrollBar::~ScrollBar()
{
}
void ScrollBar::Update()
{
}
bool ScrollBar::Clicked(Ogre::Vector2 Pos)
{
	return false;
}
void ScrollBar::Release()
{
}