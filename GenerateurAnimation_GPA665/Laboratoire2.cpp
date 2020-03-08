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

	// Chose action depending on ExecMode
	switch (ExecMode)
	{
	case emOpenScript:
		// Load the animation from sScriptFile
		OpenScript(&Anim, sScriptFile);
		break;
	case emFreeScript:
		// Unload the animation
		FreeScript(&Anim);
		break;
	case emPlayForward:
		// Plays the animation forward
		PlayForwardScript(&Anim);
		break;
	case emPlayBackward:
		// Play the animation backward
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
	// Unload animation if is isn't empty
	if (Anim->unload()) {
		// Load animation from sScriptFile
		if (!Anim->load(sScriptFile)) {
			// If there is an error while the animation is being loaded,
			// Will unload animation and return that an error occurred
			Anim->unload();
			return false;
		}
	}
	// If unloading fails, return that an error occurred
	else {
		return false;
	}

	// If all goes well, return that no error occurred
	return true;
}
//------------------------------------------------------------

//------------------------------------------------------------
//- Lib�re toute la m�moire reli�e � votre structure de ------
//- donn�es --------------------------------------------------
//------------------------------------------------------------
int FreeScript(Animation *Anim)
{
	// Unload animation and return if it was successful
	return Anim->unload();
}
//------------------------------------------------------------

//------------------------------------------------------------
//- Parcours la structure de donn�es et joue l'animation du --
//- d�but � la fin -------------------------------------------
//------------------------------------------------------------
int PlayForwardScript(Animation *Anim)
{
	// Play animation forward and return if it was successful
	return Anim->playForward();
}
//------------------------------------------------------------

//------------------------------------------------------------
//- Parcours la structure de donn�es et joue l'animation de --
//- la fin au d�but ------------------------------------------
//------------------------------------------------------------
int PlayBackwardScript(Animation *Anim)
{
	// Play animation backward and return if it was successful
	return Anim->playBackward();
}
//------------------------------------------------------------
