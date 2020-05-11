#include <QTimerEvent>
#include <QCoreApplication>
#include "logevent.h"
#include <QDir>
#include <QDebug>

QObject * LogEvent::mObject = NULL;
int LogEvent::mLogLevel = LogEvent::LOG_DEBUG;
log4cpp::Category& root = log4cpp::Category::getRoot().getInstance("RootName");

LogEvent::LogEvent(Type type, const QString &log):
    QEvent(type) {
    mLogString = log;
}

LogEvent::~LogEvent() {

}

void LogEvent::setEventReceiver(QObject *obj) {
    mObject = obj;
}

void LogEvent::setLogLevel(int level)
{
    switch(level)
    {
    case LOG_ERROR:
        LogEvent::postLog("Set log level to: ERROR");
        mLogLevel = level;
        break;
    case LOG_WARN:
        LogEvent::postLog("Set log level to: WARN");
        mLogLevel = level;
        break;
    case LOG_INFO:
        LogEvent::postLog("Set log level to: INFO");
        mLogLevel = level;
        break;
    case LOG_NOTICE:
        LogEvent::postLog("Set log level to: NOTICE");
        mLogLevel = level;
        break;
    case LOG_DEBUG:
        LogEvent::postLog("Set log level to: DEBUG");
        mLogLevel = level;
        break;
    case LOG_NOTSET:
        LogEvent::postLog("Set log level to: NOTSET");
        mLogLevel = level;
        break;            
    case LOG_CRIT:
        LogEvent::postLog("Set log level to: CRIT");
        mLogLevel = level;
        break;
    case LOG_ALERT:
        LogEvent::postLog("Set log level to: ALERT");
        mLogLevel = level;
        break;
    case LOG_FATAL:
        LogEvent::postLog("Set log level to: FATAL");
        mLogLevel = level;
        break;
    default:
        break;
    }
    root.setPriority(level);
}

void LogEvent::initLog4cpp()
{
    QString file;

    QString logDir = QDir::homePath() + "/.INTECHIWB";

    if(!QDir().exists(logDir))
    {
        if(!QDir().mkdir(logDir))
        {
            qDebug("mkdir %s failed", logDir.toLocal8Bit().data());
            logDir = QDir::homePath() + "/Sharing/";
            if(!QDir().mkdir(logDir))
            {
                logDir = QDir::homePath() + "/";
            }
        }
        else
        {
            logDir = QDir::homePath() + "/.INTECHIWB/Sharing/";
            if(!QDir().mkdir(logDir))
            {
                logDir = QDir::homePath() + "/.INTECHIWB/";
            }
        }

    }
    else
    {
        logDir = logDir + "/Sharing/";
        if(!QDir().exists(logDir))
        {
            if(!QDir().mkdir(logDir))
            {
                logDir = QDir::homePath() + "/.INTECHIWB/";
            }
        }
    }
    file = logDir + "sharing.log";
    log4cpp::PatternLayout* pLayout = new log4cpp::PatternLayout();
    pLayout->setConversionPattern("%d: %p: %m%n");
    log4cpp::RollingFileAppender* rollfileAppender = new log4cpp::RollingFileAppender(
                                    "rollfileAppender", file.toLocal8Bit().data(), 1 * 1024 * 1024, 1);
    rollfileAppender->setLayout(pLayout);
    root.addAppender(rollfileAppender);
    root.setPriority(log4cpp::Priority::DEBUG);
    root.info("Log4cpp init finish.");
}

void LogEvent::exitLog4cpp()
{
    log4cpp::Category::shutdown();
}

bool LogEvent::postLog(const QString &log) {
    root.emerg(log.toLocal8Bit().data());

    if (mObject != NULL) {
        QCoreApplication::postEvent(mObject, new LogEvent((Type)eventType(), log));
        return true;
    } else {
        return false;
    }
}

bool LogEvent::postLog(int level, const QString &log)
{
    switch(level)
    {
    case LOG_DEBUG:
        root.debug(log.toLocal8Bit().data());
        break;
    case LOG_INFO:
        root.info(log.toLocal8Bit().data());
        break;
    case LOG_NOTICE:
        root.notice(log.toLocal8Bit().data());
        break;
    case LOG_WARN:
        root.warn(log.toLocal8Bit().data());
        break;
    case LOG_ERROR:
        root.error(log.toLocal8Bit().data());
        break;
    case LOG_CRIT:
        root.crit(log.toLocal8Bit().data());
        break;
    case LOG_ALERT:
        root.alert(log.toLocal8Bit().data());
        break;
    case LOG_FATAL:
        root.fatal(log.toLocal8Bit().data());
        break;
    default:
        break;
    }

    if (mObject != NULL) {
        if(level > mLogLevel )
            return false;
        QCoreApplication::postEvent(mObject, new LogEvent((Type)eventType(), log));
        return true;
    } else {
        return false;
    }
}

int LogEvent::eventType() {
    return QEvent::User + 1;
}

QString LogEvent::getLog() {
    return mLogString;
}


