#pragma once
class Chartconfig
{
public:
	Chartconfig(void);
	~Chartconfig(void);

public:
	int nInitWidth;
	int nWidthExtent;

	COLORREF crDot;
	COLORREF crDataLine;
	COLORREF crBG;
	COLORREF crGuideLine;
	COLORREF crAxis;

	BOOL bShowGuideLine;
	BOOL bShowDataLine;
	BOOL bAxisYSensitive;

	double dblAxisYMin;
	double dblAxisYMax;

	int nMarginTop;
	int nMarginLeft;
	int nMarginBottom;
	int nMarginRight;

	CString szAxisXNM;
	CString szAxisYNM;
	CString szFormat;
};

