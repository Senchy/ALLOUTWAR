#include "Physics\Physics_Formulas.h"

/**< Initialise the pointer too this object */
Physics_Formulas* Physics_Formulas::mPhysicsInstance = 0;											
Physics_Formulas::Physics_Formulas()
	: mGravity(0, -9.81, 0)
{
}
Physics_Formulas* Physics_Formulas::getInstance()
{
	/**< Check if we have an instance of this class yet if we dont create an instance */
	if(mPhysicsInstance == 0)
	{
		mPhysicsInstance = new Physics_Formulas();
	}
	/**< Return the instance of this class */
	return mPhysicsInstance;
}
Physics_Formulas::~Physics_Formulas()
{
}
Physics::Vector Physics_Formulas::GetGravity(bool isonground)
{
	/**< If its on the ground dont apply Gravity */
	if(isonground)
	{
		return mGravity;
	}
	else
	{
		return Physics::Vector(0,0,0);
	}
}
void Physics_Formulas::SetGravity(float gravity)
{
	mGravity = Physics::Vector(0,gravity,0);
}
Physics::Vector Physics_Formulas::New_Position(Physics::Vector Position, Physics::Vector Velocity, Physics::Vector Acceleration, float time)
{
	/**< Euclidean distance formula to get the new position (d = p + ut + 1/2att) */
	Physics::Vector postranslation = Position;														
	Position = Position + Velocity * time +  (Acceleration * 0.5) * (time * time);					
	return (Position - postranslation);																
}
Physics::Vector Physics_Formulas::New_Velocity(Physics::Vector Velocity, Physics::Vector Acceleration, float time)
{
	/**< Euclidean velocity formula to get the new velocity (v = ut + 1/2att) */
	Physics::Vector VecTranslation = Velocity;														
	Velocity = Velocity + Acceleration * time;														
	return (Velocity - VecTranslation);														
}

void Physics_Formulas::Translate_Body(Physics::Vector Translation, Physics::Vector Vertices[], int number_of_Vertices)
{
	/**< Go through each vertex and translate each one by a set amount */
	for(int iter = 0;iter < number_of_Vertices;iter++)
	{
		Vertices[iter] = Vertices[iter] + Translation;
	}
}
Physics::Matrix Physics_Formulas::Get_Rotate_To_Direction(Physics::Vector CurrectDirection, Physics::Vector NewDirection)
{
	/**< Check if the direction are the same direction */
	if(CurrectDirection == NewDirection)
	{
		return Physics::Matrix(0);
	}
	/**< Get direction prependicular to both current direction and the direction we want */
	Physics::Vector Cross = NewDirection.cross(CurrectDirection).Normalise_copy();
	float angle = NewDirection.anglebetween(CurrectDirection);
	float x,y,z,w;
	/**< Create quaternion matrix */
	x = Cross.x * std::sin(angle/2);
	y = Cross.y * std::sin(angle/2);
	z = Cross.z * std::sin(angle/2);
	w = std::cos(angle/2);
	Physics::Matrix Returner(Cross.x * std::sin(angle/2), Cross.y * std::sin(angle/2),Cross.z * std::sin(angle/2),std::cos(angle/2));
	return Returner;
}
void Physics_Formulas::Rotate_Body_To_Direction(Physics::Vector Currentdirection, Physics::Vector TargetDirection, Physics::Vector Vertices[], int number_of_Vertices)
{
	/**< Check if the direction are the same direction */
	if(Currentdirection == TargetDirection)
	{
		return;
	}
	/**< Create Rotation Matrix */
	Physics::Matrix Rotation_Matrix = Get_Rotate_To_Direction(Currentdirection,TargetDirection);
	/**< Rotate all points by the Rotation matrix */
	for(int iter = 0; iter < number_of_Vertices; iter++)
	{
		Vertices[iter] = Vertices[iter] * Rotation_Matrix;
	}
}
void Physics_Formulas::Rotate_Body(Physics::Vector axis, float angle, Physics::Vector Vertices[], int number_of_Vertices)
{
	/**< Make sure the angle isnt 0 */
	if(angle == 0)
	{
		return;
	}
	Physics::Matrix rotationmatrix = Physics::Matrix();
	angle *= (3.141/180);
	rotationmatrix.AXIS_MATRIX(axis.x,axis.y,axis.z,angle);
	/**< Go through each vertex and rotate Matrix */
	for(int iter = 0; iter < number_of_Vertices; iter++)
	{
		Vertices[iter] = Vertices[iter] * rotationmatrix;
	}
}
void Physics_Formulas::Rotate_Body(Physics::Matrix rotationmatrix, Physics::Vector Vertices[], int number_of_Vertices)
{
	/**< Go through each vertex and rotate Matrix */
	for(int iter = 0; iter < number_of_Vertices;iter++)
	{
		Vertices[iter] = Vertices[iter] * rotationmatrix;
	}
}

Physics::Vector Physics_Formulas::PLANE_GetNormal(Physics::Vector Point1,Physics::Vector Point2,Physics::Vector Point3)
{
	/**< Get the perpendicular vector for two lines on the plane then return */
	Physics::Vector p1p2 = Point2 - Point1; 															
	Physics::Vector p1p3 = Point3 - Point1; 															
	p1p2 = p1p2.cross(p1p3); 																			
	p1p2.Normalise();																					
	return p1p2;
}
bool Physics_Formulas::PLANE_ISOn(Physics::Vector normal, Physics::Vector plane_point, Physics::Vector point)
{
	/**< Get the distance of the point from the plane if the distance is 0 return true */
	if (PLANE_IsOnDifference(normal,plane_point,point) == 0)
	{
		return true;
	}
	return false;
}
float Physics_Formulas::PLANE_IsOnDifference(Physics::Vector normal, Physics::Vector plane_point, Physics::Vector point)
{
	/**< Insert the values into the equation that gets the distance of a point to a plane */
	return((normal.x*(point.x - plane_point.x)) + (normal.y*(point.y - plane_point.y)) + (normal.z*(point.z - plane_point.z)));
}
Physics::Vector Physics_Formulas::PLANE_GetSlope(Physics::Vector normal)
{
	/**< Get the difference from up vector */
	Physics::Vector point = (Physics::Vector(0,1,0) - normal).Normalise_copy();
	return point;
}
float Physics_Formulas::PLANE_GetHeight(Physics::Vector normal,Physics::Vector plane_point, Physics::Vector point)
{
	return(plane_point.y +((-(normal.x * (point.x - plane_point.x)) -(normal.z * (point.z - plane_point.z))) / normal.y));
}
Physics::Vector Physics_Formulas::PLANE_GetLineIntersection(Physics::Vector planepoint, Physics::Vector planeNormal, Physics::Vector linepoint, Physics::Vector lineDir)
{
	/**< Formula for line plane intersection */
	float Xpart = (planeNormal.x * linepoint.x) - (planeNormal.x * planepoint.x);										
	float Ypart = (planeNormal.y * linepoint.y) - (planeNormal.y * planepoint.y);										
	float Zpart = (planeNormal.z * linepoint.z) - (planeNormal.z * planepoint.z);										
	float NegNormalDotPrad = -(planeNormal.x * lineDir.x) -(planeNormal.y * lineDir.y) -(planeNormal.z * lineDir.z);	
	float distancefrompoint = (Xpart + Ypart + Zpart) / NegNormalDotPrad;												
	return LINE_GetPoint(linepoint, lineDir, distancefrompoint);
}
Physics::Vector Physics_Formulas::LINE_GetPoint(Physics::Vector Point,Physics::Vector Dir, float t)
{
	/**< Formula for line P + D * s */
	Physics::Vector newdir = Dir*t;																					
	newdir.Clip();																									
	return (Point + newdir);																						
}
float Physics_Formulas::LINE_GetDistanceFrom(Physics::Vector linepoint, Physics::Vector lineDir, Physics::Vector Point)
{
	/**< Formula for distance to line d^2= ((x1-x0)+(x2-x1)t)^2+((y1-y0)+(y2-y1)t)^2+((z1-z0)+(z2-z1)t)^2 */
	Physics::Vector FirstPartofCross = (Point - linepoint);																
	Physics::Vector SecondPartofCross = (Point - (linepoint + (lineDir * 10)));											
	Physics::Vector Cross = FirstPartofCross.cross(SecondPartofCross);													
	float top = Cross.length();																							
	float bottom = (linepoint - (linepoint + (lineDir * 10))).length();				
	return (top / bottom);
}
Physics::Vector Physics_Formulas::LINE_GetPointByDistance(Physics::Vector linepoint, Physics::Vector lineDir, Physics::Vector DirFromLine, float dist)
{
	float angelfromline = lineDir.anglebetween(DirFromLine);															
	float t = dist / std::sin(angelfromline);																			
	return LINE_GetPoint(linepoint, DirFromLine, t);																	
}
Physics::Vector Physics_Formulas::LINE_GetPointPerpFromPoint(Physics::Vector linepoint, Physics::Vector lineDir, Physics::Vector DirFromLine, float dist)
{
	float t = LINE_GetDistancePerpFromPoint_OnLine(linepoint, lineDir, DirFromLine, dist);					
	return LINE_GetPoint(linepoint, lineDir, t);																	
}
float Physics_Formulas::LINE_GetDistancePerpFromPoint_OnLine(Physics::Vector linepoint, Physics::Vector lineDir, Physics::Vector DirFromLine, float dist)
{
	float angelfromline = lineDir.anglebetween(DirFromLine);															
	return (dist / std::tan(angelfromline));																			
}
Physics::Vector Physics_Formulas::LINE_GetPointPerpFromPoint(Physics::Vector linepoint, Physics::Vector lineDir, Physics::Vector point)
{
	Physics::Vector line = point - linepoint;																			
	Physics::Vector dir = line.Normalise_copy();																		
	float angle = lineDir.anglebetween(dir);																		
	/**< If angle is 0 */
	if(angle == 0)
	{
		return point;
	}
	/**< Get the distance along the line that is parallel to the point */
	float length = cos(angle) * line.length();
	/**< Find point along line using the distance */
	return LINE_GetPoint(linepoint,lineDir,length);
}