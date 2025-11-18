#include <Windows.h>

BOOL APIENTRY DllMain(HANDLE hInstance, DWORD dwReason, LPVOID v) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
