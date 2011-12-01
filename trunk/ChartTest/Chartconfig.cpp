#include "StdAfx.h"
#include "Chartconfig.h"


Chartconfig::Chartconfig(void)
{
	nInitWidth = 10;
	nWidthExtent = 10;

	crDot = RGB(255,0,0);
	crDataLine = RGB(255,200,200);
	crBG = RGB(255,255,255);
	crGuideLine = RGB(128,128,128);
	crAxis = 0;

	bShowGuideLine = FALSE;
	bShowDataLine = TRUE;

	bAxisYSensitive = TRUE;
	dblAxisYMin = 0;
	dblAxisYMax = 0;

	nMarginTop = 30;
	nMarginLeft = 80;
	nMarginRight = 20;
	nMarginBottom = 40;

	szAxisXNM = "Axis X";
	szAxisYNM = "Axis Y";
	szFormat = "%.2f";

}


Chartconfig::~Chartconfig(void)
{
}
