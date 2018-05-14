#include "viewer.h"
Viewer::Viewer()
{

	GLfloat lookPhi = 0.0;
	GLfloat lookTheta = M_PI_2;
	GLfloat textDeltaPhi = -M_PI / 18.0;
	GLfloat textDeltaTheta = M_PI / 18.0;

	GLfloat lookX = 0.0f, lookZ = -1.0f, lookY = 0.0;
	GLfloat cameraX = 0.0f, cameraZ = 1.0f, cameraY = 0.0f;
	this->location;
}
void Viewer::draw(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)		//Draw pointClouds
{
	for (size_t i = 0; i < cloud->points.size(); ++i)
	{

		glBegin(GL_POINTS);
		glVertex3f(cloud->points[i].x, cloud->points[i].y, cloud->points[i].z);
		glEnd();
	}
}
void Viewer::draw(pcl::PolygonMesh &mesh, BOOL fill)		//Draw mesh
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::fromPCLPointCloud2(mesh.cloud, *cloud);

	for (size_t i = 0; i < mesh.polygons.size() - 1; ++i)
	{
		if (fill)
		{
			//有BUG的光影
			//std::cout << triangle.cloud.data[i + 0] << "\t" << triangle.cloud.data[i + 0] << "\t" << triangle.cloud.data[i + 0] << std::endl;
			GLfloat line1X = cloud->points[mesh.polygons[i].vertices[0]].x - cloud->points[mesh.polygons[i].vertices[1]].x;
			GLfloat line1Y = cloud->points[mesh.polygons[i].vertices[0]].y - cloud->points[mesh.polygons[i].vertices[1]].y;
			GLfloat line1Z = cloud->points[mesh.polygons[i].vertices[0]].z - cloud->points[mesh.polygons[i].vertices[1]].z;
			GLfloat line2X = cloud->points[mesh.polygons[i].vertices[1]].x - cloud->points[mesh.polygons[i].vertices[2]].x;
			GLfloat line2Y = cloud->points[mesh.polygons[i].vertices[1]].y - cloud->points[mesh.polygons[i].vertices[2]].y;
			GLfloat line2Z = cloud->points[mesh.polygons[i].vertices[1]].z - cloud->points[mesh.polygons[i].vertices[2]].z;
			GLfloat nX = line1Y * line2Z - line2Y * line1Z;
			GLfloat nY = line1Z * line2X - line2Z * line1X;
			GLfloat nZ = line1X * line2Y - line2X * line1Y;
			GLfloat theta = acos((nX * this->location.x() + nY * this->location.y() + nZ * this->location.z()) / sqrtf(nX*nX + nY * nY + nZ * nZ) / sqrtf(this->location.x() * this->location.x() + this->location.y() *this->location.y() + this->location.z() * this->location.z()));
			if (acos((nX * cloud->points[mesh.polygons[i].vertices[0]].x + nY * cloud->points[mesh.polygons[i].vertices[0]].y + nZ * cloud->points[mesh.polygons[i].vertices[0]].z) / sqrtf(nX * nX + nY * nY + nZ * nZ) / sqrtf(cloud->points[mesh.polygons[i].vertices[0]].x * cloud->points[mesh.polygons[i].vertices[0]].x + cloud->points[mesh.polygons[i].vertices[0]].y * cloud->points[mesh.polygons[i].vertices[0]].y + cloud->points[mesh.polygons[i].vertices[0]].z * cloud->points[mesh.polygons[i].vertices[0]].z)) < M_PI_2)
			{
				theta = (M_PI - theta);
			}
			glColor3f(theta / M_PI, theta / M_PI, theta / M_PI);

			glBegin(GL_TRIANGLES);
			glVertex3f(cloud->points[mesh.polygons[i].vertices[0]].x, cloud->points[mesh.polygons[i].vertices[0]].y, cloud->points[mesh.polygons[i].vertices[0]].z);
			glVertex3f(cloud->points[mesh.polygons[i].vertices[1]].x, cloud->points[mesh.polygons[i].vertices[1]].y, cloud->points[mesh.polygons[i].vertices[1]].z);
			glVertex3f(cloud->points[mesh.polygons[i].vertices[2]].x, cloud->points[mesh.polygons[i].vertices[2]].y, cloud->points[mesh.polygons[i].vertices[2]].z);
			glEnd();
		}
		else
		{
			glBegin(GL_LINES);
			glVertex3f(cloud->points[mesh.polygons[i].vertices[0]].x, cloud->points[mesh.polygons[i].vertices[0]].y, cloud->points[mesh.polygons[i].vertices[0]].z);
			glVertex3f(cloud->points[mesh.polygons[i].vertices[1]].x, cloud->points[mesh.polygons[i].vertices[1]].y, cloud->points[mesh.polygons[i].vertices[1]].z);
			glVertex3f(cloud->points[mesh.polygons[i].vertices[2]].x, cloud->points[mesh.polygons[i].vertices[2]].y, cloud->points[mesh.polygons[i].vertices[2]].z);
			glVertex3f(cloud->points[mesh.polygons[i].vertices[0]].x, cloud->points[mesh.polygons[i].vertices[0]].y, cloud->points[mesh.polygons[i].vertices[0]].z);
			glEnd();
		}
	}
}
void Viewer::draw(GLfloat x, GLfloat y, std::string s)		//Draw text
{
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH) , 0.0, glutGet(GLUT_WINDOW_HEIGHT));
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);//needs to be called before RasterPos
	glRasterPos2f(x, y);
	void * font = GLUT_BITMAP_9_BY_15;

	for (std::string::iterator i = s.begin(); i != s.end(); ++i)
	{
		char c = *i;
		//this does nothing, color is fixed for Bitmaps when calling glRasterPos
		//glColor3f(1.0, 0.0, 1.0); 
		glutBitmapCharacter(font, c);
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}