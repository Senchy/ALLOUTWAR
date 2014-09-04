#ifndef CURSOR_H
#define CURSOR_H

#include "Faction\GUI\Base_GUI.h"
#include "Faction\GUI\GUI_Items\Image.h"
#include "ContainerStructs.h"

class Cursor :	public Base_GUI 
{
protected:
	/// <value>Offset of the cursor image</value>
	Ogre::Vector2				mCursorOffset;
	/// <value>When first clicked save the position</value>
	Ogre::Vector2				mStartPosition;
	/// <value>Is already Clicked</value>
	bool						mFirstClick;
	/// <value>The area selected image </value>
	Image*						mSelectArea;
public:
	///<summary> 
	///Constructor
	///</summary>
	///<param name="Name">Name of the Entity</param>
	///<param name="materialname">Name of the material used</param>
	///<param name="screensize">Size of the screen</param>
	Cursor(Ogre::String Name, Ogre::String materialname,Ogre::Vector2 screensize);
	///<summary> 
	///Destructor
	///</summary>
	~Cursor();
	///<summary> 
	///Method called on each frame of the Programe.
	///</summary>
	virtual void Update();
	///<summary> 
	///Get position of Cursor
	///</summary>
	///<returns>position of Cursor</returns>
	Ogre::Vector2 getPosition();
	///<summary> 
	///Get the position of the Cursor when the mouse button was first clicked
	///</summary>
	///<returns>position of the Cursor when the mouse button was first clicked</returns>
	Ogre::Vector2 getStartPosition();
	///<summary> 
	///Get Size of Cursor Image
	///</summary>
	///<returns>Size of Cursor Image</returns>
	Ogre::Vector2 getSize();
	///<summary> 
	///If a mouse button is down
	///</summary>
	///<returns>If a mouse button is down</returns>
	bool IsClicked();
	///<summary> 
	///Updates the Click animation
	///</summary>
	///<param name="Pos">What type of Click</param>
	void Click(ClickType Type);
	///<summary> 
	///Called when Player releases a mouse button
	///</summary>
	void ClickRelease();
	///<summary> 
	///Move the Entity by a Set amount
	///</summary>
	///<param name="Distance">Amount the Entity moves by</param>
	void Move(Ogre::Vector2 Distance);
};
#endif