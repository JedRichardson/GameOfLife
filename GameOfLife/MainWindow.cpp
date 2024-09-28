#include "MainWindow.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"
#include "wx/numdlg.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
	EVT_SIZE(MainWindow::OnSizeChange)
	EVT_MENU(0001, MainWindow::Play)
	EVT_MENU(0002, MainWindow::Pause)
	EVT_MENU(0003, MainWindow::Next)
	EVT_MENU(0004, MainWindow::Trash)
	EVT_MENU(0005, MainWindow::Settings)
	//EVT_MENU(0007, MainWindow::Randomize)
	EVT_TIMER(0006, MainWindow::OnTimer)
	//EVT_MENU(0007, MainWindow::RandomizeWithSeed)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life",        // MainWindow Constuctor
	wxPoint(0, 0), wxSize(500, 500))
{
	pStatusBar = CreateStatusBar();
	pStatusBar->SetFieldsCount(2);
	MainWindow::UpdateStatusBar();
	pToolBar = CreateToolBar();
	wxBitmap playIcon(play_xpm);
	pToolBar->AddTool(0001, "Play", playIcon);
	wxBitmap pauseIcon(pause_xpm);
	pToolBar->AddTool(0002, "Pause", pauseIcon);
	wxBitmap nextIcon(next_xpm);
	pToolBar->AddTool(0003, "Next", nextIcon);
	wxBitmap trashIcon(trash_xpm);
	pToolBar->AddTool(0004, "Trash", trashIcon);
	pToolBar->Realize();
	pMenu = new wxMenuBar();
	SetMenuBar(pMenu);
	pOptions = new wxMenu();
	pOptions->Append(0005, "Settings");
	pMenu->Append(pOptions, "Settings");
	pRandomize = new wxMenu();
	pRandomize->Append(0010, "Randomize");
	pMenu->Append(pRandomize, "Randomize");
	pRandomizeWithSeed = new wxMenu();
	pRandomizeWithSeed->Append(0007, "Randomize with Seed");
	pMenu->Append(pRandomizeWithSeed, "Randomize with Seed");
	pDrawingPanel = new DrawingPanel(this, gameBoard_);
	pDrawingPanel->SetpSettings(&settings_);
	pSizer = new wxBoxSizer(wxVERTICAL);
	pSizer->Add(pDrawingPanel, 1, wxEXPAND | wxALL);
	this->SetSizer(pSizer);
	GridInitializer();
	this->Layout();
	pInterval = new wxTimer(this, 0006);

}

MainWindow::~MainWindow()                                                    // MainWindow Destructor
{

}

void MainWindow::OnSizeChange(wxSizeEvent& event)
{
	if (pDrawingPanel == nullptr)
	{
		return;
	}
	pDrawingPanel->SetSize(event.GetSize());
	pDrawingPanel->Refresh();
	event.Skip();
}

void MainWindow::GridInitializer()
{
	gameBoard_.resize(settings_.GetGridSize());
	for (auto& i : gameBoard_)
	{
		i.resize(settings_.GetGridSize());
	}
}

void MainWindow::UpdateStatusBar()
{
	wxString genText = wxString::Format("Generations: %d", generation);
	wxString cellsText = wxString::Format("Living Cells: %d", livingCells);

	pStatusBar->SetStatusText(genText, 0);
	pStatusBar->SetStatusText(cellsText, 1);
}

void MainWindow::Play(wxCommandEvent& event)
{
	if (pInterval->IsRunning())
	{
		pInterval->Stop();
	}
	else
	{
		pInterval->Start(settings_.GetGameSpeed());
	}
}

void MainWindow::Pause(wxCommandEvent& event)
{
	pInterval->Stop();
}

void MainWindow::Next(wxCommandEvent& event)
{
	Generation();
}

void MainWindow::Trash(wxCommandEvent& event)
{
	livingCells = 0;
	generation = 0;
	for (size_t x = 0; x < settings_.GetGridSize(); x++)
	{
		for (size_t y = 0; y < settings_.GetGridSize(); y++)
		{
			gameBoard_[x][y] = false;
		}
	}
	MainWindow::UpdateStatusBar();
	pDrawingPanel->Refresh();
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
			if ((x == 0 && y == 0)|| cellX < 0 || cellX >= settings_.GetGridSize() || cellY < 0 || cellY >= settings_.GetGridSize())
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
	sandbox.resize(settings_.GetGridSize());
	for (auto& i : sandbox)
	{
		i.resize(settings_.GetGridSize());
	}
	for (size_t x = 0; x < settings_.GetGridSize(); x++)
	{
		for (size_t y = 0; y < settings_.GetGridSize(); y++)
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
	pDrawingPanel->Refresh();
	return generation;
}

void MainWindow::OnTimer(wxTimerEvent& event)
{
	Generation();
}

void MainWindow::Settings(wxCommandEvent& event)
{
	pSettingsDialog = new SettingsDialog(this);
	pSettingsDialog->ShowModal();
	if (pSettingsDialog->ShowModal())
	{
		GridInitializer();
	}
}

void MainWindow::PopulateMatrix()
{
	matrix.resize(settings_.GetGridSize());
	for (int i = 0; i < matrix.size(); i++)
	{
		matrix[i].resize(settings_.GetGridSize());
	}
	srand(time(NULL));
	for (size_t i = 0; i < matrix.size(); i++)
	{
		for (size_t j = 0; j < matrix[i].size(); j++)
		{
			int num = rand();
			if (num % 3 == 0)
			{
				matrix[i][j] = true;
			}
			else
			{
				matrix[i][j] = false;
			}
		}
	}
}

void MainWindow::Randomize()
{
}

void MainWindow::RandomizeWithSeed()
{
	wxGetNumberFromUser("Number?", "", "");
	PopulateMatrix();
}
