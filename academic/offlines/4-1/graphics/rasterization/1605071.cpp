// #rows = height, #cols = width
// z-buffer dim: width x height

#include "bitmap_image.hpp"
#include <iostream>
#include <fstream>
#include <stack>
#include <cstring>
#include <vector>
#include<cmath>
#include <iomanip>
using namespace std;

#include <chrono>
using namespace std::chrono;

#define matSize 4
#define pi (2*acos(0.0))
#define zero 0.0
#define one 1.0
#define infinite 999999

ifstream inFile, inFile4, inFile5;
ofstream outFile1, outFile2, outFile3, outFile4;

// string scene_filename = "scene.txt";
// string config_filename = "config.txt";

string folderName = "Test Cases (Updated)";
string folderNo = "3";
string path = folderName + "/" + folderNo + "/";
string scene_filename = path + "scene.txt";
string config_filename = path + "config.txt";

string output_filename1 = "stage1.txt"; //myoutput/
string output_filename2 = "stage2.txt";
string output_filename3 = "stage3.txt";
string zbuffer_output_filename = "z_buffer.txt";

vector<int> manage_pushpop;

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

    bool operator < (const MyVector &p) const
    {
        return (y < p.y);
    }

    double getValue()
    {
        return sqrt(x*x + y*y + z*z);
    }

    void printVector()
    {
        cout << x << "\t" << y << "\t" << z << endl;
    }
};

class point2D
{
    public:
        int x, y;

        void printPoint2D()
        {
            cout << x << "\t" << y << endl;
        }
};

MyVector eye, look, up; //gluLookAt params
double fovY, aspectRatio, near, far; //gluPerspective
//stage4 global_vars
int screen_Width, screen_Height;
double x_leftLimit, x_rightLimit, y_bottomLimit, y_topLimit;
double z_frontLimit, z_rearLimit, z_max;
double dx, dy;
double top_Y, bottom_Y, left_X, right_X;
double** z_buffer;
// MyVector** frame_buffer;
bitmap_image image;

MyVector normalize(MyVector a)
{
    double x = a.x, y = a.y, z = a.z;
    MyVector norm;
    double val = sqrt(x*x + y*y + z*z);

    norm.x = (x*1.0)/val;
    norm.y = (y*1.0)/val;
    norm.z = (z*1.0)/val;
    
    return norm;
}

double dotProduct(MyVector vect1, MyVector vect2)
{
    double res;
    res = vect1.x * vect2.x + vect1.y * vect2.y + vect1.z * vect2.z;
    return res;
}

MyVector crossProduct(MyVector vect1, MyVector vect2)
{
    double vx, vy, vz;
    vx = vect1.y * vect2.z - vect1.z * vect2.y;
    vy = vect1.z * vect2.x - vect1.x * vect2.z;
    vz = vect1.x * vect2.y - vect1.y * vect2.x;

    MyVector res;
    res.x = vx;
    res.y = vy;
    res.z = vz;

    return res;
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

MyVector Rodrigues(MyVector x, MyVector a, double angle)
{
    MyVector term1, term2, term3;

    double rad_angle = ((pi*1.0)/180) * angle;

    term1 = scaler_vectmult(cos(rad_angle), x);

    double dot_res = dotProduct(a, x);
    double val2 = (1 - cos(rad_angle)) * dot_res;
    term2 = scaler_vectmult(val2, a);

    MyVector cross_res = crossProduct(a, x);
    term3 = scaler_vectmult(sin(rad_angle), cross_res);

    MyVector temp_vect_sum = vect_add(term1, term2);
    MyVector R = vect_add(temp_vect_sum, term3);

    return R;
}

/*void printMyVector(MyVector v)
{
    cout << v.x << "\t" << v.y << "\t" << v.z << endl;
}*/

class MyMatrix {      // The class
  public:             // Access specifier
    int row, col;
    double **mat;  // Attribute (string variable)

    MyMatrix(int row, int col)
    {
        this->row = row;
        this->col = col;

        mat = new double *[row];
        for(int i = 0; i <row; i++)
            mat[i] = new double[col];

        for(int i=0; i<row; i++)
        {
            for(int j=0; j<col; j++)
            {
                mat[i][j] = 0.0;
            }
        }
    }

    void getMatrix_fromVect(MyVector v)
    {
        mat[0][0] = v.x;
        mat[1][0] = v.y;
        mat[2][0] = v.z;
        mat[3][0] = 1.0;
    }

    void getIdentityMatrix()
    {
        for(int i=0; i<row; i++)
        {
            for(int j=0; j<col; j++)
            {
                if(i == j) mat[i][j] = 1.0;
            }
        }
    }

    void getTranslationMatrix(double tx, double ty, double tz)
    {
        for(int i=0; i<row; i++)
        {
            for(int j=0; j<col; j++)
            {
                if(i == j) mat[i][j] = 1.0;
            }
        }

        mat[0][col-1] = tx;
        mat[1][col-1] = ty;
        mat[2][col-1] = tz;
    }

    void getScaleMatrix(double sx, double sy, double sz)
    {
        mat[0][0] = sx;
        mat[1][1] = sy;
        mat[2][2] = sz;
        mat[3][3] = 1.0;
    }

    void getRotationMatrix(double angle, double ax, double ay, double az)
    {
        MyVector a(ax, ay, az);
        MyVector a_norm = normalize(a);

        MyVector i(one, zero, zero);
        MyVector c1 = Rodrigues(i, a_norm, angle);

        MyVector j(zero, one, zero);
        MyVector c2 = Rodrigues(j, a_norm, angle);
        
        MyVector k(zero, zero, one);
        MyVector c3 = Rodrigues(k, a_norm, angle);

        mat[0][0] = c1.x, mat[0][1] = c2.x, mat[0][2] = c3.x;
        mat[1][0] = c1.y, mat[1][1] = c2.y, mat[1][2] = c3.y;
        mat[2][0] = c1.z, mat[2][1] = c2.z, mat[2][2] = c3.z;

        mat[3][3] = 1.0;
    }

    void printMatrix()
    {
        for(int i=0; i<row; i++)
        {
            for(int j=0; j<col; j++)
            {
                cout << mat[i][j] << "\t";
                //printf("%lf\t", mat[i][j]);
            }
            cout << endl;
        }
        cout << endl;
    }

    void printMatrix_singleCol()
    {
        for(int i=0; i<row-1; i++)
        {
            cout << mat[i][0] << "\t";
        }
        cout << endl;
    }

    void write_inFile1()
    {
        for(int i=0; i<row-1; i++)
        {
            outFile1 << mat[i][0];
            if(i < row-2) outFile1 << " ";
        }
        outFile1 << endl;
    }

    void write_inFile2()
    {
        for(int i=0; i<row-1; i++)
        {
            outFile2 << mat[i][0];
            if(i < row-2) outFile2 << " ";
        }
        outFile2 << endl;
    }

    void write_inFile3()
    {
        for(int i=0; i<row-1; i++)
        {
            outFile3 << mat[i][0];
            if(i < row-2) outFile3 << " ";
        }
        outFile3 << endl;
    }

};

stack <MyMatrix> S;

MyMatrix scaler_matdiv(MyMatrix m)
{
    int row = m.row;
    int col = m.col;
    MyMatrix res(row, col);
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            res.mat[i][0] = (m.mat[i][0] * 1.0) / m.mat[row-1][col-1]; 
        }
    }
    return res;
}

MyMatrix matmult(MyMatrix a, MyMatrix b)
{
    int r = a.row;
    int c_1 = a.col;
    int c = b.col;

    MyMatrix resmat(r, c);

    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)
        {
            for(int k=0; k<c_1; k++)
            {
                resmat.mat[i][j] = resmat.mat[i][j] + a.mat[i][k] * b.mat[k][j];
            }
        }
    }

    if(resmat.mat[r-1][c-1] != 1)
    {
        MyMatrix resmat2(r, c);
        resmat2 = scaler_matdiv(resmat);
        return resmat2;
    }
    else
    {
        return resmat;
    }

    //return resmat;
}

double findMax(double a, double b, double c)
{
    return max({a, b, c});
}

double findMin(double a, double b, double c)
{
    return min({a, b, c});
}

double cross2D(MyVector u, MyVector v)
{
    return u.x*v.y - v.x*u.y;
}

double sign (MyVector p1, MyVector p2, MyVector p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

class MyTriangle
{
  public:
    MyVector points[3];
    int color[3];
    double max_y, min_y;
    double min_x, max_x;
    double max_z, min_z;
    vector <MyVector> sorted_points;

    bool if_point_indise_triangle (MyVector pt)
    {
        MyVector v1 = points[0], v2 = points[1], v3 = points[2];
        float d1, d2, d3;
        bool has_neg, has_pos;

        d1 = sign(pt, v1, v2);
        d2 = sign(pt, v2, v3);
        d3 = sign(pt, v3, v1);

        has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
        has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

        return !(has_neg && has_pos);
    }

    void printTriangle()
    {
        points[0].printVector();
        points[1].printVector();
        points[2].printVector();
        cout << endl;
    }

    void printTriangle_Color()
    {
        cout << "Color: " << color[0] << "\t" << color[1] << "\t" << color[2] << endl;
        cout << endl;
    }
};

vector<MyTriangle> triangleList;

// void showstack()
// {
//     while (!S.empty())
//     {
//         S.top().printMatrix();
//         S.pop();
//         cout << endl;
//     }
//     cout << endl;
// }

void show_manage_pushpop()
{
    for(int i=0; i<manage_pushpop.size(); i++)
    {
        cout << manage_pushpop[i] << "\t";
    }
    cout << endl;
}

void update_manage_pushpop()
{
    if(manage_pushpop.size() != 0)
    {
        int count = manage_pushpop.back() + 1;
        manage_pushpop.pop_back();
        manage_pushpop.push_back(count);
        //show_manage_pushpop();
    }
}

void getviewRotation_mat(MyMatrix m, MyVector l, MyVector r, MyVector u)
{
    m.mat[0][0] = r.x, m.mat[0][1] = r.y, m.mat[0][2] = r.z;
    m.mat[1][0] = u.x, m.mat[1][1] = u.y, m.mat[1][2] = u.z;
    m.mat[2][0] = -l.x, m.mat[2][1] = -l.y, m.mat[2][2] = -l.z;
    m.mat[3][3] = 1.0;
}

MyMatrix viewTransformation()
{
    MyVector l, r, u;
    
    l = vect_sub(look, eye);
    MyVector l_norm = normalize(l);

    r = crossProduct(l_norm, up);
    MyVector r_norm = normalize(r);

    u = crossProduct(r_norm, l_norm);
    //MyVector u_norm = normalize(u);

    //printMyVector(u); //ans milano drkr
    MyMatrix viewTranslation_mat(matSize, matSize);
    viewTranslation_mat.getTranslationMatrix(-eye.x, -eye.y, -eye.z);
    //viewTranslation_mat.printMatrix();

    MyMatrix viewRotation_mat(matSize, matSize);
    getviewRotation_mat(viewRotation_mat, l_norm, r_norm, u);
    //viewRotation_mat.printMatrix();

    MyMatrix V = matmult(viewRotation_mat, viewTranslation_mat);
    //V.printMatrix();

    return V;
}

void getProjection_mat(MyMatrix m, double r, double t)
{
    m.mat[0][0] = (near * 1.0)/r;
    m.mat[1][1] = (near * 1.0)/t;
    m.mat[2][2] = -((far+near) * 1.0)/(far-near);
    m.mat[2][3] = -(2.0 * far * near)/(far-near);
    m.mat[3][2] = -1; 
}

MyMatrix projectionTransformation()
{
    double fovX = fovY * aspectRatio * 1.0;

    double angle1 = fovY / 2.0;
    double rad_angle1 = (pi/180.0) * angle1;
    double t = near * tan(rad_angle1);

    double angle2 = fovX / 2.0;
    double rad_angle2 = (pi/180.0) * angle2;
    double r = near * tan(rad_angle2);

    MyMatrix P(matSize, matSize);
    getProjection_mat(P, r, t);
    //P.printMatrix();
    return P;
}

void makeTriangle(MyVector a, MyVector b, MyVector c)
{
    MyTriangle t;
    t.points[0].x = a.x,  t.points[0].y = a.y, t.points[0].z = a.z;
    t.points[1].x = b.x,  t.points[1].y = b.y, t.points[1].z = b.z;
    t.points[2].x = c.x,  t.points[2].y = c.y, t.points[2].z = c.z;

    int min_color = 0, max_color = 255;

    int r = min_color + ( rand() % ( max_color - min_color + 1 ) );
    int g = min_color + ( rand() % ( max_color - min_color + 1 ) );
    int b1 = min_color + ( rand() % ( max_color - min_color + 1 ) );

    t.color[0] = r;
    t.color[1] = g;
    t.color[2] = b1;

    //for clipping:
    t.max_y = findMax(t.points[0].y, t.points[1].y, t.points[2].y);
    t.min_y = findMin(t.points[0].y, t.points[1].y, t.points[2].y);

    t.min_x = findMin(t.points[0].x, t.points[1].x, t.points[2].x);
    t.max_x = findMax(t.points[0].x, t.points[1].x, t.points[2].x);

    t.max_z = findMax(t.points[0].z, t.points[1].z, t.points[2].z);
    t.min_z = findMin(t.points[0].z, t.points[1].z, t.points[2].z);

    t.sorted_points.push_back(t.points[0]);
    t.sorted_points.push_back(t.points[1]);
    t.sorted_points.push_back(t.points[2]);

    sort(t.sorted_points.begin(), t.sorted_points.end());

    triangleList.push_back(t);
}

void getOutput(MyVector a, MyVector b, MyVector c)
{
    MyMatrix m1(matSize, 1);
    m1.getMatrix_fromVect(a);

    MyMatrix m2(matSize, 1);
    m2.getMatrix_fromVect(b);

    MyMatrix m3(matSize, 1);
    m3.getMatrix_fromVect(c);

    MyMatrix res1 = matmult(S.top(), m1);
    MyMatrix res2 = matmult(S.top(), m2);
    MyMatrix res3 = matmult(S.top(), m3);
    res1.write_inFile1();
    res2.write_inFile1();
    res3.write_inFile1();
    outFile1 << endl;

    MyMatrix V = viewTransformation();
    MyMatrix res1_view = matmult(V, res1);
    MyMatrix res2_view = matmult(V, res2);
    MyMatrix res3_view = matmult(V, res3);
    res1_view.write_inFile2();
    res2_view.write_inFile2();
    res3_view.write_inFile2();
    outFile2 << endl;

    MyMatrix P = projectionTransformation();
    MyMatrix res1_proj = matmult(P, res1_view);
    MyMatrix res2_proj = matmult(P, res2_view);
    MyMatrix res3_proj = matmult(P, res3_view);
    res1_proj.write_inFile3();
    res2_proj.write_inFile3();
    res3_proj.write_inFile3();
    outFile3 << endl;

    // MyVector p1, p2, p3;
    // p1.x = res1_proj.mat[0][0], p1.y = res1_proj.mat[1][0], p1.z = res1_proj.mat[2][0];
    // p2.x = res2_proj.mat[0][0], p2.y = res2_proj.mat[1][0], p2.z = res2_proj.mat[2][0];
    // p3.x = res3_proj.mat[0][0], p3.y = res3_proj.mat[1][0], p3.z = res3_proj.mat[2][0];

    // makeTriangle(p1, p2, p3);
}

void readFromFile()
{
    string command;
    inFile.open(scene_filename);
    outFile1.open(output_filename1);
    outFile2.open(output_filename2);
    outFile3.open(output_filename3);

    if(!inFile) { // file couldn't be opened
      cerr << "Error: file could not be opened" << endl;
      exit(1);
    }

    inFile >> eye.x >> eye.y >> eye.z;
    inFile >> look.x >> look.y >> look.z;
    inFile >> up.x >> up.y >> up.z;

    inFile >> fovY >> aspectRatio >> near >> far;

    while (true)
    {
        inFile >> command;
        if(command.compare("triangle") == 0)
        {
            MyVector p1, p2, p3;
            inFile >> p1.x >> p1.y >> p1.z;
            inFile >> p2.x >> p2.y >> p2.z;
            inFile >> p3.x >> p3.y >> p3.z;

            // p1.printVector();
            // p2.printVector();
            // p3.printVector();
            // cout << endl;

            getOutput(p1, p2, p3);
        }
        else if(command.compare("translate") == 0)
        {
            double tx, ty, tz;
            inFile >> tx >> ty >> tz;
            //cout << tx << "\t" << ty << "\t" << tz << endl;
            MyMatrix translation_mat(matSize, matSize);
            translation_mat.getTranslationMatrix(tx, ty, tz);
            //translation_mat.printMatrix();
            MyMatrix prod = matmult(S.top(), translation_mat);
            S.push(prod);
            update_manage_pushpop();
        }
        else if(command.compare("scale") == 0)
        {
            double sx, sy, sz;
            inFile >> sx >> sy >> sz;
            //cout << sx << "\t" << sy << "\t" << sz << endl;
            MyMatrix scale_mat(matSize, matSize);
            scale_mat.getScaleMatrix(sx, sy, sz);
            //scale_mat.printMatrix();
            MyMatrix prod = matmult(S.top(), scale_mat);
            S.push(prod);
            update_manage_pushpop();
        }
        else if(command.compare("rotate") == 0)
        {
            double angle, ax, ay, az;
            inFile >> angle >> ax >> ay >> az;

            MyMatrix rotation_mat(matSize, matSize);
            rotation_mat.getRotationMatrix(angle, ax, ay, az);
            //rotation_mat.printMatrix(); //answer milano drkr

            MyMatrix prod = matmult(S.top(), rotation_mat);
            S.push(prod);
            update_manage_pushpop();
        }
        else if(command.compare("push") == 0)
        {
            int count = 0;
            manage_pushpop.push_back(count);
            //show_manage_pushpop();
        }
        else if(command.compare("pop") == 0)
        {
            if(manage_pushpop.size() != 0)
            {
                for(int i=0; i<manage_pushpop.back(); i++)
                {
                    S.pop();
                }
                manage_pushpop.pop_back();
                //show_manage_pushpop();
            }
            //cout << "inside pop" << endl;
        }
        else if(command.compare("end") == 0)
        {
            break;
        }
    }
}

void readConfig()
{
    inFile4.open(config_filename);

    if(!inFile4) { // file couldn't be opened
      cerr << "Error: file could not be opened" << endl;
      exit(1);
    }

    inFile4 >> screen_Width >> screen_Height;
    inFile4 >> x_leftLimit;
    inFile4 >> y_bottomLimit;
    x_rightLimit = -x_leftLimit;
    y_topLimit = -y_bottomLimit;
    inFile4 >> z_frontLimit >> z_rearLimit;
    z_max = z_rearLimit;

    // cout << screen_Width << "\t" << screen_Height << endl;
    // cout << x_leftLimit << "\t" << y_bottomLimit << endl;;
    // cout << z_frontLimit << "\t" << z_rearLimit << endl;
}

void makeList_ofTrinagle()
{
    inFile5.open(output_filename3);
    if(!inFile5) { // file couldn't be opened
      cerr << "Error: file could not be opened" << endl;
      exit(1);
    }
    while(true)
    {
        MyVector p1, p2, p3;
        inFile5 >> p1.x >> p1.y >> p1.z;
        inFile5 >> p2.x >> p2.y >> p2.z;
        inFile5 >> p3.x >> p3.y >> p3.z;

        if(inFile5.eof()) break;

        makeTriangle(p1, p2, p3);
    }

    // cout << triangleList.size() << endl;

    // for(int i=0; i<triangleList.size(); i++)
    // {
    //     cout << "triangle_no: " << i << endl;
    //     MyTriangle temp_t = triangleList[i];
    //     // temp_t.printTriangle();
    //     temp_t.printTriangle_Color();
        
    //     cout << endl;
    // }
}

void create_z_buffer()
{
    z_buffer = new double*[screen_Width];
 
    for (int i = 0; i < screen_Width; i++)
    {
        z_buffer[i] = new double[screen_Height];
    }

    for (int i = 0; i < screen_Width; i++)
    {
        for (int j = 0; j < screen_Height; j++)
        {
            z_buffer[i][j] = z_rearLimit;
        }
    }

    /*for (int i = 0; i < screen_Height; i++)
    {
        for (int j = 0; j < screen_Width; j++)
        {
            cout << z_buffer[i][j] << " ";
        }
        cout << endl;
    }*/
}

void create_frame_buffer()
{
    image.setwidth_height(screen_Width, screen_Height);

    for(int i=0; i<screen_Width; i++)
    {
        for(int j=0; j<screen_Height; j++)
        {
            double f_r = zero;
            double f_g = zero;
            double f_b = zero;
            
            image.set_pixel(i, j, f_r, f_g, f_b); 
        }
    }

    image.save_image("output.bmp");
}

int findRow(double py)
{
    // int row = (y_topLimit-py) / (dy * 1.0);
    int row = round((top_Y-py) / (dy * 1.0));

    if(row == screen_Height)
    // if(abs(py - y_bottomLimit) < 1e-7)
    {
        row = row - 1;
    }
    else if(row == -1)
    {
        row = 0;
    }

    return row;
}

int findCol(double px)
{
    // int col = (px-x_leftLimit) / (dx * 1.0);
    int col = round((px-left_X) / (dx * 1.0));
    
    if(col == screen_Width)
    // if(abs(px - x_rightLimit) < 1e-7)
    {
        col = col - 1;
    }
    else if(col == -1)
    {
        col = 0;
    }

    return col;
}

double get_middleValue_Y(int row_no)
{
    double ys = top_Y - row_no * dy;
    return ys;
}

double get_middleValue_X(int col_no)
{
    double scan_x = left_X + col_no * dx;
    return scan_x;
}

double getDistance(MyVector a, MyVector b)
{
    double distance = ((a.x - b.x)*(a.x - b.x)) + ((a.y - b.y)*(a.y - b.y)) + ((a.z - b.z)*(a.z - b.z));
    distance = sqrt(distance);
    return distance;
}

bool point_on_tr_side(double ab, double ai, double bi) //s->side
{
    // if(ai+bi > ab+1e-7) return false; //outside triangle
    // else return true;

    if(abs(ai+bi - ab) < 1e-7) return true;
    else return false; //outside triangle
}

void update_buffer_2(int index)
{
    MyTriangle tr = triangleList[index];

    double x1 = tr.points[0].x;
    double x2 = tr.points[1].x;
    double x3 = tr.points[2].x;
    
    double y1 = tr.points[0].y;
    double y2 = tr.points[1].y;
    double y3 = tr.points[2].y;

    double z1 = tr.points[0].z;
    double z2 = tr.points[1].z;
    double z3 = tr.points[2].z;

    double side12, side23, side31;
    side12 = getDistance(tr.points[0], tr.points[1]);
    side23 = getDistance(tr.points[1], tr.points[2]);
    side31 = getDistance(tr.points[2], tr.points[0]);

    //cout << side12 << "\t" << side23 << "\t" << side31 << endl;

    double clip_y_top, clip_y_bottom, clip_x_left, clip_x_right;

    if(tr.min_y > top_Y || tr.max_y < bottom_Y)
    {
        cout << "traingle screen er baire" << endl;
        return;
    }

    if(tr.max_y > top_Y) clip_y_top = top_Y;
    else clip_y_top = tr.max_y;

    if(tr.min_y < bottom_Y) clip_y_bottom = bottom_Y;
    else clip_y_bottom = tr.min_y;

    int top_row = findRow(clip_y_top);
    int bottom_row = findRow(clip_y_bottom);

    // cout << top_row << "\t" << bottom_row << endl;
    //cout << tr.min_x << "\t" << tr.max_x << endl;

    //double ys = y1;
    for(int i=top_row; i<bottom_row+1; i++) //ekhane prob hoy 1st, last row bad na dile
    {
        double ys = get_middleValue_Y(i);

        double x12 = x1 - (x1-x2) * ((y1-ys) / (y1-y2));
        double x23 = x2 - (x2-x3) * ((y2-ys) / (y2-y3));
        double x31 = x3 - (x3-x1) * ((y3-ys) / (y3-y1));

        double z12 = z1 - (z1-z2) * ((y1-ys) / (y1-y2));
        double z23 = z2 - (z2-z3) * ((y2-ys) / (y2-y3));
        double z31 = z3 - (z3-z1) * ((y3-ys) / (y3-y1));

        double xa = -infinite, xb = -infinite, za = -infinite, zb = -infinite;

        MyVector p12, p23, p31; //intersect_points
        p12.x = x12; p12.y = ys, p12.z = z12;
        p23.x = x23; p23.y = ys, p23.z = z23;
        p31.x = x31; p31.y = ys, p31.z = z31;

        double d_e1, d_e2, d_f2, d_f3, d_g3, d_g1; //e-12, f-23, g-31 er intersect point

        d_e1 = getDistance(p12, tr.points[0]);
        d_e2 = getDistance(p12, tr.points[1]);
        d_f2 = getDistance(p23, tr.points[1]);
        d_f3 = getDistance(p23, tr.points[2]);
        d_g3 = getDistance(p31, tr.points[2]);
        d_g1 = getDistance(p31, tr.points[0]);

        bool on_side_12 = point_on_tr_side(side12, d_e1, d_e2);
        bool on_side_23 = point_on_tr_side(side23, d_f2, d_f3);
        bool on_side_31 = point_on_tr_side(side31, d_g3, d_g1);

        if(on_side_12 && on_side_23)
        {
            xa = x12, xb = x23;
            za = z12, zb = z23;
        }
        else if(on_side_23 && on_side_31)
        {
            xa = x23, xb = x31;
            za = z23, zb = z31;
        }
        else if(on_side_31 && on_side_12)
        {
            xa = x12, xb = x31;
            za = z12, zb = z31;
        }
        else if(on_side_12)
        {
            //cout << "here12 with row" << i << endl;
            xa = x12, xb = x12;
            za = z12, zb = z12;
        }
        else if(on_side_23)
        {
            //cout << "here23 with row" << i << endl;
            xa = x23, xb = x23;
            za = z23, zb = z23;
        }
        else if(on_side_31)
        {
            //cout << "here31 with row" << i << endl;
            xa = x31, xb = x31;
            za = z31, zb = z31;
        }
        else
        {
            // cout << "something went wrong with row " << i << endl;
            continue; //ekhane continue dewa uchiti
        }

        if(xa > xb)
        {
            double temp = xa;
            xa = xb;
            xb = temp;

            temp = za;
            za = zb;
            zb = temp;
        }

        if(xb < left_X || xa > right_X)
        {
            continue;
        }

        if(xa < left_X) clip_x_left = left_X;
        else clip_x_left = xa;

        if(xb > right_X) clip_x_right = right_X;
        else clip_x_right = xb;

        int start_col = findCol(clip_x_left);
        int end_col = findCol(clip_x_right);
        
        // cout << "row: " << i << "----" << start_col << "\t" << end_col << endl;

        for(int j=start_col; j<end_col+1; j++)
        {
            double xp = get_middleValue_X(j);
            double zp = zb - (zb-za) * ((xb-xp) / (xb-xa));
            
            if(z_buffer[j][i] > zp && zp >= z_frontLimit) //z_buffer[i][j] > zp ekhane = dewa jabe na
            {
                // cout << "here " << i << " ---- " << j << endl;
                z_buffer[j][i] = zp;

                image.set_pixel(j,i,tr.color[0],tr.color[1],tr.color[2]);
            }
        }
    }
    image.save_image("output.bmp");
}

void write_in_z_bufferFile()
{
    outFile4.open(zbuffer_output_filename);
    
    for(int i=0; i<screen_Height; i++)
    {
        for(int j=0; j<screen_Width; j++)
        {
            if(z_buffer[j][i] < z_max)
            {
                outFile4 << z_buffer[j][i] << "\t";
            }
        }
        outFile4 << endl;
    }
}

void free_memory()
{
    for( int i = 0 ; i < screen_Width ; i++ )
    {
        delete[] z_buffer[i]; // delete array within matrix
    }
    // delete actual matrix
    delete[] z_buffer;
}

void stage4_portion()
{
    makeList_ofTrinagle();
    readConfig();

    dx = ((x_rightLimit - x_leftLimit) * 1.0) / screen_Width;
    dy = ((y_topLimit - y_bottomLimit) * 1.0) / screen_Height;

    top_Y = y_topLimit - (dy/2.0);
    left_X = x_leftLimit + (dx/2.0);

    bottom_Y = y_bottomLimit + (dy/2.0);
    right_X = x_rightLimit - (dx/2.0);

    // cout << "top_Y\tbottom_Y: ";
    // cout << top_Y << "\t" << bottom_Y << endl;
    // cout << "left_X\tright_X: ";
    // cout << left_X << "\t" << right_X << endl;

    create_z_buffer();
    create_frame_buffer();
    
    //cout << "dx: " << dx << "\t" << "dy: " << dy << endl;
    //cout << triangleList.size() << endl;

    auto start = high_resolution_clock::now();
    for(int i=0; i<triangleList.size(); i++)
    {
        update_buffer_2(i);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    // cout << duration.count() << endl;

    // update_buffer_2(11); //test case 3 er jonno 5, 6 dekha jay na ; 2,7 overlap?
    // int row = findRow(-1);
    // int col = findCol(1);
    // cout << row << "\t" << col << endl;
    
    write_in_z_bufferFile();
    //draw_fullScreen();

    free_memory();
}

int main()
{
    srand(time(0));
    printf("begin...\n");
    outFile1 << fixed << setprecision(7);
    outFile2 << fixed << setprecision(7);
    outFile3 << fixed << setprecision(7);
    outFile4 << fixed << setprecision(6);
    cout << fixed << setprecision(7);

    MyMatrix identity_mat(matSize, matSize);
    identity_mat.getIdentityMatrix();
    S.push(identity_mat);
    
    readFromFile();
    inFile.close();
    outFile1.close();
    outFile2.close();
    outFile3.close();

    stage4_portion();
    inFile4.close();
    inFile5.close();
    outFile4.close();
    
    printf("end\n");
}