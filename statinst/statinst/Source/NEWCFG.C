/******************************************************************************/
/*                                                                            */
/* Program: STATINST.EXE                                                      */
/*                                                                            */
/* Description: Description                                                   */
/*                                                                            */
/* File Name : NEWCFG.C                                                       */
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
#include "NEWCFG.H"
#include "NEWCFG.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */


#include "global.h"
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY NEWCFGDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  HWND hwndFrame = hwndDlg;
 /* ##START Form.37 Top of window procedure */
 /* Code sections - Top of window procedure */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      {
      /* ##START Form.1  */
      /* Form events - Opened */

      {
      INT x_screen, y_screen, x_offset, y_offset;
      POINTL pt;
      SWP swp;
      WinQueryWindowPos( hwndDlg, &swp );     
      WinQueryPointerPos( HWND_DESKTOP, &pt ); 
      swp.x = pt.x - (swp.cx /2);             
      swp.y = pt.y - (swp.cy /2);
      x_screen = WinQuerySysValue( HWND_DESKTOP, SV_CXSCREEN );
      y_screen = WinQuerySysValue( HWND_DESKTOP, SV_CYSCREEN );
      x_offset = x_screen*.005;
      y_offset = y_screen*.005;
      if ( swp.cx + swp.x  > x_screen )  
          swp.x = x_screen - (swp.cx + x_offset);
      if ( swp.x <= 0 )                            
          swp.x = x_offset;
      if ( swp.y + swp.cy > y_screen )   
          swp.y = y_screen - (swp.cy + y_offset);
      if ( swp.y <= 0 )                            
          swp.y = y_offset;
      WinSetWindowPos(hwndDlg, HWND_TOP, 
                      swp.x, swp.y, 0, 0,
      		SWP_ACTIVATE | SWP_MOVE | SWP_SHOW );
      }
      /* ##END  */
      }
      break;

   /* Form event Closed WM_CLOSE */
   case WM_CLOSE :
      /* ##START Form.2  */
      /* ##END  */
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      break;

   case WM_COMMAND :
      switch (SHORT1FROMMP(mp1)) {
      /* Button 2001 Clicked/Selected */
      case 2001:
         {
         /* ##START 2001.0  */
         /* Event Clicked/selected - Update  2001 */

         UPDATECONFIG = TRUE;
         ISCANCELLED = FALSE;
         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      /* Button 2002 Clicked/Selected */
      case 2002:
         {
         /* ##START 2002.0  */
         /* Event Clicked/selected - ~Cancel  2002 */


         ISCANCELLED = TRUE;
         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      /* Button 2004 Clicked/Selected */
      case 2004:
         {
         /* ##START 2004.0  */
         /* Event Clicked/selected - Do not Update  2004 */

         ISCANCELLED = FALSE;
         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
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
HWND OpenNEWCFG(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           NEWCFGDlgProc, 
           0, ID_NEWCFGFORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}
