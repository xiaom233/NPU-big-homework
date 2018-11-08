// pvzMoneyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pvzMoney.h"
#include "pvzMoneyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPvzMoneyDlg dialog

CPvzMoneyDlg::CPvzMoneyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPvzMoneyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPvzMoneyDlg)
	m_sunny = 2000;
	m_runing  = false;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPvzMoneyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPvzMoneyDlg)
	DDX_Control(pDX, IDC_CHECK_LOCK, m_autolock);
	DDX_Text(pDX, IDC_EDIT_SUNNY, m_sunny);
	DDV_MinMaxInt(pDX, m_sunny, 1, 9000);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPvzMoneyDlg, CDialog)
	//{{AFX_MSG_MAP(CPvzMoneyDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_MODIFY, OnBtnModify)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_LOCK, OnCheckLock)
	ON_BN_CLICKED(IDC_CHECK_ADDSUNNY, OnCheckAddsunny)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPvzMoneyDlg message handlers

BOOL CPvzMoneyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	SetTimer(2,1000,NULL);
	GetDlgItem(IDC_BTN_MODIFY)->EnableWindow(false);
	GetDlgItem(IDC_CHECK_LOCK)->EnableWindow(false);
	GetDlgItem(IDC_EDIT_SUNNY)->EnableWindow(false);
	GetDlgItem(IDC_CHECK_ADDSUNNY)->EnableWindow(false);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPvzMoneyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPvzMoneyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPvzMoneyDlg::OnBtnModify() 
{
	HWND hWnd = ::FindWindow(NULL,"植物大战僵尸中文版");
	if(hWnd == 0) return;
	HANDLE hProc;
	DWORD proID;
	GetWindowThreadProcessId(hWnd,&proID);
	hProc=OpenProcess(PROCESS_ALL_ACCESS, false,proID);
	if(hProc==NULL) 
	{
		m_sunny = (int)hWnd;
		UpdateData(false);
		MessageBox("cannot open process!");
		return;
	}
	
	DWORD ads_ps=0x006a9ec0; //内存地址
	DWORD value;				
	ReadProcessMemory(hProc,(void *)ads_ps,&value,4,NULL);
	ads_ps = value + 0x768;
	ReadProcessMemory(hProc,(void *)ads_ps,&value,4,NULL);
	ads_ps = value + 0x5560;
	UpdateData();
	value = m_sunny;
	WriteProcessMemory(hProc,(void *)ads_ps,&value,4,NULL);	
	CloseHandle(hProc);	

	
}

void CPvzMoneyDlg::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == 1)
	{
	
		HWND hWnd = ::FindWindow(NULL,"植物大战僵尸中文版");
		if(hWnd == 0) return;
		HANDLE hProc;
		DWORD proID;
		GetWindowThreadProcessId(hWnd,&proID);
		hProc=OpenProcess(PROCESS_ALL_ACCESS, false,proID);
		if(hProc==NULL) 
		{
			//m_sunny = (int)hWnd;
			//UpdateData(false);
			//MessageBox("cannot open process!");
			return;
		}
		
		DWORD ads_ps=0x006a9ec0; //内存地址
		DWORD value;				
		ReadProcessMemory(hProc,(void *)ads_ps,&value,4,NULL);
		ads_ps = value + 0x768;
		ReadProcessMemory(hProc,(void *)ads_ps,&value,4,NULL);
		ads_ps = value + 0x5560;
		UpdateData();
		value = m_sunny;
		WriteProcessMemory(hProc,(void *)ads_ps,&value,4,NULL);	
		CloseHandle(hProc);	
	}
	else if(nIDEvent == 2)
	{
		HWND hWnd = ::FindWindow(NULL,"植物大战僵尸中文版");
		if(hWnd == 0) 
		{		
			SetDlgItemText(IDC_STATIC,"游戏未运行");
			if(m_runing)
			{
				GetDlgItem(IDC_BTN_MODIFY)->EnableWindow(false);
				GetDlgItem(IDC_CHECK_LOCK)->EnableWindow(false);
				GetDlgItem(IDC_EDIT_SUNNY)->EnableWindow(false);
				GetDlgItem(IDC_CHECK_ADDSUNNY)->EnableWindow(false);
				m_runing = false;
			}
		}
		else
		{
			SetDlgItemText(IDC_STATIC,"游戏运行中");
			if(!m_runing)
			{
				GetDlgItem(IDC_BTN_MODIFY)->EnableWindow(true);
				GetDlgItem(IDC_CHECK_LOCK)->EnableWindow(true);
				GetDlgItem(IDC_EDIT_SUNNY)->EnableWindow(true);
				GetDlgItem(IDC_CHECK_ADDSUNNY)->EnableWindow(true);
				m_runing = true;
			}
		}
	}
}

//锁定
void CPvzMoneyDlg::OnCheckLock() 
{	
if(m_autolock.GetCheck() == BST_CHECKED) 
	SetTimer(1,500,NULL);
else
	KillTimer(1);	
}

//安放植物加阳光
void CPvzMoneyDlg::OnCheckAddsunny() 
{
	HWND hWnd = ::FindWindow(NULL,"植物大战僵尸中文版");
	if(hWnd == 0) return;
	HANDLE hProc;
	DWORD proID,oldFlag;
	GetWindowThreadProcessId(hWnd,&proID);
	hProc=OpenProcess(PROCESS_ALL_ACCESS, false,proID);
	if(hProc==NULL) 
	{
		//m_sunny = (int)hWnd;
		//UpdateData(false);
		//MessageBox("cannot open process!");
		return;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK_ADDSUNNY))->GetCheck() == BST_CHECKED)
	{
		DWORD ads_ps=0x0041ba74; //内存地址
		WORD value;
		value = 0xde01;
		VirtualProtectEx(hProc,(void *)ads_ps,2,PAGE_READWRITE,&oldFlag);
		WriteProcessMemory(hProc,(void *)ads_ps,&value,2,NULL);
		VirtualProtectEx(hProc,(void *)ads_ps,2,oldFlag,NULL);
		CloseHandle(hProc);	
	}
	else
	{
		DWORD ads_ps=0x0041ba74; //内存地址
		WORD value;
		value = 0xf32b;
		VirtualProtectEx(hProc,(void *)ads_ps,2,PAGE_READWRITE,&oldFlag);
		WriteProcessMemory(hProc,(void *)ads_ps,&value,2,NULL);
		VirtualProtectEx(hProc,(void *)ads_ps,2,oldFlag,NULL);
		CloseHandle(hProc);	
	}
}
