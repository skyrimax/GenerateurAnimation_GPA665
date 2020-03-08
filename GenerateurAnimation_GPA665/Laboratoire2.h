#ifndef	_LABORATOIRE2_H_
#define	_LABORATOIRE2_H_
#include "Animation.h"

enum ExecuteMode
{
	emOpenScript,
	emFreeScript,
	emPlayForward,
	emPlayBackward
};

// Redirection function, excecute on of the other functions depending on ExecMode
void Execute(ExecuteMode ExecMode, const char *sScriptFile);

// Functions to load and unload the animation
int OpenScript(Animation *Anim, const char *sScriptFile);
int FreeScript(Animation *Anim);

// Functions to play the animation forward and backward
int PlayForwardScript(Animation *Anim);
int PlayBackwardScript(Animation *Anim);

#endif /* _LABORATOIRE2_H_ */