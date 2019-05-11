#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>

namespace guiutils
{
void centerOnScreen(QWidget* widget)
{
  widget->move(QApplication::desktop()->screen()->rect().center() - widget->rect().center());
}
}
