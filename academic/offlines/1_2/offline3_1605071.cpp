#include<iostream>
#include<cmath>
using namespace std;

typedef enum {UNDEFINED, POINT2D, POINT3D, CIRCLE, SQUARE, RECTANGLE, SPHERE} STYPE;

class Shape
{
	STYPE type;
public:
	Shape();
	Shape(STYPE argtype);
	virtual void print();
	virtual double area();
	//virtual double volume();
	virtual bool contains(const Shape *rhs);
	//Intentionally made non-virtual
	bool operator==(const Shape &rhs);
	virtual ~Shape(){}
};

Shape::Shape()
{
	type = UNDEFINED;
}

Shape::Shape(STYPE argtype)
{
	type = argtype;
}

double Shape::area()
{
	cout << "I am a dummy Shape";
	return 0.0;
}

/*double Shape::volume()
{
	cout << "\nI am a dummy Shape";
	return 0.0;
}*/
bool Shape::contains(const Shape *rhs)
{
	cout << "You see this, because appropriate contains function is undefined";
	return false;
}

void Shape::print()
{
	cout << "Type: " << type;
}

bool Shape::operator==(const Shape &rhs)
{
	if(type==rhs.type) return true;
	else return false;
}

class Point2D : public Shape
{
	double x,y;
public:
	Point2D();
	Point2D(STYPE argtype, double argx, double argy);
	void print();
	double area();
	bool contains(const Shape * s);
	bool contains(const Point2D * rhs);
	bool operator==(const Shape *s);
	bool operator==(const Point2D &rhs);

    void setX(double argx) {x=argx;}
    void setY(double argy) {y=argy;}
	double getX() const { return x; }
	double getY() const { return y; }
	~Point2D(){}
};

Point2D::Point2D() //calls Base's default constructor
{
	x = 0.0;
	y = 0.0;
}

Point2D::Point2D(STYPE argtype, double argx, double argy) : Shape(argtype)
{
	x = argx;
	y = argy;
}

void Point2D::print()
{
	Shape::print();
	cout << " (" << x << "," << y << ")";
}

double Point2D::area()
{
	return 0.0;
}

bool Point2D::contains(const Shape *s)
{
	const Point2D * pointType = dynamic_cast<const Point2D*>(s);
	if(pointType!=NULL)
	{
		//Supported
		return contains(pointType);   //bujhi na
	}
	//By default, use base
	return Shape::contains(s);
}

bool Point2D::contains(const Point2D * rhs)
{
	if(x==rhs->x && y==rhs->y) return true;
	else return false;
}

bool Point2D::operator==(const Point2D & rhs)
{
	if( !Shape::operator==(rhs) ) return false;
	if( x==rhs.x && y==rhs.y ) return true;
	else return false;
}

class Rectangle : public Shape
{
	Point2D topRight;
	Point2D bottomLeft;
public:
	Rectangle();//implement this
	Rectangle(STYPE type, Point2D tr, Point2D bl);//implement this
    void SetTR(Point2D tr){topRight=tr;}
    void SetBL(Point2D bl){bottomLeft=bl;}
    Point2D GetTR() const {return topRight;}
    Point2D GetBL() const{return bottomLeft;}

	void print(); //implement this
	double area(); //implement this
	bool contains(const Shape *rhs);
	bool contains(const Point2D *s);//implement this to check containment for point2d only
	bool operator==(const Rectangle &rhs); //implement this

	~Rectangle(){}
};
Rectangle :: Rectangle()
{
    Point2D topRight();
    Point2D bottomLeft();
}

Rectangle::Rectangle(STYPE type ,Point2D tr,Point2D bl): Shape(type)
{
    topRight=tr;
    bottomLeft=bl;
}

/*void Rectangle::print()
{
    cout<<"Top right co-ordinate:";
    topRight.print();
    cout<<" ,Bottom left co-ordinate:";
    bottomLeft.print();
    cout<<"\n";
}*/

void Rectangle::print()
{
    cout << "Top right point: ";
	topRight.print();
	cout<<" ";
	cout << "Bottom left point: ";
	bottomLeft.print();
}

double Rectangle::area()
{
    return abs(topRight.getX()-bottomLeft.getX())*(topRight.getY()-bottomLeft.getY());
}

bool Rectangle::contains(const Shape *rhs)
{
    const Point2D * pointType = dynamic_cast<const Point2D*>(rhs);
	if(pointType!=NULL)
	{
		//Supported
		return contains(pointType);
	}

	return Shape::contains(rhs);
}

bool Rectangle::contains(const Point2D *s)
{
    if((s->getX()<topRight.getX()) && (s->getX()>bottomLeft.getX()) && (s->getY()<topRight.getY()) && (s->getY()>bottomLeft.getY()))
        return true;
    else
        return false;
}

bool Rectangle ::operator==(const Rectangle &rhs)
{
    //if(topRight.getX()>=rhs.topRight.getX()  && topRight.getY()>=rhs.topRight.getY()  && bottomLeft.getX()<=rhs.bottomLeft.getX() && bottomLeft.getY()<=rhs.bottomLeft.getY())
    if(abs(bottomLeft.getX()-rhs.topRight.getX()) &&  abs(bottomLeft.getY()-rhs.topRight.getY()))
    {
        return true;
    }
    else
        return false;
}

/*bool Rectangle ::operator==(const Rectangle &rhs)
{
    if(area()==rhs.area())
        return true;
    else
        return false;
}*/

class Circle : public Shape
{
	Point2D center;
	double radius;
public:
	Circle();
	Circle(STYPE type, Point2D c, double r); //implement this
	void setC(Point2D c){center=c;}
	void setR(double r){radius=r;}
	Point2D getC() const {return center;}
	double getR() const {return radius;}

	double area(); //implement this
	void print(); //implement this
	bool contains(const Shape * s); //implemented partially
	bool contains(const Point2D * p); //implement this
	bool contains(const Circle * rhs); //implement this
	bool contains(const Rectangle * p); //implement this
	bool operator==(const Circle &rhs); //implement this
	~Circle(){}
};

Circle ::Circle()
{
    Point2D center();
    radius=0;
}

Circle ::Circle(STYPE type, Point2D c, double r) : Shape(type)
{
    center=c;
    radius=r;
}

double Circle::area()
{
    return 3.1419*radius*radius;
}

/*void Circle::print()
{
    cout<<"Center:";
    center.print();
    cout<<" Radius:"<<radius<<endl;
}*/

void Circle::print()
{
    cout << "Center: ";
	center.print();
	cout << "Radius: " << radius;
}


bool Circle::contains(const Shape * s)
{
    const Point2D * pointType = dynamic_cast<const Point2D*>(s);
	if(pointType!=NULL)
	{
		//Supported
		return contains(pointType);
	}

	const Circle * circleType = dynamic_cast<const Circle*>(s);
	if(circleType!=NULL)
	{
		//Supported
		return contains(circleType);
	}

	const Rectangle * rectangleType = dynamic_cast<const Rectangle*>(s);
	if(rectangleType!=NULL)
	{
		//Supported
		return contains(rectangleType);
	}

	return Shape::contains(s);
}

bool Circle::contains(const Point2D * p)
{
    double d,r;
    d = (center.getX()-p->getX())* (center.getX()-p->getX()) + (center.getY()-p->getY())* (center.getY()-p->getY());
    d=sqrt(d);
    r = getR();

    if(d<r)
    {
        return true;
    }
    else
        return false;

}
bool Circle ::contains(const Circle * rhs)
{
    double d,d2;
    d = (center.getX()-rhs->center.getX())* (center.getX()-rhs->center.getX()) + (center.getY()-rhs->center.getY())* (center.getY()-rhs->center.getY());
    d=sqrt(d);
    d2=  getR()- rhs->getR();

    if(d<=d2)
    {
        return true;
    }
    else
        return false;
}
bool Circle ::contains(const Rectangle * p)
{
    double d,d1,d2,d3,d4;
    d=radius;

    d2=(center.getX()-p->GetBL().getX() )* (center.getX()-p->GetBL().getX()) + (center.getY()-p->GetBL().getY() )* (center.getY()-p->GetBL().getY());
    d2=sqrt(d2);
    d1=(center.getX()-p->GetTR().getX()) * (center.getX()-p->GetTR().getX()) + (center.getY()-p->GetTR().getY()) * (center.getY()-p->GetTR().getY());
    d1=sqrt(d1);
    d3=(center.getX()-p->GetTR().getX() )* (center.getX()-p->GetTR().getX()) + (center.getY()-p->GetBL().getY()) * (center.getY()-p->GetBL().getY());
    d3=sqrt(d3);
    d4=(center.getX()-p->GetBL().getX() )* (center.getX()-p->GetBL().getX()) + (center.getY()-p->GetTR().getY()) * (center.getY()-p->GetTR().getY());
    d3=sqrt(d4);

    if(d1<=d && d2<=d && d3<=d  && d4<=d )
    {
        return true;
    }
    else
        return false;
}

bool Circle::operator==(const Circle & rhs)
{
	if( !Shape::operator==(rhs) ) return false;
	if( radius==rhs.radius ) return true;
	else return false;
}


class Shape3D : public Shape
{

public:
	Shape3D();
	Shape3D(STYPE argtype);
    double area();
	virtual double volume();
	~Shape3D(){}
};

Shape3D::Shape3D()
{

}

Shape3D::Shape3D(STYPE argtype) : Shape(argtype)
{

}

double Shape3D::area()
{
	cout << "I am a dummy Shape";
	return 0.0;
}
double Shape3D::volume()
{
	cout << "You see this, because appropriate function is missing in the derived class";
	return 0.0;
}


class Point3D : public Point2D ,public Shape3D
{
    double z;
public:
    Point3D(); //already implemented
    Point3D(STYPE type, double argx, double argy, double argz); //implement this
    void setZ(double argz){z=argz;}
    double getZ() const {return z;}
    void print(); //already implemented
    //double area(); Not needed, base version is sufficient
	bool contains(const Shape *rhs); //implement this
	bool contains(const Point3D *rhs);  //implement this
	~Point3D(){}
};

Point3D::Point3D()
{
    z = 0;
}

Point3D:: Point3D(STYPE argtype, double argx, double argy, double argz):Point2D(argtype,argx,argy), Shape3D(argtype)
{
    z=argz;
}
void Point3D::print()
{
	Shape3D::print();
    cout << " (" << getX() << "," << getY() << "," << z << ")";
}

bool Point3D :: contains(const Shape *rhs)
{
    const Point3D * pointType = dynamic_cast<const Point3D*>(rhs);
	if(pointType!=NULL)
	{

		return contains(pointType);
	}

	return Point2D::contains(rhs);
}

bool Point3D ::contains(const Point3D *rhs)
{
    if(getX()==rhs->getX() && getY()==rhs->getY() && z==rhs->z) return true;
	else return false;
}


class Sphere : public Shape3D
{
	Point3D center;
	double radius;
public:
	Sphere();//implement this
	Sphere(STYPE type, Point3D c, double r);//implement this
	void setR(double r){radius=r;}
	double getR() const {return radius;}
	void print(); //implement this
	double area(); //implement this
	double volume(); //implement this
	bool contains(const Shape * rhs); //implement this for checking containgment of Point3D, Sphere inside sphere
	bool contains(const Point3D * p); //implement this
	bool contains(const Sphere * s); //implement this
	~Sphere(){}
};
Sphere::Sphere()
{
    Point3D center();
    radius=0;
}

Sphere :: Sphere(STYPE type, Point3D c, double r) : Shape3D(type)
{
    center=c;
    radius=r;
}
void Sphere::print()
{
    cout<<"Center:";
    center.print();
    cout<<" Radius:"<<radius;
}

double Sphere::area()
{
    return 4*3.1419*radius*radius;
}

double Sphere::volume()
{
    return (4*3.1419*radius*radius*radius)/3;
}

bool Sphere::contains(const Shape * rhs)
{
    const Point3D * pointType = dynamic_cast<const Point3D*>(rhs);
	if(pointType!=NULL)
	{
		//Supported
		return contains(pointType);
	}

	const Sphere * sphereType = dynamic_cast<const Sphere*>(rhs);
	if(sphereType!=NULL)
	{
		//Supported
		return contains(sphereType);
	}

	return Shape::contains(rhs);
}

bool Sphere::contains(const Point3D * p)
{

    double d,r;
    d = (center.getX()-p->getX())* (center.getX()-p->getX()) + (center.getY()-p->getY())* (center.getY()-p->getY()) + (center.getZ()-p->getZ())* (center.getZ()-p->getZ());
    d=sqrt(d);
    r = radius;

    if(d<r)
    {
        return true;
    }
    else
        return false;

}
bool Sphere ::contains(const Sphere * s)
{
    double d,d2;
    d = (center.getX()-s->center.getX())* (center.getX()-s->center.getX()) + (center.getY()-s->center.getY())* (center.getY()-s->center.getY()) + (center.getZ()-s->center.getZ()) * (center.getZ()-s->center.getZ());
    d=sqrt(d);
    d2=  radius- s->getR();

    if(d<=d2)
    {
        return true;
    }
    else
        return false;
}
int main(void)
{
	//Write main function to demonstrate your code
	//Create circles, rectanges, point2d,point3d,and sphere objects using base class pointers
	//then call the virtual methods to show that polymorphism works!
	while(1)
	{
		int choice;
		Shape * shape, *shape1,*shape2,*shape3,*shape4,*shape5,*shape6,*shape7,*shape8,*shape9;
		Shape3D * shape3D, *shape3D1, *shape3D2;
		cout << "1. Point2D 2. Rectangle 3. Circle\n";
        cout << "4. Point3D 5. Sphere. 0. Exit\n";
        cout << "Your choice:";
        cin >> choice;
		switch(choice)
		{

			case 1:
            {
                shape = new Point2D(POINT2D, 5.0,10.0);
                shape1 = new Point2D(POINT2D,3.0,4.0);
                shape2 = new Point2D(POINT2D,5.0,10.0);
                cout<<"The first point is:";
				shape->print();
				cout<<"\nThe second point is:";
				shape1->print();
				cout << "\nArea: " << shape->area()<<endl;
				if(shape->contains(shape1))
                    cout<<"1st point contains the 2nd point."<<endl;
                else
                     cout<<"1st point does not contain the 2nd point."<<endl;
                if(shape==shape2)
                    cout<<"They are same"<<endl;
                else
                    cout<<"They are not same"<<endl;
				break;
            }
			case 2:
            {
                Point2D p1(POINT2D,5.0,5.0);
				Point2D p2(POINT2D,20.0,20.0);
				shape = new Rectangle(RECTANGLE, p2, p1);
				shape3 = new Point2D(POINT2D,6.0,7.0);
				cout<<"Rectangle is:";
				shape->print();
				cout << "\nArea: " << shape->area()<<endl;
				cout<<"The point is:";
				shape3->print();
				if(shape->contains(shape3))
                    cout<<"\nThe rectangle contains the point"<<endl;
                else
                    cout<<"\nThe rectangle does not contain the point"<<endl;

				break;
            }
			case 3:
            {
                Point2D p1(POINT2D,0.0,0.0);
				shape = new Circle(CIRCLE,p1,10.0);
				shape->print();
				cout<<"\nArea: "<<shape->area()<<endl;
				cout<<"A point is :";
				shape4= new Point2D(POINT2D,5.0,7.0);
				shape4->print();
				if(shape->contains(shape4))
                    cout<<"\nThe circle contains the point."<<endl;
                else
                    cout<<"\nThe circle does not contain the point."<<endl;

                Point2D p2(POINT2D,2.0,3.0);
                cout<<"A Circle is :";
				shape5 = new Circle(CIRCLE,p2,6.0);
				shape5->print();
				if(shape->contains(shape5))
                    cout<<"\nThe 1st circle contains the 2nd Circle."<<endl;
                else
                    cout<<"\n3The 1st circle does not contain the 2nd Circle."<<endl;

                Point2D p3(POINT2D,2.0,3.0),p4(POINT2D,-1.0,2.0);
                cout<<"A Rectangle is :";
				shape6 = new Rectangle(RECTANGLE,p3,p4);
				shape6->print();
				if(shape->contains(shape6))
                    cout<<"\nThe circle contains the Rectangle."<<endl;
                else
                    cout<<"\nThe circle does not contain the Rectangle."<<endl;

				break;
            }
			case 4:
            {
                cout<<"The 1st point is:";
                shape3D = new Point3D(POINT3D,5.0,10.0,20.0);
				shape3D->print();
				cout << "\nArea: " << shape3D->area();
				cout << "\nvolume: " << shape3D->volume()<<endl;
				cout<<"The 2nd point is:";
				shape3D1 = new Point3D(POINT3D,2.0,5.0,10.0);
				shape3D1->print();
				if(shape3D->contains(shape3D1))
                    cout<<"\nThe 1st point contains the 2nd point."<<endl;
                else
                     cout<<"\nThe 1st point does not contain the 2nd point."<<endl;


				break;
            }
			case 5:
            {
                Point3D p1(POINT3D,0.0,0.0,0.0);
				shape3D = new Sphere(SPHERE,p1,10.0);
				cout<<"the 1st sphere is:";
				shape3D->print();
				cout << "\nArea: " << shape3D->area();
				cout << "\nVolume: " << shape3D->volume();
				shape3D2 = new Point3D(POINT3D,1.0,1.0,1.0);
				if(shape3D->contains(shape3D2))
                    cout<<"The Sphere contains the point."<<endl;
                else
                    cout<<"The Sphere does not contain the point."<<endl;

                Point3D p2(POINT3D,2.0,3.0,4.0);
                cout<<"A Sphere is :";
				shape3D1 = new Sphere(SPHERE,p2,6.0);
				shape3D1->print();
				if(shape3D->contains(shape3D1))
                    cout<<"\nThe 1st Sphere contains the 2nd Sphere."<<endl;
                else
                    cout<<"\nThe 1st Sphere does not contain the 2nd Sphere."<<endl;

				break;
		    }
		}

		if(choice==0.0)return 0;


	}

	//add other functions for demonstration
	return 0;
}
