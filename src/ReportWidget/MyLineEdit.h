/*
 * =====================================================================================
 *
 *       Filename:  MyLineEdit.h
 *        Created:  2015/3/27 10:17:38
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  ��дQLineEdit�Ľ��㶪ʧ�¼��󣬱��浱ǰֵ
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

protected: //���㶪ʧ
	void focusOutEvent(QFocusEvent *e);
};

#endif   /* ----- #ifndef MYLINEEDIT_INC  ----- */
