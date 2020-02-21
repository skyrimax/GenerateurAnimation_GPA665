/* -------------------------------------------------------------------------
 * FICHIERS D'INCLUSIONS ET DEFINITIONS
 * ------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>

#include "resource.h"
#include "Win32_AppWindow.h"
#include "Win32_GraphicWindow.h"

#include "Laboratoire2.h"

#define MDI_CLIENT_CHILD_ID	10
#define FIRST_MDI_CHILD_ID	100
#define WIN32_COMMCTRL_STATUSBAR_ID		3

#define MAIN_TOOLBAR_NB_BUTTON	3
#define MAIN_TOOLBAR_DIMENSIONS	16
#define MAIN_TOOLBAR_SEPARATEURS	0

static HWND hToolbar, hStatus;
static HACCEL _hProjectAccel;

ExecuteMode gPlayMode;

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

TBBUTTON _main_toolbar_button[] = 
{
	0, 0, 0, TBSTYLE_SEP, 0, 0, 0, 0,
	0, IDM_FICHIER_OUVRIR, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
	1, IDM_PLAY_FORWARD, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
	2, IDM_PLAY_BACKWARD, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
};


/* -------------------------------------------------------------------------
 *
 * Nom:         Win32_DispatchAccelerator
 *
 * Description: Redirige les accelerateurs aux bonnes fenetres
 *
 * Parametres:  msg -- le message de la queue des evenements
 *
 * Retour:      1: Accelerateur traite, 0 pas d'accelerateurs
 *
 * Auteur:      NM, 02-03-1999
 *
 * ------------------------------------------------------------------------- */
static int Win32_DispatchAccelerator(MSG *msg)
{
	return TranslateAccelerator(Win32App_GetAppWindow(), _hProjectAccel, msg);
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	HWND hAppWindow;
	
	InitCommonControls();

	if (!(hAppWindow = Win32_CreateAppWindow(HWND_DESKTOP)))
		return 0;
	
	/* --- Chargement des accelerateurs --- */
	_hProjectAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR));

	while (GetMessage(&msg, (HWND)NULL, 0, 0)) 
    { 
		if (!(TranslateMDISysAccel( Win32App_GetClientMDI(), &msg)))
		{
			//if((!IsDialogMessage(hCourbes, &msg)))
			{
				if (!Win32_DispatchAccelerator(&msg))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
    } 
    return msg.wParam; 
}


static HWND Win32_CreateStatusbar(HWND parent, char *text, int flag)
{
	HWND statusbar = CreateStatusWindow(WS_CHILD | WS_VISIBLE | CCS_BOTTOM |
		(flag ? SBARS_SIZEGRIP : 0),
		text ? text : "Ready",
		parent, WIN32_COMMCTRL_STATUSBAR_ID);

	if (!flag)
		SendMessage(statusbar, SB_SETTEXT, (0 | SBT_NOBORDERS),
			(LPARAM)(text ? text : "Ready"));

	return statusbar;
}

void Win32_StatusbarSetText(const char *text)
{
	SendMessage(hStatus, SB_SETTEXT, 0,
		(LPARAM)(text ? text : "Ready"));
	
	SendMessage(hStatus, WM_PAINT, 0, 0);
}	


void BrowseOpen(HWND hwnd, const char *sTitre, int mode)
{
	OPENFILENAME file_info;
	char sFilename[256]="";
	/* --- Initialisation du comportement de la boite de dialogue --- */
	file_info.lStructSize       = sizeof(OPENFILENAME);
	file_info.hwndOwner         = hwnd;
	file_info.hInstance         = NULL;
	file_info.lpstrFilter		= "*.*\0*.*";
	file_info.lpstrCustomFilter = NULL; 
	file_info.nMaxCustFilter    = 0;
	file_info.nFilterIndex      = 0;
	file_info.lpstrFile         = sFilename;
	file_info.nMaxFile          = 256;
	file_info.lpstrFileTitle    = NULL;
	file_info.nMaxFileTitle     = 256;
	file_info.lpstrInitialDir   = NULL;
	file_info.lpstrTitle        = sTitre;
	file_info.Flags             = OFN_HIDEREADONLY | OFN_EXPLORER;
	file_info.nFileOffset       = 0;
	file_info.nFileExtension    = 0;
	file_info.lpstrDefExt       = NULL;
	file_info.lCustData         = 0;
	file_info.lpfnHook          = NULL;
	file_info.lpTemplateName    = NULL;
	GetOpenFileName(&file_info);

	if(strlen(sFilename))
		Execute(emOpenScript, sFilename);
}

HWND Win32App_SetClientMDI(HWND hwnd)
{
	static HWND hClientMDI=NULL;

	if (hwnd)
		hClientMDI=hwnd;

	return hClientMDI;
}

HWND Win32App_SetAppWindow(HWND hwnd)
{
	static HWND hAppWindow=NULL;

	if (hwnd)
		hAppWindow=hwnd;

	return hAppWindow;
}

static HWND Win32_CreateToolbar(HWND parent, int bmp_id, int nb_button_bmp,
								 int nb_button, TBBUTTON *button_list)
{
	return CreateToolbarEx(parent, WS_CHILD | WS_VISIBLE | CCS_TOP
		, 2, nb_button_bmp,
		GetModuleHandle(NULL), bmp_id, button_list, nb_button,
		MAIN_TOOLBAR_DIMENSIONS, MAIN_TOOLBAR_DIMENSIONS, 
		MAIN_TOOLBAR_DIMENSIONS * nb_button_bmp,	
		MAIN_TOOLBAR_DIMENSIONS, sizeof(TBBUTTON));
}



void Win32_Resize(HWND client, UINT x, UINT y)
{
	RECT rect;
	int toolbar_height, statusbar_height;

	GetWindowRect(hToolbar, &rect);
	toolbar_height = rect.bottom - rect.top;

	GetWindowRect(hStatus, &rect);
	statusbar_height = rect.bottom - rect.top;
	MoveWindow(hStatus, 0, y - statusbar_height, x,
		statusbar_height, TRUE);
	
	/* --- On resize la fenetre client --- */
	MoveWindow(client, 0, toolbar_height, x,
		y-(statusbar_height+toolbar_height), 1); 
	SendMessage(hToolbar, TB_AUTOSIZE, 0, 0);
}

/* -------------------------------------------------------------------------
 * DEBUT DES MESSAGE HANDLERS WIN32
 * ------------------------------------------------------------------------- */
static BOOL Cls_OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	CLIENTCREATESTRUCT mdi_client;

	mdi_client.hWindowMenu = NULL;
	mdi_client.idFirstChild = FIRST_MDI_CHILD_ID;

	if (!Win32App_SetClientMDI(CreateWindowEx(WS_EX_CLIENTEDGE, "MDICLIENT",
		"IMInspect - MDIClient", WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS , 0, 0, 0, 0,
		hwnd, (HMENU)MDI_CLIENT_CHILD_ID, GetModuleHandle(NULL), &mdi_client)))
		return 0;

	if (!Win32_CreateOpenglWindow(hwnd))
		return 0;

	hStatus = Win32_CreateStatusbar(hwnd, NULL, TRUE);

	hToolbar = Win32_CreateToolbar(hwnd, IDB_TOOLBAR,
		MAIN_TOOLBAR_NB_BUTTON, sizeof(_main_toolbar_button) /
		sizeof(TBBUTTON), _main_toolbar_button);

	return TRUE;
}

static void Cls_OnClose(HWND hwnd)
{
//	PostMessage(Scene.GetOpenglWindow(), WM_CLOSE, 0, 0);
	Execute(emFreeScript, NULL);
	PostQuitMessage(0);
}

static void Cls_OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}

static void Cls_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	Win32_Resize(Win32_GetGDIWindow(), cx, cy);
}

static void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDM_ABOUT:
		DialogBox(GetModuleHandle(NULL), (LPCTSTR)IDD_ABOUTBOX, hwnd, (DLGPROC)About);
		break;
	case IDM_FICHIER_QUITTER:
		SendMessage(hwnd, WM_CLOSE,0,0);
		break;
	case IDM_FICHIER_OUVRIR:
		BrowseOpen(hwnd, "Ouverture d'image", 0);
		break;
	case IDM_PLAY_FORWARD:
		gPlayMode = emPlayForward;
		Animate();
		break;
	case IDM_PLAY_BACKWARD:
		gPlayMode = emPlayBackward;
		Animate();
		break;
	default:
		DefFrameProc(hwnd, Win32App_GetClientMDI(), WM_COMMAND,
			MAKEWPARAM(id, codeNotify), (LPARAM)hwndCtl);
	}
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}



LRESULT CALLBACK Win32_AppWindowWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		HANDLE_MSG(hwnd, WM_CREATE,	Cls_OnCreate);
		HANDLE_MSG(hwnd, WM_DESTROY,Cls_OnDestroy);
		HANDLE_MSG(hwnd, WM_CLOSE,	Cls_OnClose);
		HANDLE_MSG(hwnd, WM_COMMAND,Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_SIZE,	Cls_OnSize);
	default:
		return DefFrameProc(hwnd, Win32App_GetClientMDI(), uMsg, wParam, lParam);
	}
}

/* -------------------------------------------------------------------------
 *
 * Nom:         win32_CreateAppWindow
 *
 * Description: Creation de la fenetre principale
 *
 * Parametres:  parent -- la fenetre parent
 *
 * Retour:      la fenetre principale
 *
 * ------------------------------------------------------------------------- */
HWND Win32_CreateAppWindow(HWND parent)
{
	char class_name[] = "application_window_class";
	WNDCLASSEX wndclass;
	
	wndclass.cbSize        = sizeof(wndclass);
	wndclass.style         = 0;
	wndclass.lpfnWndProc   = Win32_AppWindowWndProc;
	wndclass.cbClsExtra    = 0;
	wndclass.cbWndExtra    = 0;
	wndclass.hInstance     = GetModuleHandle(NULL);
	wndclass.hIcon         = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);
	wndclass.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU);
	wndclass.lpszClassName = class_name;
	wndclass.hIconSm       = NULL;

	
	if (!RegisterClassEx(&wndclass))
		return NULL;

	if (!Win32App_SetAppWindow(CreateWindowEx(0, class_name, "Laboratoire 2, plateforme d'animation",
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE ,
		10,10,500,400, parent, NULL,	
		GetModuleHandle(NULL), NULL)))
		return NULL;

	return Win32App_GetAppWindow();
}

