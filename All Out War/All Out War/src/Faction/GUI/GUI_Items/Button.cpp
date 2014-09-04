#include "Faction\GUI\GUI_Items\Button.h"

Button::Button(Ogre::String Name, Ogre::String materialnameUp,Ogre::String materialnameDown,int Zbuff, Ogre::Vector2 Position, Ogre::Vector2 size,Ogre::Vector2 screensize, bool ReleaseUp)
	:	Base_GUI( Name
				, materialnameUp
				, Zbuff
				, Position
				, size
				, screensize)
	,	mIsDown(true)
	,	mReleaseUp(ReleaseUp)
	,	mUpMaterial(materialnameUp)
	,	mDownMaterial(materialnameDown)
{
}
Button::~Button()
{
}
void Button::Update()
{
}
bool Button::Clicked(Ogre::Vector2 Pos)
{
	/**< If click position is on Button */
	if(mGUI_Entity->getLeft() < Pos.x 
		&& (mGUI_Entity->getLeft() + mGUI_Entity->getWidth()) > Pos.x
		&&	mGUI_Entity->getTop() < Pos.y 
		&& (mGUI_Entity->getTop() + mGUI_Entity->getHeight()) > Pos.y)
	{
		/**< If a release Button set down true and set material to down material */
		if(mReleaseUp)
		{
			mIsDown = true;
			mGUI_Entity->setMaterialName(mDownMaterial);
		}/**< Check if its down if its down put it up or if its up put it down Set material accordingly */
		else
		{
			if(mIsDown)
			{
				mIsDown = false;
				mGUI_Entity->setMaterialName(mUpMaterial);
			}
			else
			{
				mIsDown = true;
				mGUI_Entity->setMaterialName(mDownMaterial);
			}
		}
		return true;
	}
	return false;
}
void Button::Release()
{
	/**< If a release Button set down false and set material to Up material */
	if(mReleaseUp)
	{
		mIsDown = false;
		mGUI_Entity->setMaterialName(mUpMaterial);
	}
}
void Button::SetPosition(Ogre::Vector2 Pos)
{
	Base_GUI::SetPosition(Pos);
}
void Button::Move(Ogre::Vector2 Distance)
{
	Base_GUI::Move(Distance);
}
bool Button::IsDown()
{
	return mIsDown;
}