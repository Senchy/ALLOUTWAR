#include "Faction\GUI\GUI_Object\ResearchTree.h"

ResearchTree::ResearchTree(Ogre::String Name, Ogre::String materialname,Ogre::Vector2 screensize)
	:	SideMenu( Name
				, materialname
				, 50
				, screensize)
{
}
ResearchTree::~ResearchTree()
{
}
void ResearchTree::Update()
{
	SideMenu::Update();
}
bool ResearchTree::Clicked(Ogre::Vector2 Pos)
{
	return SideMenu::Clicked( Pos);
}
void ResearchTree::Release()
{
	SideMenu::Release();
}