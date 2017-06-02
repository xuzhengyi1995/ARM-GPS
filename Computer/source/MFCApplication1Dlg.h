
// MFCApplication1Dlg.h : 头文件
//

#pragma once
#include "CWebBrowser2.h"
#include "Com.h"
#include "afxwin.h"
#define TIMEID1 1
#define TIMEID2 2

// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// 标准构造函数
	afx_msg void OnTimer(UINT nIDEvent);
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	char received[60];
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	//afx_msg void OnBnClickedCancel();
	//afx_msg void OnEnChangeRichedit21();
	//afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	void map_go();
	char temp[30];
	int t_p;
	CWebBrowser2 web;
	CEdit Condition_disp;
	DECLARE_EVENTSINK_MAP()
	void DocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT* URL);
	CFont *time_font;
	CFont *position_font;
	CFont *info_font;
	CStatic Time_disp;
	CStatic Position_disp;
	CStatic Speed_disp;
	CStatic Th_disp;
};
