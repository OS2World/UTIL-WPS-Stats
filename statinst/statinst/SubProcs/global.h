/*  global.h */

#define INCL_WIN
#define INCL_DOS
#define INCL_BSE
#define INCL_DOSFILEMGR   
#define INCL_DOSERRORS    
#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <process.h>
#include <bsedos.h>
#include <direct.h>
#include <gdef.h>


APIRET rc;
INT pgmData[4];
HINI hini;
SWP swp;

CHAR cmdhrinstall[GLMAXPATH];
CHAR dwIniFile[GLMAXPATH];
HINI DWhini;

CHAR installDIR[GLMAXPATH];
INT PATHRet;
PEAOP2 pbuf;
BOOL UPDATECONFIG;
BOOL ISCANCELLED;
BOOL UNINSTALLME;
BOOL DELETELIBPATH;



// extern INT existPath(CHAR *pathStr);
extern VOID msgOK(CHAR *title, CHAR *message);
extern VOID debugMsgStr(CHAR *str, CHAR *varName);
extern VOID debugMsgInt(INT num, CHAR *varName);
extern VOID debugMsgULong(ULONG num, CHAR *varName);
extern VOID debugMsgCH(CHAR ch, CHAR *varName);
extern INT addToFile(CHAR *fname, CHAR *fnameTMP, CHAR *dest, CHAR *txtToMatch);
extern INT removeFromFile(CHAR *fname, CHAR *fnameTMP, CHAR *dest, CHAR *txtToMatch);
extern INT createFolders(CHAR *pathStr);
extern INT setFileAttrib(CHAR *uchFileName, ULONG attrib);

