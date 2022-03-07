#include "stdafx.h"

#include "window.h"

#ifdef Q_OS_WIN
#include <windows.h>
#endif

Window::Window(QQmlEngine* engine, bool transparent, bool takeFocus, QWidget* parent)
    : QQuickWidget(engine, parent)
{
    this->takeFocus = takeFocus;

    setClearColor(Qt::transparent);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);
#if defined(Q_OS_LINUX)
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
#elif defined(Q_OS_MAC)
    setAttribute(Qt::WA_TransparentForMouseEvents, transparent);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
#else
    setAttribute(Qt::WA_TransparentForMouseEvents, transparent);
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
#endif
}

void Window::setParentWindow(Window* parent, const QPoint& offset)
{
    this->parentWindow = parent;
    this->parentOffset = offset;
    connect(parent->quickWindow(), &QQuickWindow::xChanged,
        this, &Window::repositionToParent);
    connect(parent->quickWindow(), &QQuickWindow::yChanged,
        this, &Window::repositionToParent);
    connect(quickWindow(), &QQuickWindow::visibleChanged,
        this, &Window::repositionToParent);
}

QObject* Window::global()
{
    return dynamic_cast<QQmlApplicationEngine*>(engine())->rootObjects()[0]->property("o").value<QObject*>();
}

void Window::showEvent(QShowEvent* e)
{
    QQuickWidget::showEvent(e);

#ifdef Q_OS_WIN
    if (!takeFocus) {
        HWND hwnd = (HWND)winId();
        auto style = GetWindowLongW(hwnd, GWL_EXSTYLE) | WS_EX_NOACTIVATE;
        SetWindowLongW(hwnd, GWL_EXSTYLE, style);
    }
#endif
}

void Window::repositionToParent()
{
    move(parentWindow->quickWindow()->x() + parentOffset.x(),
        parentWindow->quickWindow()->y() + parentOffset.y());
}
