#ifndef MOVEBUTTON_H
#define MOVEBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QMainWindow>

class MoveButton : public QPushButton
{
    Q_OBJECT
private:
    bool m_mousePressed;
    QPoint m_windowsPos;
    QPoint m_mousePos;
    QMainWindow *m_window;

public:
    MoveButton(QWidget *parent = nullptr);

    void setMainWindow(QMainWindow *window);
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
};

#endif // MOVEBUTTON_H
