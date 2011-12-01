#pragma once

#include "Chartconfig.h"
#include "Chartdata.h"

// CChartControl

class CChartControl : public CWnd
{
	DECLARE_DYNAMIC(CChartControl)

public:
	CChartControl();
	virtual ~CChartControl();

protected:
	DECLARE_MESSAGE_MAP()

public:
	Chartconfig m_cChartConfig;
	CChartdata m_ChartData;

	HBITMAP m_hMemBitmap;
	HDC m_hMemDC;

	CRect rcWindow;
	CRect rcData;
	HFONT hFont, hOldFont;
	double dblXIntv, dblYIntv;
	int nXDataSize;
	double dblYDataSize, dblYCenter, dblYMin, dblYMax, dblYPixelSize, dblYDataPerP;

public:
	void DrawChart(HDC hDC);
	void CalcDataRect();
	void CalcAxis();
	void DrawBG(HDC hDC);
	void DrawAxisLine(HDC hDC);
	void DrawAxisX(HDC hDC);
	void DrawAxisY(HDC hDC);
	void DrawData(HDC hDC);
	void DrawDotRect(HDC hDC,int x, int y, int nW, int nH);

	void CreateMemResource();

	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


