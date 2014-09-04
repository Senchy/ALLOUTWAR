#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "LinkList.h"
#include "BaseApplication.h"
#include "Entities\Static Entities\Town_Center.h"
#include "Entities\Static Entities\Tree.h"
#include "Entities\Dynamic Entities\Citizen.h"
#include "Entities\Dynamic Entities\FireBall.h"
#include "Physics\Collisions_Manager.h"
#include "Physics\HM_Plane.h"

class Entity_Factory
{
private:
	/// <value>Pointer to a Factory instance that is the only instance of this class</value>
	static Entity_Factory*					mFactoryInstance;
	/// <value>Pointer to the only instance of collision manager</value>
	Collision_Manager*						mCManager;
	/// <value>Pointer to Ogre scene manager</value>
	Ogre::SceneManager*						mManager;
	/// <value>Pointer to the Height Map</value>
	Height_Map*								mHeightMap;
	/// <value>Pointer to Graph of AI Nodes</value>
	Graph*									mGraph;
	/// <value>The List of Entitys that dont usual move</value>
	LinkList<Base_Shape *>					mStaticEntity_List;
	/// <value>The List of Entitys that usual move</value>
	LinkList<Base_Shape *>					mDynamicEntity_List;
	/// <value>The List of Nodes that are entitys set for creation</value>
	LinkList<MakeEntity_Node *>				mCreate_List;
	///<summary> 
	///Constructor
	///</summary>
	///<param name="manager">Pointer to Ogre scene manager</param>
	///<param name="hightmap">Pointer to the Height Map</param>
	///<param name="graph">Pointer to Graph</param>
	Entity_Factory(Ogre::SceneManager*	manager, Height_Map* hightmap, Graph* graph);
	///<summary> 
	///Hides all Graph Nodes that are inside the Entity given
	///</summary>
	///<param name="newObject">Pointer to Entity</param>
	void HideNodes(Base_Shape* newObject);	
	///<summary> 
	///Unhides all Graph Nodes that are inside the Entity given
	///</summary>
	///<param name="newObject">Pointer to Entity</param>
	void UnHideNodes(Base_Shape* newObject);
public:
	///<summary> 
	///Destructor
	///</summary>
	~Entity_Factory();
	///<summary> 
	///Get instance of the class
	///</summary>
	///<param name="manager">Pointer to Ogre scene manager</param>
	///<param name="hightmap">Pointer to the Height Map</param>
	///<param name="graph">Pointer to Graph</param>
	///<returns>Pointer to the only instance of this class</returns>
	static Entity_Factory* getInstance(Ogre::SceneManager* manager,  Height_Map* hightmap, Graph* graph);
	///<summary> 
	///Adds a new Entity to ether the Dynamic Entity list or Static Entity list
	///</summary>
	///<param name="Name">Type of Entity</param>
	///<param name="pos">Starting position of Entity</param>
	void AddEntity(Entity_Name Name, Physics::Vector pos);
	///<summary> 
	///Adds a new Entity to Static Entity list
	///</summary>
	///<param name="Name">Type of Entity</param>
	///<param name="pos">Starting position of Entity</param>
	Static_Ent* AddStaticEntity(Entity_Name Name, Physics::Vector pos);
	///<summary> 
	///Adds a new Entity to ether the Dynamic Entity list
	///</summary>
	///<param name="Name">Type of Entity</param>
	///<param name="pos">Starting position of Entity</param>
	Dynamic_Ent* AddDynamicEntity(Entity_Name Name, Physics::Vector pos);
	///<summary> 
	///Removes an Entity from the Dynamic Entity List based on Index
	///</summary>
	///<param name="To">Index in the Dynamic Entity List</param>
	void RemoveDynamicEnity(int index);
	///<summary> 
	///Removes an Entity from the Static Entity List based on Index
	///</summary>
	///<param name="To">Index in the Static Entity List</param>
	void RemoveStaticEnity(int index);
	///<summary> 
	///Removes an Entity from the static entity list based on pointer to Entity
	///</summary>
	///<param name="To">Pointer to Entity</param>
	void RemoveStaticEnity(Base_Shape* removeent);
	///<summary> 
	///Method called on each frame of the Programe.
	///</summary>
	///<param name="timesincelastframe">Time since last called</param>
	void Update(float timesincelastframe);	
	///<summary> 
	///Get the shortest Path of AI Graph Nodes from the start position to the end position.
	///</summary>
	///<param name="Startpos">Position that we start from</param>
	///<param name="EndPos">Position that we want to get to</param>
	///<param name="Path">Empty list that we store the Result in</param>
	///<param name="Advanced">If we want to search with advanced weights</param>
	void GetPath(Physics::Vector Startpos, Physics::Vector EndPos, LinkList<Graph_Node* > *Path, bool Advanced = false);
};
#endif