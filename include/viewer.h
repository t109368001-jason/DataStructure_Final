#ifndef VIEWER_H  
#define VIEWER_H  

#include <pcl/point_types.h>
#include <pcl/surface/gp3.h>
#include <gl/glut.h>
#include "sphere.h"

#define CAMERA_MOVE_SPEED		0.05f
#define CAMERA_ROTATE_SPEED		10.0f
#define CAMERA_ROTATE_PRE_PIXEL	50.0f

enum PlayMode { Once, OnceKeepCache, Loop };
enum ModeDirection { Forward, Backward, Left, Right };

class Viewer
{
public:
	Sphere location;
	Sphere look;
	GLfloat xClick;
	GLfloat yClick;
	Viewer();
    std::queue<pcl::PolygonMesh> Buffer;
	void draw(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);		// Draw point cloud
	void draw(pcl::PolygonMesh &mesh, BOOL fill);							// Draw mesh
	void draw(GLfloat x, GLfloat y, std::string s);				// Draw caption
	void rotation(GLfloat theta, GLfloat phi);
	void move(ModeDirection direction);
	void moveAroud(GLfloat theta, GLfloat phi);
	void screenshot(std::string fileName);

};
#endif // VIEWER_H
