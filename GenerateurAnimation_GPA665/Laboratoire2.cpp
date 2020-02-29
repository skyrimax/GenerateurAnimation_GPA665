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

	switch (ExecMode)
	{
	case emOpenScript:
		OpenScript(&Anim, sScriptFile);
		break;
	case emFreeScript:
		FreeScript(&Anim);
		break;
	case emPlayForward:
		PlayForwardScript(&Anim);
		break;
	case emPlayBackward:
		PlayBackwardScript(&Anim);
		break;
	default:
		break;
	}
}
//------------------------------------------------------------

//------------------------------------------------------------
//- Ouvre le fichier contenant le script et construit toute --
//- la structure de donn�es ----------------------------------
//------------------------------------------------------------
int OpenScript(Animation *Anim, const char *sScriptFile)
{
	if (Anim->unload()) {
		return Anim->load(sScriptFile);
	}
	else {
		return false;
	}
}
//------------------------------------------------------------

//------------------------------------------------------------
//- Lib�re toute la m�moire reli�e � votre structure de ------
//- donn�es --------------------------------------------------
//------------------------------------------------------------
int FreeScript(Animation *Anim)
{
	return Anim->unload();
}
//------------------------------------------------------------

//------------------------------------------------------------
//- Parcours la structure de donn�es et joue l'animation du --
//- d�but � la fin -------------------------------------------
//------------------------------------------------------------
int PlayForwardScript(Animation *Anim)
{
	return Anim->playForward();
}
//------------------------------------------------------------

//------------------------------------------------------------
//- Parcours la structure de donn�es et joue l'animation de --
//- la fin au d�but ------------------------------------------
//------------------------------------------------------------
int PlayBackwardScript(Animation *Anim)
{
	return Anim->playBackward();
}
//------------------------------------------------------------
