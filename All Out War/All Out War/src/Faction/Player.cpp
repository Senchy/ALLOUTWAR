#include "Faction\Player.h"

Player::Player(Ogre::SceneManager* manager,Height_Map* map, Ogre::Camera* camera, float width, float height)
	:	Faction()
	,	mHeightMap(map)
	,	Player_GUI(Ogre::Vector2(width,height))
	,	mCamera(camera)
	,	mOffset(80.0f)
	,	mManager(manager)
	,	mGoingForward(false)
	,	mGoingBack(false)
	,	mGoingRight(false)
	,	mGoingLeft(false)
	,	mGoingUp(false)
	,	mGoingDown(false)
	,	mVelocity(0,0,0)
	,	mGroundHeight(0)
{
	mCManager = Collision_Manager::getInstance();
}
Player::~Player()
{
}
bool Player::Update(float timesincelastframe)
{
	/**< Call Base Updates */
	Faction::Update(timesincelastframe);
	Player_GUI::Update(timesincelastframe);
	mVelocity = Ogre::Vector3(0,0,0);
	/**< Add to Velocity depending on booleans */
	if(mGoingForward)	{ mVelocity += Ogre::Vector3(mCamera->getDirection().x,0,mCamera->getDirection().z); }
	if(mGoingBack)		{ mVelocity -= Ogre::Vector3(mCamera->getDirection().x,0,mCamera->getDirection().z); }
	if(mGoingLeft)		{ mVelocity -= Ogre::Vector3(mCamera->getRight().x,0,mCamera->getRight().z); }
	if(mGoingRight)		{ mVelocity += Ogre::Vector3(mCamera->getRight().x,0,mCamera->getRight().z); }
	mVelocity = mVelocity.normalisedCopy();
	/**< Get how high off the Gound our base Height should be */
	mGroundHeight = mHeightMap->GetNode((GetPosition().x / 20),(GetPosition().z / 20))->GetHeight(GetPosition());
	/**< Move depending on Velocity */
	mCamera->setPosition((Ogre::Vector3(mCamera->getPosition().x, mGroundHeight + mOffset, mCamera->getPosition().z) + 
		Ogre::Vector3((mVelocity.x * 30) * timesincelastframe,0,(mVelocity.z * 30) * timesincelastframe)));
	return true;
}
void Player::injectKeyDown(const OIS::KeyEvent& evt)
{
	/**< If Delete key has been pressed*/
	if(evt.key == OIS::KC_DELETE)
	{
		/**< Check if anything has been selected */
		if(mSelectedEntities.GetSize() > 0)
		{
			/**< Check if we can remove the Entity */
			Static_Ent* remove = dynamic_cast<Static_Ent*>(mSelectedEntities.At(0));
			if(remove)
			{
				/**<  remove Entity for the List of Buildings that we own */
				for(ListIterator<Base_Ent* > iter(&mBuildings); !iter.IsNuLL();iter++)
				{
					if(iter.Value() == remove)
					{
						iter.Remove();
					}
				}
				/**< Remove from our selected Entitys */
				mSelectedEntities.Pop_Front();
				/**< Mark for deletion */
				remove->Kill();
			}
		}
	}
	/**< Check which Keys are pressed to moe the Player */
	if (evt.key == OIS::KC_UP)		{ mGoingForward = true; }
	if (evt.key == OIS::KC_DOWN)	{ mGoingBack = true; }
	if (evt.key == OIS::KC_LEFT)	{ mGoingLeft = true; }
	if (evt.key == OIS::KC_RIGHT)	{ mGoingRight = true;}
		
	/**< Check if the Player wants to create an Entity */
	if (evt.key == OIS::KC_1)		{ mCreateType = Entity_Name::town_center; }
	if (evt.key == OIS::KC_2)		{ mCreateType = Entity_Name::fireball; }
	if (evt.key == OIS::KC_3)		{ mCreateType = Entity_Name::citizen; }
	if (evt.key == OIS::KC_4)		{ mCreateType = Entity_Name::tree; }
	if (evt.key == OIS::KC_0)		{ mCreateType = Entity_Name::None; }
}
void Player::injectKeyUp(const OIS::KeyEvent& evt)
{
	/**< Check if Player has stoped moving in a Direction */
	if (evt.key == OIS::KC_UP)		{ mGoingForward = false; }
	if (evt.key == OIS::KC_DOWN)	{ mGoingBack = false; }
	if (evt.key == OIS::KC_LEFT)	{ mGoingLeft = false; }
	if (evt.key == OIS::KC_RIGHT)	{ mGoingRight = false; }
}
void Player::injectMouseMove(const OIS::MouseEvent& evt)
{
	/**< Move cursor based on Mouse movments */
	mCursor.Move(Ogre::Vector2(evt.state.X.abs,evt.state.Y.abs));
	Ogre::Vector2 curpos = mCursor.getPosition();
	/**< Check how Far mouse wheel has moved */
	float WheelChange = (evt.state.Z.rel / 80);
	/**< If the wheel has changed in a direction make sure we haven't reached the Max or min distance that the camera can move */
	if(!(mOffset <= 20 && WheelChange > 0) && !(mOffset >= 100 && WheelChange < 0))
	{
		/**< Move Camera but make sure to move the position that the camera is looking at */
		mOffset -= WheelChange;
		mCamera->lookAt(GetPosition().x,mGroundHeight,GetPosition().z + 60);
	}
	
	/**< If the cursor is at an Edge of the Screen move the player in that Direction */
	if(curpos.y <= 0.01)
	{
		mGoingForward = true;
	}
	else if(curpos.y >= 0.98)
	{
		mGoingBack = true;
	}	
	else
	{
		mGoingForward = false;
		mGoingBack = false;
	}
	if(curpos.x <= 0)
	{
		mGoingLeft = true;
	}
	else if(curpos.x >= 0.992)
	{
		mGoingRight = true;
	}
	else
	{
		mGoingLeft = false;
		mGoingRight = false;
	}
}
void Player::injectMouseDown(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
	/**< If the player hasn't clicked a GUI Entity */
	if(!Player_GUI::Click())
	{
		/**< Get cursor position and create a ray from the camera in cursor direction into the world */
		Ogre::Vector2 curpos = mCursor.getPosition();
		Ogre::Ray raydir = mCamera->getCameraToViewportRay(curpos.x,curpos.y);
		Ray ray;
		ray.mDirection = Physics::Vector(raydir.getDirection().x, raydir.getDirection().y, raydir.getDirection().z);
		ray.mStartPosition = Physics::Vector(mCamera->getPosition().x, mCamera->getPosition().y, mCamera->getPosition().z );
		ray.mDistance = 1000;
		Base_Shape* IsHit = 0;
		float dist = mCManager->ShootRay(ray,&IsHit);
		Physics::Vector MovePos = Physics::Vector(ray.mStartPosition + (ray.mDirection * (dist * ray.mDistance)));
		/**< If Player clicked left button */
		if(id == OIS::MB_Left)
		{
			/**< Clear Selected Entities */
			mSelectedEntities.Clear();	
			/**< If Ray hit an Entity */
			if(IsHit)
			{
				/**< Check if the Entity belongs to the Player if it does add too the Selected Entity */
				for(ListIterator<Base_Ent* > iter(&mUnits); !iter.IsNuLL();iter++)
				{
					if(IsHit)
					{
						if(iter.Value()->GetEntityNumber() == IsHit->GetEntityNumber())
						{
							mSelectedEntities.Push_Front(iter.Value());
						}
					}
				}
				for(ListIterator<Base_Ent* > iter(&mBuildings); !iter.IsNuLL();iter++)
				{
					if(IsHit)
					{
						if(iter.Value()->GetEntityNumber() == IsHit->GetEntityNumber())
						{
							mSelectedEntities.Push_Front(iter.Value());
						}
					}
				}
			}
		}
		/**< If Player clicked right button */
		if (id == OIS::MB_Right)
		{
			/**< Check if we create an Entity */
			switch(mCreateType)
			{
			case(Entity_Name::citizen):
				mUnits.Push_Back(mFactory->AddDynamicEntity(mCreateType,MovePos));
				break;
			case(Entity_Name::fireball):
				mUnits.Push_Back(mFactory->AddDynamicEntity(mCreateType,MovePos));
				break;
			case(Entity_Name::town_center):
				mBuildings.Push_Back(mFactory->AddStaticEntity(mCreateType,MovePos));
				break;
			case(Entity_Name::None):
				/**< If we have selected any Entities */
				if(mSelectedEntities.GetSize() > 0)
				{
					/**< Check if we hit anything */
					if(dist < 1.0f)
					{
						/**< Only move the Entities we Selected that are Dynamic Entities */
						/**< Get path to move to position then set path of all dynamic Entities we have selecyed */
						for(ListIterator<Base_Ent* > iter(&mSelectedEntities); !iter.IsNuLL();iter++)
						{
							Dynamic_Ent* Unit = dynamic_cast<Dynamic_Ent* >(iter.Value());
							if(Unit)
							{
								LinkList<Graph_Node* >* Path = new LinkList<Graph_Node* >();
								mFactory->GetPath(Unit->GetPosition(), MovePos, Path, false);
								Unit->SetMove(MovePos,Path);
							}
						}
					}
				}
				break;
			}
			mCreateType = Entity_Name::None;
		}
	}
}
void Player::injectMouseUp(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
	/**< If Player has clicked left button */
	if (id == OIS::MB_Left)
	{	
		/**< Get Highest and lowest Values of were the cursor started clicking and were it finished clicking */
		Ogre::Vector2 Lowest = mCursor.getPosition();
		Ogre::Vector2 Highest = mCursor.getStartPosition();
		if(Highest.x < Lowest.x)
		{
			float temp = Lowest.x;
			Lowest.x = Highest.x;
			Highest.x = temp;
		}	
		if(Highest.y < Lowest.y)
		{
			float temp = Lowest.y;
			Lowest.y = Highest.y;
			Highest.y = temp;
		}
		/**< Select all units that the Player owns that are within the highest and lowest click positions */
		for(ListIterator<Base_Ent* > iter(&mUnits); !iter.IsNuLL();iter++)
		{
			Physics::Vector entpos = iter.Value()->GetPosition();
			Ogre::Vector3 point = mCamera->getProjectionMatrix() * (mCamera->getViewMatrix() * Ogre::Vector3(entpos.x,entpos.y,entpos.z));
			Ogre::Vector2 result = Ogre::Vector2((point.x / 2) + 0.5f,1 - ((point.y / 2) + 0.5f));
			if(result.x > Lowest.x && result.x < Highest.x && result.y > Lowest.y && result.y < Highest.y)
			{
				mSelectedEntities.Push_Front(iter.Value());
			}
		}
	}
	if (id == OIS::MB_Right)
	{
	}
	Player_GUI::Release();
}
Physics::Vector Player::GetPosition()
{
	return Physics::Vector(mCamera->getPosition().x + (mCamera->getDirection().x * 50),mCamera->getPosition().y,mCamera->getPosition().z + (mCamera->getDirection().z * 50));
}