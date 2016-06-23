#include "mainwindow.h"
#include <QApplication>
#include "globals.h"
#include <sstream>

# ifndef QStringLiteral
# define QStringLiteral(str) QString::fromUtf8("" str "", sizeof(str) - 1)
# endif

# ifndef QByteArrayLiteral
# define QByteArrayLiteral(str) QByteArray(str, sizeof(str) - 1)
# endif

int main(int argc, char **argv)
{
  QApplication a(argc, argv);
  MainWindow w;
  QString s =  QStringLiteral("Hello");
  w.show();

  return a.exec();
}
