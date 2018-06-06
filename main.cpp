#include <iostream>
#include <fstream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <pcl/surface/poisson.h>
#include <math.h>
#include <vector>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <wingdi.h>
#include "include/viewer.h"
#include <thread>

#define VIEWER_WIDTH 1024.0f
#define VIEWER_HEIGHT 768.0f

pcl::PolygonMesh triangle;
std::stringstream fileName;

Viewer *viewer = new Viewer;

void Mouse(int button, int state, int x, int y);
void mouseMove(int x, int y);
void ChangeSize(int w, int h);
void Display(void);
void Keyboard(unsigned char key, int x, int y);
void SpecialKeys(int key, int x, int y);
void triangulation(pcl::PolygonMesh &triangle, std::string str);
void poission_surface(pcl::PolygonMesh &poission, std::string str);
//void poission(const pcl::PCLPointCloud2::ConstPtr &input, pcl::PolygonMesh &output,	int depth, int solver_divide, int iso_divide, float point_weight)
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
void triangulation(pcl::PolygonMesh &triangle, std::string str)
{

	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PCLPointCloud2 cloud_blob;
	pcl::io::loadPCDFile(&(*str.begin()), cloud_blob);
	pcl::fromPCLPointCloud2(cloud_blob, *cloud);


	pcl::CentroidPoint<pcl::PointXYZ> centroid;
	pcl::PointXYZ cent;
	for (size_t i = 0; i < cloud->points.size(); i++)
	{
		centroid.add(cloud->points[i]);
	}
	centroid.get(cent);
	//std::cout << cent << std::endl;
	for (size_t i = 0; i < cloud->points.size(); i++)
	{
		cloud->points[i].x -= cent.x;
		cloud->points[i].y -= cent.y;
		cloud->points[i].z -= cent.z;
	}
	//viewer->Buffer.push(triangle);
	//* the data should be available in cloud

	// Normal estimation*
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
	tree->setInputCloud(cloud);
	n.setInputCloud(cloud);
	n.setSearchMethod(tree);
	n.setKSearch(30);
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
	gp3.setSearchRadius(50);

	// Set typical values for the parameters
	gp3.setMu(2.5);
	gp3.setMaximumNearestNeighbors(300);
	gp3.setMaximumSurfaceAngle(M_PI / 2); // 45 degrees
	gp3.setMinimumAngle(M_PI / 36); // 10 degrees
	gp3.setMaximumAngle(5 * M_PI / 6); // 120 degrees
	gp3.setNormalConsistency(false);

	// Get result
	gp3.setInputCloud(cloud_with_normals);
	gp3.setSearchMethod(tree2);
	gp3.reconstruct(triangle);
}
//void poission(const pcl::PCLPointCloud2::ConstPtr &input, pcl::PolygonMesh &output,int depth, int solver_divide, int iso_divide, float point_weight)
void poission_surface(pcl::PolygonMesh &poission, std::string str)
{

	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PCLPointCloud2 cloud_blob;
	pcl::io::loadPCDFile(&(*str.begin()), cloud_blob);
	pcl::fromPCLPointCloud2(cloud_blob, *cloud);


	pcl::CentroidPoint<pcl::PointXYZ> centroid;
	pcl::PointXYZ cent;
	for (size_t i = 0; i < cloud->points.size(); i++)
	{
		centroid.add(cloud->points[i]);
	}
	centroid.get(cent);
	//std::cout << cent << std::endl;
	for (size_t i = 0; i < cloud->points.size(); i++)
	{
		cloud->points[i].x -= cent.x;
		cloud->points[i].y -= cent.y;
		cloud->points[i].z -= cent.z;
	}
	//viewer->Buffer.push(triangle);
	//* the data should be available in cloud

	// Normal estimation*
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
	tree->setInputCloud(cloud);
	n.setInputCloud(cloud);
	n.setSearchMethod(tree);
	n.setKSearch(30);
	n.compute(*normals);
	//* normals should not contain the point normals + surface curvatures

	// Concatenate the XYZ and normal fields*
	pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>);
	pcl::concatenateFields(*cloud, *normals, *cloud_with_normals);
	//* cloud_with_normals = cloud + normals
	// Create search tree*
	pcl::search::KdTree<pcl::PointNormal>::Ptr tree2(new pcl::search::KdTree<pcl::PointNormal>);
	tree2->setInputCloud(cloud_with_normals);

	pcl::Poisson<pcl::PointNormal> poisson;
	poisson.setDepth(8);
	poisson.setSolverDivide(8);
	poisson.setIsoDivide(8);
	poisson.setPointWeight(4.0f);
	poisson.setInputCloud(cloud_with_normals);

	poisson.reconstruct(poission);
}
void t1()
{
	while (1)
	{
		std::cout << "thread1" << std::endl;
		Sleep(1000);
	}
}
int main(int argc, char* argv[])
{
	HANDLE thread1;
	DWORD tID1;
	thread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)t1, 0, 0, &tID1);
	//pcl::PolygonMesh triangle;
	//viewer->Buffer.push(triangle);

	//triangulation(triangle, "../file/75.pcd");
<<<<<<< HEAD
	for (size_t i = 50; i < 55; i += 5)
=======
	for (size_t i = 50; i <= 75; i += 5)
>>>>>>> master
	{
		pcl::PolygonMesh triangle;
		std::stringstream str;
		str << "../file/";
		str << i;
		str << ".pcd";
		//triangulation(triangle, str.str());
		poission_surface(triangle, str.str());
		viewer->Buffer.push(triangle);
	}
<<<<<<< HEAD
	/*for (size_t i = 100; i > 50; i -= 5)
=======
	for (size_t i = 70; i >= 50; i -= 5)
>>>>>>> master
	{
		pcl::PolygonMesh triangle;
		std::stringstream str;
		str << "../file/";
		str << i;
		str << ".pcd";
		triangulation(triangle, str.str());
		viewer->Buffer.push(triangle);
	}*/
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
	pcl::PolygonMesh temp;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);

	gluLookAt(viewer->location.getY(), viewer->location.getZ(), viewer->location.getX(), viewer->location.getY() + viewer->look.getY(), viewer->location.getZ() + viewer->look.getZ(), viewer->location.getX() + viewer->look.getX(), 0.0f, 1.0f, 0.0f);

	if (viewer->mode == Start)
	{
		if ((clock() - viewer->count) > (1000 / viewer->FPS))
		{
			temp = viewer->Buffer.front();
			viewer->Buffer.pop();
			viewer->draw(temp, true);
			viewer->Buffer.push(temp);
			viewer->count = clock();
<<<<<<< HEAD
		}
		else
		{
			viewer->draw(viewer->Buffer.back(), true);
		}
=======
		}
		else
		{
			viewer->draw(viewer->Buffer.back(), false);
		}
>>>>>>> master
		glutPostRedisplay();
	}
	else if (viewer->mode == Stop)
	{
		viewer->draw(viewer->Buffer.front(), false);
		glutPostRedisplay();
	}
	viewer->draw(10, 64, "W S A D : Move camera");
	viewer->draw(10, 48, "Up Down Left Right : Rotate camera");
	viewer->draw(10, 32, "Mouse drag : Rotate object");
	viewer->draw(10, 16, "Mouse scroll : Zoom");

	glutSwapBuffers();
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
	case 3:		viewer->move(Forward);	break;
	case 4:		viewer->move(Backward);	break;
	default:	std::cout << "Mouse : " << button << "\tState : " << state << std::endl;	break;
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
	case 'w':	viewer->move(Forward);	break;
	case 's':	viewer->move(Backward);	break;
	case 'a':	viewer->move(Left);		break;
	case 'd':	viewer->move(Right);	break;
	case 'f':
		viewer->look.theta = M_PI - viewer->location.theta;
		viewer->look.phi = viewer->location.phi + M_PI;
		break;
		//case '1':   viewer->mode == Start;  break;
		//case '2':   viewer->mode == Stop;   break;
	case 32:
		if (viewer->mode == Start)
			viewer->mode = Stop;
		else
			viewer->mode = Start;
		break;

	default:	printf("   Keyboard %c == %d\n", key, key);	break;

	}
	glutPostRedisplay();
}
void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:		viewer->rotation(0.0, 1.0);		break;
	case GLUT_KEY_RIGHT:	viewer->rotation(0.0, -1.0);	break;
	case GLUT_KEY_UP:		viewer->rotation(-1.0, 0.0);	break;
	case GLUT_KEY_DOWN:		viewer->rotation(1.0, 0.0);		break;
	}
	glutPostRedisplay();
}
