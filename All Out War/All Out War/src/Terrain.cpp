#include "Terrain.h"

Terrain::Terrain(Ogre::SceneManager* manager,int type ,Physics::Vector *points, Physics::Vector *colours)
{
	/**< Set colour values and vector values for our 4 coners of the plain */
	Ogre::Vector3 P1 = Ogre::Vector3(points[0].x, points[0].y, points[0].z);
	Ogre::Vector3 P2 = Ogre::Vector3(points[1].x, points[1].y, points[1].z);
	Ogre::Vector3 P3 = Ogre::Vector3(points[2].x, points[2].y, points[2].z);
	Ogre::Vector3 P4 = Ogre::Vector3(points[3].x, points[3].y, points[3].z);
	Ogre::ColourValue C1 = Ogre::ColourValue(colours[0].x, colours[0].y, colours[0].z);
	Ogre::ColourValue C2 = Ogre::ColourValue(colours[1].x, colours[1].y, colours[1].z);
	Ogre::ColourValue C3 = Ogre::ColourValue(colours[2].x, colours[2].y, colours[2].z);
	Ogre::ColourValue C4 = Ogre::ColourValue(colours[3].x, colours[3].y, colours[3].z);
	std::ostringstream Stream;
	Stream << Map_Number;
	mManualObject = manager->createManualObject("Height_Map " + Stream.str());
	mManualObject->begin("Examples/ColourTest", Ogre::RenderOperation::OT_TRIANGLE_LIST);
	/**< Based on what direction the split is create the Triangles with different points */
	if(type % 2 == 0)
	{
		Ogre::Vector3 Normal = (P2 - P1).crossProduct(P3 - P1);	
		Normal.normalise();
		mManualObject->position(P2);
		mManualObject->colour(C2);
		mManualObject->normal(Normal);
		mManualObject->position(P1);
		mManualObject->colour(C1);
		mManualObject->normal(Normal);
		mManualObject->position(P3);
		mManualObject->colour(C3);
		mManualObject->normal(Normal);
				
		Normal = (P3 - P2).crossProduct(P4 - P2);	
		Normal.normalise();
		mManualObject->position(P4);
		mManualObject->colour(C4);
		mManualObject->normal(Normal);
		mManualObject->position(P2);
		mManualObject->colour(C2);
		mManualObject->normal(Normal);
		mManualObject->position(P3);
		mManualObject->colour(C3);
		mManualObject->normal(Normal);
	}
	else
	{
		Ogre::Vector3 Normal = (P1 - P4).crossProduct(P2 - P4);	
		Normal.normalise();
		mManualObject->position(P1);
		mManualObject->colour(C1);
		mManualObject->normal(Normal);
		mManualObject->position(P4);
		mManualObject->colour(C4);
		mManualObject->normal(Normal);
		mManualObject->position(P2);
		mManualObject->colour(C2);
		mManualObject->normal(Normal);
	
		Normal = (P1 - P3).crossProduct(P4 - P3);	
		Normal.normalise();
		mManualObject->position(P1);
		mManualObject->colour(C1);
		mManualObject->normal(Normal);
		mManualObject->position(P3);
		mManualObject->colour(C3);
		mManualObject->normal(Normal);
		mManualObject->position(P4);
		mManualObject->colour(C4);
		mManualObject->normal(Normal);
	}
	mManualObject->end();
	/**< Add Image to the scene */
	manager->getRootSceneNode()->createChildSceneNode()->attachObject(mManualObject);
	Map_Number++;
}
Terrain::~Terrain()
{
}