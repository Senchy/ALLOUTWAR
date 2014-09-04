#include "Faction\GUI\GUI_Items\Cursor.h"

Cursor::Cursor(Ogre::String Name, Ogre::String materialname,Ogre::Vector2 screensize)
	:	Base_GUI(	Name
				,	materialname
				,	600
				,	Ogre::Vector2(0.5088, 0.5083)
				,	Ogre::Vector2(40,40)
				,	screensize)
	,	mCursorOffset(0.0088,0.0083)
	,	mStartPosition(0,0)
	,	mFirstClick(false)
{
}
Cursor::~Cursor()
{
}
void Cursor::Update()
{
	/**< If Its first time that it has been clicked */
	/**< Set the start position and create the select area image */
	if(mFirstClick == false && IsClicked() == true)
	{
		mStartPosition = getPosition();
		mSelectArea = new Image("SelectArea","AOW/MultiSelectCursor",mStartPosition,Ogre::Vector2(0,0),mScreenSize);
		mSelectArea->SetZorder(200);
		mFirstClick = true;
	}
	/**< If its Clicked */
	/**< Scale the Select area Image to cover from were the player started the Click to where it is now */
	if(IsClicked() == true)
	{
		Ogre::Vector2 newSize = getPosition() - mStartPosition;
		Ogre::Vector2 newPosition = mStartPosition;
		if(newSize.x < 0)
		{
			newPosition.x = getPosition().x;
			newSize.x *= -1;
		}
		if(newSize.y < 0)
		{
			newPosition.y = getPosition().y;
			newSize.y *= -1;
		}
		mSelectArea->SetPosition(newPosition);
		mSelectArea->Scale(newSize);
	}
}
void Cursor::Move(Ogre::Vector2 Distance)
{
	/**< Get new position on screen and check if the Cursor is hitting off the sides of the Screen */
	float XScreenPosition = (Distance.x/mScreenSize.x) - mCursorOffset.x;
	float YScreenPosition = (Distance.y/mScreenSize.y) - mCursorOffset.y;
	float cursorwidth = 1 - (mGUI_Entity->getWidth()/2);
	float cursorheight = 1 - (mGUI_Entity->getHeight()/2);
	if(XScreenPosition >= 0.993)
	{
		XScreenPosition = 0.993;
	}
	if(YScreenPosition >= 0.986)
	{
		YScreenPosition = 0.986;
	}
	mGUI_Entity->setPosition(XScreenPosition,YScreenPosition);
}
bool Cursor::IsClicked()
{
	if(mGUI_Entity->getMaterialName() == "AOW/Cursor_Normal")
	{
		return false;
	}
	return true;
}
Ogre::Vector2 Cursor::getPosition()
{
	return Ogre::Vector2(mGUI_Entity->getLeft()+ mCursorOffset.x,mGUI_Entity->getTop() + mCursorOffset.y);
}
Ogre::Vector2 Cursor::getStartPosition()
{
	return mStartPosition;
}
Ogre::Vector2 Cursor::getSize()
{
	return Ogre::Vector2(mGUI_Entity->getWidth(),mGUI_Entity->getHeight());
}
void Cursor::Click(ClickType Type)
{
	/**< Switch Image of Cursor based on click */
	switch(Type)
	{
	case(ClickType::Move):
		mGUI_Entity->setMaterialName("AOW/Cursor_BlueClick");
		break;
	case(ClickType::Enemy):
		mGUI_Entity->setMaterialName("AOW/Cursor_RedClick");
		break;
	case(ClickType::Friendly):
		mGUI_Entity->setMaterialName("AOW/Cursor_GreenClick");
		break;
	case(ClickType::GUI):
		mGUI_Entity->setMaterialName("AOW/Cursor_YellowClick");
		break;
	}
}
void Cursor::ClickRelease()
{
	/**< Set Image of cursor back and delete Selected Area Image*/
	mGUI_Entity->setMaterialName("AOW/Cursor_Normal");
	if(mFirstClick == true)
	{
		delete mSelectArea;
	}
	mFirstClick = false;
}