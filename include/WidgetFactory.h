/*
 * =====================================================================================
 *
 *       Filename:  WidgetFactory.h
 *        Created:  2014-11-19 16:20:12
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  ��ȡmylabel,����ͼƬ
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

	//��ǰ��������
	static enum {Home=0, Report, Record, Camera,Image};
	//�����Report,Image��������Ӧlabel�����¼�
	static void SetCurrentWidget(int nw);

	//��ȡmylabel,nameͼƬ·����
	static QLabel* GetLabel(QWidget *parent, QString name = "c");
};

#endif   /* ----- #ifndef WIDGETFACTORY_INC  ----- */
