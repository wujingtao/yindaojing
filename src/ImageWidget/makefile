#目录
QTDIR= E:\Qt\Qt5.4.0\5.4\msvc2010_opengl
MOCPATH = $(QTDIR)\bin\moc.exe	
UICPATH = $(QTDIR)\bin\uic.exe
OUTDIR = ..\..\out
GF = GeneratedFiles

#参数
DEFINES = -DUNICODE -DWIN32 -DWIN64 -DQT_DLL -DQT_NO_DEBUG -DNDEBUG -DQT_CORE_LIB -DQT_GUI_LIB -DQT_WIDGETS_LIB -DIMAGEWIDGET_LIB
CXXFLAGS      = -nologo -Zm200 -Zc:wchar_t -O2 -MD -GR -W3 -w34100 -w34189 -EHsc $(DEFINES)
INCPATH       = -I"$(QTDIR)\include" -I"$(QTDIR)\include\QtWidgets" -I"$(QTDIR)\include\QtGui" -I"$(QTDIR)\include\QtCore" -I"$(QTDIR)\mkspecs\win32-msvc2010" -I"GeneratedFiles" -I"."
LFLAGS        = /NOLOGO /DYNAMICBASE /NXCOMPAT /INCREMENTAL:NO /SUBSYSTEM:WINDOWS
LIBS          = /LIBPATH:$(QTDIR)\lib Qt5Widgets.lib Qt5Gui.lib Qt5Core.lib

#项目文件
INCLUDES = MyScrollArea.h MyLabelImage.h $(GF)\ui_imagewidget.h ImageWidget.h ImageFactory.h
SOURCES = MyScrollArea.cpp MyLabelImage.cpp $(GF)\Release\moc_ImageWidget.cpp ImageWidget.cpp ImageFactory.cpp

ImageWidget.dll:ImageWidget.obj
	link $(LFLAGS) /dll $(OUTDIR)\*.obj $(LIBS) /out:$(OUTDIR)\ImageWidget.dll
ImageWidget.obj:$(GF)\Release moc_ImageWidget.cpp $(INCLUDES)
	cl /c /Fo$(OUTDIR)\ $(CXXFLAGS) $(INCPATH) $(SOURCES) 

$(GF)\Release:
	if not exist "$(GF)\Release" mkdir $(GF)\Release
moc_ImageWidget.cpp:ImageWidget.h
	$(MOCPATH) ImageWidget.h -o $(GF)\Release\moc_ImageWidget.cpp
$(GF)\ui_imagewidget.h:imagewidget.ui
	$(UICPATH) imagewidget.ui -o $(GF)\ui_imagewidget.h
	
clean:
	if exist $(OUTDIR) del $(OUTDIR)\*.obj
	if exist $(OUTDIR) del $(OUTDIR)\*.exp
	
