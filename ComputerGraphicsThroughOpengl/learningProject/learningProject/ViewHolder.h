#pragma once
class BaseView;
class ViewHolder
{
public:
	static BaseView* getView();
	static void setView(BaseView* v);
};

