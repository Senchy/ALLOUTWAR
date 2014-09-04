#ifndef PLAYER_H
#define PLAYER_H

#include "Faction\Faction.h"
#include "Physics\Height_Map.h"
#include "Faction\GUI\Player_GUI.h"
#include "Physics\Collisions_Manager.h"
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

class Player : public Faction , Player_GUI
{
private:
	/// <value>Distance from Player position to camera</value>
	float					mOffset;
	/// <value>Height of the Map that the player is over</value>
	float					mGroundHeight;
	/// <value>Pointer to the Height Map</value>
	Height_Map*				mHeightMap;
	/// <value>Pointer to Ogre scene manager</value>
    Ogre::SceneManager*		mManager;
	/// <value>Pointer to the players camera</value>
	Ogre::Camera*			mCamera;
	/// <value>Speed to the player</value>
	Ogre::Vector3			mVelocity;
	/// <value>Pointer to the only instance of collision manager</value>
	Collision_Manager*		mCManager;
	/// <value>If the player is moving forward</value>
	bool					mGoingForward;
	/// <value>If the player is moving backwards</value>
	bool					mGoingBack;
	/// <value>If the player is moving left</value>
	bool					mGoingLeft;
	/// <value>If the player is moving right</value>
	bool					mGoingRight;
	/// <value>If the player is away from the ground</value>
	bool					mGoingUp;
	/// <value>If the player is towards from the ground</value>
	bool					mGoingDown;
public:
	///<summary> 
	///Constructor
	///</summary>
	///<param name="manager">Ogre scene manager</param>
	///<param name="map">The height map of the game</param>
	///<param name="camera">The camera used by the player</param>
	///<param name="width">Width of the screen</param>
	///<param name="height">Height of the screen</param>
	Player(Ogre::SceneManager* manager,Height_Map* map, Ogre::Camera* camera,float width,float height);
	///<summary> 
	///Destructor
	///</summary>
	~Player();
	///<summary> 
	///Method called on each frame of the Programe.
	///</summary>
	///<param name="timesincelastframe">Time since last called</param>
	virtual bool Update(float timesincelastframe);
	///<summary> 
	///Code used when a keyboard key is down
	///</summary>
	///<param name="evt">What key is pressed</param>
	void injectKeyDown(const OIS::KeyEvent& evt);
	///<summary> 
	///Code used when a keyboard key is Up
	///</summary>
	///<param name="evt">What key has just come up</param>
	void injectKeyUp(const OIS::KeyEvent& evt);
	///<summary> 
	///Code used when a mouse moves its position
	///</summary>
	///<param name="evt">Change in mouse position</param>
	void injectMouseMove(const OIS::MouseEvent& evt);
	///<summary> 
	///Code used when a mouse key is down
	///</summary>
	///<param name="evt">Change in mouse state</param>
	///<param name="id">What mouse key is pressed</param>
	void injectMouseDown(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
	///<summary> 
	///Code used when a mouse key is up
	///</summary>
	///<param name="evt">Change in mouse state</param>
	///<param name="id">What mouse key is up</param>
	void injectMouseUp(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
	///<summary> 
	///Get the position of the player.
	///Players position is infront of the camera
	///</summary>
	///<returns>Players position</returns>
	Physics::Vector GetPosition();
};

#endif