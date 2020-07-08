#include "MiniDump.h"
#include "Shlwapi.h"
#pragma comment(lib,"Shlwapi.lib")

static void hprintf(HANDLE LogFile, LPCTSTR format, ...)
{
	TCHAR buffer[2000];	// wvsprintf never prints more than one K.

	va_list arglist;
	va_start(arglist, format);
	wvsprintf(buffer, format, arglist);
	va_end(arglist);

	DWORD NumBytes;
	WriteFile(LogFile, buffer, lstrlen(buffer) * sizeof(TCHAR), &NumBytes, 0);
}

static BOOL GetLogicalAddress(PVOID addr, PTSTR szModule, DWORD len, DWORD& section, DWORD& offset)
{
	MEMORY_BASIC_INFORMATION mbi;

	if (!VirtualQuery(addr, &mbi, sizeof(mbi)))
		return FALSE;

	DWORD hMod = (DWORD)mbi.AllocationBase;

	if (!GetModuleFileName((HMODULE)hMod, szModule, len))
		return FALSE;

	// Point to the DOS header in memory
	PIMAGE_DOS_HEADER pDosHdr = (PIMAGE_DOS_HEADER)hMod;

	// From the DOS header, find the NT (PE) header
	PIMAGE_NT_HEADERS pNtHdr = (PIMAGE_NT_HEADERS)(hMod + pDosHdr->e_lfanew);

	PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNtHdr);

	DWORD rva = (DWORD)addr - hMod; // RVA is offset from module load address

									// Iterate through the section table, looking for the one that encompasses
									// the linear address.
	for (unsigned i = 0;
		i < pNtHdr->FileHeader.NumberOfSections;
		i++, pSection++)
	{
		DWORD sectionStart = pSection->VirtualAddress;
		DWORD sectionEnd = sectionStart
			+ max(pSection->SizeOfRawData, pSection->Misc.VirtualSize);

		// Is the address in this section???
		if ((rva >= sectionStart) && (rva <= sectionEnd))
		{
			// Yes, address is in the section.  Calculate section and offset,
			// and store in the "section" & "offset" params, which were
			// passed by reference.
			section = i + 1;
			offset = rva - sectionStart;
			return TRUE;
		}
	}

	return FALSE;   // Should never get here!
}

MiniDump::MiniDump()
{
	
}


MiniDump::~MiniDump()
{
}

void MiniDump::EnableAutoDump(bool bEnable)
{
	if (bEnable)
	{
		SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
	}
}

LONG MiniDump::ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{
	/*if (IsDebuggerPresent())
	{
	return EXCEPTION_CONTINUE_SEARCH;
	}*/
	
	static int n = 0;
	n++;
	TCHAR szDumpDir[MAX_PATH] = { 0 };
	TCHAR szDumpFile[MAX_PATH] = { 0 };
	TCHAR szMsg[MAX_PATH] = { 0 };
	SYSTEMTIME	stTime = { 0 };
	// 构建dump文件路径;
	GetLocalTime(&stTime);
	GetModuleFileName(NULL, szDumpDir, MAX_PATH);
	*(wcsrchr(szDumpDir,'\\'))=0;
	//::GetCurrentDirectory(MAX_PATH, szDumpDir);
	TSprintf(szDumpFile, _T("%s\\%04d%02d%02d_%02d%02d%02d-%d.dmp"), szDumpDir,
		stTime.wYear, stTime.wMonth, stTime.wDay,
		stTime.wHour, stTime.wMinute, stTime.wSecond,n);
	// 创建dump文件;
	//::MessageBox(0, 0, 0, 0);
	WriteErrorLog(pException);
	CreateDumpFile(szDumpFile, pException);
	
	// 弹出一个错误对话框或者提示上传， 并退出程序;
	TSprintf(szMsg, _T("I'm so sorry, but the program crashed.\r\ndump file : %s"), szDumpFile);
	//FatalAppExit(-1, szMsg);
	return EXCEPTION_EXECUTE_HANDLER;
}

void MiniDump::CreateDumpFile(LPCWSTR strPath, EXCEPTION_POINTERS *pException)
{
	// 创建Dump文件;
	HANDLE hDumpFile = CreateFile(strPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	// Dump信息;
	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
	dumpInfo.ExceptionPointers = pException;
	dumpInfo.ThreadId = GetCurrentThreadId();
	dumpInfo.ClientPointers = FALSE;

	// 写入Dump文件内容;
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, (MINIDUMP_TYPE)(MiniDumpNormal | MiniDumpWithDataSegs), &dumpInfo, NULL, NULL);
	CloseHandle(hDumpFile);
}

void MiniDump::WriteErrorLog(PEXCEPTION_POINTERS pExInfo) {
	PEXCEPTION_RECORD	pException = pExInfo->ExceptionRecord;
	PCONTEXT pContext = pExInfo->ContextRecord;
	MEMORY_BASIC_INFORMATION memInfo;
	TCHAR szDumpDir[MAX_PATH] = {0};
	GetModuleFileName(NULL, szDumpDir, MAX_PATH);
	*(wcsrchr(szDumpDir, '\\')) = 0;
	TCHAR szErrorLog[MAX_PATH * 2] = { 0 };
	lstrcat(szErrorLog, _T("./Error.Log"));
	TSprintf(szErrorLog, _T("%s\\Error.Log"), szDumpDir);

	BOOL bFileExists = PathFileExists(szErrorLog);
	HANDLE hLogFile = CreateFile(szErrorLog, GENERIC_WRITE, 0, 0,
		bFileExists ? OPEN_EXISTING : CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, 0);
	if (hLogFile != INVALID_HANDLE_VALUE)
	{
		TCHAR szTemp[256];

		if (bFileExists)
		{
			// 末尾追加
			SetFilePointer(hLogFile, 0, NULL, FILE_END);
			hprintf(hLogFile, _T("\r\n--------------------\r\n"));
		}

		SYSTEMTIME	stTime = { 0 };
		// 构建dump文件路径;
		GetLocalTime(&stTime);

		wsprintf(szTemp, _T("%02d-%02d-%02d %02d:%02d:%02d\r\n"),
			stTime.wYear, stTime.wMonth, stTime.wDay,
			stTime.wHour, stTime.wMinute, stTime.wSecond);
		hprintf(hLogFile, szTemp);
		hprintf(hLogFile, _T("qtutility log\r\n"));

		//Program Information:
		hprintf(hLogFile, _T("\r\nProgram Information:\r\n"));

		//System Information:
		hprintf(hLogFile, _T("\r\nSystem Information:\r\n"));
		//操作系统信息
		//DirectX信息
		//显示设备信息
		//CPU类型
		//内存
		MEMORYSTATUSEX memoryStatus;
		memset(&memoryStatus, sizeof(MEMORYSTATUS), 0);
		memoryStatus.dwLength = sizeof(MEMORYSTATUS);
		GlobalMemoryStatusEx(&memoryStatus);
		hprintf(hLogFile, _T("Memory: [Available]%I64dM / [Total]%I64dM \r\n"), memoryStatus.ullAvailPhys >> 20, memoryStatus.ullTotalPhys >> 20);
		//硬盘
		TCHAR szBuffer[MAX_PATH];
		ZeroMemory(szBuffer, sizeof(szBuffer));
		GetWindowsDirectory(szBuffer, sizeof(szBuffer));
		TCHAR szHarddisk[MAX_PATH];
		lstrcpy(szHarddisk, szBuffer);
		TCHAR * pszDisk = wcschr(szHarddisk, _T(':'));
		if (pszDisk != NULL)
		{
			szHarddisk[pszDisk - szHarddisk + 1] = 0;
		}
		if (GetProcAddress(GetModuleHandle(_T("kernel32.dll")), "GetDiskFreeSpaceExA"))
		{
			ULARGE_INTEGER ulAvailable;
			ULARGE_INTEGER ulTotal;
			ULARGE_INTEGER ulFree;
			GetDiskFreeSpaceEx(szHarddisk, &ulAvailable, &ulTotal, &ulFree);
			hprintf(hLogFile, _T("System Disk: [Available]%ldM / [Total]%ldM\r\n"), (ulFree.HighPart << (32 - 20)) + (ulFree.LowPart >> 20),
				(ulTotal.HighPart << (32 - 20)) + (ulTotal.LowPart >> 20));
		}
		else
		{
			DWORD dwSectorsPerCluster;     // sectors per cluster
			DWORD dwBytesPerSector;        // bytes per sector
			DWORD dwNumberOfFreeClusters;  // free clusters
			DWORD dwTotalNumberOfClusters;  // total clusters
			GetDiskFreeSpace(szHarddisk, &dwSectorsPerCluster, &dwBytesPerSector, &dwNumberOfFreeClusters, &dwTotalNumberOfClusters);
			hprintf(hLogFile, _T("System Disk: [Available]%ldM / [Total]%ldM\r\n"), ((((dwNumberOfFreeClusters*dwSectorsPerCluster) >> 10)*dwBytesPerSector) >> 10,
				(((dwTotalNumberOfClusters*dwSectorsPerCluster) >> 10)*dwBytesPerSector) >> 10));
		}
		//网络
		//是否设置了代理服务器
		//是否在防火墙内
		//IP地址
		//Error Information:
		hprintf(hLogFile, _T("\r\nError Information:\r\n"));
		TCHAR szCrashModuleName[MAX_PATH] = { _T("Unknown") };
		if (VirtualQuery((void*)pContext->Eip, &memInfo, sizeof(memInfo)) &&
			GetModuleFileName((HINSTANCE)memInfo.AllocationBase, szCrashModuleName, sizeof(szCrashModuleName)) > 0)
		{
		}
		hprintf(hLogFile, _T("Error Module:%s \r\n"), szCrashModuleName);
		hprintf(hLogFile, _T("Code: 0x%08x \r\n"), pException->ExceptionCode);
		hprintf(hLogFile, _T("Flag: 0x%08x \r\n"), pException->ExceptionFlags);
		hprintf(hLogFile, _T("Addr: 0x%08x \r\n"), pException->ExceptionAddress);
		if (EXCEPTION_ACCESS_VIOLATION == pException->ExceptionCode)
		{
			for (int i = 0; i < (int)pException->NumberParameters; i++)
			{
				hprintf(hLogFile, _T("%d: %d(0x%08x)\r\n"), i, pException->ExceptionInformation[i], pException->ExceptionInformation[i]);
			}
			if (pException->NumberParameters >= 2)
			{
				TCHAR szReadWrite[256] = { 0 };
				if (pException->ExceptionInformation[0])
				{
					lstrcpy(szReadWrite, _T("Write to"));
				}
				else
				{
					lstrcpy(szReadWrite, _T("Read from"));
				}
				hprintf(hLogFile, _T("%s location %08x caused an access violation.\r\n"), szReadWrite, pException->ExceptionInformation[1]);
			}
		}
		hprintf(hLogFile, _T("Caused error at %04x:%08x.\r\n"), pContext->SegCs, pContext->Eip);

		hprintf(hLogFile, _T("\r\nRegisters:\r\n"));
		hprintf(hLogFile, _T("EAX=%08x CS=%04x EIP=%08x EFLGS=%08x\r\n"),
			pContext->Eax, pContext->SegCs, pContext->Eip, pContext->EFlags);
		hprintf(hLogFile, _T("EBX=%08x SS=%04x ESP=%08x EBP=%08x\r\n"),
			pContext->Ebx, pContext->SegSs, pContext->Esp, pContext->Ebp);
		hprintf(hLogFile, _T("ECX=%08x DS=%04x ESI=%08x FS=%04x\r\n"),
			pContext->Ecx, pContext->SegDs, pContext->Esi, pContext->SegFs);
		hprintf(hLogFile, _T("EDX=%08x ES=%04x EDI=%08x GS=%04x\r\n"),
			pContext->Edx, pContext->SegEs, pContext->Edi, pContext->SegGs);

		int NumCodeBytes = 16;	// Number of code bytes to record.

		hprintf(hLogFile, _T("Bytes at CS:EIP:\r\n"));
		unsigned char *code = (unsigned char*)pContext->Eip;
		for (int codebyte = 0; codebyte < NumCodeBytes; codebyte++)
		{
			__try
			{
				hprintf(hLogFile, _T("%02x "), code[codebyte]);
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				hprintf(hLogFile, _T("?? "));
			}
		}
		hprintf(hLogFile, _T("\r\n"));

		hprintf(hLogFile, _T("Call Stack:\r\n"));
		DWORD pc = pContext->Eip;
		PDWORD pFrame, pPrevFrame;

		pFrame = (PDWORD)pContext->Ebp;
		do
		{
			TCHAR szModule[MAX_PATH] = _T("");
			DWORD section = 0, offset = 0;

			__try
			{
				if (GetLogicalAddress((PVOID)pc, szModule, sizeof(szModule), section, offset) == FALSE)
				{
					break;
				}
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				break;
			}
			hprintf(hLogFile, _T("%08X %04X:%08X %s\r\n"), pc, section, offset, szModule);

			pc = pFrame[1];

			pPrevFrame = pFrame;

			pFrame = (PDWORD)pFrame[0]; // precede to next higher frame on stack

			if ((DWORD)pFrame & 3)    // Frame pointer must be aligned on a
				break;                  // DWORD boundary.  Bail if not so.

			if (pFrame <= pPrevFrame)
				break;

			// Can two DWORDs be read from the supposed frame address?          
			if (IsBadWritePtr(pFrame, sizeof(PVOID) * 2))
				break;

		} while (1);
		hprintf(hLogFile, _T("\r\n"));

		hprintf(hLogFile, _T("\r\nqtutility error log end......\r\n"));

		CloseHandle(hLogFile);
	}
	else
	{
		
	}
}