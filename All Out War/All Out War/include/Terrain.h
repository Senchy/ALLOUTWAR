#ifndef TERRAIN_H
#define TERRAIN_H

#include "BaseApplication.h"
#include "Physics\Vector.h"

class Terrain
{
private:
	/// <value>Pointer to Ogre Image</value>
	Ogre::ManualObject*			mManualObject;
public:	
	///<summary> 
	///Constructor
	///Creates Ogre Image of two triangles that make a square
	///</summary>
	///<param name="manager">Pointer to the Ogre Scene Manager</param>
	///<param name="type">Type of plane Split</param>
	///<param name="points">Array of points for Vertices</param>
	///<param name="colours">Array of colour values for Vertices</param>
	Terrain(Ogre::SceneManager* manager,int type ,Physics::Vector *points, Physics::Vector *colours);
	///<summary> 
	///Add Edge to the Node given to the other Node given.
	///</summary>
	///<param name="To">Pointer to Node the Edge points too </param>
	///<returns>If an edge is added</returns>
	~Terrain();
};
static int Map_Number = 0;
#endif