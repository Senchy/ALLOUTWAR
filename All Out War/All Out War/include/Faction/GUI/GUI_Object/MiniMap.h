#ifndef MINIMAP_H
#define MINIMAP_H

#include "Faction\GUI\GUI_Object\Table.h"

class MiniMap :	public Table 
{
protected:
public:
	///<summary> 
	///Constructor
	///</summary>
	///<param name="Name">Name of the Entity</param>
	///<param name="materialname">Name of the material used</param>
	///<param name="screensize">Size of the screen</param>
	MiniMap(Ogre::String Name, Ogre::String materialname,Ogre::Vector2 screensize);
	///<summary> 
	///Destructor
	///</summary>
	~MiniMap();
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