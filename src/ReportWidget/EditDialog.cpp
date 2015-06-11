#include "EditDialog.h"
#include "FileCentre.h"

#include <vector>
#include <sstream>
#include <fstream>
#include <string>
using std::stringstream;
using std::ofstream;
using std::ifstream;
using std::endl;
using std::string;
using std::vector;

EditDialog::EditDialog(QWidget *parent, QString name) : QDialog(parent)
{
	mName = name;
	ui.setupUi(this);

	//���
	connect(ui.pbAdd, SIGNAL(clicked()), this, SLOT(addSlot()));
	//ɾ��
	connect(ui.pbDelete, SIGNAL(clicked()), this, SLOT(deleteSlot()));
	//��
	connect(ui.pbUp, SIGNAL(clicked()), this, SLOT(upSlot()));
	//��
	connect(ui.pbDown, SIGNAL(clicked()), this, SLOT(downSlot()));
	//ȷ��
	connect(ui.pbOk, SIGNAL(clicked()), this, SLOT(okSlot()));
	//˫���༭
	connect(ui.lvItem, SIGNAL(itemDoubleClicked( QListWidgetItem*)), this, SLOT(editSlot(QListWidgetItem*)));

	initListWidget(mName);
}


EditDialog::~EditDialog(void)
{
}

void EditDialog::initListWidget(const QString &name)
{
	vector<string> vecValue;	
	FileCentre *fc = FileCentre::GetInstance();
	fc->readFile(name.toStdString(), vecValue);

	for(int i=0; i<vecValue.size(); i++)
	{
		ui.lvItem->addItem(new QListWidgetItem(QString::fromStdString(vecValue[i])));	
	}
}


 void EditDialog::addSlot()
 {
	QListWidgetItem *item = new QListWidgetItem(QStringLiteral("�½���Ŀ")); 
	ui.lvItem->addItem(item);
	editSlot(item);
 }

 void EditDialog::deleteSlot()
 {
	 QListWidgetItem *item = ui.lvItem->currentItem();
	 ui.lvItem->removeItemWidget(item);
	 delete item;
 }

 void EditDialog::upSlot()
 {
	 int row = ui.lvItem->currentRow();
	 if(row > 0)
	 {
		 --row;
		 updown(row);
	 }

 }

 void EditDialog::downSlot()
 {
	 int total = ui.lvItem->count();
	 int row = ui.lvItem->currentRow();

	 if(row != -1 && ++row < total)
	 {
		updown(row);	
	 }
 }

 void EditDialog::updown(int row)
 {
	 //��ǰitem
	 QListWidgetItem *item = ui.lvItem->currentItem();
	 QString strItem = item->text();
	 //��һ��item
	 QListWidgetItem *repItem = ui.lvItem->item(row);
	 QString strUpItem = repItem->text();
	 //�滻text
	 item->setText(strUpItem);
	 repItem->setText(strItem);

	 //�����滻
	 ui.lvItem->setCurrentItem(repItem);
 }

 void EditDialog::okSlot()
 {
	 stringstream ss;		 
	 int total = ui.lvItem->count();
	 for(int i=0; i<total;  i++)
	 {
		 QString str = ui.lvItem->item(i)->text();	 
		 ss<<str.toStdString()<<endl;
	 }

	 FileCentre *fc = FileCentre::GetInstance();
	 fc->saveFile(mName.toStdString(), ss);

	 accept();
 }

 void EditDialog::editSlot(QListWidgetItem *item)
 {
	 item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsEditable|Qt::ItemIsSelectable);
	 ui.lvItem->editItem(item); 
 }
