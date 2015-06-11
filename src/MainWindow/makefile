#目录
QTDIR = E:\Qt\Qt5.4.0\5.4\msvc2010_opengl
MOCPATH = $(QTDIR)\bin\moc.exe	
UICPATH = $(QTDIR)\bin\uic.exe
GF = GeneratedFiles
OUTDIR = ..\..\out

#参数
DEFINES = -DUNICODE -DWIN32 -DWIN64 -DQT_DLL -DQT_NO_DEBUG -DNDEBUG -DQT_CORE_LIB -DQT_GUI_LIB -DQT_WIDGETS_LIB -DMAINWINDOW_LIB
CXXFLAGS      = -nologo -Zm200 -Zc:wchar_t -O2 -MD -GR -W3 -w34100 -w34189 -EHsc $(DEFINES)
INCPATH = -I".\GeneratedFiles" -I".\GeneratedFiles\Release" -I"$(QTDIR)\include" -I"$(QTDIR)\include\QtCore" -I"$(QTDIR)\include\QtWidgets" -I"$(QTDIR)\include\QtGui" -I"..\..\include"
LFLAGS        = /NOLOGO /DYNAMICBASE /NXCOMPAT /INCREMENTAL:NO /SUBSYSTEM:WINDOWS 
LIBS = /LIBPATH:$(QTDIR)\lib qtmain.lib shell32.lib Qt5Core.lib Qt5Gui.lib Qt5Widgets.lib /LIBPATH:$(OUTDIR) FileCentre.lib ReportWidget.lib CameraWidget.lib RecordWidget.lib MyLabel.lib ImageWidget.lib


INCLUDES = $(GF)\ui_mainwidget.h MainWidget.h $(GF)\ui_mainwindow.h MainWindow.h
SOURCES = $(GF)\Release\moc_MainWidget.cpp MainWidget.cpp $(GF)\Release\moc_MainWindow.cpp MainWindow.cpp main.cpp

MainWindow.exe:MainWindow.obj
	link $(LFLAGS) /out:$(OUTDIR)\MainWindow.exe $(OUTDIR)\*.obj $(LIBS)
MainWindow.obj:$(GF)\Release moc_MainWidget.cpp moc_MainWindow.cpp $(INCLUDES)
	cl /c $(CXXFLAGS) $(INCPATH) /Fo$(OUTDIR)\ $(SOURCES)

$(GF)\Release:
	if not exist "$(GF)\Release" mkdir $(GF)\Release
#moc文件
moc_MainWidget.cpp:MainWidget.h
	$(MOCPATH) $(DEFINES) $(INCPATH) MainWidget.h -o $(GF)\Release\moc_MainWidget.cpp
moc_MainWindow.cpp:MainWindow.h
	$(MOCPATH) $(DEFINES) $(INCPATH) MainWindow.h -o $(GF)\Release\moc_MainWindow.cpp
#ui_文件
$(GF)\ui_mainwidget.h:mainwidget.ui
	$(UICPATH) mainwidget.ui -o $(GF)\ui_mainwidget.h
$(GF)\ui_mainwindow.h:mainwidget.ui
	$(UICPATH) mainwindow.ui -o $(GF)\ui_mainwindow.h

clean:
	if exist $(OUTDIR) del $(OUTDIR)\*.obj
	if exist $(OUTDIR) del $(OUTDIR)\*.exp

