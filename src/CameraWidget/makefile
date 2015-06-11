#目录
QTDIR = E:\Qt\Qt5.4.0\5.4\msvc2010_opengl
MOCPATH = $(QTDIR)\bin\moc.exe	
UICPATH = $(QTDIR)\bin\uic.exe
GF = GeneratedFiles
OUTDIR = ..\..\out

#参数
DEFINES = -DUNICODE -DWIN32 -DWIN64 -DQT_DLL -DQT_NO_DEBUG -DNDEBUG -DQT_CORE_LIB -DCAMERAWIDGET_LIB
CXXFLAGS      = -nologo -Zm200 -Zc:wchar_t -O2 -MD -GR -W3 -w34100 -w34189 -EHsc $(DEFINES)
INCPATH = -I".\GeneratedFiles" -I".\GeneratedFiles\Release" -I"$(QTDIR)\include" -I"$(QTDIR)\include\QtCore" -I"$(QTDIR)\include\QtWidgets" -I"$(QTDIR)\include\QtGui" -I"..\..\include" -I"..\..\include\flycapture"
LFLAGS        = /NOLOGO /DYNAMICBASE /NXCOMPAT /INCREMENTAL:NO /SUBSYSTEM:WINDOWS 
LIBS = /LIBPATH:$(OUTDIR) FileCentre.lib ImageAlgorithm.lib /LIBPATH:$(QTDIR)\lib qtmain.lib Qt5Core.lib Qt5Widgets.lib Qt5Gui.lib Qt5SerialPort.lib /LIBPATH:..\..\lib\flycapture FlyCapture2_v100.lib

#项目文件
INCLUDES = $(GF)\ui_view.h ViewWidget.h RWBmp.h ShowThread.h ImageThread.h FlyCapture.h $(GF)\ui_camerawidget.h CameraWidget.h CameraFactory.h
SOURCES = ViewWidget.cpp RWBmp.cpp $(GF)\Release\moc_ShowThread.cpp ShowThread.cpp ImageThread.cpp FlyCapture.cpp $(GF)\Release\moc_CameraWidget.cpp CameraWidget.cpp CameraFactory.cpp 

CameraWidget.dll:CameraWidget.obj
	link $(LFLAGS) $(OUTDIR)\*.obj $(LIBS) /dll /out:$(OUTDIR)\CameraWidget.dll
CameraWidget.obj: $(GF)\Release moc_ShowThread.cpp moc_CameraWidget.cpp $(INCLUDES)
	cl /c $(CXXFLAGS) $(INCPATH) /Fo$(OUTDIR)\ $(SOURCES)

$(GF)\Release:
	if not exist "$(GF)\Release" mkdir $(GF)\Release
moc_ShowThread.cpp:ShowThread.h
	$(MOCPATH) $(DEFINES) $(INCPATH) ShowThread.h -o $(GF)\Release\moc_ShowThread.cpp
moc_CameraWidget.cpp:CameraWidget.h
	$(MOCPATH) $(DEFINES) $(INCPATH) CameraWidget.h -o $(GF)\Release\moc_CameraWidget.cpp


	
$(GF)\ui_view.h:view.ui
	$(UICPATH) view.ui -o $(GF)\ui_view.h
$(GF)\ui_camerawidget.h:camerawidget.ui	
	$(UICPATH) camerawidget.ui -o $(GF)\ui_camerawidget.h

clean:
	if exist $(OUTDIR) del $(OUTDIR)\*.obj
	if exist $(OUTDIR) del $(OUTDIR)\*.exp

