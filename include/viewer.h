#ifndef VIEWER_H  
#define VIEWER_H  

#include <pcl/point_types.h>
#include <pcl/surface/gp3.h>
#include <pcl/common/centroid.h>
#include <gl/glut.h>
#include <time.h>
#include "sphere.h"

#define CAMERA_MOVE_SPEED		0.05f
#define CAMERA_ROTATE_SPEED		10.0f
#define CAMERA_ROTATE_PRE_PIXEL	50.0f

enum ModeDirection { Forward, Backward, Left, Right };

enum PlayMode { Play, Pause };

class Viewer
{
public:
	clock_t count;
	Sphere location;
	Sphere look;
	GLfloat xClick;
	GLfloat yClick;
	GLfloat FPS;
	PlayMode mode;
	BOOL fill;
	std::queue<pcl::PolygonMesh> Buffer;
	Viewer();
	void Viewer::draw(pcl::PCLPointCloud2 cloud2);		// Draw point cloud
	void draw(pcl::PolygonMesh &mesh, BOOL fill);							// Draw mesh
	void draw(GLfloat x, GLfloat y, std::string s);				// Draw caption
	void rotation(GLfloat theta, GLfloat phi);
	void move(ModeDirection direction);
	void moveAroud(GLfloat theta, GLfloat phi);
	void screenshot();
	void screenshot(std::string fileName);
};
#endif // VIEWER_H
