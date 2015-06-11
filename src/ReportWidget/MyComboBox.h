/*
 * =====================================================================================
 *
 *       Filename:  MyComboBox.h
 *        Created:  2014/10/30 17:54:30
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  ��дqcombobox˫���¼��͵����¼�
 *
 * =====================================================================================
 */

#ifndef  MYCOMBOBOX_INC
#define  MYCOMBOBOX_INC

#include <qcombobox.h>

class MyComboBox :
	public QComboBox
{
public:
	MyComboBox(QWidget *parent = 0);
	~MyComboBox(void);

public:
	void clear();
	//�̳�
protected:
	//��˫���¼��������壬�Զ�̬���ֵ
	void mouseDoubleClickEvent (QMouseEvent *e) ;
	//�������¼�����ֵ������
	void mousePressEvent (QMouseEvent *e); 
	//���㶪ʧ
	void focusOutEvent(QFocusEvent *e);

private:
	//�Ƿ����ֵ
	int mFlag;
};

#endif   /* ----- #ifndef MYCOMBOBOX_INC  ----- */
