#include "qrcode/qrencode.h"
#include "qrcode/qrenc.c"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrl>
#include <QDir>
#include <QMenu>
#include <QDebug>
#include <QProcess>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDesktopServices>
#include <QPageSize>
#include <QPdfWriter>
#include <QPagedPaintDevice>
#include <QTime>
#include <QPainter>

#include "myhelper.h"
#include "iconhelper.h"
#include "configapp.h"

static QColor col_white = QColor::fromCmykF(0.0, 0.0, 0.0, 0.0);//white
static QColor col_c = QColor::fromCmykF(1.0, 0.0, 0.0, 0.0);//cycan
static QColor col_m = QColor::fromCmykF(0.0, 1.0, 0.0, 0.0);//magenta
static QColor col_y = QColor::fromCmykF(0.0, 0.0, 1.0, 0.0);//yellow
static QColor col_k = QColor::fromCmykF(0.0, 0.0, 0.0, 1.0);//black
static QColor col_blue = QColor::fromCmyk(1.0, 1.0, 0.0, 0.0);//deep blue

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("ASY Print");
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d), 10);
    IconHelper::Instance()->SetIcon(ui->btnMenu_Min, QChar(0xf068), 10);
//    IconHelper::Instance()->SetIcon(ui->btnMenu, QChar(0xf0c9), 10);
//    IconHelper::Instance()->SetIcon(ui->btnMenu_dir, QChar(0xf07c), 10);

    ui->btnMenu->setVisible(false);
    ui->btnMenu_dir->setVisible(false);

    m_hasPressed = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *)
{

}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap(":icon/main_bg"), QRect());

    QWidget::paintEvent(e);
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        m_hasPressed = true;
        m_lastPressPos = e->globalPos() - this->pos();
        e->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(m_hasPressed && (e->buttons() && Qt::LeftButton))
    {
        move(e->globalPos() - m_lastPressPos);
        e->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    m_hasPressed = false;
}

void MainWindow::on_btnMenu_Min_clicked()
{
    this->showMinimized();
}

void MainWindow::on_btnMenu_Close_clicked()
{
    //提示保存配置TODO
    this->close();
}
