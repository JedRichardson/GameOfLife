#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"
#include "GameSettings.h"
#include "SettingsDialog.h"

class MainWindow : public wxFrame
{
	DrawingPanel* pDrawingPanel;
	SettingsDialog* pSettingsDialog;
	wxBoxSizer* pSizer;
	std::vector<std::vector<bool>> gameBoard_;
	int generation;
	int livingCells;
	wxStatusBar* pStatusBar;
	wxToolBar* pToolBar;
	std::vector<std::vector<bool>> sandbox;
	wxTimer* pInterval = nullptr;
	GameSettings settings_;
	wxMenuBar* pMenu;
	wxMenu* pOptions;
	wxMenu* pRandomize;
	wxMenu* pRandomizeWithSeed;
	wxMenu* pLoad;
	wxMenu* pSave;
	std::vector<std::vector<bool>> matrix;

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
	void OnTimer(wxTimerEvent& event);
	void Settings(wxCommandEvent& event);
	void PopulateMatrix();
	void Randomize();
	void RandomizeWithSeed();

	wxDECLARE_EVENT_TABLE();


};

