/*
 * =====================================================================================
 *
 *       Filename:  MySpinBox.h
 *        Created:  2015/3/27 10:19:16
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  ���㶪ʧ�¼��󱣴浱ǰֵ
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

protected: //���㶪ʧ
	void focusOutEvent(QFocusEvent *e);
};

