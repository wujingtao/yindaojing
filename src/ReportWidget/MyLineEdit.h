/*
 * =====================================================================================
 *
 *       Filename:  MyLineEdit.h
 *        Created:  2015/3/27 10:17:38
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  重写QLineEdit的焦点丢失事件后，保存当前值
 *
 * =====================================================================================
 */

#ifndef  MYLINEEDIT_INC
#define  MYLINEEDIT_INC

#include <qlineedit.h>

class MyLineEdit :
	public QLineEdit
{
public:
	MyLineEdit(QWidget *parent = 0);
	~MyLineEdit(void);

protected: //焦点丢失
	void focusOutEvent(QFocusEvent *e);
};

#endif   /* ----- #ifndef MYLINEEDIT_INC  ----- */
