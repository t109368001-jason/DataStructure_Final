#ifndef VIEWER_H  
#define VIEWER_H  

//#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
//#include <pcl/kdtree/kdtree_flann.h>
//#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
//#include <gl/GL.h>
//#include <gl/GLU.h>
#include <gl/glut.h>

class Viewer
{
private:
	pcl::Vector3fMap location;
	pcl::Vector3fMap look;
public:
	Viewer();
	void draw(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);		// Draw point cloud
	void draw(pcl::PolygonMesh &mesh, BOOL fill);							// Draw mesh
	void draw(GLfloat x, GLfloat y, std::string s);				// Draw caption
	void ratation(GLfloat theta, GLfloat phi);
	void moveAroud(GLfloat theta, GLfloat phi);
	void screenshot(std::string fileName);

};
#endif // VIEWER_H
