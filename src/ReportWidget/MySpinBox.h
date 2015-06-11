/*
 * =====================================================================================
 *
 *       Filename:  MySpinBox.h
 *        Created:  2015/3/27 10:19:16
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  焦点丢失事件后保存当前值
 *
 * =====================================================================================
 */

#ifndef  MYSPINBOX_INC
#define  MYSPINBOX_INC

#endif   /* ----- #ifndef MYSPINBOX_INC  ----- */
#include <qspinbox.h>
class MySpinBox :
	public QSpinBox
{
public:
	MySpinBox(QWidget *parent = 0);
	~MySpinBox(void);

protected: //焦点丢失
	void focusOutEvent(QFocusEvent *e);
};

