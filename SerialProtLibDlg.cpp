
// SerialProtLibDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SerialProtLib.h"
#include "SerialProtLibDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSerialProtLibDlg 对话框



CSerialProtLibDlg::CSerialProtLibDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSerialProtLibDlg::IDD, pParent)
	, m_strRxData(_T(""))
	, m_strTxData(_T(""))
	, m_portName(_T(""))
	, m_baudRate(_T(""))
	, m_RxHex(FALSE)
	, m_TxHex(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSerialProtLibDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RXDATA, m_strRxData);
	DDX_Text(pDX, IDC_EDIT_TXDATA, m_strTxData);
	DDX_CBString(pDX, IDC_COMBO_CommSelect, m_portName);
	DDX_CBString(pDX, IDC_COMBO_BaudRate_Select, m_baudRate);
	DDX_Check(pDX, IDC_CHECK_RX_HEX, m_RxHex);
	DDX_Check(pDX, IDC_CHECK_TX_HEX, m_TxHex);
}

BEGIN_MESSAGE_MAP(CSerialProtLibDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_CommSelect, &CSerialProtLibDlg::OnCbnSelchangeComboCommselect)
	ON_CBN_SELCHANGE(IDC_COMBO_BaudRate_Select, &CSerialProtLibDlg::OnCbnSelchangeComboBaudrateSelect)
	ON_CBN_SELCHANGE(IDC_COMBO_Date_Select, &CSerialProtLibDlg::OnCbnSelchangeComboDateSelect)
	ON_CBN_SELCHANGE(IDC_COMBO_StopBit, &CSerialProtLibDlg::OnCbnSelchangeComboStopbit)
	ON_CBN_SELCHANGE(IDC_COMBO_ParityCheck, &CSerialProtLibDlg::OnCbnSelchangeComboParitycheck)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CSerialProtLibDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CSerialProtLibDlg::OnBnClickedButtonSend)
	ON_MESSAGE(WM_COMMSG, &CSerialProtLibDlg::OnComm)
END_MESSAGE_MAP()


// CSerialProtLibDlg 消息处理程序

BOOL CSerialProtLibDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	((CComboBox*)GetDlgItem(IDC_COMBO_CommSelect))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_BaudRate_Select))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_Date_Select))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_StopBit))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_ParityCheck))->SetCurSel(0);
	OnCbnSelchangeComboCommselect();
	OnCbnSelchangeComboBaudrateSelect();
	OnCbnSelchangeComboDateSelect();
	OnCbnSelchangeComboStopbit();
	OnCbnSelchangeComboParitycheck();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSerialProtLibDlg::OnPaint()
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
HCURSOR CSerialProtLibDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSerialProtLibDlg::OnCbnSelchangeComboCommselect()
{
	// TODO:  在此添加控件通知处理程序代码
	int select = ((CComboBox*)GetDlgItem(IDC_COMBO_CommSelect))->GetCurSel();
	CString name;
	((CComboBox*)GetDlgItem(IDC_COMBO_CommSelect))->GetLBText(select, name);
	serialPort.setPortName(name.GetString(),this->GetSafeHwnd());

}

//波特率
void CSerialProtLibDlg::OnCbnSelchangeComboBaudrateSelect()
{
	// TODO:  在此添加控件通知处理程序代码

	UpdateData(true);
	int select = ((CComboBox*)GetDlgItem(IDC_COMBO_BaudRate_Select))->GetCurSel();

	switch (select)
	{
	case 1:
		serialPort.setBaudRate(14400);
		break;
	case 2:
		serialPort.setBaudRate(19200);
		break;
	case 3:
		serialPort.setBaudRate(38400);
		break;
	case 4:
		serialPort.setBaudRate(5600);
		break;
	case 5:
		serialPort.setBaudRate(57600);
		break;
	case 6:
		serialPort.setBaudRate(115200);
		break;
	case 7:
		serialPort.setBaudRate(128000);
		break;
	case 8:
		serialPort.setBaudRate(256000);
		break;
	default:
		serialPort.setBaudRate(9600);
		break;
	}

	UpdateData(false);
}


void CSerialProtLibDlg::OnCbnSelchangeComboDateSelect()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	int select = ((CComboBox*)GetDlgItem(IDC_COMBO_Date_Select))->GetCurSel();

	switch (select)
	{
	case 1:
		serialPort.setDataBits(ZoSerialPort::Data7);
		break;
	case 2:
		serialPort.setDataBits(ZoSerialPort::Data6);
		break;
	case 3:
		serialPort.setDataBits(ZoSerialPort::Data5);
		break;
	default:
		serialPort.setDataBits(ZoSerialPort::Data8);
		break;
	}
}


void CSerialProtLibDlg::OnCbnSelchangeComboStopbit()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	int select = ((CComboBox*)GetDlgItem(IDC_COMBO_StopBit))->GetCurSel();

	switch (select)
	{
	case 1:
		serialPort.setStopBits(ZoSerialPort::TwoStop);
		break;
	default:
		serialPort.setStopBits(ZoSerialPort::OneStop);
		break;
	}
}


void CSerialProtLibDlg::OnCbnSelchangeComboParitycheck()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	int select = ((CComboBox*)GetDlgItem(IDC_COMBO_ParityCheck))->GetCurSel();

	switch (select)
	{
	case 1:
		serialPort.setParity(ZoSerialPort::OddParity);
		break;
	case 2:
		serialPort.setParity(ZoSerialPort::EvenParity);
		break;
	default:
		serialPort.setParity(ZoSerialPort::NoParity);
		break;
	}
}

//打开关闭串口
void CSerialProtLibDlg::OnBnClickedButtonOpen()
{
	// TODO:  在此添加控件通知处理程序代码
	if (serialPort.isOpen() == true)
	{
		serialPort.close();
		SetDlgItemText(IDC_BUTTON_OPEN, _T("打开串口"));
	}
	else
	{
		serialPort.open();
		SetDlgItemText(IDC_BUTTON_OPEN, _T("关闭串口"));
	}
}

//发送数据
void CSerialProtLibDlg::OnBnClickedButtonSend()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);

	serialPort.WritePort(m_strTxData, m_TxHex);
	
}


afx_msg LRESULT CSerialProtLibDlg::OnComm(WPARAM wParam, LPARAM lParam)
{

	UpdateData(true);
	m_strRxData += serialPort.ReadPort(m_RxHex);
	UpdateData(false);
	return 0;
}
