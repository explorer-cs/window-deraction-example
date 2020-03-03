#ifndef X11WINDOWMANAGER_H
#define X11WINDOWMANAGER_H

#include <QObject>

class X11WindowManager : public QObject
{
    Q_OBJECT
public:
    explicit X11WindowManager(QObject *parent = nullptr);
    bool eventFilter(QObject *watched, QEvent *event) override;

    void registerWidget(QWidget *w);
    void unregisterWidget(QWidget *w);

private:
    bool m_is_draging = false;
    QWidget *m_current_widget = nullptr;
};

#endif // X11WINDOWMANAGER_H
