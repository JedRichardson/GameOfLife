#include "MainWindow.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
	EVT_SIZE(MainWindow::OnSizeChange)
	EVT_MENU(0001, MainWindow::Play)
	EVT_MENU(0002, MainWindow::Pause)
	EVT_MENU(0003, MainWindow::Next)
	EVT_MENU(0004, MainWindow::Trash)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life",        // MainWindow Constuctor
	wxPoint(0, 0), wxSize(500, 500))
{
	statusBar = CreateStatusBar();
	MainWindow::StatusBarText();
	toolBar = CreateToolBar();
	wxBitmap playIcon(play_xpm);
	toolBar->AddTool(0001, "Play", playIcon);
	wxBitmap pauseIcon(pause_xpm);
	toolBar->AddTool(0002, "Pause", pauseIcon);
	wxBitmap nextIcon(next_xpm);
	toolBar->AddTool(0003, "Next", nextIcon);
	wxBitmap trashIcon(trash_xpm);
	toolBar->AddTool(0004, "Trash", trashIcon);
	toolBar->Realize();
	drawingPanel = new DrawingPanel(this, gameBoard_);
	sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(drawingPanel, 1, wxEXPAND | wxALL);
	this->SetSizer(sizer);
	GridInitializer();
	this->Layout();
	
}

MainWindow::~MainWindow()                                                    // MainWindow Destructor
{

}

void MainWindow::OnSizeChange(wxSizeEvent& event)
{
	if (drawingPanel == nullptr)
	{
		return;
	}
	drawingPanel->SetSize(event.GetSize());
	drawingPanel->Refresh();
	event.Skip();
}

void MainWindow::GridInitializer()
{
	gameBoard_.resize(gridSize_);
	for (auto& i : gameBoard_)
	{
		i.resize(gridSize_);
	}
	drawingPanel->SetGridSize(gridSize_);
}

void MainWindow::StatusBarText()
{
	statusBar->SetStatusText("Generation:\t\tLiving Cells: ");
}

void MainWindow::Play(wxCommandEvent& event)
{
}

void MainWindow::Pause(wxCommandEvent& event)
{
}

void MainWindow::Next(wxCommandEvent& event)
{
}

void MainWindow::Trash(wxCommandEvent& event)
{
}


