#ifndef	_LABORATOIRE2_H_
#define	_LABORATOIRE2_H_


enum ExecuteMode
{
	emOpenScript,
	emFreeScript,
	emPlayForward,
	emPlayBackward
};


//------------------------------------------------------------
//------------------ Fonctions à modifier --------------------
//------------------------------------------------------------

/*************************************************************
************************** ATTENTION *************************
**************************************************************
* Les fichiers Laboratoire2.c et Laboratoire2.cpp font
* souvent référence au type de donnée Animation qui n'existe
* pas encore.  C'est à vous de déclarer tous les types 
* associés dans votre nouveau *.h.  Sans l'inclusion de ce 
* nouveau fichier avec la déclaration correcte de vos types
* de données, il sera impossible de compiler le présent
* projet
**************************************************************
************* Vous pouvez effacer ce commentaire *************
*************************************************************/
typedef struct{
}Animation;

#pragma message("*************************************************\n")
#pragma message("** Attention: Structure Animation vide a ete cree \n")
#pragma message("** dans laboratoire2.h. Veuillez remplacer cette \n")
#pragma message("** structure par la votre dans un fichier approprie. \n")
#pragma message("*************************************************\n")

//------------------------------------------------------------
void Execute(ExecuteMode ExecMode, const char *sScriptFile);

//------------------------------------------------------------
int OpenScript(Animation *Anim, const char *sScriptFile);
int FreeScript(Animation *Anim);

//------------------------------------------------------------
int PlayForwardScript(Animation *Anim);
int PlayBackwardScript(Animation *Anim);



#endif /* _LABORATOIRE2_H_ */