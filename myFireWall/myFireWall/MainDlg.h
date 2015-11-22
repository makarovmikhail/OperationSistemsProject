
// MainDlg.h : ���� ���������
//

#pragma once
#include "afxcmn.h"


// ���������� ���� CMainlDlg
class CMainlDlg : public CDialogEx
{
// ��������
public:
	CMainlDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
	enum { IDD = IDD_MYFIREWALL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickFireWallOn();
	afx_msg void OnClickFireWallOff();
	int FireOff();
	int FireOn();
	afx_msg void OnClickShowRule();
	int showAllRules();
	CListCtrl m_ctrlList;
};
