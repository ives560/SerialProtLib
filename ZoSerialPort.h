#pragma once

#include"ZoSerialDevice.h"

#define WM_COMMSG WM_USER + 1

class ZoSerialPort:public ZoSerialDevice
{

public:
	ZoSerialPort();
	~ZoSerialPort();


public:
	CWinThread* threadHandle;
	HWND wndHandle;

public:
	int String2Hex(CString str, CByteArray& senddate);
	char ConvertHexChar(char ch);

	static UINT __cdecl ThreadReceiveData(LPVOID lpParameter);
	bool open();
	void setPortName(string name, HWND hwnd=NULL);
	int WritePort(CString str, bool ishex);
	CString ReadPort(bool ishex);
};

