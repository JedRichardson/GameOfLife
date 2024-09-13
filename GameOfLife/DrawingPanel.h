#pragma once
#include "wx/wx.h"
class DrawingPanel : public wxPanel
{
private:
	int gridSize = 15;
	std::vector<std::vector<bool>>& gameBoardRef;

public:
	DrawingPanel(wxFrame* parent, std::vector<std::vector<bool>>& gameBoard);

	~DrawingPanel();

	void OnPaint(wxPaintEvent& paint);
	void SetGridSize(int size);
	int GetGridSize() { return gridSize; }
	void MouseClick(wxMouseEvent&);
};

