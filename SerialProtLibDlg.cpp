
// SerialProtLibDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SerialProtLib.h"
#include "SerialProtLibDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSerialProtLibDlg �Ի���



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


// CSerialProtLibDlg ��Ϣ�������

BOOL CSerialProtLibDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSerialProtLibDlg::OnPaint()
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
HCURSOR CSerialProtLibDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSerialProtLibDlg::OnCbnSelchangeComboCommselect()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int select = ((CComboBox*)GetDlgItem(IDC_COMBO_CommSelect))->GetCurSel();
	CString name;
	((CComboBox*)GetDlgItem(IDC_COMBO_CommSelect))->GetLBText(select, name);
	serialPort.setPortName(name.GetString(),this->GetSafeHwnd());

}

//������
void CSerialProtLibDlg::OnCbnSelchangeComboBaudrateSelect()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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

//�򿪹رմ���
void CSerialProtLibDlg::OnBnClickedButtonOpen()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (serialPort.isOpen() == true)
	{
		serialPort.close();
		SetDlgItemText(IDC_BUTTON_OPEN, _T("�򿪴���"));
	}
	else
	{
		serialPort.open();
		SetDlgItemText(IDC_BUTTON_OPEN, _T("�رմ���"));
	}
}

//��������
void CSerialProtLibDlg::OnBnClickedButtonSend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
