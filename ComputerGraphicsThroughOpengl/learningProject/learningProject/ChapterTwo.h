#pragma once
#include "BaseView.h";
class ChapterTwo : public BaseView
{
public:
	void drawScene(void) override;
	ChapterTwo(char * name, double left, double right, double bottom, double top, double inNear, double inFar);
};

