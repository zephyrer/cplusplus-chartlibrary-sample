
// ChartTest.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CChartTestApp:
// �� Ŭ������ ������ ���ؼ��� ChartTest.cpp�� �����Ͻʽÿ�.
//

class CChartTestApp : public CWinApp
{
public:
	CChartTestApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CChartTestApp theApp;