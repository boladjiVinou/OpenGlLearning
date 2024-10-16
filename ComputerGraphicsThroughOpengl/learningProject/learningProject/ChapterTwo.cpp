#include "ChapterTwo.h"
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;


ChapterTwo::ChapterTwo(char * name, double left, double right, double bottom, double top, double inNear, double inFar) :BaseView(name, left, right, bottom, top, inNear, inFar)
{
    this->_initHeight = 250; // another way to include more stuff in the projection
	// this->_initWidth = 250;
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

**************************************Exercice 2.4***********************
double tmp = (double)w / h;
glOrtho(_left*tmp, _right* tmp, _bottom, _top, _near, _far);

**************************************Exercice 2.5 **********************

Our current view is in the plan xy so only x, y coordinates are considered for the display

**************************************Exercice 2.6 *******************************
new ChapterTwo(cstr,-100.0, 200.0, -100.0, 200.0, -1.0, 1.0);
************************************** exercice 2.8 ****************************
6 sides with
glVertex3f(-120.0, 20.0, 1.5);
glVertex3f(220.0, 20.0, -1.5);
glVertex3f(50.0, 210.0, 0.0);

***************************************Exercice 2.11********************************
If you invert the left and right parameters, you effectively change the orientation of the coordinate system along the x-axis. Here’s what happens:

Coordinate System Inversion:

When left > right: The orthographic projection matrix creates a coordinate system where increasing x-values move leftward. This can result in a "flipped" or "mirrored" appearance along the x-axis.
When left < right: The x-coordinate increases from left to right, as expected. This is the typical case for a standard orthographic projection.
Rendering Impact:

Flipping Objects: If you invert left and right, objects rendered in the scene will appear flipped horizontally. For example, a square positioned at (1, 1) might appear at (-1, 1) after inversion, which effectively mirrors the image.
Texture Coordinates: If you’re using textures, the texture coordinates will also be affected in the horizontal direction. This could lead to textures appearing flipped or stretched incorrectly.

When you invert the left and right parameters, you essentially flip the x-axis of the viewing volume. This means that objects that were previously on the left side of the screen will now appear on the right side, and vice versa.

***************************************Exercice 2.12**********************************

	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3f(0.5f,0.5f,0.0f);
	glVertex3f(50.0f, 21.0f, 0.0f);
	glEnd();
**************************************************************************************

*/	

void ChapterTwo::exercice_2_13()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(30, 30, 0);
	glVertex3f(80, 10, 0);
	glVertex3f(60, 30, 0);
	glVertex3f(80, 80, 0);
	glVertex3f(60, 60, 0);
	glVertex3f(10, 80, 0);
	glVertex3f(30, 60, 0);
	glVertex3f(10, 10, 0);
	glVertex3f(30, 30, 0);
	glVertex3f(80, 10, 0);
	glEnd();
	glFinish();
}

void ChapterTwo::exercice_2_14() 
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(10, 70, 0);
	glVertex3f(10, 80, 0);
	glVertex3f(30, 70, 0);
	glVertex3f(50, 80, 0);
	glVertex3f(30, 10, 0);
	glVertex3f(50, 30, 0);
	glVertex3f(50, 10, 0);
	glVertex3f(60, 30, 0);
	glVertex3f(80, 10, 0);
	glVertex3f(60, 80, 0);
	glVertex3f(80, 70, 0);
	glVertex3f(100, 80, 0);
	glVertex3f(100, 70, 0);
	glEnd();
	glFinish();
}
void ChapterTwo::exercice_2_15() 
{
	glColor3f(0.5f, 0.5f, 0.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(60.0, 30.0, 0.0);
	glVertex3f(10.0, 30.0, 0.0);
	glVertex3f(10.0, 10.0, 0.0);
	glVertex3f(80.0, 10.0, 0.0);
	glVertex3f(80.0, 80.0, 0.0);
	glVertex3f(60.0, 80.0, 0.0);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(30.0, 60.0, 0.0);
	glVertex3f(80.0, 60.0, 0.0);
	glVertex3f(80.0, 80.0, 0.0);
	glVertex3f(10.0, 80.0, 0.0);
	glVertex3f(10.0, 10.0, 0.0);
	glVertex3f(30.0, 10.0, 0.0);
	glEnd();
	glFinish();
}
void ChapterTwo:: exercice_2_16() 
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex3f(80, 20, 0);
	glVertex3f(40, 40, 0);
	glVertex3f(20, 80, 0);
	glVertex3f(20, 20, 0);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_POLYGON);
	glVertex3f(180, 20, 0);
	glVertex3f(140, 40, 0);
	glVertex3f(120, 80, 0);
	glVertex3f(120, 20, 0);
	glEnd();
	glFinish();
	// Opengl use triangle_fan for the filling, thats why we have a different result despite 
	// specifying the same configuration of vertices, triangle_fan is done from the 1st specified vertice
}
void ChapterTwo::exercice_2_17()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	

	glVertex3f(20, 20, 0);
	glVertex3f(80, 20, 0);
	glVertex3f(40, 40, 0);
	glVertex3f(20, 80, 0);
	
	glEnd();
	glFinish();
	// it exists if the first vertice is glVertex3f(80, 20, 0);
	// or glVertex3f(20, 80, 0);
}
void ChapterTwo::exercice_2_18()
{
	glColor3f(0.5f, 0.5f, 0.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(10,80,0);
	glVertex3f(20, 80, 0);
	glVertex3f(10, 10, 0);
	glVertex3f(20, 10, 0);
	glVertex3f(20, 30, 0);
	glVertex3f(80, 10, 0);
	glVertex3f(80, 30, 0);
	glVertex3f(70, 30, 0);
	glVertex3f(80, 80, 0);
	glVertex3f(70, 80, 0);
	glVertex3f(70, 60, 0);
	glVertex3f(20, 80, 0);
	glVertex3f(20, 60, 0);
	glVertex3f(70, 60, 0);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(40, 60, 0);
	glVertex3f(50, 60, 0);
	glVertex3f(40, 30, 0);
	glVertex3f(50, 30, 0);
	glEnd();
	glFinish();
}

void ChapterTwo::exercice_2_19()
{
	glColor3f(0.5f, 0.5f, 0.0f);
	glBegin(GL_LINE_STRIP);
	double pi = 3.14;
	double angle = 0;
	double maxAngle = pi;
	double radius = 10;
	double numVertices = 30;
	double x = 50;
	double y = 50;

	for (int i = 0; i < 3; i++)
	{
		maxAngle = pi;
		for (int j = 0; j < numVertices; ++j)
		{
			glVertex3f(x +radius * cos(angle), y-radius * sin(angle), 0.0);
			angle += maxAngle / numVertices;
			radius += 2 / numVertices;
		}
		maxAngle = pi;
		for (int j = 0; j < numVertices; ++j)
		{
			angle += maxAngle / numVertices;
			radius += 3 / numVertices;
			glVertex3f(x + radius * cos(angle), y - radius * sin(angle), 0.0);
		}

		angle = 0;
	}
	glEnd();
	glFinish();

}
void ChapterTwo::exercice_2_20()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0.5f, 0.5f, 0.0f);
	glBegin(GL_POLYGON);
	double pi = 3.14;
	double angle = 0;
	double maxAngle = 2*pi;
	double radius = 10;
	double numVertices = 30;
	double x = 50;
	double y = 50;
	for (int j = 0; j < numVertices; ++j)
	{
		glVertex3f(x + radius * cos(angle), y + radius * sin(angle), 0.0);
		angle += maxAngle / numVertices;
	}
	glEnd();
	x = 100;
	y = 50;
	angle = 0;
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x, y, 0);
	for (int j = 0; j < numVertices; ++j)
	{
		glVertex3f(x + radius * cos(angle), y - radius * sin(angle), 0.0);
		angle += maxAngle / numVertices;
	}
	glVertex3f(x + radius * cos(angle), y - radius * sin(angle), 0.0);
	glEnd();
	glFinish();
}
void ChapterTwo::exercice_2_21()
{
	glColor3f(0.0f, 0.7f, 0.0f);
	double lineNumVertices = 20;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(5);
	// leaf boundary
	glBegin(GL_LINE_STRIP);
	glVertex3f(75, 5, 0);
	glVertex3f(65, 20, 0);
	glVertex3f(65, 25, 0);//
	double p1[2];
	p1[0] = 65;
	p1[1] = 25;
	double p2[2];
	p2[0] = 75;
	p2[1] = 75;
	drawArc(p1, p2, 6, -3.14/1.6,15);
	p1[0] = 75;
	p1[1] = 75;
	p2[0] = 65;
	p2[1] = 25;
	drawArc(p1, p2, 6, -3.14 / 1.6, 15);
	glVertex3f(65, 25, 0);
	glEnd();
	//leaf lines
	glBegin(GL_LINE_STRIP);
	p1[0] = 75;
	p1[1] = 75;
	p2[0] = 65;
	p2[1] = 25;
	drawArc(p1, p2, 6, -0.3, 15);
	glVertex3f(65, 25, 0);
	glEnd();
	glLineWidth(3);
	//left
	glBegin(GL_LINE_STRIP);
	glVertex3f(67, 31, 0);
	glVertex3f(58, 39, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(69, 39, 0);
	glVertex3f(58, 53, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(72, 52, 0);
	glVertex3f(62, 63, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(74, 62, 0);
	glVertex3f(67, 69, 0);
	glEnd();
	//right
	glBegin(GL_LINE_STRIP);
	glVertex3f(67, 31, 0);
	glVertex3f(78, 36, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(69.3, 38, 0);
	glVertex3f(83, 47, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(72, 50, 0);
	glVertex3f(83, 62, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(74, 61, 0);
	glVertex3f(80.2, 68.13, 0);
	glEnd();
	glFinish();
}
double  ChapterTwo :: distance(const double p1[2], const double p2[2])
{
	return sqrt(((p2[0] - p1[0]) * (p2[0] - p1[0])) + ((p2[1] - p1[1]) * (p2[1] - p1[1])));
}
void  ChapterTwo::drawArc(const double p1[2], const double p2[2],double height,double phi, int segments)
{
/* I read https://stackoverflow.com/questions/44877698/geometry-arc-algorithm
*/
	double tmpDistance = distance(p1,p2);
	if (tmpDistance >= height)
	{
		double midPoint[2];
		midPoint[0] = (p1[0] + p2[0]) / 2;
		midPoint[1] = (p1[1] + p2[1]) / 2;
		double direction[2];
		direction[0] = (p2[0] - p1[0]) / 2;
		direction[1] = (p2[1] - p1[1] ) / 2;
		double lengthDirection = sqrt((direction[0] * direction[0]) + (direction[1] * direction[1]));
		double unitDir[2];
		unitDir[0] = direction[0] / lengthDirection;
		unitDir[1] = direction[1] / lengthDirection;
		double leftPerpendicularVector[2];
		leftPerpendicularVector[0] = -unitDir[1];
		leftPerpendicularVector[1] = unitDir[0];
		double circleCenter[2];

		if (phi == 3.14) 
		{
			circleCenter[0] = midPoint[0];
			circleCenter[1] = midPoint[1];
		}
		else 
		{
			circleCenter[0] = midPoint[0] + leftPerpendicularVector[0] * lengthDirection / tan(phi/2);
			circleCenter[1] = midPoint[1] + leftPerpendicularVector[1] * lengthDirection / tan(phi / 2);
		}
		double centerToStart[2];
		centerToStart[0] = p1[0] - circleCenter[0];
		centerToStart[1] = p1[1] - circleCenter[1];
		for (int i = 0; i < segments; i++) 
		{
			double angle = i * phi / segments;
			double x = circleCenter[0] + centerToStart[0] * cos(angle) - centerToStart[1] * sin(angle);
			double y = circleCenter[1] + centerToStart[0] * sin(angle) + centerToStart[1] * cos(angle);
			glVertex3f(x,y, 0);
		}
	}
	else 
	{
		//oops
		int a = 0;
	}
}
void ChapterTwo::exercice_2_22()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,0.0f,0.0f);
	drawCircleWithTriangleStrip(50, 50,0, 30, 100);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawCircleWithTriangleStrip(50, 50,0, 10, 100);
}
void ChapterTwo::drawCircleWithTriangleStrip(int x, int y, int z, int radius, int nbSegments)
{
	glBegin(GL_TRIANGLE_STRIP);
	float t = 0;
	int vCount = 0;
	for (int i = 0; i < nbSegments; ++i)
	{
		++vCount;

		double point[2];
		if (vCount == 3)
		{
			point[0] = x;
			point[1] = y;
			vCount = 0;
		}
		else
		{
			point[0] = x + radius * cos(t);
			point[1] = y + radius * sin(t);

		}
		t += 2 * 3.14 / nbSegments;
		glVertex3f(point[0], point[1], z);
	}
	glVertex3f(x + radius * cos(0), y + radius * sin(0), z);
	glEnd();

	glFinish();
}

/*
****************************Exercice 2.23**************************
Only the first one is affected because only the first one depend on 
rendering order, the second one depends on z value the order doesnt
matter because the depth testing is enabled, the 3rd one 'draw' the
hole by limiting the triangle scopes into an interval, changing the
order of the points drawing wont change thing either
*******************************************************************
*/

void ChapterTwo::exercice_2_24()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glColor3f(0.0f, 1.0f, 0.0f);
	drawCircleWithTriangleStrip(50, 50, 1, 50, 100);
	glColor3f(1.0f, 0.0f, 0.0f);
	drawCircleWithTriangleStrip(50, 50, 2, 40, 100);
	glColor3f(0.0f, 0.3f, 1.0f);
	drawCircleWithTriangleStrip(50, 50, 3, 30, 100);
	glColor3f(1.0f, 1.0f, 0.0f);
	drawCircleWithTriangleStrip(50, 50, 4, 20, 100);
	glColor3f(0.5f, 0.0f, 1.0f);
	drawCircleWithTriangleStrip(50, 50, 5, 10, 100);
	glDisable(GL_DEPTH_TEST);
}

void ChapterTwo::exercice_2_25()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 0.0f, 0.0f);
	float t = 0;
	int nbSegments = 100;
	glVertex3f(50, 50, -200);
	int radius = 40;
	glVertex3f(50 + radius * cos(0), 50 + radius * sin(0), 0);
	for (int i = 0; i < nbSegments; ++i)
	{
		t += 2 * 3.14 / nbSegments;
		glVertex3f(50 + radius * cos(t),
			50 + radius * sin(t), 
			0);
	}
	glEnd();
	glFinish();
}
/**********************************Exercice 2.26****************************
it will coil 10 times
a revolution cost 2pi
-10pi<t<10pi
from 0 to 10pi
we have 5 revolutions to do in order to reach 10 pi
from  0 to -10 pi
we have 5 revolutions to do in order to reach -10 pi
****************************************************************************
***********************************Exercice 2.29****************************
Lets pA and pB being the perspective projections of object A and B on the front face
in the scene.
A is discarded if pA < pB if objects are on the same axis
*/

void ChapterTwo::exercice_2_30()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 1.0f);
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	int nbSegments = 100;
	double steps = 2 * 3.14 / nbSegments;
	for (double phase = -3.14; phase >= -3.14 && phase <= 3.14; phase += steps) 
	{
		glVertex3d( (3.14 + phase)*30, (sin(phase)+1.1)*45, 0);
		
	}
	glEnd();
	glFinish();
}

void ChapterTwo::drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw a polygon with specified vertices.
	//glBegin(GL_POLYGON);
	/*glVertex3f(20.0, 20.0, 0.5);
	glVertex3f(80.0, 20.0, -0.5);
	glVertex3f(80.0, 80.0, 0.1);
	glVertex3f(20.0, 80.0, 0.2);*/
	/*glVertex3f(-120.0, 20.0, 1.5);
	glVertex3f(220.0, 20.0, -1.5);
	glVertex3f(50.0, 210.0, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(120.0, 120.0, 0.0);
	glVertex3f(180.0, 120.0, 0.0);
	glVertex3f(180.0, 180.0, 0.0);
	glVertex3f(120.0, 180.0, 0.0);
	glEnd();*/


	/*glBegin(GL_POLYGON);
	glVertex3f(-20.0, -20.0, 0.0);
	glVertex3f(80.0, 20.0, 0.0);
	glVertex3f(120.0, 120.0, 0.0);
	glVertex3f(20.0, 80.0, 0.0);
	glEnd();*/

	/*glBegin(GL_POLYGON); 
	glColor3f(1.0, 0.0, 0.0); 
	glVertex3f(20.0, 20.0, 0.0); 
	glColor3f(0.0, 1.0, 0.0); 
	glVertex3f(80.0, 20.0, 0.0);
	glColor3f(0.0, 0.0, 1.0); 
	glVertex3f(80.0, 80.0, 0.0); 
	glColor3f(1.0, 1.0, 0.0); 
	glVertex3f(20.0, 80.0, 0.0);
	glEnd();*/
	/*glLineWidth(5.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(20.0f, 20.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(80.0f, 20.0f, 0.0f);
	glEnd();

	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3f(0.5f,0.5f,0.0f);
	glVertex3f(50.0f, 21.0f, 0.0f);
	glEnd();*/
	glColor3f(0.5f, 0.5f, 0.0f);
	exercice_2_30();
	glFlush();
}