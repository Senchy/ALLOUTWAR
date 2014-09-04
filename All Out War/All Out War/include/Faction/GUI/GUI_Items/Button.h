#ifndef BUTTON_H
#define BUTTON_H

#include "Faction\GUI\Base_GUI.h"

class Button : public Base_GUI 
{
protected:
	/// <value>If the button is down</value>
	bool			mIsDown;
	/// <value>If stays down untill clicked again</value>
	bool			mReleaseUp;
	/// <value>Name of the material used when button is up</value>
	Ogre::String	mUpMaterial;
	/// <value>Name of the material used when button is down</value>
	Ogre::String	mDownMaterial;
public:
	///<summary> 
	///Constructor
	///</summary>
	///<param name="Name">Name of the Entity</param>
	///<param name="materialnameUp">Name of the material used when button is up</param>
	///<param name="materialnameDown">Name of the material used when button is down</param>
	///<param name="Zbuff">How close to the screen</param>
	///<param name="Position">Position of the button</param>
	///<param name="size">Size of the button</param>
	///<param name="screensize">Size of the screen</param>
	///<param name="ReleaseUp">If stays down untill clicked again(Default : false)</param>
	Button(Ogre::String Name,Ogre::String materialnameUp,Ogre::String materialnameDown,int Zbuff, Ogre::Vector2 Position, Ogre::Vector2 size,Ogre::Vector2 screensize, bool ReleaseUp = false);
	///<summary> 
	///Destructor
	///</summary>
	~Button();
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
	///<summary> 
	///If the button is down
	///</summary>
	///<returns>If the button is clicked</returns>
	bool IsDown();
};
#endif