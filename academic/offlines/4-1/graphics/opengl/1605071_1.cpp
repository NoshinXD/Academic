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
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>

#define pi (2*acos(0.0))

#include <iostream>
using namespace std;

#include <vector>

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;
static GLfloat rotation = 0.0;
struct point
{
	double x,y,z;
};

struct point pos, u, r, l, bullet_pos;
struct point target_u, target_r, target_l;

double sphere_radius, sphere_slices, sphere_stacks;
double hemisphere_radius, hemisphere_slices, hemisphere_stacks;
double cylinder_radius, cylinder_slices, cylinder_stacks;
double horn_radius, horn_outerRadius, horn_slices, horn_stacks;
double plane_a, plane_x, plane_m, bullet_size;

double whole_z, hemi_2_x, hemi_1_y, hemi_2_y;

double line_len = 200;
int fire = 0;

point intersect;
point temp;

vector<point> bullets;

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

void drawSquare(double a)
{
    //glColor3f(0.7,0.7,0.7);
	glBegin(GL_QUADS);{
	    //glColor3f(1.0, 0.0, 0.0);
		glVertex3f(plane_a, a, a);
		//glColor3f(0.0, 1.0, 0.0);
		glVertex3f(plane_a,-a, a);
		//glColor3f(0.0, 0.0, 1.0);
		glVertex3f(plane_a,-a, -a);
		//glColor3f(0.0, 1.0, 1.0);
		glVertex3f(plane_a, a, -a);
	}glEnd();
}


/*void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
    glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_LINES);
        {
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}*/

void drawLastPart(double radius, double outer_radius, int slices,int stacks)
{
    struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=outer_radius - radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].z=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].x=h;
		}
	}
	//draw quads using generated points

	for(i=0;i<stacks;i++)
	{
        //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
        double flag = 1.0;
		for(j=0;j<slices;j++)
		{
		    //flag = (i ^ j) & 1;
		    glColor3f(flag, flag, flag);
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                /*glVertex3f(-points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(-points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(-points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(-points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);*/
			}glEnd();
			flag = 1 - flag;
		}
		//flag = 1 - flag;
	}
}

void drawSphere(double radius,int slices,int stacks) //stack->circle; slice->segment of circle
{
	struct point points[100][100];
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
	double flag = 0.0;
	for(i=0;i<stacks;i++)
	{
        //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
			    glColor3f(flag, flag, flag);
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                glColor3f(1-flag, 1-flag, 1-flag);
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
		flag = 1 - flag;
	}
}

void drawMyHalfSphere(double radius, int slices, int stacks, int hemi)
{
    struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].z=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].x=h;
		}
	}
	//draw quads using generated points

	for(i=0;i<stacks;i++)
	{
        //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
        double flag = 1.0;
		for(j=0;j<slices;j++)
		{
		    //flag = (i ^ j) & 1;
		    glColor3f(flag, flag, flag);
		    //glColor3f(flag, 0, 0);
			glBegin(GL_QUADS);{
			    if(hemi == 2)
			    {
			        //upper hemisphere
                    glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
                    glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
                    glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
                    glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
			    }
			    else
			    {
			        //lower hemisphere
                    glVertex3f(-points[i][j].x,points[i][j].y,points[i][j].z);
                    glVertex3f(-points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
                    glVertex3f(-points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
                    glVertex3f(-points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
			    }
			}glEnd();
			flag = 1 - flag;
		}
		//flag = 1 - flag;
	}
}

void drawMyCylinder(double radius, int slices, int stacks) //here stacks->height of cylinder
{
    struct point points[100][100];
	int i,j;
	//double h,r;
	double h = stacks;
	double r = radius;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		for(j=0;j<=slices;j++)
		{
			points[i][j].z=r*cos(((double)j/(double)slices)*(2*pi)); //points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*(2*pi));
			points[i][j].x=i; //i+h
		}
	}
	//draw quads using generated points

	for(i=0;i<stacks;i++)
	{
        //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
        double flag = 1.0;
		for(j=0;j<slices;j++)
		{
		    //flag = (i ^ j) & 1;
		    glColor3f(flag, flag, flag);
		    //glColor3f(0, 0, flag);
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                /*glVertex3f(-points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(-points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(-points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(-points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);*/
			}glEnd();
			flag = 1 - flag;
		}
		//flag = 1 - flag;
	}
}

void drawMyLine(point &p1, point &p2)
{
    //glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    {
        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p2.x, p2.y, p2.z);
    }
    glEnd();
}

void getSolutionPoint(point &p, point &q)
{
    //point intersect;

    double t = (1.0*(plane_x - p.x)) / (q.x - p.x);

    intersect.x = p.x + 1.0 * t * (q.x - p.x);
    intersect.y = p.y + 1.0 * t * (q.y - p.y);
    intersect.z = p.z + 1.0 * t * (q.z - p.z);

    //return intersect;
}

void drawTargetLine()
{
    glPushMatrix();
    {
        double factor = 300.0;

        glColor3f(0.0,1.0,0.0);

        point line_p1, line_p2;
        double val = (target_l.x*target_l.x) + (target_l.y*target_l.y) + (target_l.z*target_l.z);
        val = sqrt(val);

        line_p1.x = (target_l.x*1.0) / val;
        line_p1.y = (target_l.y*1.0) / val;
        line_p1.z = (target_l.z*1.0) / val;

        line_p2.x = factor * line_p1.x;
        line_p2.y = factor * line_p1.y;
        line_p2.z = factor * line_p1.z;

        //drawMyLine(line_p1, line_p2);

        getSolutionPoint(line_p1, line_p2);
        //cout << line_p1.x << " " << line_p2.y << " " << line_p2.z << endl;
        //cout << intersect.x << " " << intersect.y << endl;
    }
    glPopMatrix();
}

void myDrawSS()
{
    //edit here
    glPushMatrix();
    {
        glRotatef(whole_z, 0, 0, 1); //works : q,w
        drawMyHalfSphere(sphere_radius, sphere_slices, sphere_stacks, 1);
        glRotatef(hemi_1_y, 0, 1, 0); //works : e,r
        drawMyHalfSphere(sphere_radius, sphere_slices, sphere_stacks, 2);

        glTranslatef(sphere_radius,0,0);
        glRotatef(hemi_2_y, 0, 1, 0); //works : a,s
        glRotatef(hemi_2_x, 1, 0, 0); //works : d,f
        glTranslatef(hemisphere_radius,0,0);
        drawMyHalfSphere(hemisphere_radius, hemisphere_slices, hemisphere_stacks, 1);

        glTranslatef(0,0,0);
        drawMyCylinder(cylinder_radius, cylinder_slices, cylinder_stacks);

        glTranslatef(cylinder_stacks,0,0);
        drawLastPart(horn_radius, horn_outerRadius, horn_slices, horn_stacks);
    }
    glPopMatrix();
}

void drawTargetPlane()
{
    glPushMatrix();
    {
        glTranslatef(plane_x, 0, 0);
        glColor3f(0.7,0.7,0.7);
        drawSquare(plane_m);
    }
    glPopMatrix();
}

//point temp;

void drawBullet()
{
    glColor3f(1.0,0.0,0.0);
    //drawSquare(50);

    for(int i=0; i<bullets.size(); i++)
    {
        glPushMatrix();
        {
            if((bullets[i].y > -(plane_m-bullet_size) && bullets[i].y < (plane_m-bullet_size)) && (bullets[i].z > -(plane_m-bullet_size) && bullets[i].z < (plane_m-bullet_size)))
            {
                glTranslatef(bullets[i].x - plane_a, bullets[i].y, bullets[i].z);
                //glTranslatef(plane_x, bullets[i].y, bullets[i].z);
                glColor3f(1.0,0.0,0.0);
                drawSquare(bullet_size);
            }
        }
        glPopMatrix();
    }
}

void crossProduct(point &point1, point &point2, point &resultant)
{
    resultant.x = point1.y * point2.z - point1.z * point2.y;
    resultant.y = point1.z * point2.x - point1.x * point2.z;
    resultant.z = point1.x * point2.y - point1.y * point2.x;
}

void vector_rotation(point &p, point &res, double this_angle)
{
    double rad_angle = (pi/180) * this_angle;

    p.x = p.x * cos(rad_angle) + res.x * sin(rad_angle);
    p.y = p.y * cos(rad_angle) + res.y * sin(rad_angle);
    p.z = p.z * cos(rad_angle) + res.z * sin(rad_angle);
}

void keyboardListener(unsigned char key, int x,int y){
    //cout << "key " << key << endl;
    double this_angle = 3.0;
    point res1, res2;
    double limit = 40, inc_factor = 5;
    double deg_angle;

	switch(key){
		case '1':
            //point res1;
            crossProduct(u, l, res1);
            vector_rotation(l, res1, this_angle);

            //point res2;
            crossProduct(u, r, res2);
            vector_rotation(r, res2, this_angle);

			break;

        case '2':
            //point res1;
            crossProduct(l, u, res1);
            vector_rotation(l, res1, this_angle);

            //point res2;
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

        case 'q':
            //cout << "here in q" << endl;

            if(whole_z > -limit)
            {
                whole_z = whole_z - inc_factor;

                crossProduct(target_u, target_l, res1);
                vector_rotation(target_l, res1, inc_factor);

                //point res2;
                crossProduct(target_u, target_r, res2);
                vector_rotation(target_r, res2, inc_factor);
            }

            break;

        case 'w':

            if(whole_z < limit)
            {
                whole_z = whole_z + inc_factor;
                //pos.z = pos.z + inc_factor;
                crossProduct(target_l, target_u, res1);
                vector_rotation(target_l, res1, inc_factor);

                //point res2;
                crossProduct(target_r, target_u, res2);
                vector_rotation(target_r, res2, inc_factor);
            }

            break;

        case 'e':
            //cout << "here in e" << endl;

            if(hemi_1_y < limit)
            {
                hemi_1_y = hemi_1_y + inc_factor;

                //deg_angle = (180/pi) * hemi_1_y;
                deg_angle = hemi_1_y;

                crossProduct(target_l, target_r, res1);
                vector_rotation(target_l, res1, inc_factor);

                crossProduct(target_u, target_r, res2);
                vector_rotation(target_u, res2, inc_factor);
            }

            break;

        case 'r':
            if(hemi_1_y > -limit)
            {
                hemi_1_y = hemi_1_y - inc_factor;

                //deg_angle= (180/pi) * hemi_1_y;
                deg_angle = hemi_1_y;

                crossProduct(target_r, target_l, res1);
                vector_rotation(target_l, res1, inc_factor);

                crossProduct(target_r, target_u, res2);
                vector_rotation(target_u, res2, inc_factor);
            }

            break;

        case 'a':
            //cout << "here in a" << endl;

            if(hemi_2_y < limit)
            {
                hemi_2_y = hemi_2_y + inc_factor;

                crossProduct(target_l, target_r, res1);
                vector_rotation(target_l, res1, inc_factor);

                crossProduct(target_u, target_r, res2);
                vector_rotation(target_u, res2, inc_factor);
            }

            break;

        case 's':

            // cout << "here in s" << endl;

            if(hemi_2_y > -limit)
            {
                hemi_2_y = hemi_2_y - inc_factor;

                crossProduct(target_r, target_l, res1);
                vector_rotation(target_l, res1, inc_factor);

                crossProduct(target_r, target_u, res2);
                vector_rotation(target_u, res2, inc_factor);
                //cout
            }

            break;

        case 'd':
            if(hemi_2_x < limit)
            {
                hemi_2_x = hemi_2_x + inc_factor;
            }

            break;

        case 'f':
            if(hemi_2_x > -limit)
            {
                hemi_2_x = hemi_2_x - inc_factor;
            }

            break;

		default:
			break;
	}
}

void inc_pos(point &position, point &vect, double f)
{
    position.x = position.x + f * vect.x;
    position.y = position.y + f * vect.y;
    position.z = position.z + f * vect.z;
}

void dec_pos(point &position, point &vect, double f)
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
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){	// 2 times?? in ONE click? -- solution is checking DOWN or UP
				//drawaxes=1-drawaxes;
				fire = 1;
				//if(bullet_count < 10)
                point newB;
                newB.x = intersect.x;
                newB.y = intersect.y;
                newB.z = intersect.z;

                bullets.push_back(newB);
				/*temp.x = intersect.x;
                temp.y = intersect.y;
                temp.z = intersect.z;*/
			}
			else
			{
			    //fire = 0;
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

    //glColor3f(1,0,0);
    //drawSquare(10);

    //drawSS();
    myDrawSS();
    drawTargetLine();
    drawTargetPlane();
    drawBullet();
    //drawCone(20,50,24);

	//drawSphere(30,24,20);




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	//angle+=0.05;
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;

	plane_a = 2;
	plane_x = 200;
	plane_m = 120;
	bullet_size = 3;

	whole_z = 0;
	hemi_2_x = 0;
	hemi_1_y = 0;
	hemi_2_y = 0;

    pos.x = 100;
	pos.y = 100;
	pos.z = 0;

	u.x = 0;
	u.y = 0;
	u.z = -1;

	r.x = -(1/sqrt(2));
	r.y = 1/sqrt(2);
	r.z = 0;

	l.x = -(1/sqrt(2));
	l.y = -(1/sqrt(2));
	l.z = 0;

    //y-axis
	target_u.x = 0;
	target_u.y = 0;
	target_u.z = -1;

    //z-axis
	target_r.x = 0;
	target_r.y = -1;
	target_r.z = 0;

    //x-axis
	target_l.x = 1;
	target_l.y = 0;
	target_l.z = 0;

	bullet_pos.x = 0;
	bullet_pos.y = 0;
	bullet_pos.z = 0;

	sphere_radius = 30;
    sphere_slices = 100;
    sphere_stacks = 30;

    hemisphere_radius = 10;
    hemisphere_slices = 50;
    hemisphere_stacks = 30;

    cylinder_radius = 10; //cylinder_radius = hemisphere_radius
    cylinder_slices = 50;
    cylinder_stacks = 70;

    horn_radius = 10; //horn_outerRadius - horn_radius = cylinder_radius
    horn_outerRadius = 20;
    horn_slices = 50;
    horn_stacks = 10;

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
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("Gun");

	init();
	cout << "used flag for hemi" << endl;

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
