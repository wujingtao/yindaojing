/*
 * =====================================================================================
 *
 *       Filename:  MyLabel.h
 *        Created:  2014/10/29 17:47:00
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  重写label，响应单击事件
 *
 * =====================================================================================
 */

#include <qlabel.h>

class  MyLabel :
	public QLabel
{
public:
		//path图片路径名
	MyLabel(QWidget *parent, QString path = "c");
	~MyLabel(void){}

	//设置当前程序的窗体，nw为枚举类型
	static void SetCurrentWidget(int nw);
protected:
	//继承，鼠标单击事件
	void mousePressEvent(QMouseEvent *e);

private:
	//图片路径
	QString mPathName;
	//关联报表label图像加载
	//static const int IMAGENUM = 4;
	//static QString mStrImage[IMAGENUM];
	//保存当前窗体
	static int mNameWidget;
};

