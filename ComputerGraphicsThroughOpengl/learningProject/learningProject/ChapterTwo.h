#pragma once
#include "BaseView.h";
class ChapterTwo : public BaseView
{
public:
	void drawScene(void) override;
	void exercice_2_13();
	void exercice_2_14();
	void exercice_2_15();
	ChapterTwo(char * name, double left, double right, double bottom, double top, double inNear, double inFar);
};

