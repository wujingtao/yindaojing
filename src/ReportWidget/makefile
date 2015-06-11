#目录
QTDIR = E:\Qt\Qt5.4.0\5.4\msvc2010_opengl
MOCPATH = $(QTDIR)\bin\moc.exe	
UICPATH = $(QTDIR)\bin\uic.exe
GF = GeneratedFiles
OUTDIR = ..\..\out

#参数
DEFINES = -DUNICODE -DWIN32 -DWIN64 -DQT_DLL -DQT_NO_DEBUG -DNDEBUG -DQT_CORE_LIB -DQT_WIDGETS_LIB -DREPORTWIDGET_LIB
CXXFLAGS      = -nologo -Zm200 -Zc:wchar_t -O2 -MD -GR -W3 -w34100 -w34189 -EHsc $(DEFINES)
INCPATH = -I".\GeneratedFiles" -I".\GeneratedFiles\Release" -I"$(QTDIR)\include" -I"$(QTDIR)\include\QtCore" -I"$(QTDIR)\include\QtWidgets" -I"$(QTDIR)\include\QtGui" -I"$(QTDIR)\include\QtPrintSupport" -I"..\..\include"
LFLAGS        = /NOLOGO /DYNAMICBASE /NXCOMPAT /INCREMENTAL:NO /SUBSYSTEM:WINDOWS 
LIBS = /LIBPATH:$(OUTDIR) FileCentre.lib  /LIBPATH:$(QTDIR)\lib qtmain.lib Qt5Core.lib Qt5Widgets.lib Qt5Gui.lib Qt5PrintSupport.lib

#项目文件
SOURCES = MyLabel.cpp $(GF)\Release\moc_MyTextEdit.cpp MyTextEdit.cpp MyLineEdit.cpp MySpinBox.cpp Report_a.cpp $(GF)\Release\moc_EditDialog.cpp EditDialog.cpp MyComboBox.cpp $(GF)\Release\moc_ReportWidget.cpp ReportWidget.cpp MyLabel.cpp ReportFactory.cpp 
INCLUDES = extraui.h MyLabel.h MyTextEdit.h MyLineEdit.h MySpinBox.h $(GF)\ui_report_a.h Report_a.h $(GF)\ui_editdialog.h EditDialog.h MyComboBox.h $(GF)\ui_reportwidget.h ReportWidget.h MyLabel.h ReportFactory.h

ReportWidget.dll:ReportWidget.obj
	link $(LFLAGS) /dll /out:$(OUTDIR)\ReportWidget.dll $(OUTDIR)\*.obj $(LIBS)
ReportWidget.obj:moc_MyTextEdit.cpp moc_EditDialog.cpp moc_ReportWidget.cpp $(INCLUDES)
	cl /c $(CXXFLAGS) $(INCPATH) /Fo$(OUTDIR)\ $(SOURCES)

#生产moc文件
moc_MyTextEdit.cpp:$(GF)\Release MyTextEdit.h
	$(MOCPATH) $(DEFINES) $(INCPATH) MyTextEdit.h -o $(GF)\Release\moc_MyTextEdit.cpp
moc_EditDialog.cpp:EditDialog.h
	$(MOCPATH) $(DEFINES) $(INCPATH) EditDialog.h -o $(GF)\Release\moc_EditDialog.cpp
moc_ReportWidget.cpp:ReportWidget.h
	$(MOCPATH) $(DEFINES) $(INCPATH) ReportWidget.h -o $(GF)\Release\moc_ReportWidget.cpp

#生成窗体头文件
$(GF)\Release:
	if not exist "$(GF)\Release" mkdir $(GF)\Release
$(GF)\ui_report_a.h:report_a.ui
	$(UICPATH) report_a.ui -o $(GF)\ui_report_a.h
$(GF)\ui_editdialog.h:	editdialog.ui
	$(UICPATH) editdialog.ui -o $(GF)\ui_editdialog.h
$(GF)\ui_reportwidget.h:reportwidget.ui
	$(UICPATH) reportwidget.ui -o $(GF)\ui_reportwidget.h

clean:
	if exist $(OUTDIR) del $(OUTDIR)\*.obj
	if exist $(OUTDIR) del $(OUTDIR)\*.exp

