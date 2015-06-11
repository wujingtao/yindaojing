#include "FileCentre.h"
#include <fstream>
using std::ifstream;
using std::ofstream;

#include <qsettings.h>
#include <qtextcodec.h>


FileCentre* FileCentre::s_mFC = NULL;
FileCentre::FileCentre(void)
{
}


FileCentre::~FileCentre(void)
{
}


void FileCentre::readFile(const string &name, vector<string> &vecValue)
{
	string fileName = "values/" + name;
	ifstream ifs(fileName);
	if(ifs.is_open())
	{
		string str;	
		while(getline(ifs, str))	
		{
			vecValue.push_back(str);
		}
	}
}

void FileCentre::saveFile(const string &name, const stringstream &ss)
{
	string fileName = "values/" + name;
	ofstream ofs(fileName);
	ofs<<ss.str();
}

void FileCentre::SaveNameValue(const QString &name, const QString &value)
{
	QString fileName = mRecordPath + "/report.ini";
	QSettings setReport(fileName, QSettings::IniFormat);
	setReport.setIniCodec(QTextCodec::codecForName("GB2312"));
	//setReport.setIniCodec(QTextCodec::codecForName("GBK"));
	setReport.beginGroup("report");
	setReport.setValue(name, value);
	setReport.endGroup();	
}

void FileCentre::ReadNameValue(const QString &name, QString &value)
{
	
}

void FileCentre::ReadSystemValue(const QString &name, QString &value, QString group)
{
	QSettings setting("system.ini", QSettings::IniFormat);
	setting.setIniCodec(QTextCodec::codecForName("GB2312"));
	//setting.setIniCodec(QTextCodec::codecForName("UTF-8"));
	setting.beginGroup(group);
	value = setting.value(name).toString();

	setting.endGroup();
}


void FileCentre::SetRecordPath(const QString &s)
{
	mRecordPath = s;
}

QString FileCentre::GetRecordPath() const
{
	return mRecordPath;
}

FileCentre* FileCentre::GetInstance()
{
	if(s_mFC == NULL)
	{
		s_mFC = new FileCentre();	
	}

	return s_mFC;
}


void FileCentre::ReadAllValue(const QString &file, ControlName &cn)
{
	QSettings setReport(file, QSettings::IniFormat);
	setReport.setIniCodec(QTextCodec::codecForName("GB2312"));
	//setReport.setIniCodec(QTextCodec::codecForName("GBK"));
	setReport.beginGroup("report");
	cn.cbCheck = setReport.value("cbCheck").toString();
	cn.leName = setReport.value("leName").toString();
	cn.sbAge = setReport.value("sbAge").toInt();
	cn.cbExamine = setReport.value("cbExamine").toString();
	cn.cbRoom = setReport.value("cbRoom").toString();
	cn.sbCheckNo = setReport.value("sbCheckNo").toInt();
	cn.sbPatientNo = setReport.value("sbPatientNo").toInt();
	cn.sbHospitalNo = setReport.value("sbHospitalNo").toInt();
	cn.sbAreaNo = setReport.value("sbAreaNo").toInt();
	cn.sbBedNo = setReport.value("sbBedNo").toInt();
	cn.cbMoon = setReport.value("cbMoon").toString();
	cn.cbMarry = setReport.value("cbMarry").toString();
	cn.sbPreg = setReport.value("sbPreg").toInt();
	cn.sbBirth = setReport.value("sbBirth").toInt();
	cn.cbContra = setReport.value("cbContra").toString();
	cn.cbPatient = setReport.value("cbPatient").toString();
	cn.cbBed = setReport.value("cbBed").toString();
	cn.cbResult = setReport.value("cbResult").toString();
	cn.cbConfine = setReport.value("cbConfine").toString();
	cn.cbS1 = setReport.value("cbS1").toString();
	cn.cbColor = setReport.value("cbColor").toString();
	cn.cbS2 = setReport.value("cbS2").toString();
	cn.cbBlood = setReport.value("cbBlood").toString();
	cn.cbS3 = setReport.value("cbS3").toString();
	cn.cbIodine = setReport.value("cbIodine").toString();
	cn.cbS4 = setReport.value("cbS4").toString();
	cn.teContent = setReport.value("teContent").toString();
	cn.cbS4 = setReport.value("cbS4").toString();
	cn.cbS5 = setReport.value("cbS5").toString();
	cn.cbApply = setReport.value("cbApply").toString();
	cn.cbDiag = setReport.value("cbDiag").toString();
	cn.lb1 = setReport.value("lb1").toString();
	cn.lb2 = setReport.value("lb2").toString();
	cn.lb3 = setReport.value("lb3").toString();
	cn.lb4 = setReport.value("lb4").toString();
	cn.teImageText= setReport.value("teImageText").toString();
	cn.reportname= setReport.value("reportname").toString();
	cn.createtime= setReport.value("createtime").toString();
	setReport.endGroup();
	
}
