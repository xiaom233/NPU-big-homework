// pvzMoneyDlg.h : header file
//

#if !defined(AFX_PVZMONEYDLG_H__F210FEEB_671F_46FA_8AE4_010FA80A0F23__INCLUDED_)
#define AFX_PVZMONEYDLG_H__F210FEEB_671F_46FA_8AE4_010FA80A0F23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPvzMoneyDlg dialog

class CPvzMoneyDlg : public CDialog
{
// Construction
public:
	CPvzMoneyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPvzMoneyDlg)
	enum { IDD = IDD_PVZMONEY_DIALOG };
	CButton	m_autolock;
	int		m_sunny;
	bool	m_runing;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPvzMoneyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPvzMoneyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnModify();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheckLock();
	afx_msg void OnCheckAddsunny();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PVZMONEYDLG_H__F210FEEB_671F_46FA_8AE4_010FA80A0F23__INCLUDED_)
