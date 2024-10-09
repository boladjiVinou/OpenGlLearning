#include "BaseView.h";
#include "ViewHolder.h";
#include "ChapterTwo.h";
// Main routine.
int main(int argc, char **argv)
{
	std::string title = "ChapterTwo";
	char *cstr = &title[0];
	BaseView* currView = new ChapterTwo(cstr,0,100,0,100,-100,100);
	currView->display(argc,argv);
	delete currView;
}