#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include "Physics\Vector.h"
#include "LinkList.h"

class Graph_Node
{
private:
	/// <value>Position of the Node </value>
	Physics::Vector mPosition;
	/// <value>Direction Of the Node</value>
	Physics::Vector mDirection;
	/// <value>If the Node has been iterated through</value>
	bool			mUsed;
	/// <value>If the Node is on the corner of an object</value>
	bool			mCornerNode;
	/// <value>If the Node is inbetween to objects</value>
	bool			mNarrow;
	/// <value>Struct that connects a Node to another Node with information on how to get to the next Node</value>
	struct Edge
	{
		/// <value>Pointer to the Node that it connects to</value>
		Graph_Node* mTo;							
		/// <value>If the Edge is not available</value>
		bool mHidden;
		/// <value>Cost it takes to get to the next Node</value>
		float mWeight;
		/// <value>Additional cost it takes to get to the next Node when doing an advanced search</value>
		float mAdvancedWeight;			
	};
	/// <value>List of Edges that this Node has </value>
	LinkList<Edge*> mEdges;	
public:		
	///<summary> 
	///Constructor
	///</summary>
	///<param name="pos">Position of the Node</param>
	///<param name="dir">Direction Of the Node</param>
	///<param name="cornernode">If this Node is a corner node (Default : false)</param>
	Graph_Node(Physics::Vector pos, Physics::Vector dir, bool cornernode = false);
	///<summary> 
	///Destructor
	///</summary>
	~Graph_Node();


	///<summary> 
	///Get the position of this Node
	///</summary>
	///<returns>Position of this Node</returns>
	Physics::Vector GetPosition();
	///<summary> 
	///Get the direction of this Node
	///</summary>
	///<returns>Direction of this Node</returns>
	Physics::Vector GetDirection();
	///<summary> 
	///Get if the Node is used
	///</summary>
	///<returns>If the Node is used</returns>
	bool GetUsed();
	///<summary> 
	///Get if the Node is narrow
	///</summary>
	///<returns>If the Node is narrow</returns>
	bool GetNarrow();
	///<summary> 
	///Get if the Node is a corner Node
	///</summary>
	///<returns>If the Node is a corner Node</returns>
	bool IsCornerNode();
	///<summary> 
	///Set the position of this Node
	///</summary>
	///<param name="pos">New position of the Node</param>
	void SetPosition(Physics::Vector pos);
	///<summary> 
	///Set the direction of the Node
	///</summary>
	///<param name="dir">New direction of the Node</param>
	void SetDirection(Physics::Vector dir);
	///<summary> 
	///Sets if the Node is used or not 
	///</summary>
	///<param name="used">If the Node is used</param>
	void SetUsed(bool used);
	///<summary> 
	///Sets if the Node is narrow or not 
	///</summary>
	///<param name="narrow">If the Node is narrow</param>
	void SetNarrow(bool narrow);
	///<summary> 
	///Get the number of Edges that this Node has
	///</summary>
	///<returns>Size of the list of Edges</returns>
	int GetEdgeCount();
	///<summary> 
	///Create a New Edge.
	///Add it to the list of Edges that connects this Node to other Nodes.
	///</summary>
	///<param name="to">Pointer to the Node this Node is Connected too</param>
	///<param name="weight">Weight of the Edge</param>
	///<param name="advanced">Advanced Weight of the Edge</param>
	void AddEdge(Graph_Node* to, float weight, float advanced);
	///<summary> 
	///Find Edge that points to the Node pass.
	///Remove the Edge if found.
	///</summary>
	///<param name="to">Pointer to the Node that an Edge points to</param>
	void RemoveEdge(Graph_Node* to);
	///<summary> 
	///Find Edge at the index given.
	///Remove the Edge if found.
	///</summary>
	///<param name="index">Index to the Edge we want to Remove</param>
	void RemoveEdge(int index);
	///<summary> 
	///Traverse the Edges in this Node and remove each Edge
	///</summary>
	void RemoveEdges();


	///<summary> 
	///Set hidden of all Edges in this Node
	///</summary>
	///<param name="hidden">If all Edges are Hidden</param>
	void SetHidden(bool hidden);
	///<summary> 
	///Find Edge at the index given.
	///Set hidden of the Edge.
	///</summary>
	///<param name="index">Index to the Edge we want to set</param>
	///<param name="hidden">If the Edge is Hidden</param>
	void SetHidden(int index, bool hidden);
	///<summary> 
	///Find Edge that points to the Node pass.
	///Set hidden of the Edge.
	///</summary>
	///<param name="to">Pointer to the Node that an Edge points to</param>
	///<param name="hidden">If the Edge is Hidden</param>
	void SetHidden(Graph_Node* to,bool hidden);
	///<summary> 
	///Get Edge at a given index, in the list of Edges
	///</summary>
	///<param name="index">Index of an Edge in th list of Edges</param>
	///<returns>Pointer to a Node</returns>
	Graph_Node* GetTo(int index);
	///<summary> 
	///Check if all the Nodes are Hidden
	///</summary>
	///<returns>If Node is completely Hidden</returns>
	bool GetHidden();
	///<summary> 
	///Find Edge at the index given.
	///Get if the Edge is hidden
	///</summary>
	///<param name="index">Index to the Edge we want</param>
	///<returns>If the Edge is Hidden</returns>
	bool GetHidden(int index);
	///<summary> 
	///Find Edge at a given index.
	///Get the weight of the Edge
	///</summary>
	///<param name="index">Index of an Edge in th list of Edges</param>
	///<returns>The weight of the Edge</returns>
	float GetWeight(int index);
	///<summary> 
	///Find Edge that points to the Node pass.
	///Get the weight of the Edge
	///</summary>
	///<param name="to">Pointer to a Node</param>
	///<returns>The weight of the Edge</returns>
	float GetWeight(Graph_Node* to);
	///<summary> 
	///Find Edge at a given index.
	///Get the advanced weight of the Edge
	///</summary>
	///<param name="index">Index of an Edge in th list of Edges</param>
	///<returns>The advanced weight of the Edge</returns>
	float GetAdvancedWeight(int index);
	///<summary> 
	///Find Edge that points to the Node pass.
	///Get the advanced weight of the Edge
	///</summary>
	///<param name="to">Pointer to a Node</param>
	///<returns>The advanced weight of the Edge</returns>
	float GetAdvancedWeight(Graph_Node* to);

};
#endif