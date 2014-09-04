#include "Faction\GUI\GUI_Object\Table.h"

Table::Table(Ogre::String Name, Ogre::String materialname, Ogre::Vector2 Position, Ogre::Vector2 size,Ogre::Vector2 screensize)
	:	Base_GUI( Name
				, materialname
				, 400
				, Position
				, size
				, screensize)
{
}
Table::~Table()
{
}
void Table::Update()
{
}
bool Table::Clicked(Ogre::Vector2 Pos)
{
	return Base_GUI::Clicked( Pos);
}
void Table::Release()
{
}
void Table::SetPosition(Ogre::Vector2 Pos)
{
	Base_GUI::SetPosition(Pos);
}
void Table::Move(Ogre::Vector2 Distance)
{
	Base_GUI::Move(Distance);
}