#ifndef	_MEDIA_H_
#define	_MEDIA_H_


/* -------------------------------------------------------------------------
 * Declarations
 * ------------------------------------------------------------------------- */
typedef struct {
	int NbrParam;		/* Le nombre de paramètre utilisés */
	int Val[8];		/* Les N paramètres utilisés */
	char String[256]; /* Paramètre sous forme de chaîne de caractères */
} Parameters;


bool	Media_Clear(Parameters *Param);
bool	Media_Delay(Parameters *Param);
bool	Media_DrawLine(Parameters *Param);
bool	Media_DrawPixel(Parameters *Param);
bool	Media_DrawRect(Parameters *Param);
bool	Media_DrawEllipse(Parameters *Param);
bool	Media_DrawArc(Parameters *Param);
bool	Media_SetBrushColor(Parameters *Param);
bool	Media_SetPenColor(Parameters *Param);
bool	Media_PlaySound(Parameters *Param);
bool	Media_TextOut(Parameters *Param);


// Fonctions internes au logiciel
bool Media_SetCurrentWindowSize(int *cx, int *cy, bool set);

#endif /* _MEDIA_H_ */