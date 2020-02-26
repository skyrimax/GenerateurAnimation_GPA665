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

//------------------------------------------------------------
void Execute(ExecuteMode ExecMode, const char *sScriptFile);

//------------------------------------------------------------
int OpenScript(Animation *Anim, const char *sScriptFile);
int FreeScript(Animation *Anim);

//------------------------------------------------------------
int PlayForwardScript(Animation *Anim);
int PlayBackwardScript(Animation *Anim);



#endif /* _LABORATOIRE2_H_ */