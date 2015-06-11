/*
 * =====================================================================================
 *
 *       Filename:  EditDialog.h
 *        Created:  2015/3/27 10:12:51
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  mycombobox���øô��嶯̬���ֵ
 *
 * =====================================================================================
 */

#ifndef  EDITDIALOG_INC
#define  EDITDIALOG_INC

#include <qdialog.h>
#include "ui_editdialog.h"

class EditDialog : public QDialog
{
	Q_OBJECT
public:
	EditDialog(QWidget *parent, QString name = "");
	~EditDialog(void);

private:
		//�����°�ťʱ,��ȡ��ǰ�У����øú���
	void updown(int row);
	//��ʼ������ֵ���ô���
	void initListWidget(const QString &name);

	//�ۺ��������ڹ��캯����ʼ��
 private slots:
	 void addSlot();
	 void deleteSlot();
	 void upSlot();
	 void downSlot();
	 void editSlot(QListWidgetItem *item);
	 void okSlot();

private:
	Ui::editdialog ui;		
	//���浱ǰ�ؼ���
	QString mName;
};

#endif   /* ----- #ifndef EDITDIALOG_INC  ----- */
