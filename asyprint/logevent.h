#ifndef LOGEVENT
#define LOGEVENT

#include <QEvent>
#include <QObject>
#include <QString>

#include <log4cpp/Category.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/RollingFileAppender.hh>

extern log4cpp::Category& root;
class LogEvent: public QEvent {
public:
    enum LogLevel
    {
        LOG_EMERG = 0,
        LOG_FATAL = 0,
        LOG_ALERT = 100,
        LOG_CRIT = 200,
        LOG_ERROR = 300,
        LOG_WARN = 400,
        LOG_NOTICE = 500,
        LOG_INFO = 600,
        LOG_DEBUG = 700,
        LOG_NOTSET = 800
    };

    LogEvent(Type type, const QString &);
    ~LogEvent();

    static int    eventType();
    static bool   postLog(const QString &);
    static bool   postLog(int, const QString &);
    static void   setEventReceiver(QObject *);
    static void   setLogLevel(int level);
    static int    getLogLevel()
    { return mLogLevel; }
    static void   initLog4cpp();
    static void   exitLog4cpp();

    QString getLog();

private:
    QString                 mLogString;
    static QObject        * mObject;
    static int              mLogLevel;
};

#endif // LOGEVENT

