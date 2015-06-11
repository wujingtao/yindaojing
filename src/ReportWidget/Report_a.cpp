#include "Report_a.h"
#include "ControlName.h"
#include "FileCentre.h"


Report_a::Report_a(void)
{
	ui.setupUi(this);

	initValue();
}


Report_a::~Report_a(void)
{
}


void Report_a::initValue()
{
	ControlName cn;
	FileCentre *fc = FileCentre::GetInstance();
	QString path = fc->GetRecordPath();
	fc->ReadAllValue(path.append("/report.ini"), cn);	

	ui.lbCheck->setText(cn.cbCheck);
	ui.lbTime->setText( cn.createtime.left(16));	
	ui.lbName->setText( cn.leName);
	ui.lbAge->setText( QString("%1").arg(cn.sbAge));
	ui.lbExamine->setText( cn.cbExamine);
	ui.lbRoom->setText(  cn.cbRoom);
	ui.lbCheckNo->setText( QString("%1").arg(cn.sbCheckNo));
	ui.lbPatientNo->setText( QString("%1").arg(cn.sbPatientNo));
	ui.lbHospitalNo->setText( QString("%1").arg(cn.sbHospitalNo));
	ui.lbAreaNo->setText( QString("%1").arg(cn.sbAreaNo));
	ui.lbBedNo->setText( QString("%1").arg(cn.sbBedNo));
	ui.lbMoon->setText( cn.cbMoon);
	ui.lbMarry->setText( cn.cbMarry);
	ui.lbPreg->setText( QString("%1").arg(cn.sbPreg));
	ui.lbBirth->setText( QString("%1").arg(cn.sbBirth));
	ui.lbContra->setText( cn.cbContra);
	ui.lbPatient->setText( cn.cbPatient);
	ui.lbBed->setText( cn.cbBed);
	ui.lbResult->setText( cn.cbResult);
	ui.lbConfine->setText( cn.cbConfine);
	ui.lbColor->setText( cn.cbColor);
	ui.lbBlood->setText( cn.cbBlood);
	ui.lbIodine->setText( cn.cbIodine);
	ui.lbS1->setText( cn.cbS1);
	ui.lbS2->setText( cn.cbS2);
	ui.lbS3->setText( cn.cbS3);
	ui.lbS4->setText( cn.cbS4);
	ui.lbS5->setText( cn.cbS5);
	ui.teImageText->setText( cn.teImageText);
	ui.teContent->setText( cn.teContent);
	ui.lbApply->setText( cn.cbApply);
	ui.lbDiag->setText( cn.cbDiag);
	ui.lb1->setPixmap(cn.lb1);
	ui.lb2->setPixmap(cn.lb2);
	ui.lb3->setPixmap(cn.lb3);
	ui.lb4->setPixmap(cn.lb4);
}	