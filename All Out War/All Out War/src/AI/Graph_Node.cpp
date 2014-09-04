#include "AI\Graph_Node.h"

Graph_Node::Graph_Node(Physics::Vector pos, Physics::Vector dir, bool cornernode)
	:	mPosition(pos)
	,	mDirection(dir)
	,	mUsed(false)
	,	mNarrow(false)
	,	mCornerNode(cornernode)
{
}
Graph_Node::~Graph_Node()
{
}
void Graph_Node::AddEdge(Graph_Node* to, float weight, float advanced)
{
	/**< Create new Edge and all the values pased to the Edge also set Hidden to false then push to List of Edges*/
	Edge* newedge = new Edge();		
	newedge->mTo = to;					
	newedge->mHidden = false;
	newedge->mWeight = weight;					
	newedge->mAdvancedWeight = advanced;		
	mEdges.Push_Back(newedge);					
}
void Graph_Node::RemoveEdge(Graph_Node* to)
{
	/**< Create List Iterator for the Edges in this Node */
	/**< Traverse the List till the To = the given GraphNode then Remove the node */
	/**< Return right after so it breaks the loop */
	for(ListIterator<Edge*> iter(&mEdges);!iter.IsNuLL();iter++)
	{
		if(iter.Value()->mTo == to)
		{
			delete iter.Remove();
			return;
		}
	}
}
void Graph_Node::RemoveEdge(int index)
{
	/**< Check if the Index is in Range */
	if(index < 0 || index > mEdges.GetSize())
	{
		return;
	}
	int i = 0;
	/**< Create List Iterator for the Edges in this Node */
	/**< Traverse the List till the index = the Graph Node we are on then remove the Node */
	/**< Return right after so it breaks the loop */
	for(ListIterator<Edge*> iter(&mEdges);!iter.IsNuLL();iter++)
	{
		if(i == index)
		{
			delete iter.Remove();
			return;
		}
		i++;
	}
}
void Graph_Node::RemoveEdges()
{
	/**< Create List Iterator for the Edges in this Node */
	/**< Traverse the List and remove every Node */
	for(ListIterator<Edge*> iter(&mEdges);!iter.IsNuLL();iter++)
	{
		delete iter.Remove();
	}
}
int Graph_Node::GetEdgeCount()
{
	return mEdges.GetSize();
}
Physics::Vector Graph_Node::GetPosition()
{
	return mPosition;
}
Physics::Vector Graph_Node::GetDirection()
{
	return mDirection;
}
float Graph_Node::GetWeight(int index)
{
	return mEdges.At(index)->mWeight;
}
float Graph_Node::GetWeight(Graph_Node* to)
{
	/**< Create List Iterator for the Edges in this Node */
	/**< Traverse the List till the To = the Graph given Node */
	/**< Then return the Weight of the Edge to the Node */
	for(ListIterator<Edge*> iter(&mEdges); !iter.IsNuLL(); iter++)
	{
		if(iter.Value()->mTo == to)
		{
			return iter.Value()->mWeight;
		}
	}
}
float Graph_Node::GetAdvancedWeight(int index)
{
	return mEdges.At(index)->mAdvancedWeight;
}
float Graph_Node::GetAdvancedWeight(Graph_Node* to)
{
	/**< Create List Iterator for the Edges in this Node */
	/**< Traverse the List till the To = the Graph given Node */
	/**< Then return the Advanced Weight of the Edge to the Node */
	for(ListIterator<Edge*> iter(&mEdges); !iter.IsNuLL(); iter++)
	{
		if(iter.Value()->mTo == to)
		{
			return iter.Value()->mAdvancedWeight;
		}
	}
}
Graph_Node* Graph_Node::GetTo(int index)
{
	return mEdges.At(index)->mTo;
}
void Graph_Node::SetPosition(Physics::Vector pos)
{
	mPosition = pos;
}
void Graph_Node::SetDirection(Physics::Vector dir)
{
	mDirection = dir;
}
void Graph_Node::SetHidden(bool hidden)
{
	/**< Create List Iterator for the Edges in this Node */
	/**< Set all Edges too Hidden and the Edges pointing to this Node to Hidden */
	for(ListIterator<Edge*> iter(&mEdges); !iter.IsNuLL(); iter++)
	{
		iter.Value()->mHidden = hidden;
		iter.Value()->mTo->SetHidden(this,hidden);
	}
}
bool Graph_Node::GetHidden(int index)
{
	return mEdges.At(index)->mHidden;
}
bool Graph_Node::GetHidden()
{
	/**< Traverse the List if one of the Edges are not Hidden return false. */
	for(int i = 0; i < mEdges.GetSize(); i++)
	{
		if(mEdges.At(i)->mHidden == false)
		{
			return false;
		}
	}
	return true;
}
void Graph_Node::SetHidden(int index, bool hidden)
{
	mEdges.At(index)->mHidden = hidden;
}
void Graph_Node::SetHidden(Graph_Node* to,bool hidden)
{
	/**< Create List Iterator for the Edges in this Node */
	/**< Traverse the List till the To = the Graph given Node */
	/**< Set that Edge to the bool given */
	for(ListIterator<Edge*> iter(&mEdges); !iter.IsNuLL(); iter++)
	{
		if(iter.Value()->mTo == to)
		{
			iter.Value()->mHidden = hidden;
		}
	}
}
void Graph_Node::SetUsed(bool used)
{
	mUsed = used;
}
bool Graph_Node::GetUsed()
{
	return mUsed;
}
void Graph_Node::SetNarrow(bool narrow)
{
	mNarrow = narrow;
}
bool Graph_Node::GetNarrow()
{
	return mNarrow;
}
bool Graph_Node::IsCornerNode()
{
	return mCornerNode;
}