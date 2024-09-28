#pragma once
#include "wx/wx.h"
struct GameSettings
{
private:
	unsigned int Red = 128;
	unsigned int Blue = 128;
	unsigned int Green = 128;
	unsigned int Alpha = 255;

	unsigned int dRed = 255;
	unsigned int dBlue = 255;
	unsigned int dGreen = 255;
	unsigned int dAlpha = 255;

	int gridSize_ = 15;
	int interval_ = 50;

public:
	void SetCellColor(wxColor color)
	{
		Red = color.GetRed();
		Blue = color.GetBlue();
		Green = color.GetGreen();
		Alpha = color.GetAlpha();
	}
	void SetDeadCellColor(wxColor color)
	{
		dRed = color.GetRed();
		dBlue = color.GetBlue();
		dGreen = color.GetGreen();
		dAlpha = color.GetAlpha();
	}
	void SetGameSpeed(int interval)
	{
		interval_ = interval;
	}
	void SetGridSize(int gridSize)
	{
		gridSize_ = gridSize;
	}

	wxColor GetCellColor()
	{
		wxColor color(Red, Blue, Green, Alpha);
		return color;
	}
	wxColor GetDeadCellColor()
	{
		wxColor color(dRed, dBlue, dGreen, dAlpha);
		return color;
	}
	int GetGridSize()
	{
		return gridSize_;
	}
	int GetGameSpeed()
	{
		return interval_;
	}
};