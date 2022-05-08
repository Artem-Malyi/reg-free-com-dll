//
// RegFreeCOMDllClient.cpp : Defines the entry point for the console application.
//

#include "string"
#include "atlbase.h"
#include "atlsafe.h"
#include <conio.h>

#import "RegFreeCOMDll.tlb" raw_interfaces_only


HANDLE g_ActivationContext = NULL;
ULONG_PTR g_Cookie = 0;

using namespace RegFreeCOMDll;
using namespace std;

//Forward declarations.
void EnableActivationContext();
void DisableActivationContext();

int main()
{
	CoInitialize(0);

	//EnableActivationContext();

	try
	{
		IRegFreePtr pRegFree(__uuidof(RegFree));
		CComBSTR bstrMessage = "C++ client message";
		pRegFree->RegFreeCOMHello(bstrMessage);

	}
	catch (_com_error _com_err)
	{
		wprintf(L"\n %s", _com_err.ErrorMessage());
		_getch();
	}

	//DisableActivationContext();

	CoUninitialize();

    return 0;
}

void EnableActivationContext()
{
	ACTCTX ctContext;
	memset(&ctContext, 0, sizeof(ctContext));
	WCHAR   modulePath[MAX_PATH] = { 0 };

	//Build manifest file path.
	GetModuleFileName(0, modulePath, sizeof(modulePath));
	wstring wstrModulePath = modulePath;

	size_t pos = wstrModulePath.rfind('\\');
	wstrModulePath = wstrModulePath.substr(0, pos);

	ctContext.cbSize = sizeof(ctContext);
	ctContext.lpSource = L"RegFreeCOMDllClient.exe.manifest";
	ctContext.lpAssemblyDirectory = wstrModulePath.c_str();
	ctContext.dwFlags = ACTCTX_FLAG_ASSEMBLY_DIRECTORY_VALID;

	g_ActivationContext = CreateActCtx(&ctContext);
	ActivateActCtx(g_ActivationContext, &g_Cookie);
}


void DisableActivationContext()
{
	DeactivateActCtx(0, g_Cookie);
	ReleaseActCtx(g_ActivationContext);
}