
// SerialProtLibDlg.h : ͷ�ļ�
//

#pragma once

#include "ZoSerialPort.h"

// CSerialProtLibDlg �Ի���
class CSerialProtLibDlg : public CDialogEx
{
// ����
public:
	CSerialProtLibDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SERIALPROTLIB_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	ZoSerialPort serialPort;


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strRxData;
	CString m_strTxData;
	afx_msg void OnCbnSelchangeComboCommselect();
	afx_msg void OnCbnSelchangeComboBaudrateSelect();
	afx_msg void OnCbnSelchangeComboDateSelect();
	afx_msg void OnCbnSelchangeComboStopbit();
	afx_msg void OnCbnSelchangeComboParitycheck();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonSend();
	CString m_portName;
	CString m_baudRate;
protected:
	afx_msg LRESULT OnComm(WPARAM wParam, LPARAM lParam);
public:
	BOOL m_RxHex;
	BOOL m_TxHex;
};
