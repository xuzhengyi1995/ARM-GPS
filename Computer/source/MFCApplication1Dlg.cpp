
// MFCApplication1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "CWebBrowser2.h"
#include "Mshtml.h"
#include "resolve.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg �Ի���



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, web);
	DDX_Control(pDX, IDC_EDIT1, Condition_disp);
	DDX_Control(pDX, time_d, Time_disp);
	DDX_Control(pDX, position, Position_disp);
	DDX_Control(pDX, speed, Speed_disp);
	DDX_Control(pDX, th, Th_disp);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	//ON_BN_CLICKED(IDCANCEL, &CMFCApplication1Dlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMFCApplication1Dlg ��Ϣ�������

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	t_p = 0;

	this->SetWindowText(L"��Ƭ��������");
	CDialogEx::OnInitDialog();
	VARIANT vt;
	COleVariant vaUrl = _T("http://www.gpsspg.com/maps.htm");
	web.Navigate2(vaUrl, &vt, &vt, &vt, &vt);
	time_font = new CFont;
	time_font->CreatePointFont(400, L"΢���ź�");

	position_font = new CFont;
	position_font->CreatePointFont(200, L"΢���ź�");

	info_font = new CFont;
	info_font->CreatePointFont(120, L"΢���ź�");

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetTimer(TIMEID1, 5000, 0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	//MessageBox(L"Hello!");
	
}


void CMFCApplication1Dlg::map_go()
{
	BSTR bstrText = _bstr_t(temp);
	
	IHTMLElementCollection *objAllElement = NULL;
	IHTMLDocument2 *objDocument = NULL;

	objDocument = (IHTMLDocument2*)web.get_Document();
	objDocument->get_all(&objAllElement);

	CComPtr<IDispatch>pDisp;
	objAllElement->item(COleVariant(_T("s_t")), COleVariant((long)0), &pDisp);
	CComQIPtr<IHTMLElement, &IID_IHTMLElement>pElement;
	pElement = pDisp;
	pElement->put_innerText(bstrText);

	VARIANT   name;
	CComBSTR   tag;
	long     index;
	objAllElement->get_length(&index);
	name.vt = VT_I4;
	for (long i = 0; i <index; i++)//��������Ԫ�أ�ͨ��id���Ի�ȡֵ  
	{
		name.lVal = i;
		IDispatch   *   pDispatch = NULL;
		objAllElement->item(name, name, &pDispatch);
		IHTMLElement*   spElement;
		pDispatch->QueryInterface(IID_IHTMLElement, (void**)&spElement);
		BSTR   tag;
		spElement->get_id(&tag);
		CString   ss(tag);
		if (ss == "s_btn")
		{
			spElement->click();
		}

		spElement->Release();
	}

}


void CMFCApplication1Dlg::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == 1)
	{
		com_port->Write("G");
		memset(this->received, '\0', 60);
		com_port->ReadString(this->received, 60, 500);

		resolve r_s(received);
		bool is_right = r_s.process();
		CString time_p(r_s.utc_time);
		memset(temp, '\0', 30);
		sprintf(temp, "%f%c,%f%c", r_s.gps_lati, r_s.gps_ns, r_s.gps_long, r_s.gps_ew);
		CString position_p(temp);
		memset(temp, '\0', 30);
		sprintf(temp, "%f", r_s.gps_speed);
		CString speed_p(temp);
		memset(temp, '\0', 30);
		sprintf(temp, "%d C / %d %%", r_s.t, r_s.h);
		CString th_p(temp);
		if (!is_right)
		{
			MessageBox(L"��⵽����������ע����Ż�Ƭ�����룡");
			time_p = L"У��Ͳ�ͨ��";
			position_p = L"У��Ͳ�ͨ��";
			speed_p = L"У��Ͳ�ͨ��";
			th_p = L"У��Ͳ�ͨ��";
		}
		else
		{
			if (r_s._is_gps_ready && r_s.gps_lati != 0)
			{
				if (t_p > 2)
				{
					VARIANT vt;
					COleVariant vaUrl = _T("http://www.gpsspg.com/maps.htm");
					web.Navigate2(vaUrl, &vt, &vt, &vt, &vt);
					t_p = 0;
				}
				++t_p;
				time_p = L"UTC��" + time_p;
				position_p = L"��λ��" + position_p;
				speed_p = L"�ٶȣ� " + speed_p + L" KM/H";
				th_p = L"�¶�/ʪ�ȣ� " + th_p;
				memset(temp, '\0', 30);
				sprintf(temp, "%f,%f", r_s.gps_lati, r_s.gps_long);
			}
			else
			{
				time_p = L"GPSδ׼����";
				position_p = L"GPSδ׼����";
				speed_p = L"GPSδ׼����";
				th_p = L"�¶�/ʪ�ȣ� " + th_p;
			}
		}

		CString str, new_str(received);
		Condition_disp.GetWindowTextW(str);
		str = str + new_str + L"\r\n";
		Condition_disp.SetWindowTextW(str);
		Condition_disp.SetFont(info_font);

		Time_disp.SetWindowTextW(time_p);
		Time_disp.SetFont(time_font);

		Position_disp.SetWindowTextW(position_p);
		Position_disp.SetFont(position_font);

		Speed_disp.SetWindowTextW(speed_p);
		Speed_disp.SetFont(position_font);

		Th_disp.SetWindowTextW(th_p);
		Th_disp.SetFont(position_font);
	}
	else
	{
		map_go();
		KillTimer(2);
	}
}


BEGIN_EVENTSINK_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_EVENT(CMFCApplication1Dlg, IDC_EXPLORER1, 259, CMFCApplication1Dlg::DocumentCompleteExplorer1, VTS_DISPATCH VTS_PVARIANT)
END_EVENTSINK_MAP()


void CMFCApplication1Dlg::DocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT* URL)
{
	SetTimer(TIMEID2, 1000, 0);
}
