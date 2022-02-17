//trying to shoot

/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include <GL/glut.h>
#include "1605071_classes.h"
#include "bitmap_image.hpp"

#include <stdlib.h>
#include <math.h>

#define pi (2*acos(0.0))
#define infinite 999999

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream inFile;
string scene_filename = "scene.txt";
string bmp_filename = "out.bmp";

int recursion_level, pixel;
int object_count, light_src_count;

vector<Object*> object_vect;
vector<Light> light_vect;
Floor floor1;

MyVector topleft;
double du, dv;

int windowHeight = 500, windowWidth = 500;
int imageWidth, imageHeight;
double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;
static GLfloat rotation = 0.0;

struct MyVector pos, u, r, l, bullet_pos;
struct MyVector target_u, target_r, target_l;
double fovY = 80;

bitmap_image myImage;

double plane_a, plane_x, plane_m, bullet_size;

double whole_z, hemi_2_x, hemi_1_y, hemi_2_y;

void drawAxes()
{
    if(drawaxes==1)
    {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);{
            glVertex3f( 100,0,0);
            glVertex3f(-100,0,0);

            glVertex3f(0,-100,0);
            glVertex3f(0, 100,0);

            glVertex3f(0,0, 100);
            glVertex3f(0,0,-100);
        }glEnd();
    }
}


void drawGrid()
{
    int i;
    if(drawgrid==1)
    {
        glColor3f(0.6, 0.6, 0.6);	//grey
        glBegin(GL_LINES);{
            for(i=-8;i<=8;i++){

                if(i==0)
                    continue;	//SKIP the MAIN axes

                //lines parallel to Y-axis
                glVertex3f(i*10, -90, 0);
                glVertex3f(i*10,  90, 0);

                //lines parallel to X-axis
                glVertex3f(-90, i*10, 0);
                glVertex3f( 90, i*10, 0);
            }
        }glEnd();
    }
}

void myDrawSS()
{
    //edit here
    for(int i=0; i<object_count; i++)
    {
        glPushMatrix();
        {
            glTranslatef(object_vect[i]->reference_point.x, object_vect[i]->reference_point.y,object_vect[i]->reference_point.z);
            object_vect[i]->draw();
        }
        glPopMatrix();
    }

    glPushMatrix();
    {
        object_vect[object_count]->draw();
    }
    glPopMatrix();

    for(int i=0; i<light_vect.size(); i++)
    {
//        glPointSize(5.0f);
//        glColor3f(light_vect[i].color[0], light_vect[i].color[1], light_vect[i].color[2]);
//        glBegin(GL_POINTS);
//        glVertex3f(light_vect[i].light_pos.x, light_vect[i].light_pos.y, light_vect[i].light_pos.z);
//        glEnd();
        light_vect[i].draw();
    }
}

void create_frame_buffer_2()
{
    myImage.setwidth_height(imageWidth, imageHeight);

    for(int i=0; i<imageWidth; i++)
    {
        for(int j=0; j<imageHeight; j++)
        {
            double f_r = 0.0;
            double f_g = 0.0;
            double f_b = 0.0;
            myImage.set_pixel(i, j, f_r, f_g, f_b);
//            cout << i << "\t" << j << endl;
        }
    }

//    myImage.save_image("out.bmp");
    myImage.save_image(bmp_filename);
    // cout << "after initializing and saving...1" << endl;
}

MyVector scaler_vectmult(double val, MyVector vect)
{
    MyVector res;
    res.x = val * vect.x;
    res.y = val * vect.y;
    res.z = val * vect.z;

    return res;
}

MyVector vect_add(MyVector v1, MyVector v2)
{
    double vx, vy, vz;
    vx = v1.x + v2.x;
    vy = v1.y + v2.y;
    vz = v1.z + v2.z;

    MyVector res;
    res.x = vx;
    res.y = vy;
    res.z = vz;

    return res;
}

MyVector vect_sub(MyVector v1, MyVector v2) //v1-v2
{
    double vx, vy, vz;
    vx = v1.x - v2.x;
    vy = v1.y - v2.y;
    vz = v1.z - v2.z;

    MyVector res;
    res.x = vx;
    res.y = vy;
    res.z = vz;

    return res;
}

void clip_color(double *capture_color)
{
    if(capture_color[0] < 0) capture_color[0] = 0;
    if(capture_color[0] > 1) capture_color[0] = 1;

    if(capture_color[1] < 0) capture_color[1] = 0;
    if(capture_color[1] > 1) capture_color[1] = 1;

    if(capture_color[2] < 0) capture_color[2] = 0;
    if(capture_color[2] > 1) capture_color[2] = 1;
}

void capture()
{
    cout << "capture started..." << endl;
    create_frame_buffer_2();
//    double viewAngle = cameraAngle;
    double viewAngle = fovY;
//    cout << fovY << endl;
    double rad_angle = (pi/180) * viewAngle;
    double placeDistance = (windowHeight/2.0) / tan(rad_angle/2.0);

    MyVector eye = pos;

    topleft.x = eye.x + l.x*placeDistance - r.x*windowWidth/2.0 + u.x*windowHeight/2.0;
    topleft.y = eye.y + l.y*placeDistance - r.y*windowWidth/2.0 + u.y*windowHeight/2.0;
    topleft.z = eye.z + l.z*placeDistance - r.z*windowWidth/2.0 + u.z*windowHeight/2.0;

//    topleft.printVector();

    du = (windowWidth*1.0) / imageWidth;
    dv = (windowHeight*1.0) / imageHeight;
//    cout << du << "\t" << dv << endl;

    // choose middle of the grid cell
    topleft.x = topleft.x + r.x * (0.5*du) - u.x * (0.5*dv);
    topleft.y = topleft.y + r.y * (0.5*du) - u.y * (0.5*dv);
    topleft.z = topleft.z + r.z * (0.5*du) - u.z * (0.5*dv);
//    topleft.printVector();

//    cout << object_vect.size() << endl;
    for(int i=0; i<imageWidth; i++)
    {
        for(int j=0; j<imageHeight; j++)
        {
            int nearest = -1;
            double t, tMin = infinite;

            // calculate curPixel
            MyVector curPixel;
            curPixel.x = topleft.x + r.x * (i*du) - u.x * (j*dv);
            curPixel.y = topleft.y + r.y * (i*du) - u.y * (j*dv);
            curPixel.z = topleft.z + r.z * (i*du) - u.z * (j*dv);

            //cast ray  from eye to (curPixel-eye) direction
            MyVector dir = vect_sub(curPixel, eye);
            Ray ray(eye, dir);

            double capture_color[3];
            capture_color[0] = 0.0, capture_color[1] = 0.0, capture_color[2] = 0.0;

            for(int obj=0; obj<object_vect.size(); obj++)
            {
                double dummyColor[3];
                dummyColor[0] = 0.0, dummyColor[1] = 0.0, dummyColor[2] = 0.0;

                t = object_vect[obj]->intersect(&ray, dummyColor, 0);
//                if(obj == 8)
//                {
//                    cout << t << endl;
//                }

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
                tMin = object_vect[nearest]->intersect(&ray, capture_color, 1);

                //clipping color
                clip_color(capture_color);
            }

            double f_r, f_g, f_b;
            f_r = capture_color[0]*255.0, f_g = capture_color[1]*255.0, f_b = capture_color[2]*255.0;

            myImage.set_pixel(i, j, f_r, f_g, f_b);
        }
    }
    myImage.save_image(bmp_filename);
    cout << "bmp saved" << endl;
}

void crossProduct(MyVector &MyVector1, MyVector &MyVector2, MyVector &resultant)
{
    resultant.x = MyVector1.y * MyVector2.z - MyVector1.z * MyVector2.y;
    resultant.y = MyVector1.z * MyVector2.x - MyVector1.x * MyVector2.z;
    resultant.z = MyVector1.x * MyVector2.y - MyVector1.y * MyVector2.x;
}

void vector_rotation(MyVector &p, MyVector &res, double this_angle)
{
    double rad_angle = (pi/180) * this_angle;

    p.x = p.x * cos(rad_angle) + res.x * sin(rad_angle);
    p.y = p.y * cos(rad_angle) + res.y * sin(rad_angle);
    p.z = p.z * cos(rad_angle) + res.z * sin(rad_angle);
}

void keyboardListener(unsigned char key, int x,int y){
    //cout << "key " << key << endl;
    double this_angle = 3.0;
    MyVector res1, res2;
    double limit = 40, inc_factor = 5;
    double deg_angle;

    switch(key){
        case '1':
            //MyVector res1;
            crossProduct(u, l, res1);
            vector_rotation(l, res1, this_angle);

            //MyVector res2;
            crossProduct(u, r, res2);
            vector_rotation(r, res2, this_angle);

            break;

        case '2':
            //MyVector res1;
            crossProduct(l, u, res1);
            vector_rotation(l, res1, this_angle);

            //MyVector res2;
            crossProduct(r, u, res2);
            vector_rotation(r, res2, this_angle);

            break;

        case '3':
            crossProduct(l, r, res1);
            vector_rotation(l, res1, this_angle);

            crossProduct(u, r, res2);
            vector_rotation(u, res2, this_angle);

            break;

        case '4':
            crossProduct(r, l, res1);
            vector_rotation(l, res1, this_angle);

            crossProduct(r, u, res2);
            vector_rotation(u, res2, this_angle);

            break;

        case '5':
            crossProduct(r, l, res1);
            vector_rotation(r, res1, this_angle);

            crossProduct(u, l, res2);
            vector_rotation(u, res2, this_angle);

            break;

        case '6':
            crossProduct(l, r, res1);
            vector_rotation(r, res1, this_angle);

            crossProduct(l, u, res2);
            vector_rotation(u, res2, this_angle);

            break;
        case '0':
            capture();

            break;

        default:
            break;
    }
    glutPostRedisplay();
}

void inc_pos(MyVector &position, MyVector &vect, double f)
{
    position.x = position.x + f * vect.x;
    position.y = position.y + f * vect.y;
    position.z = position.z + f * vect.z;
}

void dec_pos(MyVector &position, MyVector &vect, double f)
{
    position.x = position.x - f * vect.x;
    position.y = position.y - f * vect.y;
    position.z = position.z - f * vect.z;
}


void specialKeyListener(int key, int x,int y){
    //cout << "special key " << key << endl;
    double factor = 2.0;
    switch(key){
        case GLUT_KEY_DOWN:		//down arrow key
            //code here
            dec_pos(pos, l, factor);
            //cameraHeight -= 3.0;
            break;
        case GLUT_KEY_UP:		// up arrow key
            //code here
            inc_pos(pos, l, factor);
            //cameraHeight += 3.0;
            break;

        case GLUT_KEY_RIGHT:
            //code here
            //cout << "hello" << endl;
            //cout << "r.x = " << r.x << endl;
            dec_pos(pos, r, factor);
            //cameraAngle += 0.03;
            break;
        case GLUT_KEY_LEFT:
            //code here
            inc_pos(pos, r, factor);
            //cameraAngle -= 0.03;
            break;

        case GLUT_KEY_PAGE_UP:
            //code here
            inc_pos(pos, u, factor);
            break;
        case GLUT_KEY_PAGE_DOWN:
            //code here
            dec_pos(pos, u, factor);
            break;

        case GLUT_KEY_INSERT:
            break;

        case GLUT_KEY_HOME:
            break;
        case GLUT_KEY_END:
            break;

        default:
            break;
    }
    glutPostRedisplay();
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
    switch(button){
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN){	// 2 times?? in ONE click? -- solution is checking DOWN or UP
                drawaxes=1-drawaxes;

            }
            else
            {

            }
            break;

        case GLUT_RIGHT_BUTTON:
            //........
            if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
                drawaxes=1-drawaxes;
            }
            break;

        case GLUT_MIDDLE_BUTTON:
            //........
            break;

        default:
            break;
    }
    glutPostRedisplay();
}

void display(){

    //clear the display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);	//color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /********************
    / set-up camera here
    ********************/
    //load the correct matrix -- MODEL-VIEW matrix
    glMatrixMode(GL_MODELVIEW);

    //initialize the matrix
    glLoadIdentity();

    //now give three info
    //1. where is the camera (viewer)?
    //2. where is the camera looking?
    //3. Which direction is the camera's UP direction?

    //gluLookAt(100,100,100,	0,0,0,	0,0,1);
    //gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
    //gluLookAt(0,0,200,	0,0,0,	0,1,0);
    gluLookAt(pos.x, pos.y, pos.z,   pos.x+l.x, pos.y+l.y, pos.z+l.z,   u.x, u.y, u.z);


    //again select MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);


    /****************************
    / Add your objects from here
    ****************************/
    //add objects

    drawAxes();
    drawGrid();

    myDrawSS();

    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}


void animate(){
    //angle+=0.05;
    //codes for any changes in Models, Camera
//    glutPostRedisplay();
}

void init(){
    //codes for initialization
    drawgrid=0;
    drawaxes=1;
    cameraHeight=150.0;
    cameraAngle=1.0;
    angle=0;

//    plane_a = 2;
//    plane_x = 200;
//    plane_m = 120;
//    bullet_size = 3;

//    whole_z = 0;
//    hemi_2_x = 0;
//    hemi_1_y = 0;
//    hemi_2_y = 0;

    pos.x = 100;
    pos.y = 100;
    pos.z = 0;

    u.x = 0;
    u.y = 0;
    u.z = 1; // u.z = -1;

    r.x = -(1/sqrt(2));
    r.y = 1/sqrt(2);
    r.z = 0;

    l.x = -(1/sqrt(2));
    l.y = -(1/sqrt(2));
    l.z = 0;

    //clear the screen
    glClearColor(0,0,0,0);

    /************************
    / set-up projection here
    ************************/
    //load the PROJECTION matrix
    glMatrixMode(GL_PROJECTION);

    //initialize the matrix
    glLoadIdentity();
    //glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    //give PERSPECTIVE parameters
//    gluPerspective(80,	1,	1,	1000.0); //from offline 1
    gluPerspective(fovY, 1,	1,	1000.0);
    //field of view in the Y (vertically)
    //aspect ratio that determines the field of view in the X direction (horizontally)
    //near distance
    //far distance
}

void print_light_vect()
{
    for(int i=0; i<light_vect.size(); i++)
    {
        light_vect[i].printObject();
    }
}

void loadData()
{
    // cout << "begin..." << endl;
    inFile.open(scene_filename);
    if(!inFile) { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }

    // writing codes here
    inFile >> recursion_level;
    inFile >> pixel;
    imageWidth = pixel, imageHeight = pixel;
    inFile >> object_count;

    for(int i=0; i<object_count; i++)
    {
        string object;
        inFile >> object;

        if(object.compare("sphere") == 0)
        {
            MyVector center;
            inFile >> center.x >> center.y >> center.z;
            double radius;
            inFile >> radius;

            Object *temp;
            temp = new Sphere(center, radius);

            double r, g, b;
            inFile >> r >> g >> b;
            temp->setColor(r, g, b);
            double ambient_coeff, diffuse_coeff, specular_coeff, reflection_coeff;
            inFile >> ambient_coeff >> diffuse_coeff >> specular_coeff >> reflection_coeff;
            temp->setCoEfficients(ambient_coeff, diffuse_coeff, specular_coeff, reflection_coeff);
            double refraction_coeff = reflection_coeff /  2.0;
            temp->set_refraction_coeff(refraction_coeff);
            double s;
            inFile >> s;
            temp->setShine(s);

            object_vect.push_back(temp);
        }
        else if(object.compare("triangle") == 0)
        {
            MyVector p1, p2, p3;
            inFile >> p1.x >> p1.y >> p1.z;
            inFile >> p2.x >> p2.y >> p2.z;
            inFile >> p3.x >> p3.y >> p3.z;

            Object *temp;
            temp = new Triangle(p1, p2, p3);

            double r, g, b;
            inFile >> r >> g >> b;
            temp->setColor(r, g, b);
            double ambient_coeff, diffuse_coeff, specular_coeff, reflection_coeff;
            inFile >> ambient_coeff >> diffuse_coeff >> specular_coeff >> reflection_coeff;
            temp->setCoEfficients(ambient_coeff, diffuse_coeff, specular_coeff, reflection_coeff);
            double refraction_coeff = reflection_coeff /  2.0;
            temp->set_refraction_coeff(refraction_coeff);
            double s;
            inFile >> s;
            temp->setShine(s);

            object_vect.push_back(temp);
        }
        else if(object.compare("general") == 0)
        {
            double a, b, c, d, e, f, g, h, i, j;
            inFile >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j;
            MyVector cube_ref_MyVector;
            double length, width, height;
            inFile >> cube_ref_MyVector.x >> cube_ref_MyVector.y >> cube_ref_MyVector.z >> length >> width >> height;

            Object *temp;
            temp = new General(a, b, c, d, e, f, g, h, i, j, cube_ref_MyVector, length, width, height);

            double r, g2, b2;
            inFile >> r >> g2 >> b2;
            temp->setColor(r, g2, b2);
            double ambient_coeff, diffuse_coeff, specular_coeff, reflection_coeff;
            inFile >> ambient_coeff >> diffuse_coeff >> specular_coeff >> reflection_coeff;
            temp->setCoEfficients(ambient_coeff, diffuse_coeff, specular_coeff, reflection_coeff);
            double refraction_coeff = reflection_coeff /  2.0;
            temp->set_refraction_coeff(refraction_coeff);
            double s;
            inFile >> s;
            temp->setShine(s);

            object_vect.push_back(temp);
        }
    }

    inFile >> light_src_count;

    for(int i=0; i<light_src_count; i++)
    {
        MyVector light_pos;
        double r, g, b;
        inFile >> light_pos.x >> light_pos.y >> light_pos.z;
        inFile >> r >> g >> b;
        Light light(light_pos, r, g, b);

        light_vect.push_back(light);
    }

//    print_light_vect();
    double floorWidth = 1000, tileWidth = 20;
    Object *temp;
    temp = new Floor(floorWidth, tileWidth);
    double floor_ambient_coeff = 0.4, floor_diffuse_coeff = 0.2, floor_specular_coeff = 0.3, floor_reflection_coeff = 0.3;
    temp->setCoEfficients(floor_ambient_coeff, floor_diffuse_coeff, floor_specular_coeff, floor_reflection_coeff);
    double floor_refraction_coeff = floor_reflection_coeff /  2.0;
    temp->set_refraction_coeff(floor_refraction_coeff);
    int shine = 5;
    temp->setShine(shine);
    object_vect.push_back(temp);

    inFile.close();

//    ---------------------checking------------------------

//------------------------------------------------
}

void unLoadData()
{
    for(int i=0; i<object_count; i++)
    {
        delete object_vect[i];
    }
}

int main(int argc, char **argv){
    loadData();

    atexit(unLoadData);

    glutInit(&argc,argv);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

    glutCreateWindow("Ray_Tracing");

    init();
//    cout << "used flag for hemi" << endl;

    glEnable(GL_DEPTH_TEST);	//enable Depth Testing
//    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);

    glutDisplayFunc(display);	//display callback function
    glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);

    glutMainLoop();		//The main loop of OpenGL

    return 0;
}