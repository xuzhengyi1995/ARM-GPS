
// MFCApplication1Dlg.h : ͷ�ļ�
//

#pragma once
#include "CWebBrowser2.h"
#include "Com.h"
#include "afxwin.h"
#define TIMEID1 1
#define TIMEID2 2

// CMFCApplication1Dlg �Ի���
class CMFCApplication1Dlg : public CDialogEx
{
// ����
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	afx_msg void OnTimer(UINT nIDEvent);
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	char received[60];
	// ���ɵ���Ϣӳ�亯��
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
