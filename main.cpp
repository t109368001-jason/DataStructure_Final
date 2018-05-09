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
#include<Windows.h>    
#include<stdio.h>    
#include<gl/GL.h>  
#include<gl/GLU.h> 
#include<gl/glut.h>
#include<conio.h>    
#include<stdio.h>    
#include<math.h>    
#include<string.h>    

pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
pcl::PolygonMesh triangles;

pcl::CentroidPoint<pcl::PointXYZ> centroid;

static GLfloat xRot = 45.0f;
static GLfloat yRot = 45.0f;
static GLfloat zRot = 45.0f;

void RenderScene(void)
{
	//清除
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//保存矩陣 
	glPushMatrix();

	//旋轉 
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);

	glPointSize(1.0);
	glColor3f(1.0, 1.0, 1.0);

	glLineWidth(1.0);

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
void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':	zRot -= 5.0f;	break;
	case 's':	zRot += 5.0f;	break;
		/*
		case 'j': d[0] += 0.1;  break;
		case 'k': d[1] += 0.1;  break;
		case 'l': d[2] += 0.1;  break;

		case 'x': xAngle += 5;  break;
		case 'y': yAngle += 5;  break;
		case 'z': zAngle += 5;  break;*/

	default: printf("   Keyboard %c == %d\n", key, key);

	}

	glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;

	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if (key == GLUT_KEY_PAGE_UP)
		glScalef(1.25, 1.25, 1.25);

	if (key == GLUT_KEY_PAGE_DOWN)
		glScalef(0.8, 0.8, 0.8);

	if (key > 356.0f)
		xRot = 0.0f;

	if (key < -1.0f)
		xRot = 355.0f;

	if (key > 356.0f)
		yRot = 0.0f;

	if (key < -1.0f)
		yRot = 355.0f;

	// Refresh the Window
	glutPostRedisplay();
}


void ChangeSize(int w, int h)
{
	GLfloat fAspect;
	pcl::PointXYZ x;
	centroid.get(x);

	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	fAspect = (GLfloat)w / (GLfloat)h;
	gluPerspective(35.0f, fAspect, 1.0f, 1000.0f);
	//glOrtho(-400+x.x, 400-x.x, -400+x.y, 400-x.y, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -1000.0f);
}
int main(int argc, char* argv[])
{
	// Load input file into a PointCloud<T> with an appropriate type
	pcl::PCLPointCloud2 cloud_blob;
	pcl::io::loadPCDFile("bunny.pcd", cloud_blob);
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
	GLenum type;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("RGB Cube");
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
	return 0;
}