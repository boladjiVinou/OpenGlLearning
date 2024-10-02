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
	void exercice_2_20();
	void exercice_2_21();
	ChapterTwo(char * name, double left, double right, double bottom, double top, double inNear, double inFar);
private:
	void drawArc(const double p1[2], const double p2[2], double height, double phi,int segments);
	double distance(const double p1[2], const double p2[2]);
};

