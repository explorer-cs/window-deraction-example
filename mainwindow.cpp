#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <private/qwidgetresizehandler_p.h>
#include "x11windowmanager.h"
#include "decorator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //禁用主题框架x11窗口管理扩展
    setProperty("useStyleWindowManager", false);

    //初始化QWidgetResizeHandler，禁用其拖拽和缩放功能
    m_resize_handler = new QWidgetResizeHandler(this);
    m_resize_handler->setActive(QWidgetResizeHandler::Move, false);
    m_resize_handler->setActive(QWidgetResizeHandler::Resize, false);
    m_resize_handler->setMovingEnabled(false);

    m_window_manager = new X11WindowManager(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    //FrameLess
    setWindowFlag(Qt::FramelessWindowHint, checked);
    show();
}

void MainWindow::on_checkBox_2_toggled(bool checked)
{
    //gtk border only
    Decorator::wrapWindow(this, checked);
}

void MainWindow::on_checkBox_3_toggled(bool checked)
{
    //x11 window drag move
    if (checked) {
        m_window_manager->registerWidget(this);
    } else {
        m_window_manager->unregisterWidget(this);
    }
}

void MainWindow::on_checkBox_4_toggled(bool checked)
{
    //QWidgetResizeHandler
    m_resize_handler->setActive(QWidgetResizeHandler::Resize, checked);
    m_resize_handler->setMovingEnabled(checked);
}
