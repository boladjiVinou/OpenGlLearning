#include "ViewHolder.h"


static BaseView* CURRENT_VIEW;

BaseView* ViewHolder::getView() 
{
	return CURRENT_VIEW;
}
void ViewHolder::setView(BaseView* v) 
{
	CURRENT_VIEW = v;
}
