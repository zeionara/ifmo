PROJ = firstapp
PROJFILE = pwb.mak
DEBUG = 0

PWBRMAKE  = pwbrmake
NMAKEBSC1  = set
NMAKEBSC2  = nmake
ASM  = ml
AFLAGS_G  = /Cx /W2 /WX
AFLAGS_D  = /Zi
AFLAGS_R  = /nologo
MAPFILE_D  = NUL
MAPFILE_R  = NUL
LFLAGS_G  = /NOI /BATCH
LFLAGS_D  = /CO /FAR /PACKC
LFLAGS_R  = /EXE /FAR /PACKC
LINKER	= link
ILINK  = ilink
LRF  = echo > NUL

OBJS  = .\firstapp.obj
SBRS  = .\firstapp.sbr

all: .\$(PROJ).exe

.SUFFIXES:
.SUFFIXES: .sbr .obj .asm

.\firstapp.obj : firstapp.asm
!IF $(DEBUG)
	$(ASM) /c $(AFLAGS_G) $(AFLAGS_D) /Fo.\firstapp.obj firstapp.asm
!ELSE
	$(ASM) /c $(AFLAGS_G) $(AFLAGS_R) /Fo.\firstapp.obj firstapp.asm
!ENDIF

.\firstapp.sbr : firstapp.asm
!IF $(DEBUG)
	$(ASM) /Zs $(AFLAGS_G) $(AFLAGS_D) /FR.\firstapp.sbr firstapp.asm
!ELSE
	$(ASM) /Zs $(AFLAGS_G) $(AFLAGS_R) /FR.\firstapp.sbr firstapp.asm
!ENDIF


.\$(PROJ).bsc : $(SBRS)
	$(PWBRMAKE) @<<
$(BRFLAGS) $(SBRS)
<<

.\$(PROJ).exe : $(OBJS)
!IF $(DEBUG)
	$(LRF) @<<.\$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_D)
$(LLIBS_G: = +^
) +
$(LLIBS_D: = +^
) +
$(LIBS: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_D);
<<
!ELSE
	$(LRF) @<<.\$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_R)
$(LLIBS_G: = +^
) +
$(LLIBS_R: = +^
) +
$(LIBS: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_R);
<<
!ENDIF
	$(LINKER) @.\$(PROJ).lrf


.asm.sbr :
!IF $(DEBUG)
	$(ASM) /Zs $(AFLAGS_G) $(AFLAGS_D) /FR$@ $<
!ELSE
	$(ASM) /Zs $(AFLAGS_G) $(AFLAGS_R) /FR$@ $<
!ENDIF

.asm.obj :
!IF $(DEBUG)
	$(ASM) /c $(AFLAGS_G) $(AFLAGS_D) /Fo$@ $<
!ELSE
	$(ASM) /c $(AFLAGS_G) $(AFLAGS_R) /Fo$@ $<
!ENDIF


run: .\$(PROJ).exe
	.\$(PROJ).exe $(RUNFLAGS)

debug: .\$(PROJ).exe
	CV $(CVFLAGS) .\$(PROJ).exe $(RUNFLAGS)
