#include "Physics\Height_Map.h"

HM_Node::HM_Node(Physics::Vector Points[],float res[], int type)
	:	mFormula(Physics_Formulas::getInstance())
	,	mType(type % 2)
{
	/**< Set all resistances and Points passed in */
	for(int i = 0; i< 4; i++)
	{
		mVertices[i] = Points[i];
		mResistance[i] = res[i];
	}
	/**< Based on Type create different direction split for the triangles */
	if(mType == 0)
	{
		mDirection = (Points[2] - Points[1]);
		mGraphNode = new Graph_Node((Points[2] + Points[1]) / 2,Physics::Vector(0));
		Physics::Vector FirstTrianglePoints[3] = {Points[1],Points[0],Points[2]};
		mTriangles[1] = new HM_Plane(FirstTrianglePoints);
		Physics::Vector SecondTrianglePoints[3] = {Points[3],Points[1],Points[2]};
		mTriangles[0] = new HM_Plane(SecondTrianglePoints);
	}
	else
	{
		mDirection = (Points[3] - Points[0]);
		mGraphNode = new Graph_Node((Points[3] + Points[0]) / 2,Physics::Vector(0));
		Physics::Vector FirstTrianglePoints[3] = {Points[0],Points[3],Points[1]};
		mTriangles[0] = new HM_Plane(FirstTrianglePoints);
		Physics::Vector SecondTrianglePoints[3] = {Points[0],Points[2],Points[3]};
		mTriangles[1] = new HM_Plane(SecondTrianglePoints);
	}
}
Graph_Node* HM_Node::GetGraphNode()
{
	return mGraphNode;
}
void HM_Node::CreateTerrain(Ogre::SceneManager* manager, Physics::Vector *colours)
{
	mTerrain = new Terrain(manager,mType,mVertices,colours);
}
HM_Node::~HM_Node()
{
	mTriangles[0]->~HM_Plane();
	mTriangles[0] = 0;
	mTriangles[1]->~HM_Plane();
	mTriangles[1] = 0;
}
Physics::Vector HM_Node::GetPosition()
{
	return mGraphNode->GetPosition();
}
Physics::Vector HM_Node::GetVertice(int Index)
{
	return mVertices[Index];
}
float HM_Node::GetHeight(Physics::Vector pos)
{
	/**< Get which plane we are on the get height of point on the plane */
	HM_Plane* plane = GetTriangle(pos);
	return mFormula->PLANE_GetHeight(plane->GetNormal(), plane->GetVertices(0), pos);
}
HM_Plane* HM_Node::GetTriangle(int index)
{
	return mTriangles[index];
}
HM_Plane* HM_Node::GetTriangle(Physics::Vector Pos)
{
	/**< Get which triangle we are on based on the directional split of the plane */
	if(mFormula->PLANE_IsOnDifference(Physics::Vector(-mDirection.z,0,mDirection.x).Normalise_copy(),GetPosition(),Pos) < 0)
	{
		return mTriangles[0];
	}
	else
	{
		return mTriangles[1];
	}
}
float HM_Node::CheckRay(Ray ray)
{
	Physics::Vector pos = GetPosition();
	Physics::Vector Point = mFormula->PLANE_GetLineIntersection(mTriangles[1]->GetVertices(0),mTriangles[1]->GetNormal(),ray.mStartPosition,ray.mDirection);
	/**< Check is the Point on the plane */
	if(Point.x < (pos.x + 10) && Point.x > (pos.x - 10) && Point.z < (pos.z + 10) && Point.z > (pos.z - 10))
	{	
		/**< If the point is on the other triangle get the position on the other triangle */
		if(mTriangles[0] == GetTriangle(Point))
		{
			Point = mFormula->PLANE_GetLineIntersection(mTriangles[0]->GetVertices(0),mTriangles[0]->GetNormal(),ray.mStartPosition,ray.mDirection);
		}
		return ((Point - ray.mStartPosition).length() / ray.mDistance);
	}
	return 1.0f;
}
float HM_Node::GetResistance(int index)
{
	return mResistance[index];
}
float HM_Node::GetDampener(Physics::Vector pos)
{
	/**< Translate all the points back to the center point */
	pos -= GetPosition();
	float Proximity_To_Point[4] = { 10 - pos.x + pos.z,
									10 + pos.x + pos.z,
									10 + pos.x - pos.z,
									10 - pos.x - pos.z};
	/**< Add to the Proximity_To_Point based on how close the position is to each point */
	if(pos.x < 0)
	{
		Proximity_To_Point[1] += pos.x;
		Proximity_To_Point[2] += pos.x;
	}
	else if(pos.x > 0)
	{
		Proximity_To_Point[0] -= pos.x;
		Proximity_To_Point[3] -= pos.x;
	}
	if(pos.z < 0)
	{
		Proximity_To_Point[0] += pos.z;
		Proximity_To_Point[1] += pos.z;
	}
	else if(pos.z > 0)
	{
		Proximity_To_Point[2] -= pos.z;
		Proximity_To_Point[3] -= pos.z;
	}
	/**< If any are less than 0 set them to 0 */
	for(int i = 0; i< 4; i++)
	{
		if(Proximity_To_Point[i] < 0){	Proximity_To_Point[i] = 0; }
	}
	return((Proximity_To_Point[0] * mResistance[0]) + (Proximity_To_Point[1] * mResistance[1]) + (Proximity_To_Point[2] * mResistance[2]) + (Proximity_To_Point[3] * mResistance[3]))
			/	(Proximity_To_Point[0] + Proximity_To_Point[1] + Proximity_To_Point[2] + Proximity_To_Point[3]);
}


Height_Map::Height_Map(int width, int height, Graph* graph)
	:	mWidth(width),
		mHeight(height),
		mGraph(graph)
{
	/**< Set size of 2d array*/
	mNodes = new HM_Node**[width];
	for(int w = 0; w < width; w++)
		mNodes[w] = new HM_Node*[height];
}
Height_Map::~Height_Map()
{
}
void Height_Map::ChangeNodeSet(Graph_Node* nodeone,Graph_Node* nodetwo,Graph_Node* nodethree, bool Change)
{
	/**< Change hidden for each point to the other points*/
	nodeone->SetHidden(nodetwo,Change);
	nodeone->SetHidden(nodethree,Change);
	nodetwo->SetHidden(nodeone,Change);
	nodetwo->SetHidden(nodethree,Change);
	nodethree->SetHidden(nodeone,Change);
	nodethree->SetHidden(nodetwo,Change);
}
void Height_Map::GetTextureValues(GroundType gvalue, Physics::Vector& cv, float& res)
{
	/**< Get vertex color and resistance based on image pixel value */
	switch(gvalue)
	{
	case(Long_Grass):
		cv = Physics::Vector(0,1,0);
		res = 1;
		break;
	case(Short_Grass):
		cv = Physics::Vector(0,0.9,0);
		res = 1;
		break;
	case(Rocky_Grass):
		cv = Physics::Vector(0,0.8,0);
		res = 1;
		break;
	case(Mud_Grass):
		cv = Physics::Vector(0,0.7,0);
		res = 1;
		break;
	case(Mud):
		cv = Physics::Vector(0,0.6,0);
		res = 1;
		break;
	case(Swamp_Grass):
		cv = Physics::Vector(0,0.5,0);
		res = 1;
		break;
	case(Swamp):
		cv = Physics::Vector(0,0.4,0);
		res = 1;
		break;
	case(Light_Forrest):
		cv = Physics::Vector(0,0.3,0);
		res = 1;
		break;
	case(Dense_Forrest):
		cv = Physics::Vector(0,0.2,0);
		res = 1;
		break;
	case(Beach_Sand):
		cv = Physics::Vector(0,0.1,0);
		res = 1;
		break;
	case(Desert_Sand):
		cv = Physics::Vector(0,0.09,0);
		res = 1;
		break;
	case(Desert_Plain):
		cv = Physics::Vector(0,0.08,0);
		res = 1;
		break;
	case(Rocky_Sand):
		cv = Physics::Vector(0,0.07,0);
		res = 1;
		break;
	case(Sea_Shore):
		cv = Physics::Vector(0,0.3,0.9);
		res = 1;
		break;
	case(Deep_Sea):
		cv = Physics::Vector(0,0,0.1);
		res = 1;
		break;
	case(River_Bank):
		cv = Physics::Vector(0,0.6,1);
		res = 1;
		break;
	case(Stream):
		cv = Physics::Vector(0,0.3,1);
		res = 1;
		break;
	case(River):
		cv = Physics::Vector(0,0,1);
		res = 1;
		break;
	case(River_Rapids):
		cv = Physics::Vector(0,0,0.5);
		res = 1;
		break;
	default:
		cv = Physics::Vector(0,0,0);
		res = 1;
		break;
	}
}
void Height_Map::SetNodes(int x, int y, Physics::Vector* Points,GroundType* gvalue, int type,Ogre::SceneManager* manager)
{
	float res[4];
	Physics::Vector colors[4];
	/**< Get all the colour and resistances for each corner of the node */
	GetTextureValues(gvalue[0],colors[0],res[0]);
	GetTextureValues(gvalue[1],colors[1],res[1]);
	GetTextureValues(gvalue[2],colors[2],res[2]);
	GetTextureValues(gvalue[3],colors[3],res[3]);
	/**< Create new node */
	mNodes[x][y] = new HM_Node(Points,res,type);
	/**< Create Image for the Node */
	mNodes[x][y]->CreateTerrain(manager,colors);
	/**< Add the Nodes AI Graph Node to the AI Graph */
	mGraph->AddNode(mNodes[x][y]->GetGraphNode());
}
Graph_Node* Height_Map::AddCornerNode(Physics::Vector vertpos, Physics::Vector Dir,float offset)
{
	Physics::Vector NewNodePos = vertpos + Dir * offset;
	HM_Node* NewGraphNode_Node = GetNode(NewNodePos.x / 20, NewNodePos.z / 20);
	NewNodePos.y = NewGraphNode_Node->GetHeight(NewNodePos);
	/**< If the nodes Slope is too steep */
	if(NewGraphNode_Node->GetTriangle(NewNodePos)->GetSlopeAngle() > 0.9)
	{
		return 0;
	}
	/**< If any of the resistances are too strong */
	if( NewGraphNode_Node->GetResistance(0) < 0.1 || 
		NewGraphNode_Node->GetResistance(1) < 0.1 || 
		NewGraphNode_Node->GetResistance(2) < 0.1 || 
		NewGraphNode_Node->GetResistance(3) < 0.1 )
	{
		return 0;
	}
	int Xgraph = 0;
	int Ygraph = 0;
	/**< Round up and down values */
	if(Dir.x > 0) { Xgraph = 1; }
	else if(Dir.x < 0) { Xgraph = -1; }
	if(Dir.z > 0) { Ygraph = 1; }
	else if(Dir.z < 0) { Ygraph = -1; }
	/**< Get node in the Y axis by direction given */
	HM_Node* VertNode = GetNode(int(NewNodePos.x / 20) - Xgraph, int(NewNodePos.z / 20) - Ygraph);
	/**< Get node in the X axis by direction given */
	HM_Node* Verticalnode = GetNode((NewNodePos.x / 20),int(NewNodePos.z / 20) - Ygraph);
	/**< Get node in the X axis and Y axis by direction given */
	HM_Node* Horizontalnode = GetNode(int(NewNodePos.x / 20) - Xgraph, NewNodePos.z / 20);
	Graph_Node* newNode = new Graph_Node(NewNodePos,Dir,true);	
	float DisFromCornerToNode = (NewGraphNode_Node->GetPosition() - vertpos).lengthxz();
	/**< If the Node is too close to the corner that a node is begin added to the Graph */
	/**< Else add Edges from the node begin added to the Node we would have removed */
	if(DisFromCornerToNode < (offset + 4))
	{
		NewGraphNode_Node->GetGraphNode()->SetHidden(true);
	}
	else
	{
		mGraph->AddEdge(newNode,NewGraphNode_Node->GetGraphNode());
		mGraph->AddEdge(NewGraphNode_Node->GetGraphNode(),newNode);
	}
	/**< Hide edges going from the Nodes */
	ChangeNodeSet(VertNode->GetGraphNode(),	Verticalnode->GetGraphNode(), Horizontalnode->GetGraphNode(), true);
	AttachEdgeToNode(newNode,NewNodePos.x / 20,NewNodePos.z / 20);
	return newNode;
}
void Height_Map::RemoveCornerNode(Graph_Node* removenode, Physics::Vector Objectpos)
{
	HM_Node* removeGraphNode_Node = GetNode(removenode->GetPosition().x / 20, removenode->GetPosition().z / 20);
	Physics::Vector Dir = Physics::Vector(removenode->GetPosition().x - Objectpos.x, 0, removenode->GetPosition().z - Objectpos.z).Normalise_copy(); 
	int Xgraph = 0;
	int Ygraph = 0;
	/**< Round up and down values */
	if(Dir.x > 0) { Xgraph = 1; }
	else if(Dir.x < 0) { Xgraph = -1; }
	if(Dir.z > 0) { Ygraph = 1; }
	else if(Dir.z < 0) { Ygraph = -1; }
	/**< Get node in the Y axis by direction given */
	HM_Node* VertNode = GetNode(int(removenode->GetPosition().x / 20) - Xgraph, int(removenode->GetPosition().z / 20) - Ygraph);
	/**< Get node in the X axis by direction given */
	HM_Node* Verticalnode = GetNode((removenode->GetPosition().x / 20),int(removenode->GetPosition().z / 20) - Ygraph);
	/**< Get node in the X axis and Y axis by direction given */
	HM_Node* Horizontalnode = GetNode(int(removenode->GetPosition().x / 20) - Xgraph, removenode->GetPosition().z / 20);
	/**< Unhide node that is on the same HM Node */
	removeGraphNode_Node->GetGraphNode()->SetHidden(false);
	removeGraphNode_Node->GetGraphNode()->RemoveEdge(removenode);
	/**< Unhide edges going from the Nodes */
	ChangeNodeSet(VertNode->GetGraphNode(),	Verticalnode->GetGraphNode(), Horizontalnode->GetGraphNode(), false);
	RemoveEdgeToNode(removenode,removenode->GetPosition().x / 20,removenode->GetPosition().z / 20);
	mGraph->RemoveNode(removenode);
}
void Height_Map::RemoveEdgeToNode(Graph_Node* Node,int xNodePosition, int yNodePosition)
{
	/**< Remove all edges to this node */
	if(CheckNode(xNodePosition,yNodePosition-1))
	{
		mNodes[xNodePosition][yNodePosition-1]->GetGraphNode()->RemoveEdge(Node);
	}
	if(CheckNode(xNodePosition,yNodePosition+1))
	{
		mNodes[xNodePosition][yNodePosition+1]->GetGraphNode()->RemoveEdge(Node);
	}
	if(CheckNode(xNodePosition-1,yNodePosition))
	{
		mNodes[xNodePosition-1][yNodePosition]->GetGraphNode()->RemoveEdge(Node);
	}
	if(CheckNode(xNodePosition+1,yNodePosition))
	{
		mNodes[xNodePosition+1][yNodePosition]->GetGraphNode()->RemoveEdge(Node);
	}
	if(CheckNode(xNodePosition+1,yNodePosition+1))
	{
		mNodes[xNodePosition+1][yNodePosition+1]->GetGraphNode()->RemoveEdge(Node);
	}
	if(CheckNode(xNodePosition-1,yNodePosition-1))
	{
		mNodes[xNodePosition-1][yNodePosition-1]->GetGraphNode()->RemoveEdge(Node);
	}
	if(CheckNode(xNodePosition+1,yNodePosition-1))
	{
		mNodes[xNodePosition+1][yNodePosition-1]->GetGraphNode()->RemoveEdge(Node);
	}
	if(CheckNode(xNodePosition-1,yNodePosition+1))
	{
		mNodes[xNodePosition-1][yNodePosition+1]->GetGraphNode()->RemoveEdge(Node);
	}
}
void Height_Map::AttachEdgeToNode(Graph_Node* NewNode,int xNodePosition, int yNodePosition)
{
	/**< Make sure index is in range */
	/**< Make sure the resistance isnt too low */
	/**< Add edge point to this node and away from this node */
	if(CheckNode(xNodePosition,yNodePosition-1))
	{
		if(mNodes[xNodePosition][yNodePosition]->GetResistance(2) != 0 && mNodes[xNodePosition][yNodePosition]->GetResistance(3) != 0)
		{
			mGraph->AddEdge(NewNode,mNodes[xNodePosition][yNodePosition - 1]->GetGraphNode());
			mGraph->AddEdge(mNodes[xNodePosition][yNodePosition - 1]->GetGraphNode(),NewNode);
		}
	}
	if(CheckNode(xNodePosition,yNodePosition+1))
	{
		if(mNodes[xNodePosition][yNodePosition]->GetResistance(0) != 0 && mNodes[xNodePosition][yNodePosition]->GetResistance(1) != 0)
		{
			mGraph->AddEdge(NewNode,mNodes[xNodePosition][yNodePosition + 1]->GetGraphNode());
			mGraph->AddEdge(mNodes[xNodePosition][yNodePosition + 1]->GetGraphNode(),NewNode);
		}
	}
	if(CheckNode(xNodePosition-1,yNodePosition))
	{
		if(mNodes[xNodePosition][yNodePosition]->GetResistance(0) != 0 && mNodes[xNodePosition][yNodePosition]->GetResistance(2) != 0)
		{
			mGraph->AddEdge(NewNode,mNodes[xNodePosition - 1][yNodePosition]->GetGraphNode());
			mGraph->AddEdge(mNodes[xNodePosition - 1][yNodePosition]->GetGraphNode(),NewNode);
		}
	}
	if(CheckNode(xNodePosition+1,yNodePosition))
	{
		if(mNodes[xNodePosition][yNodePosition]->GetResistance(1) != 0 && mNodes[xNodePosition][yNodePosition]->GetResistance(3) != 0)
		{
			mGraph->AddEdge(NewNode,mNodes[xNodePosition + 1][yNodePosition]->GetGraphNode());
			mGraph->AddEdge(mNodes[xNodePosition + 1][yNodePosition]->GetGraphNode(),NewNode);
		}
	}
	if(CheckNode(xNodePosition+1,yNodePosition+1))
	{
		if(mNodes[xNodePosition][yNodePosition]->GetResistance(1) != 0)
		{
			mGraph->AddEdge(NewNode,mNodes[xNodePosition + 1][yNodePosition + 1]->GetGraphNode());
			mGraph->AddEdge(mNodes[xNodePosition + 1][yNodePosition + 1]->GetGraphNode(),NewNode);
		}
	}
	if(CheckNode(xNodePosition-1,yNodePosition-1))
	{
		if(mNodes[xNodePosition][yNodePosition]->GetResistance(2) != 0)
		{
			mGraph->AddEdge(NewNode,mNodes[xNodePosition - 1][yNodePosition - 1]->GetGraphNode());
			mGraph->AddEdge(mNodes[xNodePosition - 1][yNodePosition - 1]->GetGraphNode(),NewNode);
		}
	}
	if(CheckNode(xNodePosition+1,yNodePosition-1))
	{
		if(mNodes[xNodePosition][yNodePosition]->GetResistance(3) != 0)
		{
			mGraph->AddEdge(NewNode,mNodes[xNodePosition + 1][yNodePosition - 1]->GetGraphNode());
			mGraph->AddEdge(mNodes[xNodePosition + 1][yNodePosition - 1]->GetGraphNode(),NewNode);
		}
	}
	if(CheckNode(xNodePosition-1,yNodePosition+1))
	{
		if(mNodes[xNodePosition][yNodePosition]->GetResistance(0) != 0)
		{
			mGraph->AddEdge(NewNode,mNodes[xNodePosition - 1][yNodePosition + 1]->GetGraphNode());
			mGraph->AddEdge(mNodes[xNodePosition - 1][yNodePosition + 1]->GetGraphNode(),NewNode);
		}
	}
}
void Height_Map::INITEdges(int xNodePosition, int yNodePosition)
{
	Physics::Vector dirsum = Physics::Vector(0);
	bool CheckNarrow = false;
	/**< Make sure index is in range */
	/**< Make sure the resistance isnt too low */
	/**< Add edge point to this node and away from this node */
	if(CheckNode(xNodePosition,yNodePosition-1))
	{
		if(mNodes[xNodePosition][yNodePosition]->GetResistance(2) != 0 && mNodes[xNodePosition][yNodePosition]->GetResistance(3) != 0)
		{
			if(mGraph->AddEdge(mNodes[xNodePosition][yNodePosition]->GetGraphNode(),mNodes[xNodePosition][yNodePosition - 1]->GetGraphNode()))
			{
				dirsum += Physics::Vector(0,0,-1);
				CheckNarrow = true;
			}
		}
	}
	if(CheckNode(xNodePosition,yNodePosition+1))
	{
		if(mNodes[xNodePosition][yNodePosition]->GetResistance(0) != 0 && mNodes[xNodePosition][yNodePosition]->GetResistance(1) != 0)
		{
			if(mGraph->AddEdge(mNodes[xNodePosition][yNodePosition]->GetGraphNode(),mNodes[xNodePosition][yNodePosition + 1]->GetGraphNode()))
			{
				dirsum += Physics::Vector(0,0,1);
				CheckNarrow = true;
			}
		}
	}
	if(!CheckNarrow)
	{
		mNodes[xNodePosition][yNodePosition]->GetGraphNode()->SetNarrow(true);
	}
	CheckNarrow = false;
	if(CheckNode(xNodePosition-1,yNodePosition))
	{
				
		if(mNodes[xNodePosition][yNodePosition]->GetResistance(0) != 0 && mNodes[xNodePosition][yNodePosition]->GetResistance(2) != 0)
		{
			if(mGraph->AddEdge(mNodes[xNodePosition][yNodePosition]->GetGraphNode(),mNodes[xNodePosition - 1][yNodePosition]->GetGraphNode()))
			{
				dirsum += Physics::Vector(-1,0,0);
				CheckNarrow = true;
			}
		}
	}
	if(CheckNode(xNodePosition+1,yNodePosition))
	{
		if(mNodes[xNodePosition][yNodePosition]->GetResistance(1) != 0 && mNodes[xNodePosition][yNodePosition]->GetResistance(3) != 0)
		{
			if(mGraph->AddEdge(mNodes[xNodePosition][yNodePosition]->GetGraphNode(),mNodes[xNodePosition + 1][yNodePosition]->GetGraphNode()))
			{
				dirsum += Physics::Vector(1,0,0);
				CheckNarrow = true;
			}
		}
	}
	if(!CheckNarrow)
	{
		mNodes[xNodePosition][yNodePosition]->GetGraphNode()->SetNarrow(true);
	}
	CheckNarrow = false;
	if(CheckNode(xNodePosition+1,yNodePosition+1))
	{
		if(mNodes[xNodePosition][yNodePosition]->GetResistance(1) != 0)
		{
			if(mGraph->AddEdge(mNodes[xNodePosition][yNodePosition]->GetGraphNode(),mNodes[xNodePosition + 1][yNodePosition + 1]->GetGraphNode()))
			{
				dirsum += Physics::Vector(1,0,1);
				CheckNarrow = true;
			}
		}
	}
	if(CheckNode(xNodePosition-1,yNodePosition-1))
	{
		if(mNodes[xNodePosition][yNodePosition]->GetResistance(2) != 0)
		{
			if(mGraph->AddEdge(mNodes[xNodePosition][yNodePosition]->GetGraphNode(),mNodes[xNodePosition - 1][yNodePosition - 1]->GetGraphNode()))
			{
				dirsum += Physics::Vector(-1,0,-1);
				CheckNarrow = true;
			}
		}
	}
	if(!CheckNarrow)
	{
		mNodes[xNodePosition][yNodePosition]->GetGraphNode()->SetNarrow(true);
	}
	CheckNarrow = false;
	if(CheckNode(xNodePosition+1,yNodePosition-1))
	{
		if(mNodes[xNodePosition][yNodePosition]->GetResistance(3) != 0)
		{
			if(mGraph->AddEdge(mNodes[xNodePosition][yNodePosition]->GetGraphNode(),mNodes[xNodePosition + 1][yNodePosition - 1]->GetGraphNode()))
			{
				dirsum += Physics::Vector(1,0,-1);
				CheckNarrow = true;
			}
		}
	}
	if(CheckNode(xNodePosition-1,yNodePosition+1))
	{
		if(mNodes[xNodePosition][yNodePosition]->GetResistance(0) != 0)
		{
			if(mGraph->AddEdge(mNodes[xNodePosition][yNodePosition]->GetGraphNode(),mNodes[xNodePosition - 1][yNodePosition + 1]->GetGraphNode()))
			{
				dirsum += Physics::Vector(-1,0,1);
				CheckNarrow = true;
			}
		}
	}
	mNodes[xNodePosition][yNodePosition]->GetGraphNode()->SetDirection(dirsum.Normalise_copy());
	if(!CheckNarrow)
	{
		mNodes[xNodePosition][yNodePosition]->GetGraphNode()->SetNarrow(true);
	}
}
bool Height_Map::CheckNode(int x, int y)
{
	/**< Check if index is in range */
	if(x < 0 || x >= mWidth || y < 0 || y >= mHeight)
	{
		return false;
	}
	return true;
}
Physics::Vector Height_Map::GetVertex(int x, int y, int index)
{
	/**< Check if index is in range if not move to the closest available node */
	if(x >= mWidth)		{ x = mWidth - 1; }
	if(y >= mHeight)	{ y = mHeight - 1; }
	if(x < 0)			{ x = 0; }
	if(y < 0)			{ y = 0; }
	return mNodes[x][y]->GetVertice(index);
}
Physics::Vector Height_Map::GetNodePosition(int x, int y)
{
	/**< Check if index is in range if not move to the closest available node */
	if(x >= mWidth)		{ x = mWidth - 1; }
	if(y >= mHeight)	{ y = mHeight - 1; }
	if(x < 0)			{ x = 0; }
	if(y < 0)			{ y = 0; }
	return mNodes[x][y]->GetPosition();
}
HM_Node* Height_Map::GetNode(int x, int y)
{
	/**< Check if index is in range if not move to the closest available node */
	if(x >= mWidth)		{ x = mWidth - 1; }
	if(y >= mHeight)	{ y = mHeight - 1; }
	if(x < 0)			{ x = 0; }
	if(y < 0)			{ y = 0; }
	return mNodes[x][y];
}
float Height_Map::CheckRay(Ray ray)
{
	/**< Check if ray points straight down if it does get Node position */
	if(ray.mDirection.x == 0 && ray.mDirection.z == 0)
	{
		return GetNode(ray.mStartPosition.x, ray.mStartPosition.z)->CheckRay(ray);
	}
	float x = ray.mStartPosition.x/20;
	float z = ray.mStartPosition.z/20;
	int iter = 0;
	int GoalDist = (ray.mDistance + 40) / 20;
	/**< While we havent reached the farthest possible node */
	while(iter < GoalDist)
	{
		float Check = 1.0f;
		/**< Check if index is in range if not set to the closest available node */
		if( x > 0 && x < mWidth && z > 0 && z < mHeight)
		{
			/**< Check if teh ray is hitting this node */
			Check = GetNode(x,z)->CheckRay(ray);
		}
		/**< increment x and z by direction */
		x += ray.mDirection.x;
		z += ray.mDirection.z;
		/**< if hit return */
		if(Check < 1.0f)
		{
			return Check;
		}
		iter++;
	}
	return 1.0f;
}
bool Height_Map::CheckCreationSlopes(int x, int y, int width, int height)
{
	width = x + width;
	height = y + height;
	/**< Check if min index is in range */
	if(x >= mWidth || y >= mHeight || x <= 0 || y <= 0)	
	{ 
		return false; 
	}
	/**< Check if max index is in range */
	if(width >= mWidth || height >= mHeight || width < 0 || height < 0)	
	{
		return false; 
	}
	/**< Go through X vaules and Check if the Slopes arnt too steep and Resistance isnt too strong */
	for(int XIter = x; XIter < width; XIter++)
	{
		/**< Go through Y vaules and Check if the Slopes arnt too steep and Resistance isnt too strong */
		for(int YIter = y; YIter < height; YIter++)
		{
			HM_Node* currentnode = mNodes[XIter][YIter];
			float topslope = currentnode->GetTriangle(0)->GetSlopeAngle();
			float bottomslope = currentnode->GetTriangle(1)->GetSlopeAngle();
			if(currentnode->GetTriangle(0)->GetSlopeAngle() > 0.4 || 
				currentnode->GetTriangle(1)->GetSlopeAngle() > 0.4 ||
				currentnode->GetResistance(0) < 0.1 ||
				currentnode->GetResistance(1) < 0.1 ||
				currentnode->GetResistance(2) < 0.1 ||
				currentnode->GetResistance(3) < 0.1 )
			{
				return false;
			}
		}
	}
	return true;
}