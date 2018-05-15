#ifndef SPHERE_H  
#define SPHERE_H  

#include <pcl/point_types.h>
#include <gl/glut.h>
class Sphere
{
public:
	GLfloat radius;
	GLfloat theta;
	GLfloat phi;
	Sphere();
	Sphere(GLfloat radius, GLfloat theta, GLfloat phi);
	GLfloat getX();
	GLfloat getY();
	GLfloat getZ();
	Eigen::Vector3f getVector();
	void set(Eigen::Vector3f v);
	BOOL checkTheta(GLfloat deltaTheta);
};

#endif // SPHERE_H
