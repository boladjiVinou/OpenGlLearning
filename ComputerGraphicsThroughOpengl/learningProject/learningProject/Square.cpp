#include "Square.h"


Square::Square(char * name, double left, double right, double bottom, double top, double inNear, double inFar) :BaseView(name, left, right, bottom, top, inNear, inFar)
{
	
}
void Square::drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0);

	// Draw a polygon with specified vertices.
	glBegin(GL_POLYGON);
	glVertex3f(30.0, 20.0, 0.0);
	glVertex3f(80.0, 20.0, 0.0);
	glVertex3f(80.0, 80.0, 0.0);
	glVertex3f(20.0, 80.0, 0.0);
	glEnd();

	glFlush();
}