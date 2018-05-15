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

#define CAMERA_MOVE_SPEED		0.05f
#define CAMERA_ROTATE_SPEED		10.0f
#define CAMERA_ROTATE_PRE_PIXEL	50.0f

enum PlayMode { Once, OnceKeepCache, Loop };

class Sphere
{
public:
	GLfloat radius;
	GLfloat theta;
	GLfloat phi;
	Sphere()
	{

	}
	Sphere(GLfloat radius, GLfloat theta, GLfloat phi)
	{
		this->radius = radius;
		this->theta = theta;
		this->phi = phi;
	}
	GLfloat getX()
	{
		return this->radius*sin(this->theta)*cos(this->phi);
	}
	GLfloat getY()
	{
		return this->radius*sin(this->theta)*sin(this->phi);
	}
	GLfloat getZ()
	{
		return this->radius*cos(this->theta);
	}
	Eigen::Vector3f getVector()
	{
		return Eigen::Vector3f(this->getX(), this->getY(), this->getZ());
	}
	void set(Eigen::Vector3f v)
	{
		this->radius = v.norm();
		this->theta = acos(v.dot(Eigen::Vector3f::UnitZ()) / v.norm() / Eigen::Vector3f::UnitZ().norm());
		this->phi = Eigen::Vector3f(v.dot(Eigen::Vector3f::UnitX()),v.dot(Eigen::Vector3f::UnitY()), 0).dot(Eigen::Vector3f::UnitX())/v.norm()/ Eigen::Vector3f(v.dot(Eigen::Vector3f::UnitX()), v.dot(Eigen::Vector3f::UnitY()), 0).norm();
	}
	void fixTheta()
	{
		if (this->theta < 0.0)
		{
			this->theta = 0.0;
		}
		if (this->theta > M_PI)
		{
			this->theta;
		}
	}
};

class Viewer
{
public:
	Sphere location;
	Sphere look;
	GLfloat xClick;
	GLfloat yClick;
	Viewer();
<<<<<<< HEAD
    std::queue<pcl::PolygonMesh> Buffer;
	void Mouse(int button, int state, int x, int y);
	void mouseMove(int x, int y);
	void ChangeSize(int w, int h);
	void Display(void);
	void Keyboard(unsigned char key, int x, int y);
	void SpecialKeys(int key, int x, int y);
=======
>>>>>>> master
	void draw(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);		// Draw point cloud
	void draw(pcl::PolygonMesh &mesh, BOOL fill);							// Draw mesh
	void draw(GLfloat x, GLfloat y, std::string s);				// Draw caption
	void rotation(GLfloat theta, GLfloat phi);
	void moveAroud(GLfloat theta, GLfloat phi);
	void screenshot(std::string fileName);

};
#endif // VIEWER_H
