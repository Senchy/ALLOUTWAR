#ifndef TABLE_H
#define TABLE_H

#include "Faction\GUI\Base_GUI.h"

class Table : public Base_GUI
{
protected:
public:
	///<summary> 
	///Constructor
	///</summary>
	///<param name="Name">Name of the Entity</param>
	///<param name="materialname">Name of the material used</param>
	///<param name="Position">Position of Image</param>
	///<param name="size">Size of Image</param>
	///<param name="screensize">Size of the screen</param>
	Table(Ogre::String Name, Ogre::String materialname, Ogre::Vector2 Position, Ogre::Vector2 size,Ogre::Vector2 screensize);
	///<summary> 
	///Destructor
	///</summary>
	~Table();
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