#include "BaseView.h"
#include "ViewHolder.h"
BaseView::BaseView(char *  name, double left, double right, double bottom, double top, double inNear, double inFar)
{
	this->_name = name;
	this->_left = left;
	this->_right = right;
	this->_bottom = bottom;
	this->_top = top;
	this->_near = inNear;
	this->_far = inFar;
}
BaseView::BaseView() 
{
	std::string title = "OpenGL Training";
	char *cstr = &title[0];
	this->_name = cstr;
	this->_left = 0.0;
	this->_right = 100.0;
	this->_bottom = 0.0;
	this->_top = 100.0;
	this->_near = -1.0;
	this->_far = 1.0;
}
BaseView::~BaseView()
{
	int a = 0;
}

void  BaseView::staticDraw()
{
	ViewHolder::getView()->drawScene();
}
void BaseView::drawScene(void) 
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 0.0, 0.0);

	// Draw a polygon with specified vertices.
	glBegin(GL_POLYGON);
	glVertex3f(30.0, 20.0, 0.0);
	glVertex3f(80.0, 20.0, 0.0);
	glVertex3f(80.0, 80.0, 0.0);
	glVertex3f(20.0, 80.0, 0.0);
	glEnd();

	glFlush();
}
void BaseView::setup(void) 
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}
void BaseView::resize(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(_left, _right, _bottom, _top, _near, _far);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void BaseView::staticResize(int w, int h) 
{
	ViewHolder::getView()->resize(w, h);
}

void BaseView::keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:
			exit(0);
			break;
		default:
			break;
	}
}
void BaseView:: staticKeyInput(unsigned char key, int x, int y)
{
	ViewHolder::getView()->keyInput(key, x, y);
}
void BaseView::display(int argc, char **argv)
{
	ViewHolder::setView(this);

	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	glutCreateWindow(_name);

	glutDisplayFunc(&BaseView::staticDraw);
	glutReshapeFunc(&BaseView::staticResize);
	glutKeyboardFunc(&BaseView::staticKeyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}