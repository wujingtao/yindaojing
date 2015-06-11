/*
 * =====================================================================================
 *
 *       Filename:  EditDialog.h
 *        Created:  2015/3/27 10:12:51
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  mycombobox调用该窗体动态添加值
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
		//当上下按钮时,获取当前行，调用该函数
	void updown(int row);
	//初始化本地值到该窗体
	void initListWidget(const QString &name);

	//槽函数，已在构造函数初始化
 private slots:
	 void addSlot();
	 void deleteSlot();
	 void upSlot();
	 void downSlot();
	 void editSlot(QListWidgetItem *item);
	 void okSlot();

private:
	Ui::editdialog ui;		
	//保存当前控件名
	QString mName;
};

#endif   /* ----- #ifndef EDITDIALOG_INC  ----- */
