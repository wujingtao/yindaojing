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
	//读取文件所有值
	void readFile(const string &name, vector<string> &vecValue);
	void saveFile(const string &name, const stringstream &ss);
	//设置/获取当前病案库的病案路径
	void SetRecordPath(const QString &s);
	//获取当前病案库的病案路径
	QString GetRecordPath() const;
	//读取文件单个值
	void ReadNameValue(const QString &name, QString &value);
	//保存文件单个值
	void SaveNameValue(const QString &name, const QString &value);
	//读取系统文件单个值
	void ReadSystemValue(const QString &name, QString &value, QString group="system");
	//读取文件所有值
	void ReadAllValue(const QString &file, ControlName &cn);
	
};

#endif   /* ----- #ifndef FILECENTRE_INC  ----- */
