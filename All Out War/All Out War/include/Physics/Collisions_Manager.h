#ifndef COLLISIONS_MANAGER_H
#define COLLISIONS_MANAGER_H

#include "Physics\Shape_Cylinder.h"
#include "Physics\Shape_Sphere.h"
#include "Physics\Shape_Square.h"
#include "Physics\Height_Map.h"
#include "LinkList.h"
#include "ContainerStructs.h"
#include <vector>

class Collision_Manager
{
private:
	/// <value>Pointer to a Collision Manager instance that is the only instance of this class</value>
	static Collision_Manager*		mInstance;
	/// <value>Pointer to list of Dynamic Entitys (Entities that Move)</value>
	LinkList<Base_Shape* >			*mDynamicList;
	/// <value>Pointer to list of Static Entitys (Entities that usualy stay still)</value>
	LinkList<Base_Shape* >			*mStaticList;
	/// <value>Pointer to the Height Map</value>
	Height_Map*						mMap;
	/// <value>Pointer to a Physics_Formula instance</value>
	Physics_Formulas*				mFormula;
	///<summary> 
	///Check the collsions between two Squares. 
	///If they are colliding return the result
	///</summary>
	///<param name="squareone">Pointer to Square</param>
	///<param name="squaretwo">Pointer to Square</param>
	///<param name="point_of_collision">(Ref) Point of collision</param>
	///<param name="normal_of_collision">(Ref) Normal of the point of collision</param>
	///<returns>If the two Shapes are colliding</returns>
	bool CheckSQUARE_SQUARE(Square *squareone, Square *squaretwo, Physics::Vector& point_of_collision, Physics::Vector& normal_of_collision);
	///<summary> 
	///Check the collsions between a Squares and a Cylinder. 
	///If they are colliding return the result
	///</summary>
	///<param name="square">Pointer to Square</param>
	///<param name="cylinder">Pointer to Cylinder</param>
	///<param name="point_of_collision">(Ref) Point of collision</param>
	///<param name="normal_of_collision">(Ref) Normal of the point of collision</param>
	///<returns>If the two Shapes are colliding</returns>
	bool CheckSQUARE_CYLINDER(Square* square, Cylinder* cylinder, Physics::Vector& point_of_collision, Physics::Vector& normal_of_collision);	
	///<summary> 
	///Check the collsions between a Squares and a Sphere. 
	///If they are colliding return the result
	///</summary>
	///<param name="square">Pointer to Square</param>
	///<param name="sphere">Pointer to Sphere</param>
	///<param name="point_of_collision">(Ref) Point of collision</param>
	///<param name="normal_of_collision">(Ref) Normal of the point of collision</param>
	///<returns>If the two Shapes are colliding</returns>
	bool CheckSQUARE_SPHERE(Square* square, Sphere* sphere, Physics::Vector& point_of_collision, Physics::Vector& normal_of_collision);	
	///<summary> 
	///Check the collsions between a Sphere and a Cylinders. 
	///If they are colliding return the result
	///</summary>
	///<param name="sphere">Pointer to Sphere</param>
	///<param name="cylinder">Pointer to Cylinder</param>
	///<param name="point_of_collision">(Ref) Point of collision</param>
	///<param name="normal_of_collision">(Ref) Normal of the point of collision</param>
	///<returns>If the two Shapes are colliding</returns>
	bool CheckSPHERE_CYLINDER(Sphere* sphere, Cylinder* cylinder, Physics::Vector& point_of_collision, Physics::Vector& normal_of_collision);
	///<summary> 
	///Check the collsions between two Cylinder. 
	///If they are colliding return the result
	///</summary>
	///<param name="cylinderone">Pointer to Cylinder</param>
	///<param name="cylindertwo">Pointer to Cylinder</param>
	///<param name="point_of_collision">(Ref) Point of collision</param>
	///<param name="normal_of_collision">(Ref) Normal of the point of collision</param>
	///<returns>If the two Shapes are colliding</returns>
	bool CheckCYLINDER_CYLINDER( Cylinder* cylinderone, Cylinder* cylindertwo, Physics::Vector& point_of_collision, Physics::Vector& normal_of_collision);
	
	///<summary> 
	///Get a point on the hull of the first shape in the direction given.
	///Get a point on the hull of the second shape in the opposite of the direction given.
	///Then take point two away from point one and return the result.
	///This gives us the Minkowski Difference of the two Shape.
	///</summary>
	///<param name="Direction">Direction to find point on hull</param>
	///<param name="ShapeOne">Pointer to Shape</param>
	///<param name="ShapeTwo">Pointer to Shape</param>
	///<returns>Point on the hull of the Minkowski Difference of the two Shapes</returns>
	Physics::Vector Support(Physics::Vector Direction, Base_Shape* ShapeOne, Base_Shape* ShapeTwo);
	///<summary> 
	///Find what Simplex we are going to use by the size of the List.
	///When we find what simplex to use, call the function and pass the variables.
	///Then return the result.
	///</summary>
	///<param name="list">A reference to the list of points we have</param>
	///<param name="Direction">A refernece to the search direction</param>
	///<returns>If we have encapsulate the point (0,0,0)</returns>
	bool DoSimplex(std::vector<Physics::Vector> &list, Physics::Vector &Direction);
	///<summary> 
	///Check were the point (0,0,0) is in relation to the line.
	///Add a point to the list using Support in the direction 
	///of the passed direction.
	///Set the direction towards the point (0,0,0)
	///</summary>
	///<param name="list"> A reference to the list of points we have</param>
	///<param name="Direction">A refernece to the search direction</param>
	///<returns>If its possible to encapsulate the point (0,0,0)</returns>
	bool SimplexLine(std::vector<Physics::Vector> &list, Physics::Vector &Direction);
	///<summary> 
	///Check were the point (0,0,0) is in relation to the triangle.
	///Add a point to the list using Support in the direction 
	///of the passed direction.
	///Set the direction towards the point (0,0,0) based of the planes
	///and edges of the triangle and add a point in the direction that
	///</summary>
	///<param name="list"> A reference to the list of points we have</param>
	///<param name="Direction">A refernece to the search direction</param>
	///<returns>If its possible to encapsulate the point (0,0,0)</returns>
	bool SimplexTriangle(std::vector<Physics::Vector> &list, Physics::Vector &Direction);
	///<summary> 
	///Check if the Quadrilateral encapsulates the point (0,0,0).
	///If it does return true
	///If it doesnt delete the first point we added and call SimplexTriangle 
	///on the remaining points.
	///</summary>
	///<param name="list"> A reference to the list of points we have</param>
	///<param name="Direction">A refernece to the search direction</param>
	///<returns>If its possible to encapsulate the point (0,0,0)</returns>
	bool SimplexQuadrilateral(std::vector<Physics::Vector> &list, Physics::Vector &Direction);
	///<summary> 
	///Constructor
	///</summary>
	Collision_Manager();
public:
	///<summary> 
	///If there has been no instance create an instance of this object and return it.
	///If there is already an instance of this object return it.
	///</summary>
	///<returns>Pointer to the Instance of this Object</returns>
	static Collision_Manager* getInstance();
	///<summary> 
	///Destructor
	///</summary>
	~Collision_Manager();
	///<summary> 
	///Check if the bounding radius of one Object is colliding 
	///with the bounding radius of the other Object.
	///</summary>
	///<param name="ShapeOne">Pointer to first Shape</param>
	///<param name="ShapeTwo">Pointer to second Shape</param>
	///<returns>If the two Shapes are colliding</returns>
	bool Check_BoundingRadius(Base_Shape* ShapeOne, Base_Shape* ShapeTwo);
	///<summary> 
	///GJK Collision algorithm
	///Checks if two Shapes are colliding based on the Minkowski Difference 
	///of the two Shapes. Checks if the point(0,0,0) is inside the new Shape
	///If it is then the Shapes are colliding
	///</summary>
	///<param name="ShapeOne">Pointer to Shape</param>
	///<param name="ShapeTwo">Pointer to Shape</param>
	///<returns>If the two Shapes are colliding</returns>
	bool Check_GFK(Base_Shape* ShapeOne, Base_Shape* ShapeTwo);
	///<summary> 
	///SAT Collision algorithm
	///Check what type of Shapes are being Passed into the function.
	///Then call the appropriate SAT method.
	///Return result.
	///</summary>
	///<param name="ShapeOne">Pointer to Shape</param>
	///<param name="ShapeTwo">Pointer to Shape</param>
	///<param name="point_of_collision">(Ref) Point of collision</param>
	///<param name="normal_of_collision">(Ref) Normal of the point of collision</param>
	///<returns>If the two Shapes are colliding</returns>
	bool Check_SAT(Base_Shape* ShapeOne, Base_Shape* ShapeTwo, Physics::Vector& point_of_collision, Physics::Vector& normal_of_collision);
	///<summary> 
	///Checks if any of the Entitys in the list of Shapes are colliding
	///If they are then calls appropriate code tell them that they are colliding
	///</summary>
	///<param name="CollisionList">Pointer to a Set of Shapes</param>
	void FindCollisions(LinkList<Base_Shape* >* CollisionList);
	///<summary> 
	///Checks if any of the Entities in the list of Shapes are colliding with any
	///Entities from the other list of Shapes
	///If they are then calls appropriate code tell them that they are colliding
	///</summary>
	///<param name="FirstList">Pointer to a Set of Shapes</param>
	///<param name="SecondList">Pointer to a Set of Shapes</param>
	void FindCollisions(LinkList<Base_Shape* >* FirstList, LinkList<Base_Shape* >* SecondList);
	///<summary> 
	///Checks if any of the Entities in the list of Shapes are colliding with any
	///the Shape that was Passed
	///If they are then calls appropriate code tell them that they are colliding
	///</summary>
	///<param name="CollisionList">Pointer to a Set of Shapes</param>
	///<param name="Shape">Pointer to Shape</param>
	bool Check_If_Colliding(LinkList<Base_Shape* >* CollisionList, Base_Shape* Shape);
	///<summary> 
	///Check how close the xz of a point is by a radius to any other entity in the game
	///</summary>
	///<param name="pos">Point we are checking</param>
	///<param name="radius">Distance from point</param>
	///<returns>If a Entity in the Game is within the Radius to the Point</returns>
	bool Check_Proximity(Physics::Vector pos, float radius);
	///<summary> 
	///Initialisation of this Class
	///</summary>
	///<param name="dynamiclist">Pointer to the Entitys that move</param>
	///<param name="staticlist">Pointer to the Entities that usualy stay still</param>
	///<param name="Map">Pointer to the Height Map</param>
	void INIT(LinkList<Base_Shape* > *dynamiclist,LinkList<Base_Shape* > *staticlist,Height_Map *Map);
	///<summary> 
	///Shoot ray into the World and Check if it hits any Shape that is Passed in
	///</summary>
	///<param name="ray">Ray Details</param>
	///<param name="Shape">Pointer to an Array of Shapes</param>
	///<returns>Returns new distance of Ray</returns>
	float ShootRay(Ray ray,Base_Shape** Shape);
};
#endif