#include "Entity_Factory.h"

Entity_Factory* Entity_Factory::mFactoryInstance = 0;											/* Initialise the pointer too this object */

Entity_Factory::Entity_Factory(Ogre::SceneManager*	manager, Height_Map* hightmap, Graph* graph)
	:	mManager(manager),
		mHeightMap(hightmap),
		mGraph(graph)
{
	/**< Get instance of Collision Manager and Set the Values for Collision Manager */
	mCManager = Collision_Manager::getInstance();
	mCManager->INIT(&mDynamicEntity_List, &mStaticEntity_List, mHeightMap);
}
Entity_Factory* Entity_Factory::getInstance(Ogre::SceneManager*	manager, Height_Map* hightmap, Graph* graph)
{
	/**< Check if we have an instance of this class yet if we dont create an instance */
	if(mFactoryInstance == 0)
	{
		mFactoryInstance = new Entity_Factory(manager,hightmap,graph);
	}
	/**<  Return the instance of this class */
	return mFactoryInstance;
}
Entity_Factory::~Entity_Factory()
{
}
void Entity_Factory::AddEntity(Entity_Name Name, Physics::Vector pos)
{
	/**< Try add Static Entity if I cant Try add Dynamic Entity */
	if(AddStaticEntity(Name,pos) == 0)
	{
		AddDynamicEntity(Name,pos);
	}
}
Static_Ent* Entity_Factory::AddStaticEntity(Entity_Name Name, Physics::Vector pos)
{
	/**< Create a new Entity and add it too the Entity list */
	Ogre::Vector2 terrainpos = Ogre::Vector2(pos.x / 20, pos.z / 20);
	switch(Name)
	{
		case(town_center):
		{
			/**< If the Town centre can be created on the Slopes */
			if (mHeightMap->CheckCreationSlopes(terrainpos.x -1, terrainpos.y -1, 3,3))
			{
				/**< Create town centre and Nodes */
				Graph_Node** newnodes = new Graph_Node*[4];
				Town_Center* Adder = new Town_Center(pos,mManager,mHeightMap->GetNode(terrainpos.x,terrainpos.y),newnodes);
				/**< If the the any Static entitys are already created in that Position */
				if(!mCManager->Check_If_Colliding(&mStaticEntity_List,Adder))
				{
					/**< Create Nodes and create edges to thease nodes */
					Physics::Vector NodeDir = Adder->GetVertex(1) - Adder->GetPosition();
					NodeDir = Physics::Vector(NodeDir.x, 0, NodeDir.z).Normalise_copy();
					newnodes[0] =  mHeightMap->AddCornerNode(Adder->GetVertex(1),NodeDir);

					NodeDir = Adder->GetVertex(3) - Adder->GetPosition();
					NodeDir = Physics::Vector(NodeDir.x, 0, NodeDir.z).Normalise_copy();
					newnodes[1] =  mHeightMap->AddCornerNode(Adder->GetVertex(3),NodeDir);

					NodeDir = Adder->GetVertex(2) - Adder->GetPosition();
					NodeDir = Physics::Vector(NodeDir.x, 0, NodeDir.z).Normalise_copy();
					newnodes[2] =  mHeightMap->AddCornerNode(Adder->GetVertex(2),NodeDir);

					NodeDir = Adder->GetVertex(0) - Adder->GetPosition();
					NodeDir = Physics::Vector(NodeDir.x, 0, NodeDir.z).Normalise_copy();
					newnodes[3] = mHeightMap->AddCornerNode(Adder->GetVertex(0),NodeDir);
					HideNodes(Adder);

					mGraph->AddNode(newnodes[0]);
					mGraph->AddNode(newnodes[1]);
					mGraph->AddNode(newnodes[2]);
					mGraph->AddNode(newnodes[3]);
					
					/**< Add it too the Static List */
					mStaticEntity_List.Push_Back(Adder);
					return Adder;
				}
				else
				{
					/**< Delete node if there is already a Static entity at this Position */
					delete Adder;
					return 0;
				}
			}
			break;
		}
		case(tree):
		{
			/**< If the Tree can be created on the Slopes */
			if (mHeightMap->CheckCreationSlopes(terrainpos.x, terrainpos.y, 1,1))
			{
				Tree* Adder = new Tree(pos, mManager, &mCreate_List,mHeightMap->GetNode(terrainpos.x,terrainpos.y));
				/**< If the the any Static entitys are already created in that Position */	
				if(!mCManager->Check_If_Colliding(&mStaticEntity_List, Adder))
				{
					/**< Add it too the Static List */
					mStaticEntity_List.Push_Back(Adder);
					return Adder;
				}
				else
				{
					/**< Delete node if there is already a Static entity at this Position */
					delete Adder;
					return 0;
				}
			}
			break;
		}
	}
	return 0;
}
Dynamic_Ent* Entity_Factory::AddDynamicEntity(Entity_Name Name, Physics::Vector pos)
{
	/* Create a new Object and add it too the entity list */
	Ogre::Vector2 terrainpos = Ogre::Vector2(pos.x / 20, pos.z / 20);
	switch(Name)
	{
	case(citizen):
		{
			Citizen* Adder = new Citizen(Physics::Vector(pos.x, mHeightMap->GetNodePosition(terrainpos.x,terrainpos.y).y -3, pos.z), mManager);
			Adder->SetHM_Node(mHeightMap->GetNode(terrainpos.x,terrainpos.y));
			/**< Add it too the Dynamic List */
			mDynamicEntity_List.Push_Back(Adder);
			return Adder;
			break;
		}
	case(fireball):
		{
			FireBall* Adder = new FireBall(pos, mManager);
			Adder->SetHM_Node(mHeightMap->GetNode(terrainpos.x,terrainpos.y));
			/**< Add it too the Dynamic List */
			mDynamicEntity_List.Push_Back(Adder);
			return Adder;
			break;
		}
	}
	return 0;
}
void Entity_Factory::RemoveDynamicEnity(int index)
{
	delete mDynamicEntity_List.Remove(index);
}
void Entity_Factory::RemoveStaticEnity(Base_Shape* removeent)
{
	/**< Go through static list and find the Entity that we want to remove then remove from list */
	for(int i = 0; i < mStaticEntity_List.GetSize(); i++)
	{
		if(mStaticEntity_List.At(i) == removeent)
		{
			delete mStaticEntity_List.Remove(i);
		}
	}
}
void Entity_Factory::RemoveStaticEnity(int index)
{
	delete mStaticEntity_List.Remove(index);
}
void Entity_Factory::Update(float timesincelastframe)
{
	/**< Call Updates for all Dynamic Entitys */
	for(ListIterator<Base_Shape* > updateiter(&mDynamicEntity_List); !updateiter.IsNuLL();updateiter++)
	{
		updateiter.Value()->Update(timesincelastframe);
		Physics::Vector updatepos = updateiter.Value()->GetPosition();
		updateiter.Value()->SetHM_Node(mHeightMap->GetNode(updatepos.x/20,updatepos.z/20));
		/**< Remove Entity that has been maked for destruction */
		if(updateiter.Value()->IsDead())
		{
			delete updateiter.Remove();
		}
	}
	/**< Call Updates for all Static Entitys */
	for(ListIterator<Base_Shape* > updateiter(&mStaticEntity_List); !updateiter.IsNuLL();updateiter++)
	{
		updateiter.Value()->Update(timesincelastframe);
		/**< Remove Entity that has been maked for destruction */
		if(updateiter.Value()->IsDead())
		{
			Base_Shape* removeent = updateiter.Remove();
			Graph_Node** nodes = removeent->GetCornerNodes();
			/**< If the Entity has Nodes around it Remove those Nodes and Unhide the Nodes under this one */
			if(nodes != 0)
			{
				mHeightMap->RemoveCornerNode(nodes[0], removeent->GetPosition());
				mHeightMap->RemoveCornerNode(nodes[1], removeent->GetPosition());
				mHeightMap->RemoveCornerNode(nodes[2], removeent->GetPosition());
				mHeightMap->RemoveCornerNode(nodes[3], removeent->GetPosition());
				UnHideNodes(removeent);
			}
			delete removeent;
		}
	}
	/**< Check collision for all the Entitys */
	mCManager->FindCollisions(&mDynamicEntity_List);
	mCManager->FindCollisions(&mDynamicEntity_List,&mStaticEntity_List);
	/**< If there are any Entitys waiting to be created Create the Entity in the first node on the list */
	while(mCreate_List.GetSize() != 0)
	{
		MakeEntity_Node* node = mCreate_List.Pop_Front();
		AddEntity(node->mType,node->mPosition);
		delete node;
	}
}
void Entity_Factory::GetPath(Physics::Vector Startpos, Physics::Vector EndPos, LinkList<Graph_Node* > *Path, bool Advanced)
{
	mGraph->GetPath(Startpos,EndPos,Path,Advanced);
}
void Entity_Factory::HideNodes(Base_Shape* newObject)
{
	LinkList<Graph_Node*> OpenList;
	Graph_Node*	currentNode;
	/**< If point on the Plane we are creating this Entity on is inside the Entity then push the AI node onto the Open List */
	if(newObject->CheckPoint(mHeightMap->GetNodePosition(newObject->GetPosition().x /20,newObject->GetPosition().z /20)))
	{
		OpenList.Push_Front(mHeightMap->GetNode(newObject->GetPosition().x /20,newObject->GetPosition().z /20)->GetGraphNode());
	}
	/**< While we have nodes to expand */
	while(OpenList.GetSize() != 0)
	{
		/**< Get first node and Hide the Node then check if any of the nodes connected to */
		/**< this Node are inside the Entity push the Node onto the Open List */
		currentNode = OpenList.Pop_Front();
		for(int iter = 0; iter < currentNode->GetEdgeCount(); iter++)
		{
			if(!(currentNode->GetHidden(iter)))
			{
				if(newObject->CheckPoint(currentNode->GetTo(iter)->GetPosition()))
				{
					OpenList.Push_Back(currentNode->GetTo(iter));
				}
			}
		}
		currentNode->SetHidden(true);
	}
}
void Entity_Factory::UnHideNodes(Base_Shape* newObject)
{
	LinkList<Graph_Node*> OpenList;
	Graph_Node*	currentNode;
	/**< If point on the Plane we are creating this Entity on is inside the Entity then push the AI node onto the Open List */
	if(newObject->CheckPoint(mHeightMap->GetNodePosition(newObject->GetPosition().x /20,newObject->GetPosition().z /20)))
	{
		OpenList.Push_Front(mHeightMap->GetNode(newObject->GetPosition().x /20,newObject->GetPosition().z /20)->GetGraphNode());
	}
	/**< While we have nodes to expand */
	while(OpenList.GetSize() != 0)
	{
		/**< Get first node and UnHide the Node then check if any of the nodes connected to */
		/**< this Node are inside the Entity push the Node onto the Open List */
		currentNode = OpenList.Pop_Front();
		for(int iter = 0; iter < currentNode->GetEdgeCount(); iter++)
		{
			if((currentNode->GetHidden(iter)))
			{
				if(newObject->CheckPoint(currentNode->GetTo(iter)->GetPosition()))
				{
					OpenList.Push_Back(currentNode->GetTo(iter));
				}
			}
		}
		currentNode->SetHidden(false);
	}
}