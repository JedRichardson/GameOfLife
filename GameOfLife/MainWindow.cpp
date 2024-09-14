#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
	EVT_SIZE(MainWindow::OnSizeChange)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life",        // MainWindow Constuctor
	wxPoint(0, 0), wxSize(500, 500))
{
	statusBar = CreateStatusBar();
	MainWindow::StatusBarText();
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
	statusBar->SetStatusText("Generation: ");
}



