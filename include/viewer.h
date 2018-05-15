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

#define CAMERA_MOVE_SPEED 0.05f
#define CAMERA_ROTATE_SPEED 20.0f

enum PlayMode { Once, OnceKeepCache, Loop };

class Sphere
{
private:
	GLfloat radius;
	GLfloat theta;
	GLfloat phi;
public:
	Sphere()
	{

	}
	Sphere(GLfloat radius, GLfloat theta, GLfloat phi)
	{
		this->radius = radius;
		this->theta = theta;
		this->phi = phi;
	}
	GLfloat getRadius()
	{
		return this->radius;
	}
	GLfloat getTheta()
	{
		return this->radius;
	}
	GLfloat getPhi()
	{
		return this->radius;
	}
	void setRadius(GLfloat radius)
	{
		this->radius = radius;
	}
	void setTheta(GLfloat theta)
	{
		this->theta = theta;
	}
	void setPhi(GLfloat phi)
	{
		this->phi = phi;
	}

	GLfloat getX()
	{
		return this->radius*sin(this->getTheta)*cos(this->phi);
	}
	GLfloat getY()
	{
		return this->radius*sin(this->getTheta)*sin(this->phi);
	}
	GLfloat getZ()
	{
		return this->radius*cos(this->getTheta);
	}
	Eigen::Vector3f getVector()
	{
		return Eigen::Vector3f(this->getX(), this->getY(), this->getZ());
	}
	void set(Eigen::Vector3f v)
	{
		this->radius = v.norm();
		this->theta = v.dot(Eigen::Vector3f::UnitY()) / v.norm() / Eigen::Vector3f::UnitY().norm();
		this->phi = v.
	}
};

class Viewer
{
private:
	Sphere location;
	Sphere look;
	GLfloat xClick;
	GLfloat yClick;
public:
	Viewer();
    std::queue<pcl::PolygonMesh> Buffer;
	void Mouse(int button, int state, int x, int y);
	void mouseMove(int x, int y);
	void ChangeSize(int w, int h);
	void Display(void);
	void Keyboard(unsigned char key, int x, int y);
	void SpecialKeys(int key, int x, int y);
	void draw(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);		// Draw point cloud
	void draw(pcl::PolygonMesh &mesh, BOOL fill);							// Draw mesh
	void draw(GLfloat x, GLfloat y, std::string s);				// Draw caption
	void rotation(GLfloat theta, GLfloat phi);
	void moveAroud(GLfloat theta, GLfloat phi);
	void screenshot(std::string fileName);

};
#endif // VIEWER_H
