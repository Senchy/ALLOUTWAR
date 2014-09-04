#include "Faction\GUI\Player_GUI.h"

Player_GUI::Player_GUI(Ogre::Vector2 screensize)
	:	mCursor("Cursor"
				,"AOW/Cursor_Normal"
				,screensize)
	,	mResearchTable(new ResearchTree("ResearchTree","AOW/BaseTable",screensize))
	,	mTownListTable(new TownListInfo("TownListInfo","AOW/BaseTable",screensize))
	,	mSelectedMenu(new SelectedMenu("SelectedMenu","AOW/SelectMenu",screensize))
	,	mCommandMenu(new CommandMenu("CommandMenu","AOW/CommandTable",screensize))
	,	mMiniMap(new MiniMap("MiniMap","AOW/BaseTable",screensize))
	,	mCreateType(Entity_Name::None)
{
}
Player_GUI::~Player_GUI()
{
}
bool Player_GUI::Click()
{
	/**< If the Cursor position is inside any Entity when clicked return true */
	mCursor.Click(ClickType::Move);
	Ogre::Vector2 cursorpos = mCursor.getPosition();
	if(mResearchTable->Clicked(cursorpos)) {return true;}
	if(mTownListTable->Clicked(cursorpos)) {return true;}
	if(mSelectedMenu->Clicked(cursorpos)) {return true;}
	if(mCommandMenu->Clicked(cursorpos)) {return true;}
	if(mMiniMap->Clicked(cursorpos)) {return true;}
	return false;
}
void Player_GUI::Release()
{
	mCursor.ClickRelease();
	mResearchTable->Release();
	mTownListTable->Release();
	mSelectedMenu->Release();
	mCommandMenu->Release();
	mMiniMap->Release();
}
void Player_GUI::Update(float timesincelastframe)
{
	mCursor.Update();
	mResearchTable->Update();
	mTownListTable->Update();
	mSelectedMenu->Update();
	mCommandMenu->Update();
	mMiniMap->Update();
}