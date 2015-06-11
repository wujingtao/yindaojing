/*
 * =====================================================================================
 *
 *       Filename:  MyLabel.h
 *        Created:  2015/3/27 10:09:09
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  ��дlabel���̳е����¼����غ��Ƴ�ͼ��
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
	 *����: ����labelͼ��
	 *����: fullName in ͼ��ȫ·�� 
	 *����: void
	 */
	void setMyPixmap(const QString &fullName);
protected:
	//�̳У���굥���¼�
	void mousePressEvent(QMouseEvent *e);
};

#endif   /* ----- #ifndef MYLABEL_INC  ----- */
