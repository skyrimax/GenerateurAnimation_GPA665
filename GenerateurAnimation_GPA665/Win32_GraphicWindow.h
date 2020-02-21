#ifndef	_WIN32_OPENGLWINDOW_H_
#define	_WIN32_OPENGLWINDOW_H_


/* -------------------------------------------------------------------------
 * FICHIERS D'INCLUSIONS
 * ------------------------------------------------------------------------- */
#include<commctrl.h>


#define Win32_GetGDIWindow()	(Win32_SetGDIWindow(NULL))

extern HWND Win32_SetGDIWindow(HWND);
void Animate();

HWND Win32_CreateOpenglWindow(HWND);


#endif /* _WIN32_OPENGLWINDOW_H_ */
