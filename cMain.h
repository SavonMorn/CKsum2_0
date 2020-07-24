#pragma once
#include "getSum.h"

class cMain : public wxFrame
{

public:
	cMain();
	~cMain();
	wxString bx1Txt = "Enter the first directory's path.";
	wxString bx2Txt = "Enter the second directory's path.";
	wxString info = {"Compare Two - Checksum two files and compair. \nCheck Pause Check - Checksum two files and compair but with a pause between entering paths.\nGenerate Txt File - Check one and output a file with data.\nCompare to File - Compare a past check to a new one.\n"};
	wxString choices[4] = { "Compare Two","Check Pause Check",
		"Generate Txt File","Compare to File" };
	wxStaticText* title = nullptr;
	wxRadioBox* menu = nullptr;
	wxButton* button1 = nullptr;
	wxTextCtrl* txtBox1 = nullptr;
	wxTextCtrl* txtBox2 = nullptr;
	wxTextCtrl* outBox = nullptr;
	getSum* getMD5 = nullptr;
	bool done = false;

	void bx1Clk(wxMouseEvent& evt);
	void bx2Clk(wxMouseEvent& evt);
	void button1Clicked(wxCommandEvent& evt);
	void select(wxCommandEvent& evt);
	
};

