#include "setupdebugoutput.h"
#include <QtGlobal>
#include <QString>
#include <QHash>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QStandardPaths>
#include <QtDebug>

static QString logFilePath;
static bool logToFile = false;

void customMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
  QHash<QtMsgType, QString> msgLevelHash({{QtDebugMsg, "Debug"}, {QtInfoMsg, "Info"}, {QtWarningMsg, "Warning"}, {QtCriticalMsg, "Critical"}, {QtFatalMsg, "Fatal"}});
  QByteArray localMsg = msg.toLocal8Bit();
  QTime time = QTime::currentTime();
  QString formattedTime = time.toString("hh:mm:ss.zzz");
  QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();
  QString logLevelName = msgLevelHash[type];
  QByteArray logLevelMsg = logLevelName.toLocal8Bit();

  if (logToFile) {
    QString txt = QString("%1 %2: %3 (%4)").arg(formattedTime, logLevelName, msg,  context.file);
    QFile outFile(logFilePath);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
    outFile.close();
  } else {
    fprintf(stderr, "%s %s: %s (%s:%u, %s)\n", formattedTimeMsg.constData(), logLevelMsg.constData(), localMsg.constData(), context.file, context.line, context.function);
    fflush(stderr);
  }

  if (type == QtFatalMsg)
    abort();
}

void setupDebugOutput()
{
#ifdef FORCE_DEBUG_REDIRECT
  logToFile = true;
#else
  QByteArray envVar = qgetenv("QTDIR");       //  check if the app is running in Qt Creator
  logToFile = envVar.isEmpty();
#endif

  if (logToFile) {
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    dir.mkpath(".");
    logFilePath = dir.absoluteFilePath("log.txt");
    qInfo() << "Log file path:" << logFilePath;
    QFile outFile(logFilePath);
    outFile.open(QIODevice::WriteOnly);
    outFile.close();
  }

  qInstallMessageHandler(customMessageOutput);
}
