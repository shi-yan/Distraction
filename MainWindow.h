#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QWebEngineFullScreenRequest>
#include <QFocusEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void enterEvent(QEvent *e) override;
    void leaveEvent(QEvent *e) override;

private:
    Ui::MainWindow *ui;
    QWebEngineView *m_webView;
    int m_resizeScale;
    unsigned int m_controlBarHeight;
    void setUrl(const QString &urlStr);

private slots:
    void resizeClicked(bool clicked);
    void youtubeClicked(bool clicked);

};

#endif // MAINWINDOW_H
