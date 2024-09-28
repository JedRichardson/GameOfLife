#pragma once
#include "wx/wx.h"
#include "GameSettings.h"
#include "wx/spinctrl.h"
#include "wx/clrpicker.h"
#include <fstream>
class SettingsDialog : public wxDialog
{
	GameSettings* pSettings;
	wxBoxSizer* spinnerSizer;
	wxBoxSizer* colorSizer;
	wxSpinCtrl* _spinner;
	wxColourPickerCtrl* _colorPicker;
public:
	SettingsDialog(wxWindow* parent);
	~SettingsDialog();
	void SetpSettings(GameSettings* settings) { pSettings = settings; }
	void OnConfirmation(wxCommandEvent& event);
	void SaveData();
	void LoadData();

	wxDECLARE_EVENT_TABLE();
};

