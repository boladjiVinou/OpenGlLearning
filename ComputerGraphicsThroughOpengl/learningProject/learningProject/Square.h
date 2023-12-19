#pragma once
#include "BaseView.h";
class Square : public BaseView
{
public:
	void drawScene(void) override;
	Square(char * name, double left, double right, double bottom, double top, double inNear, double inFar);
};

