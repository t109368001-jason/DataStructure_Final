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

std::stringstream fileName;

Viewer viewer;

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
	/*

	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PolygonMesh triangle;
	// Load input file into a PointCloud<T> with an appropriate type
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
	*/
	system("pause");
	return 0;
}