#ifndef CONFIGAPP_H
#define CONFIGAPP_H
#include <QString>
#include <QSettings>
#include <QFile>
#include <QCoreApplication>
#include <QMap>
#include <QTimer>
#include <Windows.h>

#define Warning(a, ...)     qWarning("Warning: %s(%d) : "a,  __FILE__, __LINE__, ##__VA_ARGS__)
#define Debug(a, ...)       qDebug("Debug: %s(%d) : "a,  __FILE__, __LINE__, ##__VA_ARGS__)
#define Critical(a, ...)    qCritical("Critical: %s(%d) : "a,  __FILE__, __LINE__, ##__VA_ARGS__)
#define Fatal(a, ...)       qFatal("Fatal: %s(%d) : "a,  __FILE__, __LINE__, ##__VA_ARGS__)

class ConfigApp
{
public:
    static bool BAutoRunUpdate;
    static bool BIsAutoRun;             //程序开机自启动
    static bool BIsStartHotspot;        //热点
    static bool BIsRegistered;          //是否注册
    static QString AppName;             //应用程序英文名称
    static QString ConfigPath;          //缓存路径
    static QString LocalHostName;       //PC用户名
    static QString ConnectPwd;
    static QString Language;

    static QString UniqueId;
    static QString RecvFileDir;

    static QStringList  RecvFileList;
    static int          RecvFileNum;

    static int PostilMode;
    static int RtmpQuality;


    static void initApp();
    static void ReadDefaultLanguage();  //读取默认配置文件，载入安装时选择的语言
    static void ReadConfig();           //读取配置文件,在main函数最开始加载程序载入
    static void WriteConfig();          //写入配置文件,在更改配置文件程序关闭时调用
    static void WriteJson();            //写入json配置文件

    //asy
    static int     page_dpi;           //纸张DPI
    static qreal   page_width;         //纸张长
    static qreal   page_height;        //纸张高
    static int     num_per_row;        //纸张每行图标数
    static int     num_per_col;        //纸张每列图标数

    static qreal   margin_top;         //纸张上边距
    static qreal   margin_bottom;      //纸张下边距
    static qreal   margin_left;        //纸张左边距
    static qreal   margin_right;       //纸张右边距

    static float   item_width;         //图标对象宽
    static float   item_height;        //图标对象高
    static float   item_spacing;       //图标对象间隔
    static float   qrdX;               //qr在对象中的偏移X
    static float   qrdY;               //qr在对象中的偏移Y
    static bool    bIsHorizon;         //是否按横向排列图标

    static float   qrWidthMM;          //qr的大小，正方形

    static int     numberColorMode;    //qr下数字颜色模式   0 全黑，1 间隔1个变更颜色 2 其他
    static QColor  number_color1;      //qr下数字颜色1 ***所有颜色都以CMYK颜色模式呈现
    static QColor  number_color2;      //qr下数字颜色2
    static QColor  number_color3;      //qr下数字颜色3
    static QColor  number_color4;      //qr下数字颜色4

    static QColor  qr_topleft_color;          //qr左上颜色
    static QColor  qr_topright_color;         //qr右上颜色
    static QColor  qr_bottomleft_color;       //qr左下颜色
    static QColor  qr_bottomright_color;      //qr右下颜色

    static bool    bKeyBGColor;        //是否绘制key背景颜色框
    static QColor  key_color;          //key颜色
    static QColor  midKey_color;       //qr中间的key颜色

    //暂不使用
    static int      key_pos1;           //第一排第n位
    static int      key_pos2;           //第二排第n位
    static int      numberLen;          //qr下数字长度，默认16 一般不做变更
    static float    numberX;            //qr下数字X轴偏移，一般不做变更
    static float    numberY;            //qr下数字Y轴偏移，一般不做变更
    static float    numberSpace;        //qr下数字间隔，一般不做变更
};

class Extensions
{
public:
    Extensions();
    ~Extensions();

    QStringList image()
    { return m_image; }
    QStringList video()
    { return m_video; }
    QStringList audio()
    { return m_audio; }

protected:
    QStringList m_image;
    QStringList m_video;
    QStringList m_audio;
};


class QCustomTimer : public QObject
{
    Q_OBJECT
public:
    explicit QCustomTimer(QObject *parent = 0);
    ~QCustomTimer();

private:
    QTimer      *m_pTimer;       //定时器对象
    QThread     *m_pTimerThread; //定时器依赖线程

signals:
    void startSignal( int nMsc );//开启定时器信号
    void stopSignal();           //停止定时器信号
    void TimeOut();              //定时器触发，外部需连接此信号
    void deletelater();          //延时删除定时器信号
public slots:
    void onTimer();              //对象内部定时触发槽函数，向外部发射定时器触发信号
public:
    void StartTimer( int nMsc ); //开启定时器
    void StopTimer();            //关闭定时器
    void DeleteLater();          //延时删除定时器对象
    bool IsActive();
};

#endif // CONFIGAPP_H


