#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"



DrawingPanel::DrawingPanel(wxFrame* parent, std::vector<std::vector<bool>>& gameBoard) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize), gameBoardRef(gameBoard)
{
	this->SetBackgroundStyle(wxBG_STYLE_PAINT);
	this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
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
			context->DrawRectangle(xPosition, yPosition, width, height);
		}
	}
	
	
}

void DrawingPanel::SetGridSize(int size)
{
	gridSize = size;
}
