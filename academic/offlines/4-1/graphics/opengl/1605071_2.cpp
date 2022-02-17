//inside bubble_maybe etai final
//trying to update position after updating all speed
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
#include<time.h>

#include <ctime>

#include <iostream>
using namespace std;

#define pi (2*acos(0.0))
#define bubble_count 5

clock_t start, current, current1, current2;

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;

struct point
{
	double x,y,z;
};

struct bubble
{
    point speed;
    point store_speed;
    point pos;
    point init_pos;
    int bubble_upperSquare_clash_flag;
    int bubble_sideSquare_clash_flag;
    int if_inside_circle;
    clock_t generation_time;
    int conflict_with_bubble;
};

point circle_pos;
//point v;
double a;
double big_rad;
double small_rad;
bubble bubbles[5];
//int count;

double speed_upper_limit, speed_lower_limit;

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

void drawMySqaure(double a)
{
    glColor3f(0.0,1.0,0.0);
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);{
		glVertex3f( a, a,0);
		glVertex3f( a,-a,0);
	}glEnd();
	//glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);{
		glVertex3f( a,-a,0);
		glVertex3f(-a,-a,0);
	}glEnd();
	//glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINES);{
		glVertex3f(-a,-a,0);
		glVertex3f(-a, a,0);
	}glEnd();
	//glColor3f(1.0,0.0,1.0);
	glBegin(GL_LINES);{
		glVertex3f( a, a,0);
		glVertex3f(-a, a,0);
	}glEnd();
}

void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
    //glColor3f(0.7,0.7,0.7);
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
}

void myDrawSS()
{
    glColor3f(0.0,1.0,0.0);
    drawMySqaure(a);

    glColor3f(1.0,0.0,0.0);
    drawCircle(big_rad, 50);

    for(int i=0; i<bubble_count; i++)
    {
        glPushMatrix();
        {
            current = clock();
            //glTranslatef(bubbles[i].pos.x,bubbles[i].pos.y,0);
            //glColor3f(0.8,0.0,0.5);
            if(current >= bubbles[i].generation_time)
            {
                glTranslatef(bubbles[i].pos.x,bubbles[i].pos.y,0);
                glColor3f(0.9,0.6,0.5);
                drawCircle(small_rad, 30);
            }
        }
        glPopMatrix();
    }
}

void pause_speed(int i)
{
    if(bubbles[i].speed.x == 0 && bubbles[i].speed.y == 0)
    {
        bubbles[i].speed.x = bubbles[i].store_speed.x;
        bubbles[i].speed.y = bubbles[i].store_speed.y;
    }
    else
    {
        bubbles[i].speed.x = 0;
        bubbles[i].speed.y = 0;
    }
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){
        //int i;
		case '1':
			drawgrid=1-drawgrid;
			break;

        case 'p':
            //i = 0;
            for(int i=0; i<bubble_count; i++)
            {
                pause_speed(i);
            }

            break;

		default:
			break;
	}
}

void decrease_speed(int i)
{
    double temp_speed_x = (1.0/1.3) * bubbles[i].speed.x;
    double temp_speed_y = (1.0/1.3) * bubbles[i].speed.y;

    double speed_val = sqrt(temp_speed_x*temp_speed_x + temp_speed_y*temp_speed_y);

    //cout << "speed_val:" << speed_val << endl;
    if(speed_val > speed_lower_limit)
    {
        bubbles[i].speed.x = temp_speed_x;
        bubbles[i].speed.y = temp_speed_y;
    }

    if(bubbles[i].speed.x != 0 && bubbles[i].speed.y)
    {
        //cout << "decreasing speed" << endl;
        bubbles[i].store_speed.x = bubbles[i].speed.x;
        bubbles[i].store_speed.y = bubbles[i].speed.y;
    }
}


void increase_speed(int i)
{
    double temp_speed_x = 1.3 * bubbles[i].speed.x;
    double temp_speed_y = 1.3 * bubbles[i].speed.y;

    double speed_val = sqrt(temp_speed_x*temp_speed_x + temp_speed_y*temp_speed_y);

    if(speed_val < speed_upper_limit)
    {
        //cout << "speed_val:" << speed_val << endl;
        bubbles[i].speed.x = temp_speed_x;
        bubbles[i].speed.y = temp_speed_y;
    }

    if(bubbles[i].speed.x != 0 && bubbles[i].speed.y)
    {
        bubbles[i].store_speed.x = bubbles[i].speed.x;
        bubbles[i].store_speed.y = bubbles[i].speed.y;
    }
}


void specialKeyListener(int key, int x,int y){
	switch(key){
	    //int i;
	    double temp_speed_x, temp_speed_y, speed_val;
		case GLUT_KEY_DOWN:		//down arrow key
			//cameraHeight -= 3.0;
            //i = 0;
            for(int i=0; i<bubble_count; i++)
            {
                decrease_speed(i);
            }

			break;
		case GLUT_KEY_UP:		// up arrow key
			//cameraHeight += 3.0;
			//i = 0;
			for(int i=0; i<bubble_count; i++)
			{
                increase_speed(i);
			}

			break;

		case GLUT_KEY_RIGHT:
			//cameraAngle += 0.03;
			break;
		case GLUT_KEY_LEFT:
			cameraAngle -= 0.03;
			break;

		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
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
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				drawaxes=1-drawaxes;
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}


point getSpeed(double val, int i)
{
    point p;

    if(i == 2)
    {
        p.x = 0.01;
    }
    else
    {
        while(true)
        {
            p.x = 0.01 + (double) fRand(0.01, 0.7);
            if(p.x < val)
            {
                break;
            }
        }
    }

    p.y = sqrt(val*val - p.x*p.x);
    //p.y = 0.01 + (coeff/y_divisor) * (double) rand()/RAND_MAX;
    p.z = 0;

    //cout << p.x << " " << p.y << endl;
    return p;
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
	gluLookAt(0,0,200,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	//drawAxes();
	drawGrid();

    //glColor3f(1,0,0);
    //drawSquare(10);

    //drawSS();
    myDrawSS();
    //tempDrawSS();

    //drawCircle(30,24);

    //drawCone(20,50,24);

	//drawSphere(30,24,20);




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

double getDistance(point &p1, point &p2)
{
    double distance = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
    distance = sqrt(distance);
    return distance;
}

void bubble_motion()
{
    for(int i=0; i<bubble_count; i++)
    {
        clock_t this_current_time = clock();
        /*if(this_current_time < bubbles[i].generation_time)
        {

        }*/
        if(this_current_time >= bubbles[i].generation_time)
        {
            bubbles[i].pos.x = bubbles[i].pos.x + bubbles[i].speed.x;
            bubbles[i].pos.y = bubbles[i].pos.y + bubbles[i].speed.y;
        }
    }
}

void handle_sqaure_collision()
{
    for(int i=0; i<bubble_count; i++)
    {
        if(bubbles[i].if_inside_circle == 0)
        {
            if(bubbles[i].pos.y >= (a-small_rad))
            {
                //cout << "bubbles[i].pos.x > a" << endl;
                bubbles[i].speed.y = -bubbles[i].speed.y;
                bubbles[i].store_speed.y = bubbles[i].speed.y;
                bubbles[i].bubble_upperSquare_clash_flag = 1;
            }
            else if(bubbles[i].pos.y <= -(a-small_rad) && bubbles[i].bubble_upperSquare_clash_flag == 1)
            {
                bubbles[i].speed.y = -bubbles[i].speed.y;
                bubbles[i].store_speed.y = bubbles[i].speed.y;
                bubbles[i].bubble_upperSquare_clash_flag = 0;
            }
            else if(bubbles[i].pos.x >= (a-small_rad))
            {
                bubbles[i].speed.x = -bubbles[i].speed.x;
                bubbles[i].store_speed.x = bubbles[i].speed.x;
                bubbles[i].bubble_sideSquare_clash_flag = 1;
            }
            else if(bubbles[i].pos.x <= -(a-small_rad) && bubbles[i].bubble_sideSquare_clash_flag == 1)
            {
                bubbles[i].speed.x = -bubbles[i].speed.x;
                bubbles[i].store_speed.x = bubbles[i].speed.x;
                bubbles[i].bubble_sideSquare_clash_flag = 0;
            }
        }
    }
}

boolean if_insideBubble(int current_i)
{
    boolean inside = false;
    for(int i=0; i<bubble_count; i++)
    {
        if(i != current_i)
        {
            double distance = getDistance(bubbles[i].pos, bubbles[current_i].pos);
            if(distance <= 2.0*small_rad)
            {
                //bubbles[current_i].overlap_flag[i] = 1;
                inside = true;
                break;
            }
        }
    }
    return inside;
}

void check_if_inside_circle()
{
    for(int i=0; i<bubble_count; i++)
    {
        double distance = getDistance(bubbles[i].pos, circle_pos);

        if(distance <= (big_rad-small_rad)) //boro circle er moddhe eshe geche
        {
            boolean inside = if_insideBubble(i);
            if(inside == false)
            {
                bubbles[i].if_inside_circle = 1;
            }
        }
    }
}

point get_reflection_vector(point &d, point &center1, point &center2)
{
    point temp_n, n;
    temp_n.x = center1.x - center2.x;
    temp_n.y = center1.y - center2.y;

    /*double distance = (center1.x - center2.x)*(center1.x - center2.x) + (center1.y - center2.y)*(center1.y - center2.y);
    distance = sqrt(distance);*/

    double distance = getDistance(center1, center2);

    //normalizing n
    n.x = (temp_n.x * 1.0) / distance;
    n.y = (temp_n.y * 1.0) / distance;

    point r;
    double dot_product = d.x*n.x + d.y*n.y;
    r.x = d.x - 2*dot_product*n.x;
    r.y = d.y - 2*dot_product*n.y;
    return r;
}

boolean if_obtuse(point &d, point &center1, point &center2) //works
{
    boolean obtuse = false;
    point temp_n, n;
    temp_n.x = center1.x - center2.x;
    temp_n.y = center1.y - center2.y;

    /*double distance = (center1.x - center2.x)*(center1.x - center2.x) + (center1.y - center2.y)*(center1.y - center2.y);
    distance = sqrt(distance);*/

    double distance = getDistance(center1, center2);

    //normalizing n
    n.x = (temp_n.x * 1.0) / distance;
    n.y = (temp_n.y * 1.0) / distance;

    double dot_product = d.x*n.x + d.y*n.y;

    if(dot_product > 0)
    {
        obtuse = true;
    }
    return obtuse;
}

boolean if_obtuse_2(point &d, point &center1, point &center2)
{
    boolean obtuse = false;
    point temp_n, n;
    temp_n.x = center1.x - center2.x;
    temp_n.y = center1.y - center2.y;

    /*double distance = (center1.x - center2.x)*(center1.x - center2.x) + (center1.y - center2.y)*(center1.y - center2.y);
    distance = sqrt(distance);*/

    double distance = getDistance(center1, center2);

    //normalizing n
    n.x = (temp_n.x * 1.0) / distance;
    n.y = (temp_n.y * 1.0) / distance;

    double dot_product = d.x*n.x + d.y*n.y;

    if(dot_product < 0)
    {
        obtuse = true;
    }
    return obtuse;
}

void bubble_bubble_collision(int current_i)
{
    for(int i=0; i<bubble_count; i++)
    {
        if(i != current_i && bubbles[i].if_inside_circle == 1)
        {
            double distance = getDistance(bubbles[i].pos, bubbles[current_i].pos);

            point current_i_next_pos;
            current_i_next_pos.x = bubbles[current_i].pos.x + bubbles[current_i].speed.x;
            current_i_next_pos.y = bubbles[current_i].pos.y + bubbles[current_i].speed.y;

            point i_next_pos;
            i_next_pos.x = bubbles[i].pos.x + bubbles[i].speed.x;
            i_next_pos.y = bubbles[i].pos.y + bubbles[i].speed.y;

            double next_distance = getDistance(bubbles[i].pos, current_i_next_pos);

            if(next_distance <= 2.0*small_rad)
            {
                boolean obtuse = if_obtuse(bubbles[current_i].speed, bubbles[i].pos, bubbles[current_i].pos);

                if(obtuse == true)
                {
                    point r1;
                //cout << "before collision: " <<  bubbles[current_i].speed.x << " " <<  bubbles[current_i].speed.y << endl;
                    r1 = get_reflection_vector(bubbles[current_i].speed, bubbles[i].pos, bubbles[current_i].pos);

                    bubbles[current_i].speed.x = r1.x;
                    bubbles[current_i].speed.y = r1.y;

                    bubbles[current_i].store_speed.x = bubbles[current_i].speed.x;
                    bubbles[current_i].store_speed.y = bubbles[current_i].speed.y;

                    bubbles[current_i].conflict_with_bubble = 1;
                }
            }
        }
    }
}

void circle_bubble_collision(int i)
{
    double distance = getDistance(bubbles[i].pos, circle_pos);

    point next_pos;
    next_pos.x = bubbles[i].pos.x + bubbles[i].speed.x;
    next_pos.y = bubbles[i].pos.y + bubbles[i].speed.y;
    double next_distance = getDistance(next_pos, circle_pos);

    //if(distance <= (big_rad-small_rad) && next_distance >= (big_rad-small_rad)) //refelction_with_circle
    if(next_distance >= (big_rad-small_rad))
    {
        boolean obtuse = if_obtuse_2(bubbles[i].speed, circle_pos, bubbles[i].pos);

        //if(obtuse == true)
        {
            //cout << "here obtuse" << endl;
            point r;
            r = get_reflection_vector(bubbles[i].speed, circle_pos, bubbles[i].pos);

            bubbles[i].speed.x = r.x;
            bubbles[i].speed.y = r.y;

            bubbles[i].store_speed.x = bubbles[i].speed.x;
            bubbles[i].store_speed.y = bubbles[i].speed.y;
        }
    }
}

void reflection_inside_circle()
{
    for(int i=0; i<bubble_count; i++)
    {
        if(bubbles[i].if_inside_circle == 1)
        {
            circle_bubble_collision(i);
            bubble_bubble_collision(i);
        }
    }

    for(int i=0; i<bubble_count; i++)
    {
        if(bubbles[i].if_inside_circle == 1)
        {
            //bubble_bubble_collision(i);
        }
    }
}


void animate(){
	//angle+=0.05;
	//codes for any changes in Models, Camera
	//sqaure_collision
    //int i = 0;
    //cout << bubbles[i].speed.x << " " << bubbles[i].speed.y << endl;
    bubble_motion();
    handle_sqaure_collision();
    check_if_inside_circle();
    reflection_inside_circle();

	glutPostRedisplay();
}

void init_bubbles(int i, double val)
{
    point v = getSpeed(val, i);
    //if(i==4) cout << "last v : " << v.x << " " << v.y << endl;
    //cout << theta << endl;
    double speed_val = sqrt(v.x*v.x + v.y*v.y);
    double theta = atan2(v.y, v.x);
    //cout << speed_val * cos(theta) << " " << speed_val * sin(theta) << endl;

    //cout << "init_speed_val:" << speed_val << endl;

    bubbles[i].speed.x = v.x;
    bubbles[i].speed.y = v.y;
    bubbles[i].speed.z = 0;

    bubbles[i].store_speed.x = bubbles[i].speed.x;
    bubbles[i].store_speed.y = bubbles[i].speed.y;
    bubbles[i].store_speed.z = bubbles[i].speed.z;

    bubbles[i].generation_time = (i+1) * 1000;

    bubbles[i].pos.x = -(a-small_rad); //-(a+small_rad);
    bubbles[i].pos.y = -(a-small_rad);
    bubbles[i].pos.z = 0;

    bubbles[i].init_pos.x = -a;
    bubbles[i].init_pos.y = -(a+small_rad);
    bubbles[i].init_pos.z = 0;

    bubbles[i].bubble_upperSquare_clash_flag = 0;
    bubbles[i].bubble_sideSquare_clash_flag = 0;
    bubbles[i].if_inside_circle = 0;
    bubbles[i].conflict_with_bubble = 0;
}

void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;
	//count = 0;
	circle_pos.x = 0;
    circle_pos.y = 0;
    circle_pos.z = 0;
    a = 130;
    big_rad = 85;
    small_rad = 12; //small_rad < (a-big_rad)
    //double init_pos = -(a+small_rad);
    double val = 0.0 + (double) fRand(0.5, 0.9);
    val = (1.0/2) * val;
    //cout << val << endl;
	for(int i=0; i<bubble_count; i++)
	{
	    init_bubbles(i, val);
	}

    speed_upper_limit = 1.2;
    speed_lower_limit = 0.05;

    start = clock();
	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
    srand(time(0));
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("Bubbles");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
