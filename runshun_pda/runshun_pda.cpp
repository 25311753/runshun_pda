// runshun_pda.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "runshun_pda.h"
#include "runshun_pdaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Crunshun_pdaApp

BEGIN_MESSAGE_MAP(Crunshun_pdaApp, CWinApp)
END_MESSAGE_MAP()


// Crunshun_pdaApp ����
Crunshun_pdaApp::Crunshun_pdaApp()
	: CWinApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� Crunshun_pdaApp ����
Crunshun_pdaApp theApp;

// Crunshun_pdaApp ��ʼ��

BOOL Crunshun_pdaApp::InitInstance()
{

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	Crunshun_pdaDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
		//  �Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
