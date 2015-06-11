#目录
QTDIR = E:\Qt\Qt5.4.0\5.4\msvc2010_opengl
MOCPATH = $(QTDIR)\bin\moc.exe	
UICPATH = $(QTDIR)\bin\uic.exe
GF = GeneratedFiles
OUTDIR= ..\..\out

DEFINES = -DUNICODE -DWIN32 -DWIN64 -DQT_DLL -DQT_NO_DEBUG -DNDEBUG -DQT_CORE_LIB -DQT_WIDGETS_LIB -DRECORDWIDGET_LIB
CXXFLAGS      = -nologo -Zm200 -Zc:wchar_t -O2 -MD -GR -W3 -w34100 -w34189 -EHsc $(DEFINES)
INCPATH       = -I"$(QTDIR)\include" -I"$(QTDIR)\include\QtWidgets" -I"$(QTDIR)\include\QtGui" -I"$(QTDIR)\include\QtCore" -I"$(QTDIR)\mkspecs\win32-msvc2010" -I"..\..\include" -I"GeneratedFiles" -I"."
LFLAGS        = /NOLOGO /DYNAMICBASE /NXCOMPAT /INCREMENTAL:NO /SUBSYSTEM:WINDOWS
LIBS          = /LIBPATH:$(QTDIR)\lib qtmain.lib Qt5Core.lib Qt5Gui.lib Qt5Widgets.lib /LIBPATH:$(OUTDIR) FileCentre.lib

#项目文件
SOURCES = $(GF)\Release\moc_RecordWidget.cpp RecordWidget.cpp RecordFactory.cpp
INCLUDES = $(GF)\ui_recordwidget.h RecordWidget.h RecordFactory.h

RecordWidget.dll:RecordWidget.obj
	link $(LFLAGS) /dll $(OUTDIR)\*.obj $(LIBS) /out:$(OUTDIR)\RecordWidget.dll
RecordWidget.obj: $(GF)\Release moc_RecordWidget.cpp $(INCLUDES)
	cl /c /Fo$(OUTDIR)\ $(CXXFLAGS) $(INCPATH) $(SOURCES) 

$(GF)\Release:
	if not exist "$(GF)\Release" mkdir $(GF)\Release
moc_RecordWidget.cpp:RecordWidget.h
	$(MOCPATH) RecordWidget.h -o $(GF)\Release\moc_RecordWidget.cpp
$(GF)\ui_recordwidget.h:recordwidget.ui
	$(UICPATH) recordwidget.ui -o $(GF)\ui_recordwidget.h

clean:
	if exist $(OUTDIR) del $(OUTDIR)\*.obj
	if exist $(OUTDIR) del $(OUTDIR)\*.exp

