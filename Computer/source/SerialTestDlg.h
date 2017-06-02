#pragma once
#include "afxwin.h"


// CSerialTestDlg 对话框
//afx_msg void OnCommRecv(WPARAM wParam, LPARAM lParam);
class CSerialTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSerialTestDlg)

public:
	CSerialTestDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSerialTestDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_COM };
#endif

protected:
	void CSerialTestDlg::OnCancel();
	virtual BOOL CSerialTestDlg::OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void CSerialTestDlg::FindAllCom();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_combo_com_list;
};
