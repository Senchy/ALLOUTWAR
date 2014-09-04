#include "Faction\GUI\GUI_Items\Image.h"

Image::Image(Ogre::String Name, Ogre::String materialname, Ogre::Vector2 Position, Ogre::Vector2 size,Ogre::Vector2 screensize)
	: Base_GUI( Name
				, materialname
				, 550
				, Position
				, size
				, screensize)
{
}
Image::~Image()
{
}
void Image::SetZorder(float z)
{
	mGUI_Layer->setZOrder( z );
}
void Image::Scale(Ogre::Vector2 scale)
{
	mGUI_Entity->setDimensions(scale.x,scale.y);
}
Ogre::Vector2 Image::GetPosition()
{
	return Ogre::Vector2(mGUI_Entity->getLeft(),mGUI_Entity->getHeight());
}
void Image::Update()
{
}
bool Image::Clicked(Ogre::Vector2 Pos)
{
	return false;
}
void Image::Release()
{
}