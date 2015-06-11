/*
 * =====================================================================================
 *
 *       Filename:  ViewWidget.h
 *        Created:  2014/7/30 11:21:10
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  ������ʾ����
 *
 * =====================================================================================
 */

#ifndef  VIEWWIDGET_INC
#define  VIEWWIDGET_INC

#include <QtWidgets\qwidget.h>
#include "ui_view.h"
//ȫ�ֲ���
class GlobalArgs
{
public:
	static int g_radio;
	static int g_frame;
};

class ViewWidget :
	public QWidget
{
public:
	ViewWidget(QWidget *parent = NULL);
	~ViewWidget(void);

public:
	//���ñ�����ʾ�ı�
	void SetSave(bool save);

//�̳�
protected:
	//ÿ����ʾ����ֵ
 void timerEvent( QTimerEvent *qevent );

private:
	Ui::view mViewUi;
	//�Ƿ񱣴�������
	bool mbSave;
};

#endif   /* ----- #ifndef VIEWWIDGET_INC  ----- */
