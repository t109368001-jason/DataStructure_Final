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

#define MOVE_SPEED 0.05f
#define ROTATE_SPEED 20.0f			//20 deg per 100 pixel

pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
pcl::PolygonMesh triangle;

pcl::CentroidPoint<pcl::PointXYZ> centroid;

GLfloat lookPhi = 0.0;
GLfloat lookTheta = M_PI_2;
// actual vector representing the camera's direction
GLfloat xLook = 0.0f, zLook = -1.0f, yLook = 0.0;
// XZ position of the camera
GLfloat cameraX = 0.0f, cameraZ = 5.0f, cameraY = 0.0f;

GLfloat xClick = -1, yClick = -1;
BOOL fixPhi = false;
BOOL fixTheta = false;
void output(GLfloat x, GLfloat y,GLfloat z, char *string)
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

	gluLookAt(cameraX, cameraY, cameraZ,
		cameraX + xLook, cameraY + yLook, cameraZ + zLook,
		0.0f, 1.0f, 0.0f);
	/*
	//旋轉 
	glRotatef(xRot, 0.0f, 1.0f, 0.0f);
	glRotatef(yRot, 1.0f, 0.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);

	glutWireTeapot(2);
	*/

	pcl::PointCloud<pcl::PointXYZ> *x = cloud.get();
	for (size_t i = 0; i < triangle.polygons.size() - 1; ++i)
	{
		glBegin(GL_LINES);
		glVertex3f(x->points[triangle.polygons[i].vertices[0]].x, x->points[triangle.polygons[i].vertices[0]].y, x->points[triangle.polygons[i].vertices[0]].z);
		glVertex3f(x->points[triangle.polygons[i].vertices[1]].x, x->points[triangle.polygons[i].vertices[1]].y, x->points[triangle.polygons[i].vertices[1]].z);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(x->points[triangle.polygons[i].vertices[1]].x, x->points[triangle.polygons[i].vertices[1]].y, x->points[triangle.polygons[i].vertices[1]].z);
		glVertex3f(x->points[triangle.polygons[i].vertices[2]].x, x->points[triangle.polygons[i].vertices[2]].y, x->points[triangle.polygons[i].vertices[2]].z);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(x->points[triangle.polygons[i].vertices[0]].x, x->points[triangle.polygons[i].vertices[0]].y, x->points[triangle.polygons[i].vertices[0]].z);
		glVertex3f(x->points[triangle.polygons[i].vertices[2]].x, x->points[triangle.polygons[i].vertices[2]].y, x->points[triangle.polygons[i].vertices[2]].z);
		glEnd();
	}
	//output(cameraX + xLook*10, cameraY + yLook*10, cameraZ + zLook*10,"xxxx");
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

		// when the button is releasedmovedTheta
		if (state == GLUT_UP) {
			xClick = -1;
			yClick = -1;
		}
		else {// state = GLUT_DOWN
			xClick = x;
			yClick = y;
		}
	}
	//glutPostRedisplay();
}
void mouseMove(int x, int y) 
{
	GLfloat radius;
	GLfloat theta;
	GLfloat deltaTheta;
	GLfloat deltaPhi;
	GLfloat phi;
	GLfloat movedTheta;
	GLfloat movedPhi;

	radius = sqrtf(cameraZ * cameraZ + cameraX * cameraX + cameraY * cameraY);
	theta = atan(sqrtf(cameraZ * cameraZ + cameraX * cameraX) / cameraY);
	phi = atan(cameraX / cameraZ);
	if (fixPhi == true)phi += M_PI;
	if (fixTheta == true)theta += M_PI;
	cout << "theta = " << theta;
	deltaTheta = ((yClick - y) / 100.0 * ROTATE_SPEED) * M_PI / 180.0;
	deltaPhi = ((xClick - x) / 100.0 * ROTATE_SPEED) * M_PI / 180.0;

	if (((theta + deltaTheta) > M_PI) || ((theta + deltaTheta) < 0))
	{
		deltaTheta = 0;
	}
	movedTheta = theta + deltaTheta;
	movedPhi = phi + deltaPhi;


	cameraZ = radius * sin(movedTheta) * cos(movedPhi);
	cameraX = radius * sin(movedTheta) * sin(movedPhi);
	cameraY = radius * cos(movedTheta);

	cout << "\tmovedTheta = " << movedTheta << endl;
	if ((fabs(theta) < M_PI_2) && (fabs(movedTheta) > M_PI_2))
	{
		fixTheta = true;
	}
	if ((fabs(theta) > M_PI_2) && (fabs(movedTheta) < M_PI_2))
	{
		fixTheta = false;
	}
	if ((fabs(phi) < M_PI_2) && (fabs(movedPhi) > M_PI_2))
	{
		fixPhi = true;
	}
	if (((fabs(phi) > M_PI_2) && (fabs(movedPhi) < M_PI_2))|| ((fabs(phi) < M_PI + M_PI_2) && (fabs(movedPhi) > M_PI + M_PI_2)))
	{
		fixPhi = false;
	}

	xClick = x;
	yClick = y;
	lookTheta -= deltaTheta;
	lookPhi -= deltaPhi;
	zLook = -sin(lookTheta)*cos(lookPhi);
	xLook = sin(lookTheta)*sin(lookPhi);
	yLook = cos(lookTheta);
	glutPostRedisplay();
}
void Keyboard(unsigned char key, int x, int y)
{
	GLfloat fraction = MOVE_SPEED;
	GLfloat xTemp = cameraX, zTemp = cameraZ;
	switch (key)
	{
	case 'w':
		cameraX += xLook * fraction;
		cameraZ += zLook * fraction;
		cameraY += yLook * fraction;
		break;
	case 's':
		cameraX -= xLook * fraction;
		cameraZ -= zLook * fraction;
		cameraY -= yLook * fraction;
		break;
	case 'a':
		fraction = fmax(fabs(cameraX), fabs(cameraZ)) / fraction;
		cout << "cameraX += " << -zTemp / fraction << endl;
		cout << "cameraZ += " << xTemp / fraction << endl;
		cameraX += -zTemp / fraction;
		cameraZ += xTemp / fraction;
		break;
	case 'd':
		fraction = fmax(fabs(cameraX), fabs(cameraZ)) / fraction;
		cout << "cameraX -= " << -zTemp / fraction << endl;
		cout << "cameraZ -= " << xTemp / fraction << endl;
		cameraX -= -zTemp / fraction;
		cameraZ -= xTemp / fraction;
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
		lookPhi -= 0.1f;
		zLook = -sin(lookTheta)*cos(lookPhi);
		xLook = sin(lookTheta)*sin(lookPhi);
		yLook = cos(lookTheta);
		break;
	case GLUT_KEY_RIGHT:
		lookPhi += 0.1f;
		zLook = -sin(lookTheta)*cos(lookPhi);
		xLook = sin(lookTheta)*sin(lookPhi);
		yLook = cos(lookTheta);
		break;
	case GLUT_KEY_UP:
		if (lookTheta < (M_PI - 0.1))
			lookTheta -= 0.1f;
		zLook = -sin(lookTheta)*cos(lookPhi);
		xLook = sin(lookTheta)*sin(lookPhi);
		yLook = cos(lookTheta);
		break;
		break;
	case GLUT_KEY_DOWN:
		if (lookTheta > 0.1)
			lookTheta += 0.1f;
		zLook = -sin(lookTheta)*cos(lookPhi);
		xLook = sin(lookTheta)*sin(lookPhi);
		yLook = cos(lookTheta);
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
	gp3.reconstruct(triangle);

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