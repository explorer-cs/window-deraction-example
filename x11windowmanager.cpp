#include "x11windowmanager.h"
#include <QWidget>
#include <QMouseEvent>

#include <QX11Info>
#include <X11/Xlib.h>

X11WindowManager::X11WindowManager(QObject *parent) : QObject(parent)
{

}

bool X11WindowManager::eventFilter(QObject *watched, QEvent *event)
{
    if (!watched->isWidgetType())
        return false;
    switch (event->type()) {
    case QEvent::MouseButtonPress: {
        if (static_cast<QMouseEvent *>(event)->button() == Qt::LeftButton) {
            m_is_draging = true;
            m_current_widget = qobject_cast<QWidget *>(watched);
        }
        break;
    }
    case QEvent::MouseMove: {
        if (m_is_draging) {
            Display *display = QX11Info::display();
            Atom netMoveResize = XInternAtom(display, "_NET_WM_MOVERESIZE", False);
            XEvent xEvent;
            const auto pos = QCursor::pos();

            memset(&xEvent, 0, sizeof(XEvent));
            xEvent.xclient.type = ClientMessage;
            xEvent.xclient.message_type = netMoveResize;
            xEvent.xclient.display = display;
            xEvent.xclient.window = m_current_widget->topLevelWidget()->winId();
            xEvent.xclient.format = 32;
            xEvent.xclient.data.l[0] = pos.x();
            xEvent.xclient.data.l[1] = pos.y();
            xEvent.xclient.data.l[2] = 8;
            xEvent.xclient.data.l[3] = Button1;
            xEvent.xclient.data.l[4] = 0;

            XUngrabPointer(display, CurrentTime);
            XSendEvent(display, QX11Info::appRootWindow(QX11Info::appScreen()),
                       False, SubstructureNotifyMask | SubstructureRedirectMask,
                       &xEvent);
            XFlush(display);

            m_is_draging = false;
        }
        break;
    }
    case QEvent::MouseButtonRelease: {
        m_is_draging = false;
        break;
    }
    default:
        break;
    }
    return false;
}

void X11WindowManager::registerWidget(QWidget *w)
{
    w->removeEventFilter(this);
    w->installEventFilter(this);
}

void X11WindowManager::unregisterWidget(QWidget *w)
{
    w->removeEventFilter(this);
}
