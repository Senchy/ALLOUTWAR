#include "Physics\Collisions_Manager.h"

Collision_Manager* Collision_Manager::mInstance = 0;
///// SAT /////
///////////////
bool Collision_Manager::CheckSQUARE_SQUARE( Square *squareone, Square *squaretwo,Physics::Vector& point_of_collision, Physics::Vector& normal_of_collision)
{
	/**<  Go through every point in both squares and check if a points in one square is inside the other square */
	for(int iter = 0; iter < 8; iter++)
	{
		/**<  check if a point (iter) in square two is inside square one */
		if((squareone->CheckPoint(squaretwo->GetVertex(iter))))
		{
			point_of_collision = squaretwo->GetVertex(iter);
			normal_of_collision = squareone->FindNormal(point_of_collision);
			return true;
		}
		/**<  check if a point (iter) in square one is inside square two */
		if((squaretwo->CheckPoint(squareone->GetVertex(iter))))
		{
			point_of_collision = squareone->GetVertex(iter);
			normal_of_collision = squaretwo->FindNormal(point_of_collision);
			return true;
		}
	}
	/**<  There was no point in ether square */
	return false;
}
bool Collision_Manager::CheckSQUARE_CYLINDER( Square* square, Cylinder* cylinder, Physics::Vector& point_of_collision, Physics::Vector& normal_of_collision)
{
	/**<  Go through every point in the squares and check if a points in the square is inside the cylinder */
	for(int iter = 0; iter < 8; iter++)
	{
		/**<  check if a point (iter) in the square is inside the cylinder */
		if(cylinder->CheckPoint(square->GetVertex(iter)))
		{
			point_of_collision = square->GetVertex(iter);
			normal_of_collision = square->FindNormal(point_of_collision);
			return true;
		}
	}
	/**< The direction and magnitude of the line and get normals of Planes */
	Physics::Vector cylinderdir = (cylinder->GetVertex(0) - cylinder->GetVertex(1));						
	float discheck = cylinderdir.length()/ 2;																	
	Physics::Vector Normals[3];							
	Physics::Vector Mid_Point_On_Closest_Line;
	Physics::Vector collisionpoint;
	Normals[0] = mFormula->PLANE_GetNormal(square->GetVertex(1),square->GetVertex(0),square->GetVertex(4));
	Normals[1] = mFormula->PLANE_GetNormal(square->GetVertex(0),square->GetVertex(1),square->GetVertex(2));
	Normals[2] = mFormula->PLANE_GetNormal(square->GetVertex(0),square->GetVertex(2),square->GetVertex(6));	
	int normalNumber = 0;
	int vertex = 0;
	/**< Check if the cylinder is behind any normals by getting a line on the hull of */
	/**< the cylinder in the opposite direction of the normal */
	/**< If the point is behind the normal check if its inside the square */
	for(int iter = 0; iter < 6; iter++)																			
	{
		/**< Switch to the negitive normals when we have check all the positive ones */
		if(iter == 3)
		{
			vertex = 7;
			normalNumber = 0;
			Normals[0] *= -1;
			Normals[1] *= -1;
			Normals[2] *= -1;
		}
		/**< If the cylinder is parallel to the plane */
		if(cylinderdir.dot(Normals[normalNumber]) == 0)
		{
			/**< use the center of the cylinder as the mid point of the line we are going too check */
			Mid_Point_On_Closest_Line = cylinder->GetPosition();
			/**< Create a line in the opposite direction of the normal */
			/**< (which because they are parallel the new line will be perpendicular to the cylinder line) */
			/**< then get the point were the line hits the plane */
			collisionpoint = mFormula->PLANE_GetLineIntersection(square->GetVertex(vertex),Normals[normalNumber],Mid_Point_On_Closest_Line, -Normals[normalNumber]);
			discheck = cylinder->GetRadius();
			/**< Check if the distance from the midpoint to the collision point is less than the check distance */
			if((collisionpoint - Mid_Point_On_Closest_Line).length() <= discheck)
			{
				/**< If the point is inside the square */
				if(square->CheckPoint(collisionpoint))
				{
					point_of_collision = collisionpoint;
					normal_of_collision = square->FindNormal(collisionpoint);
					return true;
				}
			}
		}
		else
		{
			discheck = cylinderdir.length()/ 2;
			/**< Get the mid point of the edge that is closest to the square */
			/**< Get the point that is closest to the square (using normal of the square side) */
			/**< Create edge using the point and the direction of the cylider */
			/**< Then get the point that is parallel to the center point on the edge */
			Mid_Point_On_Closest_Line = mFormula->LINE_GetPointPerpFromPoint(cylinder->Farthest_Point(-Normals[normalNumber]),cylinderdir.Normalise_copy(),cylinder->GetPosition());
			/**< Find where the edge intersects the plane */
			collisionpoint = mFormula->PLANE_GetLineIntersection(square->GetVertex(vertex),Normals[normalNumber],Mid_Point_On_Closest_Line,cylinderdir.Normalise_copy());
			/**< Check how far the center of the line is from the point were the line intercets with the plane */
			if((collisionpoint - Mid_Point_On_Closest_Line).length() <= discheck)
			{
				/**< Check if the point of intercetion is inside the square */
				if(square->CheckPoint(collisionpoint))
				{
					point_of_collision = collisionpoint;
					normal_of_collision = square->FindNormal(collisionpoint);
					return true;
				}
			}
		}
		normalNumber++;
	}
	return false;
}
bool Collision_Manager::CheckSQUARE_SPHERE( Square* square, Sphere* sphere, Physics::Vector& point_of_collision, Physics::Vector& normal_of_collision)
{
	/**< Go through every point in the squares and check if a points in the square is inside the sphere */
	for(int iter = 0; iter < 8; iter++)
	{
		/**< check if a point (iter) in the square is inside the sphere */
		if(sphere->CheckPoint(square->GetVertex(iter)))
		{
			point_of_collision = square->GetVertex(iter);
			normal_of_collision = square->FindNormal(point_of_collision);
			return true;
		}
	}
	int normalNumber = 0;
	Physics::Vector Direction_Square_to_Sphere = (sphere->GetPosition() - square->GetPosition()).Normalise_copy();
	float BestPointdir, SecondPointdir;
	BestPointdir = SecondPointdir = 500;
	Physics::Vector BestNormal, SecondNormal;
	/**< get the ideal point by getting the direction from center to each point then get the point */ 
	/**< that has the closest direction to the given direction */
	Physics::Vector Normals[3];
	Normals[0] = mFormula->PLANE_GetNormal(square->GetVertex(1),square->GetVertex(0),square->GetVertex(4));
	Normals[1] = mFormula->PLANE_GetNormal(square->GetVertex(0),square->GetVertex(1),square->GetVertex(2));
	Normals[2] = mFormula->PLANE_GetNormal(square->GetVertex(0),square->GetVertex(2),square->GetVertex(6));
	for(int iter = 0; iter < 6;iter++)
	{
		int currentvertex = 0;
		if(iter == 3)
		{
			currentvertex = 7;
			normalNumber = 0;
			Normals[0] *= -1;
			Normals[1] *= -1;
			Normals[2] *= -1;
		}
		float currentDir = ((Normals[normalNumber]).Normalise_copy()).anglebetween(Direction_Square_to_Sphere);
		if(SecondPointdir > currentDir)
		{
			SecondNormal = Normals[normalNumber];
			SecondPointdir = currentDir;
		}
		if(BestPointdir > currentDir)
		{
			SecondNormal = BestNormal;
			SecondPointdir = SecondPointdir;
			BestNormal = Normals[normalNumber]; 
			BestPointdir = currentDir;
		}
		normalNumber++;
	}	
	Physics::Vector CollisionPoint = sphere->Farthest_Point_In_Direction(-BestNormal);
	if(square->CheckPoint(CollisionPoint))
	{
		point_of_collision = CollisionPoint;
		normal_of_collision = square->FindNormal(point_of_collision);
		return true;
	}
	CollisionPoint = sphere->Farthest_Point_In_Direction(-SecondNormal);
	if(square->CheckPoint(CollisionPoint))
	{
		point_of_collision = CollisionPoint;
		normal_of_collision = square->FindNormal(point_of_collision);
		return true;
	}
	Physics::Vector LineDir = BestNormal.cross(SecondNormal);
	Physics::Vector BestPoint = square->GetVertex(0);
	float bestdist = (sphere->GetPosition() - square->GetVertex(0)).length();
	for(int i = 1;i < 8; i++)
	{
		float currdist = (sphere->GetPosition() - square->GetVertex(i)).length();
		if(currdist < bestdist)
		{
			bestdist = currdist;
			BestPoint = square->GetVertex(i);
		}
	}
	Physics::Vector pointonline;
	pointonline = mFormula->LINE_GetPointPerpFromPoint(BestPoint,LineDir,sphere->GetPosition());
	CollisionPoint = sphere->Farthest_Point_In_Direction((pointonline - sphere->GetPosition()).Normalise_copy());
	if(square->CheckPoint(CollisionPoint))
	{
		point_of_collision = CollisionPoint;
		normal_of_collision = square->FindNormal(point_of_collision);
		return true;
	}
	return false;
}
bool Collision_Manager::CheckSPHERE_CYLINDER( Sphere* sphere, Cylinder* cylinder, Physics::Vector& point_of_collision, Physics::Vector& normal_of_collision)
{
	/**< Get direction and magnitude of the center of the cylinder to the top */
	/**< Get direction perpendicular to both direction and the cylinder */
	Physics::Vector Dir = (sphere->GetPosition() - cylinder->GetPosition()).Normalise_copy();
	Physics::Vector Normal = (cylinder->GetPosition() - cylinder->GetVertex(1)).Normalise_copy();														
	Physics::Vector cross = Normal.cross(Dir);																						
	Physics::Vector perp = cross.cross(Normal);		
	perp.Normalise();
	if(perp == Physics::Vector(0))
	{
		if((sphere->GetPosition() - cylinder->GetPosition()).length() < (cylinder->GetPosition() - cylinder->GetVertex(1)).length() + sphere->GetBoundingRadius())
		{
			point_of_collision = sphere->Farthest_Point_In_Direction(-Dir);
			normal_of_collision = -Dir;
			return true;
		}
	}
	else
	{
		Physics::Vector cornerpoint = cylinder->Farthest_Point(Dir);
		Physics::Vector sidepoint = sphere->Farthest_Point_In_Direction(-perp);
		Physics::Vector toppoint;
		if(Dir.dot(Normal) > Dir.dot(-Normal))
		{
			toppoint = sphere->Farthest_Point_In_Direction(-Normal);
			Normal = Normal;
		}
		else
		{
			toppoint = sphere->Farthest_Point_In_Direction(Normal);
			Normal = -Normal;
		}
		if(cylinder->CheckPoint(sidepoint))
		{
			point_of_collision = sidepoint;
			normal_of_collision = -perp;
			return true;
		}
		if(cylinder->CheckPoint(toppoint))
		{
			point_of_collision = toppoint;
			normal_of_collision = Normal;
			return true;
		}
		if(sphere->CheckPoint(cornerpoint))
		{
			point_of_collision = cornerpoint;
			normal_of_collision = (sphere->GetPosition() - cornerpoint).Normalise_copy();
			return true;
		}
	}
	return false;
}
bool Collision_Manager::CheckCYLINDER_CYLINDER( Cylinder* cylinderone, Cylinder* cylindertwo, Physics::Vector& point_of_collision, Physics::Vector& normal_of_collision)
{
	/**< Get the direction and magnatude of cylinder One */
	Physics::Vector Onedir = (cylinderone->GetVertex(0) - cylinderone->GetVertex(1));
	/**< Get the direction and magnatude of cylinder Two */
	Physics::Vector twodir = (cylindertwo->GetVertex(0) - cylindertwo->GetVertex(1));
	/**< Get the a direction that is perpedicular to both cylinders */
	Physics::Vector PerpDir = Onedir.cross(twodir).Normalise_copy();
	/**< If the cylinders are parallel */
	if(PerpDir == Physics::Vector(0))
	{
		/**< Get the centerpoint for cylinder two and project it onto the center line of cylinder one */
		Physics::Vector twopos = mFormula->LINE_GetPointPerpFromPoint(cylinderone->GetPosition(),Onedir.Normalise_copy(),cylindertwo->GetPosition());
		/**< check how far the center point is from the projected point */
		/*<* If its larger that the length of the two cylinders added then it is too far away to be colliding */
		if((twopos - cylinderone->GetPosition()).length() < (Onedir.length() + twodir.length()) / 2)
		{
			/**< Check how far the centerpoint of the cylinder two is from the line in center*/
			/**< If its larger that the radius of the two cylinders added then it is too far away to be colliding */
			if(mFormula->LINE_GetDistanceFrom(cylinderone->GetPosition(),Onedir,cylindertwo->GetPosition()) <= cylinderone->GetRadius() + cylindertwo->GetRadius())
			{
				point_of_collision = mFormula->LINE_GetPoint(cylinderone->GetPosition(), Onedir,cylinderone->GetBoundingRadius());
				normal_of_collision = -((twopos - cylindertwo->GetPosition()).Normalise_copy());
				return true;
			}
		}
	}
	else
	{
		/**< Get the midpoint egde on cylinder one that is closest to cylinder two using perpdir*/
		Physics::Vector linepoint = mFormula->LINE_GetPointPerpFromPoint(cylinderone->Farthest_Point(PerpDir),Onedir.Normalise_copy(),cylinderone->GetPosition());
		/**< Get the midpoint on egde on cylinder two that is closest to cylinder one using negitive perpdir*/
		Physics::Vector linetwopoint = mFormula->LINE_GetPointPerpFromPoint(cylindertwo->Farthest_Point(-PerpDir),twodir.Normalise_copy(),cylindertwo->GetPosition());
		/**< Get the point that intersects a plane created by the top point on cylinder two and the direction of cylinder two */
		/**< (this creates a plane on top of the cylinder two pointing up to check if the cylinder one is hiting the top of the cylinder two) */
		/**< and a line created by the edge midpoint on cylinder one and the direction of cylinder one */
		Physics::Vector pointonplane = mFormula->PLANE_GetLineIntersection(cylindertwo->GetVertex(0),twodir.Normalise_copy(),linepoint,Onedir.Normalise_copy());
		/**< Check if the point is close enought to the midpoint on the edge to be inside the cylinder one */
		if((pointonplane - linepoint).length() <= (Onedir.length() / 2))
		{
			/**< Check if the point is close enuogh to the center of the plane to check if its hitting the top */
			if((cylindertwo->GetVertex(0) - pointonplane).length() <= cylindertwo->GetRadius())
			{
				point_of_collision = pointonplane;
				normal_of_collision = twodir;
				return true;
			}
		}
		/**< Get the point that intersects a plane created by the bottom point on cylinder two and the negitive direction of cylinder two */
		/**< (this creates a plane on the bottom of the cylinder two pointing up to check if the cylinder two is hiting the bottom of the cylinder two) */
		/**< and a line created by the edge midpoint on cylinder one and the direction of cylinder one */
		pointonplane = mFormula->PLANE_GetLineIntersection(cylindertwo->GetVertex(1),-twodir.Normalise_copy(),linepoint,Onedir.Normalise_copy());
		/**< Check if the point is close enought to the midpoint on the edge to be inside the cylinder one */
		if((pointonplane - linepoint).length() <= (Onedir.length() / 2))
		{
			/**< Check if the point is close enuogh to the center of the plane to check if its hitting the bottom */
			if((cylindertwo->GetVertex(1) - pointonplane).length() <= cylindertwo->GetRadius())
			{
				point_of_collision = pointonplane;
				normal_of_collision = -twodir;
				return true;
			}
		}
		/**< Get the point that intersects a plane created by the edge midpoint on cylinder two and the negitive perpidiclar direction */
		/**< (This creates a plane that is on the edge of cylinder two that points in the direction of cylinder one) */
		/**< and a line created by the edge midpoint on cylinder one and the direction of cylinder one */
		pointonplane = mFormula->PLANE_GetLineIntersection(linetwopoint, -PerpDir,linepoint,Onedir.Normalise_copy());
		/**< Check if the point is close enought to the midpoint on the edge to be inside the cylinder one */
		if((pointonplane - linepoint).length() <= (Onedir.length() / 2))
		{
			/**< Check if the point is close enought to the midpoint on the edge to be inside the cylinder two */
			if((pointonplane - linetwopoint).length() <= (twodir.length() / 2))
			{
				point_of_collision = pointonplane;
				normal_of_collision = PerpDir;
				return true;
			}
		}
	}
	return false;
}

///// GJK /////
///////////////
Physics::Vector Collision_Manager::Support(Physics::Vector Direction, Base_Shape* ShapeOne, Base_Shape* ShapeTwo)
{
	/**< Get the a point on shape one that is on the hull in a given direction */
	Physics::Vector PointOne = ShapeOne->Farthest_Point_In_Direction(Direction);
	/**< Get the a point on shape two that is on the hull in a negitive given direction */
	Physics::Vector PointTwo = ShapeTwo->Farthest_Point_In_Direction(-Direction);
	/**< Take the first point away from the second point this gives us the Minkowski Difference of the two Shapes */
	/**< The Minkowski Difference is a new shape that is bot shapes combined and we need the point in a certain direction on the Minkowski Difference  */
	return (PointOne - PointTwo);
}
bool Collision_Manager::DoSimplex(std::vector<Physics::Vector> &list, Physics::Vector &Direction)
{
	/**< Switch based on how many elements are in the list */
	switch(list.size())
	{
	case 2:
		/**< Call line simplex if there are two points */
		return SimplexLine(list,Direction);
		break;
	case 3:
		/**< Call triangle simplex if there are two points */
		return SimplexTriangle(list,Direction);
		break;
	case 4:
		/**< Call quadrilateral simplex if there are two points */
		return SimplexQuadrilateral(list,Direction);
		break;
	}
	return false;
}
bool Collision_Manager::SimplexLine(std::vector<Physics::Vector> &list, Physics::Vector &Direction)
{
	/**< Get Direction perpendicualr to the line and from first point to vector 0  */
	Physics::Vector a,b,o, ab;				
	a = list[1];																						
	b = list[0];
	o = Physics::Vector(0) - a;																			
	ab = b-a;																							
	Direction = ((b-a).cross(o)).cross(b-a).Normalise_copy();											
	return false;
}
bool Collision_Manager::SimplexTriangle(std::vector<Physics::Vector> &list, Physics::Vector &Direction)
{
	Physics::Vector a,b,c,ab,ac,o, abc, abperp, acperp;
	a = list[2];																							
	b = list[1];
	c = list[0];
	ab = b-a;																								
	ac = c-a;																								
	o = Physics::Vector(0) - a;																				
	abc = mFormula->PLANE_GetNormal(a,b,c);																
	abperp = (ab * (ac.dot(ab))) - (ac * (ab.dot(ab)));														
	acperp = (ac * (ab.dot(ac))) - (ab * (ac.dot(ac)));														
	/* Is point(0,0,0) infront of the line ab */
	if(abperp.dot(o) > 0)
	{
		/**< Set the direction perpedicular from the line ab to the direction towards point(0,0,0) */
		Direction = (((ab).cross(o)).cross(ab)).Normalise_copy();
	}
	else
	{
		/**< Is point(0,0,0) infront of line ac */
		if(acperp.dot(o) > 0)
		{
			/**< Set the direction perpedicular from the line ac to the direction towards point(0,0,0) */
			Direction = (((ac).cross(o)).cross(ac)).Normalise_copy();
		}
		else
		{
			/**< Is the point ontop of the triangle or below */
			if(abc.dot(o) > 0)
			{
				/**< Set the direction to the normal of the triangle */
				Direction = abc.Normalise_copy();
			}
			else
			{
				/**< Set the direction to the normal of the triangle */
				Direction = -abc.Normalise_copy();
			}
		}
	}
	return false;
}
bool Collision_Manager::SimplexQuadrilateral(std::vector<Physics::Vector> &list, Physics::Vector &Direction)
{
	Physics::Vector a = list[3];																		
	Physics::Vector b = list[2];
	Physics::Vector c = list[1];
	Physics::Vector d = list[0];
	Physics::Vector abcplane = mFormula->PLANE_GetNormal(b,a,c);										
	Physics::Vector acdplane = mFormula->PLANE_GetNormal(a,d,c);						
	Physics::Vector abdplane = mFormula->PLANE_GetNormal(a,b,d);								
	Physics::Vector cdbplane = mFormula->PLANE_GetNormal(d,b,c);						
	float abc = mFormula->PLANE_IsOnDifference(abcplane,a,Physics::Vector(0,0,0));			
	float acd = mFormula->PLANE_IsOnDifference(acdplane,a,Physics::Vector(0,0,0));		
	float abd = mFormula->PLANE_IsOnDifference(abdplane,a,Physics::Vector(0,0,0));		
	float dbc = mFormula->PLANE_IsOnDifference(cdbplane,c,Physics::Vector(0,0,0));		
	/**< Check if the point (0,0,0) is behind all the planes so check if the quadrilateral encapsulates the point */
	/**< If it doesnt get pop the first element added to the vector and the call the triangle simplex to create the quadrilateral again for the next pass */
	if(abc <= 0 && acd <= 0 && abd <= 0 && dbc <= 0)
	{
		return true; 
	}
	else
	{
		list.erase(list.begin());
		SimplexTriangle(list,Direction);
		return false;
	}
}

///// Initialisation /////
//////////////////////////
Collision_Manager::Collision_Manager()
{
	mFormula = Physics_Formulas::getInstance();
}
Collision_Manager::~Collision_Manager()
{
}
Collision_Manager* Collision_Manager::getInstance()
{
	/**< Check if we have an instance of this class yet if we dont create an instance */
	if(mInstance == 0)
	{
		mInstance = new Collision_Manager();
	}
	/**< Return the instance of this class */
	return mInstance;
}

///// Check Colliding Functions /////
/////////////////////////////////////
bool Collision_Manager::Check_BoundingRadius(Base_Shape* ShapeOne, Base_Shape* ShapeTwo)
{
	/**< Distance from one shape to the other and distance we need for them to be colliding */
	float distance = ShapeOne->GetPosition().distance(ShapeTwo->GetPosition());							
	float needed_Distance = ShapeOne->GetBoundingRadius() + ShapeTwo->GetBoundingRadius();				
	/**< If Distance is less than the distance we need to collide return true */
	if(needed_Distance > distance)
	{
		return true;
	}
	return false;
}
bool Collision_Manager::Check_SAT(Base_Shape* ShapeOne, Base_Shape* ShapeTwo, Physics::Vector& point_of_collision, Physics::Vector& normal_of_collision)
{
	/**< Select a cast to the right shape, The shapes are give a number when created so we know what */ 
	/**< type of shape they are for effectiant casting */
	bool returner;
	switch(ShapeOne->GetType())
	{
	case 0:
			switch(ShapeTwo->GetType())
			{
			case 0:
				point_of_collision = mFormula->LINE_GetPoint(ShapeOne->GetPosition(), (ShapeTwo->GetPosition() - ShapeOne->GetPosition()).Normalise_copy(),ShapeOne->GetBoundingRadius());
				normal_of_collision = (ShapeTwo->GetPosition() - ShapeOne->GetPosition()).Normalise_copy();
				return true;
				break;
			case 1:
				returner = CheckSPHERE_CYLINDER(dynamic_cast<Sphere*>(ShapeOne),dynamic_cast<Cylinder*>(ShapeTwo),point_of_collision,normal_of_collision);
				return returner;
				break;
			case 2:
				returner = CheckSQUARE_SPHERE(dynamic_cast<Square*>(ShapeTwo),dynamic_cast<Sphere*>(ShapeOne),point_of_collision,normal_of_collision);
				normal_of_collision *= -1;
				return returner;
				break;
			}
		break;
	case 1:
			switch(ShapeTwo->GetType())
			{
			case 0:
				returner = CheckSPHERE_CYLINDER(dynamic_cast<Sphere*>(ShapeTwo),dynamic_cast<Cylinder*>(ShapeOne),point_of_collision,normal_of_collision);
				normal_of_collision *= -1;
				return returner;
				break;
			case 1:
				returner = CheckCYLINDER_CYLINDER(dynamic_cast<Cylinder*>(ShapeOne),dynamic_cast<Cylinder*>(ShapeTwo),point_of_collision,normal_of_collision);
				return returner;
				break;
			case 2:
				returner = CheckSQUARE_CYLINDER(dynamic_cast<Square*>(ShapeTwo),dynamic_cast<Cylinder*>(ShapeOne),point_of_collision,normal_of_collision);
				normal_of_collision *= -1;
				return returner;
				break;
			}
		break;
	case 2:
			switch(ShapeTwo->GetType())
			{
			case 0:
				returner = CheckSQUARE_SPHERE(dynamic_cast<Square*>(ShapeOne),dynamic_cast<Sphere*>(ShapeTwo),point_of_collision,normal_of_collision);
				return returner;
				break;
			case 1:
				returner = CheckSQUARE_CYLINDER(dynamic_cast<Square*>(ShapeOne),dynamic_cast<Cylinder*>(ShapeTwo),point_of_collision,normal_of_collision);
				return returner;
				break;
			case 2:
				returner = CheckSQUARE_SQUARE(dynamic_cast<Square*>(ShapeOne),dynamic_cast<Square*>(ShapeTwo),point_of_collision,normal_of_collision);
				return returner;
				break;
			}
		break;
	}
}
bool Collision_Manager::Check_GFK(Base_Shape* ShapeOne, Base_Shape* ShapeTwo)
{
	/**< Set our direction in the same direction of the two shape in relation to each other */
	/**< Add our first point to the simplex list using a set direction on the Minkowski Difference of the two shapes */
	/**< then set direction in the opposite direction of our original search direction */
	std::vector<Physics::Vector> Simplex;																
	Physics::Vector Dir = (ShapeTwo->GetPosition() - ShapeOne->GetPosition()).Normalise_copy();		
	Simplex.push_back(Support(Dir,ShapeOne,ShapeTwo));												
	Dir = -Dir;																							
	/**< Keep looping until we ecapsulate the point in a quadrilateral or we find out the point is unreachable */
	while(true)
	{
		/**< Add our new point too the simplex in a set direction the point is on the Minkowski Difference of the two shapes */
		Simplex.push_back(Support(Dir,ShapeOne,ShapeTwo));
		/**< Check if the point (0,0,0) is unreachable */
		if(Simplex[Simplex.size() - 1].dot(Dir) <= 0)
		{
			return false;
		}
		/**< Check is the point(0,0,0) encapsulated if it isnt then continue the loop */
		/**< and get new direction (if nessisary remove the first point) */
		if(DoSimplex(Simplex,Dir))
		{
			return true;
		}
	}
}
void Collision_Manager::INIT(LinkList<Base_Shape* >* dynamiclist,LinkList<Base_Shape* >* staticlist,Height_Map *Map)
{
	mDynamicList = dynamiclist;
	mStaticList = staticlist;
	mMap = Map;
}
float Collision_Manager::ShootRay(Ray ray,Base_Shape** Shape)
{
	/**< Go Through Dynamic List and Check what is the closest Entity we hit if we hit an */
	/**< Entity set the Shape pointer to that Entity and the ray distance to the distance to the Entity*/ 
	float Closestshape = 1.0f;
	for(ListIterator<Base_Shape* > iter(mDynamicList); !iter.IsNuLL(); iter++)
	{
		float Currentshape = iter.Value()->CheckRay(ray);
		if(Closestshape > Currentshape)
		{
			Closestshape = Currentshape;
			*Shape = iter.Value();
		}
	}
	/**< Go Through Dynamic List and Check what is the closest Entity we hit if we hit an */
	/**< Entity set the Shape pointer to that Entity and the ray distance to the distance to the Entity*/ 
	for(ListIterator<Base_Shape* > iter(mStaticList); !iter.IsNuLL(); iter++)
	{
		float Currentshape = iter.Value()->CheckRay(ray);
		if(Closestshape > Currentshape)
		{
			Closestshape = Currentshape;
			*Shape = iter.Value();
		}
	}
	/**< Check Hieght map Ray cast and If the Height map Distance is Closer than  */
	/**< the Entity distance then set the Entity pointer to null and return the Height Map distance */
	float ClosestGround = mMap->CheckRay(ray);
	if(Closestshape < ClosestGround)
	{
		return Closestshape;
	}
	else
	{
		*Shape = 0;
		return ClosestGround;
	}
}
void Collision_Manager::FindCollisions(LinkList<Base_Shape* >* CollisionList)
{
	/**< Go through each Object and check if it colliding with another Object */
	for(ListIterator<Base_Shape* > checkiter(CollisionList); !checkiter.IsNuLL();checkiter++)
	{
		ListIterator<Base_Shape* > collisioniter(CollisionList);
		collisioniter = checkiter;
		collisioniter++;
		/**< Start from the element in the list that we are updating as we have already checked elements already */
		for(;!collisioniter.IsNuLL();collisioniter++)
		{
			if(Check_BoundingRadius((checkiter.Value()),collisioniter.Value()))
			{
				Physics::Vector collisionpoint;
				Physics::Vector collisionnormal;
				if(Check_SAT(checkiter.Value(),collisioniter.Value(),collisionpoint, collisionnormal))
				{
					checkiter.Value()->SetCollisionDetails(collisioniter.Value(), collisionpoint, -collisionnormal);
					collisioniter.Value()->SetCollisionDetails(checkiter.Value(), collisionpoint, collisionnormal);
				}
			}
		}
	}
}
void Collision_Manager::FindCollisions(LinkList<Base_Shape* >* FirstList, LinkList<Base_Shape* >* SecondList)
{
	/**< Go through each Object and check if it colliding with another Object */
	for(ListIterator<Base_Shape* > checkiter(FirstList); !checkiter.IsNuLL();checkiter++)
	{	
		for(ListIterator<Base_Shape* > collisioniter(SecondList); !collisioniter.IsNuLL();collisioniter++)
		{
			if(Check_BoundingRadius((checkiter.Value()),collisioniter.Value()))
			{
				Physics::Vector collisionpoint;
				Physics::Vector collisionnormal;
				if(Check_SAT(checkiter.Value(),collisioniter.Value(),collisionpoint, collisionnormal))
				{
					checkiter.Value()->SetCollisionDetails(collisioniter.Value(), collisionpoint, -collisionnormal);
					collisioniter.Value()->SetCollisionDetails(checkiter.Value(), collisionpoint, collisionnormal);
				}
			}
		}
	}
}
bool Collision_Manager::Check_If_Colliding(LinkList<Base_Shape* >* CollisionList, Base_Shape* Shape)
{
	/**< Go through each Object and check if it colliding with the Entity Passed */
	for(ListIterator<Base_Shape* > checkiter(CollisionList); !checkiter.IsNuLL();checkiter++)
	{
		if(Check_BoundingRadius((checkiter.Value()), Shape))
		{
			Physics::Vector point, normal;
			if(Check_SAT(checkiter.Value(), Shape, point, normal))
			{
				return true;
			}
		}
	}
	return false;
}
bool Collision_Manager::Check_Proximity(Physics::Vector pos, float radius)
{
	/**< Go through each Entity in the Dynamic List and check if the XZ distance to the possition passed within the distance passed */
	for(ListIterator<Base_Shape* > iter(mDynamicList); !iter.IsNuLL(); iter++)
	{
		if((iter.Value()->GetPosition() - pos).lengthxz() < (radius + iter.Value()->GetBoundingRadius()))
		{
			return true;
		}
	}
	/**< Go through each Entity in the static List and check if the XZ distance to the possition passed within the distance passed */
	for(ListIterator<Base_Shape* > iter(mStaticList); !iter.IsNuLL(); iter++)
	{
		if((iter.Value()->GetPosition()- pos).lengthxz() < (radius + iter.Value()->GetBoundingRadius()))
		{
			return true;
		}
	}
	return false;
}