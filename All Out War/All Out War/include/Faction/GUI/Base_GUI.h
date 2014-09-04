#ifndef BASE_GUI_H
#define BASE_GUI_H

#include "Ogre.h"
#include "OgreFontManager.h"
#include "OgreBorderPanelOverlayElement.h"
#include "OgreTextAreaOverlayElement.h"

class Base_GUI
{
protected:
	/// <value>The Layer that this GUI Entity is On</value>
	Ogre::Overlay*				mGUI_Layer;
	/// <value>THe GUI Entity</value>
	Ogre::OverlayContainer*		mGUI_Entity;
	/// <value>The GUI Manager</value>
	Ogre::OverlayManager&		mOverlayManager;
	/// <value>The Size of the screen</value>
	Ogre::Vector2				mScreenSize;
public:
	///<summary> 
	///Constructor
	///</summary>
	///<param name="Name">Name of Entity</param>
	///<param name="materialname">Material name</param>
	///<param name="zorder">Order of what is on top</param>
	///<param name="Position">The Position on the Screen</param>
	///<param name="size">The size of the Entity</param>
	///<param name="screensize">The size of the Screen</param>
	Base_GUI(Ogre::String Name, Ogre::String materialname,int zorder, Ogre::Vector2 Position, Ogre::Vector2 size,Ogre::Vector2 screensize);
	///<summary> 
	///Destructor
	///</summary>
	~Base_GUI();
	///<summary> 
	///Method called on each frame of the Programe.
	///</summary>
	virtual void Update();
	///<summary> 
	///When player clicks on screen check if the cursor position is over the Entity
	///</summary>
	///<param name="Pos">Position that has been clicked</param>
	///<returns>If it has been clicked</returns>
	virtual bool Clicked(Ogre::Vector2 Pos);
	///<summary> 
	///When player releases the button call this fuction
	///</summary>
	virtual void Release();
	///<summary> 
	///Set the position of the the Entity
	///</summary>
	///<param name="Pos">New position on screen</param>
	virtual void SetPosition(Ogre::Vector2 Pos);
	///<summary> 
	///Move the Entity by a Set amount
	///</summary>
	///<param name="Distance">Amount the Entity moves by</param>
	virtual void Move(Ogre::Vector2 Distance);
};
#endif