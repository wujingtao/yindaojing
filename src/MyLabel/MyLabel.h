/*
 * =====================================================================================
 *
 *       Filename:  MyLabel.h
 *        Created:  2014/10/29 17:47:00
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  ��дlabel����Ӧ�����¼�
 *
 * =====================================================================================
 */

#include <qlabel.h>

class  MyLabel :
	public QLabel
{
public:
		//pathͼƬ·����
	MyLabel(QWidget *parent, QString path = "c");
	~MyLabel(void){}

	//���õ�ǰ����Ĵ��壬nwΪö������
	static void SetCurrentWidget(int nw);
protected:
	//�̳У���굥���¼�
	void mousePressEvent(QMouseEvent *e);

private:
	//ͼƬ·��
	QString mPathName;
	//��������labelͼ�����
	//static const int IMAGENUM = 4;
	//static QString mStrImage[IMAGENUM];
	//���浱ǰ����
	static int mNameWidget;
};

