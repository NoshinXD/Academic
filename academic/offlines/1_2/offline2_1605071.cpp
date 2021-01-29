#include<iostream>
#include<cmath>
using namespace std;

class Point2D
{
	double x,y;
public:
	Point2D(){ x = 0; y = 0; }
	Point2D(double x, double y);

	void setX(double x);
	void setY(double y);
	double getX();
	double getY();
	void print();

	Point2D operator + (Point2D ob1);
	Point2D operator * (double n);
	bool operator == (Point2D ob3);
	bool operator != (Point2D ob4);

	~Point2D(){ x = 0; y = 0; }
};

Point2D::Point2D(double argx,double argy)
{
	x = argx;
	y = argy;
}

void Point2D::setX(double argx)
{
	x = argx;
}

void Point2D::setY(double argy)
{
	y = argy;
}

double Point2D::getX()
{
	return x;
}

double Point2D::getY()
{
	return y;
}

void Point2D::print()
{
	cout << "(" << x << "," << y << ")";
}

Point2D Point2D::operator + (Point2D ob1)
{
    Point2D p;

    p.x=x+ob1.x;
    p.y=y+ob1.y;

    return p;
}

Point2D Point2D::operator * (double n)
{
    Point2D p;

    p.x=x*n;
    p.y=y*n;

    return p;
}

bool Point2D::operator == (Point2D ob3)
{
    return (x == ob3.x) & (y == ob3.y);
}

bool Point2D::operator != (Point2D ob4)
{
    return (x == ob4.x) & (y == ob4.y);
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

    void print();

	Circle operator+(Point2D rhs);
	Circle operator*(double n);

	Circle operator+(Circle rhs);
	Circle operator-(Circle rhs);

	bool operator==(Circle rhs);
    bool operator>(Circle rhs);
    bool operator>=(Circle rhs);
    bool operator<(Circle rhs);
    bool operator<=(Circle rhs);

    Circle operator++();
    Circle operator++(int notused);

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

void Circle::print()
{
	cout << "Center: ";
	center.print();
	cout<<" ";
	cout << "Radius: " << radius;
}

Circle Circle::operator+(Point2D p)
{
    Circle rhs;

    rhs.center.setX(center.getX()+p.getX());
    rhs.center.setY(center.getY()+p.getY());

    rhs.setR(getR());

    return rhs;
}

Circle Circle::operator*(double n)
{
    Circle c;

    c.center.setX(center.getX()*n);
    c.center.setY(center.getY()*n);

    c.setR(getR());

    return c;
}

Circle Circle::operator+(Circle rhs)
{
    double a = getR()/(getR()+rhs.getR());

    Circle c;

    c.center.setX(center.getX()*a + rhs.center.getX()*(1-a));
    c.center.setY(center.getY()*a + rhs.center.getY()*(1-a));

    c.setR(getR()+rhs.getR());

    return c;
}

Circle Circle::operator-(Circle rhs)
{
    double a = getR()/(getR()+rhs.getR());

    Circle c;

    c.center.setX(center.getX()*a+rhs.center.getX()*(1-a));
    c.center.setY(center.getY()*a+rhs.center.getY()*(1-a));

    c.setR(fabs(getR()-rhs.getR()));

    return c;
}

bool Circle::operator==(Circle rhs)
{
    return 3.1416*getR()*getR() == 3.1416*rhs.getR()*rhs.getR();
}

bool Circle::operator>(Circle rhs)
{
    return 3.1416*getR()*getR() > 3.1416*rhs.getR()*rhs.getR();
}

bool Circle::operator>=(Circle rhs)
{
    return 3.1416*getR()*getR() >= 3.1416*rhs.getR()*rhs.getR();
}

bool Circle::operator<(Circle rhs)
{
    return 3.1416*getR()*getR() < 3.1416*rhs.getR()*rhs.getR();
}

bool Circle::operator<=(Circle rhs)
{
    return 3.1416*getR()*getR() <= 3.1416*rhs.getR()*rhs.getR();
}

Circle Circle::operator++()
{
    double r;
    Circle c;

    radius++;
    r=radius;

    c.center.setX(center.getX());
    c.center.setY(center.getY());
    c.setR(getR());

    return c;
}

Circle Circle::operator++(int notused)
{
    double r;
    Circle c;

    c.center.setX(center.getX());
    c.center.setY(center.getY());
    c.setR(getR());

    radius++;

    return c;
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

    void print();

	Rectangle operator + (Point2D p);
	Rectangle operator * (double n);

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

void Rectangle::print()
{
	cout << "tr: ";
	tr.print();
	cout<<" ";
	cout << "bl: ";
	bl.print();
}

Rectangle Rectangle:: operator+(Point2D p)
{
    Rectangle r;

    r.setTR(tr.operator+(p));
    r.setBL(bl.operator+(p));

    return r;
}

Rectangle Rectangle::operator*(double n)
{
    Rectangle r;

    r.setTR(tr.operator*(n));
    r.setBL(bl.operator*(n));

    return r;
}

int main(void)
{
    cout<<"POINT INFO:\n"<<endl;

    Point2D p1(5,6),p2(7,8),p,q;

    cout<<"Point 1: ";
    p1.print();

    cout<<"\nPoint 2: ";
    p2.print();

    p = p1 + p2;
    cout<<"\nSummation of the two points: ";
    p.print();

    double n=2;

    q = p1 * n;
    cout<<"\nScaling of Point 1: ";
    q.print();

    cout<<"\nThe two co-ordinates are same: ";
    if(p1==p2)
        cout<<"True"<<endl;
    else
        cout<<"False"<<endl;

    cout<<"The two co-ordinates are not same: ";
    if(p1==p2)
        cout<<"False"<<endl;
    else
        cout<<"True"<<endl;

    cout<<"\nCIRCLE INFO:"<<endl;

    Point2D center1(1,2), center2(2,3);

    Circle cir(center1, 6), cirhs(center2, 5), cir1,cir2,cir3,cir4,cir5,cir6;

    cout<<"\nCircle 1: ";
    cir.print();
    cout<<"\nCircle 2: ";
    cirhs.print();

	cir1=cir+p1;
	cout<<"\nAdding Point 1 to Center of Circle 1: ";
	cir1.print();

	cir2=cir*n;
	cout<<"\nAfter scaling Center of Circle 1: ";
	cir2.print();

	cir3=cir+cirhs;
	cout<<"\nAdding two circles: ";
	cir3.print();

	cir4=cir-cirhs;
	cout<<"\nSubtracting two circles: ";
	cir4.print();

    cout<<"\nCircle 1 is equal to Circle 2: ";
    if(cir==cirhs)
        cout<<"TRUE"<<endl;
    else
        cout<<"FALSE"<<endl;

    cout<<"Circle 1 is greater than Circle 2: ";
    if(cir>cirhs)
        cout<<"TRUE"<<endl;
    else
        cout<<"FALSE"<<endl;

    cout<<"Circle 1 is greater or equal to Circle 2: ";
    if(cir>=cirhs)
        cout<<"TRUE"<<endl;
    else
        cout<<"FALSE"<<endl;

    cout<<"Circle 1 is less than Circle 2: ";
    if(cir<cirhs)
        cout<<"TRUE"<<endl;
    else
        cout<<"FALSE"<<endl;

    cout<<"Circle 1 is less or equal to Circle 2: ";
    if(cir<=cirhs)
        cout<<"TRUE"<<endl;
    else
        cout<<"FALSE"<<endl;

    cir++;
    ++cirhs;

    cout<<"Postfix for Circle 1: ";
    cir.print();

    cout<<"\nprefix for Circle 2: ";
    cirhs.print();

    cout<<"\n\nRECTANGLE INFO:"<<endl;

    Point2D tr(5,10),bl(2,6);

    Rectangle rec(tr, bl),rec1,rec2;

    cout<<"\nRectangle: ";
    rec.print();

    rec1=rec+p1;
    cout<<"\nAdding Point 1: ";
    rec1.print();

    rec2=rec*n;
    cout<<"\nAfter scaling top-right and bottom-left points of Rectangle: ";
    rec2.print();

	return 0;
}















