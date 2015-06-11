/*
 * =====================================================================================
 *
 *       Filename:  MyComboBox.h
 *        Created:  2014/10/30 17:54:30
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  重写qcombobox双击事件和单击事件
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
	//继承
protected:
	//当双击事件弹出窗体，以动态添加值
	void mouseDoubleClickEvent (QMouseEvent *e) ;
	//当单击事件加载值到窗体
	void mousePressEvent (QMouseEvent *e); 
	//焦点丢失
	void focusOutEvent(QFocusEvent *e);

private:
	//是否加载值
	int mFlag;
};

#endif   /* ----- #ifndef MYCOMBOBOX_INC  ----- */
