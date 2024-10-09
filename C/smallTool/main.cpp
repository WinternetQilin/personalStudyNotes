#include"resource/cJSON.h"
#include <graphics.h>
#include<stdio.h>
#include<windows.h>
#include<winhttp.h>
#include<malloc.h>
#include<wchar.h>
#include<string.h>
#include<stdlib.h>
#pragma comment(lib, "winhttp.lib")
#define URL_LENGTH 1024     //Url地址
#define DATA_LENGTH 1024	//接收数据的长度
#define WINDOW_WIDTH 220	//窗口宽度
#define WINDOW_HEIGH 190	//窗口高度

wchar_t* toUnicode(char* valuestring)
{
	wchar_t* wstr;
	int len = MultiByteToWideChar(CP_UTF8, 0, valuestring, -1, NULL, 0);
	wstr = (wchar_t*)malloc(len * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, valuestring, -1, wstr, len);
	return wstr;
}

int btn_x = 0, btn_y = 120, btn_width = 100, btn_height = 30;
void initWindow(int left, int top)
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGH);
	setbkcolor(WHITE);
	cleardevice();

	setfillcolor(RGB(238, 241, 247));
	setfillstyle(BS_SOLID);

	solidrectangle(btn_x, btn_y, btn_x + btn_width, btn_y + btn_height);//100x30

	settextcolor(BLACK);
	textheight(6);
	setbkmode(TRANSPARENT);
	outtextxy(btn_x + 3, btn_y + 6, _T("点击更改城市"));

	SetWindowPos(GetHWnd(), HWND_TOP, left, top, WINDOW_WIDTH, WINDOW_HEIGH, SWP_NOZORDER);

}

void getWeather(const wchar_t city[]) {

	HINTERNET hSession = NULL, hConnect = NULL, hRequest = NULL;
	DWORD dwSize = 0;
	DWORD dwDownloaded = 0;
	//LPSTR pszOutBuffer;
	char* pszOutBuffer;
	cJSON* json_root = NULL;

	wchar_t requestUrl[URL_LENGTH] = { 0 }; //请求的url
	wchar_t data[DATA_LENGTH] = { 0 };  //接收的数据
	wchar_t key[] = L"839d868f4f65b8029f503df1d36cd70c"; //key值
	wchar_t output[] = L"json";  //请求数据的方式
	wchar_t extensions[] = L"base"; //请求的气象类型
	//拼接请求的URL地址
	wcscpy(requestUrl, L"/v3/weather/weatherInfo?key=");
	wcscat(requestUrl, key);
	wcscat(requestUrl, L"&city=");
	wcscat(requestUrl, city);
	wcscat(requestUrl, L"&output=");
	wcscat(requestUrl, output);
	wcscat(requestUrl, L"&extensions=");
	wcscat(requestUrl, extensions);


	//1.使用WinHttpOpen来获取一个会话句柄
	BOOL bResults = FALSE;
	hSession = WinHttpOpen(L"WinHTTP getWeather/1.0",
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS, 0);

	if (hSession) {
		//2.指定一个HTTP服务器
		hConnect = WinHttpConnect(hSession, L"restapi.amap.com", INTERNET_DEFAULT_HTTP_PORT, 0);

		if (hConnect) {
			//3.创建一个请求句柄
			hRequest = WinHttpOpenRequest(hConnect, L"GET", requestUrl, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);

			if (hRequest) {
				//4.发送一个请求
				bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);

				if (bResults)
				{
					bResults = WinHttpReceiveResponse(hRequest, NULL);
					if (bResults)
					{

						//检查有用的数据(data)
						dwSize = 0;
						if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
							printf("Error %u in WinHttpQueryDataAvailable.\n", GetLastError());
						// 创建接收数据的字符数组，大小dwSize+1
						pszOutBuffer = (char*)calloc(dwSize + 1, sizeof(char));
						if (!pszOutBuffer)
						{
							printf("pszOutBuffer calloc failed\n");
							dwSize = 0;
						}
						else
						{
							//读取数据(data)
							ZeroMemory(pszOutBuffer, dwSize + 1);
							if (!WinHttpReadData(hRequest, pszOutBuffer, dwSize, &dwDownloaded))printf("Error %u in WinHttpReadData.\n", GetLastError());
							else
							{
								//解析json数据
								json_root = cJSON_Parse(pszOutBuffer);
								if (json_root->child == NULL)
								{
									const char* error_ptr = cJSON_GetErrorPtr();
									if (error_ptr != NULL) {
										fprintf(stderr, "Error before: %s\n", error_ptr);
										return;
									}
								}
								else
								{
									cJSON* infocode = cJSON_GetObjectItem(json_root, "infocode");
									if (atoi(infocode->valuestring) != 10000)
									{
										printf("天气查询失败：%d\n", atoi(infocode->valuestring));
										outtextxy(0, 0, _T("天气查询失败"));
										outtextxy(0, 30, _T("（可能是输入城市有误）"));
										return;
									}

									cJSON* lives = cJSON_GetObjectItem(json_root, "lives");
									if (lives->child == NULL)
									{
										outtextxy(0, 0, _T("天气查询失败"));
										outtextxy(0, 30, _T("（可能是输入城市有误）"));
										return;
									}
									cJSON* live = cJSON_GetArrayItem(lives, 0);
									if (live->child == NULL)
									{
										outtextxy(0, 0, _T("天气查询失败"));
										outtextxy(0, 30, _T("（可能是输入城市有误）"));
										return;
									}
									//城市
									wchar_t* uni_city = toUnicode(cJSON_GetObjectItem(live, "city")->valuestring);
									//天气
									wchar_t* uni_weather = toUnicode(cJSON_GetObjectItem(live, "weather")->valuestring);
									//温度
									wchar_t* uni_temperature = toUnicode(cJSON_GetObjectItem(live, "temperature_float")->valuestring);
									wcscat(uni_temperature, L"℃");
									//风向
									wchar_t* uni_winddirection = toUnicode(cJSON_GetObjectItem(live, "winddirection")->valuestring);
									wcscat(uni_winddirection, L"风");
									//风力
									wchar_t* uni_windpower = toUnicode(cJSON_GetObjectItem(live, "windpower")->valuestring);
									wcscat(uni_windpower, L"级");
									//湿度
									wchar_t* uni_humidity = toUnicode(cJSON_GetObjectItem(live, "humidity")->valuestring);
									wcscat(uni_humidity, L"%");

									//输出到界面
									settextcolor(BLACK);
									textheight(12);
									//左半边
									outtextxy(0, 0, _T("城市："));
									outtextxy(40, 0, uni_city);
									outtextxy(0, 30, _T("天气："));
									outtextxy(40, 30, uni_weather);
									outtextxy(0, 60, _T("温度："));
									outtextxy(40, 60, uni_temperature);
									//右半边
									int right_x = 100;
									outtextxy(right_x, 0, _T("风向："));
									outtextxy(right_x + 50, 0, uni_winddirection);
									outtextxy(right_x, 30, _T("风力："));
									outtextxy(right_x + 50, 30, uni_windpower);
									outtextxy(right_x, 60, _T("湿度："));
									outtextxy(right_x + 50, 60, uni_humidity);

								}
							}
						}
					}
					else
					{
						printf("no message\n");
					}
				}
			}
			else
			{
				printf("hRequest error\n");
			}
		}
		else
		{
			printf("hConnect error:%u\n", GetLastError());
		}
	}
	else
	{
		printf("hSession error\n");
	}
}

int main()
{
	initWindow((GetSystemMetrics(SM_CXSCREEN) - WINDOW_WIDTH) / 2, (GetSystemMetrics(SM_CYSCREEN) - WINDOW_HEIGH) / 2);
	getWeather(L"桂林");
	while (1)
	{
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= btn_x && msg.x <= btn_x + btn_width && msg.y >= btn_y && msg.y <= btn_y + btn_height)
			{
				wchar_t inputStr[1024];
				InputBox(inputStr, 1024, L"请输入城市");
				RECT rect;
				GetWindowRect(GetHWnd(), &rect);
				closegraph();
				initWindow(rect.left, rect.top);
				getWeather(inputStr);
			}
		}
	}
	return 0;
}