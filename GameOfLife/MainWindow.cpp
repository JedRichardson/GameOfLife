#include "MainWindow.h"


MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life",        // MainWindow Constuctor
	wxPoint(0, 0), wxSize(400, 400))
{
	drawingPanel = new DrawingPanel(this);
}

MainWindow::~MainWindow()                                                    // MainWindow Destructor
{

}

