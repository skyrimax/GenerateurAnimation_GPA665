#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <math.h>

#include "media.h"
#include "Scene_DC.h"


static COLORREF SetBrushColor(int R, int G, int B);
static COLORREF SetPenColor(int R, int G, int B);
static void SetPen(bool Set);
static COLORREF GetBrushColor();
static COLORREF GetPenColor();


/*******************************************************
* Nom : Media_Delay
*
* Description : 
*
* -Parametres-
* int Millisec: Temps de délai em millisec
*
* Retour : true si ok, false sinon
*******************************************************/
bool Media_Delay(Parameters *Param)
{
	if(!Param)
		return false;

	WaitMessage();
	Sleep(Param->Val[0]);

	return true;
}


/*******************************************************
* Nom : Media_PlaySound
*
* Description : 
*
* -Parametres-
* const char *sFichier: fichier .wav à jouer
*
* Retour : true si ok, false sinon
*******************************************************/
bool Media_PlaySound(Parameters *Param)
{
	if(!Param)
		return false; 
	return PlaySound(Param->String,NULL , SND_FILENAME | SND_ASYNC)?true:false;
}



/*******************************************************
* Nom : Media_SetPenColor
*
* Description : Definie la couleur du trait
*
* -Parametres-
* Parameters *Param: 
*
* Retour :  true si ok, false sinon
*******************************************************/
bool Media_SetPenColor(Parameters *Param)
{
	if(!Param)
		return false;

	SetPenColor(Param->Val[0], Param->Val[1], Param->Val[2]);
	return true;
}


/*******************************************************
* Nom : Media_SetBrushColor
*
* Description : 
*
* -Parametres-
* Parameters *Param: 
*
* Retour :  true si ok, false sinon
*******************************************************/
bool Media_SetBrushColor(Parameters *Param)
{
	if(!Param)
		return false;

	SetBrushColor(Param->Val[0], Param->Val[1], Param->Val[2]);
	return true;
}

/*******************************************************
* Nom : Media_DrawArc
*
* Description : 
*
* -Parametres-
* int xOrg: Origine
* int yOrg: 
* int xDst: Destination
* int yDst: 
* int xStart: Debut
* int yStart: 
* int xEnd: Fin
* int yEnd: 
*
* Retour : true si ok, false sinon
*******************************************************/
bool Media_DrawArc(Parameters *Param)
{
	if(!Param)
		return false;

	SetPen(TRUE);

	Arc(Scene_DC, Param->Val[0], Param->Val[1], Param->Val[2], Param->Val[3], 
		Param->Val[4], Param->Val[5], Param->Val[6], Param->Val[7]);

	SetPen(FALSE);

	return true;
}


/*******************************************************
* Nom : Media_DrawLine
*
* Description : 
*
* -Parametres-
* int xOrg: Origine
* int yOrg: 
* int xDst: Destination
* int yDst: 
*
* Retour : true si ok, false sinon
*******************************************************/
bool Media_DrawLine(Parameters *Param)
{
	if(!Param)
		return false;

	SetPen(TRUE);
				
	MoveToEx(Scene_DC,Param->Val[0],Param->Val[1],NULL);
	LineTo(Scene_DC,Param->Val[2],Param->Val[3]);

	SetPen(FALSE);

	return true;
}


/*******************************************************
* Nom : Media_DrawPixel
*
* Description : 
*
* -Parametres-
* int x: 
* int y: 
*
* Retour : true si ok, false sinon
*******************************************************/
bool Media_DrawPixel(Parameters *Param)
{
	if(!Param)
		return false;

	Param->Val[2] = Param->Val[0]+1;
	Param->Val[3] = Param->Val[1]+1;

	Media_DrawRect(Param);

	return true;
}


/*******************************************************
* Nom : Media_GetCurrentWindowSize
*
* Description : 
*
* -Parametres-
* int *cx: largeur de fenetre
* int *cy: hauteur de fenetre
*
* Retour : true si ok, false sinon
*******************************************************/
bool Media_GetCurrentWindowSize(int *cx, int *cy)
{
	return Media_SetCurrentWindowSize(cx,cy,FALSE);
}

bool Media_SetCurrentWindowSize(int *cx, int *cy, bool set)
{
	static int X=0, Y=0;

	if(!cx || !cy)
		return FALSE;

	if(set)
	{
		X=*cx;
		Y=*cy;
	}
	else
	{
		*cx=X;
		*cy=Y;
	}
	return TRUE;
}

/*******************************************************
* Nom : Media_Clear
*
* Description : 
*
* -Parametres-
* int R: Teinte de rouge (0 a 255)
* int G: Teinte de vert
* int B: Teinte de bleu
*
* Retour : true si ok, false sinon
*******************************************************/
bool Media_Clear(Parameters *Param)
{
	if(!Param)
		return false;

	int cx, cy, R, G, B;
	COLORREF LastColor;
	RECT r;
	HBRUSH brush;

	R = Param->Val[0];
	G = Param->Val[1];
	B = Param->Val[2];

	LastColor = GetBrushColor();

	Media_GetCurrentWindowSize(&cx,&cy);

	SetPen(TRUE);

	r.bottom=cy;
	r.left=0;
	r.right=cx;
	r.top=0;

	brush = CreateSolidBrush(SetBrushColor(R, G, B));
	
	FillRect(Scene_DC, &r,(HBRUSH)brush);
		
	SetPen(FALSE);

	R=LastColor&0xff; G=(LastColor>>8)&0xff; B=(LastColor>>16)&0xff;

	SetBrushColor(R, G, B);

	return true;
}


/*******************************************************
* Nom : Media_DrawEllipse
*
* Description : 
*
* -Parametres-
* int xOrg: Origine
* int yOrg: 
* int xDst: Destination
* int yDst: 
*
* Retour : true si ok, false sinon
*******************************************************/
bool Media_DrawEllipse(Parameters *Param)
{
	if(!Param)
		return false;

	HBRUSH brush, Old;

	SetPen(TRUE);
	brush = CreateSolidBrush(GetBrushColor());
	Old = (HBRUSH)SelectObject(Scene_DC, brush);

	Ellipse(Scene_DC, Param->Val[0], Param->Val[1], Param->Val[2], Param->Val[3]);

	SelectObject(Scene_DC, Old);
	DeleteObject(brush);
	SetPen(FALSE);

	return true;
}


/*******************************************************
* Nom : Media_DrawRect
*
* Description : 
*
* -Parametres-
* int xOrg: Origine
* int yOrg: 
* int xDst: Destination
* int yDst: 
*
* Retour : true si ok, false sinon
*******************************************************/
bool Media_DrawRect(Parameters *Param)
{
	if(!Param)
		return false;

	RECT r;
	HBRUSH brushpen, brush, Old;

	SetPen(TRUE);
	brush = CreateSolidBrush(GetBrushColor());
	brushpen  = CreateSolidBrush(GetPenColor());
	Old = (HBRUSH)SelectObject(Scene_DC, brush);


	r.bottom=Param->Val[3];
	r.left=Param->Val[0];
	r.right=Param->Val[2];
	r.top=Param->Val[1];
	
	FillRect(Scene_DC, &r,(HBRUSH)brush);
	FrameRect(Scene_DC, &r,(HBRUSH)brushpen);
		
	SelectObject(Scene_DC, Old);
	DeleteObject(brush);
	DeleteObject(brushpen);
	SetPen(FALSE);

	return true;
}


/*******************************************************
* Nom : Media_TextOut
*
* Description : Ecrit une chaine de caractères
*
* -Parametres-
* Parameters *Param: 
*
* Retour : true si ok, false sinon
*******************************************************/
bool	Media_TextOut(Parameters *Param)
{
	if(!Param)
		return false;

	TextOut(Scene_DC, Param->Val[0], Param->Val[1], Param->String, strlen(Param->String));
	return true;
}


/* Fonctions internes au logiciel */

static COLORREF SetPenColor(int R, int G, int B)
{ 
	static COLORREF CurColor = RGB(0,0,0);
	
	if(!(R==-1 && G==-1 && B==-1))
		CurColor = RGB(R, G, B);

	return CurColor;
}

static COLORREF GetPenColor()
{
	return SetPenColor(-1, -1, -1);
}

static void SetPen(bool Set)
{
	static HPEN hPen=0, hOldPen=0;

	if(Set)
	{
		hPen = CreatePen(PS_SOLID,0,GetPenColor());
		hOldPen = (HPEN)SelectObject(Scene_DC, hPen);
	}
	else
	{
		SelectObject(Scene_DC, hOldPen);
		DeleteObject(hPen); 
	}
}

static COLORREF SetBrushColor(int R, int G, int B)
{ 
	static COLORREF CurColor = RGB(0,0,0);
	
	if(!(R==-1 && G==-1 && B==-1))
		CurColor = RGB(R, G, B);

	return CurColor;
}


static COLORREF GetBrushColor()
{
	return SetBrushColor(-1, -1, -1);
}
