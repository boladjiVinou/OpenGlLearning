#include "BaseView.h";
#include "ViewHolder.h";
#include "Square.h";
// Main routine.
int main(int argc, char **argv)
{
	std::string title = "Square";
	char *cstr = &title[0];
	BaseView* currView = new Square(cstr, 0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
	currView->display(argc,argv);
	delete currView;
}