#include "myhead.h"


int net_GET(string url,char result[]){
    // 初始化WinINet
    HINTERNET hSession = InternetOpen("Mainwin", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (hSession == NULL)
    {
        std::cerr << "InternetOpen failed: " << GetLastError() << std::endl;
        return -1;
    }
    // 连接到指定的服务器
    HINTERNET hConnect = InternetConnect(hSession, domainName.c_str(), INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    if (hConnect == NULL)
    {
        std::cerr << "InternetConnect failed: " << GetLastError() << std::endl;
        InternetCloseHandle(hSession);
        return -1;
    }
    // 创建一个HTTP请求
    HINTERNET hRequest = HttpOpenRequest(hConnect, "GET", url.c_str(), NULL, NULL, NULL, 0, 0);
    if (hRequest == NULL)
    {
        std::cerr << "HttpOpenRequest failed: " << GetLastError() << std::endl;
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hSession);
        return -1;
    }
    // 发送HTTP请求
    BOOL bResult = HttpSendRequest(hRequest, NULL, 0, NULL, 0);
    if (!bResult)
    {
        std::cerr << "HttpSendRequest failed: " << GetLastError() << std::endl;
        InternetCloseHandle(hRequest);
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hSession);
        return -1;
    }
    // 读取HTTP响应
    char buffer[1024];
    int j = 0;
    DWORD dwRead;
    while (InternetReadFile(hRequest, buffer, sizeof(buffer), &dwRead) && dwRead > 0)
    {
        for(int i=0;i<dwRead;i++){
			result[j] = buffer[i];
			j++;
		}
    }
    result[j]='\0';
    
    // 关闭句柄
    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hSession);
    return 0;
}
