#pragma once
#include "BaseView.h";
class ChapterTwo : public BaseView
{
public:
	void drawScene(void) override;
	void exercice_2_13();
	void exercice_2_14();
	void exercice_2_15();
	void exercice_2_16();
	void exercice_2_17();
	void exercice_2_18();
	void exercice_2_19();
	ChapterTwo(char * name, double left, double right, double bottom, double top, double inNear, double inFar);
};

