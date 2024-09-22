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
	wxStatusBar* statusBar2;
	wxToolBar* toolBar;
	std::vector<std::vector<bool>> sandbox;
	wxTimer* timer;
	int gameSpeed = 50;

public:
	MainWindow();      // MainWindow Constructor
	~MainWindow();     // MainWindow Destructor
	void OnSizeChange(wxSizeEvent& event);
	void GridInitializer();
	void UpdateStatusBar();
	void Play(wxCommandEvent& event);
	void Pause(wxCommandEvent& event);
	void Next(wxCommandEvent& event);
	void Trash(wxCommandEvent& event);
	int NeighborCount(int row, int column);
	int Generation();
	void Timer(wxTimerEvent& event);

	wxDECLARE_EVENT_TABLE();


};

