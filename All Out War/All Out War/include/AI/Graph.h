#ifndef GRAPH_H
#define GRAPH_H

#include "AI\Graph_Node.h"

class Graph
{
private:
	/// <value>The List of Nodes that AI units use to more around</value>
	LinkList<Graph_Node*> mNodes;
	/// <value>Struct That is used to find the optimal Path</value>
	struct PathNode{
		/// <value>Pointer to a Graph Node that is being considered for the path </value>
		Graph_Node* mNode;
		/// <value>Pointer to the Path Node that this Path Node is created from</value>
		PathNode* mPrevious;												
		/// <value>The cost it took to get to this node</value>
		float mKnownCost;
		/// <value>Guess of how much it will take to get to the Goal Node</value>
		float mGuess;
		///<summary> 
		///Constructor
		///</summary>
		///<param name="Node">Pointer to the Graph_Node</param>
		///<param name="Previous">Pointer to the previous Path Node</param>
		///<param name="KnownCost">Cost to this point</param>
		///<param name="Guess">Guess to the goal</param>
		PathNode(Graph_Node* Node,PathNode* Previous,float KnownCost,float Guess)
		{
			mNode = Node;
			mPrevious = Previous;
			mKnownCost = KnownCost;
			mGuess = Guess;
		}
	};
public:
	///<summary> 
	///Constructor
	///</summary>
	Graph();
	///<summary> 
	///Destructor
	///</summary>
	~Graph();
	///<summary> 
	///Adds a new node to the link list of Graph Nodes at a set position.
	///Sets the direction of the new node to null.
	///</summary>
	///<param name="pos">The position of the new node</param>
	void AddNode(Physics::Vector pos);
	///<summary> 
	///Add a Graph Node tp the link list of Graph Nodes.
	///</summary>
	///<param name="node">Pointer to the Graph Node we are adding to the Graph</param>
	void AddNode(Graph_Node* node);
	///<summary> 
	///Add Edge to the Node given to the other Node given.
	///Only add an Edge to the Node if the Y distance is in range.
	///Set weight based on XZ distance.
	///Set advanced weight based on XZ distance and Y difference.
	///</summary>
	///<param name="From">Pointer to the Node we are adding an edge</param>
	///<param name="To">Pointer to Node the Edge points too </param>
	///<returns>If an edge is added</returns>
	bool AddEdge(Graph_Node* From, Graph_Node* To);
	///<summary> 
	///Find the Node in the link list that has the position given.
	///If we found the Node remove it from the link list of Graph Nodes.
	///Go through all the Edges in the Node and remove the Edges in other Nodes that point to this Node.
	///Remove all the Edges from the Node.
	///Delete the Node.
	///</summary>
	///<param name="pos">The position of the Node we want to remove</param>
	void RemoveNode(Physics::Vector pos);
	///<summary> 
	///Find the Node in the link list.
	///If we found the Node remove it from the link list of the Graph Nodes.
	///Go through all the Edges in the Node and remove the Edges in other Nodes that point to this Node.
	///Remove all the Edges from the Node.
	///Delete the Node.
	///</summary>
	///<param name="node">Pointer to the Node we want to remove</param>
	void RemoveNode(Graph_Node* node);
	///<summary> 
	///Get the Node that is at the given index.
	///</summary>
	///<param name="index">Position of the Node in the link list</param>
	///<returns>Pointer to the Graph Node we Want</returns>
	Graph_Node* getGRAPHNODE(int index);
	///<summary> 
	///Get the size of the Link list of Graph Nodes.
	///</summary>
	///<returns>the size of the link list of Graph Nodes</returns>
	int Graphsize();
	///<summary> 
	///Get the shortest Path from the start position to the end position.
	///First find the closest Nodes to the Start and End Positions and set them as our start Node and goal Node.
	///Create a list of Nodes that we have evalutated(ClosedList) and a list of Nodes we have yet to Evaluate(OpenList).
	///Add a Path Node made from the start Node to the OpenList.
	///Then while the OpenList still has Nodes in it, pop the first Node from the Openlist and Push the node onto the Closedlist.
	///Create new Path Nodes from the Edges of the poped Node.
	///Add the Path Nodes onto the OpenList sorted by the Guess cost.
	///If we reach the Goal Node
	///Create Path by going back throught the ClosedList, starting with the Goal Node adding the Nodes too the Path
	///</summary>
	///<param name="Startpos">Position that we start from</param>
	///<param name="EndPos">Position that we want to get to</param>
	///<param name="Path">Empty list that we store the Result in</param>
	///<param name="Advanced">If we want to search with advanced weights</param>
	void GetPath(Physics::Vector Startpos, Physics::Vector EndPos, LinkList<Graph_Node* > *Path, bool Advanced = false);
	///<summary> 
	///Get the shortest Path from the start Node to the end Node.
	///Create a list of Nodes that we have evalutated(ClosedList) and a list of Nodes we have yet to Evaluate(OpenList).
	///Add a Path Node made from the start Node to the OpenList.
	///Then while the OpenList still has Nodes in it, pop the first Node from the Openlist and Push the node onto the Closedlist.
	///Create new Path Nodes from the Edges of the poped Node.
	///Add the Path Nodes onto the OpenList sorted by the Guess cost.
	///If we reach the Goal Node
	///Create Path by going back throught the ClosedList, starting with the Goal Node adding the Nodes too the Path
	///</summary>
	///<param name="StartNode">Position that we start from</param>
	///<param name="EndNode">Position that we want to get to</param>
	///<param name="Path">Empty list that we store the Result in</param>
	///<param name="Advanced">If we want to search with advanced weights</param>
	void GetPath(Graph_Node* StartNode, Graph_Node* EndNode, LinkList<Graph_Node* > *Path, bool Advanced = false);
};

#endif