#pragma once
#include "string"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "ViewHolder.h"
#include <functional>
using namespace std;
//class BaseView;
//static BaseView* currentInstance;
class BaseView
{
public:
	BaseView(char * name, double left, double right, double bottom, double top, double inNear, double inFar);
	BaseView();
	~BaseView();
	void display(int argc, char **argv);
	static void staticDraw();
	static void staticResize(int w, int h);
	static void staticKeyInput(unsigned char key, int x, int y);
protected:
	void virtual drawScene(void);
	void setup(void);
	double _left;
	double _right;
	double _bottom;
	double _top;
	double _near;
	double _far;
	double _initWidth;
	double _initHeight;
private:
	void resize(int w, int h);
	void keyInput(unsigned char key, int x, int y);
	char * _name;
};

