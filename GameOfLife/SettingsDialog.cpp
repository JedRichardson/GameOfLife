#include "SettingsDialog.h"
#include "wx/spinctrl.h"
#include "wx/clrpicker.h"

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
	
wxEND_EVENT_TABLE()

SettingsDialog::SettingsDialog(wxWindow* parent)
	: wxDialog(parent, wxID_ANY, "Settings", wxPoint(100,100), wxSize(300,300))
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	spinnerSizer = new wxBoxSizer(wxHORIZONTAL);
	colorSizer = new wxBoxSizer(wxHORIZONTAL);

	wxSizer* buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);

	SetSizer(sizer); 
	_spinner = new wxSpinCtrl(this, 0001);
	_colorPicker = new wxColourPickerCtrl(this, 0002);
	wxStaticText* spinnerLabel = new wxStaticText(this, wxID_ANY, "Number:");
	spinnerLabel->SetMinSize(wxSize(100, 50));
	wxStaticText* colorLabel = new wxStaticText(this, wxID_ANY, "Color:");
	colorLabel->SetMinSize(wxSize(100, 50));


	spinnerSizer->Add(spinnerLabel);
	spinnerSizer->Add(_spinner);

	colorSizer->Add(colorLabel);
	colorSizer->Add(_colorPicker);

	sizer->Add(spinnerSizer);
	sizer->Add(colorSizer);
	sizer->Add(buttonSizer);

	
	
	
	
}

SettingsDialog::~SettingsDialog()
{
}

void SettingsDialog::OnConfirmation(wxCommandEvent& event)
{
	if (wxOK)
	{
		
	}
}

void SettingsDialog::SaveData()
{
	std::ofstream file("settings.bin", std::ios::out | std::ios::binary);
	file.write((char*)this, sizeof(pSettings));
	file.close();
}

void SettingsDialog::LoadData()
{
	std::ifstream file("settings.bin", std::ios::binary | std::ios::in);
	file.read((char*)this, sizeof(pSettings));
	file.close();
}



