#ifndef	_WIN32_APPWINDOW_H_
#define	_WIN32_APPWINDOW_H_


/* -------------------------------------------------------------------------
 * FICHIERS D'INCLUSIONS
 * ------------------------------------------------------------------------- */
#include<commctrl.h>

#define Win32App_GetClientMDI()		(Win32App_SetClientMDI(NULL))
#define Win32App_GetAppWindow()		(Win32App_SetAppWindow(NULL))

void Win32_Resize(HWND client, UINT x, UINT y);
HWND Win32App_SetClientMDI(HWND hwnd);
HWND Win32App_SetAppWindow(HWND hwnd);
HWND Win32_CreateAppWindow(HWND parent);
void Win32_StatusbarSetText(const char *text);

#endif /* _WIN32_APPWINDOW_H_ */
