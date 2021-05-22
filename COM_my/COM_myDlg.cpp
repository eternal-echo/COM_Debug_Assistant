
// COM_myDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "COM_my.h"
#include "COM_myDlg.h"
#include "afxdialogex.h"

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


// CCOM_myDlg �Ի���



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


// CCOM_myDlg ��Ϣ�������

BOOL CCOM_myDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	//����������Ĭ��ѡ��
	m_ComboBaudRate.SetCurSel(0);
	m_ComboDataBit.SetCurSel(3);
	m_ComboParityBit.SetCurSel(2);
	m_ComboStopBit.SetCurSel(0);
	//��ȡ�����б� ������������
	SetTimer(TIMER_COM_CHECK, 1000, NULL);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCOM_myDlg::OnPaint()
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
HCURSOR CCOM_myDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCOM_myDlg::OnBnClickedButtonSwitch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_ConCom.get_PortOpen())//�Ѵ򿪴��� 
	{
		m_ConCom.put_PortOpen(FALSE);//�رմ���
		m_CButton_Switch.SetWindowText("�򿪴���");
	}
	else//δ�򿪴���
	{
		//��ȡ�˿ں�
		CString strPortID;
		m_ComboPortID.GetWindowText(strPortID);
		int nID=atol(strPortID.TrimLeft("COM"));//ɾ��COM�ö˿ںţ�strת��Ϊint
		//��ȡ������
		CString strBaudRate;
		m_ComboBaudRate.GetWindowText(strBaudRate);
		//��ȡУ��λ �ޣ��棻ż
		CString strParityBit;
		m_ComboParityBit.GetWindowText(strParityBit);
		if (strParityBit == "��")
			strParityBit = "n";
		else if (strParityBit == "��")
			strParityBit = "o";
		else//ż
			strParityBit = "e";
		//��ȡ����λ
		CString strDataBit;
		m_ComboDataBit.GetWindowText(strDataBit);
		//��ȡֹͣλ
		CString strStopBit;
		m_ComboStopBit.GetWindowText(strStopBit);
		//���ò���
		CString strSetting= strBaudRate+","+ strParityBit + "," + strDataBit+","+ strStopBit;

		m_ConCom.put_CommPort(nID);//ѡ��˿�
		m_ConCom.put_Settings(strSetting);//����
		m_ConCom.put_PortOpen(TRUE);//�򿪶˿�

		m_ConCom.put_InputMode(1);//���뷽ʽΪ������
		m_ConCom.put_RThreshold(1);
		m_ConCom.put_InputLen(0);//���õ�ǰ������Ϊ�㣬���ý�����
		m_ConCom.get_Input();//��ȡ�����������ǻ������������� ������
		
		//�򿪴��ڽ��������ؼ��޸�Ϊ�رմ��ڣ��´ε���ɹر�
		m_CButton_Switch.SetWindowText("�رմ���");

	}
}


void CCOM_myDlg::OnCbnSelchangeComboBaudrate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCOM_myDlg::OnCbnSelchangeComboStopBit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
BEGIN_EVENTSINK_MAP(CCOM_myDlg, CDialogEx)
	ON_EVENT(CCOM_myDlg, IDC_MSCOMM_COM, 1, CCOM_myDlg::OnOncommMscommCom, VTS_NONE)
END_EVENTSINK_MAP()


void CCOM_myDlg::OnOncommMscommCom()//�������Ͱ�ť����
{
	// TODO: �ڴ˴������Ϣ����������
	COleSafeArray safeArray_inp;
	//���ڿؼ���ʶ�������
	BYTE rxdata[2048];
	//char����洢
	CString strtemp;
	if (m_ConCom.get_CommEvent()==2)//���������ַ� �����¼�
	{
		safeArray_inp = m_ConCom.get_Input();//��ȡmscomm�ؼ�����������
		int len = safeArray_inp.GetOneDimSize();//��Ч���ݳ���
		for (long k=0;k<len ;k++)
		{
			safeArray_inp.GetElement(&k,rxdata+k);//��ȫ����Ԫ�����δ����ַ���
		}
		rxdata[len] = '\0';//�ַ������һλΪ0
		strtemp.Format("%s", rxdata);
		m_StrReceive += strtemp;
		UpdateData(FALSE);//ˢ�����Ի���
	}

}


void CCOM_myDlg::OnBnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strSwitch;
	m_CButton_Switch.GetWindowText(strSwitch);
	UpdateData(TRUE);
	if (strSwitch == "�رմ���")
	{
		if (m_BAutoSend == 1)
		{
			SetTimer(TIMER_AUTO_SEND,m_nPeriod,NULL);//��m_nPeriod ms����һ������
		}
		else
		{
			UpdateData(TRUE);//����
			if(m_BNewLine==1)//�Զ�����
				m_strSend += "\n";
			m_ConCom.put_Output(COleVariant(m_strSend));//���������ݷ��͵�mscomm�ؼ�
		}
	}
	else
		AfxMessageBox("���ȴ򿪴��ڣ�");
}


void CCOM_myDlg::OnBnClickedButtonClearReceiveArea()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ս�����
	m_StrReceive.Empty();
	UpdateData(FALSE);//ˢ�½���

}


void CCOM_myDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case TIMER_AUTO_SEND:
		UpdateData(TRUE);//����
		if (m_BNewLine == 1)//�Զ�����
			m_strSend += "\n";
		m_ConCom.put_Output(COleVariant(m_strSend));//���������ݷ��͵�mscomm�ؼ�

		break;
	case TIMER_COM_CHECK:
		const int COM_NUM = 15;//��󴮿���
		int i = 1;
		for (i = 1; i <= COM_NUM; i++)//ѭ��COM_NUM�Σ��������������
		{
			//�γ�ԭʼ�豸����
			CString sPort;
			sPort.Format(_T("\\\\.\\COM%d"), i);
			//���Դ򿪸ö˿�
			BOOL bSuccess = FALSE;
			HANDLE hPort = ::CreateFile(sPort, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);

			//��Ӵ��ں�
			CString strPortID;
			strPortID.Empty();
			strPortID.AppendFormat("COM%d", i);

			if (hPort == INVALID_HANDLE_VALUE)
				//���ڴ�ʧ��
			{
				DWORD dwError = GetLastError();

				if (dwError == ERROR_ACCESS_DENIED)
				{
					bSuccess = TRUE;
				}
				int nDelIndex = m_ComboPortID.FindStringExact(-1, strPortID);
				if(nDelIndex!= CB_ERR)//���ڴ����б��У���ɾ������
					m_ComboPortID.DeleteString(nDelIndex);
			}
			else
			{
				//�ö˿��ѳɹ���
				bSuccess = TRUE;
				//��Ҫ���ǹرն˿ڣ���Ϊ���ǲ���������κ�����
				CloseHandle(hPort);
				if (m_ComboPortID.FindStringExact(-1, strPortID)== CB_ERR)//�����ڲ����ڣ�����Ӵ���
					m_ComboPortID.AddString(strPortID);
			}
		}
		break;

	}
	CDialogEx::OnTimer(nIDEvent);

}


void CCOM_myDlg::OnBnClickedCheckAutoSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);//��ȡ��ѡ״̬
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCOM_myDlg::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
