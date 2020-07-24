#pragma once
#include "wx/wx.h"
#include "cMain.h"
class cApp : public wxApp
{
	cMain* m_Frame1 = nullptr;

public:
	cApp();
	~cApp();

	virtual bool OnInit();
};

