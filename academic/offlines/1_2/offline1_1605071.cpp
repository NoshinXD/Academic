#include<iostream>
#include<cmath>
using namespace std;

class Point2D
{
	int x,y;
public:
	Point2D(){ x = 0; y = 0; }
	Point2D(int x, int y);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	void print();
	~Point2D(){ x = 0; y = 0; }
};

Point2D::Point2D(int argx,int argy)
{
	x = argx;
	y = argy;
}

void Point2D::setX(int argx)
{
	x = argx;
}

void Point2D::setY(int argy)
{
	y = argy;
}

int Point2D::getX()
{
	return x;
}

int Point2D::getY()
{
	return y;
}

void Point2D::print()
{
	cout << "(" << x << "," << y << ")";
}

class Circle
{
	Point2D center;
	double radius;
public:
    Circle()
    {
        Point2D(0,0);
        radius=0;
    }

	Circle(Point2D c, double r);

    void setC(Point2D c);
	void setR(double r);

	Point2D getC();
	double getR();

	double area();
	void print();
	int intersect(Circle rhs);
	int contains(Circle rhs);
	int contains(Point2D p);
	double perimeter();

	~Circle()
	{
	    Point2D(0,0);
        radius=0;
	}
};

Circle::Circle(Point2D c, double r)
{
	center = c;
    radius=r;
}

void Circle::setC(Point2D c)
{
    center = c;
}

void Circle::setR(double r)
{
    radius = r;
}

Point2D Circle::getC()
{
   return center;
}

double Circle::getR()
{
   return radius;
}

double Circle::area()
{
	return 3.1419*radius*radius;
}

int Circle::contains(Circle rhs)
{
	double d;

	d=(center.getX()-rhs.center.getX())*(center.getX()-rhs.center.getX())+(center.getY()-rhs.center.getY())*(center.getY()-rhs.center.getY());
	d=sqrt(d);

	d=d+rhs.radius;

	if(radius>=d)
        return 1;
    else
        return 0;
}

int Circle::intersect(Circle rhs)
{
	double d;

	d = (center.getX()-rhs.center.getX())*(center.getX()-rhs.center.getX())+(center.getY()-rhs.center.getY())*(center.getY()-rhs.center.getY());
	d = sqrt(d);

	if(d<radius+rhs.radius)
        return 1;
    else
        return 0;
}

int Circle::contains(Point2D p)
{
    double d;

    d=(center.getX()-p.getX())*(center.getX()-p.getX())+(center.getY()-p.getY())*(center.getY()-p.getY());
    d=sqrt(d);

    if(d<=radius)
        return 1;
    else
        return 0;
}

double Circle::perimeter()
{
    return 2*3.1416*radius;
}

void Circle::print()
{
	cout << "Center: ";
	center.print();
	cout << "Radius: " << radius;
}

class Rectangle
{
	Point2D tr, bl;

public:
	Rectangle()
    {
        Point2D(0,0);
        Point2D(0,0);

    }

	Rectangle(Point2D trp, Point2D blp);

	void setTR(Point2D trp);
	void setBL(Point2D blp);

    Point2D getTR();
	Point2D getBL();

	double area();
	int intersect(Rectangle rhs);
	int contains(Rectangle rhs);
	int inside(Circle c);
	double perimeter();

	~Rectangle()
    {
        Point2D(0,0);
        Point2D(0,0);
    }
};

Rectangle::Rectangle(Point2D trp, Point2D blp)
{
    tr = trp;
    bl = blp;
}

void Rectangle::setTR(Point2D trp)
{
    tr = trp;
}

void Rectangle::setBL(Point2D blp)
{
    bl = blp;
}

Point2D Rectangle::getTR()
{
   return tr;
}

Point2D Rectangle::getBL()
{
   return bl;
}

double Rectangle::area()
{
    return (abs(bl.getX()-tr.getX())*abs(bl.getY()-tr.getY()));
}

int Rectangle::contains(Rectangle rhs)
{
    if(rhs.tr.getX()<=tr.getX() && rhs.bl.getX()>=bl.getX() && rhs.tr.getY()<=tr.getY() && rhs.bl.getY()>=bl.getY())
        return 1;
    else
        return 0;
}

int Rectangle::intersect(Rectangle rhs)
{
    if(contains(rhs)==1 || rhs.tr.getX()<=bl.getX() || rhs.bl.getX()>=tr.getX() || rhs.bl.getY()>=tr.getY() || rhs.tr.getY()<=bl.getY())
        return 0;
    else
        return 1;
}

/*int Rectangle::inside(Circle c)
{
    int in=c.contains(tr)+c.contains(bl);

    if(in==2)
        return 1;
    else
        return 0;
}*/

int Rectangle::inside(Circle c)
{
    double d,d1,d2,d3,d4;

    d=c.getR();

    d1=(c.getC().getX()-bl.getX())*(c.getC().getX()-bl.getX())+(c.getC().getY()-bl.getY())*(c.getC().getY()-bl.getY());
    d1=sqrt(d1);

    d2=(c.getC().getX()-tr.getX())*(c.getC().getX()-tr.getX())+(c.getC().getY()-tr.getY())*(c.getC().getY()-tr.getY());
    d2=sqrt(d2);

    d3=(c.getC().getX()-bl.getX())*(c.getC().getX()-bl.getX())+(c.getC().getY()-tr.getY())*(c.getC().getY()-tr.getY());
    d3=sqrt(d1);

    d4=(c.getC().getX()-tr.getX())*(c.getC().getX()-tr.getX())+(c.getC().getY()-tr.getY())*(c.getC().getY()-tr.getY());
    d4=sqrt(d1);

    if(d1<=d && d2<=d && d3<=d && d4<=d)
        return 1;
    else
        return 0;
}

double Rectangle::perimeter()
{
    return 2*(abs(bl.getX()-tr.getX())+abs(tr.getY()-bl.getY()));
}

int main(void)
{
    cout<<"CIRCLE INFO:"<<endl;

    Point2D center(1,2), centerhs(2,3), cent(3,4);

    Circle cir(center, 6), cirhs(centerhs, 5), cirt(cent, 4);

	cout<<"Area: "<<cir.area()<<endl;

    if(cir.intersect(cirhs)==1)
        cout<<"Circle 1 intersects Circle 2."<<endl;
    else
        cout<<"Circle 1 does not intersect Circle 2."<<endl;

    if(cir.contains(cirt)==1)
        cout<<"Circle 1 contains Circle 2."<<endl;
    else
        cout<<"Circle 1 does not contain Circle 2."<<endl;

    cout<<"perimeter: "<<cir.perimeter()<<endl;


    cout<<"RECTANGLE INFO:"<<endl;

    Point2D tr(5,10),bl(2,6), trrhs(4,6),blrhs(2,1), trt(4,9),blt(3,7);

    Rectangle rec(tr, bl), recrhs(trrhs, blrhs), rect(trt,blt);

	cout<<"Area: "<<rec.area()<<endl;

	if(rec.intersect(recrhs)==1)
        cout<<"Rectangle 1 intersects Rectangle 2."<<endl;
    else
        cout<<"Rectangle 1 does not intersect Rectangle 2."<<endl;

	if(rec.contains(rect)==1)
        cout<<"Rectangle 1 contains Rectangle 2."<<endl;
    else
        cout<<"Rectangle 1 does not contain Rectangle 2."<<endl;

    if(rec.inside(cirhs)==1)
        cout<<"Rectangle 1 is completely inside the circle."<<endl;
    else
        cout<<"Rectangle 1 is not completely inside the circle."<<endl;

    cout<<"Perimeter: "<<rec.perimeter()<<endl;

	return 0;
}
