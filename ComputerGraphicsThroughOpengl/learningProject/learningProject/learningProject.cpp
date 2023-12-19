#include "BaseView.h";
#include "ViewHolder.h";
#include "ChapterTwo.h";
// Main routine.
int main(int argc, char **argv)
{
	std::string title = "ChapterTwo";
	char *cstr = &title[0];
	BaseView* currView = new ChapterTwo(cstr, 0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
	currView->display(argc,argv);
	delete currView;
}