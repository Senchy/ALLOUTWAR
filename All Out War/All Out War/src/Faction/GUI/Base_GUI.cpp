#include "Faction\GUI\Base_GUI.h"


Base_GUI::Base_GUI(Ogre::String Name, Ogre::String materialname,int zorder, Ogre::Vector2 Position, Ogre::Vector2 size,Ogre::Vector2 screensize)
	:	mScreenSize(screensize)
		,mOverlayManager(Ogre::OverlayManager::getSingleton())
{
	/**< Create an overlay */
    mGUI_Layer = mOverlayManager.create( Name + "Overlay" );
	/**< Create an panel */
	mGUI_Entity = static_cast<Ogre::OverlayContainer*>( mOverlayManager.createOverlayElement( "Panel", Name + "Panel" ) );
    mGUI_Entity->setPosition(Position.x , Position.y);
    mGUI_Entity->setDimensions( size.x/mScreenSize.x, size.y/mScreenSize.y);
    mGUI_Entity->setMaterialName( materialname );
	/**< Add the panel to the overlay */
    mGUI_Layer->add2D( mGUI_Entity );
	mGUI_Layer->setZOrder( zorder );
	/**< Show the overlay*/
    mGUI_Layer->show();
}
Base_GUI::~Base_GUI()
{
	mOverlayManager.destroyOverlayElement(mGUI_Entity);
	mOverlayManager.destroy(mGUI_Layer);
}
void Base_GUI::Update()
{
}
bool Base_GUI::Clicked(Ogre::Vector2 Pos)
{
	/**< Check if the Cursor position is inside the Entity when clicked */
	if((mGUI_Entity->getLeft() < Pos.x 
		&& (mGUI_Entity->getLeft() + mGUI_Entity->getWidth()) > Pos.x
		&&	mGUI_Entity->getTop() < Pos.y 
		&& (mGUI_Entity->getTop() + mGUI_Entity->getHeight()) > Pos.y))
	{
		return true;
	}
	return false;
}
void Base_GUI::Release()
{
}
void Base_GUI::SetPosition(Ogre::Vector2 Pos)
{
	mGUI_Entity->setPosition(Pos.x,Pos.y);
}
void Base_GUI::Move(Ogre::Vector2 Distance)
{
	/**< Add distance onto the Position of the Entity to move the Entity */
	float nx = mGUI_Entity->getLeft() + Distance.x;
	float ny = mGUI_Entity->getTop() + Distance.y;
	mGUI_Entity->setPosition(nx,ny);
}