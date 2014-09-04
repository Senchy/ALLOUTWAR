#include "Physics\Shape_Square.h"

Square::Square(Physics::Vector pos, Physics::Vector size,Entity_Name Entity_Type, int entnumber)
	:	Base_Shape(pos, 2,Entity_Type,entnumber), 
		mSize(size)
{
	/**< Get all the points on the square by using the position and size passed */
	mVertices[0] = Physics::Vector((mSize.x/2) + mPosition.x,(mSize.y/2) + mPosition.y,(mSize.z/2) + mPosition.z);		
	mVertices[1] = Physics::Vector((mSize.x/2) + mPosition.x,(mSize.y/2) + mPosition.y,(-mSize.z/2) + mPosition.z);
	mVertices[2] = Physics::Vector((-mSize.x/2) + mPosition.x,(mSize.y/2) + mPosition.y,(mSize.z/2) + mPosition.z);
	mVertices[3] = Physics::Vector((-mSize.x/2) + mPosition.x,(mSize.y/2) + mPosition.y,(-mSize.z/2) + mPosition.z);
	mVertices[4] = Physics::Vector((mSize.x/2) + mPosition.x,(-mSize.y/2) + mPosition.y,(mSize.z/2) + mPosition.z);
	mVertices[5] = Physics::Vector((mSize.x/2) + mPosition.x,(-mSize.y/2) + mPosition.y,(-mSize.z/2) + mPosition.z);
	mVertices[6] = Physics::Vector((-mSize.x/2) + mPosition.x,(-mSize.y/2) + mPosition.y,(mSize.z/2) + mPosition.z);
	mVertices[7] = Physics::Vector((-mSize.x/2) + mPosition.x,(-mSize.y/2) + mPosition.y,(-mSize.z/2) + mPosition.z);
	mBoundingRadius = (mPosition - mVertices[0]).length();																
}
Square::~Square()
{
	Base_Shape::~Base_Shape();
}

Physics::Vector Square::GetSize()
{
	return mSize;
}
Physics::Vector Square::GetVertex(int index)
{
	return mVertices[index];
}
void Square::SetPosition(Physics::Vector Pos)
{
	/**< Translate all points by the same amount we translate the Position */
	Physics::Vector translation = (Pos - mPosition);															
	mFormula->Translate_Body(translation,mVertices,8);																
	mPosition = Pos;																								
}
void Square::Scale(Physics::Vector size)
{
	mSize = size;
	/**< Get all points on the square by using the position and new size passed, then rotate to the current direction */
	mVertices[0] = Physics::Vector((mSize.x/2) + mPosition.x,(mSize.y/2) + mPosition.y,(mSize.z/2) + mPosition.z);
	mVertices[1] = Physics::Vector((mSize.x/2) + mPosition.x,(mSize.y/2) + mPosition.y,(-mSize.z/2) + mPosition.z);
	mVertices[2] = Physics::Vector((-mSize.x/2) + mPosition.x,(mSize.y/2) + mPosition.y,(mSize.z/2) + mPosition.z);
	mVertices[3] = Physics::Vector((-mSize.x/2) + mPosition.x,(mSize.y/2) + mPosition.y,(-mSize.z/2) + mPosition.z);
	mVertices[4] = Physics::Vector((mSize.x/2) + mPosition.x,(-mSize.y/2) + mPosition.y,(mSize.z/2) + mPosition.z);
	mVertices[5] = Physics::Vector((mSize.x/2) + mPosition.x,(-mSize.y/2) + mPosition.y,(-mSize.z/2) + mPosition.z);
	mVertices[6] = Physics::Vector((-mSize.x/2) + mPosition.x,(-mSize.y/2) + mPosition.y,(mSize.z/2) + mPosition.z);
	mVertices[7] = Physics::Vector((-mSize.x/2) + mPosition.x,(-mSize.y/2) + mPosition.y,(-mSize.z/2) + mPosition.z);	
	mBoundingRadius = (mPosition - mVertices[0]).length();																
	Physics::Matrix rot = mFormula->Get_Rotate_To_Direction(Physics::Vector(1,0,0),mDirection);
	if(rot == Physics::Matrix(0))	{ return; }
	mFormula->Translate_Body(-GetPosition(),mVertices, 8);
	mFormula->Rotate_Body(rot,mVertices,8);
	mFormula->Translate_Body(GetPosition(),mVertices,8);	
}
void Square::Translate(Physics::Vector Pos)
{
	mFormula->Translate_Body(Pos,mVertices,8);		
	mPosition += Pos;
}
void Square::Rotate(Physics::Vector axis, float angle,bool IsLocal)
{
	/**< Translate to center for accurate rotation about the center of the Square then rotate all Points then translate back */
	mFormula->Translate_Body(-GetPosition(),mVertices,8);																
	mFormula->Rotate_Body(axis,angle,mVertices,8);										
	mFormula->Translate_Body(GetPosition(),mVertices,8);													
	Base_Shape::Rotate(axis,angle,IsLocal);																			
}
void Square::Rotate(Physics::Matrix matrix)
{
	/**< Translate to center for accurate rotation about the center of the Square then rotate all Points then translate back */
	if(matrix == Physics::Matrix(0))	{ return; }
	mFormula->Translate_Body(-GetPosition(),mVertices, 8);
	mFormula->Rotate_Body(matrix,mVertices,8);
	mFormula->Translate_Body(GetPosition(),mVertices,8);	
	Base_Shape::Rotate(matrix);
}
void Square::RotatetoNormal(Physics::Vector Normal)
{
	/**< Check if we need to rotate */
	if(Normal == mUp)
	{
		return;
	}
	/**< Translate to center for accurate rotation about the center of the Square then rotate all Points */
	/**< by the difference of up and normal Vector then translate back */
	mFormula->Translate_Body(-GetPosition(),mVertices,8);																		
	mFormula->Rotate_Body_To_Direction(mUp,Normal,mVertices,8);															
	mFormula->Translate_Body(GetPosition(),mVertices,8);																	
	Base_Shape::RotatetoNormal(Normal);	
}
void Square::Rotate_To_Direction(Physics::Vector Target_Direction,bool IsLocal)
{
	/**< Check if we need to rotate */
	if(Target_Direction == mDirection)
	{
		return;
	}
	/**< Translate to center for accurate rotation about the center of the Square then rotate all Points */
	/**< by the difference of the Direction and the direction passed then translate back */
	mFormula->Translate_Body(-GetPosition(),mVertices,8);																			
	mFormula->Rotate_Body_To_Direction(mDirection,Target_Direction,mVertices,8);										
	mFormula->Translate_Body(GetPosition(),mVertices,8);															
	Base_Shape::Rotate_To_Direction(Target_Direction,IsLocal);			
}

Physics::Vector Square::Farthest_Point_In_Direction(Physics::Vector Dir)
{
	Physics::Vector Normals[6];
	float ideal_angle = 390;												
	int ideal_plane = 0;
	/**< Get normals for all the planes */
	Normals[0] = mFormula->PLANE_GetNormal(mVertices[1],mVertices[0],mVertices[4]);									
	Normals[1] = mFormula->PLANE_GetNormal(mVertices[0],mVertices[1],mVertices[2]);
	Normals[2] = mFormula->PLANE_GetNormal(mVertices[2],mVertices[6],mVertices[0]);
	Normals[3] = -Normals[0];
	Normals[4] = -Normals[1];
	Normals[5] = -Normals[2];
	/**< Find the plane that is cloest to the direction of the given direction */
	for(int iter = 0; iter < 6; iter++)
	{
		float angle = Dir.anglebetween(Normals[iter]);
		if(angle < ideal_angle)	
		{	
			ideal_angle = angle;	
			ideal_plane = iter;
		}
	}
	/**< If the plane is a possitive then get the point with veryices 0 else use 7 */
	if(ideal_plane < 3)
	{
		return mFormula->PLANE_GetLineIntersection(mVertices[0],Normals[ideal_plane],GetPosition(),Dir);
	}
	else
	{
		return mFormula->PLANE_GetLineIntersection(mVertices[7],Normals[ideal_plane],GetPosition(),Dir);
	}
}
Physics::Vector Square::Farthest_Point(Physics::Vector Dir)
{
	int bestpoint = 0;
	float bestpointdir = (mVertices[0] - GetPosition()).anglebetween(Dir);
	/**< Get the ideal point by getting the direction from center to each point then get */
	/**< the point that has the closest direction to the given direction */
	for(int iter = 1; iter < 8;iter++)
	{
		float pointdir = ((mVertices[iter] - GetPosition()).Normalise_copy()).anglebetween(Dir);
		if(pointdir < bestpointdir)
		{
			bestpointdir =  pointdir;
			bestpoint = iter;
		}
	}	
	return mVertices[bestpoint];
}

void Square::Update(float timesincelastframe)
{
	Base_Shape::Update(timesincelastframe);
	/**< Translate body the the distance we translated the position */
	mFormula->Translate_Body(mLastTranslation,mVertices,8);
	mPosition += mLastTranslation;
}
bool Square::CheckPoint(Physics::Vector point)
{
	float distance = mFormula->PLANE_IsOnDifference(mFormula->PLANE_GetNormal(mVertices[1],mVertices[0],mVertices[4]),mVertices[0],point);	
	/**< Check if the point is behind the plane but not passed the depth of the square */
	/**< Add one to the offset as sometimes the point of collision or testing point is about 0.001 outside the plane */
	if(distance > 0.01 || distance < -(mSize.x + 0.01))
	{
		return false;
	}
	distance = mFormula->PLANE_IsOnDifference(mFormula->PLANE_GetNormal(mVertices[0],mVertices[1],mVertices[2]),mVertices[0],point);			
	/**< Check if the point is behind the plane but not passed the depth of the square */
	if(distance > 0.01 || distance < -(mSize.y + 0.01))
	{
		return false;
	}
	distance = mFormula->PLANE_IsOnDifference(mFormula->PLANE_GetNormal(mVertices[0],mVertices[2],mVertices[6]),mVertices[0],point);	
	/**< Check if the point is behind the plane but not passed the depth of the square */	
	if(distance > 0.01 || distance < -(mSize.z + 0.01))
	{
		return false;
	}
	return true;
}
Physics::Vector Square::FindNormal(Physics::Vector point)
{
	Physics::Vector normal = mFormula->PLANE_GetNormal(GetVertex(1),GetVertex(0),GetVertex(4));
	/**< Get the distance from the point to the forward plane check is the Position closest to this Normal or negitive Normal */	
	float distance = mFormula->PLANE_IsOnDifference(normal,mVertices[0],point);	
	if(distance > -1)
	{
		return normal;
	}
	if(distance < -(mSize.x - 1))
	{
		return -normal;
	}
	normal = mFormula->PLANE_GetNormal(GetVertex(0),GetVertex(1),GetVertex(2));
	distance = mFormula->PLANE_IsOnDifference(normal,mVertices[0],point);
	/**< Get the distance from the point to the Up plane check is the Position closest to this Normal or negitive Normal */	
	if(distance > -1)
	{
		return normal;
	}
	if(distance < -(mSize.y - 1))
	{
		return -normal;
	}
	normal = mFormula->PLANE_GetNormal(GetVertex(0),GetVertex(2),GetVertex(6));
	distance = mFormula->PLANE_IsOnDifference(normal,mVertices[0],point);
	/**< Get the distance from the point to the Side plane check is the Position closest to this Normal or negitive Normal */	
	if(distance > -1)
	{
		return normal;
	}
	if(distance < -(mSize.z - 1))
	{
		return -normal;
	}

}
float Square::CheckRay(Ray ray)
{
	/**< Check if ray is shot in direction of Entity */
	if(mPosition.distance(ray.mStartPosition) > (ray.mDistance + mBoundingRadius) || mFormula->PLANE_IsOnDifference(ray.mDirection,ray.mStartPosition,mPosition) <= 0)
	{
		return 1.0f;
	}
	/**< Check if the Ray comes close to the bounding Radius */
	float DisFromLine = mFormula->LINE_GetDistanceFrom(ray.mStartPosition,ray.mDirection,mPosition);
	if(mBoundingRadius < DisFromLine)
	{
		return 1.0f;
	}
	else
	{
		Physics::Vector Direction_Square_To_Point = (ray.mStartPosition - mPosition).Normalise_copy();
		Physics::Vector Normals[3];
		int normalNumber, currentvertex;
		normalNumber = currentvertex = 0;
		/**< Get normals for all the planes */
		Normals[0] = mFormula->PLANE_GetNormal( GetVertex(1), GetVertex(0), GetVertex(4));
		Normals[1] = mFormula->PLANE_GetNormal( GetVertex(0), GetVertex(1), GetVertex(2));
		Normals[2] = mFormula->PLANE_GetNormal( GetVertex(0), GetVertex(2), GetVertex(6));
		/**< Check if ray hits any Plane on the Square */
		for(int iter = 0; iter < 6; iter++)
		{
			if(iter == 3)
			{
				currentvertex = 7;
				normalNumber = 0;
				Normals[0] *= -1;
				Normals[1] *= -1;
				Normals[2] *= -1;
			}
			if(Normals[normalNumber].dot(Direction_Square_To_Point) >= 0)
			{
				Physics::Vector PointIntersection = mFormula->PLANE_GetLineIntersection(GetVertex(currentvertex),Normals[normalNumber],ray.mStartPosition,ray.mDirection);
				/**< If it hits a Plane check if the point on the plane is inside the square */
				if(CheckPoint(PointIntersection))
				{
					return (PointIntersection.distance(ray.mStartPosition) / ray.mDistance);
				}
			}
			normalNumber++;
		}
		return 1.0f;
	}
}