/*
 * =====================================================================================
 *
 *       Filename:  MyLabel.h
 *        Created:  2015/3/27 10:09:09
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  重写label，继承单击事件加载和移除图像
 *
 * =====================================================================================
 */

#ifndef  MYLABEL_INC
#define  MYLABEL_INC

#include <qlabel.h>
class MyLabel :
	public QLabel 
{
public:
	MyLabel(QWidget *parent = 0);
	~MyLabel(void);

public:

	/* 
	 *功能: 设置label图像
	 *参数: fullName in 图像全路径 
	 *返回: void
	 */
	void setMyPixmap(const QString &fullName);
protected:
	//继承，鼠标单击事件
	void mousePressEvent(QMouseEvent *e);
};

#endif   /* ----- #ifndef MYLABEL_INC  ----- */
