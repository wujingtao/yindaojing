OUTDIR = ..\out

all:OUTDIR
	cd FileCentre
	nmake
	nmake clean

	cd ..
	cd ImageAlgorithm
	nmake
	nmake clean

	cd ..
	cd CameraWidget
	nmake
	nmake clean

	cd ..
	cd RecordWidget
	nmake
	nmake clean

	cd ..
	cd ReportWidget
	nmake
	nmake clean

	cd ..
	cd ImageWidget
	nmake
	nmake clean

	cd ..
	cd MyLabel
	nmake
	nmake clean

	cd ..
	cd MainWindow
	nmake
	nmake clean

OUTDIR:
	if not exist "$(OUTDIR)" mkdir $(OUTDIR)

