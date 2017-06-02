
// MFCApplication1Dlg.cpp : 实现文件
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




// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCApplication1Dlg 对话框



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


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	t_p = 0;

	this->SetWindowText(L"单片机监测程序");
	CDialogEx::OnInitDialog();
	VARIANT vt;
	COleVariant vaUrl = _T("http://www.gpsspg.com/maps.htm");
	web.Navigate2(vaUrl, &vt, &vt, &vt, &vt);
	time_font = new CFont;
	time_font->CreatePointFont(400, L"微软雅黑");

	position_font = new CFont;
	position_font->CreatePointFont(200, L"微软雅黑");

	info_font = new CFont;
	info_font->CreatePointFont(120, L"微软雅黑");

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetTimer(TIMEID1, 5000, 0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
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
	for (long i = 0; i <index; i++)//遍历所有元素，通过id属性获取值  
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
			MessageBox(L"检测到数据有误，请注意干扰或单片机距离！");
			time_p = L"校验和不通过";
			position_p = L"校验和不通过";
			speed_p = L"校验和不通过";
			th_p = L"校验和不通过";
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
				time_p = L"UTC：" + time_p;
				position_p = L"定位：" + position_p;
				speed_p = L"速度： " + speed_p + L" KM/H";
				th_p = L"温度/湿度： " + th_p;
				memset(temp, '\0', 30);
				sprintf(temp, "%f,%f", r_s.gps_lati, r_s.gps_long);
			}
			else
			{
				time_p = L"GPS未准备好";
				position_p = L"GPS未准备好";
				speed_p = L"GPS未准备好";
				th_p = L"温度/湿度： " + th_p;
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
