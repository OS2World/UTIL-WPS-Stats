/******************************************************************************/
/*                                                                            */
/* Program: STATINST.EXE                                                      */
/*                                                                            */
/* Description: Description                                                   */
/*                                                                            */
/* File Name : NPATH.C                                                        */
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
#include "NPATH.H"
#include "NPATH.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */

#include "global.h"
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY NPATHDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  HWND hwndFrame = hwndDlg;
 /* ##START Form.37 Top of window procedure */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      {
      /* ##START Form.1  */
      /* Form events - Opened */


      {
      SWP swp, swpD;
      int dtWidth;
      int offX, offY;
      dtWidth = WinQuerySysValue(HWND_DESKTOP,SV_CXSCREEN);
      offX = 20;
      offY = 10;
      WinQueryWindowPos(WinQueryWindow(hwndDlg, QW_OWNER), (PSWP) &swp);
      WinQueryWindowPos(hwndDlg, (PSWP) &swpD);
      if( swp.x < 5 )
         swp.x += ((-swp.x) + 1); 
      if( (swp.x+offX+swpD.cx) > (dtWidth-5) )
         {
         int over;
         over = (swp.x+offX+swpD.cx) - (dtWidth-5);
         offX = - (offX+over);   
         }
      if( (swp.y-70) < 5 )
         offY = - offY; 
      WinSetWindowPos(hwndDlg, HWND_TOP, 
                      swp.x+offX, swp.y-offY, 0, 0,
      		SWP_ACTIVATE | SWP_MOVE | SWP_SHOW );
      }
      /* ##END  */
      }
      break;

   /* Form event Closed WM_CLOSE */
   case WM_CLOSE :
      {
      /* ##START Form.2  */
      /* Form events - Closed */
      /* ##END  */
      }
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      break;

   /* Form event Destroyed WM_DESTROY */
   case WM_DESTROY :
      {
      /* ##START Form.3  */
      /* Form events - Destroyed */


      PATHRet = 0;
      /* ##END  */
      }
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      break;

   case WM_COMMAND :
      switch (SHORT1FROMMP(mp1)) {
      /* Button 1001 Clicked/Selected */
      case 1001:
         {
         /* ##START 1001.0  */
         /* Event Clicked/selected - C~ontinue  1001 */

         createFolders(installDIR);
         /* DosCreateDir(installDIR, pbuf);*/
         PATHRet = 1;
         WinDismissDlg( hwndDlg, TRUE );
         /* ##END  */
         }
         break;
      /* Button 1002 Clicked/Selected */
      case 1002:
         {
         /* ##START 1002.0  */
         /* Event Clicked/selected - ~Cancel  1002 */

         PATHRet = 0;
         WinDismissDlg( hwndDlg, TRUE );
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
HWND OpenNPATH(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           NPATHDlgProc, 
           0, ID_NPATHFORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}
