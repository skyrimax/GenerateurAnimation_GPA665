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
	static Animation Anim;	//Structure contenant l'information générale sur votre structure de données

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
//- la structure de données ----------------------------------
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
//- Libère toute la mémoire reliée à votre structure de ------
//- données --------------------------------------------------
//------------------------------------------------------------
int FreeScript(Animation *Anim)
{
	return Anim->unload();
}
//------------------------------------------------------------

//------------------------------------------------------------
//- Parcours la structure de données et joue l'animation du --
//- début à la fin -------------------------------------------
//------------------------------------------------------------
int PlayForwardScript(Animation *Anim)
{
	return Anim->playForward();
}
//------------------------------------------------------------

//------------------------------------------------------------
//- Parcours la structure de données et joue l'animation de --
//- la fin au début ------------------------------------------
//------------------------------------------------------------
int PlayBackwardScript(Animation *Anim)
{
	return Anim->playBackward();
}
//------------------------------------------------------------
