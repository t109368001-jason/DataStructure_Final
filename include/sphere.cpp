#include "sphere.h"

Sphere::Sphere()
{
	this->radius = 1;
	this->theta = 0;
	this->phi = 0;
}
Sphere::Sphere(GLfloat radius, GLfloat theta, GLfloat phi)
{
	this->radius = radius;
	this->theta = theta;
	this->phi = phi;
}
GLfloat Sphere::getX()
{
	return this->radius*sin(this->theta)*cos(this->phi);
}
GLfloat Sphere::getY()
{
	return this->radius*sin(this->theta)*sin(this->phi);
}
GLfloat Sphere::getZ()
{
	return this->radius*cos(this->theta);
}
Eigen::Vector3f Sphere::getVector()
{
	return Eigen::Vector3f(this->getX(), this->getY(), this->getZ());
}
void Sphere::set(Eigen::Vector3f v)
{
	this->radius = v.norm();
	this->theta = acos(v.dot(Eigen::Vector3f::UnitZ()) / v.norm() / Eigen::Vector3f::UnitZ().norm());
	this->phi = atan(v[1] / v[0]);
	if (v[0] < 0.0)
		this->phi = -this->phi;
}
void Sphere::fixTheta()
{
	if (this->theta < 0.0)
	{
		this->theta = 0.0;
	}
	if (this->theta > M_PI)
	{
		this->theta = M_PI;
	}
}