// runshun_pdaDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"

// Crunshun_pdaDlg 对话框
class Crunshun_pdaDlg : public CDialog
{
// 构造
public:
	Crunshun_pdaDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_RUNSHUN_PDA_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void changeStatus();
	void loadCidToList();
	BOOL chk_dup_cid(CString &cid);
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
public:
	CString m_edt_cid;
	CListCtrl m_lst_cid_status;
	int m_rd_model;
	afx_msg void OnBnClickedRdBatch();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnExit();
	int m_status2;
	int m_rd_onoff;
	afx_msg void OnBnClickedRdOnline();
	afx_msg void OnBnClickedRdOffline();
	afx_msg void OnBnClickedBtnDump();
	afx_msg void OnBnClickedRdPass2();
	afx_msg void OnBnClickedRdYjfxt2();
};
