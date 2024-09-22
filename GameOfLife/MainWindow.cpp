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
	EVT_TIMER(0005, MainWindow::Timer)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life",        // MainWindow Constuctor
	wxPoint(0, 0), wxSize(500, 500))
{
	statusBar = CreateStatusBar();
	statusBar->SetFieldsCount(2);
	MainWindow::UpdateStatusBar();
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
	timer = new wxTimer(this, 0005);
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

void MainWindow::UpdateStatusBar()
{
	wxString genText = wxString::Format("Generations: %d", generation);
	wxString cellsText = wxString::Format("Living Cells: %d", livingCells);

	statusBar->SetStatusText(genText, 0);
	statusBar->SetStatusText(cellsText, 1);
}

void MainWindow::Play(wxCommandEvent& event)
{
	timer->Start(gameSpeed);
}

void MainWindow::Pause(wxCommandEvent& event)
{
	timer->Stop();
}

void MainWindow::Next(wxCommandEvent& event)
{
	Generation();
}

void MainWindow::Trash(wxCommandEvent& event)
{
	livingCells = 0;
	generation = 0;
	for (size_t x = 0; x < gridSize_; x++)
	{
		for (size_t y = 0; y < gridSize_; y++)
		{
			gameBoard_[x][y] = false;
		}
	}
	MainWindow::UpdateStatusBar();
	drawingPanel->Refresh();
}

int MainWindow::NeighborCount(int row, int column)
{
	int livingNeighbors = 0;
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++) 
		{
			int cellX = row + x;
			int cellY = column + y;
			if ((x == 0 && y == 0)|| cellX < 0 || cellX >= gridSize_ || cellY < 0 || cellY >= gridSize_)
				continue;
			bool living = gameBoard_[row + x][column + y];
			if (living)
				livingNeighbors++;
		}
	}
	return livingNeighbors;
}

int MainWindow::Generation()
{
	livingCells = 0;
	bool keepALive = false;
	sandbox.resize(gridSize_);
	for (auto& i : sandbox)
	{
		i.resize(gridSize_);
	}
	for (size_t x = 0; x < gridSize_; x++)
	{
		for (size_t y = 0; y < gridSize_; y++)
		{
			int livingNeighbors = this->NeighborCount(x, y);
			bool living = gameBoard_[x][y];
			if (living) 
			{
				keepALive = (livingNeighbors >= 2 && livingNeighbors <= 3);
			}
			else 
			{
				keepALive = (livingNeighbors == 3);
			}
			
			sandbox[x][y] = keepALive;
			if (keepALive)
				livingCells++;
		}
	}
	swap(gameBoard_, sandbox);
	generation++;
	MainWindow::UpdateStatusBar();
	drawingPanel->Refresh();
	return generation;
}

void MainWindow::Timer(wxTimerEvent& event)
{
	Generation();
}
