#ifndef WinHttpHelper_hpp
#define WinHttpHelper_hpp
#include "http_define.h"
#include "winhttp/utility.h"
#include "winhttp/http_tunnel.h"
#include "winhttp/MD5.h"
namespace WinHttpHelper
{
	unsigned int __stdcall HttpPost(void * para)
	{
		if ( !para )
		{
			OutputDebugStringA("param is null");
		}
		STStatisticData* pData = (STStatisticData*)para;

		common_cz::HttpTunnel http_tunnel;
		char body[2048];
		sprintf_s(body,
			"{\"name\":\"%s\",\"userid\":\"%lld\",\"mac\":\"%s\",\"params\":%s}",
			pData->strName,
			pData->uiUserId,
			pData->strMac,
			pData->strParam
			);

		/////////////////////////
		char strKey[] = "KKKKBBBB!!!AAA";
		char strBody[4096] = {0}; 
		strcat(strBody,body);
		strcat(body,strKey);

		///º∆À„MD5
		CHAR szMd5[128] = {0};
		Cmd5::MDStringA(szMd5, body);
		//////////////////////////

		std::string strUrl = common_cz::UnicodeToAscii(MACRO_SERVER_EVENTLOG_SERVER) + std::string(&szMd5[0]);
		std::wstring strReturnValue,strProxyInfo;
		std::string strSOAPAction;

		std::string request_body = strBody;
		std::string response;
		http_tunnel.SetMethod(SERVICE_METHOD_POST);
		int response_code = 0;
#if 1
		if (http_tunnel.Request("http://eventapi.7fgame.com:1080/eventlog?appid=2&sign=7d33ddd4cd9e664503fb333a93c35857", "{\"name\":\"item.add\",\"userid\":124896424,\"params\":{\"ItemTypeId\":50001,\"Amount\":100,\"PackageId\":31}}", &response, SERVICE_REQUEST_TIMEOUT, &response_code) &&
			response_code == SERVICE_SUCCESS_RESP_CODE) {

		} 
		else 
		{

		}
#else
		if (http_tunnel.Request(strUrl, request_body, &response, SERVICE_REQUEST_TIMEOUT, &response_code) &&
			response_code == SERVICE_SUCCESS_RESP_CODE) {

		} else {

		}
#endif
		

		if (!pData)
		{
			delete pData;
			pData = NULL;
		}
		return 1;
	}

	void WinHttpPost(std::string &url,std::string & body)
	{

	}
};

#endif