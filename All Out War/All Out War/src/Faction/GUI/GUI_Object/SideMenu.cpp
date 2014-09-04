#include "Faction\GUI\GUI_Object\SideMenu.h"

SideMenu::SideMenu(Ogre::String Name, Ogre::String materialname,float ButtonPosy,Ogre::Vector2 screensize)
	:	Table(	Name
				, materialname 
				, Ogre::Vector2(1.0, 0)
				, Ogre::Vector2(((screensize.x/16) * 4), ((screensize.y/9) * 6))
				, screensize)
	,	mOpenMenu(Name + "OpenButton" 
				, "AOW/LeftButton"
				, "AOW/RightButton"
				, 300 
				, Ogre::Vector2((1.0f - (40.0f / screensize.x)),(ButtonPosy / screensize.y))
				, Ogre::Vector2(40,50)
				, screensize)
	,	mXposition(1.0)
	,	mYbuttonPos(ButtonPosy)
	,	mSlideLimit(1.0f - (float((screensize.x/16) * 3.9) / screensize.x))
{
}
SideMenu::~SideMenu()
{
}
void SideMenu::Update()
{
	/**< If the Button is Down move the Menu to the side of the Screen */
	if(mOpenMenu.IsDown())
	{
		if(mXposition < 1)
		{
			Move(Ogre::Vector2(0.01,0));
		}
	}/**< If the Button is Up move the Menu out to the middle of the Screen */
	else
	{
		if(mXposition >= mSlideLimit)
		{
			Move(Ogre::Vector2(-0.01,0));
		}
	}
}
bool SideMenu::Clicked(Ogre::Vector2 Pos)
{
	/**< Check if Button or Table has been pressed */
	if(mOpenMenu.Clicked( Pos) 
		|| Table::Clicked( Pos))
	{
		return true;
	}
	return false;
}
void SideMenu::Release()
{
	mOpenMenu.Release();
}
void SideMenu::SetPosition(Ogre::Vector2 Pos)
{
	/**< Set the Button position the the Entitys position */
	mXposition = Pos.x;
	mOpenMenu.SetPosition(Ogre::Vector2(Pos.x - mScreenSize.x/30,Pos.y - mYbuttonPos));
	Table::SetPosition(Pos);
}
void SideMenu::Move(Ogre::Vector2 Distance)
{
	/**< Move Button and Table the given distance in the X axis */
	mXposition += Distance.x;
	mOpenMenu.Move(Distance);
	Table::Move(Distance);
}