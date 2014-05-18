// runshun_pdaDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "runshun_pda.h"
#include "runshun_pdaDlg.h"
#include <afxinet.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MODEL_SINGLE 0
#define MODEL_BATCH 1
#define STATUS_PASS 0
#define STATUS_YJFXT 1
#define ONLINE 0
#define OFFLINE 1

// Crunshun_pdaDlg �Ի���

Crunshun_pdaDlg::Crunshun_pdaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Crunshun_pdaDlg::IDD, pParent)
	, m_edt_cid(_T(""))
	, m_rd_model(0)
	, m_status2(0)
	, m_rd_onoff(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Crunshun_pdaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_CID, m_edt_cid);
	DDX_Control(pDX, IDC_LST_CID_STATUS, m_lst_cid_status);
	DDX_Radio(pDX, IDC_RD_PASS2, m_status2);
	DDV_MinMaxInt(pDX, m_status2, 0, 1);
	DDX_Radio(pDX, IDC_RD_ONLINE, m_rd_onoff);
}

BEGIN_MESSAGE_MAP(Crunshun_pdaDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_CLEAR, &Crunshun_pdaDlg::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_EXIT, &Crunshun_pdaDlg::OnBnClickedBtnExit)
	ON_BN_CLICKED(IDC_RD_ONLINE, &Crunshun_pdaDlg::OnBnClickedRdOnline)
	ON_BN_CLICKED(IDC_RD_OFFLINE, &Crunshun_pdaDlg::OnBnClickedRdOffline)
	ON_BN_CLICKED(IDC_BTN_DUMP, &Crunshun_pdaDlg::OnBnClickedBtnDump)
	ON_BN_CLICKED(IDC_RD_PASS2, &Crunshun_pdaDlg::OnBnClickedRdPass2)
	ON_BN_CLICKED(IDC_RD_YJFXT2, &Crunshun_pdaDlg::OnBnClickedRdYjfxt2)
END_MESSAGE_MAP()


// Crunshun_pdaDlg ��Ϣ�������

BOOL Crunshun_pdaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//init list control
	m_lst_cid_status.ModifyStyle( 0, LVS_REPORT );               // ����ģʽ  
	m_lst_cid_status.SetExtendedStyle(m_lst_cid_status.GetExtendedStyle() \
		| LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT ); 
	m_lst_cid_status.InsertColumn(0,_T("����"));
	m_lst_cid_status.InsertColumn(1,_T("״̬"));
	CRect rect;  
	m_lst_cid_status.GetClientRect(rect); //��õ�ǰ�ͻ�����Ϣ  
	m_lst_cid_status.SetColumnWidth(0, rect.Width() * 1/ 2); //�����еĿ�ȡ�  
	m_lst_cid_status.SetColumnWidth(1, rect.Width() * 1/ 2);  

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void Crunshun_pdaDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_RUNSHUN_PDA_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_RUNSHUN_PDA_DIALOG));
	}
}
#endif





void Crunshun_pdaDlg::OnBnClickedBtnClear()
{
	m_lst_cid_status.DeleteAllItems();
	GetDlgItem(IDC_EDT_CID)-> SetFocus(); 
}

void Crunshun_pdaDlg::OnBnClickedBtnExit()
{
	DestroyWindow();
}

void Crunshun_pdaDlg::OnBnClickedRdOnline()
{
	GetDlgItem(IDC_BTN_DUMP)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_CID)-> SetFocus(); 
}

void Crunshun_pdaDlg::OnBnClickedRdOffline()
{
	GetDlgItem(IDC_BTN_DUMP)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT_CID)-> SetFocus(); 
}

void Crunshun_pdaDlg::OnBnClickedRdPass2()
{
	GetDlgItem(IDC_EDT_CID)-> SetFocus(); 
}

void Crunshun_pdaDlg::OnBnClickedRdYjfxt2()
{
	GetDlgItem(IDC_EDT_CID)-> SetFocus(); 
}

BOOL Crunshun_pdaDlg::chk_dup_cid(CString &cid){
	for (int i=0; i<m_lst_cid_status.GetItemCount(); i++)
	{
		if (cid == m_lst_cid_status.GetItemText(i,0))
		{
			return true;
		}
	}
	return FALSE;
}
BOOL Crunshun_pdaDlg::PreTranslateMessage(MSG* pMsg){
	if(WM_KEYDOWN == pMsg->message)
	{
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDT_CID);
		ASSERT(pEdit);
		if(pMsg->hwnd == pEdit->GetSafeHwnd() && VK_RETURN == pMsg->wParam)
		{
			UpdateData(TRUE);
			if (chk_dup_cid(m_edt_cid))
			{
				AfxMessageBox(_T("�б��Ѵ��ڸõ���"));
				m_edt_cid = "";
				UpdateData(FALSE);
			} 
			else
			{
				switch (m_rd_onoff)
				{
				case ONLINE:
					changeStatus();
					break;
				case OFFLINE:
					loadCidToList();
					break;
				default:
					break;
				}
			}
			return TRUE;
		}else if(VK_RETURN == pMsg->wParam){			
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void Crunshun_pdaDlg::loadCidToList(){
//	UpdateData(TRUE);
	m_lst_cid_status.InsertItem(0, m_edt_cid);
	m_lst_cid_status.SetItemText(0,1,_T("�����ߵ���"));
	m_edt_cid = "";
	UpdateData(FALSE);
}
void Crunshun_pdaDlg::changeStatus(){
//	UpdateData(TRUE);
	CString url;
	CString new_status = m_status2==0?L"����":L"�ѽ�������";
	url.Format(L"/change_status?cid=%s&new_status=%d", m_edt_cid, m_status2);

	try{
		CInternetSession session;
		session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000 * 20);
		session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);
		session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);

		CHttpConnection* pConnection = session.GetHttpConnection( TEXT("124.173.70.227"),(INTERNET_PORT)37964);
		CHttpFile* pFile = pConnection->OpenRequest( CHttpConnection::HTTP_VERB_GET, url);

		pFile->SendRequest();

		DWORD dwRet;
		pFile->QueryInfoStatusCode(dwRet);
	//	CString status = L"";
		if(dwRet != HTTP_STATUS_OK)
		{
			if (dwRet == HTTP_STATUS_NOT_FOUND)
			{
				AfxMessageBox(L"���Ų�����");
			} 
			else
			{
				CString errText;
				errText.Format(L"���������룺%d", dwRet);
				AfxMessageBox(errText);
			}
			session.Close();
			pFile->Close(); 
			delete pFile;
			m_edt_cid = "";
			UpdateData(FALSE);
			GetDlgItem(IDC_EDT_CID)-> SetFocus(); 
			return;
		}

		session.Close();
		pFile->Close(); 
		delete pFile;
		pFile = NULL;

		m_lst_cid_status.InsertItem(0, m_edt_cid);
		m_lst_cid_status.SetItemText(0,1,new_status);
	}catch (CInternetException *pEx)
	{
		TCHAR pszError[64] = {0};
		pEx->GetErrorMessage(pszError, 64);
//		_tprintf_s(_T("%63s"), pszError);
		AfxMessageBox(pszError);
	}

	//refresh data
	m_edt_cid = "";
	UpdateData(FALSE);
	GetDlgItem(IDC_EDT_CID)-> SetFocus(); 
}


void Crunshun_pdaDlg::OnBnClickedBtnDump()
{
	CFileDialog fileDlg(FALSE);
	fileDlg.m_ofn.lpstrTitle=_T("���ű��浽�ļ�");
	fileDlg.m_ofn.lpstrFilter=_T("Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0");
	fileDlg.m_ofn.lpstrDefExt=_T("txt");
	if(IDOK==fileDlg.DoModal())
	{
//		AfxMessageBox(fileDlg.GetPathName());
		CFile file(fileDlg.GetPathName(),CFile::modeCreate | CFile::modeWrite);
		WORD unicode = 0xFEFF;//UNICODE�����ļ�ͷ  
		file.Write(&unicode,2);
		CString strCid;
		for (int i=0; i<m_lst_cid_status.GetItemCount(); i++)
		{
			strCid = m_lst_cid_status.GetItemText(i,0) + _T(" ") + m_lst_cid_status.GetItemText(i,1) + _T("\r\n");
			file.Write(strCid,wcslen(strCid)*sizeof(wchar_t));
		}
		file.Close();
	}
		GetDlgItem(IDC_EDT_CID)-> SetFocus(); 
}

