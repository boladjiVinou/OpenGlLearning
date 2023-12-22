#include "ChapterTwo.h"


ChapterTwo::ChapterTwo(char * name, double left, double right, double bottom, double top, double inNear, double inFar) :BaseView(name, left, right, bottom, top, inNear, inFar)
{
	this->_initHeight = 250;
}
/*
**********************************************Exercice 2.1*************************************

a) Lets compute the size and the location of the square
Shoot:

1 unit = 1 cm
1 unit -> 10 mm
1 pixel -> 0.2 mm
1 pixel = ( 0.2 mm * 1 unit ) / 10 mm
        = 0.02 unit
renderedWidth -> worldWidth

renderedWidth = (worldWidth * 1 pixel) / 0.02 unit
              = 60 / 0.02
			  = 3000 pixel
renderedHeight = renderedWidth = 3000 pixel

x = 20 / 0.02
  = 1000 pixel
y = 80/0.02
  = 4000 pixel



Print:

The view box in world is 100 * 100 units
which gives us 5000 pixels * 5000 pixels

the final window has a size of 500 * 500 pixels
it is jsut a division by 10

the final size of the square

width = renderedWidth / 10 = 300 pixels
height = width = 300 pixels
x = 100 pixels
y = 400 pixels;

b) Lets compute the new size with a axis of 1 meter

1 unit = 1000 mm

1 pixel = 0.2/1000 = 0.0002 unit

renderedWidth = (worldWidth * 1 pixel) / 0.02 unit
			  = 60 / 0.0002
			  = 300000
renderedHeight = renderedWidth = 300000

x = 20 / 0.0002
  = 100000 pixel
y = 80/0.0002
  = 400000 pixel

Print:
The view box in world is 100 * 100 units
which gives us 500000 pixels * 500000 pixels
the final size is a division by 1000

width = 300 pixels
height = 300 pixels
x = 100 pixels
y = 400 pixels

c) Lets compute the size with a different window shape

The view box in world is 100 * 100 units
which gives us 5000 pixels * 5000 pixels

the final window has a size of 500 * 250 pixels
it is jsut a division by 10 for width
and a division by 20 for height

width = renderedWidth / 10 = 300 pixels
height = renderedHeight / 20 = 150 pixels
x = 1000 / 10 = 100
y = 4000 /20 =  200


***********************************Exercice 2.2******************************************
a) top right square
b) bottom left square
c) centered square, near far have no impact as long as they are different and included in the viewer box

***********************************Exercice 2.3*******************************************

Lets compute the new area
the view box is 200 * 200 units
which give us 200/0.02 -> 10000 pixels
10000 * 10000
the final window has a size of 500 * 250

so in x we have a scale of 500/10000 = 1/20 
in y we have a scale of 250 / 10000 = 1/40
renderedHeight = renderedWidth = 3000 pixels

finalHeight = 3000/40 = 75
finalWidht = 3000/ 20 = 150

The area is 150*75 = 11250


*/
void ChapterTwo::drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0);

	// Draw a polygon with specified vertices.
	glBegin(GL_POLYGON);
	glVertex3f(20.0, 20.0, 0.0);
	glVertex3f(80.0, 20.0, 0.0);
	glVertex3f(80.0, 80.0, 0.0);
	glVertex3f(20.0, 80.0, 0.0);
	glEnd();

	glFlush();
}