#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"



DrawingPanel::DrawingPanel(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
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
	int width = (GetSize().GetWidth()) / gridSize;
	int height = (GetSize().GetHeight()) / gridSize;
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
