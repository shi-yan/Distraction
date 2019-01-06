#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QHBoxLayout>

#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QWebEngineFullScreenRequest>
#include <QPropertyAnimation>
#include <QClipboard>
#include <QDebug>
#include <QUrlQuery>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_resizeScale = 2;
    ui->setupUi(this);
    this->setStyleSheet("background-color: black;");
    m_controlBarHeight = 28;

    ui->controlWidget->setVisible(false);

    ui->verticalLayout_2->insertWidget(0, m_webView = new QWebEngineView(this));
    m_webView->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
   // m_webView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //m_webView->setStyleSheet("background-color: black;");
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);


    //m_webView->load(QUrl(QStringLiteral("https://www.youtube.com/embed/aqz-KE-bpKQ")));


    QRect rect = QApplication::desktop()->screenGeometry(this);
    int width = 128*(m_resizeScale+2);
    int height = 72*(m_resizeScale+2);

    //m_webView->setGeometry(0,0,width,height);

    if (ui->controlWidget->isVisible())
    {
        height += m_controlBarHeight;
    }

    setGeometry(rect.width() - 50 - width, 50, width, height);

    connect(ui->resizePushButton, SIGNAL(clicked(bool)), this, SLOT(resizeClicked(bool)) );
    connect(ui->goPushButton, SIGNAL(clicked(bool)), this, SLOT(youtubeClicked(bool)));
    ui->movePushButton->setMainWindow(this);


    setUrl("https://www.youtube.com/watch?v=aqz-KE-bpKQ");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enterEvent(QEvent *e)
{
    int width = 128*(m_resizeScale+2);
    int height = 72*(m_resizeScale+2);

    //if (ui->controlWidget->isVisible())
    {
        height += m_controlBarHeight;
    }
    ui->controlWidget->setVisible(true);

    setGeometry(geometry().x(),geometry().y(), width, height);


    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(150);
    animation->setStartValue(windowOpacity());
    animation->setEndValue(1.0);
    animation->start();

    connect(animation, SIGNAL(finished()), animation, SLOT(deleteLater()));

    setFocus(Qt::MouseFocusReason);
}

void MainWindow::leaveEvent(QEvent *e)
{
    int width = 128*(m_resizeScale+2);
    int height = 72*(m_resizeScale+2);

   // if (ui->controlWidget->isVisible())
    {
       // height += m_controlBarHeight;
    }

    setGeometry(geometry().x(),geometry().y(), width, height);
    ui->controlWidget->setVisible(false);

    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(150);
    animation->setStartValue(windowOpacity());
    animation->setEndValue(0.3);
    animation->start();


    connect(animation, SIGNAL(finished()), animation, SLOT(deleteLater()));
}

void MainWindow::resizeClicked(bool clicked)
{
    m_resizeScale = (--m_resizeScale);

    if (m_resizeScale < 0)
    {
        m_resizeScale = 3;
    }

    int width = 128*(m_resizeScale+2);
    int height = 72*(m_resizeScale+2);

    if (ui->controlWidget->isVisible())
    {
        height += m_controlBarHeight;
    }

    setGeometry(geometry().x(),geometry().y(), width, height);

}

void MainWindow::setUrl(const QString &urlStr)
{
    QUrl url = QUrl::fromUserInput(urlStr);
    QUrlQuery query(url);

    if (url.isValid() && query.hasQueryItem("v") && url.host() == "www.youtube.com")
    {


        QUrl embedLink = QUrl::fromUserInput(QString("https://www.youtube.com/embed/").append(query.queryItemValue("v")));

        ui->addressLineEdit->setText(url.toString());

        m_webView->load(embedLink);
    }
}

void MainWindow::youtubeClicked(bool clicked)
{
    QClipboard *clipboard = QApplication::clipboard();
    QString originalText = clipboard->text();

    setUrl(originalText);
}

