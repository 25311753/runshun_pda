// runshun_pda.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#ifdef STANDARDSHELL_UI_MODEL
#include "resource.h"
#endif

// Crunshun_pdaApp:
// �йش����ʵ�֣������ runshun_pda.cpp
//

class Crunshun_pdaApp : public CWinApp
{
public:
	Crunshun_pdaApp();
	
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Crunshun_pdaApp theApp;
