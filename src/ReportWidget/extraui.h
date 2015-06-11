//因ui的头文件编译时会自动修改，所以每次修改完后ui头文件添加该头文件
#include "MyComboBox.h"
#include "MyTextEdit.h"
#include "MyLineEdit.h"
#include "MySpinBox.h"
//ui内替换4个label
#include "MyLabel.h"
#define QComboBox MyComboBox
#define QTextEdit MyTextEdit
#define QLineEdit MyLineEdit
#define QSpinBox MySpinBox
//lb1 = WidgetFactory::GetLabel(wgReport);
//lb2 = WidgetFactory::GetLabel(wgReport);
//lb3 = WidgetFactory::GetLabel(wgReport);
//lb4 = WidgetFactory::GetLabel(wgReport);
