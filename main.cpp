#include <iostream>
#include <fstream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <math.h>
#include <vector>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <wingdi.h>
#include "include\viewer.h"

#define VIEWER_WIDTH 1024.0f
#define VIEWER_HEIGHT 768.0f

std::stringstream fileName;

Viewer *viewer = new Viewer;
pcl::PolygonMesh triangle;

void Mouse(int button, int state, int x, int y);
void mouseMove(int x, int y);
void ChangeSize(int w, int h);
void Display(void);
void Keyboard(unsigned char key, int x, int y);
void SpecialKeys(int key, int x, int y);

/*
void ReadStlModel()
{
	//ifstream infile("C:\\Users\\FrankFang\\Desktop\\stl.txt");
	std::ifstream infile("C:\\Users\\FrankFang\\Desktop\\mode.stl");
	if (!infile.is_open())
	{
		return;
	}
	std::string temp, modelname;

	char dump[256];
	int trinumber = 0;
	std::vector<std::vector<GLfloat>> tempTriAngle;
	infile >> temp;
	int test = temp.compare("solid");
	if (test != 0)
	{
		return;
	}

	infile.getline(dump, 25);
	infile >> temp;
	while (temp.compare("facet") == 0)
	{
		trinumber++;//三角形数目
		infile >> temp;//get rid of "normal "
		infile >> tempTriAngle.NormDir.x;
		infile >> tempTriAngle.NormDir.y;
		infile >> tempTriAngle.NormDir.z;

		infile.getline(dump, 256); infile.getline(dump, 256);//get rid of "outer loop"
		for (int i = 0; i<3; i++)
		{
			infile >> temp;
			infile >> tempTriAngle.vertex[i].x;
			infile >> tempTriAngle.vertex[i].y;
			infile >> tempTriAngle.vertex[i].z;
			//tempTriAngle.push_back(temppoint[i]);
		}
		TrangleVector.push_back(tempTriAngle);
		infile >> temp;
		infile >> temp;
		infile >> temp;
	}//while()
}
*/

int main(int argc, char* argv[])
{
<<<<<<< HEAD


	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PolygonMesh triangle;

	/*	// Load input file into a PointCloud<T> with an appropriate type
=======
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	// Load input file into a PointCloud<T> with an appropriate type
>>>>>>> master
	pcl::PCLPointCloud2 cloud_blob;
	pcl::io::loadPCDFile("../file/bunny.pcd", cloud_blob);
	pcl::fromPCLPointCloud2(cloud_blob, *cloud);
	//* the data should be available in cloud

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
	glutInitWindowSize(VIEWER_WIDTH, VIEWER_HEIGHT);
	glutCreateWindow("Point Clout Viewer");
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(mouseMove);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(Display);

	glutMainLoop();
	return 0;
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	glPointSize(1.0);
	glLineWidth(1.0);

	glLoadIdentity();
	//viewer->xClick = 0;
	//mouseMove(5, 0);

	gluLookAt(viewer->location.getY(), viewer->location.getZ(), viewer->location.getX(), viewer->location.getY() + viewer->look.getY(), viewer->location.getZ() + viewer->look.getZ(), viewer->location.getX() + viewer->look.getX(), 0.0f, 1.0f, 0.0f);
	std::cout << viewer->location.radius << "\t";
	std::cout << viewer->location.theta << "\t";
	std::cout << viewer->location.phi << "\t";
	std::cout << viewer->look.radius << "\t";
	std::cout << viewer->look.theta << "\t";
	std::cout << viewer->look.phi << "\t";
	std::cout << std::endl;
	std::cout << std::endl;
	viewer->draw(triangle, false);

	viewer->draw(10, 64, "W S A D : Move camera");
	viewer->draw(10, 48, "Up Down Left Right : Rotate camera");
	viewer->draw(10, 32, "Mouse drag : Rotate object");
	viewer->draw(10, 16, "Mouse scroll : Zoom");


	glutSwapBuffers();
	/*
	if (filename < 2)
	{
	std::stringstream ss;
	ss << "../picture/";
	ss << filename++;
	ss << ".bmp";
	SaveAsBMP(&(*ss.str().begin()));
	glutPostRedisplay();
	}*/
}
void ChangeSize(int w, int h)
{
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
void Mouse(int button, int state, int x, int y)
{
	// only start motion if the left button is pressed
	switch (button)
	{
	case GLUT_LEFT_BUTTON:			//Mouse left buttton
		if (state == GLUT_UP) {
			viewer->xClick = -1;
			viewer->yClick = -1;
		}
		else {
			viewer->xClick = x;
			viewer->yClick = y;
		}
		break;
	case GLUT_MIDDLE_BUTTON:		//Mouse middle button

		break;
	case GLUT_RIGHT_BUTTON:			//Mouse right button

		break;
	case 3:							//Mouse scroll up

		break;
	case 4:							//Mouse scroll down

		break;
	default:
		std::cout << "Mouse : " << button << "\tState : " << state << std::endl;
		break;
	}
	glutPostRedisplay();
}
void mouseMove(int x, int y)
{
	viewer->moveAroud(x, y);
	glutPostRedisplay();
}
void Keyboard(unsigned char key, int x, int y)
{
	GLfloat fraction = CAMERA_MOVE_SPEED;
	switch (key)
	{
	case 'w':
		viewer->location.set(viewer->location.getVector() + viewer->look.getVector()*CAMERA_MOVE_SPEED);
		break;
	case 's':
		viewer->location.set(viewer->location.getVector() - viewer->look.getVector()*CAMERA_MOVE_SPEED);
		break;
	case 'a':
		break;
	case 'd':

		break;
	case 'f':

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
		viewer->rotation(0.0, 1.0);
		break;
	case GLUT_KEY_RIGHT:
		viewer->rotation(0.0, -1.0);
		break;
	case GLUT_KEY_UP:
		viewer->rotation(-1.0, 0.0);
		break;
	case GLUT_KEY_DOWN:
		viewer->rotation(1.0, 0.0);
		break;
	}
	glutPostRedisplay();
}