#include "Faction\GUI\GUI_Items\MiniMapNode.h"

MiniMapNode::MiniMapNode(Ogre::String Name, Ogre::String materialname,Ogre::Vector2 screensize)
	: Base_GUI( Name
				, materialname
				, 550
				, Ogre::Vector2(0.5,0.5)
				, Ogre::Vector2(100,100)
				, screensize)
{
}
MiniMapNode::~MiniMapNode()
{
}
void MiniMapNode::Update()
{
}
bool MiniMapNode::Clicked(Ogre::Vector2 Pos)
{
	return false;
}
void MiniMapNode::Release()
{
}