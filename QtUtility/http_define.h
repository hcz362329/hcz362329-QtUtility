#ifndef http_define_h
#define http_define_h
#include <Windows.h>
#pragma pack(push,1)

#ifndef MACRO_SERVER_EVENTLOG_SERVER
#define MACRO_SERVER_EVENTLOG_SERVER (L"http://eventapi.7fgame.com:1080/eventlog?appid=2&sign=")
#endif


struct STStatisticData
{
	char strName[128];
	UINT64 uiUserId;
	char strMac[128];
	char strParam[4096];

	STStatisticData()
	{
		memset(strName,0,_countof(strName));
		uiUserId	= 0;
		memset(strMac,0,_countof(strMac));
		memset(strParam,0,_countof(strParam));
	}
};
#pragma pack(pop)

#endif