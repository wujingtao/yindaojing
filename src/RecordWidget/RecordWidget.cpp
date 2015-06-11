#include "RecordWidget.h"
#include <qsettings.h>
#include <qtextcodec.h>
#include <qscrollbar.h>
#include <qmessagebox.h>

#include "FileCentre.h"

int RecordWidget::s_OBJ = 0;
RecordWidget::RecordWidget(QString from)
{
	++s_OBJ;
	mPath = "";
	bLeName = false;
	bSbAge = false;
	ui.setupUi(this);
	if(from == "home")
	{
		ui.pbBack->setText(QStringLiteral("关闭"));	
		//关闭回到主窗体
		connect(ui.pbBack, SIGNAL(clicked()), this, SLOT(closeSlot()));
	}
	else
	{
		//返回
		connect(ui.pbBack, SIGNAL(clicked()), this, SLOT(reportSlot()));
	}

	//打开
	connect(ui.pbOpen, SIGNAL(clicked()), this, SLOT(reportSlot()));
	//日期筛选
	connect(ui.pbToday, SIGNAL(clicked()), this, SLOT(todaySlot()));
	connect(ui.pbWeek, SIGNAL(clicked()), this, SLOT(weekSlot()));
	connect(ui.pbMonth, SIGNAL(clicked()), this, SLOT(monthSlot()));
	connect(ui.pbYear, SIGNAL(clicked()), this, SLOT(yearSlot()));
	connect(ui.pbAll, SIGNAL(clicked()), this, SLOT(allSlot()));
	//搜索
	connect(ui.pbSearch, SIGNAL(clicked()), this, SLOT(searchSlot()));

	//行改变
	connect(ui.twRecord, SIGNAL(cellClicked(int, int)), this, SLOT(changeSlot(int, int)));

	//滚动条改变
	connect(ui.twRecord->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(sliderMovedSlot(int)));
	

	loadRecord();
}


RecordWidget::~RecordWidget(void)
{
	--s_OBJ;
}

int RecordWidget::GetOBJ()
{
	return s_OBJ;
}

void RecordWidget::sliderMovedSlot(int value)
{
	if(bLeName || bSbAge)
	{return;}

	int max = ui.twRecord->verticalScrollBar()->maximum();
	if(value == max)
	{
		if(miPage*100 < mFolderList.count())
		{
			++miPage;
			currentPage();
		}
	}
}

void RecordWidget::closeSlot()
{
	emit closeSignal();
}

void RecordWidget::reportSlot()
{
	if(mPath != "")
	{
		FileCentre *fc = FileCentre::GetInstance();
		fc->SetRecordPath(mPath);
	}
	emit reportSignal();
}

void RecordWidget::changeSlot(int r, int c)
{
	QTableWidgetItem *item = ui.twRecord->item(r, 0);
	mPath = item->text();
	emit changeSignal(mPath);		
}

void RecordWidget::loadRecord()
{
	ui.twRecord->setColumnCount(6); 
	QStringList headers; 
	headers <<QStringLiteral("路径")<< QStringLiteral("时间") << QStringLiteral("姓名") 
		<< QStringLiteral("年龄") <<QStringLiteral("病历号")<<QStringLiteral("医生")<< QStringLiteral("病例属性"); 
	ui.twRecord->setHorizontalHeaderLabels(headers);
	//ui.twRecord->resizeColumnsToContents();

	//文件夹
	//读取文件夹所有文档
	//读取文件记录
	//加载到table
	QSettings sett("system.ini", QSettings::IniFormat);
	sett.beginGroup("system");
	mFilePath = sett.value("filepath").toString();
	sett.endGroup();

	QDir dir(mFilePath);
	mFolderList = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name | QDir::Reversed);
	
	miPage = 0;
	if(mFolderList.count() > 0)
	{
		miPage = 1;
		currentPage();	
	}


	/*
    //获取所选文件类型过滤器
    QStringList filters;
    filters<<"*.ini";
    //定义迭代器并设置过滤器
    mDirIterator = new QDirIterator(filePath, filters, QDir::NoFilter, QDirIterator::Subdirectories);
    //QStringList string_list;
	static int i=0;
    for(i; mDirIterator->hasNext(); i++)
    {
        mDirIterator->next();
        QFileInfo fileInfo = mDirIterator->fileInfo();
		QString filePath = fileInfo.absoluteFilePath();
        //string_list.append(file_path);
		QSettings sett(filePath, QSettings::IniFormat);
		sett.setIniCodec(QTextCodec::codecForName("GB2312"));
		sett.beginGroup("report");
		QString createtime = sett.value("createtime").toString();
		QString leName = sett.value("leName").toString();
		QString sbAge = sett.value("sbAge").toString();
		sett.endGroup();

        ui.twRecord->setItem(i, 0, new QTableWidgetItem(fileInfo.absolutePath())); 
        ui.twRecord->setItem(i, 1, new QTableWidgetItem(createtime)); 
        ui.twRecord->setItem(i, 2, new QTableWidgetItem(leName)); 
        ui.twRecord->setItem(i, 3, new QTableWidgetItem(sbAge)); 

		if(i == 10000)
		{
			break;	
		}
    }
	ui.twRecord->setRowCount(i);
	//ui.twRecord->setColumnWidth(0, 0);
	ui.twRecord->resizeColumnToContents(1); 
	ui.twRecord->sortByColumn(1);
	i = 0;
	*/
}


void RecordWidget::currentPage()
{
	int start = (miPage-1)*100;
	int fcount = mFolderList.count();
	int end = miPage*100 > fcount ? fcount : miPage*100;
	ui.twRecord->setRowCount(end);

	QFileInfoList file_list;
	int i = start;
    for(i; i< end; i++)
    {
        QString name = mFolderList.at(i).absoluteFilePath();

		QDir dir(name);
		QStringList filters;
		filters <<"*.ini";
		dir.setNameFilters(filters);
		QFileInfoList child_file_list = dir.entryInfoList(QDir::Files | QDir::NoSymLinks);
		file_list.append(child_file_list);
		/*防止文件为空
		if(!child_file_list.empty())
		{
		file_list.append(child_file_list);
		}
		*/
    }

	int file_count = file_list.size();
	//ui.twRecord->setRowCount(file_count);
	for(int j=0; j<file_count; j++)
	{
        QFileInfo file_info = file_list.at(j);
		QString file_path = file_info.absoluteFilePath();

		QSettings sett(file_path, QSettings::IniFormat);
		sett.setIniCodec(QTextCodec::codecForName("GB2312"));
		sett.beginGroup("report");
		QString createtime = sett.value("createtime").toString();
		QString leName = sett.value("leName").toString();
		QString sbAge = sett.value("sbAge").toString();
		sett.endGroup();

        ui.twRecord->setItem(start + j, 0, new QTableWidgetItem(file_info.absolutePath())); 
        ui.twRecord->setItem(start + j, 1, new QTableWidgetItem(createtime)); 
        ui.twRecord->setItem(start + j, 2, new QTableWidgetItem(leName)); 
        ui.twRecord->setItem(start + j, 3, new QTableWidgetItem(sbAge)); 

	}
	//ui.twRecord->setRowCount(j);
	//ui.twRecord->setColumnWidth(0, 0);
	//ui.twRecord->resizeColumnToContents(1); 
	ui.twRecord->resizeColumnsToContents();
	//ui.twRecord->sortByColumn(1);
}


void RecordWidget::todaySlot()
{
	QDate today = QDate::currentDate();

	ui.deStartDate->setDate(today);
	ui.deEndDate->setDate(today);
}

void RecordWidget::weekSlot()
{
	QDate today = QDate::currentDate();
	int w = today.dayOfWeek();

	ui.deStartDate->setDate(today.addDays(-1*w + 1));
	ui.deEndDate->setDate(today.addDays(7-w));
}

void RecordWidget::monthSlot()
{
	QDate today = QDate::currentDate();
	int m = today.day();
	int md = today.daysInMonth();

	ui.deStartDate->setDate(today.addDays(-1*m + 1));
	ui.deEndDate->setDate(today.addDays(md-m));
}

void RecordWidget::yearSlot()
{
	QDate today = QDate::currentDate();
	int y = today.year();

	ui.deStartDate->setDate(QDate(y,01,01));
	ui.deEndDate->setDate(QDate(y,12,31));
}

void RecordWidget::allSlot()
{
	ui.deStartDate->setDate(QDate(2000,01,01));
	ui.deEndDate->setDate(QDate(2099,12,31));
}

void RecordWidget::searchSlot()
{
	QDate date1 = ui.deStartDate->date();
	QDate date2 = ui.deEndDate->date();
	if(date1 > date2)
	{
		QMessageBox::warning(this, QStringLiteral("日期提醒"),
						QStringLiteral("开始日期大于结束日期！"), QStringLiteral("确定"));
		return;

	}

	int y1 = date1.toString("yy").toInt();
	int y2 = date2.toString("yy").toInt();
	int m1 = date1.month();
	int m2 = date2.month();
	/*
	int m1_1 = m1/10;
	int m1_2 = m1%10;
	int m2_1 = m2/10;
	int m2_2 = m2%10;
	*/

	QDir dir(mFilePath);
	QStringList strList;
	//同年
	if(y1 == y2)
	{
		if(m1<10 && m2<10)
		{
			//同年，01-09
			strList<<QString("%1%2[%3-%4]*").arg(y1).arg(0).arg(m1).arg(m2);	
		}
		else if(m1<10 && m2>=10)
		{
			//01-09 10-12
			strList<<QString("%1%2[%3-9]*").arg(y1).arg(0).arg(m1)	
				<<QString("%1%2[0-%3]*").arg(y1).arg(1).arg(m2-10);
		}
		else if(m1>=10 && m2>=10)
		{
			//同年，10-12
			strList<<QString("%1%2[%3-%4]*").arg(y1).arg(1).arg(m1-10).arg(m2-10);	
		}
	}
	//跨年
	else if(y1<y2)
	{
		//y1 m1-12	
		if(m1<10)
		{
			//01-09 10-12
			strList<<QString("%1%2[%3-9]*").arg(y1).arg(0).arg(m1)
				<<QString("%1%2[0-2]*").arg(y1).arg(1);	
		}
		else
		{
			//10-12
			strList<<QString("%1%2[%3-2]*").arg(y1).arg(1).arg(m1-10);	
		}

		if((y1+1)!=y2)
		{
			//y1+1 y2-1
			strList<<QString("[%1-%2][%3-%4]0[1-9]*").arg((y1+1)/10).arg((y2-1)/10).arg((y1+1)%10).arg((y2-1)%10)
				<<QString("[%1-%2][%3-%4]1[0-2]*").arg((y1+1)/10).arg((y2-1)/10).arg((y1+1)%10).arg((y2-1)%10);
		}

		//y2 01-m2
		if(m2<10)
		{
			//01-m2
			strList<<QString("%1%2[1-%3]*").arg(y2).arg(0).arg(m2);
		}
		else
		{
			//01-09	09-m2
			strList<<QString("%1%2[1-9]*").arg(y2).arg(0)
				<<QString("%1%2[0-%3]*").arg(y2).arg(1).arg(m2-10);	
		}		
	}


	//跨年
	//x | [(x+1)-(y-1)][0-9] | y
	

	mFolderList = dir.entryInfoList(strList, QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name | QDir::Reversed);

	bLeName = false;
	bSbAge = false;
	if(mFolderList.count() > 0)
	{
		QString len = ui.leName->text();
		if(!ui.leName->text().isEmpty())
		{
			bLeName = true;
		}
		if(ui.sbAgeEnd->value() !=0)
		{
			bSbAge = true;	
		}

		if(bLeName || bSbAge)
		{
			searchPage();	
		}
		else
		{
		miPage = 1;
		currentPage();	
		}
	}
	else
	{
		ui.twRecord->setRowCount(0);	
	}
}

void RecordWidget::searchPage()
{
	int fcount = mFolderList.count();

	QFileInfoList file_list;
    for(int i=0; i< fcount; i++)
    {
        QString name = mFolderList.at(i).absoluteFilePath();

		QDir dir(name);
		QStringList filters;
		filters <<"*.ini";
		dir.setNameFilters(filters);
		QFileInfoList child_file_list = dir.entryInfoList(QDir::Files | QDir::NoSymLinks);
		file_list.append(child_file_list);
    }

	int file_count = file_list.size();
	ui.twRecord->setRowCount(file_count);

	QString leName = ui.leName->text().trimmed();
	int ageStart = ui.sbAgeStart->value();
	int ageEnd = ui.sbAgeEnd->value();
	int s = 0;
	for(int j=0; j<file_count; j++)
	{
        QFileInfo file_info = file_list.at(j);
		QString file_path = file_info.absoluteFilePath();

		QSettings sett(file_path, QSettings::IniFormat);
		sett.setIniCodec(QTextCodec::codecForName("GB2312"));
		sett.beginGroup("report");
		QString createtime = sett.value("createtime").toString();
		QString leName = sett.value("leName").toString();
		QString sbAge = sett.value("sbAge").toString();
		sett.endGroup();

		if(bLeName && leName != ui.leName->text().trimmed())
		{
			continue;	
		}
		//int sb = sbAge.toInt();
		if(bSbAge && (sbAge.toInt() < ageStart || sbAge.toInt() > ageEnd))
		{
			continue;	
		}

        ui.twRecord->setItem(s, 0, new QTableWidgetItem(file_info.absolutePath())); 
        ui.twRecord->setItem(s, 1, new QTableWidgetItem(createtime)); 
        ui.twRecord->setItem(s, 2, new QTableWidgetItem(leName)); 
        ui.twRecord->setItem(s, 3, new QTableWidgetItem(sbAge)); 
		++s;
	}
	ui.twRecord->setRowCount(s);
	//ui.twRecord->setColumnWidth(0, 0);
	//ui.twRecord->resizeColumnToContents(1); 
	ui.twRecord->resizeColumnsToContents();
	//ui.twRecord->sortByColumn(1);
}
