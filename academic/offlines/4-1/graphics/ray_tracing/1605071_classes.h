//
// Created by ubushin on ২০/৬/২১.
//

#ifndef RAY_TRACINGV1_1605071_CLASSES_H
#define RAY_TRACINGV1_1605071_CLASSES_H

#endif //RAY_TRACINGV1_1605071_CLASSES_H

#include <GL/glut.h>
#include <iostream>
#include<cmath>
#include <vector>
#include <algorithm>
#include "bitmap_image.hpp"

using namespace std;

#define pi (2*acos(0.0))
#define AMB 0
#define DIFF 1
#define SPEC 2
#define REC_REFLECTION 3
#define infinite 999999
#define eta 1.5

extern int recursion_level;

double epsilon = 1e-4;

string image_filename = "1605071.bmp";
bitmap_image image(image_filename);
//struct point
//{
//    double x,y,z;
//};

class MyVector
{
public:
    double x,y,z;
    MyVector() {}

    MyVector(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double getValue()
    {
        return sqrt(x*x + y*y + z*z);
    }

    void normalize()
    {
        double val = sqrt(x*x + y*y + z*z);

        x = (x*1.0)/val;
        y = (y*1.0)/val;
        z = (z*1.0)/val;
    }

    double dotProduct_inClass(MyVector vect)
    {
        double res;
        res = x * vect.x + y * vect.y + z * vect.z;
        return res;
    }

    MyVector crossProduct_inClass(MyVector vect) // v1 corss v2 = v1.crossProduct_inClass(v2);
    {
        double vx, vy, vz;
        vx = y * vect.z - z * vect.y;
        vy = z * vect.x - x * vect.z;
        vz = x * vect.y - y * vect.x;

        MyVector res;
        res.x = vx;
        res.y = vy;
        res.z = vz;

        return res;
    }

    MyVector scaler_vectmult_inClass(double val)
    {
        MyVector res;
        res.x = val * x;
        res.y = val * y;
        res.z = val * z;

        return res;
    }

    MyVector vect_add_inClass(MyVector vect)
    {
        double vx, vy, vz;
        vx = x + vect.x;
        vy = y + vect.y;
        vz = z + vect.z;

        MyVector res;
        res.x = vx;
        res.y = vy;
        res.z = vz;

        return res;
    }

    MyVector vect_sub_inClass(MyVector vect) //v1-v2 = v1.vect_sub_inClass(v2);
    {
        double vx, vy, vz;
        vx = x - vect.x;
        vy = y - vect.y;
        vz = z - vect.z;

        MyVector res;
        res.x = vx;
        res.y = vy;
        res.z = vz;

        return res;
    }

    void printVector()
    {
        cout << x << "\t" << y << "\t" << z << endl;
    }
};

class Ray
{
public:
    MyVector start;
    MyVector dir;

    Ray(MyVector s, MyVector d)
    {
        start = s;
        dir = d;
        dir.normalize();
    }

    void printRay()
    {
        dir.printVector();
        cout << endl;
    }
};

class  Light
{
public:
    MyVector light_pos;
    double color[3];

    Light(MyVector pos, double r, double g, double b)
    {
        light_pos = pos;
        color[0] = r, color[1] = g, color[2] = b;
    }

    void draw()
    {
        glPointSize(5.0f);
        glColor3f(color[0], color[1], color[2]);
        glBegin(GL_POINTS);
        glVertex3f(light_pos.x, light_pos.y, light_pos.z);
        glEnd();
    }

//    void printLight()
    void printObject()
    {
        light_pos.printVector();
        cout << color[0] << ", " << color[1] << ", " << color[2] << endl;
        cout << endl;
    }
};

extern vector<Light> light_vect;

//double findMin(double a, double b)
//{
//    return min({a, b});
//}

class Object
{
public:
    int id = -1;
    MyVector reference_point;
    double height, width, length;
    double color[3];
    double coEfficients[4];
    double refraction_coEfficient;
    int shine;

    Object() {}

    virtual void printObject() {}
    virtual void draw() {}
    virtual MyVector getNormal(MyVector intersectionPoint) {}
    void setColor(double r, double g, double b) {
        color[0] = r, color[1] = g, color[2] = b;
    }
    void setCoEfficients(double ambient_coeff, double diffuse_coeff, double specular_coeff, double reflection_coeff) {
        coEfficients[0] = ambient_coeff, coEfficients[1] = diffuse_coeff,
        coEfficients[2] = specular_coeff, coEfficients[3] = reflection_coeff;
    }

    void set_refraction_coeff(double refraction_coeff)
    {
        refraction_coEfficient = refraction_coeff;
    }

    void setShine(int s) {
        shine = s;
    }

    virtual double intersect(Ray *r, double *capture_color, int level)
    {
        cout << "in virtual intersect method" << endl;
        return -1.0;
    }

    void printOthers() {
        cout << color[0] << ", " << color[1] << ", " << color[2] << endl;
        cout << coEfficients[0] << ", " << coEfficients[1] << ", " << coEfficients[2] << ", " << coEfficients[3] << endl;
        cout << refraction_coEfficient << endl;
        cout << shine << endl;
        cout << endl;
    }

//    void print_lwh()
//    {
//
//    }
};

extern vector<Object*> object_vect;

//MyVector getReflectedRay(MyVector L, MyVector N)
//{
//    double L_dot_N = L.dotProduct_inClass(N);
//    double val = 2.0 * L_dot_N;
//    MyVector N_X_val = N.scaler_vectmult_inClass(val);
//    MyVector R = N_X_val.vect_sub_inClass(L);
//
//    return R;
//}

MyVector getReflectedRay(MyVector L, MyVector N)
{
    double L_dot_N = L.dotProduct_inClass(N);
    double val = 2.0 * L_dot_N;
    MyVector N_X_val = N.scaler_vectmult_inClass(val);
    MyVector R = L.vect_sub_inClass(N_X_val);  // as now L is opposite

    return R;
}

MyVector getRefractedRay(MyVector L, MyVector N)
{
    double N_dot_I = L.dotProduct_inClass(N);
    double k = 1.0 - eta * eta * (1.0 - N_dot_I * N_dot_I);

    MyVector R;
    if(k < 0.0)
    {
        R.x = 0.0, R.y = 0.0, R.z = 0.0;
    }
    else
    {
        R.x = eta * L.x - (eta * N_dot_I + sqrt(k)) * N.x;
        R.y = eta * L.y - (eta * N_dot_I + sqrt(k)) * N.y;
        R.z = eta * L.z - (eta * N_dot_I + sqrt(k)) * N.z;
    }
    return R;
}

double getAdd_color(double l_color, double coEfficient, double special_val, double intersectionPointColor)
{
    double add_color = l_color * coEfficient * special_val * intersectionPointColor;
    return add_color;
}

void illumination_with_Phong(MyVector intersectionPoint, MyVector normal, Ray *r, int shine, double* capture_color, double* intersectionPointColor, double* coEfficients)
{
    for(int l=0; l<light_vect.size(); l++)
    {
        // cast rayl from l.light_pos to intersectionPoint
        MyVector ray_l_dir = light_vect[l].light_pos.vect_sub_inClass(intersectionPoint); //not normalized  //ok
        double ray_l_dir_value = ray_l_dir.getValue();
        ray_l_dir.normalize(); // just to be safe

        MyVector dir_X_eps = ray_l_dir.scaler_vectmult_inClass(epsilon);
        MyVector ray_l_start = intersectionPoint.vect_add_inClass(dir_X_eps);
        Ray ray_l(ray_l_start, ray_l_dir);

        // check if ray_l is not obscured by any object
        bool obscured = false; // ray_l is not obscured by any object

        for(int i=0; i<object_vect.size(); i++)
        {
            double dummyColor[3];
            dummyColor[0] = 0.0, dummyColor[1] = 0.0, dummyColor[2] = 0.0;

            double t = object_vect[i]->intersect(&ray_l, dummyColor, 0);

            if(t > 0 && t < ray_l_dir_value) //confusion about t < ray_l_dir_value
//            if(t > 0)
            {
                obscured = true; //ray_l is obscured by an object
                break;
            }
        }

        double lambertValue = 0, phongValue = 0, phongValue_pow_shine = 0;
        if(obscured == false)
        {
            //calculate lambertValue
            lambertValue = ray_l.dir.dotProduct_inClass(normal);
            lambertValue = max(lambertValue, 0.0);
            // find reflected ray ray_r for ray_l
            MyVector ray_r_dir = getReflectedRay(ray_l.dir, normal);
            ray_r_dir.normalize(); // has to be done
            //calculate phongValue
            phongValue = r->dir.dotProduct_inClass(ray_r_dir);
            phongValue_pow_shine = pow(phongValue, shine);
            phongValue_pow_shine = max(phongValue_pow_shine, 0.0);
        }

        capture_color[0] = capture_color[0] + getAdd_color(light_vect[l].color[0], coEfficients[DIFF], lambertValue, intersectionPointColor[0]);
        capture_color[1] = capture_color[1] + getAdd_color(light_vect[l].color[1], coEfficients[DIFF], lambertValue, intersectionPointColor[1]);
        capture_color[2] = capture_color[2] + getAdd_color(light_vect[l].color[2], coEfficients[DIFF], lambertValue, intersectionPointColor[2]);

//        capture_color[0] = capture_color[0] + getAdd_color(light_vect[l].color[0], coEfficients[SPEC], phongValue_pow_shine, 1.0);
//        capture_color[1] = capture_color[1] + getAdd_color(light_vect[l].color[1], coEfficients[SPEC], phongValue_pow_shine, 1.0);
//        capture_color[2] = capture_color[2] + getAdd_color(light_vect[l].color[2], coEfficients[SPEC], phongValue_pow_shine, 1.0);

        capture_color[0] = capture_color[0] + getAdd_color(light_vect[l].color[0], coEfficients[SPEC], phongValue_pow_shine, intersectionPointColor[0]);
        capture_color[1] = capture_color[1] + getAdd_color(light_vect[l].color[1], coEfficients[SPEC], phongValue_pow_shine, intersectionPointColor[1]);
        capture_color[2] = capture_color[2] + getAdd_color(light_vect[l].color[2], coEfficients[SPEC], phongValue_pow_shine, intersectionPointColor[2]);

    }
}

void recursive_reflection(Ray *r, MyVector normal, MyVector intersectionPoint, double* capture_color, double* coEfficients, int level)
{
    // construct reflected ray from intersection point
//    MyVector reflectedRay_dir = getReflectedRay(r->dir, normal);
    MyVector reflectedRay_dir = getReflectedRay(r->dir, normal);
    reflectedRay_dir.normalize(); // has to be done
    MyVector dir_X_eps = reflectedRay_dir.scaler_vectmult_inClass(epsilon);
    MyVector reflectedRay_start = intersectionPoint.vect_add_inClass(dir_X_eps);
    Ray r_reflected(reflectedRay_start, reflectedRay_dir);

    // find tmin from the nearest object
    int nearest = -1;
    double t, tMin = infinite;
    double reflected_color[3];
    reflected_color[0] = 0.0, reflected_color[1] = 0.0, reflected_color[2] = 0.0;

    for(int obj=0; obj<object_vect.size(); obj++)
    {
        double dummyColor[3];
        dummyColor[0] = 0.0, dummyColor[1] = 0.0, dummyColor[2] = 0.0;

        t = object_vect[obj]->intersect(&r_reflected, dummyColor, 0);

        if(t <= 0)
        {
            continue;
        }
        if(t < tMin)
        {
            tMin = t;
            nearest = obj;
        }
    }
    if(nearest != -1)
    {
        tMin = object_vect[nearest]->intersect(&r_reflected, reflected_color, level+1);

        capture_color[0] = capture_color[0] + reflected_color[0] * coEfficients[REC_REFLECTION];
        capture_color[1] = capture_color[1] + reflected_color[1] * coEfficients[REC_REFLECTION];
        capture_color[2] = capture_color[2] + reflected_color[2] * coEfficients[REC_REFLECTION];
    }
}

void refraction(Ray *r, MyVector normal, MyVector intersectionPoint, double* capture_color, double refraction_coEfficient, int level)
{
    MyVector refractedRay_dir = getRefractedRay(r->dir, normal);
    refractedRay_dir.normalize(); // has to be done
    MyVector dir_X_eps = refractedRay_dir.scaler_vectmult_inClass(epsilon);
    MyVector refractedRay_start = intersectionPoint.vect_add_inClass(dir_X_eps);
    Ray r_refracted(refractedRay_start, refractedRay_dir);

    // find tmin from the nearest object
    int nearest = -1;
    double t, tMin = infinite;
    double refracted_color[3];
    refracted_color[0] = 0.0, refracted_color[1] = 0.0, refracted_color[2] = 0.0;

    for(int obj=0; obj<object_vect.size(); obj++)
    {
        double dummyColor[3];
        dummyColor[0] = 0.0, dummyColor[1] = 0.0, dummyColor[2] = 0.0;

        t = object_vect[obj]->intersect(&r_refracted, dummyColor, 0);

        if(t <= 0)
        {
            continue;
        }
        if(t < tMin)
        {
            tMin = t;
            nearest = obj;
        }
    }
    if(nearest != -1)
    {
        tMin = object_vect[nearest]->intersect(&r_refracted, refracted_color, level+1);

        capture_color[0] = capture_color[0] + refracted_color[0] * refraction_coEfficient;
        capture_color[1] = capture_color[1] + refracted_color[1] * refraction_coEfficient;
        capture_color[2] = capture_color[2] + refracted_color[2] * refraction_coEfficient;
    }
}

class Sphere : public Object
{
public:
    Sphere(MyVector center, double radius)
    {
        reference_point = center;
        length = radius;
    }

    void draw() {
        int slices = 100;
        int stacks = 30;
        double radius = length;
        MyVector points[100][100];
        int i,j;
        double h,r;
        //generate points
        for(i=0;i<=stacks;i++)
        {
            h=radius*sin(((double)i/(double)stacks)*(pi/2));
            r=radius*cos(((double)i/(double)stacks)*(pi/2));
            for(j=0;j<=slices;j++)
            {
                points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
                points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
                points[i][j].z=h;
            }
        }
        //draw quads using generated points
        double flag = 1.0;
        glColor3f(color[0], color[1], color[2]);
        for(i=0;i<stacks;i++)
        {
            //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
            for(j=0;j<slices;j++)
            {
                glBegin(GL_QUADS);
                {
                    //upper hemisphere
                    glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
                    glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
                    glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
                    glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                    //lower hemisphere
                    glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
                    glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
                    glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
                    glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
                }
                glEnd();
            }
//            flag = 1 - flag;
        }
    }

    MyVector getNormal(MyVector intersectionPoint)
    {
//        cout << "in sphere getNormal" << endl;

        MyVector normal;
        //code here
        normal = intersectionPoint.vect_sub_inClass(reference_point);
        normal.normalize();
//        normal.printVector();
        return normal;
    }

    double intersect(Ray *r, double *capture_color, int level)
    {
//        cout << "from sphere intersect" << endl;
//        r->start.printVector();
//        r->dir.printVector();

        MyVector rayStart_minus_center = r->start.vect_sub_inClass(reference_point);

        double a = r->dir.dotProduct_inClass(r->dir);
        double b = 2.0 * r->dir.dotProduct_inClass(rayStart_minus_center);
        double c = rayStart_minus_center.dotProduct_inClass(rayStart_minus_center) - length*length;

//        cout << a << "\t" << b << "\t" << c << endl;
        double d_square = b*b - 4*a*c;

//        cout << "d_square: " << d_square << endl;

        if(d_square < 0)
        {
            return -1.0;
        }

        double t_plus, t_minus, t;

        double d = sqrt(d_square);
        t_plus = (-b+d) / (2.0*a);
        t_minus = (-b-d) / (2.0*a);

//        cout << "t_plus: " << t_plus << "\tt_minus: " << t_minus << endl;
        if(t_plus < 0 && t_minus < 0)
        {
            t = -1.0;
        }
        else if(t_minus < 0)
        {
            t = t_plus;
        }
        else
        {
            t = t_minus;
        }
        
        if(level == 0)
        {
            return t;
        }

        double tmin = t;
        MyVector intersectionPoint;
        MyVector dir_X_tmin = r->dir.scaler_vectmult_inClass(tmin);

        intersectionPoint = r->start.vect_add_inClass(dir_X_tmin);

        // getColorAt(intersectionPoint)
        double intersectionPointColor[3];
        intersectionPointColor[0] = color[0], intersectionPointColor[1] = color[1], intersectionPointColor[2] = color[2];

        // color = intersectionPointColor * coEfficient[AMB]
        capture_color[0] = intersectionPointColor[0] * coEfficients[AMB];
        capture_color[1] = intersectionPointColor[1] * coEfficients[AMB];
        capture_color[2] = intersectionPointColor[2] * coEfficients[AMB];

        // works fine ig :(

        MyVector normal = getNormal(intersectionPoint);

        illumination_with_Phong(intersectionPoint, normal, r, shine, capture_color, intersectionPointColor, coEfficients);

        if(level >= recursion_level)
        {
            return tmin;
        }
        recursive_reflection(r, normal, intersectionPoint, capture_color, coEfficients, level);

        refraction(r, normal, intersectionPoint, capture_color, refraction_coEfficient, level);

    }

//    void printSphere()
    void printObject()
    {
        cout << "sphere printing..." << endl;
        reference_point.printVector();
        cout << "radius: " << length << endl;
        cout << endl;
    }
};

double getDeterminant(MyVector row0, MyVector row1, MyVector row2)
{
    double ans;

    ans = row0.x * (row1.y * row2.z - row2.y * row1.z)
          - row0.y * (row1.x * row2.z - row1.z * row2.x)
          + row0.z * (row1.x * row2.y - row1.y * row2.x);

    return ans;
}

class Triangle : public Object
{
public:
    MyVector p1, p2, p3;
   Triangle(MyVector a, MyVector b, MyVector c)
   {
       p1 = a, p2 = b, p3 = c;
   }
//    Triangle(const Sphere &old_obj) : Object(old_obj)
//    {
//        cout << "in triangle class" << endl;
//    }
    void draw() {
       double flag = 1.0;
        glBegin(GL_TRIANGLES);{
            glColor3f(color[0], color[1], color[2]);
            glVertex3f(p1.x, p1.y, p1.z);
            glVertex3f(p2.x, p2.y, p2.z);
            glVertex3f(p3.x, p3.y, p3.z);
        }glEnd();
   }

    MyVector getNormal(MyVector intersectionPoint)
    {
        MyVector normal;
        //code here
//        cout << "in triangle getNormal" << endl;
        MyVector edge_ba = p2.vect_sub_inClass(p1);
        MyVector edge_ca = p3.vect_sub_inClass(p1);
        normal = edge_ba.crossProduct_inClass(edge_ca);

        normal.normalize();
        return normal;
    }

    double intersect(Ray *r, double *capture_color, int level)
    {
//       cout << "in triangle intersect" << endl;
//        creating matrix for A
        MyVector A_row0(p1.x-p2.x, p1.x-p3.x, r->dir.x);
        MyVector A_row1(p1.y-p2.y, p1.y-p3.y, r->dir.y);
        MyVector A_row2(p1.z-p2.z, p1.z-p3.z, r->dir.z);
        double det_A = getDeterminant(A_row0, A_row1, A_row2);

//        cout << det_A << endl;

//        creating matrix for beta
        MyVector beta_row0(p1.x-r->start.x, p1.x-p3.x, r->dir.x);
        MyVector beta_row1(p1.y-r->start.y, p1.y-p3.y, r->dir.y);
        MyVector beta_row2(p1.z-r->start.z, p1.z-p3.z, r->dir.z);
        double det_beta = getDeterminant(beta_row0, beta_row1, beta_row2);

//        creating matrix for gamma
        MyVector gamma_row0(p1.x-p2.x, p1.x-r->start.x, r->dir.x);
        MyVector gamma_row1(p1.y-p2.y, p1.y-r->start.y, r->dir.y);
        MyVector gamma_row2(p1.z-p2.z, p1.z-r->start.z, r->dir.z);
        double det_gamma = getDeterminant(gamma_row0, gamma_row1, gamma_row2);

//        creating matrix for t
        MyVector t_row0(p1.x-p2.x, p1.x-p3.x, p1.x-r->start.x);
        MyVector t_row1(p1.y-p2.y, p1.y-p3.y, p1.y-r->start.y);
        MyVector t_row2(p1.z-p2.z, p1.z-p3.z, p1.z-r->start.z);
        double det_t = getDeterminant(t_row0, t_row1, t_row2);

//        cout << det_beta << endl;

        double beta, gamma, t;

        if(det_A == 0)
        {
            return -1.0;
        }

        beta = det_beta / det_A;
        gamma = det_gamma / det_A;
        t = det_t / det_A;

//        cout << det_A << endl;
//        cout << beta << "\t" << gamma << "\t" << t << endl;

        if(!(beta+gamma < 1 && beta > 0 && gamma > 0 && t > 0))
        {
            return -1.0;
        }

        if(level == 0)
        {
            return t;
        }

        double tmin = t;
        MyVector intersectionPoint;
        MyVector dir_X_tmin = r->dir.scaler_vectmult_inClass(tmin);

        intersectionPoint = r->start.vect_add_inClass(dir_X_tmin);

        // getColorAt(intersectionPoint)
        double intersectionPointColor[3];
        intersectionPointColor[0] = color[0], intersectionPointColor[1] = color[1], intersectionPointColor[2] = color[2];

        // color = intersectionPointColor * coEfficient[AMB]
        capture_color[0] = intersectionPointColor[0] * coEfficients[AMB];
        capture_color[1] = intersectionPointColor[1] * coEfficients[AMB];
        capture_color[2] = intersectionPointColor[2] * coEfficients[AMB];

        MyVector normal = getNormal(intersectionPoint);

        illumination_with_Phong(intersectionPoint, normal, r, shine, capture_color, intersectionPointColor, coEfficients);

        if(level >= recursion_level)
        {
            return tmin;
        }
        recursive_reflection(r, normal, intersectionPoint, capture_color, coEfficients, level);

        refraction(r, normal, intersectionPoint, capture_color, refraction_coEfficient, level);

    }

//    void printTriangle()
    void printObject()
    {
        cout << "triangle printing..." << endl;
        p1.printVector();
        p2.printVector();
        p3.printVector();
        cout << endl;
    }

};

bool inside_range(double val, double max_val, double min_val)
{
    if(val >= min_val && val <= max_val)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool if_inside_cube(double t, Ray *r, MyVector reference_point, double length, double width, double height)
{
//    r->start.printVector();
//    r->dir.printVector();

    MyVector dir_X_t = r->dir.scaler_vectmult_inClass(t);
    MyVector isP = r->start.vect_add_inClass(dir_X_t); //isP => InterSectionPoint

    double min_x, max_x, min_y, max_y, min_z, max_z;
    min_x = reference_point.x, max_x = reference_point.x + length;
    min_y = reference_point.y, max_y = reference_point.y + width;
    min_z = reference_point.z, max_z = reference_point.z + height;

    bool inside_cubeLength = false, inside_cubeWidth = false, inside_cubeHeight = false;
    if(length == 0)
    {
        inside_cubeLength = true;
    }
    else
    {
        inside_cubeLength = inside_range(isP.x, max_x, min_x);
    }

    if(width == 0)
    {
        inside_cubeWidth = true;
    }
    else
    {
        inside_cubeWidth = inside_range(isP.y, max_y, min_y);
    }

    if(height == 0)
    {
        inside_cubeHeight = true;
    }
    else
    {
        inside_cubeHeight = inside_range(isP.z, max_z, min_z);
    }

    bool inside_cube = false;
    if(inside_cubeLength && inside_cubeWidth && inside_cubeHeight)
    {
        inside_cube = true;
    }

    return inside_cube;
}

class General : public Object
{
public:
    double A, B, C, D, E, F, G, H, I, J;
    General(double l1, double l2, double l3, double l4, double l5,
            double l6, double l7, double l8, double l9, double l10,
            MyVector cube_ref_point, double l, double w, double hei)
    {
        A = l1, B = l2, C = l3, D = l4, E = l5,
        F = l6, G = l7, H = l8, I = l9, J = l10;
        reference_point = cube_ref_point;
        length = l, width = w, height = hei;
    }

    void draw() {}

    MyVector getNormal(MyVector intersectionPoint)
    {
        MyVector normal;
        //code here
        double nx, ny, nz;
        nx = intersectionPoint.x, ny = intersectionPoint.y, nz = intersectionPoint.z;

        normal.x = 2*A*nx + D*ny + E*nz + G;
        normal.y = 2*B*ny + D*nx + F*nz + H;
        normal.z = 2*C*nz + E*nx + F*ny + I;

        normal.normalize();
        return normal;
    }

    double intersect(Ray *r, double *capture_color, int level)
    {
//        cout << "in general intersect" << endl;
        double a = A * r->dir.x * r->dir.x + B * r->dir.y * r->dir.y + C * r->dir.z * r->dir.z
                + D * r->dir.x * r->dir.y + E * r->dir.x * r->dir.z + F * r->dir.y * r->dir.z;

        double b = 2 * A * r->start.x * r->dir.x + 2 * B * r->start.y * r->dir.y + 2 * C * r->start.z * r->dir.z
                + D * (r->start.x * r->dir.y + r->start.y * r->dir.x)
                + E * (r->start.x * r->dir.z + r->start.z * r->dir.x)
                + F * (r->start.y * r->dir.z + r->start.z * r->dir.y)
                + G * r->dir.x + H * r->dir.y + I * r->dir.z;

        double c = A * r->start.x * r->start.x + B * r->start.y * r->start.y + C * r->start.z * r->start.z
                + D * r->start.x * r->start.y + E * r->start.x * r->start.z + F * r->start.y * r->start.z
                + G * r->start.x + H * r->start.y + I * r->start.z + J;

        double t_plus, t_minus, t;

        if(a == 0)
        {
            if(b == 0)
            {
                return -1.0;
            }
            t_plus = - c / b;
            t_minus = - c / b;
        }
        else
        {
            double d_square = b*b - 4*a*c;
            if(d_square < 0)
            {
                return -1.0;
            }
            double d = sqrt(d_square);
            t_plus = (-b+d) / (2.0*a);
            t_minus = (-b-d) / (2.0*a);
        }

        if(t_plus < 0 && t_minus < 0)
        {
            return -1.0;
        }

        if(t_plus > 0 && t_minus < 0)
        {
//            cout << "t_plus > 0 && t_minus < 0" << endl;
            bool inside_cube_plus = if_inside_cube(t_plus, r, reference_point, length, width, height);
            if(inside_cube_plus)
            {
                t = t_plus;
            }
            else
            {
                t = -1.0;
            }
        }
        else
        {
//            cout << "t_plus > 0 && t_minus > 0" << endl;
            bool inside_cube_plus = if_inside_cube(t_plus, r, reference_point, length, width, height);
            bool inside_cube_minus = if_inside_cube(t_minus, r, reference_point, length, width, height);

            if(inside_cube_plus && inside_cube_minus)
            {
                t = min(t_plus, t_minus);
            }
            else if(inside_cube_plus)
            {
                t = t_plus;
            }
            else if(inside_cube_minus)
            {
                t = t_minus;
            }
            else
            {
                t = -1.0;
            }
        }

//      cout << t_plus << "\t" << t_minus << endl;

        if(level == 0)
        {
            return t;
        }

        double tmin = t;
        MyVector intersectionPoint;
        MyVector dir_X_tmin = r->dir.scaler_vectmult_inClass(tmin);

        intersectionPoint = r->start.vect_add_inClass(dir_X_tmin);

        // getColorAt(intersectionPoint)
        double intersectionPointColor[3];
        intersectionPointColor[0] = color[0], intersectionPointColor[1] = color[1], intersectionPointColor[2] = color[2];

        // color = intersectionPointColor * coEfficient[AMB]
        capture_color[0] = intersectionPointColor[0] * coEfficients[AMB];
        capture_color[1] = intersectionPointColor[1] * coEfficients[AMB];
        capture_color[2] = intersectionPointColor[2] * coEfficients[AMB];

        MyVector normal = getNormal(intersectionPoint);
        illumination_with_Phong(intersectionPoint, normal, r, shine, capture_color, intersectionPointColor, coEfficients);

        if(level >= recursion_level)
        {
            return tmin;
        }
        recursive_reflection(r, normal, intersectionPoint, capture_color, coEfficients, level);

        refraction(r, normal, intersectionPoint, capture_color, refraction_coEfficient, level);

    }

//    void printGeneral()
    void printObject()
    {
        cout << "general printing..." << endl;
        cout << A << ", " << B << ", " << C << ", " << D << ", " << E << ", "
                << F << ", " << G << ", " << H << ", " << I << ", " << J << endl;
        reference_point.printVector();
        cout << length << ", " << width << ", " << height << endl;
        cout << endl;
    }
};

MyVector getTexture(MyVector reference_point, double length, MyVector intersectionPoint, int i, int j)
{
    int image_w = image.width(), image_h = image.height();

    double cur_tile_bottom_x = reference_point.x + i * length;
    double cur_tile_bottom_y = reference_point.y + j * length;

    double mx = (length * 1.0) / image_w;
    double my = (length * 1.0) / image_h;

    int m = int((intersectionPoint.x - cur_tile_bottom_x) / mx);
    int n = int((intersectionPoint.y - cur_tile_bottom_y) / my);

    unsigned char tr, tg, tb;
    image.get_pixel(m, n, tr, tg, tb);

//    cout << tr << "\t" << tg << "\t" << tb << endl;

    MyVector texture_color;
    texture_color.x = tr, texture_color.y = tg, texture_color.z = tb;

    return texture_color;
}

class Floor : public Object
{
public:
    Floor()
    {

    }

    Floor(double floorWidth, double tileWidth)
    {
        reference_point.x = -floorWidth/2.0, reference_point.y = -floorWidth/2.0;
        length = tileWidth;
    }

//    void setAttributes(double floorWidth, double tileWidth)
//    {
//        reference_point.x = -floorWidth/2.0, reference_point.y = -floorWidth/2.0;
//        length = tileWidth;
//    }

    void draw() {
        int tile_count = abs((reference_point.x * 2) / length);
//        tile_count = 3;
//        cout << tile_count << endl;
        double flag;
        double x, y;
        x = reference_point.x;
        y = reference_point.y;

        for(int i=0; i<tile_count; i++)
        {
            if(i % 2 == 0) flag = 1.0;
            else flag = 0.0;

            for(int j=0; j<tile_count; j++)
            {
                glBegin(GL_QUADS);{
                    glColor3f(flag, flag, flag);
                    glVertex3f(x, y, 0);
                    glVertex3f(x+length, y, 0);
                    glVertex3f(x+length, y+length, 0);
                    glVertex3f(x, y+length, 0);
                }glEnd();
                flag = 1-flag;
                y = y + length;
            }
            x = x + length;
            y = reference_point.y;
        }

    }

    MyVector getNormal(MyVector intersectionPoint) //pass a dummy intersectionPoint
    {
        MyVector normal;
        normal.x = 0, normal.y = 0, normal.z = 1;
        return normal;
    }

    double intersect(Ray *r, double *capture_color, int level)
    {
//        cout << "inside floor intersection " << level << endl;
        MyVector dummyIntersectionPoint(0, 0, 0);
        MyVector normal = getNormal(dummyIntersectionPoint);

        double dir_dot_normal = r->dir.dotProduct_inClass(normal);

        if(dir_dot_normal == 0)
        {
            return -1.0;
        }

        double rayStart_dot_normal = r->start.dotProduct_inClass(normal);

        //cout << rayStart_dot_normal;

        double t = - rayStart_dot_normal / dir_dot_normal;

        if(level == 0)
        {
            return t;
        }

        double tmin = t;
        MyVector intersectionPoint;
        MyVector dir_X_tmin = r->dir.scaler_vectmult_inClass(tmin);

        intersectionPoint = r->start.vect_add_inClass(dir_X_tmin);

        if(!(intersectionPoint.x >= reference_point.x && intersectionPoint.x <= -reference_point.x))
        {
            return -1.0;
        }
        if(!(intersectionPoint.y >= reference_point.y && intersectionPoint.y <= -reference_point.y))
        {
            return -1.0;
        }

        double dx = intersectionPoint.x - reference_point.x;
        double dy = intersectionPoint.y - reference_point.y;

        int i = dx / (length*1.0);
        int j = dy / (length*1.0);

        int tile_count = abs((reference_point.x * 2) / length);

        bool i_inside_range = inside_range(i, tile_count-1, 0);
        bool j_inside_range = inside_range(j, tile_count-1, 0);

        if(!(i_inside_range && j_inside_range))
        {
            return -1.0;
        }

        int tile_color;
        if((i+j) % 2 == 0) tile_color = 1.0;
        else tile_color = 0.0;

        // getColorAt(intersectionPoint)
        double intersectionPointColor[3];
        intersectionPointColor[0] = tile_color, intersectionPointColor[1] = tile_color, intersectionPointColor[2] =tile_color;

        // --------texture-----------
        if(tile_color == 0)
        {
            MyVector texture_color = getTexture(reference_point, length, intersectionPoint, i, j);
            double tr, tg, tb;
            tr = texture_color.x, tg = texture_color.y, tb = texture_color.z;

            intersectionPointColor[0] = double (tr/255.0), intersectionPointColor[1] = double (tg/255.0), intersectionPointColor[2] = double(tb/255.0);
        }
        // -------------------


        // color = intersectionPointColor * coEfficient[AMB]
        capture_color[0] = intersectionPointColor[0] * coEfficients[AMB];
        capture_color[1] = intersectionPointColor[1] * coEfficients[AMB];
        capture_color[2] = intersectionPointColor[2] * coEfficients[AMB];

//        capture_color[0] = intersectionPointColor[0];
//        capture_color[1] = intersectionPointColor[1];
//        capture_color[2] = intersectionPointColor[2];

        // works fine ig :(

        illumination_with_Phong(intersectionPoint, normal, r, shine, capture_color, intersectionPointColor, coEfficients);

        if(level >= recursion_level)
        {
            return tmin;
        }
        recursive_reflection(r, normal, intersectionPoint, capture_color, coEfficients, level);

        refraction(r, normal, intersectionPoint, capture_color, refraction_coEfficient, level);

    }

//    void printFloor()
    void printObject()
    {
        cout << reference_point.x << ", " << length << endl;
        cout << endl;
    }
};

//class Temp
//{
//public:
//    void check_extern()
//    {
//        for(int i=0; i<light_vect.size(); i++)
//        {
//            light_vect[i].printObject();
//        }
//    }
//};