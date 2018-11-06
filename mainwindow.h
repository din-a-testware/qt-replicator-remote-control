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
    QWebSocket *m_webSocket_control;

    QWebSocket *m_webSocket;
    QVector<QStringList> replicationData;

    QSettings settings;

private slots:
    void on_pushButton_clicked();

    void onConnected();

    void onDisconnected();

    void onConnected_recipe();

    void onDisconnected_recipe();

    void populateRecipeList(QVector<QStringList> result);

    void loadRecipe(QVector<QStringList> result);

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

    void on_pushButton_11_clicked();

    void on_button_ShowRecipe_clicked();

    void on_button_ShowIngredients_clicked();

    void on_button_SearchRecipe_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_12_clicked();

    void on_LCARS_PushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
