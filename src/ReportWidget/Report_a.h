/*
 * =====================================================================================
 *
 *       Filename:  Report_a.h
 *        Created:  2015-03-18 16:01:24
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  根据此模板打印报表
 *
 * =====================================================================================
 */

#pragma once
#include "qwidget.h"
#include "ui_report_a.h"
class Report_a :
	public QWidget
{
public:
	Report_a(void);
	~Report_a(void);

private:
	void initValue();

private:
	Ui::report_a ui;
};

