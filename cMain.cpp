#include "cMain.h"


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "CKsum2.0 - Graphical MD5 Check", wxPoint(10, 10), wxSize(850, 550)) {
	//Creating frames
	txtBox1 = new wxTextCtrl(this, 101, bx1Txt, wxPoint(15, 435), wxSize(800, 30));
	txtBox2 = new wxTextCtrl(this, 102, bx2Txt, wxPoint(15, 470), wxSize(800, 30));
	outBox = new wxTextCtrl(this, 103, info, wxPoint(155, 10), wxSize(660, 420), wxTE_MULTILINE);
	button1 = new wxButton(this, 10001, "Start Proccess", wxPoint(15, 395), wxSize(135, 30));
	menu = new wxRadioBox(this, 1, "Menu", wxPoint(15, 240), wxSize(135, 150), 4, choices, 1);
	title = new wxStaticText(this, 2, "CKsum 2.0 \nCompare Your Directories", wxPoint(15, 15),wxSize(140, 45));
	getMD5 = new getSum(outBox);

	//Styling
	txtBox1->SetForegroundColour(wxColor("grey"));
	txtBox2->SetForegroundColour(wxColor("grey"));
	outBox->SetBackgroundColour(wxColor("black"));
	outBox->SetForegroundColour(wxColor("white"));
	outBox->SetEditable(false);
	//Binding
	button1->Bind(wxEVT_BUTTON, &cMain::button1Clicked, this);
	menu->Bind(wxEVT_RADIOBOX, &cMain::select, this);
	txtBox1->Bind(wxEVT_LEFT_UP, &cMain::bx1Clk, this);
	txtBox2->Bind(wxEVT_LEFT_UP, &cMain::bx2Clk, this);
		
}
cMain::~cMain() {
}
//Instruction processes
void cMain::bx1Clk(wxMouseEvent& evt) {
	if ((txtBox1->GetValue()) == bx1Txt) {
		txtBox1->SetForegroundColour(wxColor("black"));
		txtBox1->Clear();
	}
	evt.Skip();
}
void cMain::bx2Clk(wxMouseEvent& evt) {
	if ((txtBox2->GetValue()) == bx2Txt&&bx2Txt!="Waiting...") {
		txtBox2->SetForegroundColour(wxColor("black"));
		txtBox2->Clear();
	}
	evt.Skip();
}
void cMain::select(wxCommandEvent& evt) {
	int a = menu->GetSelection();
	switch (a) {
	case 0:
	    	txtBox2->SetEditable(true);
			bx1Txt = "Enter the first directories path.";
			bx2Txt = "Enter the second directories path.";
			txtBox1->Clear();
			txtBox1->SetForegroundColour(wxColor("grey"));
			txtBox2->SetForegroundColour(wxColor("grey"));
			txtBox1->WriteText(bx1Txt);
			txtBox2->Clear();
			txtBox2->WriteText(bx2Txt);
		break;
	case 1:
			bx1Txt = "Enter the first directory's path.";
			bx2Txt = "Waiting...";
			txtBox2->SetEditable(false);
			txtBox1->Clear();
			txtBox1->SetForegroundColour(wxColor("grey"));
			txtBox2->SetForegroundColour(wxColor("grey"));
			txtBox1->WriteText(bx1Txt);
			txtBox2->Clear();
			txtBox2->WriteText(bx2Txt);
		break;
	case 2:
			txtBox2->SetEditable(true);
			bx1Txt = "Enter directory path.";
			bx2Txt = "Enter folder to place txt file, or leave black for start location";
			txtBox1->Clear();
			txtBox1->SetForegroundColour(wxColor("grey"));
			txtBox2->SetForegroundColour(wxColor("grey"));
			txtBox1->WriteText(bx1Txt);
			txtBox2->Clear();
			txtBox2->WriteText(bx2Txt);
		break;
	case 3:	
			txtBox2->SetEditable(true);
			bx1Txt = "Enter directory path.";
			bx2Txt = "Enter txt file path.";
			txtBox1->Clear();
			txtBox1->SetForegroundColour(wxColor("grey"));
			txtBox2->SetForegroundColour(wxColor("grey"));
			txtBox1->WriteText(bx1Txt);
			txtBox2->Clear();
			txtBox2->WriteText(bx2Txt);
		break;
	}
	evt.Skip();
}
//Main function
void cMain::button1Clicked(wxCommandEvent& evt) {
	int m = menu->GetSelection();
	wxString path1 = txtBox1->GetValue();
	wxString path2 = txtBox2->GetValue();
	std::string p1 = std::string(path1);
	std::string p2 = std::string(path2);
	

	if (done == false) {
		if (p2.find("\\")!= std::string::npos) {
			txtBox1->SetEditable(false);
			txtBox2->SetEditable(false);
			getMD5->out(m, path1, path2);
			done = true;
		}
		else if (p1.find("\\") != std::string::npos){
			txtBox1->SetEditable(false);
			txtBox2->SetEditable(false);
			getMD5->out(m, path1);
			done = true;
			if (menu->GetSelection() == 1) {
				bx2Txt = "Enter Path 2 and press process";
				txtBox2->SetEditable(true);
				txtBox2->Clear();
				txtBox2->WriteText(bx2Txt);
			}
		}
		if (done == false) {
			outBox->WriteText("Path invalid!");
		}
	}else if (menu->GetSelection() == 1 && p2.find("\\") != std::string::npos) {
		getMD5->out2(path2);
	}else { outBox->WriteText("Path invalid!"); }
	evt.Skip();

}