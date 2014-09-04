#ifndef PLAYER_GUI_H
#define PLAYER_GUI_H

#include "Entity_Factory.h"
#include "ContainerStructs.h"
#include "Faction\GUI\GUI_Items\Cursor.h"
#include "Faction\GUI\GUI_Object\TownListInfo.h"
#include "Faction\GUI\GUI_Object\ResearchTree.h"
#include "Faction\GUI\GUI_Object\SelectedMenu.h"
#include "Faction\GUI\GUI_Object\CommandMenu.h"
#include "Faction\GUI\GUI_Object\MiniMap.h"
#include "Faction\GUI\GUI_Items\Image.h"

class Player_GUI
{
protected:
	/// <value>Pointer to the cursor</value>
	Cursor						mCursor;
	/// <value>Pointer to the research table</value>
	ResearchTree*				mResearchTable;
	/// <value>Pointer to the town list menu</value>
	TownListInfo*				mTownListTable;
	/// <value>Pointer to the select menu</value>
	SelectedMenu*				mSelectedMenu;
	/// <value>Pointer to the command menu</value>
	CommandMenu*				mCommandMenu;
	/// <value>Pointer to the Minimap</value>
	MiniMap*					mMiniMap;
	/// <value>Name of the Entity we want to create</value>
	Entity_Name					mCreateType;
public:
	///<summary> 
	///Constructor
	///</summary>
	///<param name="screensize">Size of the screen</param>
	Player_GUI(Ogre::Vector2 screensize);
	///<summary> 
	///Destructor
	///</summary>
	~Player_GUI();
	///<summary> 
	///Method called on each frame of the Programe.
	///</summary>
	///<param name="timesincelastframe">Time since last called</param>
	void Update(float timesincelastframe);
	///<summary> 
	///Called Player clicks a mouse button
	///</summary>
	///<returns>If a GUI Entity has been clicked</returns>
	bool Click();
	///<summary> 
	///Called when Player releases a mouse button
	///</summary>
	void Release();
};
#endif