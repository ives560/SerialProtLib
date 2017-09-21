
// SerialProtLibDlg.h : 头文件
//

#pragma once

#include "ZoSerialPort.h"

// CSerialProtLibDlg 对话框
class CSerialProtLibDlg : public CDialogEx
{
// 构造
public:
	CSerialProtLibDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SERIALPROTLIB_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	ZoSerialPort serialPort;


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
