#include <windows.h>
#include <stdio.h>

#include "media.h"
#include "Scene_DC.h"
#include "laboratoire2.h"



//------------------------------------------------------------
//- Fonction qui redirige les appels du programme principal --
//- vers les fonctions que vous allez faires -----------------
//------------------------------------------------------------
void Execute(ExecuteMode ExecMode, const char *sScriptFile)
{
	static Animation Anim;	//Structure contenant l'information g�n�rale sur votre structure de donn�es
}
//------------------------------------------------------------


//------------------------------------------------------------
//- Ouvre le fichier contenant le script et construit toute --
//- la structure de donn�es ----------------------------------
//------------------------------------------------------------
int OpenScript(Animation *Anim, const char *sScriptFile)
{

	return true;
}
//------------------------------------------------------------

//------------------------------------------------------------
//- Lib�re toute la m�moire reli�e � votre structure de ------
//- donn�es --------------------------------------------------
//------------------------------------------------------------
int FreeScript(Animation *Anim)
{

	return true;
}
//------------------------------------------------------------

//------------------------------------------------------------
//- Parcours la structure de donn�es et joue l'animation du --
//- d�but � la fin -------------------------------------------
//------------------------------------------------------------
int PlayForwardScript(Animation *Anim)
{

	return true;
}
//------------------------------------------------------------

//------------------------------------------------------------
//- Parcours la structure de donn�es et joue l'animation de --
//- la fin au d�but ------------------------------------------
//------------------------------------------------------------
int PlayBackwardScript(Animation *Anim)
{

	return true;
}
//------------------------------------------------------------
