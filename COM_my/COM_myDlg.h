
// COM_myDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "mscomm_com.h"

#define TIMER_AUTO_SEND 1
#define TIMER_COM_CHECK 2
// CCOM_myDlg �Ի���
class CCOM_myDlg : public CDialogEx
{
// ����
public:
	CCOM_myDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COM_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// �˿ں�
	CComboBox m_ComboPortID;
	// ������
	CComboBox m_ComboBaudRate;
	// //У��λ
	CComboBox m_ComboParityBit;
	// ����λ
	CComboBox m_ComboDataBit;
	// ֹͣλ
	CComboBox m_ComboStopBit;
	// ����ͨѶ
	CMscomm_com m_ConCom;
	CString m_StrReceive;
//	CEdit m_StrSend;
	// //�Ƿ��Զ�����
	BOOL m_BNewLine;
	// �Զ�����
	BOOL m_BAutoSend;
	// ����
//	int nPeriod_ms;
	// ����// ����
	CButton m_CButton_Save;
	// �򿪹رմ���
	CButton m_CButton_Switch;
	afx_msg void OnBnClickedButtonSwitch();
	afx_msg void OnCbnSelchangeComboBaudrate();
	afx_msg void OnCbnSelchangeComboStopBit();
	DECLARE_EVENTSINK_MAP()
	void OnOncommMscommCom();
	afx_msg void OnBnClickedButtonSend();
	// ������
	CString m_strSend;
	afx_msg void OnBnClickedButtonClearReceiveArea();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// �Զ���������
	int m_nPeriod;
	afx_msg void OnBnClickedCheckAutoSend();
	afx_msg void OnBnClickedCheckNewline();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonOpen();
};
