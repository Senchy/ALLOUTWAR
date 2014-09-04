#include "Entities\Dynamic Entities\Dynamic_Ent.h"

Dynamic_Ent::Dynamic_Ent(int entnumber)
	:	Base_Ent(entnumber)
	,	mIsOnGround(false)
	,	mSpeed(6)
	,	mPath(new LinkList<Graph_Node*>())
{
}
Dynamic_Ent::~Dynamic_Ent()
{
}
void Dynamic_Ent::SetMove(Physics::Vector Pos, LinkList<Graph_Node* > *Path )
{
	mMovePosition = Pos;
	delete mPath;
	mPath = Path;
	mMove = true;
}
Physics::Vector Dynamic_Ent::Update(Physics::Vector Position)
{
	Physics::Vector velocity = Physics::Vector(0,0,0);
	if(mMove == true)
	{
		Physics::Vector Target;
		if((Position - mMovePosition).lengthxz() < 2)
		{
			mMove =  false;
		}
		if (mPath->GetSize() == 0)
		{
			Target = mMovePosition;
		}
		else
		{
			Target = mPath->At(0)->GetPosition();
			float DistanceToNode = (Position - Target).lengthxz();
			if(mPath->At(0)->IsCornerNode() || mPath->At(0)->GetNarrow())
			{
				if(DistanceToNode < 6)
				{
					mPath->Pop_Front();
				}
			}
			else if (!(mPath->At(0)->GetDirection() == Physics::Vector(0)))
			{
				if(DistanceToNode < 15)
				{
					mPath->Pop_Front();
				}
			}
			else
			{
				if(DistanceToNode < 30)
				{
					mPath->Pop_Front();
				}
			}
		}
		velocity = (Target - Position);
		velocity = Physics::Vector(velocity.x,0,velocity.z).Normalise_copy() * mSpeed;
	}
	return velocity;
}