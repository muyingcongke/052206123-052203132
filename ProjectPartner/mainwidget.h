#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QScroller>
#include "projectitem.h"
#include <QDebug>
namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void addPjItem(const QString& pjname,const QString& profile);
    bool isrightful(QString number,QString password);
private slots:
    void on_main_btn_clicked();

    void on_project_btn_clicked();

    void on_login_btn_clicked();

    void on_register_btn_clicked();

    void on_r_return_btn_clicked();

private:
    Ui::MainWidget *ui;
    QString m_number;
    QString m_password;
};

#endif // MAINWIDGET_H
