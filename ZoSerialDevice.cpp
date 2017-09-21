#include "stdafx.h"
#include "ZoSerialDevice.h"


ZoSerialDevice::ZoSerialDevice()
{
	handleCom = INVALID_HANDLE_VALUE;
}


ZoSerialDevice::~ZoSerialDevice()
{
	close();
}

bool ZoSerialDevice::open()
{
	if (handleCom != INVALID_HANDLE_VALUE)
		return true;

	handleCom = CreateFile((LPCSTR)portName.c_str(),//串口名
		GENERIC_READ | GENERIC_WRITE,//允许读和写  
		0,//独占方式  
		NULL,//默认安全属性  
		OPEN_EXISTING,//串口必须存在  
		0,//同步方式，重叠方式:FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED  
		NULL
		);
	if (handleCom == INVALID_HANDLE_VALUE)
	{
		//AfxMessageBox(L"打开串口失败");
		return false;
	}

	//PurgeComm(handleCom, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);//清除串口的所有操作。

	if (configPort())
	{
		isopen = true;
		return true;
	}

	CloseHandle(handleCom);

	return false;
}


bool ZoSerialDevice::close()
{
	if (handleCom == INVALID_HANDLE_VALUE)
		return true;

	int ret = CloseHandle(handleCom);
	if (ret == 0)
	{
		return false;
	}

	handleCom = INVALID_HANDLE_VALUE;
	isopen = false;

	return true;
}


bool ZoSerialDevice::isOpen()
{
	return isopen;
}

int ZoSerialDevice::bytesAvailable()
{
	if (isopen == false)
		return 0;

	COMSTAT cs;

	if (!ClearCommError(handleCom, NULL, &cs))
	{
		printf("Terminal failure: Unable to write to file.\n");
	}

	return cs.cbInQue;
}


void ZoSerialDevice::setPortName(string name)
{
	bool wasopen = isopen;

	if (wasopen == true)
		close();

	portName = name;

	if (wasopen == true)
		open();
}

//配置串口  
bool ZoSerialDevice::configPort()
{

	DCB dcb;
	if (!GetCommState(handleCom, &dcb))
		return false;

	GetCommState(handleCom, &dcb);
	dcb.BaudRate = baudRate; //波特率 
	dcb.ByteSize = dataBits; //数据位   
	dcb.Parity = parity; //校验  
	dcb.StopBits = stopBits; //停止位 

	if (!SetCommState(handleCom, &dcb))
		return false;

	if (!SetCommTimeouts(handleCom, &commTimeouts))//设置超时
		return false;

	//清空缓冲区  
	//PurgeComm(handleCom, PURGE_TXCLEAR | PURGE_RXCLEAR);//清空接收和发送缓冲区

	return true;
}


BOOL ZoSerialDevice::setBaudRate(int baudRate)
{
	ZoSerialDevice::baudRate = baudRate;
	if (isOpen() == false)
		return true;

	DCB dcb;
	if (!GetCommState(handleCom, &dcb))
		return false;

	set_baudrate(&dcb, baudRate);

	return SetCommState(handleCom, &dcb);
}


BOOL ZoSerialDevice::setDataBits(DataBits dataBits)
{
	ZoSerialDevice::dataBits = dataBits;
	if (isOpen() == false)
		return true;

	DCB dcb;
	if (!GetCommState(handleCom, &dcb))
		return false;

	set_databits(&dcb, dataBits);


	return SetCommState(handleCom, &dcb);
}


BOOL ZoSerialDevice::setParity(Parity parity)
{
	ZoSerialDevice::parity = parity;
	if (isOpen() == false)
		return true;

	DCB dcb;
	if (!GetCommState(handleCom, &dcb))
		return false;

	set_parity(&dcb, parity);

	return SetCommState(handleCom, &dcb);
}


BOOL ZoSerialDevice::setStopBits(StopBits stopBits)
{
	ZoSerialDevice::stopBits = stopBits;
	if (isOpen() == false)
		return true;

	DCB dcb;
	if (!GetCommState(handleCom, &dcb))
		return false;

	set_stopbits(&dcb, stopBits);

	return SetCommState(handleCom, &dcb);
}


BOOL ZoSerialDevice::setFlowControl(FlowControl flowControl)
{
	ZoSerialDevice::flowControl = flowControl;
	if (isOpen() == false)
		return true;

	DCB dcb;
	if (!GetCommState(handleCom, &dcb))
		return false;

	set_flowcontrol(&dcb, flowControl);

	return SetCommState(handleCom, &dcb);
}

bool ZoSerialDevice::setReadTimout(int millisecond)
{
	commTimeouts.ReadTotalTimeoutMultiplier = millisecond;

	if (isOpen() == false)
		return true;

	if (!SetCommTimeouts(handleCom, &commTimeouts))
	{
		return false;
	}

	return true;
}


void ZoSerialDevice::set_baudrate(DCB* dcb, int baudrate)
{
	dcb->BaudRate = baudrate;
}


void ZoSerialDevice::set_databits(DCB* dcb, DataBits databits)
{
	dcb->ByteSize = databits;
}


void ZoSerialDevice::set_parity(DCB* dcb, Parity parity)
{
	dcb->fParity = TRUE;
	switch (parity) {
	case NoParity:
		dcb->Parity = NOPARITY;
		dcb->fParity = FALSE;
		break;
	case OddParity:
		dcb->Parity = ODDPARITY;
		break;
	case EvenParity:
		dcb->Parity = EVENPARITY;
		break;
	case MarkParity:
		dcb->Parity = MARKPARITY;
		break;
	case SpaceParity:
		dcb->Parity = SPACEPARITY;
		break;
	default:
		dcb->Parity = NOPARITY;
		dcb->fParity = FALSE;
		break;
	}
}


void ZoSerialDevice::set_stopbits(DCB* dcb, StopBits stopbits)
{
	dcb->StopBits = stopbits;
}


void ZoSerialDevice::set_flowcontrol(DCB* dcb, FlowControl flowcontrol)
{
	dcb->fInX = FALSE;
	dcb->fOutX = FALSE;
	dcb->fOutxCtsFlow = FALSE;
	if (dcb->fRtsControl == RTS_CONTROL_HANDSHAKE)
		dcb->fRtsControl = RTS_CONTROL_DISABLE;
	switch (flowcontrol) {
	case NoFlowControl:
		break;
	case SoftwareControl:
		dcb->fInX = TRUE;
		dcb->fOutX = TRUE;
		break;
	case HardwareControl:
		dcb->fOutxCtsFlow = TRUE;
		dcb->fRtsControl = RTS_CONTROL_HANDSHAKE;
		break;
	default:
		break;
	}
}


int ZoSerialDevice::write(char* data, int length)
{
	if (isopen == false)
		return 0;

	DWORD bytes_written = 0;
	BOOL bErrorFlag = FALSE;

	bErrorFlag = WriteFile(
		handleCom,           // open file handle  
		data,      // start of data to write  
		length,  // number of bytes to write  
		&bytes_written, // number of bytes that were written  
		NULL);            // no overlapped structure  

	if (FALSE == bErrorFlag)
	{
		printf("Terminal failure: Unable to write to file.\n");
	}

	return bytes_written;
}


int ZoSerialDevice::read(char* data, int length)
{
	if (isopen == false)
		return 0;
	DWORD bytes_read = 0;
	BOOL bErrorFlag = FALSE;

	bErrorFlag = ReadFile(
		handleCom,
		data,
		length,
		&bytes_read,
		NULL);

	if (bErrorFlag == FALSE)
	{
		printf("Terminal failure: Unable to write to file.\n");
	}
	return bytes_read;
}
