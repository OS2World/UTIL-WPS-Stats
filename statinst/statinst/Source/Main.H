/******************************************************************************/
/*                                                                            */
/* Program: STATINST.EXE                                                      */
/*                                                                            */
/* Description: Description                                                   */
/*                                                                            */
/* File Name : Main.H                                                         */
/*                                                                            */
/* Author : GARY L. ROBINSON                                                  */
/*                                                                            */
/* Copyright 1997 Copyright notice                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5013754                          */
/*                                                                            */
/******************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

 /* ##START Form.39 Form header definitions */
 /* ##END Form header definitions */
/* Helper routines */
MRESULT HandleMessage(HWND hwndFrame, HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2);
ULONG MLEGetItemText(HWND hwndDlg, ULONG ulID, LONG lIptPosition,
      LONG lBoundary, PBYTE *ppText);
ULONG MLEInsertText(HWND hwndDlg, ULONG ulID, LONG iptPosition, PBYTE pText);
HWND OpenMain(HWND hwndOwner, PVOID pInfo);

typedef struct _MAINFORMINFO {
   PSWP pControlSize;   /* Used to handle control sizing */
   /* ##START Form.33 Window structure members */
   /* ##END Window structure members */
} MAINFORMINFO;
typedef MAINFORMINFO * PMAINFORMINFO;
#define ID_FORMTIMER 100   /* Used for timer events */
#endif