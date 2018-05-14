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

enum PlayMode {Once,OnceKeepCache, Loop};

class Viewer
{
private:
	GLfloat theta;
	GLfloat phi;
	GLfloat radius;
	Eigen::Vector3f location;
	Eigen::Vector3f look;
public:
	Viewer();
	void Mouse(int button, int state, int x, int y);
	void mouseMove(int x, int y);
	void ChangeSize(int w, int h);
	void Display(void);
	void Keyboard(unsigned char key, int x, int y);
	void SpecialKeys(int key, int x, int y);
	void draw(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);		// Draw point cloud
	void draw(pcl::PolygonMesh &mesh, BOOL fill);							// Draw mesh
	void draw(GLfloat x, GLfloat y, std::string s);				// Draw caption
	void ratation(GLfloat theta, GLfloat phi);
	void moveAroud(GLfloat theta, GLfloat phi);
	void screenshot(std::string fileName);
};
#endif // VIEWER_H
