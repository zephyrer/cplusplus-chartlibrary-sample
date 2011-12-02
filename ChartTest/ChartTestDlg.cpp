
// ChartTestDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ChartTest.h"
#include "ChartTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChartTestDlg ��ȭ ����




CChartTestDlg::CChartTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChartTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChartTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CChartTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CChartTestDlg::OnBnClickedButton1)
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CChartTestDlg �޽��� ó����

BOOL CChartTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CChartTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CChartTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CChartTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChartTestDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(!m_LineChartCtrl.m_hWnd)
	{
		for(int i=0; i<5; i++)
		{
			m_LineChartCtrl.m_ChartData.Add(50, 100);
			m_LineChartCtrl.m_ChartData.Add(50, 101);
			m_LineChartCtrl.m_ChartData.Add(50, 102);
			m_LineChartCtrl.m_ChartData.Add(50, 103);
			m_LineChartCtrl.m_ChartData.Add(50, 104);
			m_LineChartCtrl.m_ChartData.Add(50, 105);
			m_LineChartCtrl.m_ChartData.Add(50, 106);
			m_LineChartCtrl.m_ChartData.Add(50, 107);
			m_LineChartCtrl.m_ChartData.Add(50, 108);
			m_LineChartCtrl.m_ChartData.Add(50, 109);
		}

		CRect rcWindow;
		GetClientRect(rcWindow);
		m_LineChartCtrl.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 50, rcWindow.Width()/2, rcWindow.Height()), this, 1234);

		SetTimer(1234, 100, 0);
	}
	if(!m_LineChartCtrl2.m_hWnd)
	{
		CRect rcWindow;
		GetClientRect(rcWindow);
		m_LineChartCtrl2.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(rcWindow.Width()/2, 50, rcWindow.Width(),rcWindow.Height()),this, 1235);
		SetTimer(1, 200, 0);
	}
}


void CChartTestDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if(m_LineChartCtrl.m_hWnd)
	{
		m_LineChartCtrl.MoveWindow(0, 50, cx, cy-50, TRUE);
	}
}


void CChartTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(1234 == nIDEvent)
	{
		m_LineChartCtrl.m_ChartData.Add(50, rand()%50+70);
		m_LineChartCtrl.RedrawWindow();

		if(m_LineChartCtrl.m_ChartData.lstData.GetSize() > 250)
			KillTimer(1234);
	}
	if(1 == nIDEvent){
		m_LineChartCtrl2.m_ChartData.Add(50, rand()%100);
		m_LineChartCtrl2.RedrawWindow();

		if(m_LineChartCtrl2.m_ChartData.lstData.GetSize() > 250)
			KillTimer(1);
	}

	CDialog::OnTimer(nIDEvent);

	CDialogEx::OnTimer(nIDEvent);
}
