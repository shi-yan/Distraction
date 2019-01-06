#include "MoveButton.h"

MoveButton::MoveButton(QWidget *parent)
    :QPushButton(parent)
{

}

void MoveButton::setMainWindow(QMainWindow *window)
{
    m_window = window;
}


void MoveButton::mousePressEvent(QMouseEvent *e)
{
    m_mousePressed = true;
    m_mousePos = e->globalPos();

    //QWidget *parent = parentWidget();
    //if (parent)
     // parent = parent->parentWidget();

    if (m_window)
      m_windowsPos = m_window->pos();
}

void MoveButton::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    m_mousePressed = false;
}

void MoveButton::mouseMoveEvent(QMouseEvent *e)
{
    //QWidget *parent = parentWidget();
   //  if (parent)
     //  parent = parent->parentWidget();

     if (m_window && m_mousePressed)
       m_window->move(m_windowsPos + (e->globalPos() - m_mousePos));
}
