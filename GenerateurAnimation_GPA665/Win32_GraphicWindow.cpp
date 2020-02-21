/* --------------------------------------------------------------------------
 * Collineo
 *
 *
 * Fichier:     Win32_OpenglWindow.c
 * Auteur:      Nicolas Morency 23-01-2002
 *
 * Sommaire:    Fenetre opengl
 *
 *
 * Revision    Par  Commentaires
 * ----------  ---  ----------------------------------------------------------
 * JJ-MM-AAAA  XX	
 * ------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------
 * FICHIERS D'INCLUSIONS ET DEFINITIONS
 * ------------------------------------------------------------------------- */

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>

#include "resource.h"
#include "Win32_AppWindow.h"
#include "Win32_GraphicWindow.h"
#include "media.h"
#include "Laboratoire2.h"

HDC Scene_DC=NULL;

extern ExecuteMode gPlayMode;

bool DrawScene=FALSE;

HWND Win32_SetGDIWindow(HWND Win)
{
	static HWND GDIWin = NULL;

	if(!Win)
		return GDIWin;
	
	GDIWin = Win;

	return Win;
}


static void OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	Media_SetCurrentWindowSize(&cx, &cy, TRUE);
}


static void OnClose(HWND hwnd)
{
	/* Confirmation de sortie ici! */
	FORWARD_WM_CLOSE(hwnd, DefWindowProc) ;
}

void Animate()
{
	DrawScene=TRUE;
	InvalidateRect(Win32_GetGDIWindow(), NULL, 1);
	UpdateWindow(Win32_GetGDIWindow());
}

void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	RECT rcWin;
	HBRUSH brush;

	brush = CreateSolidBrush(RGB(55,55,70));

	Scene_DC = BeginPaint(hWnd, &ps);

	/* Background */
	GetClientRect(hWnd, &rcWin);
	FillRect(Scene_DC, &rcWin,(HBRUSH)brush);

	if(DrawScene)
	{
		Execute(gPlayMode, NULL);
		DrawScene=FALSE;
	}

	EndPaint(hWnd, &ps);

}


LRESULT CALLBACK win32_ProjectWndProc(HWND hwnd, UINT uMsg,WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		HANDLE_MSG(hwnd, WM_SIZE, OnSize);
		HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hwnd, WM_CLOSE,	OnClose);
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);

	}
}

/* -------------------------------------------------------------------------
 *
 * Nom: Win32_CreateOpenglWindow
 *
 * Description: Creation de la fenetre opengl
 *
 * Retour:      handle de la nouvelle fenetre
 *
 * Auteur:      NM, 23-01-2002
 *
 * ------------------------------------------------------------------------- */
HWND Win32_CreateOpenglWindow(HWND hParent)
{
	char class_name[] = "Opengl_Window_Class", window_name[] = "Opengl Window";
	WNDCLASSEX wndclass;
	HWND hOpenglWindow;
	RECT rcApp, rcClient;

	wndclass.cbSize        = sizeof(wndclass);
	wndclass.style         = CS_OWNDC;
	wndclass.lpfnWndProc   = win32_ProjectWndProc;
	wndclass.cbClsExtra    = 0;
	wndclass.cbWndExtra    = sizeof(HANDLE);
	wndclass.hInstance     = GetModuleHandle(NULL);
	wndclass.hIcon         = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_TESTS));
	wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.lpszMenuName  = NULL;
	wndclass.lpszClassName = class_name;
	wndclass.hIconSm       = NULL;
	
	RegisterClassEx(&wndclass);

	GetClientRect(Win32App_GetAppWindow(), &rcApp);
	GetClientRect(Win32App_GetClientMDI(), &rcClient);

	/* On cree la fenetre aux dimensions du Client MDI. */
	if (!(hOpenglWindow= CreateWindowEx(0, class_name, window_name, WS_CHILD,
		0,0,	rcClient.right, rcClient.bottom, hParent, 
		NULL, GetModuleHandle(NULL),NULL)))
		return NULL;

	Win32_SetGDIWindow(hOpenglWindow);

	ShowWindow(hOpenglWindow, 1);
	SetFocus(hOpenglWindow);

	return hOpenglWindow;
}
