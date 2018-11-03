#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebSocket>
#include "lcars_button.h"
#include "lcars_line.h"
#include <QFontDatabase>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <random>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFontDatabase LCARS_fonts;
    LCARS_fonts.addApplicationFont(":/fonts/Helvetica_Ultra_Compressed.ttf");


    //QString defaultIP="127.0.0.1";
    //QString defaultPort="1702";
    //QString defaultBin=QDir::homePath()+"/bin/replicator-server";
    //QString defaultDB=QDir::homePath()+"/replicator-data/databases/replicator_recipes.db";

    /*serverPath=settings.value("serverPath",defaultBin).toString();
    serverPort=settings.value("serverPort",defaultPort).toString();
    serverIP=settings.value("serverIP",defaultIP).toString();
    local_DB=settings.value("local_DB",defaultDB).toString();
    useLocalDb=settings.value("useLocalDB",false).toBool();

    serverURL = "ws://"+serverIP+":"+serverPort;
    */

    //qDebug() << serverURL;

    /*ui->server_ip->setText(serverIP);
    ui->server_port->setText(serverPort);
    ui->server_path->setText(serverPath);
    ui->local_DB->setText(local_DB);
    ui->useLocalFile->setChecked(useLocalDb);
    */

    m_webSocket = new QWebSocket("LCARS Remote Control");
    m_webSocket->ignoreSslErrors();
    connect(m_webSocket, &QWebSocket::connected, this, &MainWindow::onConnected);
    connect(m_webSocket, &QWebSocket::disconnected, this, &MainWindow::onDisconnected);

    connect(m_webSocket, &QWebSocket::textMessageReceived,
                this, &MainWindow::onTextMessageReceived);
        connect(m_webSocket, &QWebSocket::binaryMessageReceived,
                this, &MainWindow::onBinaryMessageRecieved);

    /*if ( m_webSocket->state() == QAbstractSocket::UnconnectedState) {


        m_webSocket->open(QUrl(QString("ws://"+ui->ip_Edit->toPlainText()+":1702").toStdString().c_str()));
        m_webSocket->sendTextMessage("Hi there!");
        qDebug() << (QUrl(QString("ws://"+ui->ip_Edit->toPlainText()+":1702").toStdString().c_str()));
    }*/


    QFont editFont("Helvetica Ultra Compressed",ui->LCARS_Lines_2->height()/3,0,false);
    ui->ip_Edit->setFont(editFont);
    ui->LCARS_Lines_2->setProperty("Size_TopLeft",QSize(ui->LCARS_Lines_2->height()/2,ui->LCARS_Lines_2->height()/2));
    ui->LCARS_Lines_2->setProperty("Size_TopRight",QSize(ui->LCARS_Lines_2->height()/2,ui->LCARS_Lines_2->height()/2));
    ui->LCARS_Lines_2->setProperty("Size_BottomLeft",QSize(ui->LCARS_Lines_2->height()/2,ui->LCARS_Lines_2->height()/2));
    ui->LCARS_Lines_2->setProperty("Size_BottomRight",QSize(ui->LCARS_Lines_2->height()/2,ui->LCARS_Lines_2->height()/2));
    ui->LCARS_Lines_2->setContentsMargins(ui->LCARS_Lines_2->height()/2,0,ui->LCARS_Lines_2->height()/2,0);
    ui->LCARS_Lines_2->update();

    qDebug() << "theme_id" << settings.value("theme_id").toInt();
    int theme_id = settings.value("theme_id").toInt();
    change_color_theme(theme_id);

    QString remote_ip = settings.value("remote_ip").toString();
    if (remote_ip=="") {
        remote_ip="localhost";
        ui->ip_Edit->clear();
        ui->ip_Edit->appendPlainText(remote_ip);
    } else {
        ui->ip_Edit->clear();
        ui->ip_Edit->appendPlainText(remote_ip);
    }

    QList<LCARS_Button *> widget_buttons = this->findChildren<LCARS_Button *>();;
    foreach (LCARS_Button *butt, widget_buttons) {
        if (butt->isEnabled()==true) {
        std::random_device rd;     // only used once to initialise (seed) engine
        std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
        std::uniform_int_distribution<int> uni2(0,99);
        auto random_number = uni2(rng);
        butt->setProperty("Text_Left",QString::number(random_number));
        butt->repaint();
        }
    }
    ui->tab_AppSettings->layout()->update();
    ui->tab_Settings->layout()->update();
    ui->tab_Start->layout()->update();
    ui->system_Tabs->setCurrentWidget(ui->tab_Start);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::change_color_theme(int theme){


    switch (theme) {
    case 0:
    {
        //TNG


        QList<QColor> color_theme;
        color_theme.append(QColor("#ff9900"));
        color_theme.append(QColor("#ffcc99"));
        color_theme.append(QColor("#ff9900"));
        color_theme.append(QColor("#cc6666"));
        color_theme.append(QColor("#ff9900"));
        color_theme.append(QColor("#c59ec9"));
        color_theme.append(QColor("#ff9900"));
        color_theme.append(QColor("#ff9900"));
        color_theme.append(QColor("#ff9900"));
        color_theme.append(QColor("#ff9900"));
        color_theme.append(QColor("#ff9900"));
        color_theme.append(QColor("#ff9900"));
        color_theme.append(QColor("#ff9900"));
        color_theme.append(QColor("#ff9900"));
        color_theme.append(QColor("#ff9900"));
        color_theme.append(QColor("#ff9900"));
        color_theme.append(QColor("#ff9900"));
        color_theme.append(QColor("#ff9900"));
        color_theme.append(QColor("#ff9900"));
        //color_theme_tng.append(QColor("#9c9fba"));

        int min=0;
        int max=color_theme.count()-1;

        std::random_device rd;     // only used once to initialise (seed) engine
        std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
        std::uniform_int_distribution<int> uni(min,max); // guaranteed unbiased


        QList<LCARS_Button *> widget_buttons = this->findChildren<LCARS_Button *>();;


        foreach (LCARS_Button *butt, widget_buttons) {
            auto random_integer = uni(rng);

            int center_rand = random_integer; //generator.bounded(color_theme.count());
            if (butt->isEnabled()==true) {
            butt->setProperty("Center_Color",color_theme.at(center_rand));
            if (butt->property("left_Cut").toBool() == true) {
                butt->setProperty("Edge_Left_Color","#000000");
            } else {
                butt->setProperty("Edge_Left_Color",color_theme.at(center_rand));
            }

            butt->setProperty("Left_Text_Color",QColor("#ffffff"));
            butt->setProperty("Edge_Right_Color",color_theme.at(center_rand));
            butt->setProperty("Divider_Second_Color",color_theme.at(uni(rng)));
            butt->repaint();
            }

        }

    }
        break;
    case 1:
    {
        //NEMESIS
        QList<QColor> color_theme;
        color_theme.append(QColor("#99cdff"));
        color_theme.append(QColor("#3266cc"));
        //color_theme.append(QColor("#000000"));
        color_theme.append(QColor("#3266cc"));
        color_theme.append(QColor("#cdddff"));
        color_theme.append(QColor("#3266cc"));
        color_theme.append(QColor("#99cdff"));
        color_theme.append(QColor("#3266cc"));
        int min=0;
        int max=color_theme.count()-1;

        std::random_device rd;     // only used once to initialise (seed) engine
        std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
        std::uniform_int_distribution<int> uni(min,max); // guaranteed unbiased

        QList<LCARS_Button *> widget_buttons = this->findChildren<LCARS_Button *>();;


        foreach (LCARS_Button *butt, widget_buttons) {
            auto random_integer = uni(rng);

            int center_rand = random_integer; //generator.bounded(color_theme.count());
            if (butt->isEnabled()==true) {
            butt->setProperty("Center_Color",color_theme.at(center_rand));
            if (butt->property("left_Cut").toBool() == true) {
                butt->setProperty("Edge_Left_Color","#000000");
            } else {
                butt->setProperty("Edge_Left_Color",color_theme.at(center_rand));
            }
            butt->setProperty("Left_Text_Color",QColor("#cdddff"));
            butt->setProperty("Edge_Right_Color",color_theme.at(center_rand));
            butt->setProperty("Divider_Second_Color",color_theme.at(uni(rng)));
            }
            butt->repaint();
        }
        break;
    }
    case 2:
    {
        //VOYAGER

        break;
    }
    default:
        break;
    }


    settings.setValue("theme_id",theme);



}

void MainWindow::on_pushButton_clicked()
{
    //m_webSocket->sendTextMessage("hallo");
    if ( m_webSocket->state() == QAbstractSocket::UnconnectedState) {
        //QString tempServerURL="ws://"+ui->server_ip->text()+":"+ui->server_port->text();
        QString tempServerURL="ws://localhost:1702";
        //m_webSocket->open(QUrl(QString("ws://"+ui->ip_Edit->text()+":1702").toStdString().c_str()));
        m_webSocket->open(QUrl(QString("ws://"+ui->ip_Edit->toPlainText()+":1702").toStdString().c_str()));
        m_webSocket->sendTextMessage("Hi there!");
        ui->pushButton->setText("DISCONNECT");
    }
    else {
        m_webSocket->close();
        ui->pushButton->setText("CONNECT");
    }

   }

void MainWindow::onConnected() {

    /*connect(m_webSocket, &QWebSocket::textMessageReceived,
            this, &MainWindow::onTextMessageReceived);
    connect(m_webSocket, &QWebSocket::binaryMessageReceived,
            this, &MainWindow::onBinaryMessageRecieved);
    */
    m_webSocket->sendTextMessage("connect");
    qDebug() << "Running";
}

void MainWindow::onDisconnected() {
    qDebug() << "Disconnected";

}


void MainWindow::onTextMessageReceived(QString message) {
    //ui->ip_Edit_2->setText(message);
    qDebug() << message;
}

void MainWindow::onBinaryMessageRecieved(QByteArray message) {}


void MainWindow::on_button_condBlue_clicked()
{
    m_webSocket->sendTextMessage("alert_blue");
}

void MainWindow::on_button_CondYellow_clicked()
{
    m_webSocket->sendTextMessage("alert_yellow");
}

void MainWindow::on_button_CondRed_clicked()
{
    m_webSocket->sendTextMessage("alert_red");
}

void MainWindow::on_button_Reboot_clicked()
{
    //m_webSocket->sendTextMessage("system_reboot");
    ui->system_Tabs->setCurrentWidget(ui->tab_Settings);
}

void MainWindow::on_button_Shutdown_clicked()
{
    m_webSocket->sendTextMessage("system_shutdown");
}



void MainWindow::on_pushButton_3_clicked()
{
    ui->system_Tabs->setCurrentWidget(ui->tab_Start);
}

void MainWindow::on_button_Close_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_6_clicked()
{
      m_webSocket->sendTextMessage("system_lock");
}

void MainWindow::on_pushButton_5_clicked()
{
    m_webSocket->sendTextMessage("system_shutdown");
}

void MainWindow::on_pushButton_4_clicked()
{
       m_webSocket->sendTextMessage("system_reboot");
}

void MainWindow::on_LCARS_PushButton_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(ui->anim_widget_1, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(ui->anim_widget_1->x(), ui->anim_widget_1->y(), ui->anim_widget_1->width(), 0));
    animation->setEndValue(QRect(ui->anim_widget_1->x(), ui->anim_widget_1->y(), ui->anim_widget_1->width(), this->height()/3));

    animation->start();
}

void MainWindow::on_pushButton_8_clicked()
{
    change_color_theme(0);
}

void MainWindow::on_pushButton_9_clicked()
{
    change_color_theme(1);
}

void MainWindow::on_pushButton_10_clicked()
{
    change_color_theme(2);
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->system_Tabs->setCurrentWidget(ui->tab_Start);
}

void MainWindow::on_button_Settings_clicked()
{
    ui->system_Tabs->setCurrentWidget(ui->tab_AppSettings);
}

void MainWindow::on_ip_Edit_textChanged()
{
    settings.setValue("remote_ip",ui->ip_Edit->toPlainText());
}

void MainWindow::on_pushButton_11_clicked()
{
    m_webSocket->sendTextMessage("close_gui");
}
