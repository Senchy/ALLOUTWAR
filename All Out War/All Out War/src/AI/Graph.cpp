#include "AI\Graph.h"

Graph::Graph()
{
}
Graph::~Graph()
{
	mNodes.~LinkList();
}
void Graph::AddNode(Physics::Vector pos)
{
	mNodes.Push_Back(new Graph_Node(pos,Physics::Vector(0)));
}
void Graph::AddNode(Graph_Node* node)
{
	mNodes.Push_Back(node);
}
bool Graph::AddEdge(Graph_Node* From, Graph_Node* To)
{
	/**< Get the Distance as the crow flies */
	/**< Get the differnece between the New Nodes Height and the Current Nodes Height */
	float dist = (To->GetPosition() - From->GetPosition()).lengthxz();			
	float ydif = abs(To->GetPosition().y - From->GetPosition().y);					
	/**< Make sure the differnce is at under 10 units high */
	if(ydif < 10)
	{
		/**< If the difference is under 10 units reset the Differnce to a more manageable value */
		if(ydif < 2)		{ ydif = 1; }
		else if(ydif < 4)	{ ydif = 2; }
		else if(ydif < 6)	{ ydif = 2.5; }
		else				{ ydif = 4; }
		/**< Check which Node is Higher then add Edges to the Node with Advanced Weights based on the difference of the Y Value  */
		if(To->GetPosition().y < From->GetPosition().y)
		{
			From->AddEdge(To,dist, 1 - (ydif / 10));
		}
		else
		{
			From->AddEdge(To,dist, 1 + ((ydif * ydif)/ 14));
		}
		return true;
	}
	return false;
}
void Graph::RemoveNode(Physics::Vector pos)
{
	Graph_Node* removeNode = 0;			
	/**< Traverse the list of Nodes and find the Node that has the same position */
	/**< as the position passed in and set the Remove Node to the Node we found */
	for(ListIterator<Graph_Node*> iter(&mNodes); !iter.IsNuLL();iter++)
	{
		if(iter.Value()->GetPosition() == pos)
		{
			removeNode = iter.Remove();
		}
	}
	/**< If the Remove Node is not Empty */
	if(!(removeNode == 0))
	{
		/**< Get the Number of Edges this Node has */
		int numberofedges = removeNode->GetEdgeCount();
		/**< Iterate through the the Edges in The Node and remove the Nodes that connect other Nodes to the Node we want to Remove */
		for(int nodeiter = 0;nodeiter < numberofedges;nodeiter++)
		{
			removeNode->GetTo(nodeiter)->RemoveEdge(removeNode);
		}
		/**< Remove all the Edges on this Node */
		removeNode->RemoveEdges();														
		delete removeNode;
	}
}
void Graph::RemoveNode(Graph_Node* node)
{
	Graph_Node* removeNode = 0;		
	/**< Traverse the list of Nodes and find the Node in the list that holds the Node */
	/**< passed in and set the Remove Node to the Node we found */
	for(ListIterator<Graph_Node*> iter(&mNodes); !iter.IsNuLL();iter++)
	{
		if(iter.Value() == node)
		{
			removeNode = iter.Remove();
		}
	}
	/**< If the Remove node is not Empty */
	if(!(removeNode == 0))
	{
		/**< Get the Number of Edges this Node has */
		int numberofedges = removeNode->GetEdgeCount();							
		/**< Iterate through the the Edges in the Node and remove the Nodes that connect other Nodes to the Node we want to Remove */
		for(int nodeiter = 0;nodeiter < numberofedges;nodeiter++)
		{
			removeNode->GetTo(nodeiter)->RemoveEdge(removeNode);
		}
		/**< Remove all the Edges on this Node */
		removeNode->RemoveEdges();														
		delete removeNode;
	}
}
Graph_Node* Graph::getGRAPHNODE(int index)
{
	return mNodes.At(index);
}
int Graph::Graphsize()
{
	return mNodes.GetSize();
}
void Graph::GetPath(Graph_Node* StartNode, Graph_Node* EndNode, LinkList<Graph_Node* > *Path, bool Advanced)
{
	LinkList<PathNode*> OpenList;
	LinkList<PathNode*> ClosedList;
	bool Found = false;								
	/**< Create our first Node on OpenList made From the start Node */
	OpenList.Push_Front(new PathNode(StartNode,0,0,(StartNode->GetPosition() - EndNode->GetPosition()).length()));	
	/**< If we haven't found our goal Node yet */
	while(!Found)
	{
		/**< If there are no more Nodes to expand from then there is no way to get to the goal Node so exit the Method */
		if(OpenList.GetSize() == 0)
		{
			return;
		}													
		/**< Get and remove first node on the OpenList and push onto ClosedList */
		PathNode* Currentnode = OpenList.Pop_Front();
		ClosedList.Push_Front(Currentnode);																
		/**< If Current Node is the goal Node then we have found the Goal Node so exit loop */
		if(Currentnode->mNode == EndNode)
		{
			Found = true;
		}							
		/**< Iterate through each Edge in the Node creating a new PathNode push on the OpenList */
		for(int i = 0;i < Currentnode->mNode->GetEdgeCount();i++)
		{
			float cost, Heuristic;
			/**< The current Node being pushed on the OpenList */
			Graph_Node* node = Currentnode->mNode->GetTo(i);										
			/**< Create new PathNode if Node isn't used or Edge to Node isn't hidden */
			if(!node->GetUsed() && !Currentnode->mNode->GetHidden(i))
			{
				/**< If advanced search get advanced cost and Heuristic*/
				if(!Advanced)
				{
					cost = Currentnode->mKnownCost + (Currentnode->mNode->GetWeight(i));												/**< Add up how much it took to get to this Node */
					Heuristic = (node->GetPosition() - EndNode->GetPosition()).length();												/**< Guess how much it would take to get to the Goal Node */
				}/**< Else  get normal cost and Heuristic*/
				else
				{
					cost = Currentnode->mKnownCost + (Currentnode->mNode->GetWeight(i) * Currentnode->mNode->GetAdvancedWeight(i));	/**< Add up how much it took to get to this Node */
					Heuristic = (node->GetPosition() - EndNode->GetPosition()).length();												/**< Guess how much it would take to get to the Goal Node */
				}
				PathNode* newnode = new PathNode(node,Currentnode,cost, cost + Heuristic);												/**< Create New Path Node */
				int iter = 0;
				/**< Get the position in the OpenList that has a bigger cost than the new Nodes cost. */
				/**< Push new node infront of that position */
				if(OpenList.GetSize() != 0)
				{
					while(newnode->mGuess > OpenList.At(iter)->mGuess && iter != OpenList.GetSize())
					{
						iter++;
					}
				}
				/**< Set the Edge we just Used To Used */
				/**< Insert the New Node into the OpenList */
				node->SetUsed(true);																	
				OpenList.Insert(newnode,iter);															
			}
		}
	}
	/**< Reset all Nodes in the OpenList */
	for(ListIterator<PathNode*> iter(&OpenList); !iter.IsNuLL();iter++)
	{											
		iter.Value()->mNode->SetUsed(false);
	}
	/**< Reset all Nodes in the ClosedList */
	for(ListIterator<PathNode*> iter(&ClosedList); !iter.IsNuLL();iter++)
	{												
		iter.Value()->mNode->SetUsed(false);
	}
	/**< Set the first Node on the ClosedList  */
	/**< (Which is the last Node added so will be the Goal Node) */
	/**< to the Node we will use to iterate through the Closed List */
	PathNode* CreatePathNode = ClosedList.At(0);
	/**< While the PathNode isnt 0. */
	/**< (The start Node was added to the ClosedList, with a previous that is set to 0) */
	/**< Add the GraphNode to the Path then set the created PathNode to the previous Node */
	/**<(Which is the PathNode Used to expand The current Node) */
	while(CreatePathNode != 0)
	{
		Path->Push_Front(CreatePathNode->mNode);
		CreatePathNode = CreatePathNode->mPrevious;
	}
}
void Graph::GetPath(Physics::Vector Startpos, Physics::Vector EndPos, LinkList<Graph_Node* > *Path, bool Advanced)
{
	/**< Set the start and goal node to the First Node in the Link List. */
	/**< Get the distance from that start position and end position to the first Node*/
	Graph_Node* Start = mNodes.GetHead()->Value;														
	Graph_Node* Goal = mNodes.GetHead()->Value;																						
	float startdis = (Start->GetPosition() - Startpos).length();										
	float enddis = (Goal->GetPosition() - EndPos).length();											
	/**< Iterate Through all the Nodes in the Graph Node Link list */	
	for(ListIterator<Graph_Node*> iter(&mNodes); !iter.IsNuLL();iter++)
	{
		/**< Get the distance from the current Node to the start and end position */
		float teststartdis = (iter.Value()->GetPosition() - Startpos).length();							
		float testenddis = (iter.Value()->GetPosition() - EndPos).length();		
		if(!iter.Value()->GetHidden())
		{
			/**< If current Node is closer to start position then set */
			/**< StartNode to current Node and set our start distance to the current distance */
			if(startdis > teststartdis)
			{
				startdis = teststartdis;
				Start = iter.Value();
			}
			/**< If current Node is closer to end position then set */
			/**< EndNode to current Node and set our end distance to the current distance */
			if(enddis > testenddis)
			{
				enddis = testenddis;
				Goal = iter.Value();
			}
		}
	}
	GetPath(Start,Goal,Path,Advanced);
}