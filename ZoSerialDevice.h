#pragma once

#include<string>

using std::string;
using std::wstring;

class ZoSerialDevice
{

public:
	enum BaudRate {
		Baud1200 = 1200,
		Baud2400 = 2400,
		Baud4800 = 4800,
		Baud9600 = 9600,
		Baud19200 = 19200,
		Baud38400 = 38400,
		Baud57600 = 57600,
		Baud115200 = 115200,
		UnknownBaud = -1
	};

	enum DataBits {
		Data5 = 5,
		Data6 = 6,
		Data7 = 7,
		Data8 = 8,
		UnknownDataBits = -1
	};

	enum Parity {
		NoParity = 0,
		OddParity = 1,
		EvenParity = 2,
		MarkParity = 3,
		SpaceParity = 4,
		UnknownParity = -1
	};

	enum StopBits {
		OneStop = 0,
		OneAndHalfStop = 1,
		TwoStop = 2,
		UnknownStopBits = -1
	};

	enum FlowControl {
		NoFlowControl,
		HardwareControl,
		SoftwareControl,
		UnknownFlowControl = -1
	};

public:
	ZoSerialDevice();
	~ZoSerialDevice();
	bool open();
	bool close();
	bool isOpen();
	int bytesAvailable();
	void setPortName(string name);

public:
	HANDLE handleCom;

protected:

	string portName;
	int baudRate;
	DataBits dataBits;
	Parity parity;
	StopBits stopBits;
	FlowControl flowControl;
	COMMTIMEOUTS commTimeouts;

protected:
	bool isopen;

public:
	bool configPort();
	BOOL setBaudRate(int baudRate);
	BOOL setDataBits(DataBits dataBits);
	BOOL setParity(Parity parity);
	BOOL setStopBits(StopBits stopBits);
	BOOL setFlowControl(FlowControl flowControl);

	int write(char* data, int length);
	int read(char* data, int length);

protected:
	void set_baudrate(DCB* dcb, int baudrate);
	void set_databits(DCB* dcb, DataBits databits);
	void set_parity(DCB* dcb, Parity parity);
	void set_stopbits(DCB* dcb, StopBits stopbits);
	void set_flowcontrol(DCB* dcb, FlowControl flowcontrol);



public:
	bool setReadTimout(int millisecond);
};

