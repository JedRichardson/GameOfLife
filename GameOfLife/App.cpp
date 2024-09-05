#include "App.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(App);

App::App() {

}

App::~App() {

}

bool App::OnInit() 
{
	mainWindow = new MainWindow();   // Instantiate MainWindow Pointer
	mainWindow->Show(true);          // Call Show()
	return true;
}