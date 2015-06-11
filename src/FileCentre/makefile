#目录
QTDIR = E:\Qt\Qt5.4.0\5.4\msvc2010_opengl
OUTDIR = ..\..\out

#预处理定义
DEFINES = -DUNICODE -DWIN32 -DWIN64 -DQT_DLL -DQT_NO_DEBUG -DNDEBUG -DQT_CORE_LIB -DFILECENTRE_LIB 
#nolog取消显示版权标志,o2速度最大化，EHsc启用c++异常,Zc:wchar_t视为内置类型，GR运行时内置信息
CXXFLAGS      = -nologo -Zm200 -Zc:wchar_t -O2 -MD -GR -W3 -w34100 -w34189 -EHsc $(DEFINES)
INCPATH = -I".\GeneratedFiles" -I".\GeneratedFiles\Release" -I"." -I"E:\Qt\Qt5.4.0\5.4\msvc2010_opengl\include" -I"E:\Qt\Qt5.4.0\5.4\msvc2010_opengl\include\QtCore"
#lib参数和lib,DYNAMICBASE随机基址，NXCOMPAT数据执行保护
LFLAGS        = /NOLOGO /DYNAMICBASE /NXCOMPAT /INCREMENTAL:NO /DLL /SUBSYSTEM:WINDOWS
LIBS          = /LIBPATH:$(QTDIR)\lib Qt5Core.lib 



all:$(OUTDIR)\FileCentre.dll
$(OUTDIR):
	if not exist "$(OUTDIR)" mkdir $(OUTDIR)

$(OUTDIR)\FileCentre.dll:$(OUTDIR)\FileCentre.obj
	link $(LFLAGS) $(LIBS) /dll $(OUTDIR)\FileCentre.obj /out:$(OUTDIR)\FileCentre.dll
$(OUTDIR)\FileCentre.obj:FileCentre.h
	cl /c $(CXXFLAGS) $(INCPATH) /Fo$(OUTDIR)\ FileCentre.cpp

clean:
	if exist $(OUTDIR) del $(OUTDIR)\*.obj
	if exist $(OUTDIR) del $(OUTDIR)\*.exp

