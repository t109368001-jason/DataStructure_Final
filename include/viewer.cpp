#include "viewer.h"
Viewer::Viewer()
{
	this->location.setRadius(1.0);
	this->location.setTheta(M_PI_2);
	this->location.setPhi(0.0);
	this->look.setRadius(1.0);
	this->look.setTheta(M_PI_2);
	this->look.setPhi(M_PI);
}
void Viewer::Mouse(int button, int state, int x, int y)
{
	// only start motion if the left button is pressed
	switch (button)
	{
	case GLUT_LEFT_BUTTON:			//Mouse left buttton
		if (state == GLUT_UP) {
			this->xClick = -1;
			this->yClick = -1;
		}
		else {
			this->xClick = x;
			this->yClick = y;
		}
		break;
	case GLUT_MIDDLE_BUTTON:		//Mouse middle button

		break;
	case GLUT_RIGHT_BUTTON:			//Mouse right button

		break;
	case 3:							//Mouse scroll up

		break;
	case 4:							//Mouse scroll down

		break;
	default:
		std::cout << "Mouse : " << button << "\tState : " << state << std::endl;
		break;
	}
	glutPostRedisplay();
}
void Viewer::mouseMove(int x, int y)
{
	this->rotation(((yClick - y) / 100.0 * CAMERA_ROTATE_SPEED) * M_PI / 180.0, ((xClick - x) / 100.0 * CAMERA_ROTATE_SPEED) * M_PI / 180.0);
}
void Viewer::ChangeSize(int w, int h)
{
	if (h == 0)
		h = 1;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.001, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void Viewer::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	glPointSize(1.0);
	glLineWidth(1.0);

	glLoadIdentity();
	xClick = 0;
	mouseMove(5, 0);

	gluLookAt(this->location.getX(), this->location.getY(), this->location.getZ(), this->location.getX() + this->look.getX(), this->location.getY() + this->look.getY(), this->location.getZ() + this->look.getZ(), 0.0f, 1.0f, 0.0f);

	//viewer.draw(triangle, false);

	this->draw(10, 64, "W S A D : Move camera");
	this->draw(10, 48, "Up Down Left Right : Rotate camera");
	this->draw(10, 32, "Mouse drag : Rotate object");
	this->draw(10, 16, "Mouse scroll : Zoom");


	glutSwapBuffers();
	/*
	if (filename < 2)
	{
		std::stringstream ss;
		ss << "../picture/";
		ss << filename++;
		ss << ".bmp";
		SaveAsBMP(&(*ss.str().begin()));
		glutPostRedisplay();
	}*/
}
void Viewer::Keyboard(unsigned char key, int x, int y)
{
	GLfloat fraction = CAMERA_MOVE_SPEED;
	switch (key)
	{
	case 'w':
		GLfloat tempX = this->location.getX() + this->look.getX() * CAMERA_MOVE_SPEED;
		GLfloat tempY = this->location.getY() + this->look.getY() * CAMERA_MOVE_SPEED;
		GLfloat tempZ = this->location.getZ() + this->look.getZ() * CAMERA_MOVE_SPEED;
		this->location.setRadius(sqrtf(tempX*tempX + tempY * tempY + tempZ * tempZ));
		this->location.setTheta(acos(tempY / this->location.getRadius()));
		this->location.setPhi(atan(tempX / tempZ));
		break;
	case 's':
		GLfloat tempX = this->location.getX() - this->look.getX() * CAMERA_MOVE_SPEED;
		GLfloat tempY = this->location.getY() - this->look.getY() * CAMERA_MOVE_SPEED;
		GLfloat tempZ = this->location.getZ() - this->look.getZ() * CAMERA_MOVE_SPEED;
		this->location.setRadius(sqrtf(tempX*tempX + tempY * tempY + tempZ * tempZ));
		this->location.setTheta(acos(tempY / this->location.getRadius()));
		this->location.setPhi(atan(tempX / tempZ));
		break;
	case 'a':

		break;
	case 'd':

		break;
	case 'f':

		break;


	default: printf("   Keyboard %c == %d\n", key, key);	break;

	}
	glutPostRedisplay();
}
void Viewer::SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		this->look.setPhi(this->look.getPhi() - CAMERA_ROTATE_SPEED * M_PI / 180.0);
		break;
	case GLUT_KEY_RIGHT:
		this->look.setPhi(this->look.getPhi() + CAMERA_ROTATE_SPEED * M_PI / 180.0);
		break;
	case GLUT_KEY_UP:
		this->look.setTheta(this->look.getTheta() - CAMERA_ROTATE_SPEED * M_PI / 180.0);
		if (this->look.getTheta() < 0.0)
		{
			this->look.setTheta(0.0);
		}
		break;
	case GLUT_KEY_DOWN:
		this->look.setTheta(this->look.getTheta() + CAMERA_ROTATE_SPEED * M_PI / 180.0);
		if (this->look.getTheta() > M_PI)
		{
			this->look.setTheta(M_PI);
		}
		break;
	}
	glutPostRedisplay();
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
			GLfloat theta = acos((nX * this->location.getX() + nY * this->location.getY() + nZ * this->location.getZ()) / sqrtf(nX*nX + nY * nY + nZ * nZ) / sqrtf(this->location.getX() * this->location.getX() + this->location.getY() *this->location.getY() + this->location.getZ() * this->location.getZ()));
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
	gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT));
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
void Viewer::rotation(GLfloat deltaTheta, GLfloat deltaPhi)
{
	this->location.setTheta(this->location.getTheta() + deltaTheta);
	this->location.setPhi(this->location.getPhi() + deltaPhi);
	if (this->location.getTheta() < 0.0)
	{
		this->location.setTheta(0.0);
	}
	if (this->location.getTheta() > M_PI)
	{
		this->location.setTheta(M_PI);
	}
}
void Viewer::moveAroud(GLfloat deltaTheta, GLfloat deltaPhi)
{

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