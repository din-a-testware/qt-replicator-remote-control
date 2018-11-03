#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWebSocket>
#include <QMainWindow>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QWebSocket *m_webSocket;



    QSettings settings;

private slots:
    void on_pushButton_clicked();
    void onConnected();

    void onDisconnected();

    void change_color_theme(int theme);

    void onTextMessageReceived(QString message);

    void onBinaryMessageRecieved(QByteArray message);

    void on_button_condBlue_clicked();

    void on_button_CondYellow_clicked();

    void on_button_CondRed_clicked();

    void on_button_Reboot_clicked();

    void on_button_Shutdown_clicked();

    void on_pushButton_3_clicked();

    void on_button_Close_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_LCARS_PushButton_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_7_clicked();

    void on_button_Settings_clicked();

    void on_ip_Edit_textChanged();

    void on_pushButton_11_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
