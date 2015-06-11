/*
 * =====================================================================================
 *
 *       Filename:  MyTextEdit.h
 *        Created:  2015/3/27 10:20:16
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  ��дQTextEdit��ʧ�¼������浱ǰֵ
 *
 * =====================================================================================
 */

#ifndef  MYTEXTEDIT_INC
#define  MYTEXTEDIT_INC

#include <qtextedit.h>
class MyTextEdit :
	public QTextEdit
{
	Q_OBJECT
public:
	MyTextEdit(QWidget *parent = 0);
	~MyTextEdit(void);

protected: //���㶪ʧ
	void focusOutEvent(QFocusEvent *e);

signals:
	void textEmptySignal();

};

#endif   /* ----- #ifndef MYTEXTEDIT_INC  ----- */
