#目录
QTDIR= E:\Qt\Qt5.4.0\5.4\msvc2010_opengl
OUTDIR = ..\..\out

#参数
DEFINES = -DUNICODE -DWIN32 -DWIN64 -DQT_DLL -DQT_NO_DEBUG -DNDEBUG -DQT_CORE_LIB -DQT_GUI_LIB -DQT_WIDGETS_LIB -DMYLABEL_LIB
CXXFLAGS      = -nologo -Zm200 -Zc:wchar_t -O2 -MD -GR -W3 -w34100 -w34189 -EHsc $(DEFINES)
INCPATH = -I".\GeneratedFiles" -I".\GeneratedFiles\Release" -I"." -I"$(QTDIR)\include" -I"$(QTDIR)\include\QtCore" -I"$(QTDIR)\include\QtGui" -I"$(QTDIR)\include\QtWidgets" -I"..\..\include"
LFLAGS        = /NOLOGO /DYNAMICBASE /NXCOMPAT /INCREMENTAL:NO /SUBSYSTEM:WINDOWS
LIBS          = /LIBPATH:$(QTDIR)\lib qtmain.lib Qt5Core.lib Qt5Gui.lib Qt5Widgets.lib /LIBPATH:$(OUTDIR) ReportWidget.lib ImageWidget.lib
	
#项目文件
INCLUDES = MyLabel.h WidgetFactory.h 
SOURCES = MyLabel.cpp WidgetFactory.cpp

MyLabel.dll:MyLabel.obj
	link $(LFLAGS) /dll $(OUTDIR)\*.obj $(LIBS) /out:$(OUTDIR)\MyLabel.dll
MyLabel.obj:$(INCLUDES)
	cl /c /Fo$(OUTDIR)\ $(CXXFLAGS) $(INCPATH) $(SOURCES)

clean:
	if exist $(OUTDIR) del $(OUTDIR)\*.obj
	if exist $(OUTDIR) del $(OUTDIR)\*.exp

