#include <QtGui/QApplication>
#include "login.h"
#include "sqlquery.h"
#include <QTextCodec>
int main(int argc, char *argv[])
{
    //·ÀÖ¹ÂÒÂë

    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
     QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
     QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
    sqlQuery::Instance("myscore.db");
    //µÇÂ¼´°Ìå
    login w;
    w.show();

    return a.exec();
}
