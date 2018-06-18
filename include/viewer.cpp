#include "viewer.h"

struct triangle
{
	float distanse;
	Eigen::Vector3f normal;
	std::vector<uint32_t> vertices;
};

bool compFunc(triangle &a, triangle &b) { return a.distanse > b.distanse; }

Viewer::Viewer()
{
	this->location.radius = 1.0;
	this->location.theta = M_PI_2;
	this->location.phi = 0.0;
	this->look.radius = CAMERA_MOVE_SPEED;
	this->look.theta = M_PI_2;
	this->look.phi = M_PI;
<<<<<<< HEAD
	this->mode = Start;
=======
	this->mode = Pause;
>>>>>>> master
	this->FPS = 30;
	this->count = 0;
	this->fill = true;
}

void Viewer::draw(pcl::PCLPointCloud2 cloud2)		//Draw pointClouds
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::fromPCLPointCloud2(cloud2, *cloud);
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
	if (fill && (mesh.polygons.size() > 2))
	{
		/*std::vector<triangle> sortVector;
		for (size_t i = 0; i < mesh.polygons.size(); i++)
		{
			triangle temp;
			Eigen::Vector3f line1 = cloud->points[mesh.polygons[i].vertices[0]].getVector3fMap() - cloud->points[mesh.polygons[i].vertices[1]].getVector3fMap();
			Eigen::Vector3f line2 = cloud->points[mesh.polygons[i].vertices[1]].getVector3fMap() - cloud->points[mesh.polygons[i].vertices[2]].getVector3fMap();
			Eigen::Vector3f n = line1.cross(line2);
			Eigen::Vector3f loc(this->location.getY(), this->location.getZ(), this->location.getX());

			loc -= cloud->points[mesh.polygons[i].vertices[0]].getVector3fMap();
			if (acos(n.dot(cloud->points[mesh.polygons[i].vertices[0]].getVector3fMap()) / n.norm() / cloud->points[mesh.polygons[i].vertices[0]].getVector3fMap().norm()) > M_PI_2)
			{
				n *= -1;
			}
			if (acos(n.dot(loc) / n.norm() / loc.norm()) < M_PI_2)
			{
				pcl::CentroidPoint<pcl::PointXYZ> centroid;
				pcl::PointXYZ cent;
				for (size_t j = 0; j < mesh.polygons[i].vertices.size(); j++)
				{
					centroid.add(cloud->points[mesh.polygons[i].vertices[j]]);
					temp.vertices.push_back(mesh.polygons[i].vertices[j]);
				}
				temp.normal = n;
				centroid.get(cent);
				temp.distanse = (cent.getVector3fMap() - this->location.getVector()).norm();
				sortVector.push_back(temp);
			}
		}
		std::sort(sortVector.begin(), sortVector.end(), compFunc);
		for (size_t i = 0; i < sortVector.size(); i++)
		{
			triangle temp;
			Eigen::Vector3f light(-1.0, 0.0, 0.0);
			GLfloat theta;

			temp = sortVector[i];
			theta = acos(temp.normal.dot(light) / temp.normal.norm() / light.norm());
			glColor3f(theta / M_PI, theta / M_PI, theta / M_PI);
			if (temp.vertices.size() == 3)
			{
				glBegin(GL_TRIANGLES);
				for (size_t j = 0; j < temp.vertices.size(); j++)
					glVertex3f(cloud->points[temp.vertices[j]].x, cloud->points[temp.vertices[j]].y, cloud->points[temp.vertices[j]].z);
				glEnd();
			}
			else if (temp.vertices.size() == 4)
			{
				glBegin(GL_QUADS);
				for (size_t j = 0; j < temp.vertices.size(); j++)
					glVertex3f(cloud->points[temp.vertices[j]].x, cloud->points[temp.vertices[j]].y, cloud->points[temp.vertices[j]].z);
				glEnd();
			}
			else
			{
				glBegin(GL_LINES);
				for (size_t j = 0; j < temp.vertices.size(); j++)
					glVertex3f(cloud->points[temp.vertices[j]].x, cloud->points[temp.vertices[j]].y, cloud->points[temp.vertices[j]].z);
				glVertex3f(cloud->points[temp.vertices[0]].x, cloud->points[temp.vertices[0]].y, cloud->points[temp.vertices[0]].z);
				glEnd();
			}
		}*/
		for (size_t i = 0; i < mesh.polygons.size(); i++)
		{
			Eigen::Vector3f line1 = cloud->points[mesh.polygons[i].vertices[0]].getVector3fMap() - cloud->points[mesh.polygons[i].vertices[1]].getVector3fMap();
			Eigen::Vector3f line2 = cloud->points[mesh.polygons[i].vertices[1]].getVector3fMap() - cloud->points[mesh.polygons[i].vertices[2]].getVector3fMap();
			Eigen::Vector3f n = line1.cross(line2);
			Eigen::Vector3f light(-1.0, 0.0, 0.0);
			Eigen::Vector3f loc(this->location.getY(), this->location.getZ(), this->location.getX());
			GLfloat theta;

			loc -= cloud->points[mesh.polygons[i].vertices[0]].getVector3fMap();
			if (acos(n.dot(cloud->points[mesh.polygons[i].vertices[0]].getVector3fMap()) / n.norm() / cloud->points[mesh.polygons[i].vertices[0]].getVector3fMap().norm()) >= M_PI_2)
			{
				n *= -1;
			}
			if (acos(n.dot(loc) / n.norm() / loc.norm()) <= M_PI_2)
			{
				theta = acos(n.dot(light) / n.norm() / light.norm());
				glColor3f(theta / M_PI, theta / M_PI, theta / M_PI);
				if (mesh.polygons[i].vertices.size() == 3)
				{
					glBegin(GL_TRIANGLES);
					for (size_t j = 0; j < mesh.polygons[i].vertices.size(); j++)
						glVertex3f(cloud->points[mesh.polygons[i].vertices[j]].x, cloud->points[mesh.polygons[i].vertices[j]].y, cloud->points[mesh.polygons[i].vertices[j]].z);
					glEnd();
				}
				else if (mesh.polygons[i].vertices.size() == 4)
				{
					glBegin(GL_QUADS);
					for (size_t j = 0; j < mesh.polygons[i].vertices.size(); j++)
						glVertex3f(cloud->points[mesh.polygons[i].vertices[j]].x, cloud->points[mesh.polygons[i].vertices[j]].y, cloud->points[mesh.polygons[i].vertices[j]].z);
					glEnd();
				}
				else
				{
					glBegin(GL_LINES);
					for (size_t j = 0; j < mesh.polygons[i].vertices.size(); j++)
						glVertex3f(cloud->points[mesh.polygons[i].vertices[j]].x, cloud->points[mesh.polygons[i].vertices[j]].y, cloud->points[mesh.polygons[i].vertices[j]].z);
					glVertex3f(cloud->points[mesh.polygons[i].vertices[0]].x, cloud->points[mesh.polygons[i].vertices[0]].y, cloud->points[mesh.polygons[i].vertices[0]].z);
					glEnd();
				}
			}
		}
	}
	else if((!fill) && (mesh.polygons.size() > 1))
	{
		for (size_t i = 0; i < mesh.polygons.size(); i++)
		{
			glBegin(GL_LINES);
			for (size_t j = 0; j < mesh.polygons[i].vertices.size(); j++)
				glVertex3f(cloud->points[mesh.polygons[i].vertices[j]].x, cloud->points[mesh.polygons[i].vertices[j]].y, cloud->points[mesh.polygons[i].vertices[j]].z);
			glVertex3f(cloud->points[mesh.polygons[i].vertices[0]].x, cloud->points[mesh.polygons[i].vertices[0]].y, cloud->points[mesh.polygons[i].vertices[0]].z);
			glEnd();
		}
	}
	else if(mesh.polygons.size() > 0)
	{
		this->draw(mesh.cloud);
	}
}

void Viewer::draw(GLfloat x, GLfloat y, std::string s)		//Draw text
{
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT));
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(x, y);
	void * font = GLUT_BITMAP_9_BY_15;

	for (std::string::iterator i = s.begin(); i != s.end(); ++i)
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void Viewer::rotation(GLfloat vertical, GLfloat horizontal)
{
	if (this->look.checkTheta(vertical * CAMERA_ROTATE_SPEED * M_PI / 180.0))
	{

		this->look.theta += vertical * CAMERA_ROTATE_SPEED * M_PI / 180.0;
	}
	this->look.phi += horizontal * CAMERA_ROTATE_SPEED * M_PI / 180.0;
}

void Viewer::move(ModeDirection direction)
{
	Eigen::Vector3f shift(0.0, 0.0, 0.0);
	switch (direction)
	{
	case Forward:
		shift = this->look.getVector();
		break;
	case Backward:
		shift = -this->look.getVector();
		break;
	case Left:
		break;
	case Right:
		break;
	}
	this->location.set(this->location.getVector() + shift);
}

void Viewer::moveAroud(GLfloat newX, GLfloat newY)
{
	GLfloat horizontal = (this->xClick - newX) / CAMERA_ROTATE_PRE_PIXEL;
	GLfloat vertical = (this->yClick - newY) / CAMERA_ROTATE_PRE_PIXEL;
	if (this->location.checkTheta(vertical * CAMERA_ROTATE_SPEED * M_PI / 180.0))
	{
		this->location.theta += vertical * CAMERA_ROTATE_SPEED * M_PI / 180.0;
	}
	this->location.phi += horizontal * CAMERA_ROTATE_SPEED * M_PI / 180.0;
	this->rotation(-vertical, horizontal);
	this->xClick = newX;
	this->yClick = newY;
}

void Viewer::screenshot()
{
	time_t tt;
	tm *t;
	std::stringstream ss;
	tt = time(NULL);
	t = localtime(&tt);
	t->tm_mon += 1;
	t->tm_year += 1900;
	ss << t->tm_year;
	ss << (t->tm_mon > 9) ? "-" : "-0";
	ss << t->tm_mon;
	ss << (t->tm_mday > 9) ? "-" : "-0";
	ss << t->tm_mday;
	ss << (t->tm_hour > 9) ? "-" : "-0";
	ss << t->tm_hour;
	ss << (t->tm_min > 9) ? "-" : "-0";
	ss << t->tm_min;
	ss << (t->tm_sec > 9) ? "-" : "-0";
	ss << t->tm_sec;
	std::cout << ss.str() << std::endl;
}

void Viewer::screenshot(std::string fileName)
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
	file = fopen(&(*fileName.begin()), "wb");
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