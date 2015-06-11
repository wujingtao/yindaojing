#ifndef  RECORDFACTORY_INC
#define  RECORDFACTORY_INC

class QWidget;
class RecordFactory
{
public:
	RecordFactory(void);
	~RecordFactory(void);

	static QWidget* CreateRecord(QString from = "");
};

#endif   /* ----- #ifndef RECORDFACTORY_INC  ----- */
