
// SerialProtLib.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSerialProtLibApp: 
// �йش����ʵ�֣������ SerialProtLib.cpp
//

class CSerialProtLibApp : public CWinApp
{
public:
	CSerialProtLibApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSerialProtLibApp theApp;