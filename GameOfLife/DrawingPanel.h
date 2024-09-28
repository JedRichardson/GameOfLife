#pragma once
#include "wx/wx.h"
#include "GameSettings.h"

class DrawingPanel : public wxPanel
{
	std::vector<std::vector<bool>>& gameBoardRef;
	GameSettings* pSettings;

public:
	DrawingPanel(wxFrame* parent, std::vector<std::vector<bool>>& gameBoard);

	~DrawingPanel();

	void OnPaint(wxPaintEvent& paint);
	void SetpSettings(GameSettings* settings) { pSettings = settings; }
	void MouseClick(wxMouseEvent&);

	wxDECLARE_EVENT_TABLE();
};