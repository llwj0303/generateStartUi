/*  说明:全局辅助操作类实现文件
 *  功能:窗体显示/编码设置/开机启动/文件选择与复制/对话框等
 *1.设置为开机启动
 *2.设置编码为UTF8
 *3.设置皮肤qss样式
 *4.加载中文字符
 *5.判断是否是IP地址
 *6.显示信息框,仅确定按钮
 *7.显示错误框,仅确定按钮
 *8.显示询问框,确定和取消按钮
 *9.延时 n 秒
 *10.窗体在屏幕上居中显示
 *11.获取设备分辨率的信息，参数输出
 *12.载入当前目录下的指定文件readall
 *13.各类进制转换
 *14.设置系统日期时间
 *15.获取选择的文件
 *16.获取选择的文件夹下所有文件集合
 *17.获取选择的目录
 *18.获取文件名,含拓展名
 *19.获取选择文件夹中过滤得到的files
 *20.判断文件夹是否存在
 *21.判断文件是否存在
 *22.复制文件,返回bool
 *23.异或加密算法,返回加密结果
 *24.检查指定ip是否在线
 *25.Qt调用wmi查询设备信息
 *26.获取指定文件MD5码
 *27.递归拷贝文件夹
 *28.递归删除文件夹
 *29.将某文件格式与本程序关联
 *30.获取htm文件编码格式
 *31.QString 转 char*
 *32.获取a到b之间的随机数
 *33.QByteArray 转 QString(Hex) 
 *34.QString(Hex)转 QByteArray
 *35.字符串QString转为十六进制数Hex 
 **/
#ifndef MYHELPER_H
#define MYHELPER_H

#include <QtCore>
#include <QtGui>
#include <QEventLoop>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QCryptographicHash>
#include <QApplication>
#include <QDir>

class myHelper: public QObject
{

public:

    //窗体居中显示
    static void FormInCenter(QWidget *frm)
    {
        int frmX = frm->width();
        int frmY = frm->height();
        QDesktopWidget w;
        int deskWidth = w.width();
        int deskHeight = w.height();
        QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
        frm->move(movePoint);
    }

    //窗体在父窗口居中显示
    static void FormInPCenter(QWidget *frm, QWidget *pFrm)
    {
        int frmX = frm->width();
        int frmY = frm->height();

        int pWidth = pFrm->width();
        int pHeight = pFrm->height();
        QPoint movePoint(pWidth / 2 - frmX / 2, pHeight / 2 - frmY / 2);
        frm->move(movePoint);
    }

    //判断文件夹是否存在,不存在则创建
    static bool isDirExist(QString fullPath)
    {
        QDir dir(fullPath);
        if(dir.exists())
        {
          return true;
        }
        else
        {
           bool ok = dir.mkdir(fullPath);//只创建一级子目录，即必须保证上级目录存在
           return ok;
        }
    }

    //保留小数点后n位 2 or 6
    static float GetDecimal(float in, int n)
    {
        if(n == 2)
        {
            return (float)((int)(in*100 + 0.5)) / 100.0;
        }
        else if(n == 6)
        {
            return (float)((int)(in*1000000 + 0.5)) / 1000000.0;
        }
    }

    //设置皮肤样式
    static void SetStyle(const QString &styleName)
    {
        QFile file(QString(":/icon/%1.css").arg(styleName));
        file.open(QFile::ReadOnly);
        QString qss = QLatin1String(file.readAll());
        qApp->setStyleSheet(qss);
        qApp->setPalette(QPalette(QColor("#F0F0F0")));
    }

    //28.递归删除文件夹
    static void clearTempFiles(const QString& path)
    {
        QDir Dir(path);
        if(!Dir.exists())
        {
            return;
        }

        // 第三个参数是QDir的过滤参数，这三个表示收集所有文件和目录，且不包含"."和".."目录。
        // 因为只需要遍历第一层即可，所以第四个参数填QDirIterator::NoIteratorFlags
        QDirIterator DirsIterator(path, QDir::Files);
        while(DirsIterator.hasNext())
        {
            Dir.remove(DirsIterator.next());
        }
    }

    static void Delay_MSec(unsigned int msec)
    {
        QEventLoop loop;//定义一个新的事件循环
        QTimer::singleShot(msec, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
        loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
    }
};

#endif // MYHELPER_H
