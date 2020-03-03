#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QWidgetResizeHandler;
class X11WindowManager;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_checkBox_toggled(bool checked);

    void on_checkBox_2_toggled(bool checked);

    void on_checkBox_3_toggled(bool checked);

    void on_checkBox_4_toggled(bool checked);

private:
    Ui::MainWindow *ui;

    QWidgetResizeHandler *m_resize_handler;
    X11WindowManager *m_window_manager;
};
#endif // MAINWINDOW_H
