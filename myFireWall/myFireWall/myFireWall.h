
// myFireWall.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CmyApp:
// О реализации данного класса см. myFireWall.cpp
//

class CmyApp : public CWinApp
{
public:
	CmyApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CmyApp theApp;