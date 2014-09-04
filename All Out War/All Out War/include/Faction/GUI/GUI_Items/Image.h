#ifndef IMAGE_H
#define IMAGE_H

#include "Faction\GUI\Base_GUI.h"

class Image : public Base_GUI 
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
	Image(Ogre::String Name, Ogre::String materialname, Ogre::Vector2 Position, Ogre::Vector2 size,Ogre::Vector2 screensize);
	///<summary> 
	///Destructor
	///</summary>
	~Image();
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
	///Set the size of the image
	///</summary>
	///<param name="Pos">Size of the Image</param>
	void Scale(Ogre::Vector2 scale);
	///<summary> 
	///Set how close the screen is
	///</summary>
	///<param name="Pos">Zorder</param>
	void SetZorder(float z);
	///<summary> 
	///Set the position of the the Entity
	///</summary>
	///<param name="Pos">New position on screen</param>
	Ogre::Vector2 GetPosition();
};
#endif