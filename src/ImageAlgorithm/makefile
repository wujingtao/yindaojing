#目录
QTDIR = E:\Qt\Qt5.4.0\5.4\msvc2010_opengl
OUTDIR = ..\..\out

DEFINES = -DUNICODE -DWIN32 -DWIN64 -DQT_DLL -DQT_NO_DEBUG -DNDEBUG -DQT_CORE_LIB -DIMAGEALGORITHM_LIB
CXXFLAGS      = -nologo -Zm200 -Zc:wchar_t -O2 -MD -GR -W3 -w34100 -w34189 -EHsc $(DEFINES)
INCPATH = -I".\GeneratedFiles" -I".\GeneratedFiles\Release" -I"$(QTDIR)\include" -I"$(QTDIR)\include\QtCore" -I"."
LFLAGS        = /NOLOGO /DYNAMICBASE /NXCOMPAT /INCREMENTAL:NO /SUBSYSTEM:WINDOWS 
LIBS = /LIBPATH:$(QTDIR)\lib qtmain.lib Qt5Core.lib
	
#项目文件
INCLUDES = MyListRGB.h FusionThread.h FusionSThread.h FusionAlg.h
SOURCES = MyListRGB.cpp FusionThread.cpp FusionSThread.cpp FusionAlg.cpp

#编译
ImageAlgorithm.dll:ImageAlgorithm.obj
	link $(LFLAGS) $(OUTDIR)\*.obj $(LIBS) /dll /out:$(OUTDIR)\ImageAlgorithm.dll
ImageAlgorithm.obj:$(INCLUDES)
	cl /c $(CXXFLAGS) $(INCPATH) /Fo$(OUTDIR)\ $(SOURCES)

clean:
	if exist $(OUTDIR) del $(OUTDIR)\*.obj
	if exist $(OUTDIR) del $(OUTDIR)\*.exp

