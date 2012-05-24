/* cmdhxtra.c  */

#include "cmdhxtra.h"



INT createFolders(CHAR *pathStr)
{
INT i, k, numFolds;
INT mark[50];
CHAR tmpStr[GLMAXPATH];
CHAR baseFold[GLMAXPATH];
CHAR mainFold[GLMAXPATH];
CHAR str[GLMAXPATH];
CHAR DTOPNAME[GLMAXPATH];
CHAR TMPtmpStr[GLMAXPATH];


numFolds = 0;
strcpy(tmpStr, pathStr);
if( tmpStr[strlen(tmpStr)-1] != '\\' )
   strcat(tmpStr, "\\");

for( i=0,k=0;i<strlen(tmpStr);i++ )
   {
   if( tmpStr[i] == '\\' )
      {
      numFolds++;
      mark[k] = i;
      k++;
      }
   }

for( i=0;i<(numFolds -1);i++ )
   {
   strncpy(baseFold, tmpStr, mark[i]);
   baseFold[mark[i]] = '\0';

   strncpy(mainFold, tmpStr+(mark[i]+1), (mark[i+1])-(mark[i]+1));
   mainFold[(mark[i+1])-(mark[i]+1)] = '\0';

   if( (i == 0) && (strlen(baseFold) == 2) && (baseFold[1] == ':') )
      strcat(baseFold, "\\");
      
   WinCreateObject("WPFolder",
                           mainFold,
                           "CLOSED=DEFAULT",
                           baseFold,
                           CO_FAILIFEXISTS);
   }
return(1);
}



INT removeFromFile(CHAR *fname, CHAR *fnameTMP, CHAR *dest, CHAR *txtToMatch)
{
HFILE fhan, fhanTMP;
APIRET rc, rcTMP;
INT i, k;
ULONG act, actTMP, rd, local, slen, wheat;
CHAR fline[GLMAXPATH] = "";
CHAR wrline[GLMAXPATH];
CHAR tmpStr1[GLMAXPATH];
CHAR tmpStr2[GLMAXPATH];
CHAR nline[] = "\x0a";
CHAR dline[] = "\x0d";

// debugMsgStr(dest, "dest");
// return(0);
rc = DosOpen (fname, &fhan, &act, 0L, 0, 0x0001, 0x20C0, 0L);
rcTMP = DosOpen(fnameTMP, &fhanTMP, &actTMP, 0L, 0, 0x0012, OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE, 0L); 
if (rc != 0 || act != 0x0001 || rcTMP != 0)
   {
   DosClose(fhan);
   DosClose(fhanTMP);
   }
else
   {
   do
      {
      fline[0] = '\0';    /* reset the line to "" */
      k = 0;
      do
         {
         DosRead(fhan, fline+k, sizeof(fline[0]), &rd);
         if( fline[k] != '\n' )
            {
            k++;
            }
         }
      while( rd > 0 && fline[k] != '\n' );
      fline[k] = '\0';
      
      slen = strlen(fline);
      if( slen > 12 && rd > 0 )
         {
         if( strnicmp(fline, "LIBPATH=", 8) == 0 )
            {
            CHAR shs[GLMAXPATH] = "";
            CHAR *result;
            
            strcpy(shs, dest);
            strcat(shs, ";");
            
            strcpy(wrline, fline);
            strcpy(tmpStr1, wrline);
            strcpy(tmpStr2, shs);
            strupr(tmpStr1);
            strupr(tmpStr2);
            result = strstr(tmpStr1, tmpStr2);
            if( result != NULL )
               {
               strcpy(tmpStr1, wrline);
               strndel(result, strlen(shs));
               strcat(tmpStr1, nline);
               DosWrite(fhanTMP, tmpStr1, strlen(tmpStr1), &actTMP);
               }
            else
               {      
               strcpy(tmpStr1, wrline);
               strcpy(tmpStr2, dest);
               strupr(tmpStr1);
               strupr(tmpStr2);
               result = strstr(tmpStr1, tmpStr2);
               if( result != NULL )
                  {
                  strcpy(tmpStr1, wrline);
                  strndel(result, strlen(dest));
                  strcat(tmpStr1, nline);
                  DosWrite(fhanTMP, tmpStr1, strlen(tmpStr1), &actTMP);
                  }
               else
                  {
                  strcpy(wrline, fline);
                  strcat(wrline, nline);
                  DosWrite(fhanTMP, wrline, strlen(wrline), &actTMP);
                  }   
               }
            }
         else
            {   
            strcpy(wrline, fline);
            strcat(wrline, nline);
            DosWrite(fhanTMP, wrline, strlen(wrline), &actTMP);
            }
         }
      else
         {
         if( rd > 0 )
            {
            strcpy(wrline, fline);
            strcat(wrline, nline);
            DosWrite(fhanTMP, wrline, strlen(wrline), &actTMP);
            }
         }       
      }
   while(rd >0);
   }
DosClose(fhan);
DosClose(fhanTMP);
return(1);
}




INT addToFile(CHAR *fname, CHAR *fnameTMP, CHAR *dest, CHAR *txtToMatch)
{
HFILE fhan, fhanTMP;
APIRET rc, rcTMP;
INT i, k;
ULONG act, actTMP, rd, local, slen, wheat;
CHAR fline[GLMAXPATH] = "";
CHAR wrline[GLMAXPATH];
CHAR nline[] = "\x0a";
CHAR dline[] = "\x0d";
CHAR destUpr[GLMAXPATH];
CHAR flineUpr[GLMAXPATH];


rc = DosOpen (fname, &fhan, &act, 0L, 0, 0x0001, 0x20C0, 0L);
rcTMP = DosOpen(fnameTMP, &fhanTMP, &actTMP, 0L, 0, 0x0012, OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE, 0L); 
if (rc != 0 || act != 0x0001 || rcTMP != 0)
   {
   DosClose(fhan);
   DosClose(fhanTMP);
   }
else
   {
   do
      {
      fline[0] = '\0';    /* reset the line to "" */
      k = 0;
      do
         {
         DosRead(fhan, fline+k, sizeof(fline[0]), &rd);
         if( fline[k] != '\n' )
            {
            k++;
            }
         }
      while( rd > 0 && fline[k] != '\n' );
      fline[k] = '\0';


      slen = strlen(fline);
      if( slen > 12 && rd > 0 )
         {
         strcpy(destUpr, dest);
         strupr(destUpr);
         strcpy(flineUpr, fline);
         strupr(flineUpr);
         if( (strnicmp(fline, "LIBPATH=", 8) == 0) && (strstr(flineUpr, destUpr) == NULL) )
            {
            CHAR shs[GLMAXPATH] = "";
            CHAR sh[GLMAXPATH] = "";
            
            strcpy(shs, dest);
            strcat(shs, ";");
            
            strcpy(sh, ";");
            strcat(sh, dest);
            strcat(sh, ";");
            
            if( fline[k-2] == ';' )
               {
               strcpy(wrline, fline);
               strcat(wrline, shs);
               strdelc(wrline, '\x0d');
               strcat(wrline, dline);
               strcat(wrline, nline);
               DosWrite(fhanTMP, wrline, strlen(wrline), &actTMP);
               }
            else   
               {
               strcpy(wrline, fline);
               strcat(wrline, sh);
               strdelc(wrline, '\x0d');
               strcat(wrline, dline);
               strcat(wrline, nline);
               DosWrite(fhanTMP, wrline, strlen(wrline), &actTMP);
               }
            }
         else
            {   
            strcpy(wrline, fline);
            strcat(wrline, nline);
            DosWrite(fhanTMP, wrline, strlen(wrline), &actTMP);
            }
         }
      else
         {
         if( rd > 0 )
            {
            strcpy(wrline, fline);
            strcat(wrline, nline);
            DosWrite(fhanTMP, wrline, strlen(wrline), &actTMP);
            }
         }       
      }
   while(rd >0);
   }
DosClose(fhan);
DosClose(fhanTMP);
return(1);
}




VOID msgOK(CHAR *title, CHAR *message)
{
WinMessageBox(HWND_DESKTOP,
              HWND_DESKTOP,
              message,
              title,
              0,
              MB_OK | MB_ICONEXCLAMATION );
}



/*
INT existPath(CHAR *pathStr)
{
int done, len, drv;

CHAR path[_MAX_PATH] = "";
CHAR curPath[_MAX_PATH] = "";
_getcwd(curPath, sizeof(curPath));
pathStr = strupr(pathStr);
strcpy(path, pathStr);
len = strlen(path);
drv = _getdrive();
_chdrive( 64 - path[0] );
if( path[len - 1] == '\\' && len > 3 )
   path[len - 1] = '\0';
done = _chdir(path);
if ( done == -1 )
   {
   _chdir(curPath);
   return(0);
   }
else
   {
   _chdrive(drv);
   return(1);
   }
}
*/

INT existFile(CHAR *fileStr)
{
FILEFINDBUF3 findbuf;
HDIR hDir = HDIR_CREATE;
ULONG usSearchCount = 1;
ULONG ALLFILES;


ALLFILES = FILE_NORMAL | FILE_ARCHIVED | FILE_SYSTEM | FILE_READONLY | FILE_HIDDEN;
if(DosFindFirst(fileStr, &hDir, ALLFILES, (PVOID)&findbuf, sizeof(findbuf), &usSearchCount, FIL_STANDARD))
   {
   DosFindClose(hDir);
   return(0);
   }
else
   {
   DosFindClose(hDir);
   return(1);
   }
}


VOID setFileName(CHAR *fn)
{
INT s;
CHAR tmpf[GLMAXPATH];
CHAR num[4];

s = 0;
do
   {
   strcpy(tmpf, fn);
   itoa(s, num, 10);
  
   if( s<10 )
      {
      tmpf[strlen(tmpf)-2] = '0';
      tmpf[strlen(tmpf)-1] = num[0];
      }
   else
      {
      tmpf[strlen(tmpf)-2] = num[0];
      tmpf[strlen(tmpf)-1] = num[1];
      }
   s++;      
   }
while( existFile(tmpf) && s<98 );
strcpy(fn, tmpf);
}


VOID replaceCFG(CHAR *cfgName)
{
FILE *hfile;
CHAR cfgSaveName[GLMAXPATH];
FILESTATUS3 fs3 ;
PCHAR pBuffer ;
HFILE hfileX;
ULONG ulAction, ulActionX, ulBytesRead, ulBytesWritten ;
APIRET apiret, apX;
ULONG pointpos;
CHAR spaceStr = '\n';
CHAR exitStr[] = "exit";
CHAR commandStr[GLMAXPATH];
CHAR cfgSName[] = " :\\config.$9e";


cfgSName[0] = dTopDir[0]; 
strcpy(commandStr, "RUN="); 
strcat(commandStr, cwdir);
if( commandStr[strlen(commandStr)-1] != '\\' )
   strcat(commandStr, "\\");
strcat(commandStr, "nferase.exe nfe");


apX = DosOpen(cfgSName, 
              &hfileX,
              &ulActionX,
              0L,
              FILE_NORMAL,
              OPEN_ACTION_OPEN_IF_EXISTS,
              OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE | OPEN_FLAGS_SEQUENTIAL,
              NULL);

if( apX == 0 )
   {
   apX = DosQueryFileInfo(hfileX, FIL_STANDARD,
                          (PVOID)&fs3, sizeof( fs3)) ;
   if( (apX == 0) && fs3.cbFileAlloc)
      {
      apX = DosAllocMem((PPVOID)&pBuffer, fs3.cbFileAlloc, PAG_WRITE | PAG_COMMIT) ;
      if( apX == 0 )
         {
         if( (apX = DosRead(hfileX, (PVOID)pBuffer,
                           fs3.cbFile, &ulBytesRead)) )
            DosFreeMem(pBuffer) ;
         }   
      }   
   }
     
DosClose(hfileX) ;

/*      
if((apiret = DosOpen(cfgName, &hfile,
                                    &ulAction,
                                    0L,
                                    FILE_NORMAL,
                                    OPEN_ACTION_OPEN_IF_EXISTS | OPEN_ACTION_CREATE_IF_NEW,
                                    OPEN_ACCESS_WRITEONLY | OPEN_SHARE_DENYWRITE,
                                    NULL)))
   return FALSE ;
*/

hfile = fopen(cfgName, "a+");
fwrite(&spaceStr, sizeof(spaceStr)*(sizeof(CHAR)), 1, hfile);
fwrite(&commandStr, strlen(commandStr)*(sizeof(CHAR)), 1, hfile);
fwrite(&spaceStr, sizeof(spaceStr)*(sizeof(CHAR)), 1, hfile);
fclose(hfile);

/*
DosSetFilePtr(hfile, 0, FILE_END, &pointpos);  
DosWrite (hfile, &spaceStr, sizeof(spaceStr), &ulBytesWritten);
DosWrite (hfile, commandStr, strlen(commandStr)*(sizeof(CHAR)), &ulBytesWritten);
DosWrite (hfile, &spaceStr, sizeof(spaceStr), &ulBytesWritten);

if( apX == 0 )
   {
   DosWrite (hfile, pBuffer, ulBytesRead, &ulBytesWritten);
   DosFreeMem(pBuffer) ;
   }
else
   {   
   DosWrite (hfile, &spaceStr, sizeof(spaceStr), &ulBytesWritten);
   DosWrite (hfile, exitStr, strlen(exitStr)*(sizeof(CHAR)), &ulBytesWritten);
   } 
DosClose(hfile) ;
*/
}


VOID replaceINCFG(CHAR *cfgName)
{
FILE *hfile;
CHAR cfgSaveName[GLMAXPATH];
FILESTATUS3 fs3 ;
PCHAR pBuffer ;
HFILE hfileX;
ULONG ulAction, ulActionX, ulBytesRead, ulBytesWritten ;
APIRET apiret, apX;
ULONG pointpos;
CHAR spaceStr = '\n';
CHAR exitStr[] = "exit";
CHAR commandStr[GLMAXPATH];
CHAR cfgSName[] = " :\\config.$9e";


cfgSName[0] = dTopDir[0]; 
strcpy(commandStr, "RUN="); 
strcat(commandStr, cwdir);
if( commandStr[strlen(commandStr)-1] != '\\' )
   strcat(commandStr, "\\");
strcat(commandStr, "nferase.exe nfeIN");


apX = DosOpen(cfgSName, 
              &hfileX,
              &ulActionX,
              0L,
              FILE_NORMAL,
              OPEN_ACTION_OPEN_IF_EXISTS,
              OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE | OPEN_FLAGS_SEQUENTIAL,
              NULL);

if( apX == 0 )
   {
   apX = DosQueryFileInfo(hfileX, FIL_STANDARD,
                          (PVOID)&fs3, sizeof( fs3)) ;
   if( (apX == 0) && fs3.cbFileAlloc)
      {
      apX = DosAllocMem((PPVOID)&pBuffer, fs3.cbFileAlloc, PAG_WRITE | PAG_COMMIT) ;
      if( apX == 0 )
         {
         if( (apX = DosRead(hfileX, (PVOID)pBuffer,
                           fs3.cbFile, &ulBytesRead)) )
            DosFreeMem(pBuffer) ;
         }   
      }   
   }
     
DosClose(hfileX) ;

hfile = fopen(cfgName, "a+");
fwrite(&spaceStr, sizeof(spaceStr)*(sizeof(CHAR)), 1, hfile);
fwrite(&commandStr, strlen(commandStr)*(sizeof(CHAR)), 1, hfile);
fwrite(&spaceStr, sizeof(spaceStr)*(sizeof(CHAR)), 1, hfile);
fclose(hfile);
}


BOOL copyFile (CHAR *fn, CHAR *target)
{
HFILE hfile ;
HFILE hfileT ;
ULONG ulAction, ulBytesRead ;
ULONG ulActionT, ulBytesWritten;
APIRET apiret ;
APIRET apiretT ;
FILESTATUS3 fs3 ;
PCHAR pBuffer ;

if( (apiret = DosOpen(fn, &hfile,
                       &ulAction,
                       0L,
                       FILE_NORMAL,
                       OPEN_ACTION_OPEN_IF_EXISTS,
                       OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE | OPEN_FLAGS_SEQUENTIAL,
                       NULL)) )
   return FALSE ;

apiret = DosQueryFileInfo(hfile, FIL_STANDARD,
                            (PVOID)&fs3, sizeof( fs3)) ;
if( apiret || !fs3.cbFileAlloc)
   return FALSE ;

apiret = DosAllocMem((PPVOID)&pBuffer, fs3.cbFileAlloc, PAG_WRITE | PAG_COMMIT) ;
if(apiret)
   {
   DosClose(hfile) ;
   return FALSE ;
   }

if( apiret = DosRead(hfile, (PVOID)pBuffer,
                       fs3.cbFile, &ulBytesRead))
   {
   DosFreeMem(pBuffer) ;
   DosClose(hfile) ;
   return FALSE ;
   }

/******** OPEN TARGET FILE ***********/
apiretT = DosOpen (target, &hfileT, &ulActionT, 0L, 0, 0x0012, 0x20C1, 0L);
if (apiretT == 0 && (ulActionT == 0x0002 || ulActionT == 0x0003)) 
   {
   apiretT = DosWrite (hfileT, pBuffer, ulBytesRead, &ulBytesWritten);
   if ((apiretT != 0) || (ulBytesRead != ulBytesWritten))
      {
      DosClose (hfileT);
      DosFreeMem(pBuffer) ;
      DosClose(hfile) ;
      return FALSE;
      }
         
   apiretT = DosClose (hfileT);
   
   if (apiretT != 0)
      {
      DosFreeMem(pBuffer) ;
      DosClose(hfile) ;
      return FALSE;
      }
   }
else
   {
   DosFreeMem(pBuffer) ;
   DosClose(hfile) ;
   return FALSE;
   }
   
DosFreeMem(pBuffer) ;
DosClose(hfile) ;
return TRUE ;
}



BOOL replaceFile (CHAR *fn)
{
FILESTATUS3 fs3 ;
PCHAR pBuffer ;
HFILE hfile, hfileX;
ULONG ulAction, ulActionX, ulBytesRead, ulBytesWritten ;
APIRET apiret, apX;
ULONG pointpos;
CHAR spaceStr = '\n';
CHAR exitStr[] = "exit";
CHAR commandStr[GLMAXPATH];
CHAR cfgSName[] = " :\\startup.$9e";
/* CHAR spaceStr[] = "\x0a\x0d"; */
/* CHAR endFile[] = "\x00"; */
/* CHAR endFile[] = "\x00"; */


cfgSName[0] = dTopDir[0]; 
strcpy(commandStr, "START /PM "); 
strcat(commandStr, cwdir);
if( commandStr[strlen(commandStr)-1] != '\\' )
   strcat(commandStr, "\\");
strcat(commandStr, "nferase.exe nfe");


apX = DosOpen(cfgSName, 
              &hfileX,
              &ulActionX,
              0L,
              FILE_NORMAL,
              OPEN_ACTION_OPEN_IF_EXISTS,
              OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE | OPEN_FLAGS_SEQUENTIAL,
              NULL);

if( apX == 0 )
   {
   apX = DosQueryFileInfo(hfileX, FIL_STANDARD,
                          (PVOID)&fs3, sizeof( fs3)) ;
   if( (apX == 0) && fs3.cbFileAlloc)
      {
      apX = DosAllocMem((PPVOID)&pBuffer, fs3.cbFileAlloc, PAG_WRITE | PAG_COMMIT) ;
      if( apX == 0 )
         {
         if( (apX = DosRead(hfileX, (PVOID)pBuffer,
                           fs3.cbFile, &ulBytesRead)) )
            DosFreeMem(pBuffer) ;
         }   
      }   
   }
      
DosClose(hfileX) ;
      
if(apiret = DosOpen(fn, &hfile,
                    &ulAction,
                    0L,
                    FILE_NORMAL,
                    OPEN_ACTION_OPEN_IF_EXISTS | OPEN_ACTION_CREATE_IF_NEW,
                    OPEN_ACCESS_WRITEONLY | OPEN_SHARE_DENYWRITE,
                    NULL))
   return FALSE ;

/* DosSetFilePtr(hfile, 0, FILE_END, &pointpos);  */
DosWrite (hfile, &spaceStr, sizeof(spaceStr), &ulBytesWritten);
DosWrite (hfile, commandStr, strlen(commandStr)*(sizeof(CHAR)), &ulBytesWritten);
DosWrite (hfile, &spaceStr, sizeof(spaceStr), &ulBytesWritten);
if( apX == 0 )
   {
   DosWrite (hfile, pBuffer, ulBytesRead, &ulBytesWritten);
   DosFreeMem(pBuffer) ;
   }
else
   {   
   DosWrite (hfile, &spaceStr, sizeof(spaceStr), &ulBytesWritten);
   DosWrite (hfile, exitStr, strlen(exitStr)*(sizeof(CHAR)), &ulBytesWritten);
   }
DosClose(hfile) ;

return TRUE ;
}




ULONG getCurDiskNum(VOID)
{
ULONG drvNum, ulDriveMap;

if(DosQueryCurrentDisk(&drvNum, &ulDriveMap) != 0 )
   return(0);
return(drvNum);
}


VOID saveDesktopName(VOID)
{
HOBJECT dthan;

dthan = WinQueryObject("<WP_DESKTOP>");

PrfWriteProfileData(HINI_USERPROFILE,
                    "NFNF_DTN",
                    "NFNF_DTN1",
                    &dthan,
                    sizeof(dthan));
}


VOID eraseDesktopName(VOID)
{
PrfWriteProfileData(HINI_USERPROFILE, "NFNF_DTN", NULL, NULL, 0L);
}



VOID debugMsgStr(CHAR *str, CHAR *varName)
{
CHAR dMsg[255] = "Debug Message string ... ";

strcat(dMsg, varName),
WinMessageBox( HWND_DESKTOP,
	       HWND_DESKTOP,
	       str,
	       dMsg,
	       0,
	       MB_OK | MB_ICONEXCLAMATION );
}

VOID debugMsgInt(INT num, CHAR *varName)
{
CHAR str[255] = "";
CHAR dMsg[255] = "Debug Message Int ... ";

strcat(dMsg, varName),
itoa(num, str, 10);
WinMessageBox( HWND_DESKTOP,
	       HWND_DESKTOP,
	       str,
	       dMsg,
	       0,
	       MB_OK | MB_ICONEXCLAMATION );
}


VOID debugMsgULong(ULONG num, CHAR *varName)
{
CHAR str[255] = "";
CHAR dMsg[255] = "Debug Message Int ... ";

strcat(dMsg, varName),
ultoa(num, str, 10);
WinMessageBox(HWND_DESKTOP,
              HWND_DESKTOP,
              str,
              dMsg,
              0,
              MB_OK | MB_ICONEXCLAMATION );
}

VOID debugMsgCH(CHAR ch, CHAR *varName)
{
CHAR str[255] = "";
CHAR dMsg[255] = "Debug Message char ... ";

strcat(dMsg, varName),
str[0] = ch;
str[1] = '\0';
WinMessageBox( HWND_DESKTOP,
	       HWND_DESKTOP,
	       str,
	       dMsg,
	       0,
	       MB_OK | MB_ICONEXCLAMATION );
}


VOID strdelc(CHAR *s, CHAR c)
{
while(*s)
   {
   if(*s == c)
      strcpy(s, s+1);
   else
      s++;   
   }
}

INT strndel(CHAR *s, INT n)
{
INT len;

len = strlen(s);
if(len < n)
   return(0);
strcpy(s, s + n);
return(1);   
}


INT setFileAttrib(CHAR *uchFileName, ULONG attrib)
{
HFILE       fhDelFile       = 0;               
FILESTATUS3 fsts3FileInfo   = {{0}};  
ULONG       ulBufferSize    = sizeof(FILESTATUS3); 
ULONG       ulOpenAction    = 0;                 
APIRET      rc  = 0;         
 
                   
rc = DosOpen(uchFileName, &fhDelFile,
                   &ulOpenAction, 10L, FILE_NORMAL, 
                   OPEN_ACTION_FAIL_IF_NEW | OPEN_ACTION_OPEN_IF_EXISTS,
                   OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE, 0L);

if (rc != 0) 
   {
   return(0);       
   }
 
rc = DosQueryFileInfo(fhDelFile, FIL_STANDARD,
                              &fsts3FileInfo, ulBufferSize);  
                              
if (rc != 0) 
   {
   return(0);
   }
 
fsts3FileInfo.attrFile  = attrib;

rc = DosSetFileInfo(fhDelFile, FIL_STANDARD,
                           &fsts3FileInfo, ulBufferSize);
                         
if (rc != 0) 
   {
   return(0);
   }
 
rc = DosClose(fhDelFile);

if (rc != 0) 
   {
   return(0);
   }
else   
   {
   return(1);
   }
 }
 

