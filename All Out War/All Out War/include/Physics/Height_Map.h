#ifndef HEIGHT_MAP_H
#define HEIGHT_MAP_H

#include "AI\Graph.h"
#include "Physics\Physics_Formulas.h"
#include "Physics\HM_Plane.h"
#include "Terrain.h"
#include "ContainerStructs.h"

class HM_Node
{
private:
	/// <value>Pointer to the Graph Node that is on this Height Map Node</value>
	Graph_Node*				mGraphNode;
	/// <value>What way the plane of Height map node is Split</value>
	int						mType;
	/// <value>Pointer to the instance of the Physics Formula</value>
	Physics_Formulas*		mFormula;
	/// <value>The four corners of the Plane</value>
	Physics::Vector			mVertices[4];
	/// <value>The four resistances of each corner of the Plane</value>
	float					mResistance[4];
	/// <value>The direction of the Plane split</value>
	Physics::Vector			mDirection;
	/// <value>Pointer to the Ogre image of the Plane</value>
	Terrain*				mTerrain;
	/// <value>Pointer to the two Height make Planes that make the HM_Node plane</value>
	HM_Plane*				mTriangles[2];
public:
	///<summary> 
	///Constructor
	///</summary>
	///<param name="Points">Array of points for Vertices</param>
	///<param name="res">Array of Resistances</param>
	///<param name="type">Type of plane Split</param>
	HM_Node(Physics::Vector Points[],float res[], int type);
	///<summary> 
	///Destructor
	///</summary>
	~HM_Node();
	///<summary> 
	///Call constructor for Terrain Images
	///</summary>
	///<param name="manager">Pointer to the Ogre Scene Manager</param>
	///<param name="colours">Array of colours for Vertices</param>
	void CreateTerrain(Ogre::SceneManager* manager, Physics::Vector *colours);
	///<summary> 
	///Get the Graph Node on this Height Map
	///</summary>
	///<returns>Graph Node on this Height Map</returns>
	Graph_Node* GetGraphNode();
	///<summary> 
	///Get the position of the Graph Node on this Hight Map Node
	///</summary>
	///<returns>Position of the Graph Node</returns>
	Physics::Vector GetPosition();
	///<summary> 
	///Get a Vertices of the Height Map Plane at an index
	///</summary>
	///<param name="Index">Index of Vertices</param>
	///<returns>Return Vertices</returns>
	Physics::Vector GetVertice(int Index);
	///<summary> 
	///Get a Resistance of the Height Map Plane at an index
	///</summary>
	///<param name="index">Index of Resistance</param>
	///<returns>Return Resistance</returns>
	float GetResistance(int index);
	///<summary> 
	///Get a Triangle of the Height Map Plane at an index
	///</summary>
	///<param name="index">Index of Triangle</param>
	///<returns>Return Triangle</returns>
	HM_Plane* GetTriangle(int index);
	///<summary> 
	///Get a Triangle of the Height Map Plane based on a point
	///Works out what Triangle point is on using split direction
	///</summary>
	///<param name="Pos">Position of the Point</param>
	///<returns>Return Triangle</returns>
	HM_Plane* GetTriangle(Physics::Vector Pos);
	///<summary> 
	///Get the Height of the Plane at a position 
	///</summary>
	///<param name="pos">Position of the Point</param>
	///<returns>Height of the Plane</returns>
	float GetHeight(Physics::Vector pos);
	///<summary> 
	///Get how much damping the speed of the Entity is
	///at a position on the Plane 
	///</summary>
	///<param name="pos">Position of the Point</param>
	///<returns>Height of the Plane</returns>
	float GetDampener(Physics::Vector pos);
	///<summary> 
	///Shoot ray into the World and Check if it hits this Plane
	///</summary>
	///<param name="ray">Ray Details</param>
	///<returns>Returns new distance of Ray</returns>
	float CheckRay(Ray ray);
};

class Height_Map
{
private:
	/// <value>Pointer to Graph of AI Nodes</value>
	Graph* mGraph;
	/// <value>2d array of Hight Map planes</value>
	HM_Node*** mNodes;
	/// <value>Width of Map</value>
	int mWidth;
	/// <value>Height of Map</value>
	int mHeight;
	///<summary> 
	///Get the Values for the Height Map node based on Image Pixel colour
	///</summary>
	///<param name="gvalue">(Ref)A pixel colour of the image </param>
	///<param name="cv">(Ref)New colour value of the Vertex</param>
	///<param name="res">(Ref)New resistance value of the Vertex</param>
	void GetTextureValues(GroundType gvalue, Physics::Vector& cv, float& res);
	///<summary> 
	///Set a group of AI Graph Nodes hidden value
	///</summary>
	///<param name="nodeone">Graph Node</param>
	///<param name="nodetwo">Graph Node</param>
	///<param name="nodethree">Graph Node</param>
	///<param name="Change">Hidden Value</param>
	void ChangeNodeSet(Graph_Node* nodeone,Graph_Node* nodetwo,Graph_Node* nodethree,bool Change);
public:
	///<summary> 
	///Constructor
	///</summary>
	///<param name="width">Width of Map</param>
	///<param name="height">Height of Map</param>
	///<param name="graph">Pointer to the Graph of AI Nodes</param>
	Height_Map(int width, int height, Graph* graph);	
	///<summary> 
	///Destructor
	///</summary>
	~Height_Map();
	///<summary> 
	///Create a HM_Node at a position in the Height Map Array
	///</summary>
	///<param name="x">X position in Array of Height Map Nodes</param>
	///<param name="y">Y position in Array of Height Map Nodes</param>
	///<param name="gvalue">Pixel colour on Image</param>
	///<param name="type">Plane Split Type</param>
	///<param name="manager">Pointer to the Ogre Scene Manager</param>
	void SetNodes(int x, int y, Physics::Vector* Points,GroundType* gvalue, int type,Ogre::SceneManager* manager);
	///<summary> 
	///Add a corner AI Node to the Graph.
	///Use the Vertices position of the object and the direction of the node 
	///to figure out what happened to the Graph
	///</summary>
	///<param name="vertpos">Position of the vertices that the Node is being created beside</param>
	///<param name="Dir">Direction of the AI Node</param>
	///<param name="offset">Pointer to an Array of Shapes (Default : 8)</param>
	///<returns>New Graph Node</returns>
	Graph_Node* AddCornerNode(Physics::Vector vertpos, Physics::Vector Dir, float offset = 8);
	///<summary> 
	///Remove Node from Graph
	///</summary>
	///<param name="removenode">Node we want to remove from Graph</param>
	///<param name="Objectpos">The Entities position</param>
	void RemoveCornerNode(Graph_Node* removenode, Physics::Vector Objectpos);
	///<summary> 
	///Adds Edges from Node to all the Nodes around The X,Y position of
	///the Array of Height Map Nodes
	///</summary>
	///<param name="NewNode">Pointer to Graph Node</param>
	///<param name="xNodePosition">X position in Array of Height Map Nodes</param>
	///<param name="yNodePosition">Y position in Array of Height Map Nodes</param>
	void AttachEdgeToNode(Graph_Node* NewNode,int xNodePosition, int yNodePosition);
	///<summary> 
	///Removes Edges from Node to all the Nodes around The X,Y position of
	///the Array of Height Map Nodes
	///</summary>
	///<param name="NewNode">Pointer to Graph Node</param>
	///<param name="xNodePosition">X position in Array of Height Map Nodes</param>
	///<param name="yNodePosition">Y position in Array of Height Map Nodes</param>
	void RemoveEdgeToNode(Graph_Node* Node,int xNodePosition, int yNodePosition);
	///<summary> 
	///Adds Edges to all the Nodes around The X,Y position of
	///the Array of Height Map Nodes
	///</summary>
	///<param name="xNodePosition">X position in Array of Height Map Nodes</param>
	///<param name="yNodePosition">Y position in Array of Height Map Nodes</param>
	void INITEdges(int xNodePosition, int yNodePosition);
	///<summary> 
	///Check if a Slopes are usable at X,Y position in Array of Height Map Nodes
	///and keep checking for width amount along the X and height amount along the Y
	///</summary>
	///<param name="x">X position in Array of Height Map Nodes</param>
	///<param name="y">Y position in Array of Height Map Nodes</param>
	///<param name="width">How many Nodes to Check along the x</param>
	///<param name="height">How many Nodes to Check along the y</param>
	///<returns>If Slope is Good to use</returns>
	bool CheckCreationSlopes(int x, int y, int width, int height);
	///<summary> 
	///Get Height Map Node at X,Y position in Array of Height Map Nodes
	///</summary>
	///<param name="x">X position in Array of Height Map Nodes</param>
	///<param name="y">Y position in Array of Height Map Nodes</param>
	///<returns>Pointer to Height Map Node</returns>
	HM_Node* GetNode(int x, int y);
	///<summary> 
	///Get Position of the Graph Node at X,Y position in Array of Height Map Nodes
	///</summary>
	///<param name="x">X position in Array of Height Map Nodes</param>
	///<param name="y">Y position in Array of Height Map Nodes</param>
	///<returns>Position of the Graph Node</returns>
	Physics::Vector GetNodePosition(int x, int y);
	///<summary> 
	///Get Position of a Vertices of a Height Map Node at
	///X,Y position in Array of Height Map Nodes
	///</summary>
	///<param name="x">X position in Array of Height Map Nodes</param>
	///<param name="y">Y position in Array of Height Map Nodes</param>
	///<param name="index">Index to which Vertices we want</param>
	///<returns>Position of the Vertices</returns>
	Physics::Vector GetVertex(int x, int y, int index);
	///<summary> 
	///Check if Ray Hits any Height Map Node
	///</summary>
	///<param name="ray">Ray Details</param>
	///<returns>Returns new distance of Ray</returns>
	float CheckRay(Ray ray);
	///<summary> 
	///Check if the X,Y Values are in Range of the Array of Height Map Nodes
	///</summary>
	///<param name="x">X position in Array of Height Map Nodes</param>
	///<param name="y">Y position in Array of Height Map Nodes</param>
	///<returns>If X,Y values are in range</returns>
	bool CheckNode(int x, int y);
};
#endif