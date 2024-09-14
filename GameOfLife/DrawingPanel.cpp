#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
	EVT_PAINT(DrawingPanel::OnPaint)
	EVT_LEFT_UP(DrawingPanel::MouseClick)
wxEND_EVENT_TABLE()


DrawingPanel::DrawingPanel(wxFrame* parent, std::vector<std::vector<bool>>& gameBoard) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize), gameBoardRef(gameBoard)
{
	this->SetBackgroundStyle(wxBG_STYLE_PAINT);
}



DrawingPanel::~DrawingPanel()
{
}

void DrawingPanel::OnPaint(wxPaintEvent& paint)
{
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();
	wxGraphicsContext* context = wxGraphicsContext::Create(dc);
	if (!context) { return; }
	context->SetPen(*wxBLACK);
	context->SetBrush(*wxWHITE);


	int xPosition;
	int yPosition;
	float width = (GetSize().GetWidth()) / (float)gridSize;
	float height = (GetSize().GetHeight()) / (float)gridSize;
	for (size_t i = 0; i < gridSize; i++)
	{
		xPosition = i * width;
		for (size_t j = 0; j < gridSize; j++)
		{
			yPosition = j * height;
			if (gameBoardRef[i][j])
			{
				context->SetBrush(*wxLIGHT_GREY);
			}
			else
				context->SetBrush(*wxWHITE);
			context->DrawRectangle(xPosition, yPosition, width, height);
		}
	}
	Refresh();
}

void DrawingPanel::SetGridSize(int size)
{
	gridSize = size;
}

void DrawingPanel::MouseClick(wxMouseEvent& event)
{
	int x = event.GetX();
	int y = event.GetY();
	float width = (GetSize().GetWidth()) / (float)gridSize;
	float height = (GetSize().GetHeight()) / (float)gridSize;
	int row = x / width;
	int column = y / height;
	gameBoardRef[row][column] = !gameBoardRef[row][column];
}
