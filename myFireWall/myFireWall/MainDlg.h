
// MainDlg.h : файл заголовка
//

#pragma once
#include "afxcmn.h"


// диалоговое окно CMainlDlg
class CMainlDlg : public CDialogEx
{
// Создание
public:
	CMainlDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_MYFIREWALL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
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
