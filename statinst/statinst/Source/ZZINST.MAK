# PROGRAM - Makefile (ZZINST.MAK) 
#
#       Makefile variables from Build Options 
#
CFLAGS=/c /O /Gm /Ss /W3 /Tl- -I. -I..\SUBPROCS -IG:\VISPROC
LFLAGS=/ST:32768 /A:16 /NOI /NOE /NOD
L_ADDITIONAL_LIBS=OS2386.LIB DDE4MBS.LIB 
L_ADDITIONAL_OBJS=
COMPILER=ICC
LINKER=LINK386
#
#       Additional definitions 
#
SUBPROCS=..\\SUBPROCS\\
EXCL=!
OBJECTS= \
          AREYOU.OBJ \
          Main.OBJ \
          NEWCFG.OBJ \
          NPATH.OBJ \
          cmdhxtra.OBJ 

ALL: ..\ZZINST.EXE 
#
#       Statements to compile the classes
#
AREYOU.OBJ:  AREYOU.C AREYOU.H AREYOU.RCH  MAIN.H 
    $(COMPILER) $(CFLAGS) AREYOU.C
Main.OBJ:  Main.C Main.H Main.RCH  MAIN.H 
    $(COMPILER) $(CFLAGS) Main.C
NEWCFG.OBJ:  NEWCFG.C NEWCFG.H NEWCFG.RCH  MAIN.H 
    $(COMPILER) $(CFLAGS) NEWCFG.C
NPATH.OBJ:  NPATH.C NPATH.H NPATH.RCH  MAIN.H 
    $(COMPILER) $(CFLAGS) NPATH.C
cmdhxtra.OBJ:  $(SUBPROCS)cmdhxtra.c 
    $(COMPILER) $(CFLAGS) $(SUBPROCS)cmdhxtra.c
#
#       Statements to compile resources for the classes
#
ZZINST.RES:  ZZINST.RC \
               AREYOU.RCH AREYOU.RC \
               Main.RCH Main.RC \
               NEWCFG.RCH NEWCFG.RC \
               NPATH.RCH NPATH.RC 
    RC -r ZZINST.RC
#
#       Statements to link the EXE file
#
..\ZZINST.EXE:  $(OBJECTS) ZZINST.DEF ZZINST.RES ZZINST.MAK 
    $(LINKER) @<<
           $(LFLAGS) $(L_ADDITIONAL_OBJS)  +
          AREYOU.OBJ  +
          Main.OBJ  +
          NEWCFG.OBJ  +
          NPATH.OBJ +
          cmdhxtra.OBJ ,
          ..\ZZINST.EXE,, $(L_ADDITIONAL_LIBS), ZZINST.DEF 
<<
    RC ZZINST.RES ..\ZZINST.EXE
