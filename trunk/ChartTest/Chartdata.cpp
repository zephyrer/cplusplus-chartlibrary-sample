#include "StdAfx.h"
#include "Chartdata.h"
#include <math.h>


CChartdata::CChartdata(void)
{
}


CChartdata::~CChartdata(void)
{
	Clear();
}

int CChartdata::Add(float fOrgin, float fDest)
{
	__ITEM* item = new __ITEM;
	item->fOrigin = fOrgin;
	item->fDest = fDest;
	item->fIntv = fabs(fOrgin-fDest);
	lstData.Add(item);

	if(lstData.GetSize() == 1)
		nYMin = nYMax = item->fIntv;
	else if(item->fIntv < nYMin)
		nYMin = item->fIntv;
	else if(item->fIntv > nYMax)
		nYMax = item->fIntv;

	return (int)lstData.GetSize();
}

void CChartdata::Clear()
{

	for(int i=lstData.GetSize()-1; i>=0; i--){
		delete lstData.GetAt(i);
	}

	lstData.RemoveAll();
}