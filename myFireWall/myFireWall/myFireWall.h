
// myFireWall.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CmyApp:
// � ���������� ������� ������ ��. myFireWall.cpp
//

class CmyApp : public CWinApp
{
public:
	CmyApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CmyApp theApp;