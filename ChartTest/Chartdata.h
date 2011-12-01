#pragma once
class CChartdata
{
public:
	CChartdata(void);
	~CChartdata(void);

public:
	typedef struct __ITEM
	{
		float fOrigin;
		float fDest;
		float fIntv;
	} __ITEM;

public:
	CArray<__ITEM*, __ITEM*> lstData;
	float nYMin;
	float nYMax;
	float nXMin;
	float nXMax;

public:
	int Add(float fOrgin, float fDest);
	void Clear();

};

