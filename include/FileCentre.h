#ifndef  FILECENTRE_INC
#define  FILECENTRE_INC

#include "ControlName.h"
#include <qstring.h>
#include <string>
#include <vector>
#include <sstream>
using std::vector;
using std::string;
using std::stringstream;

class FileCentre
{
public:
	~FileCentre(void);

	static FileCentre* GetInstance();
private:
	explicit FileCentre(void);
	

public:
	//��ȡ�ļ�����ֵ
	void readFile(const string &name, vector<string> &vecValue);
	void saveFile(const string &name, const stringstream &ss);
	//����/��ȡ��ǰ������Ĳ���·��
	void SetRecordPath(const QString &s);
	//��ȡ��ǰ������Ĳ���·��
	QString GetRecordPath() const;
	//��ȡ�ļ�����ֵ
	void ReadNameValue(const QString &name, QString &value);
	//�����ļ�����ֵ
	void SaveNameValue(const QString &name, const QString &value);
	//��ȡϵͳ�ļ�����ֵ
	void ReadSystemValue(const QString &name, QString &value, QString group="system");
	//��ȡ�ļ�����ֵ
	void ReadAllValue(const QString &file, ControlName &cn);
	
};

#endif   /* ----- #ifndef FILECENTRE_INC  ----- */