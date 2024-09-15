#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"
class MainWindow : public wxFrame
{
	DrawingPanel* drawingPanel;
	wxBoxSizer* sizer;
	std::vector<std::vector<bool>> gameBoard_;
	int gridSize_ = 10;
	int generation;
	int livingCells;
	wxStatusBar* statusBar;
	wxToolBar* toolBar;

public:
	MainWindow();      // MainWindow Constructor
	~MainWindow();     // MainWindow Destructor
	void OnSizeChange(wxSizeEvent& event);
	void GridInitializer();
	void StatusBarText();
	void Play(wxCommandEvent& event);
	void Pause(wxCommandEvent& event);
	void Next(wxCommandEvent& event);
	void Trash(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();


};

