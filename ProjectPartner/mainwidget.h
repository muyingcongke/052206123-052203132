#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QScroller>
#include "projectitem.h"
#include <QDebug>
#include <QListWidgetItem>
#include "datastruct.h"
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QRandomGenerator>
#include <QVector>
#include "useritem.h"
namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void addPjItemToMain(const struct Project& project);
    void addPjItemToProject(const struct Project& project);
    bool isrightful(QString number,QString password);
    void init();//初始化数据库内容、测试信息
    bool openDb();// 打开数据库
    void createTableUser();
    bool isTableExist(QString& tableName);
    void queryAllUser();
    void insertUser(const QString &number, const QString &password);
    void insertProject(const struct Project& project);
    void myinfoLoad();
    void createTableProject();
    void createTablePParticipation();
    void MainPJLoad();
    void MyPJLoad();
    void insertPParticipation(const int& id, const QString& userNumber);
    void addParticipatorItemProject(const struct UserInformation& user);
private slots:
    void on_main_btn_clicked();

    void on_project_btn_clicked();

    void on_login_btn_clicked();

    void on_register_btn_clicked();

    void on_r_return_btn_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_returnTOmain_btn_clicked();

    void on_launch_btn_clicked();

    void on_l_returnTOmain_btn_clicked();

    void on_l_launch_btn_clicked();

    void on_r_register_btn_clicked();

    void on_myinfo_btn_clicked();

    void on_d_edit_btn_clicked();

    void on_update_btn_clicked();

private:
    Ui::MainWidget *ui;
    QString m_number;
    QString m_password;
    QString m_pjCount;
    QSqlDatabase m_db;
};

#endif // MAINWIDGET_H
