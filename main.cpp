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
#include <Eigen/Geometry>
/*
#define CAMERA_MOVE_SPEED			0.05f			//
#define CAMERA_ROTATE_SPEED			20.0f			//20 deg per 100 pixel
#define VIEWER_WIDTH				1920.0f
#define VIEWER_HEIGHT				1080.0f

pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
pcl::PolygonMesh triangle;

pcl::CentroidPoint<pcl::PointXYZ> centroid;


GLfloat xClick = -1, yClick = -1;

BOOL fixPhi = false;
BOOL fixTheta = false;
BOOL meshFill = false;
uint32_t filename = 1;

std::stringstream fileName;

void mouseMove(int x, int y);
void ChangeSize(int w, int h);
void Display(void);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void ReadStlModel();
void SaveAsBMP(const char *fileName);
void SpecialKeys(int key, int x, int y);

Viewer viewer;


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

void SaveAsBMP(const char *fileName)
{
	FILE *file;
	unsigned long imageSize;
	GLbyte *data = NULL;
	GLint viewPort[4];
	GLenum lastBuffer;
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	bmfh.bfType = 'MB';
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = 54;
	glGetIntegerv(GL_VIEWPORT, viewPort);
	imageSize = ((viewPort[2] + ((4 - (viewPort[2] % 4)) % 4))*viewPort[3] * 3) + 2;
	bmfh.bfSize = imageSize + sizeof(bmfh) + sizeof(bmih);
	data = (GLbyte*)malloc(imageSize);
	glPixelStorei(GL_PACK_ALIGNMENT, 4);
	glPixelStorei(GL_PACK_ROW_LENGTH, 0);
	glPixelStorei(GL_PACK_SKIP_ROWS, 0);
	glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_PACK_SWAP_BYTES, 1);
	glGetIntegerv(GL_READ_BUFFER, (GLint*)&lastBuffer);
	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, viewPort[2], viewPort[3], GL_RGB, GL_UNSIGNED_BYTE, data);
	data[imageSize - 1] = 0;
	data[imageSize - 2] = 0;
	glReadBuffer(lastBuffer);
	file = fopen(fileName, "wb");
	bmih.biSize = 40;
	bmih.biWidth = viewPort[2];
	bmih.biHeight = viewPort[3];
	bmih.biPlanes = 1;
	bmih.biBitCount = 24;
	bmih.biCompression = 0;
	bmih.biSizeImage = imageSize;
	bmih.biXPelsPerMeter = 45089;
	bmih.biYPelsPerMeter = 45089;
	bmih.biClrUsed = 0;
	bmih.biClrImportant = 0;
	fwrite(&bmfh, sizeof(bmfh), 1, file);
	fwrite(&bmih, sizeof(bmih), 1, file);
	fwrite(data, imageSize, 1, file);
	free(data);
	fclose(file);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	glPointSize(1.0);
	glLineWidth(1.0);

	glLoadIdentity();
	xClick = 0;
	mouseMove(5, 0);
	gluLookAt(cameraX, cameraY, cameraZ, cameraX + lookX, cameraY + lookY, cameraZ + lookZ, 0.0f, 1.0f, 0.0f);

	viewer.draw(triangle,false);

	viewer.draw(10, 64, "W S A D : Move camera");
	viewer.draw(10, 48, "Up Down Left Right : Rotate camera");
	viewer.draw(10, 32, "Mouse drag : Rotate object");
	viewer.draw(10, 16, "Mouse scroll : Zoom");


	glutSwapBuffers();

	if (filename < 2)
	{
		std::stringstream ss;
		ss << "../picture/";
		ss << filename++;
		ss << ".bmp";
		SaveAsBMP(&(*ss.str().begin()));
		glutPostRedisplay();
	}
}

void Mouse(int button, int state, int x, int y)
{
	// only start motion if the left button is pressed
	switch (button)
	{
	case GLUT_LEFT_BUTTON:			//Mouse left buttton
		if (state == GLUT_UP) {
			xClick = -1;
			yClick = -1;
		}
		else {
			xClick = x;
			yClick = y;
		}
		break;
	case GLUT_MIDDLE_BUTTON:		//Mouse middle button

		break;
	case GLUT_RIGHT_BUTTON:			//Mouse right button

		break;
	case 3:							//Mouse scroll up

		cameraX += lookX * CAMERA_MOVE_SPEED;
		cameraZ += lookZ * CAMERA_MOVE_SPEED;
		cameraY += lookY * CAMERA_MOVE_SPEED;
		break;
	case 4:							//Mouse scroll down
		cameraX -= lookX * CAMERA_MOVE_SPEED;
		cameraZ -= lookZ * CAMERA_MOVE_SPEED;
		cameraY -= lookY * CAMERA_MOVE_SPEED;
		break;
	default:
		std::cout << "Mouse : " << button << "\tState : " << state << std::endl;
		break;
	}
	glutPostRedisplay();
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
	deltaTheta = ((yClick - y) / 100.0 * CAMERA_ROTATE_SPEED) * M_PI / 180.0;
	deltaPhi = ((xClick - x) / 100.0 * CAMERA_ROTATE_SPEED) * M_PI / 180.0;

	if (((theta + deltaTheta) > M_PI) || ((theta + deltaTheta) < 0))
	{
		deltaTheta = 0;
	}
	movedTheta = theta + deltaTheta;
	movedPhi = phi + deltaPhi;


	cameraZ = radius * sin(movedTheta) * cos(movedPhi);
	cameraX = radius * sin(movedTheta) * sin(movedPhi);
	cameraY = radius * cos(movedTheta);

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
	if (((fabs(phi) > M_PI_2) && (fabs(movedPhi) < M_PI_2)) || ((fabs(phi) < M_PI + M_PI_2) && (fabs(movedPhi) > M_PI + M_PI_2)))
	{
		fixPhi = false;
	}

	xClick = x;
	yClick = y;
	lookTheta -= deltaTheta;
	lookPhi -= deltaPhi;
	lookZ = -sin(lookTheta)*cos(lookPhi);
	lookX = sin(lookTheta)*sin(lookPhi);
	lookY = cos(lookTheta);
	glutPostRedisplay();
}
void Keyboard(unsigned char key, int x, int y)
{
	GLfloat fraction = CAMERA_MOVE_SPEED;
	GLfloat xTemp = cameraX, zTemp = cameraZ;
	switch (key)
	{
	case 'w':
		cameraX += lookX * CAMERA_MOVE_SPEED;
		cameraZ += lookZ * CAMERA_MOVE_SPEED;
		cameraY += lookY * CAMERA_MOVE_SPEED;
		break;
	case 's':
		cameraX -= lookX * CAMERA_MOVE_SPEED;
		cameraZ -= lookZ * CAMERA_MOVE_SPEED;
		cameraY -= lookY * CAMERA_MOVE_SPEED;
		break;
	case 'a':
		fraction = fmax(fabs(cameraX), fabs(cameraZ)) / CAMERA_MOVE_SPEED;
		cameraX += -zTemp / fraction;
		cameraZ += xTemp / fraction;
		break;
	case 'd':
		fraction = fmax(fabs(cameraX), fabs(cameraZ)) / CAMERA_MOVE_SPEED;
		cameraX -= -zTemp / fraction;
		cameraZ -= xTemp / fraction;
		break;
	case 'f':

		meshFill = !meshFill;
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
		lookZ = -sin(lookTheta)*cos(lookPhi);
		lookX = sin(lookTheta)*sin(lookPhi);
		lookY = cos(lookTheta);
		break;
	case GLUT_KEY_RIGHT:
		lookPhi += 0.1f;
		lookZ = -sin(lookTheta)*cos(lookPhi);
		lookX = sin(lookTheta)*sin(lookPhi);
		lookY = cos(lookTheta);
		break;
	case GLUT_KEY_UP:
		if (lookTheta < (M_PI - 0.1))
			lookTheta -= 0.1f;
		lookZ = -sin(lookTheta)*cos(lookPhi);
		lookX = sin(lookTheta)*sin(lookPhi);
		lookY = cos(lookTheta);
		break;
		break;
	case GLUT_KEY_DOWN:
		if (lookTheta > 0.1)
			lookTheta += 0.1f;
		lookZ = -sin(lookTheta)*cos(lookPhi);
		lookX = sin(lookTheta)*sin(lookPhi);
		lookY = cos(lookTheta);
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
*/
int main(int argc, char* argv[])
{
	/*
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