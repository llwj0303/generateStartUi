#include "configapp.h"
#include <QDir>
#include <QtCore>
#include <QProcess>
#include <QApplication>
#include <QColor>

bool ConfigApp::BAutoRunUpdate = true;
bool ConfigApp::BIsAutoRun = false;
bool ConfigApp::BIsStartHotspot = false;
bool ConfigApp::BIsRegistered = false;
QString ConfigApp::Language = "zh_CN";
QString ConfigApp::ConfigPath = "";

QString ConfigApp::AppName = "asypic";

QString ConfigApp::RecvFileDir = "";

int ConfigApp::RecvFileNum = 0;
int ConfigApp::PostilMode = 0x00;
int ConfigApp::RtmpQuality = 1;

//ASY 单位mm
int     ConfigApp::page_dpi = 300;             //纸张DPI
qreal   ConfigApp::page_width = 210.0;         //纸张长
qreal   ConfigApp::page_height = 297.0;        //纸张高
int     ConfigApp::num_per_row = 7;
int     ConfigApp::num_per_col = 16;

qreal   ConfigApp::margin_top = 0.0;         //纸张上边距
qreal   ConfigApp::margin_bottom = 0.0;      //纸张下边距
qreal   ConfigApp::margin_left = 0.0;        //纸张左边距
qreal   ConfigApp::margin_right = 0.0;       //纸张右边距

float   ConfigApp::item_width = 28.0;         //图标对象宽
float   ConfigApp::item_height = 18.0;        //图标对象高
float   ConfigApp::item_spacing = 0;          //图标对象间隔
float   ConfigApp::qrdX = 2.5;               //qr在对象中的偏移X
float   ConfigApp::qrdY = 4.5;               //qr在对象中的偏移Y
bool    ConfigApp::bIsHorizon = true;        //是否按横向排列图标

float   ConfigApp::qrWidthMM = 8.0;            //qr的大小，正方形
int     ConfigApp::numberLen = 16;           //qr下数字长度，默认16
float   ConfigApp::numberX = 8.0;            //qr下数字X轴偏移，一般不做变更
float   ConfigApp::numberY = 8.0;            //qr下数字Y轴偏移，一般不做变更
float   ConfigApp::numberSpace = 8.0;        //qr下数字间隔，一般不做变更

int     ConfigApp::numberColorMode = 0;    //qr下数字颜色模式   0 全黑，1 间隔1个变更颜色 2 其他
//QColor  ConfigApp::number_color1 = QColor::fromCmyk(0, 0, 0, 255);//black      //qr下数字颜色1 ***所有颜色都以CMYK颜色模式呈现
//QColor  ConfigApp::number_color2 = QColor::fromCmyk(0, 0, 0, 255);//black      //qr下数字颜色2
//QColor  ConfigApp::number_color3 = QColor::fromCmyk(0, 0, 0, 255);//black      //qr下数字颜色3
//QColor  ConfigApp::number_color4 = QColor::fromCmyk(0, 0, 0, 255);//black      //qr下数字颜色4

QColor  ConfigApp::number_color1 = QColor::fromCmykF(0.0, 0.0, 0.0, 1.0);//black      //qr下数字颜色1 ***所有颜色都以CMYK颜色模式呈现
QColor  ConfigApp::number_color2 = QColor::fromCmykF(0.0, 0.0, 0.0, 1.0);//black      //qr下数字颜色2
QColor  ConfigApp::number_color3 = QColor::fromCmykF(0.0, 0.0, 0.0, 1.0);//black      //qr下数字颜色3
QColor  ConfigApp::number_color4 = QColor::fromCmykF(0.0, 0.0, 0.0, 1.0);//black      //qr下数字颜色4

//QColor  ConfigApp::qr_topleft_color = QColor::fromCmyk(0, 0, 0, 255);//black          //qr左上颜色
//QColor  ConfigApp::qr_topright_color = QColor::fromCmyk(0, 0, 0, 255);//black          //qr右上颜色
//QColor  ConfigApp::qr_bottomleft_color = QColor::fromCmyk(0, 0, 0, 255);//black          //qr左下颜色
//QColor  ConfigApp::qr_bottomright_color = QColor::fromCmyk(0, 0, 0, 255);//black          //qr右下颜色

QColor  ConfigApp::qr_topleft_color = QColor::fromCmykF(0.0, 0.0, 0.0, 1.0);//black          //qr左上颜色
QColor  ConfigApp::qr_topright_color = QColor::fromCmykF(0.0, 0.0, 0.0, 1.0);//black          //qr右上颜色
QColor  ConfigApp::qr_bottomleft_color = QColor::fromCmykF(0.0, 0.0, 0.0, 1.0);//black          //qr左下颜色
QColor  ConfigApp::qr_bottomright_color = QColor::fromCmykF(0.0, 0.0, 0.0, 1.0);//black          //qr右下颜色

bool    ConfigApp::bKeyBGColor = true;          //是否绘制key背景颜色框
//QColor  ConfigApp::key_color = QColor::fromCmyk(0, 0, 0, 0);//white            //key颜色
//QColor  ConfigApp::midKey_color = QColor::fromCmyk(255, 255, 0, 0);//blue      //midkey颜色

QColor  ConfigApp::key_color = QColor::fromCmykF(0.0, 0.0, 0.0, 0.0);//white            //key颜色
QColor  ConfigApp::midKey_color = QColor::fromCmykF(1.0, 1.0, 0.0, 0.0);//blue      //midkey颜色

int     ConfigApp::key_pos1 = 6;//第一排第n位 pos1/pos2必须有一个是0
int     ConfigApp::key_pos2 = 0;//第二排第n位


void ConfigApp::initApp()
{
    ConfigPath = (QDir::homePath() + "/.ASY");
    RecvFileDir = QDir::tempPath() + "/RecvFiles";
//    Debug("RecvFileDir: %s", RecvFileDir);
    ReadConfig();
}

void ConfigApp::ReadDefaultLanguage()
{
    QSettings set(QApplication::applicationDirPath() + "/" + "config.ini", QSettings::IniFormat);
    set.beginGroup("General");
    Language = set.value("Language", Language).toString();
    set.endGroup(); // General
}

void ConfigApp::ReadConfig()
{
//    ReadDefaultLanguage();

    QString fileName = QString("%1/%2/%2_Config.ini").arg(ConfigPath).arg(AppName);
    qDebug()<<"***ReadConfig*** "<<fileName;
    //如果配置文件大小为0,则以初始值继续运行,并生成配置文件
    QFile file(fileName);
    if (file.size() == 0) {
        WriteConfig();
        WriteJson();
        return;
    }
    file.close();

    QSettings *set = new QSettings(fileName, QSettings::IniFormat);
    set->beginGroup("ConfigApp");
    ConfigApp::page_dpi = set->value("page_dpi").toInt();
    ConfigApp::page_width = set->value("page_width").toDouble();
    ConfigApp::page_height = set->value("page_height").toDouble();
    ConfigApp::num_per_row = set->value("num_per_row").toInt();
    ConfigApp::num_per_col = set->value("num_per_col").toInt();

    ConfigApp::margin_top = set->value("margin_top").toDouble();
    ConfigApp::margin_bottom = set->value("margin_bottom").toDouble();
    ConfigApp::margin_left = set->value("margin_left").toDouble();
    ConfigApp::margin_right = set->value("margin_right").toDouble();

    ConfigApp::item_width = set->value("item_width").toFloat();
    ConfigApp::item_height = set->value("item_height").toFloat();
    ConfigApp::item_spacing = set->value("item_spacing").toFloat();
    ConfigApp::qrdX = set->value("qrdX").toFloat();
    ConfigApp::qrdY = set->value("qrdY").toFloat();
    ConfigApp::bIsHorizon = set->value("bIsHorizon").toBool();

    ConfigApp::qrWidthMM = set->value("qrWidthMM").toFloat();

    ConfigApp::bKeyBGColor = set->value("bKeyBGColor").toBool();

    ConfigApp::number_color1 = set->value("number_color1").value<QColor>();
    ConfigApp::number_color2 = set->value("number_color2").value<QColor>();
    ConfigApp::number_color3 = set->value("number_color3").value<QColor>();
    ConfigApp::number_color4 = set->value("number_color4").value<QColor>();

    ConfigApp::qr_topleft_color = set->value("qr_topleft_color").value<QColor>();
    ConfigApp::qr_topright_color = set->value("qr_topright_color").value<QColor>();
    ConfigApp::qr_bottomleft_color = set->value("qr_bottomleft_color").value<QColor>();
    ConfigApp::qr_bottomright_color = set->value("qr_bottomright_color").value<QColor>();

    ConfigApp::key_color = set->value("key_color").value<QColor>();
    ConfigApp::midKey_color = set->value("midKey_color").value<QColor>();

    set->endGroup();
    delete set;//vld
}

void ConfigApp::WriteConfig()
{
    QString fileName = QString("%1/%2/%2_Config.ini").arg(ConfigPath).arg(AppName);
    qDebug()<<"***WriteConfig*** "<<fileName;

    QSettings set(fileName, QSettings::IniFormat);
    set.beginGroup("ConfigApp");
    set.setValue("page_dpi", page_dpi);
    set.setValue("page_width", page_width);
    set.setValue("page_height", page_height);
    set.setValue("num_per_row", num_per_row);
    set.setValue("num_per_col", num_per_col);

    set.setValue("margin_top", margin_top);
    set.setValue("margin_bottom", margin_bottom);
    set.setValue("margin_left", margin_left);
    set.setValue("margin_right", margin_right);

    set.setValue("item_width", item_width);
    set.setValue("item_height", item_height);
    set.setValue("item_spacing", item_spacing);
    set.setValue("qrdX", qrdX);
    set.setValue("qrdY", qrdY);
    set.setValue("bIsHorizon", bIsHorizon);

    set.setValue("qrWidthMM", qrWidthMM);
    set.setValue("numberColorMode", numberColorMode);
    set.setValue("number_color1", number_color1);
    set.setValue("number_color2", number_color2);
    set.setValue("number_color3", number_color3);
    set.setValue("number_color4", number_color4);

    set.setValue("qr_topleft_color", qr_topleft_color);
    set.setValue("qr_topright_color", qr_topright_color);
    set.setValue("qr_bottomleft_color", qr_bottomleft_color);
    set.setValue("qr_bottomright_color", qr_bottomright_color);

    set.setValue("bKeyBGColor", bKeyBGColor);
    set.setValue("key_color", key_color);
    set.setValue("midKey_color", midKey_color);
    set.endGroup();
}

void ConfigApp::WriteJson()
{
    QString fileName = QString("%1/%2/%2_Config.json").arg(ConfigPath).arg(AppName);
    qDebug()<<"***WriteJson*** "<<fileName;

    //打开文件
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)) {
        qDebug() << "File open failed!";
    } else {
        qDebug() <<"File open successfully!";
    }

    QJsonDocument jdoc;
    QJsonObject obj;
    QJsonArray arr;

    //添加节点
    obj["page_dpi"] =page_dpi;
    obj["page_width"] =page_width;
    obj["page_height"] =page_height;
    obj["num_per_row"] =num_per_row;
    obj["num_per_col"] =num_per_col;

    obj["margin_top"] =margin_top;
    obj["margin_bottom"] =margin_bottom;
    obj["margin_left"] =margin_left;
    obj["margin_right"] =margin_right;

    obj["item_width"] =item_width;
    obj["item_height"] =item_height;
    obj["item_spacing"] =item_spacing;
    obj["qrdX"] =qrdX;
    obj["qrdY"] =qrdY;
    obj["bIsHorizon"] = bIsHorizon;

    obj["qrWidthMM"] =qrWidthMM;
    obj["numberColorMode"] =numberColorMode;
    obj["bKeyBGColor"] =bKeyBGColor;

    QJsonObject Member;     //定义数组成员
    Member["cyan"] = number_color1.cyan();
    Member["magenta"] = number_color1.magenta();
    Member["yellow"] = number_color1.yellow();
    Member["black"] = number_color1.black();
    arr.append(Member);
    obj["number_color1"] = arr;
    for(int i=0;i<arr.size();i++)
    {
        arr.removeAt(i);
    }

    Member["cyan"] = number_color2.cyan();
    Member["magenta"] = number_color2.magenta();
    Member["yellow"] = number_color2.yellow();
    Member["black"] = number_color2.black();
    arr.append(Member);
    obj["number_color2"] = arr;
    for(int i=0;i<arr.size();i++)
    {
        arr.removeAt(i);
    }

    Member["cyan"] = number_color3.cyan();
    Member["magenta"] = number_color3.magenta();
    Member["yellow"] = number_color3.yellow();
    Member["black"] = number_color3.black();
    arr.append(Member);
    obj["number_color3"] = arr;
    for(int i=0;i<arr.size();i++)
    {
        arr.removeAt(i);
    }

    Member["cyan"] = number_color4.cyan();
    Member["magenta"] = number_color4.magenta();
    Member["yellow"] = number_color4.yellow();
    Member["black"] = number_color4.black();
    arr.append(Member);
    obj["number_color4"] = arr;
    for(int i=0;i<arr.size();i++)
    {
        arr.removeAt(i);
    }

    Member["cyan"] = qr_topleft_color.cyan();
    Member["magenta"] = qr_topleft_color.magenta();
    Member["yellow"] = qr_topleft_color.yellow();
    Member["black"] = qr_topleft_color.black();
    arr.append(Member);
    obj["qr_topleft_color"] = arr;
    for(int i=0;i<arr.size();i++)
    {
        arr.removeAt(i);
    }

    Member["cyan"] = qr_topright_color.cyan();
    Member["magenta"] = qr_topright_color.magenta();
    Member["yellow"] = qr_topright_color.yellow();
    Member["black"] = qr_topright_color.black();
    arr.append(Member);
    obj["qr_topright_color"] = arr;
    for(int i=0;i<arr.size();i++)
    {
        arr.removeAt(i);
    }

    Member["cyan"] = qr_bottomleft_color.cyan();
    Member["magenta"] = qr_bottomleft_color.magenta();
    Member["yellow"] = qr_bottomleft_color.yellow();
    Member["black"] = qr_bottomleft_color.black();
    arr.append(Member);
    obj["qr_bottomleft_color"] = arr;
    for(int i=0;i<arr.size();i++)
    {
        arr.removeAt(i);
    }

    Member["cyan"] = qr_bottomright_color.cyan();
    Member["magenta"] = qr_bottomright_color.magenta();
    Member["yellow"] = qr_bottomright_color.yellow();
    Member["black"] = qr_bottomright_color.black();
    arr.append(Member);
    obj["qr_bottomright_color"] = arr;
    for(int i=0;i<arr.size();i++)
    {
        arr.removeAt(i);
    }

    Member["cyan"] = key_color.cyan();
    Member["magenta"] = key_color.magenta();
    Member["yellow"] = key_color.yellow();
    Member["black"] = key_color.black();
    arr.append(Member);
    obj["key_color"] = arr;
    for(int i=0;i<arr.size();i++)
    {
        arr.removeAt(i);
    }

    Member["cyan"] = midKey_color.cyan();
    Member["magenta"] = midKey_color.magenta();
    Member["yellow"] = midKey_color.yellow();
    Member["black"] = midKey_color.black();
    arr.append(Member);
    obj["midKey_color"] = arr;
    for(int i=0;i<arr.size();i++)
    {
        arr.removeAt(i);
    }

    jdoc.setObject(obj);
    file.write(jdoc.toJson(QJsonDocument::Indented)); //Indented:表示自动添加/n回车符
    file.close();
}



//***********************************************************************
Extensions::Extensions()
{
    m_image << "PNG" << "JPG" << "JPEG" << "TIFF" << "TIF" << "WEBP";
    m_video << "avi" << "vfw" << "divx"
           << "mpg" << "mpeg" << "m1v" << "m2v" << "mpv" << "dv" /*<< "3gp"*/
           << "mov" << "mp4" << "m4v" << "mqv"
           << "dat" << "vcd"
           << "ogg" << "ogm" << "ogv"
           << "asf" << "wmv"
           << "bin" << "iso" << "vob"
           << "mkv" << "nsv" << "ram" << "flv"
           << "rm"
           << "ts" << "rmvb" << "dvr-ms" << "m2t" << "m2ts" << "rec";
    m_audio << "mp3" << "ogg" << "wav" << "wma" <<  "ac3" << "ra" << "ape" << "flac";
}

Extensions::~Extensions() {
}

//***********************************************
QCustomTimer::QCustomTimer(QObject *parent) :
    QObject(parent)
{
    m_pTimerThread = new QThread;
    m_pTimer = new QTimer;
    m_pTimer->setSingleShot(true);//单次触发
    m_pTimer->moveToThread(m_pTimerThread);//更改定时器运行的线程
    m_pTimerThread->start();

    connect( m_pTimer, SIGNAL(timeout()), this, SLOT(onTimer()) , Qt::DirectConnection);
    connect( this, SIGNAL(startSignal(int)), m_pTimer, SLOT(start(int)), Qt::BlockingQueuedConnection);
    connect( this, SIGNAL(stopSignal()), m_pTimer, SLOT(stop()), Qt::BlockingQueuedConnection);
}

QCustomTimer::~QCustomTimer()
{
    Debug("Destroyed QCustomTimer Begin");
//    m_pTimerThread->exit(0);
    if(m_pTimer)
    {
        delete m_pTimer;
        m_pTimer = NULL;
    }
    if(m_pTimerThread){
        disconnect(m_pTimerThread);
        m_pTimerThread->quit();
        m_pTimerThread->wait();
//        delete m_pTimerThread;
//        m_pTimerThread = NULL;
    }
    Debug("Destroyed QCustomTimer end");
}

void QCustomTimer::onTimer()
{
    emit TimeOut();//发射定时器触发信号
}

void QCustomTimer::StartTimer(int nMsc)
{
    emit startSignal(nMsc);//向子线程内的定时器发送开启定时器信号
}

void QCustomTimer::StopTimer()
{
    emit stopSignal();//向子线程内的定时器发送停止定时器信号
}

bool QCustomTimer::IsActive()
{
    return m_pTimer->isActive();
}
