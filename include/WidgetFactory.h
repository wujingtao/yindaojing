/*
 * =====================================================================================
 *
 *       Filename:  WidgetFactory.h
 *        Created:  2014-11-19 16:20:12
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  获取mylabel,加载图片
 *
 * =====================================================================================
 */

#ifndef  WIDGETFACTORY_INC
#define  WIDGETFACTORY_INC

#include <QString>
class QWidget;
class QLabel;
class QString;
class WidgetFactory
{
public:
	WidgetFactory(void);
	~WidgetFactory(void);

	//当前窗体类型
	static enum {Home=0, Report, Record, Camera,Image};
	//如果是Report,Image窗体则响应label单击事件
	static void SetCurrentWidget(int nw);

	//获取mylabel,name图片路径名
	static QLabel* GetLabel(QWidget *parent, QString name = "c");
};

#endif   /* ----- #ifndef WIDGETFACTORY_INC  ----- */
