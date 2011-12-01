// ChartControl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ChartTest.h"
#include "ChartControl.h"


// CChartControl

IMPLEMENT_DYNAMIC(CChartControl, CWnd)

CChartControl::CChartControl()
{
	m_hMemBitmap = NULL;
	m_hMemDC = NULL;

}

CChartControl::~CChartControl()
{
}


BEGIN_MESSAGE_MAP(CChartControl, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CChartControl 메시지 처리기입니다.




void CChartControl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CWnd::OnPaint()을(를) 호출하지 마십시오.
	HDC hDC = dc.m_hDC;

	GetClientRect(rcWindow);
	DrawChart(m_hMemDC);

	BitBlt(hDC, 0, 0, rcWindow.Width(), rcWindow.Height(),m_hMemDC,0,0,SRCCOPY);
}


void CChartControl::OnSize(UINT nType, int cx, int cy)
{
	CreateMemResource();

	CWnd::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

}

void CChartControl::DrawChart(HDC hDC)
{
	//creat font
	{
		LOGFONT lf;
		memset(&lf, 0, sizeof(lf));

		wcscpy(lf.lfFaceName, _T("Verdana"));
		lf.lfHeight = 13;
		hFont = CreateFontIndirect(&lf);
		hOldFont = (HFONT)SelectObject(hDC, hFont);
		
	}
	CalcDataRect();
	CalcAxis();

	DrawBG(hDC);
	DrawAxisX(hDC);
	DrawAxisY(hDC);

	DrawAxisLine(hDC);
	DrawData(hDC);

	//delete font
	{
		
		SelectObject(hDC, hFont);
		DeleteObject(hFont);
	}
}

void CChartControl::CalcDataRect()
{
	//calc data rect
	{
		rcData.left = rcWindow.left + m_cChartConfig.nMarginLeft;
		rcData.right = rcWindow.right - m_cChartConfig.nMarginRight;
		rcData.top = rcWindow.top + m_cChartConfig.nMarginTop;
		rcData.bottom = rcWindow.bottom - m_cChartConfig.nMarginBottom;
	}
}

void CChartControl::CalcAxis()
{
	//x축 계산
	{
		if(m_ChartData.lstData.GetSize() > m_cChartConfig.nInitWidth)
			nXDataSize = m_cChartConfig.nInitWidth
			+ ((m_ChartData.lstData.GetSize()-m_cChartConfig.nInitWidth) / (double)m_cChartConfig.nWidthExtent)
			* m_cChartConfig.nWidthExtent;
		else
			nXDataSize = m_cChartConfig.nInitWidth;

		dblXIntv = rcData.Width() / (double)nXDataSize;
	}

	//y축 계산
	{
		dblYCenter = (m_ChartData.nYMax + m_ChartData.nYMin)/2;

		if(m_ChartData.nYMax - m_ChartData.nYMin < 1)
		{
			dblYMin = m_ChartData.nYMin -1;
			dblYMax = m_ChartData.nYMax +1;
			dblYDataSize = m_ChartData.nYMax - m_ChartData.nYMin +2;
		}
		else
		{
			dblYDataSize = m_ChartData.nYMax - m_ChartData.nYMin;
			dblYMin = m_ChartData.nYMin - dblYDataSize*.2;
			dblYMax = m_ChartData.nYMax + dblYDataSize*.2;
			dblYDataSize = dblYMax - dblYMin;
		}

		dblYPixelSize = rcData.Height()/dblYDataSize;

	}

}

void CChartControl::DrawBG(HDC hDC)
{
	HBRUSH hBrush = CreateSolidBrush(m_cChartConfig.crBG);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	FillRect(hDC, rcWindow, hBrush);

	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);

}

void CChartControl::DrawAxisLine(HDC hDC)
{
	//Draw axis line
	{
		HPEN hAxisLine = CreatePen(PS_SOLID, 2, m_cChartConfig.crAxis);
		HPEN hOldPen = (HPEN)SelectObject(hDC, hAxisLine);

		MoveToEx(hDC, rcData.left, rcData.top,NULL);
		LineTo(hDC, rcData.left, rcData.bottom);
		LineTo(hDC, rcData.right, rcData.bottom);
	}

}

void CChartControl::DrawAxisX(HDC hDC)
{
	//x축 그리기
	{
		HPEN hAxisLine = CreatePen(PS_SOLID, 1, m_cChartConfig.crGuideLine);
		HPEN hOldPen = (HPEN)SelectObject(hDC, hAxisLine);

		int nAxisRight = rcData.left;
		CString szText;
		for(int i=0; i<nXDataSize; i++)
		{
			MoveToEx(hDC, rcData.left+dblXIntv*i, rcData.bottom, NULL);
			LineTo(hDC, rcData.left+dblXIntv*i, rcData.bottom+5);

			szText.Format(_T("%d"),i+1);

			if( i== 0 || nAxisRight+5 < rcData.left + dblXIntv*i)
			{
				TextOut(hDC, rcData.left + dblXIntv*i, rcData.bottom +5, szText, szText.GetLength());

				SIZE size;
				GetTextExtentPoint32(hDC, szText, szText.GetLength(), &size);

				nAxisRight = rcData.left + dblXIntv*i + size.cx;
			}
		}

		SIZE sizeText;
		GetTextExtentPoint32(hDC, m_cChartConfig.szAxisXNM,m_cChartConfig.szAxisXNM.GetLength(),&sizeText);

		TextOut(hDC, rcWindow.right - sizeText.cx - 5, rcWindow.bottom - sizeText.cy - 5, m_cChartConfig.szAxisXNM, m_cChartConfig.szAxisXNM.GetLength());

		SelectObject(hDC, hOldPen);
		DeleteObject(hAxisLine);

	}
}
void CChartControl::DrawAxisY(HDC hDC)
{
	//Y축 그리기
	{
		HPEN hAxisLine = CreatePen(PS_SOLID, 1, m_cChartConfig.crGuideLine);
		HPEN hOldPen = (HPEN)SelectObject(hDC,hAxisLine);
		CString szText;
		SIZE size;
		{
			MoveToEx(hDC, rcData.left -4, rcData.top, NULL);
			LineTo(hDC, rcData.right, rcData.top);

			szText.Format(m_cChartConfig.szFormat, dblYMax);
			GetTextExtentPoint32(hDC, szText, szText.GetLength(), &size);
			TextOut(hDC, rcData.left - 6 - size.cx, rcData.top - size.cy/2, szText, szText.GetLength());

			MoveToEx(hDC, rcData.left - 4, rcData.CenterPoint().y, NULL);
			LineTo(hDC, rcData.right, rcData.CenterPoint().y);

			szText.Format(m_cChartConfig.szFormat, dblYCenter);
			GetTextExtentPoint32(hDC, szText, szText.GetLength(), &size);
			TextOut(hDC, rcData.left - 6 - size.cx, rcData.CenterPoint().y - size.cy/2, szText, szText.GetLength());

			MoveToEx(hDC, rcData.left -4, rcData.bottom, NULL);
			LineTo(hDC, rcData.right, rcData.bottom);

			szText.Format(m_cChartConfig.szFormat, dblYMin);
			GetTextExtentPoint32(hDC, szText, szText.GetLength(), &size);
			TextOut(hDC, rcData.left - 6 - size.cx, rcData.bottom - size.cy/2, szText, szText.GetLength());

		}
		if(rcData.Height() > 200)
		{
			MoveToEx(hDC, rcData.left - 4, (rcData.CenterPoint().y + rcData.top)/2, NULL);
			LineTo(hDC, rcData.right, (rcData.CenterPoint().y + rcData.top)/2);

			szText.Format(m_cChartConfig.szFormat, (dblYMax+dblYCenter)/2);
			GetTextExtentPoint32(hDC, szText, szText.GetLength(), &size);
			TextOut(hDC, rcData.left - 6 - size.cx, (rcData.top+rcData.CenterPoint().y)/2 - size	.cy/2, szText, szText.GetLength());

			MoveToEx(hDC, rcData.left - 4, (rcData.CenterPoint().y + rcData.bottom)/2, NULL);
			LineTo(hDC,rcData.right, (rcData.CenterPoint().y + rcData.bottom)/2);

			szText.Format(m_cChartConfig.szFormat, (dblYMin+dblYCenter)/2);
			GetTextExtentPoint32(hDC, szText, szText.GetLength(), &size);
			TextOut(hDC, rcData.left - 6 - size.cx, (rcData.bottom+rcData.CenterPoint().y)/2-size.cy/2, szText, szText.GetLength());
		}
		
		TextOut(hDC, 5, 5, m_cChartConfig.szAxisYNM, m_cChartConfig.szAxisYNM.GetLength());

		SelectObject(hDC, hOldPen);
		DeleteObject(hAxisLine);

		
	}
}

void CChartControl::DrawData(HDC hDC)
{
	//draw data
	{
		int x,y;

		HPEN hDotPen = CreatePen(PS_SOLID, 1, m_cChartConfig.crDot);
		HPEN hLinePen = CreatePen(PS_SOLID, 1, m_cChartConfig.crDataLine);
		HPEN hOldPen = (HPEN)SelectObject(hDC, hDotPen);

		for(int i=0; i<m_ChartData.lstData.GetSize(); i++){
			y = rcData.CenterPoint().y + (dblYCenter - m_ChartData.lstData.GetAt(i)->fIntv)*dblYPixelSize;
			x = rcData.left + dblXIntv*(i+1);

			DrawDotRect(hDC, x, y, 2, 2);
		}

		SelectObject(hDC, hLinePen);

		if(m_cChartConfig.bShowDataLine)
		{
			for(int i=0; i<m_ChartData.lstData.GetSize(); i++)
			{
				y = rcData.CenterPoint().y+(dblYCenter - m_ChartData.lstData.GetAt(i)->fIntv)*dblYPixelSize;
				x = rcData.left + dblXIntv*(i+1);

				if(i == 0)
					MoveToEx(hDC, x, y, NULL);
				else
					LineTo(hDC, x, y);
			}
		}

		SelectObject(hDC, hOldPen);
		DeleteObject(hDotPen);
	}
}

void CChartControl::DrawDotRect(HDC hDC,int x, int y, int nW, int nH)
{
	Rectangle(hDC, x-nW, y-nH, x+nW, y+nH);
}

void CChartControl::CreateMemResource()
{
	CRect r;
	CDC *pDC = GetDC();

	GetClientRect(r);

	if(m_hMemDC == NULL)
		m_hMemDC = CreateCompatibleDC(pDC->m_hDC);

	if(m_hMemBitmap != NULL)
		DeleteObject(m_hMemBitmap);

	m_hMemBitmap = CreateCompatibleBitmap(pDC->m_hDC, r.Width(), r.Height());
	SelectObject(m_hMemDC, m_hMemBitmap);

	ReleaseDC(pDC);

}