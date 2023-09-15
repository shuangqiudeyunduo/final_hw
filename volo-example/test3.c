#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>

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
    // ����Ҫ���ն���ִ�е�����
    char command1[256] = "cargo run --bin=client 127.0.0.1:8084";
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
    Sleep(1000);

    // ���ҵ�һ���ն˵��Ӵ���
    HWND hwnd2 = FindWindow(NULL, "C:\\WINDOWS\\system32\\cmd.exe");
    HWND childHwnd2 = FindWindowEx(hwnd2, NULL, "ConsoleWindowClass", NULL);
    if (childHwnd2 == NULL)
    {
        printf("Failed to find Terminal1 window.\n");
        return 1;
    }

    // ��������ڶ����ն�
    char commandToSend[256] = "set 127.0.0.1:8083 4 8";
    sendKeysToTerminal(childHwnd2, commandToSend);
    
    char commandToSend1[256] = "get 127.0.0.1:8081 2";
    sendKeysToTerminal(childHwnd2, commandToSend1);
    
    char commandToSend5[256] = "shutdown";
    sendKeysToTerminal(childHwnd2, commandToSend5);
    
    char commandToSend6[256] = "cargo run --bin=client 127.0.0.1:8080";
    sendKeysToTerminal(childHwnd2, commandToSend6);
    
    
    char commandToSend2[256] = "set 6 7";
    sendKeysToTerminal(childHwnd2, commandToSend2);
    
    char commandToSend7[256] = "get 6";
    sendKeysToTerminal(childHwnd2, commandToSend7);
    
    char commandToSend8[256] = "set 7 8";
    sendKeysToTerminal(childHwnd2, commandToSend8);
	
     char commandToSend9[256] = "get 7";
    sendKeysToTerminal(childHwnd2, commandToSend9);
	
	
	
    return 0;
}
