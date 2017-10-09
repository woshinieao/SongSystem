#include "songsystem.h"
#include <QtGui/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SongSystem w;
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB18030"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB18030"));
	 QApplication::setStyle("windowsxp");
	w.show();
	return a.exec();
}
