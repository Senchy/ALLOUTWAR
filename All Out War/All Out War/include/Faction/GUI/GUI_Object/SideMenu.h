#ifndef SIDEMENU_H
#define SIDEMENU_H

#include "Faction\GUI\GUI_Object\Table.h"
#include "Faction\GUI\GUI_Items\Button.h"

class SideMenu : public Table 
{
protected:
	/// <value>Button used to open menu</value>
	Button					mOpenMenu;
	/// <value>Current x position used when it is sliding</value>
	float					mXposition;
	/// <value>how high the button is on the side</value>
	float					mYbuttonPos;
	/// <value>Max distance that the menu slides out</value>
	float					mSlideLimit;
public:
	///<summary> 
	///Constructor
	///</summary>
	///<param name="Name">Name of the Entity</param>
	///<param name="materialname">Name of the material used</param>
	///<param name="ButtonPosy">Position of button along Side of Menu</param>
	///<param name="screensize">Size of the screen</param>
	SideMenu(Ogre::String Name, Ogre::String materialname, float ButtonPosy,Ogre::Vector2 screensize);
	///<summary> 
	///Destructor
	///</summary>
	~SideMenu();
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
	///Called when Player releases a mouse button
	///</summary>
	virtual void Release();
	///<summary> 
	///Set Position of the button
	///</summary>
	///<param name="Pos">New Position</param>
	virtual void SetPosition(Ogre::Vector2 Pos);
	///<summary> 
	///Move the Entity by a Set amount
	///</summary>
	///<param name="Distance">Amount the Entity moves by</param>
	virtual void Move(Ogre::Vector2 Distance);
};
#endif