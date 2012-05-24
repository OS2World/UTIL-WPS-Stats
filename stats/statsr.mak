# statsr.mak
# Created by IBM WorkFrame/2 MakeMake at 4:41:21 on 22 Aug 1997
#
# The actions included in this make file are:
#  Compile::C++ Compiler
#  Link::Linker
#  Bind::Resource Bind
#  Compile::Resource Compiler

.SUFFIXES: .C .RC .obj .res 

.all: \
    .\statsr.dll

.C.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /Ti /Ge- /C %s

{H:\stats}.C.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /Ti /Ge- /C %s

.RC.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r %s %|dpfF.RES

{H:\stats}.RC.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r %s %|dpfF.RES

.\statsr.dll: \
    .\MYOBJRES.obj \
    .\MYOBJRES.res \
    {$(LIB)}statsr.def \
    statsr.mak
    @echo " Link::Linker "
    @echo " Bind::Resource Bind "
    icc.exe @<<
     /B" /de /st:524288"
     /Festatsr.dll 
     statsr.def
     .\MYOBJRES.obj
<<
    rc.exe .\MYOBJRES.res statsr.dll

.\MYOBJRES.obj: \
    H:\stats\MYOBJRES.C \
    statsr.mak

.\MYOBJRES.res: \
    H:\stats\MYOBJRES.RC \
    {H:\stats;$(INCLUDE)}stats.ih \
    statsr.mak
