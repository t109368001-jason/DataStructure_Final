#include <pcl/visualization/cloud_viewer.h>
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/vtk_io.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/point_types.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <Windows.h>    
#include <stdio.h>    
#include <gl/GL.h>  
#include <gl/GLU.h> 
#include <gl/glut.h>
#include <conio.h>    
#include <stdio.h>    
#include <math.h>    
#include <string.h>    

pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
pcl::PolygonMesh triangles;

pcl::CentroidPoint<pcl::PointXYZ> centroid;

GLfloat xRot = 0.0f;					//camera X 角度
GLfloat yRot = 0.0f;					//camera Y 角度
GLfloat zRot = 0.0f;					//camera Z 角度
float angle = 0.0;
float angle2 = M_PI_2;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f, ly = 0.0;
// XZ position of the camera
float cx = 0.0f, cz = 5.0f, cy = 0.0f;

int xOrigin = -1;
void output(float x, float y,float z, char *string)
{
	int len, i;

	glRasterPos3f(x, y ,z);
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
void Display(void)
{
	//清除
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//保存矩陣 
	glPushMatrix();

	glColor3f(1.0, 1.0, 1.0);
	glPointSize(1.0);
	glLineWidth(1.0);

	glLoadIdentity();

	gluLookAt(cx, cy, cz,
		cx + lx, cy + ly, cz + lz,
		0.0f, 1.0f, 0.0f);
	/*
	//旋轉 
	glRotatef(xRot, 0.0f, 1.0f, 0.0f);
	glRotatef(yRot, 1.0f, 0.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);

	glutWireTeapot(2);
	*/

	pcl::PointCloud<pcl::PointXYZ> *x = cloud.get();
	for (size_t i = 0; i < triangles.polygons.size() - 1; ++i)
	{
		glBegin(GL_LINES);
		glVertex3f(x->points[triangles.polygons[i].vertices[0]].x, x->points[triangles.polygons[i].vertices[0]].y, x->points[triangles.polygons[i].vertices[0]].z);
		glVertex3f(x->points[triangles.polygons[i].vertices[1]].x, x->points[triangles.polygons[i].vertices[1]].y, x->points[triangles.polygons[i].vertices[1]].z);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(x->points[triangles.polygons[i].vertices[1]].x, x->points[triangles.polygons[i].vertices[1]].y, x->points[triangles.polygons[i].vertices[1]].z);
		glVertex3f(x->points[triangles.polygons[i].vertices[2]].x, x->points[triangles.polygons[i].vertices[2]].y, x->points[triangles.polygons[i].vertices[2]].z);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(x->points[triangles.polygons[i].vertices[0]].x, x->points[triangles.polygons[i].vertices[0]].y, x->points[triangles.polygons[i].vertices[0]].z);
		glVertex3f(x->points[triangles.polygons[i].vertices[2]].x, x->points[triangles.polygons[i].vertices[2]].y, x->points[triangles.polygons[i].vertices[2]].z);
		glEnd();
	}
	//output(cx + lx*10, cy + ly*10, cz + lz*10,"xxxx");
	/*
	pcl::PointCloud<pcl::PointXYZ> *x = cloud.get();
	for (size_t i = 0; i < x->points.size(); ++i)
	{
	glBegin(GL_POINTS);

	glVertex3f(x->points[i].x * scaleD, x->points[i].y * scaleD, x->points[i].z * scaleD);
	glEnd();
	}*/

	glPopMatrix();

	glutSwapBuffers();
}

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DITHER);
	glShadeModel(GL_SMOOTH);
}
void Mouse(int button, int state, int x, int y)
{
	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			xOrigin = -1;
		}
		else {// state = GLUT_DOWN
			xOrigin = x;
		}
		cout << "Mouse click x=" << x << " y=" << y << endl;
	}
	//glutPostRedisplay();
}
void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	/*if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}*/
}
void Keyboard(unsigned char key, int x, int y)
{
	float fraction = 0.1f;
	switch (key)
	{
	case 'w':
		cx += lx * fraction;
		cz += lz * fraction;
		cy += ly * fraction;
		break;
	case 's':
		cx -= lx * fraction;
		cz -= lz * fraction;
		cy -= ly * fraction;
		break;
	case 'a':
		angle -= 0.1f;
		lz = -sin(angle2)*cos(angle);
		lx = sin(angle2)*sin(angle);
		ly = -cos(angle2);
		break;
	case 'd':
		angle += 0.1f;
		lz = -sin(angle2)*cos(angle);
		lx = sin(angle2)*sin(angle);
		ly = -cos(angle2);
		break;

	default: printf("   Keyboard %c == %d\n", key, key);	break;

	}
	glutPostRedisplay();
}
void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;
	case GLUT_KEY_UP:
		if (angle2 < (M_PI - 0.1))
			angle2 += 0.1f;
		lz = -sin(angle2)*cos(angle);
		lx = sin(angle2)*sin(angle);
		ly = -cos(angle2);
		break;
		break;
	case GLUT_KEY_DOWN:
		if (angle2 > 0.1)
			angle2 -= 0.1f;
		lz = -sin(angle2)*cos(angle);
		lx = sin(angle2)*sin(angle);
		ly = -cos(angle2);
		break;
	}
	glutPostRedisplay();
}


void ChangeSize(int w, int h)
{
	GLfloat fAspect;
	pcl::PointXYZ x;
	centroid.get(x);

	if (h == 0)
		h = 1;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.001, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
int main(int argc, char* argv[])
{
	// Load input file into a PointCloud<T> with an appropriate type
	pcl::PCLPointCloud2 cloud_blob;
	pcl::io::loadPCDFile("../file/bunny.pcd", cloud_blob);
	pcl::fromPCLPointCloud2(cloud_blob, *cloud);
	//* the data should be available in cloud
	pcl::PointCloud<pcl::PointXYZ> *x = cloud.get();
	for (size_t i = 0; i < x->points.size(); ++i)
	{
		centroid.add(x->points[i]);
	}

	// Normal estimation*
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
	tree->setInputCloud(cloud);
	n.setInputCloud(cloud);
	n.setSearchMethod(tree);
	n.setKSearch(20);
	n.compute(*normals);
	//* normals should not contain the point normals + surface curvatures

	// Concatenate the XYZ and normal fields*
	pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>);
	pcl::concatenateFields(*cloud, *normals, *cloud_with_normals);
	//* cloud_with_normals = cloud + normals

	// Create search tree*
	pcl::search::KdTree<pcl::PointNormal>::Ptr tree2(new pcl::search::KdTree<pcl::PointNormal>);
	tree2->setInputCloud(cloud_with_normals);

	// Initialize objects
	pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;

	// Set the maximum distance between connected points (maximum edge length)
	gp3.setSearchRadius(0.025);

	// Set typical values for the parameters
	gp3.setMu(2.5);
	gp3.setMaximumNearestNeighbors(10);
	gp3.setMaximumSurfaceAngle(M_PI / 4); // 45 degrees
	gp3.setMinimumAngle(M_PI / 18); // 10 degrees
	gp3.setMaximumAngle(2 * M_PI / 3); // 120 degrees
	gp3.setNormalConsistency(false);

	// Get result
	gp3.setInputCloud(cloud_with_normals);
	gp3.setSearchMethod(tree2);
	gp3.reconstruct(triangles);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("RGB Cube");
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(mouseMove);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(Display);
	SetupRC();
	glutMainLoop();
	return 0;
}