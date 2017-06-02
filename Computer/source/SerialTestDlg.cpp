// SerialTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "SerialTestDlg.h"
#include "afxdialogex.h"
#include "Com.h"


// CSerialTestDlg �Ի���

IMPLEMENT_DYNAMIC(CSerialTestDlg, CDialogEx)

CSerialTestDlg::CSerialTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_COM, pParent)
{

}

CSerialTestDlg::~CSerialTestDlg()
{
}

void CSerialTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo_com_list);
}


BEGIN_MESSAGE_MAP(CSerialTestDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSerialTestDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

BOOL CSerialTestDlg::OnInitDialog()
{
	this->SetWindowText(L"ѡ�񴮿�");
	CDialogEx::OnInitDialog();
	CSerialTestDlg::FindAllCom();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// CSerialTestDlg ��Ϣ�������

void CSerialTestDlg::FindAllCom()
{
	HKEY hKey;
	int   i = 0;
	TCHAR   portName[256], commName[256];
	DWORD   dwLong, dwSize;

	int rtn = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Hardware\\DeviceMap\\SERIALCOMM", NULL, KEY_READ, &hKey);//�򿪴���ע���  
	if (rtn == ERROR_SUCCESS)
	{
		while (TRUE)
		{
			dwLong = dwSize = sizeof(portName);
			memset(portName, 0, sizeof(portName));
			memset(commName, 0, sizeof(commName));

			rtn = RegEnumValue(hKey, i, portName, &dwLong, NULL, NULL, (PUCHAR)commName, &dwSize);

			if (rtn == ERROR_NO_MORE_ITEMS)   //   ö�ٴ���     
				break;

			m_combo_com_list.AddString(commName);
			i++;
		}
		if (m_combo_com_list.GetCount() == 0) {
			m_combo_com_list.AddString(L"û���ҵ�����");
			//û���ҵ�����  
		}
		RegCloseKey(hKey);
	}
	else
	{
		m_combo_com_list.AddString(L"û���ҵ�����");
	}
}

void CSerialTestDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString temp;
	m_combo_com_list.GetLBText(m_combo_com_list.GetCurSel(),temp);
	com_port = new cnComm;
	com_port->Open(temp);
	//t1.SetWnd(AfxGetMainWnd()->m_hWnd);
	if (com_port->IsOpen())
	{
		CDialogEx::OnOK();
	}
	else 
		MessageBox(L"���ڴ򿪲��ɹ��������ԣ�");
}

void CSerialTestDlg::OnCancel()
{
	exit(0);
}