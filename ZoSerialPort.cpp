#include "stdafx.h"
#include "ZoSerialPort.h"

ZoSerialPort::ZoSerialPort()
{

}


ZoSerialPort::~ZoSerialPort()
{

}

void ZoSerialPort::setPortName(string name, HWND hwnd/*=NULL*/)
{
	wndHandle = hwnd;

	ZoSerialDevice::setPortName(name);

	bool wasopen = isopen;

	if (wasopen == true)
		close();

	portName = name;

	if (wasopen == true)
		open();
}

bool ZoSerialPort::open()
{
	bool flag = ZoSerialDevice::open();

	if (wndHandle != NULL && flag == true && threadHandle==NULL)
	{
		threadHandle = AfxBeginThread(ThreadReceiveData, this);
	}

	return flag;
}

int ZoSerialPort::WritePort(CString str, bool ishex)
{
	int len;
	if (ishex == true)
	{
		CByteArray array;
		String2Hex(str, array);
		len = write((char*)array.GetData(), array.GetCount());
	}
	else
	{
		len = write(str.GetBuffer(), str.GetLength());
	}
	return len;
}


CString ZoSerialPort::ReadPort(bool ishex)
{
	char buffer[256];
	int len = bytesAvailable();
	read(buffer, len);
	CString data;
	CString strtemp;
	if (ishex == true)
	{
		for (int k = 0; k < len; k++)
		{

			strtemp.Format(_T("%02x"), buffer[k]);//格式化为16进制
			data += strtemp;

		}

	}
	else
	{
		data = CString(buffer);
	}

	return data;
}


UINT __cdecl ZoSerialPort::ThreadReceiveData(LPVOID lParam)
{

	ZoSerialPort* serial = (ZoSerialPort*)lParam;
	int bytes = 0;
	int oldbytes = 0;
	while (serial->isOpen())
	{
		bytes = serial->bytesAvailable();
		if (bytes>0 && bytes!=oldbytes)
		{
			::PostMessage(serial->wndHandle, WM_COMMSG, NULL, NULL);
		}

		oldbytes = bytes;

		Sleep(1);
	}

	serial->threadHandle = NULL;

	return 0;
}

int ZoSerialPort::String2Hex(CString str, CByteArray& senddate)
{
	int hexdate, lowhexdate;
	int hexdatelen = 0;
	int len = str.GetLength();
	senddate.SetSize(len / 2);

	for (int i = 0; i < len;)
	{
		char lstr, hstr = str[i];
		if (hstr == ' ')
		{
			i++;
			continue;
		}
		i++;
		if (i >= len)
			break;
		lstr = str[i];
		hexdate = ConvertHexChar(hstr);
		lowhexdate = ConvertHexChar(lstr);
		if (hexdate == 16 || lowhexdate == 16)
			break;
		else
		{
			hexdate = hexdate * 16 + lowhexdate;
		}
		i++;
		senddate[hexdatelen] = (char)hexdate;
		hexdatelen++;
	}
	senddate.SetSize(hexdatelen);
	return hexdatelen;
}


char ZoSerialPort::ConvertHexChar(char ch)
{
	if (ch >= '0'&& ch <= '9')
	{
		return ch - 0x30;
	}
	else if (ch >= 'A'&& ch <= 'F')
	{
		return ch - 'A' + 10;
	}
	else if (ch >= 'a'&& ch <= 'f')
	{
		return ch - 'a' + 10;
	}
	else
	{
		return -1;
	}
}
