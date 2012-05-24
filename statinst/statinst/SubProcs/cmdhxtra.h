/* cmdxtra.h */


#define INCL_WIN
#define INCL_DOS
#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <process.h>
#include <direct.h>
#include <gdef.h>



HWND hwndMain, hwndMenu;
HAB hab;
extern INT pgmData[4];
extern HINI hini;
extern SWP swp;
ULONG titlebH, menubH;
extern APIRET rc;
CHAR dTopDir[] = " :\\Desktop\\";
CHAR helpDir[] = " :\\os2\\help";
CHAR libDir[] = " :\\os2\\dll";
extern CHAR installDIR[];

CHAR eraseFile[GLMAXPATH];
CHAR cwdir[GLMAXPATH];
CHAR nfe[GLMAXPATH];
extern CHAR dwIniFile[GLMAXPATH];
extern HINI DWhini;

VOID msgOK(CHAR *title, CHAR *message);
ULONG getCurDiskNum(VOID);
VOID saveDesktopName(VOID);
VOID eraseDesktopName(VOID);
VOID replaceCFG(CHAR *cfgName);
VOID replaceINCFG(CHAR *cfgName);
VOID debugMsgStr(CHAR *str, CHAR *varName);
VOID debugMsgInt(INT num, CHAR *varName);
VOID debugMsgULong(ULONG num, CHAR *varName);
VOID debugMsgCH(CHAR ch, CHAR *varName);
BOOL copyFile (CHAR *fn, CHAR *target);
BOOL replaceFile (CHAR *fn);
INT existFile(CHAR *fileStr);
VOID setFileName(CHAR *fn);
// INT existPath(CHAR *pathStr);
INT addToFile(CHAR *fname, CHAR *fnameTMP, CHAR *dest, CHAR *txtToMatch);
INT removeFromFile(CHAR *fname, CHAR *fnameTMP, CHAR *dest, CHAR *txtToMatch);
INT createFolders(CHAR *pathStr);
VOID strdelc(CHAR *s, CHAR c);
INT strndel(CHAR *s, INT n);
INT setFileAttrib(CHAR *uchFileName, ULONG attrib);



