
// COM_myDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "COM_my.h"
#include "COM_myDlg.h"
#include "afxdialogex.h"

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


// CCOM_myDlg 对话框



CCOM_myDlg::CCOM_myDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COM_MY_DIALOG, pParent)
	, m_StrReceive(_T(""))
	, m_BNewLine(FALSE)
	, m_BAutoSend(FALSE)
	, m_strSend(_T(""))
	, m_nPeriod(1000)
{

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CCOM_myDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PORT, m_ComboPortID);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_ComboBaudRate);
	DDX_Control(pDX, IDC_COMBO_PARITY_BIT, m_ComboParityBit);
	DDX_Control(pDX, IDC_COMBO_DATA_BIT, m_ComboDataBit);
	DDX_Control(pDX, IDC_COMBO_STOP_BIT, m_ComboStopBit);
	DDX_Control(pDX, IDC_MSCOMM_COM, m_ConCom);
	DDX_Text(pDX, IDC_EDIT_RECEIVE, m_StrReceive);
	//  DDX_Control(pDX, IDC_EDIT_SEND, m_StrSend);
	DDX_Check(pDX, IDC_CHECK_NEWLINE, m_BNewLine);
	DDX_Check(pDX, IDC_CHECK_AUTO_SEND, m_BAutoSend);
	//  DDX_Text(pDX, IDC_EDIT_PERIOD, nPeriod_ms);
	//  DDX_Control(pDX, IDC_BUTTON_SAVE, CButtonSave);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_CButton_Save);
	DDX_Control(pDX, IDC_BUTTON_SWITCH, m_CButton_Switch);
	DDX_Text(pDX, IDC_EDIT_SEND, m_strSend);
	DDX_Text(pDX, IDC_EDIT_PERIOD, m_nPeriod);
}

BEGIN_MESSAGE_MAP(CCOM_myDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SWITCH, &CCOM_myDlg::OnBnClickedButtonSwitch)
	ON_CBN_SELCHANGE(IDC_COMBO_BAUDRATE, &CCOM_myDlg::OnCbnSelchangeComboBaudrate)
	ON_CBN_SELCHANGE(IDC_COMBO_STOP_BIT, &CCOM_myDlg::OnCbnSelchangeComboStopBit)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CCOM_myDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_RECEIVE_AREA, &CCOM_myDlg::OnBnClickedButtonClearReceiveArea)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_AUTO_SEND, &CCOM_myDlg::OnBnClickedCheckAutoSend)
	ON_BN_CLICKED(IDC_CHECK_NEWLINE, &CCOM_myDlg::OnBnClickedCheckNewline)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CCOM_myDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CCOM_myDlg::OnBnClickedButtonOpen)
END_MESSAGE_MAP()


// CCOM_myDlg 消息处理程序

BOOL CCOM_myDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	//设置下拉栏默认选择
	m_ComboBaudRate.SetCurSel(0);
	m_ComboDataBit.SetCurSel(3);
	m_ComboParityBit.SetCurSel(2);
	m_ComboStopBit.SetCurSel(0);
	//获取串口列表 设置下拉串口
	SetTimer(TIMER_COM_CHECK, 1000, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCOM_myDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCOM_myDlg::OnPaint()
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
HCURSOR CCOM_myDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCOM_myDlg::OnBnClickedButtonSwitch()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_ConCom.get_PortOpen())//已打开串口 
	{
		m_ConCom.put_PortOpen(FALSE);//关闭串口
		m_CButton_Switch.SetWindowText("打开串口");
	}
	else//未打开串口
	{
		//获取端口号
		CString strPortID;
		m_ComboPortID.GetWindowText(strPortID);
		int nID=atol(strPortID.TrimLeft("COM"));//删减COM得端口号，str转换为int
		//获取波特率
		CString strBaudRate;
		m_ComboBaudRate.GetWindowText(strBaudRate);
		//获取校验位 无；奇；偶
		CString strParityBit;
		m_ComboParityBit.GetWindowText(strParityBit);
		if (strParityBit == "无")
			strParityBit = "n";
		else if (strParityBit == "奇")
			strParityBit = "o";
		else//偶
			strParityBit = "e";
		//获取数据位
		CString strDataBit;
		m_ComboDataBit.GetWindowText(strDataBit);
		//获取停止位
		CString strStopBit;
		m_ComboStopBit.GetWindowText(strStopBit);
		//配置参数
		CString strSetting= strBaudRate+","+ strParityBit + "," + strDataBit+","+ strStopBit;

		m_ConCom.put_CommPort(nID);//选择端口
		m_ConCom.put_Settings(strSetting);//设置
		m_ConCom.put_PortOpen(TRUE);//打开端口

		m_ConCom.put_InputMode(1);//输入方式为二进制
		m_ConCom.put_RThreshold(1);
		m_ConCom.put_InputLen(0);//设置当前接收区为零，重置接收区
		m_ConCom.get_Input();//读取缓存区，覆盖缓存区残留数据 发送区
		
		//打开串口结束，将控件修改为关闭串口，下次点击可关闭
		m_CButton_Switch.SetWindowText("关闭串口");

	}
}


void CCOM_myDlg::OnCbnSelchangeComboBaudrate()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCOM_myDlg::OnCbnSelchangeComboStopBit()
{
	// TODO: 在此添加控件通知处理程序代码
}
BEGIN_EVENTSINK_MAP(CCOM_myDlg, CDialogEx)
	ON_EVENT(CCOM_myDlg, IDC_MSCOMM_COM, 1, CCOM_myDlg::OnOncommMscommCom, VTS_NONE)
END_EVENTSINK_MAP()


void CCOM_myDlg::OnOncommMscommCom()//单击发送按钮触发
{
	// TODO: 在此处添加消息处理程序代码
	COleSafeArray safeArray_inp;
	//串口控件可识别的数组
	BYTE rxdata[2048];
	//char数组存储
	CString strtemp;
	if (m_ConCom.get_CommEvent()==2)//缓存区有字符 接收事件
	{
		safeArray_inp = m_ConCom.get_Input();//获取mscomm控件缓存区数据
		int len = safeArray_inp.GetOneDimSize();//有效数据长度
		for (long k=0;k<len ;k++)
		{
			safeArray_inp.GetElement(&k,rxdata+k);//安全数组元素依次存入字符串
		}
		rxdata[len] = '\0';//字符串最后一位为0
		strtemp.Format("%s", rxdata);
		m_StrReceive += strtemp;
		UpdateData(FALSE);//刷新至对话框
	}

}


void CCOM_myDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strSwitch;
	m_CButton_Switch.GetWindowText(strSwitch);
	UpdateData(TRUE);
	if (strSwitch == "关闭串口")
	{
		if (m_BAutoSend == 1)
		{
			SetTimer(TIMER_AUTO_SEND,m_nPeriod,NULL);//隔m_nPeriod ms发送一次数据
		}
		else
		{
			UpdateData(TRUE);//接收
			if(m_BNewLine==1)//自动换行
				m_strSend += "\n";
			m_ConCom.put_Output(COleVariant(m_strSend));//发送区内容发送到mscomm控件
		}
	}
	else
		AfxMessageBox("请先打开串口！");
}


void CCOM_myDlg::OnBnClickedButtonClearReceiveArea()
{
	// TODO: 在此添加控件通知处理程序代码
	//清空接收区
	m_StrReceive.Empty();
	UpdateData(FALSE);//刷新界面

}


void CCOM_myDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case TIMER_AUTO_SEND:
		UpdateData(TRUE);//接收
		if (m_BNewLine == 1)//自动换行
			m_strSend += "\n";
		m_ConCom.put_Output(COleVariant(m_strSend));//发送区内容发送到mscomm控件

		break;
	case TIMER_COM_CHECK:
		const int COM_NUM = 15;//最大串口数
		int i = 1;
		for (i = 1; i <= COM_NUM; i++)//循环COM_NUM次，串口数最多的情况
		{
			//形成原始设备名称
			CString sPort;
			sPort.Format(_T("\\\\.\\COM%d"), i);
			//尝试打开该端口
			BOOL bSuccess = FALSE;
			HANDLE hPort = ::CreateFile(sPort, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);

			//添加串口号
			CString strPortID;
			strPortID.Empty();
			strPortID.AppendFormat("COM%d", i);

			if (hPort == INVALID_HANDLE_VALUE)
				//串口打开失败
			{
				DWORD dwError = GetLastError();

				if (dwError == ERROR_ACCESS_DENIED)
				{
					bSuccess = TRUE;
				}
				int nDelIndex = m_ComboPortID.FindStringExact(-1, strPortID);
				if(nDelIndex!= CB_ERR)//串口存在列表中，则删除串口
					m_ComboPortID.DeleteString(nDelIndex);
			}
			else
			{
				//该端口已成功打开
				bSuccess = TRUE;
				//不要忘记关闭端口，因为我们不会对它做任何事情
				CloseHandle(hPort);
				if (m_ComboPortID.FindStringExact(-1, strPortID)== CB_ERR)//若串口不存在，则添加串口
					m_ComboPortID.AddString(strPortID);
			}
		}
		break;

	}
	CDialogEx::OnTimer(nIDEvent);

}


void CCOM_myDlg::OnBnClickedCheckAutoSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//获取勾选状态
	if (m_BAutoSend==0)
	{
		KillTimer(TIMER_AUTO_SEND);
	}
	else
	{
	}
}


void CCOM_myDlg::OnBnClickedCheckNewline()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCOM_myDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fdlgData(FALSE, NULL, NULL, OFN_OVERWRITEPROMPT, "txt|*.txt||");
	if (fdlgData.DoModal()!=IDOK)
	{
		return;
	}
	CString strSavingPath = fdlgData.GetPathName();
	CStdioFile fReceivingData(strSavingPath, CFile::modeCreate | CFile::modeWrite);
	fReceivingData.Write(m_StrReceive,m_StrReceive.GetLength());
	fReceivingData.Close();

}


void CCOM_myDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strBuffer;
	CFileDialog fdlgData(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, "txt|*.txt||");
	if (fdlgData.DoModal() != IDOK)
	{
		return;
	}
	CString strOpeningPath = fdlgData.GetPathName();
	CStdioFile fSendingData(strOpeningPath, CFile::modeRead);
	while (fSendingData.ReadString(strBuffer))
	{
		m_strSend += strBuffer+"\n";
	}
	UpdateData(FALSE);
}
