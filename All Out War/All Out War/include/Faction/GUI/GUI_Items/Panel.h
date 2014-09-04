#ifndef PANEL_H
#define PANEL_H

#include "Faction\GUI\Base_GUI.h"

class Panel : public Base_GUI 
{
protected:
public:
	///<summary> 
	///Constructor
	///</summary>
	///<param name="Name">Name of the Entity</param>
	///<param name="materialname">Name of the material used</param>
	///<param name="screensize">Size of the screen</param>
	Panel(Ogre::String Name, Ogre::String materialname,Ogre::Vector2 screensize);
	///<summary> 
	///Destructor
	///</summary>
	~Panel();
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
};
#endif