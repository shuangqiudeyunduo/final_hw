#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>

// �ر�ָ�����ն˴���
void closeTerminal(HWND hwnd)
{
    // ����WM_CLOSE��Ϣ���ն˴���
    PostMessage(hwnd, WM_CLOSE, 0, 0);
}
// ��һ���ն˲�ִ��ָ��������
void openTerminal(char* command)
{
    // ����Ҫִ�е��ն�����
    char terminalCommand[256] = "start cmd.exe /k ";
    strcat(terminalCommand, command);

    // ʹ��system����ִ���ն�����
    system(terminalCommand);
}

// ��ָ�����ն˷��ͼ�������
void sendKeysToTerminal(HWND hwnd, const char* keys)
{
    // ����ָ���ն�Ϊǰ̨����
    SetForegroundWindow(hwnd);
    Sleep(1000);

    // ģ���������
    int i;
    for (i = 0; i < strlen(keys); i++)
    {
        // ����WM_CHAR��Ϣ
        PostMessage(hwnd, WM_CHAR, keys[i], 0);
        Sleep(50);
    }

    // ģ�ⷢ�ͻس���
    PostMessage(hwnd, WM_KEYDOWN, VK_RETURN, 0);
    PostMessage(hwnd, WM_KEYUP, VK_RETURN, 0);
}

int main()
{
	int i; 
    // ����Ҫ���ն���ִ�е�����
    char command1[256] = "cargo run --bin=client 127.0.0.1:8080";
	char command2[256] = "cargo run --bin=server";

    // �򿪵ڶ����ն˲�ִ������2
    openTerminal(command2);
    Sleep(1000);

    // ���ҵڶ����ն˵��Ӵ���
    HWND hwnd = FindWindow(NULL, "C:\\WINDOWS\\system32\\cmd.exe");
    HWND childHwnd = FindWindowEx(hwnd, NULL, "ConsoleWindowClass", NULL);
    if (childHwnd == NULL)
    {
        printf("Failed to find Terminal2 window.\n");
        return 1;
    }
    // �򿪵�һ���ն˲�ִ������1
    openTerminal(command1);
    Sleep(5000);

    // ���ҵ�һ���ն˵��Ӵ���
    HWND hwnd2 = FindWindow(NULL, "C:\\WINDOWS\\system32\\cmd.exe");
    HWND childHwnd2 = FindWindowEx(hwnd2, NULL, "ConsoleWindowClass", NULL);
    if (childHwnd2 == NULL)
    {
        printf("Failed to find Terminal1 window.\n");
        return 1;
    }

    // ��������ڶ����ն�
    char commandToSend[256] = "set 127.0.0.1:8083 2 4";
    sendKeysToTerminal(childHwnd2, commandToSend);
    char commandToSend2[256] = "get 127.0.0.1:8083 2";
    sendKeysToTerminal(childHwnd2, commandToSend2);
    Sleep(5000);
    
	closeTerminal(childHwnd);
	Sleep(5000);
	closeTerminal(childHwnd2);
	Sleep(5000);
	
	
	
	// ����Ҫ���ն���ִ�е�����
    char command3[256] = "cargo run --bin=client 127.0.0.1:8080";
	char command4[256] = "cargo run --bin=server";

    // �򿪵ڶ����ն˲�ִ������2
    openTerminal(command4);
    Sleep(5000);

    // ���ҵڶ����ն˵��Ӵ���
    HWND hwnd3 = FindWindow(NULL, "C:\\WINDOWS\\system32\\cmd.exe");
    HWND childHwnd3 = FindWindowEx(hwnd3, NULL, "ConsoleWindowClass", NULL);
    if (childHwnd3 == NULL)
    {
        printf("Failed to find Terminal2 window.\n");
        return 1;
    }
    // �򿪵�һ���ն˲�ִ������1
    openTerminal(command3);
    Sleep(5000);

    // ���ҵ�һ���ն˵��Ӵ���
    HWND hwnd4 = FindWindow(NULL, "C:\\WINDOWS\\system32\\cmd.exe");
    HWND childHwnd4 = FindWindowEx(hwnd4, NULL, "ConsoleWindowClass", NULL);
    if (childHwnd4 == NULL)
    {
        printf("Failed to find Terminal1 window.\n");
        return 1;
    }	
	
    char commandToSend4[256] = "get 127.0.0.1:8083 2";
    sendKeysToTerminal(childHwnd4, commandToSend4);

    return 0;
}