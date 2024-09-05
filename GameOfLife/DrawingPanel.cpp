#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"



DrawingPanel::DrawingPanel() : wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(50, 50))
{
	this->SetBackgroundStyle(wxBG_STYLE_PAINT);
	this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
}



DrawingPanel::~DrawingPanel()
{
}

void DrawingPanel::OnPaint(wxPaintEvent&)
{
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();
	wxGraphicsContext* context = wxGraphicsContext::Create(dc);
	if (!context) { return; }
	context->SetPen(*wxBLACK);
	context->SetBrush(*wxWHITE);
	context->DrawRectangle(0,0,10,10);
}
