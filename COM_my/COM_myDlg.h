
// COM_myDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "mscomm_com.h"

#define TIMER_AUTO_SEND 1
#define TIMER_COM_CHECK 2
// CCOM_myDlg 对话框
class CCOM_myDlg : public CDialogEx
{
// 构造
public:
	CCOM_myDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COM_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 端口号
	CComboBox m_ComboPortID;
	// 波特率
	CComboBox m_ComboBaudRate;
	// //校验位
	CComboBox m_ComboParityBit;
	// 数据位
	CComboBox m_ComboDataBit;
	// 停止位
	CComboBox m_ComboStopBit;
	// 串口通讯
	CMscomm_com m_ConCom;
	CString m_StrReceive;
//	CEdit m_StrSend;
	// //是否自动换行
	BOOL m_BNewLine;
	// 自动发送
	BOOL m_BAutoSend;
	// 周期
//	int nPeriod_ms;
	// 保存// 保存
	CButton m_CButton_Save;
	// 打开关闭串口
	CButton m_CButton_Switch;
	afx_msg void OnBnClickedButtonSwitch();
	afx_msg void OnCbnSelchangeComboBaudrate();
	afx_msg void OnCbnSelchangeComboStopBit();
	DECLARE_EVENTSINK_MAP()
	void OnOncommMscommCom();
	afx_msg void OnBnClickedButtonSend();
	// 发送区
	CString m_strSend;
	afx_msg void OnBnClickedButtonClearReceiveArea();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// 自动发送周期
	int m_nPeriod;
	afx_msg void OnBnClickedCheckAutoSend();
	afx_msg void OnBnClickedCheckNewline();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonOpen();
};
