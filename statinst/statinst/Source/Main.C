/******************************************************************************/
/*                                                                            */
/* Program: STATINST.EXE                                                      */
/*                                                                            */
/* Description: Description                                                   */
/*                                                                            */
/* File Name : Main.C                                                         */
/*                                                                            */
/* Author : GARY L. ROBINSON                                                  */
/*                                                                            */
/* Copyright 1997 Copyright notice                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5013754                          */
/*                                                                            */
/******************************************************************************/

/* ##START Form.41 Top of source file */
/* ##END Top of source file */
#define INCL_WIN
#define INCL_NLS
#define INCL_DOS
#define INCL_GPI
#include <os2.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/* ##START Form.43 Pre include files */
/* ##END Pre include files */
#include "MAIN.H"
#include "Main.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */

#include "global.h"
#include "NPATH.h"
#include "NEWCFG.h"
#include "AREYOU.h"
/* ##END Extra include files */
/* declare main forms info block */
PMAINFORMINFO pMainFormInfo;

int main(int argc, char *argv[], char *envp[])                                                  
{                                                                           
  HAB   hab;                                                                
  QMSG  qmsg;                                                               
  HMQ  hmq;                                                               
  HWND  hwndMainFrame;                                                               
                                                                            
  /* ##START Form.40 Top of application procedure */
  /* ##END Top of application procedure */
                                                                            
  hab = WinInitialize( 0 );                                                 
  if(!hab) {                                                                
    exit(1);                                                                
  }                                                                         
                                                                            
  hmq = WinCreateMsgQueue( hab, 0 );                                        
  if(!hmq) {                                                                
    WinTerminate(hab);                                                      
    exit(1);                                                                
  }                                                                         
  pMainFormInfo = malloc(sizeof(MAINFORMINFO));
  memset((PVOID) pMainFormInfo, 0, sizeof(MAINFORMINFO));

  /* ##START Form.35 Application initialization */
  /* ##END Application initialization */

  hwndMainFrame = OpenMain(HWND_DESKTOP, pMainFormInfo);
  if (!hwndMainFrame) {
     WinDestroyMsgQueue( hmq );
     WinTerminate( hab );
     exit(1);
  }

  /* Get and dispatch messages from the application message queue  */
  /* until WinGetMsg returns FALSE, indicating a WM_QUIT message.  */
  while( WinGetMsg( hab, &qmsg, (HWND)NULL, 0, 0 ) )                        
    WinDispatchMsg( hab, &qmsg );                                           
                                                                            
  /* ##START Form.36 Application termination */
  /* ##END Application termination */
  WinDestroyWindow(hwndMainFrame);
  WinDestroyMsgQueue( hmq );            /* and                          */  
  WinTerminate( hab );                  /* terminate the application    */  
  return(0);                                                                
}                                                                          
MRESULT EXPENTRY MainDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  PMAINFORMINFO pMainFormInfo=(PMAINFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
  HWND hwndFrame = hwndDlg;
 /* ##START Form.37 Top of window procedure */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     if (mp2==0)
        mp2 = (MPARAM) malloc(sizeof(MAINFORMINFO));
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     pMainFormInfo=(PMAINFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
      {
      /* ##START Form.1  */
      /* Form events - Opened */

      CHAR instDir[] = " :\\STATS";
      ULONG bdr;

      DosQuerySysInfo(QSV_BOOT_DRIVE, QSV_BOOT_DRIVE,
            		(PVOID)&bdr, sizeof( bdr)) ;

      instDir[0] = (CHAR)(bdr + '@');      		

      // debugMsgStr(instDir, "instDir");
      WinSetDlgItemText(hwndDlg, 1003, instDir);

      /* Set selection 1003 Entry Field */
      WinSendDlgItemMsg(hwndDlg, 1003,
                        EM_SETSEL,
                        MPFROM2SHORT(0, strlen(instDir)), 0);

      PrfQueryProfileString(HINI_USERPROFILE, 
                            "ZipZapIsInstalled", 
                            "InstallationPath",
      		      "", cmdhrinstall, 
      		      CCHMAXPATH );
      /* ##END  */
      }
      break;

   /* Form event Closed WM_CLOSE */
   case WM_CLOSE :
      /* ##START Form.2  */
      /* ##END  */
     WinPostMsg(hwndDlg, WM_QUIT, 0, 0);
      break;

   case WM_COMMAND :
      switch (SHORT1FROMMP(mp1)) {
      /* Button 1000 Clicked/Selected */
      case 1000:
         {
         /* ##START 1000.0  */
         /* Event Clicked/selected - ~Quit  1000 */

         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      /* Button 1002 Clicked/Selected */
      case 1002:
         {
         /* ##START 1002.0  */
         /* Event Clicked/selected - ~Install  1002 */


         INT tlen;
         CHAR upath[GLMAXPATH];
         USHORT usReturn;
         HWND hNewFrame;
         CHAR cfig[] = " :\\config.sys";
         CHAR cfigTMP[] = " :\\config.$s$";
         CHAR cfigBAKUP[] = " :\\config.sta";
         ULONG bdri;
         HOBJECT destobj, origobj;
         CHAR cPath[GLMAXPATH];
         CHAR cmdDLL[GLMAXPATH];
         CHAR rcstr[GLMAXPATH];




         PrfQueryProfileString(HINI_USERPROFILE, 
                               "StatsIsInstalled", 
                               "InstallationPath",
         		      "", cmdhrinstall, 
         		      CCHMAXPATH );
         		      
         		      
         if( strlen(cmdhrinstall) != 0 )		      
            {
            msgOK("Attention! Stats seems to already be installed!", "Stats must be uninstalled before it can be installed again.");
            return(0);
            }		          


         DosQuerySysInfo(QSV_BOOT_DRIVE, QSV_BOOT_DRIVE, (PVOID)&bdri, sizeof(bdri));

         cfig[0] = (CHAR)(bdri + '@');
         cfigTMP[0] = (CHAR)(bdri + '@');
         cfigBAKUP[0] = (CHAR)(bdri + '@');

         tlen = (LONG)WinQueryDlgItemTextLength(hwndDlg, 1003);
         WinQueryDlgItemText(hwndDlg, 1003, sizeof(installDIR), installDIR);
         WinQueryDlgItemText(hwndDlg, 1004, sizeof(rcstr), rcstr);

         if (tlen < 2)
            {
            msgOK("Attention! Invalid path.", "You must enter a valid path to install Stats!.");
            return(0);
            }  


         PATHRet = 1;

         while( (WinQueryObject(installDIR) == NULLHANDLE) && PATHRet == 1 )
               {
               hNewFrame = OpenNPATH(hwndDlg, 0);
               usReturn = (USHORT) WinProcessDlg(hNewFrame);
               }

         if( PATHRet == 0 )
            return(0);


         UPDATECONFIG = FALSE;
         ISCANCELLED = TRUE;

         {
            USHORT usReturn;
            HWND hNewFrame;
            hNewFrame = OpenNEWCFG(hwndDlg, 0);
            usReturn = (USHORT) WinProcessDlg(hNewFrame);
         }

         if( ISCANCELLED )
            {
            return(0);
            }

         WinEnableWindow(WinWindowFromID(hwndDlg, 1000), FALSE);
         WinEnableWindow(WinWindowFromID(hwndDlg, 1001), FALSE);
         WinEnableWindow(WinWindowFromID(hwndDlg, 1002), FALSE);


         strcpy(cmdDLL, installDIR);
         if( cmdDLL[strlen(cmdDLL)-1] != '\\' )
            strcat(cmdDLL, "\\");
         strcat(cmdDLL, "Stats.dll");


         //****** Can't install into same path as installing from ******
         _getcwd(cPath, GLMAXPATH);
         if( (strlen(cPath) == 2) && (cPath[1] == ':') )
            strcat(cPath, "\\");
         if( stricmp(installDIR, cPath) == 0 )
            {
            }
         else
            {   
            //***************  Copy Stats.DLL **********
            _getcwd(cPath, GLMAXPATH);
            if( cPath[strlen(cPath)-1] != '\\' )
               strcat(cPath, "\\");
            strcat(cPath, "Stats.dll");   

            origobj = WinQueryObject(cPath);
            if( origobj == NULLHANDLE )
               {
               DosBeep(700, 100);
               msgOK("Error!", "Could not find Stats.dll. Installation aborted.");
               WinEnableWindow(WinWindowFromID(hwndDlg, 1000), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1001), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1002), TRUE);
               return(0);
               }

            destobj = WinQueryObject(installDIR);
            if( destobj == NULLHANDLE )
               {
               DosBeep(700, 100);
               msgOK(installDIR, "Could not find destination path. Installation aborted.");
               WinEnableWindow(WinWindowFromID(hwndDlg, 1000), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1001), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1002), TRUE);
               return(0);
               }

            if( WinCopyObject(origobj, destobj, 0) == NULLHANDLE )
               {
               DosBeep(700, 100);
               msgOK(installDIR, "Could not copy Stats.dll to destination path (File may already exist). Installation aborted.");
               WinEnableWindow(WinWindowFromID(hwndDlg, 1000), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1001), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1002), TRUE);
               return(0);
               }



            //***************  Copy STATSR.DLL **********
            _getcwd(cPath, GLMAXPATH);
            if( cPath[strlen(cPath)-1] != '\\' )
               strcat(cPath, "\\");
            strcat(cPath, "statsr.dll");   
            
            origobj = WinQueryObject(cPath);
            if( origobj == NULLHANDLE )
               {
               DosBeep(700, 100);
               msgOK("Error!", "Could not find statsr.dll. Installation aborted.");
               WinEnableWindow(WinWindowFromID(hwndDlg, 1000), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1001), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1002), TRUE);
               return(0);
               }

            destobj = WinQueryObject(installDIR);
            if( destobj == NULLHANDLE )
               {
               DosBeep(700, 100);
               msgOK(installDIR, "Could not find destination path. Installation aborted.");
               WinEnableWindow(WinWindowFromID(hwndDlg, 1000), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1001), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1002), TRUE);
               return(0);
               }

            if( WinCopyObject(origobj, destobj, 0) == NULLHANDLE )
               {
               DosBeep(700, 100);
               msgOK(installDIR, "Could not copy statsr.dll to destination path (File may already exist). Installation aborted.");
               WinEnableWindow(WinWindowFromID(hwndDlg, 1000), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1001), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1002), TRUE);
               return(0);
               }


            //***************  Copy STATINST.EXE **********
            _getcwd(cPath, GLMAXPATH);
            if( cPath[strlen(cPath)-1] != '\\' )
               strcat(cPath, "\\");
            strcat(cPath, "statinst.exe");   
            
            origobj = WinQueryObject(cPath);
            if( origobj == NULLHANDLE )
               {
               DosBeep(700, 100);
               msgOK("Error!", "Could not find statinst.exe. Installation aborted.");
               WinEnableWindow(WinWindowFromID(hwndDlg, 1000), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1001), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1002), TRUE);
               return(0);
               }

            destobj = WinQueryObject(installDIR);
            if( destobj == NULLHANDLE )
               {
               DosBeep(700, 100);
               msgOK(installDIR, "Could not find destination path. Installation aborted.");
               WinEnableWindow(WinWindowFromID(hwndDlg, 1000), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1001), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1002), TRUE);
               return(0);
               }

            if( WinCopyObject(origobj, destobj, 0) == NULLHANDLE )
               {
               DosBeep(700, 100);
               msgOK(installDIR, "Could not copy statinst.exe to destination path (File may already exist). Installation aborted.");
               WinEnableWindow(WinWindowFromID(hwndDlg, 1000), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1001), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1002), TRUE);
               return(0);
               }
            }

         addToFile(cfig, cfigTMP, installDIR, "LIBPATH=");

         if( UPDATECONFIG )
            rc = DosCopy(cfig, cfigBAKUP, DCPY_EXISTING);

         if( rc == 0 )
            {
            if( UPDATECONFIG )
               {   
               setFileAttrib(cfig, FILE_NORMAL);   
               rc = DosCopy(cfigTMP, cfig, DCPY_EXISTING);
               }
            if( rc == 0 )
               {
               
               WinRegisterObjectClass("stats", cmdDLL);
               WinReplaceObjectClass("WPFolder", "stats", TRUE);
               WinRegisterObjectClass("statsfile", cmdDLL);
               WinReplaceObjectClass("WPDataFile", "statsfile", TRUE);
               WinRegisterObjectClass("statsdisk", cmdDLL);
               WinReplaceObjectClass("WPDisk", "statsdisk", TRUE);
               
               if( UPDATECONFIG )
                  {   
                  DosDelete(cfigTMP);
                  setFileAttrib(cfigBAKUP, FILE_NORMAL);   
                  }

               PrfWriteProfileString(HINI_USERPROFILE, "StatsIsInstalled",
                			    "InstallationPath", installDIR);  
               PrfWriteProfileString(HINI_USERPROFILE, "StatsIsInstalled",
                			    "rc", rcstr);  
               if( UPDATECONFIG )
                  {		    
                  msgOK("Attention!", "Stats has been registered and installed! Reboot for it to be activated");
                  }
               else
                  {   
                  msgOK("Attention!", "Stats has been registered! Update your LIBPATH statement in config.sys and Reboot for it to be activated");
                  }
               WinEnableWindow(WinWindowFromID(hwndDlg, 1000), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1001), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1002), TRUE);
               exit(0);
               }
            else
               {
               msgOK("Error 1!", "installation failed! Could not update Config.sys properly so installation was aborted.");
               WinEnableWindow(WinWindowFromID(hwndDlg, 1000), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1001), TRUE);
               WinEnableWindow(WinWindowFromID(hwndDlg, 1002), TRUE);
               }
            }
         else
            {   
            msgOK("Error! 2", "installation failed! Could not update Config.sys properly so installation was aborted.");
            WinEnableWindow(WinWindowFromID(hwndDlg, 1000), TRUE);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1001), TRUE);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1002), TRUE);
            }
         /* ##END  */
         }
         break;
      /* Button 1001 Clicked/Selected */
      case 1001:
         {
         /* ##START 1001.0  */
         /* Event Clicked/selected - ~Uninstall  1001 */

         CHAR curPath[CCHMAXPATH]; 
         CHAR cfig[] = " :\\config.sys";
         CHAR cfigTMP[] = " :\\config.$s$";
         CHAR cfigBAKUP[] = " :\\config.sta";
         ULONG bdri;
         INT ck, mark;



         PrfQueryProfileString(HINI_USERPROFILE, 
                               "StatsIsInstalled", 
                               "InstallationPath",
         		      "", cmdhrinstall, 
         		      CCHMAXPATH);

         if( strlen(cmdhrinstall) == 0 )		      
            {
            msgOK("Attention! Stats does not seem to be installed!", "Make sure you have deleted the LIBPATH= reference for ZipZap.");
            PrfWriteProfileString(HINI_USERPROFILE, "StatsIsInstalled", NULL, NULL);
            WinReplaceObjectClass("WPFolder", "stats", FALSE);
            WinDeregisterObjectClass("stats");
            WinReplaceObjectClass("WPDataFile", "statsfile", FALSE);
            WinDeregisterObjectClass("statsfile");
            WinReplaceObjectClass("WPDisk", "statsdisk", FALSE);
            WinDeregisterObjectClass("statsdisk");
            return(0);
            }		          


         UNINSTALLME = FALSE;
         DELETELIBPATH = TRUE;
         	
         {
            USHORT usReturn;
            HWND hNewFrame;
            hNewFrame = OpenAREYOU(hwndDlg, 0);
            usReturn = (USHORT) WinProcessDlg(hNewFrame);
         }

         if( !UNINSTALLME )
            return(0);


         DosQuerySysInfo(QSV_BOOT_DRIVE, QSV_BOOT_DRIVE,
               		(PVOID)&bdri, sizeof( bdri)) ;

         cfig[0] = (CHAR)(bdri + '@');
         cfigTMP[0] = (CHAR)(bdri + '@');
         cfigBAKUP[0] = (CHAR)(bdri + '@');


         WinReplaceObjectClass("WPFolder", "stats", FALSE);
         WinDeregisterObjectClass("stats"); 
         WinReplaceObjectClass("WPDataFile", "statsfile", FALSE);
         WinDeregisterObjectClass("statsfile");
         WinReplaceObjectClass("WPDisk", "statsdisk", FALSE);
         WinDeregisterObjectClass("statsdisk");


         PrfWriteProfileString(HINI_USERPROFILE, "StatsIsInstalled", NULL, NULL);


         if( strlen(cmdhrinstall) > 3 && cmdhrinstall[strlen(cmdhrinstall)-1] == '\\')
            cmdhrinstall[strlen(cmdhrinstall)-1] = '\0'; 


         if( DELETELIBPATH )   
            { 
            if( strlen(cmdhrinstall) > 1 )
               removeFromFile(cfig, cfigTMP, cmdhrinstall, "LIBPATH=");

            rc = DosCopy(cfig, cfigBAKUP, DCPY_EXISTING);
            }
         else
            {
            rc = 0;   
            }

         if( rc == 0 )
            {
            if( DELETELIBPATH )   
               { 
               setFileAttrib(cfig, FILE_NORMAL);   
               rc = DosCopy(cfigTMP, cfig, DCPY_EXISTING);
               if( rc == 0 )
                  {
                  DosDelete(cfigTMP);
                  setFileAttrib(cfigBAKUP, FILE_NORMAL);   
                  msgOK("Attention!", "Stats has been deregistered! Reboot and delete files to complete uninstallation.");
                  exit(0);
                  }
               else
                  msgOK("Error!", "Uninstallation procedure partially or totally failed!");
               }
            else
               {
               msgOK("Attention!", "Stats has been deregistered!  You may need to Reboot to a command line to delete the files to complete uninstallation since you left the LIBPATH reference in your config.sys.");
               exit(0);
               }      
            }
         else   
            msgOK("Error!", "Uninstallation procedure partially or totally failed!");
         /* ##END  */
         }
         break;
      } /* end switch */
      break;

 /* ##START Form.38 User defined messages */
 /* ##END User defined messages */
   default :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     return WinDefDlgProc(hwndDlg,msg,mp1,mp2);
   } /* end switch for main msg dispatch */
   return (MRESULT)FALSE;
} /* end dialog procedure */
HWND OpenMain(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           MainDlgProc, 
           0, ID_MAINFORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}
MRESULT HandleMessage(HWND hwndFrame, HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  HENUM  henum;
  HWND   hwndCtl;
  HWND   hwndHScroll;
  HWND   hwndVScroll;
  LONG   lOffset;
  POINTL pointl;
  PSWP   pCtlSize;
  PSWP   pswp;
  PULONG *pWindowInfo;
  RECTL  rectl;
  SWP    swp;
  ULONG  ulCnt;
  switch (msg) {
  /* Default initialization of window */
  case WM_INITDLG:
     WinSetWindowULong(hwndDlg, QWL_USER, (ULONG) mp2);
     pWindowInfo = (PULONG *) mp2;
     if (pWindowInfo)
        *pWindowInfo=0; /* clear out size data pointer */
     if (hwndFrame == hwndDlg) {
        ULONG  ulPicture;
        HACCEL hAccel;
        WinLoadMenu(hwndFrame, 0, WinQueryWindowUShort(hwndFrame, QWS_ID));
        hAccel = WinLoadAccelTable(0,0,WinQueryWindowUShort(hwndFrame, QWS_ID));
        if (hAccel)
           WinSetAccelTable(0, hAccel, hwndFrame);
        WinQueryWindowRect(hwndDlg, &rectl);
        if (WinWindowFromID(hwndFrame, FID_MENU))
           rectl.yTop += WinQuerySysValue(HWND_DESKTOP, SV_CYMENU);
        WinQueryTaskSizePos(0, 0, &swp);
        if (swp.y+rectl.yTop>WinQuerySysValue(HWND_DESKTOP,SV_CYSCREEN)) {
           swp.y=WinQuerySysValue(HWND_DESKTOP,SV_CYSCREEN)-rectl.yTop;
        } /* endif */
        if (swp.x+rectl.xRight>WinQuerySysValue(HWND_DESKTOP,SV_CXSCREEN)) {
           swp.x=WinQuerySysValue(HWND_DESKTOP,SV_CXSCREEN)-rectl.xRight;
        } /* endif */
        WinSetWindowPos(hwndFrame,0,
           swp.x, swp.y, rectl.xRight, rectl.yTop, SWP_SIZE|SWP_MOVE);
        ulPicture=(ULONG) WinLoadPointer(HWND_DESKTOP, 0,
              WinQueryWindowUShort(hwndFrame, QWS_ID));
        if (!ulPicture)
           ulPicture=(ULONG)WinQuerySysPointer(HWND_DESKTOP,SPTR_APPICON,FALSE);
        WinSendMsg(hwndFrame, WM_SETICON, (MPARAM) ulPicture, (MPARAM) 0);
     } else {
        WinSetWindowUShort(hwndDlg, QWS_ID, FID_CLIENT);

        /* Calculate window positioning and size */
        WinQueryWindowRect(hwndDlg, &rectl);
        WinSendMsg(hwndFrame, WM_QUERYBORDERSIZE, (MPARAM)&pointl, 0);
        rectl.xLeft += pointl.x;
        rectl.xRight += pointl.x;
        rectl.yBottom += pointl.y;
        rectl.yTop += pointl.y;

        if (WinWindowFromID(hwndFrame,FID_HORZSCROLL)) {
           rectl.yBottom+=WinQuerySysValue(HWND_DESKTOP,SV_CYHSCROLL);
           rectl.yTop+=WinQuerySysValue(HWND_DESKTOP,SV_CYHSCROLL);
        }
        WinCalcFrameRect(hwndFrame, &rectl, FALSE);

        WinQueryTaskSizePos(0, 0, &swp);
        if (swp.y+rectl.yTop>WinQuerySysValue(HWND_DESKTOP,SV_CYSCREEN)) {
           swp.y=WinQuerySysValue(HWND_DESKTOP,SV_CYSCREEN)-rectl.yTop;
        } /* endif */
        if (swp.x+rectl.xRight>WinQuerySysValue(HWND_DESKTOP,SV_CXSCREEN)) {
           swp.x=WinQuerySysValue(HWND_DESKTOP,SV_CXSCREEN)-rectl.xRight;
        } /* endif */

        WinSetWindowPos(hwndFrame,0,
           swp.x, swp.y, rectl.xRight, rectl.yTop, SWP_SIZE|SWP_MOVE);

        /* Initialize information to handle sizing and scrolling windows */
        pWindowInfo = (PULONG *) mp2;
        if (pWindowInfo)
           *pWindowInfo = 0;

        /* Count number of controls */
        ulCnt=0;
        henum = WinBeginEnumWindows(hwndDlg);
        hwndCtl=WinGetNextWindow(henum);
        while (hwndCtl) {
           ulCnt++;
           hwndCtl=WinGetNextWindow(henum);
        } /* endwhile */
        WinEndEnumWindows(henum);

        pCtlSize = malloc(sizeof(SWP)*(ulCnt+2));

        /* Store client window information first */
        if (pCtlSize) {
           WinQueryWindowPos(hwndDlg, &(pCtlSize[0]));

           /* Query size information on all controls */
           ulCnt=1;
           henum = WinBeginEnumWindows(hwndDlg);
           hwndCtl=WinGetNextWindow(henum);
           while (hwndCtl) {
              if (WinQueryWindowPos(hwndCtl, &(pCtlSize[ulCnt]))) {
                 if (!pCtlSize[ulCnt].cx || !pCtlSize[ulCnt].cy)
                    pCtlSize[ulCnt].hwnd = 0;
                 else
                    ulCnt++;
              }
              hwndCtl=WinGetNextWindow(henum);
           } /* endwhile */
           WinEndEnumWindows(henum);
           pCtlSize[ulCnt].hwnd = 0;
        }
       /* Store number of controls */       pCtlSize[1].ulReserved1 = ulCnt;
        pWindowInfo = (PULONG *) mp2;
        *pWindowInfo = (PULONG) pCtlSize;

        /* If scrollable, initialize scroll bars */
        if (WinWindowFromID(hwndFrame,FID_HORZSCROLL)) {
           HandleMessage(hwndFrame, hwndDlg, WM_SIZE, 0, 0);
        }
     }
     break;
  /* Default WM_SIZE for sizeable or scrollable windows */
  case WM_SIZE:
     if (hwndFrame==hwndDlg)
        return 0;
     pWindowInfo = (PULONG *) WinQueryWindowULong(hwndDlg, QWL_USER);
     if (!pWindowInfo)
        return 0;
     pCtlSize = (PSWP) *pWindowInfo;
     if (!pCtlSize)
        return 0;
     if (!WinQueryWindowPos(hwndDlg,&swp))
        return 0;
     if (!swp.cx || !swp.cy)
        return 0;

     /* Handle sizing of scrollable window */
     hwndHScroll=WinWindowFromID(hwndFrame,FID_HORZSCROLL);
     hwndVScroll=WinWindowFromID(hwndFrame,FID_VERTSCROLL);

     if (hwndHScroll && hwndVScroll) {
        /* Get viewable size of client area */
        WinQueryWindowRect(hwndFrame, &rectl);
        WinCalcFrameRect(hwndFrame, &rectl, TRUE);

        if (pCtlSize[0].cx<=rectl.xRight) {
           pCtlSize[0].x = 0;
           WinEnableWindow(hwndHScroll,FALSE);
           WinSendMsg(hwndHScroll,SBM_SETSCROLLBAR,MPFROMSHORT(0),
                      MPFROM2SHORT(0,0));
           WinSendMsg(hwndHScroll,SBM_SETTHUMBSIZE,
                      MPFROM2SHORT(0,0),0);
        } else {
           pCtlSize[0].x = pCtlSize[0].cx-rectl.xRight+rectl.xLeft;
           pCtlSize[0].ulReserved1= 0;
           WinEnableWindow(hwndHScroll,TRUE);
           WinSendMsg(hwndHScroll,SBM_SETSCROLLBAR,
                      MPFROMSHORT(pCtlSize[0].ulReserved1),
                      MPFROM2SHORT(0,pCtlSize[0].x));
           WinSendMsg(hwndHScroll,SBM_SETTHUMBSIZE,
                      MPFROM2SHORT(rectl.xRight,pCtlSize[0].cx),0);
        } /* endif */
        if (pCtlSize[0].cy<=rectl.yTop) {
           pCtlSize[0].y = 0;
           WinEnableWindow(hwndVScroll,FALSE);
           WinSendMsg(hwndVScroll,SBM_SETSCROLLBAR,MPFROMSHORT(0),
                      MPFROM2SHORT(0,0));
           WinSendMsg(hwndVScroll,SBM_SETTHUMBSIZE,
                      MPFROM2SHORT(0,0),0);
        } else {
           pCtlSize[0].y = pCtlSize[0].cy-rectl.yTop+rectl.yBottom;
           pCtlSize[0].ulReserved2= pCtlSize[0].y;
           WinEnableWindow(hwndVScroll,TRUE);
           WinSendMsg(hwndVScroll,SBM_SETSCROLLBAR,
                      MPFROMSHORT(pCtlSize[0].ulReserved2),
                      MPFROM2SHORT(0,pCtlSize[0].y));
           WinSendMsg(hwndVScroll,SBM_SETTHUMBSIZE,
                      MPFROM2SHORT(rectl.yTop, pCtlSize[0].cy),0);
        } /* endif */
        ulCnt = 1;
        hwndCtl=pCtlSize[ulCnt].hwnd;
        while (hwndCtl) {
           WinSetWindowPos(hwndCtl, 0, pCtlSize[ulCnt].x,
              pCtlSize[ulCnt].y-pCtlSize[0].y+pCtlSize[0].ulReserved2,
              0, 0, SWP_MOVE);
           ulCnt++;
           hwndCtl=pCtlSize[ulCnt].hwnd;
        }

     }
     /* Handle sizing of a regular sizeable window */
     else {
        SWP   swpCtl;
        SWP   swpTest;
        ulCnt = 1;
        hwndCtl=pCtlSize[ulCnt].hwnd;
        while (hwndCtl) {
           swpCtl.x = (pCtlSize[ulCnt].x * swp.cx)/pCtlSize[0].cx;
           swpCtl.y = (pCtlSize[ulCnt].y * swp.cy)/pCtlSize[0].cy;
           swpCtl.cx = (pCtlSize[ulCnt].cx * swp.cx)/pCtlSize[0].cx;
           swpCtl.cy = (pCtlSize[ulCnt].cy * swp.cy)/pCtlSize[0].cy;
           WinSetWindowPos(hwndCtl, 0, swpCtl.x, swpCtl.y, swpCtl.cx, swpCtl.cy, SWP_MOVE | SWP_SIZE);

           /* If needed, adjust the control position */
           WinQueryWindowPos(hwndCtl,&swpTest);
           if (swpTest.x != swpCtl.x || swpTest.y != swpCtl.y) {
              swpCtl.x += (swpCtl.x - swpTest.x);
              swpCtl.y += (swpCtl.y - swpTest.y);
              swpCtl.cx += (swpCtl.cx - swpTest.cx);
              swpCtl.cy += (swpCtl.cy - swpTest.cy);
              WinSetWindowPos(hwndCtl, 0, swpCtl.x, swpCtl.y, swpCtl.cx, swpCtl.cy, SWP_MOVE | SWP_SIZE);
           }
           ulCnt++;
           hwndCtl=pCtlSize[ulCnt].hwnd;
        }
     }
     break;
  /* If position changed, force a WM_SIZE message  */
  case WM_WINDOWPOSCHANGED:
     if (hwndFrame!=hwndDlg) {
        pWindowInfo = (PULONG *) WinQueryWindowULong(hwndDlg, QWL_USER );
        if (!pWindowInfo)
           return 0;
        pCtlSize = (PSWP) *pWindowInfo;
        if (pCtlSize) {
           pswp = (PSWP) mp1;
           if ((pswp[0].cx != pswp[1].cx) || (pswp[0].cy != pswp[1].cy))
              WinSendMsg(hwndDlg, WM_SIZE, MPFROM2SHORT(pswp[1].cx, pswp[1].cy),
                   MPFROM2SHORT(pswp[0].cx, pswp[0].cy));
        }
     }
     break;
  /* Default handling for WM_CLOSE */
  case WM_CLOSE:
     WinDismissDlg(hwndFrame, DID_CANCEL);
     WinDestroyWindow(hwndFrame);
     break;
  case WM_HSCROLL:
     if (hwndFrame==hwndDlg)
        return 0;
     pWindowInfo = (PULONG *) WinQueryWindowULong(hwndDlg, QWL_USER);
     if (!pWindowInfo)
        return 0;
     pCtlSize = (PSWP) *pWindowInfo;
     if (!pCtlSize)
        return 0;
     hwndHScroll=WinWindowFromID(hwndFrame,FID_HORZSCROLL);
     lOffset = pCtlSize[0].ulReserved1;
     switch (SHORT2FROMMP(mp2)) {
     case SB_LINELEFT:
        lOffset--;
        break;
     case SB_LINERIGHT:
        lOffset++;
        break;
     case SB_PAGELEFT:
        WinQueryWindowRect(hwndFrame, &rectl);
        WinCalcFrameRect(hwndFrame, &rectl, TRUE);
        lOffset-=rectl.xRight;
        break;
     case SB_PAGERIGHT:
        WinQueryWindowRect(hwndFrame, &rectl);
        WinCalcFrameRect(hwndFrame, &rectl, TRUE);
        lOffset+=rectl.xRight;
        break;
     case SB_SLIDERTRACK:
     case SB_SLIDERPOSITION:
        lOffset = SHORT1FROMMP(mp2);
        break;
     } /* endswitch */

     if (lOffset < 0)
        lOffset = 0;
     if (lOffset > pCtlSize[0].x)
        lOffset = pCtlSize[0].x;
     if (lOffset > pCtlSize[0].ulReserved1) {
        ulCnt = 1;
        hwndCtl=pCtlSize[ulCnt].hwnd;
        while (hwndCtl) {
           WinSetWindowPos(hwndCtl, 0, pCtlSize[ulCnt].x-lOffset,
              pCtlSize[ulCnt].y-pCtlSize[0].y+pCtlSize[0].ulReserved2,
              0, 0, SWP_MOVE );
           ulCnt++;
           hwndCtl=pCtlSize[ulCnt].hwnd;
        }
        pCtlSize[0].ulReserved1 = lOffset;
        WinSendMsg(hwndHScroll,SBM_SETPOS, MPFROMSHORT(lOffset),0);
     } /* endif */
     else
     if (lOffset < pCtlSize[0].ulReserved1) {
        ulCnt = pCtlSize[1].ulReserved1;
        while (ulCnt >0) {
           hwndCtl=pCtlSize[ulCnt].hwnd;
           WinSetWindowPos(hwndCtl, 0, pCtlSize[ulCnt].x-lOffset,
              pCtlSize[ulCnt].y-pCtlSize[0].y+pCtlSize[0].ulReserved2,
              0, 0, SWP_MOVE);
           ulCnt--;
        }
        pCtlSize[0].ulReserved1 = lOffset;
        WinSendMsg(hwndHScroll,SBM_SETPOS, MPFROMSHORT(lOffset),0);
     } /* endif */
     break;
  case WM_VSCROLL:
     if (hwndFrame==hwndDlg)
        return 0;
     pWindowInfo = (PULONG *) WinQueryWindowULong(hwndDlg, QWL_USER);
     if (!pWindowInfo)
        return 0;
     pCtlSize = (PSWP) *pWindowInfo;
     if (!pCtlSize)
        return 0;
     hwndVScroll=WinWindowFromID(hwndFrame,FID_VERTSCROLL);
     lOffset = pCtlSize[0].ulReserved2;
     switch (SHORT2FROMMP(mp2)) {
     case SB_LINEUP:
        lOffset--;
        break;
     case SB_LINEDOWN:
        lOffset++;
        break;
     case SB_PAGEUP:
        WinQueryWindowRect(hwndFrame, &rectl);
        WinCalcFrameRect(hwndFrame, &rectl, TRUE);
        lOffset-=rectl.yTop;
        break;
     case SB_PAGEDOWN:
        WinQueryWindowRect(hwndFrame, &rectl);
        WinCalcFrameRect(hwndFrame, &rectl, TRUE);
        lOffset+=rectl.yTop;
        break;
     case SB_SLIDERTRACK:
     case SB_SLIDERPOSITION:
        lOffset = SHORT1FROMMP(mp2);  /* verified should be positive */
        break;
     } /* endswitch */

     if (lOffset < 0)
        lOffset = 0;
     if (lOffset > pCtlSize[0].y)
        lOffset = pCtlSize[0].y;
     if (lOffset < pCtlSize[0].ulReserved2) {
        ulCnt = 1;
        hwndCtl=pCtlSize[ulCnt].hwnd;
        while (hwndCtl) {
           WinSetWindowPos(hwndCtl, 0,
              pCtlSize[ulCnt].x-pCtlSize[0].ulReserved1,
              pCtlSize[ulCnt].y-pCtlSize[0].y+lOffset, 0, 0, SWP_MOVE);
           ulCnt++;
           hwndCtl=pCtlSize[ulCnt].hwnd;
        }
        pCtlSize[0].ulReserved2 = lOffset;
        WinSendMsg(hwndVScroll,SBM_SETPOS, MPFROMSHORT(lOffset),0);
     } /* endif */
    else
    if (lOffset > pCtlSize[0].ulReserved2) {
       ulCnt = pCtlSize[1].ulReserved1;
       while (ulCnt > 0) {
          hwndCtl=pCtlSize[ulCnt].hwnd;
          WinSetWindowPos(hwndCtl, 0,
             pCtlSize[ulCnt].x-pCtlSize[0].ulReserved1,
             pCtlSize[ulCnt].y-pCtlSize[0].y+lOffset, 0, 0, SWP_MOVE);
          ulCnt--;
       }
       pCtlSize[0].ulReserved2 = lOffset;
       WinSendMsg(hwndVScroll,SBM_SETPOS, MPFROMSHORT(lOffset),0);
    } /* endif */
     break;
  /* When window is destroyed, deallocate window memory */
  case WM_DESTROY:
     pWindowInfo = (PULONG *) WinQueryWindowULong(hwndDlg, QWL_USER);
     if (pWindowInfo) {
        pCtlSize = (PSWP) *pWindowInfo;
        if (pCtlSize)
           free(pCtlSize);
        free(pWindowInfo);
        WinSetWindowULong(hwndDlg, QWL_USER, 0L);
     }
     break;
  }
  return (MRESULT) FALSE;
}

/***************************************************************/
/* MLEGetItemText                                              */
/*                                                             */
/* Description:                                                */
/*                                                             */
/* This helper function is used easily retrieve all or part    */
/* of the text within an MLE.  There is no limit on the amount */
/* of text to be retrieved.                                    */
/*                                                             */
/* Parameters:                                                 */
/*                                                             */
/*    hwndDlg      - handle to window containing the MLE       */
/*    ulID         - MLE identifier                            */
/*    lIptPosition - Starting IPT position to get value        */
/*                   Use 0 to start at the beginning           */
/*                   Use -1 to start at the cursor position    */
/*    lBoundary    - Number of characters to get               */
/*                   Used -1 to get characters until the end   */
/*    ppText       - Pointer to receive a pointer to text area */
/***************************************************************/
ULONG MLEGetItemText(HWND hwndDlg, ULONG ulID, LONG lIptPosition,
      LONG lBoundary, PBYTE *ppText)
{
  ULONG ulTextSize;
  PBYTE pText=0;
  HWND  hwndControl = WinWindowFromID(hwndDlg, ulID);

  /* Get text length */
  ulTextSize = (LONG)WinSendMsg(hwndControl,MLM_QUERYFORMATTEXTLENGTH,MPFROMLONG(lIptPosition),MPFROMLONG(lBoundary));
  if (ulTextSize>0) {
     PBYTE pMLEBuff=0;
     ULONG ulBuffSize;
     pText = malloc(ulTextSize);

     /* Allocate MLE transfer buffer. MLE limited to 64K tiled memory */
     ulBuffSize = 65535;
     if (pText && !DosAllocMem((PPVOID) &pMLEBuff, (ULONG) ulBuffSize,
                PAG_COMMIT | PAG_READ | PAG_WRITE | OBJ_TILE)) {
        ULONG ulBytesCopied=0;
        ULONG ulBytesToCopy;
        ULONG ulTransfer;

        /* Set import/export MLE buffer */
        WinSendMsg(hwndControl, MLM_SETIMPORTEXPORT,
           MPFROMP(pMLEBuff), MPFROMLONG( ulBuffSize));

        do {
           if (ulBuffSize < ulTextSize-ulBytesCopied)
              ulBytesToCopy=ulBuffSize;
           else
              ulBytesToCopy=ulTextSize-ulBytesCopied;

           /* Get text at given IPT */
           ulTransfer = (ULONG) WinSendMsg(hwndControl,
                    MLM_EXPORT,
                    MPFROMLONG(&lIptPosition), MPFROMLONG(&ulBytesToCopy));

           if (!ulTransfer)
              ulBytesCopied=ulTextSize;
           else {
              memcpy((PVOID)&(pText[ulBytesCopied]),
                     (PVOID)pMLEBuff, ulTransfer);
              ulBytesCopied+=ulTransfer;
           }
        } while (ulBytesCopied < ulTextSize);

        /* Free MLE transfer buffer */
        DosFreeMem((PBYTE)pMLEBuff);
     }
  }
  pText[ulTextSize]=0;
  *ppText = pText;
  return ulTextSize;
}

/***************************************************************/
/* MLEInsertText                                               */
/*                                                             */
/* Description:                                                */
/*                                                             */
/* This helper function is used easily insert text within the  */
/* MLE.  There is no limit on the amount of text to be inserted*/
/*                                                             */
/* Parameters:                                                 */
/*                                                             */
/*    hwndDlg      - handle to window containing the MLE       */
/*    ulID         - MLE identifier                            */
/*    lIptPosition - IPT to insert text                        */
/*                   Use 0 to start at the beginning           */
/*                   Use -1 to start at the cursor position    */
/*    pText        - Pointer to text area                      */
/***************************************************************/
ULONG MLEInsertText(HWND hwndDlg, ULONG ulID, LONG iptPosition, PBYTE pText)
{
  PBYTE pMLEBuff=0;
  ULONG ulBuffSize;
  ULONG ulBytesCopied=0;
  HWND  hwndControl = WinWindowFromID(hwndDlg, ulID);

  /* Allocate MLE transfer buffer. MLE limited to 64K tiled memory */
  ulBuffSize = 65535;
  if (!DosAllocMem((PPVOID) &pMLEBuff, (ULONG) ulBuffSize,
             PAG_COMMIT | PAG_READ | PAG_WRITE | OBJ_TILE)) {
     ULONG ulBytesToCopy;
     ULONG ulTextSize = strlen((char *)pText);

     /* Set import/export MLE buffer */
     WinSendMsg(hwndControl, MLM_SETIMPORTEXPORT,
           MPFROMP(pMLEBuff), MPFROMLONG( ulBuffSize));
     do {
        if (ulBuffSize < ulTextSize-ulBytesCopied)
           ulBytesToCopy=ulBuffSize;
        else
           ulBytesToCopy=ulTextSize-ulBytesCopied;
        memcpy((PVOID) pMLEBuff, &(pText[ulBytesCopied]),
                     ulBytesToCopy);

        /* Insert text at given IPT */
        WinSendMsg(hwndControl, MLM_IMPORT,
                 (MPARAM) &iptPosition, (MPARAM) ulBytesToCopy);
        ulBytesCopied+=ulBytesToCopy;
     } while (ulBytesCopied < ulTextSize);

     /* Free MLE transfer buffer */
     DosFreeMem((PBYTE)pMLEBuff);
  }
  return ulBytesCopied;
}
