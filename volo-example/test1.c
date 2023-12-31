#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>

// 关闭指定的终端窗口
void closeTerminal(HWND hwnd)
{
    // 发送WM_CLOSE消息给终端窗口
    PostMessage(hwnd, WM_CLOSE, 0, 0);
}
// 打开一个终端并执行指定的命令
void openTerminal(char* command)
{
    // 构建要执行的终端命令
    char terminalCommand[256] = "start cmd.exe /k ";
    strcat(terminalCommand, command);

    // 使用system函数执行终端命令
    system(terminalCommand);
}

// 向指定的终端发送键盘输入
void sendKeysToTerminal(HWND hwnd, const char* keys)
{
    // 设置指定终端为前台窗口
    SetForegroundWindow(hwnd);
    Sleep(1000);

    // 模拟键盘输入
    int i;
    for (i = 0; i < strlen(keys); i++)
    {
        // 发送WM_CHAR消息
        PostMessage(hwnd, WM_CHAR, keys[i], 0);
        Sleep(50);
    }

    // 模拟发送回车键
    PostMessage(hwnd, WM_KEYDOWN, VK_RETURN, 0);
    PostMessage(hwnd, WM_KEYUP, VK_RETURN, 0);
}

int main()
{
	int i; 
    // 定义要在终端中执行的命令
    char command1[256] = "cargo run --bin=client 127.0.0.1:8080";
	char command2[256] = "cargo run --bin=server";

    // 打开第二个终端并执行命令2
    openTerminal(command2);
    Sleep(1000);

    // 查找第二个终端的子窗口
    HWND hwnd = FindWindow(NULL, "C:\\WINDOWS\\system32\\cmd.exe");
    HWND childHwnd = FindWindowEx(hwnd, NULL, "ConsoleWindowClass", NULL);
    if (childHwnd == NULL)
    {
        printf("Failed to find Terminal2 window.\n");
        return 1;
    }
    // 打开第一个终端并执行命令1
    openTerminal(command1);
    Sleep(5000);

    // 查找第一个终端的子窗口
    HWND hwnd2 = FindWindow(NULL, "C:\\WINDOWS\\system32\\cmd.exe");
    HWND childHwnd2 = FindWindowEx(hwnd2, NULL, "ConsoleWindowClass", NULL);
    if (childHwnd2 == NULL)
    {
        printf("Failed to find Terminal1 window.\n");
        return 1;
    }

    // 发送命令到第二个终端
    char commandToSend[256] = "set 127.0.0.1:8083 2 4";
    sendKeysToTerminal(childHwnd2, commandToSend);
    char commandToSend2[256] = "get 127.0.0.1:8083 2";
    sendKeysToTerminal(childHwnd2, commandToSend2);
    Sleep(5000);
    
	closeTerminal(childHwnd);
	Sleep(5000);
	closeTerminal(childHwnd2);
	Sleep(5000);
	
	
	
	// 定义要在终端中执行的命令
    char command3[256] = "cargo run --bin=client 127.0.0.1:8080";
	char command4[256] = "cargo run --bin=server";

    // 打开第二个终端并执行命令2
    openTerminal(command4);
    Sleep(5000);

    // 查找第二个终端的子窗口
    HWND hwnd3 = FindWindow(NULL, "C:\\WINDOWS\\system32\\cmd.exe");
    HWND childHwnd3 = FindWindowEx(hwnd3, NULL, "ConsoleWindowClass", NULL);
    if (childHwnd3 == NULL)
    {
        printf("Failed to find Terminal2 window.\n");
        return 1;
    }
    // 打开第一个终端并执行命令1
    openTerminal(command3);
    Sleep(5000);

    // 查找第一个终端的子窗口
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
