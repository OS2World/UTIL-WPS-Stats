# stats.mak
# Created by IBM WorkFrame/2 MakeMake at 5:44:26 on 30 Aug 1997
#
# The actions included in this make file are:
#  Compile::SOM Compiler
#  Compile::C++ Compiler
#  Link::Linker

.SUFFIXES:

.SUFFIXES: \
    .IDL .c .obj 

.IDL.c:
    @echo " Compile::SOM Compiler "
    sc.exe -p -S65536 -C65536 -mnoint %s

{H:\stats\WPSDLL}.IDL.c:
    @echo " Compile::SOM Compiler "
    sc.exe -p -S65536 -C65536 -mnoint %s

.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /Ss /Gm /Ge- /Ms /C %s

{H:\stats\WPSDLL}.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /Ss /Gm /Ge- /Ms /C %s

all: \
    .\stats.dll

.\stats.dll: \
    .\STATS.obj \
    {$(LIB)}somtk.lib \
    {$(LIB)}stats.def \
    stats.mak
    @echo " Link::Linker "
    icc.exe @<<
     /B" /st:65536 /noe"
     /Festats.dll 
     somtk.lib 
     stats.def
     .\STATS.obj
<<

.\STATS.c: \
    H:\stats\WPSDLL\STATS.IDL \
    stats.mak

.\STATS.obj: \
    .\STATS.c \
    stats.mak
