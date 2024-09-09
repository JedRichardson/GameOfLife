#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"

class MainWindow : public wxFrame
{
	DrawingPanel* drawingPanel;
	wxBoxSizer* sizer;

	void OnSizeChange(wxSizeEvent& event);

public:
	MainWindow();      // MainWindow Constructor
	~MainWindow();     // MainWindow Destructor
	

	


};

