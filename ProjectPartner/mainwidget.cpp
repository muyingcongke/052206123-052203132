#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "projectitem.h"
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    m_number("052206123"),
    m_password("052203132")
{
    ui->setupUi(this);
    //设置视图
    ui->listWidget->setResizeMode(QListView::Adjust);
    ui->listWidget->setViewMode(QListView::ListMode);
    ui->listWidget->setDragEnabled(false);
    //设置鼠标左键拖动
    QScroller::grabGesture(ui->listWidget, QScroller::LeftMouseButtonGesture);
    ui->stackedWidget->setCurrentIndex(0);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::addPjItem(const QString& pjname,const QString& profile)
{
    ProjectItem* pjItem = new ProjectItem(pjname,profile);
    QListWidgetItem* newItem = new QListWidgetItem;
    newItem->setSizeHint(QSize(400,400));
    ui->listWidget->addItem(newItem);
    ui->listWidget->setItemWidget(newItem,pjItem);
}

void MainWidget::on_main_btn_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWidget::on_project_btn_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWidget::on_login_btn_clicked()
{
    QString number_input = ui->number_lineEdit->text();
    QString password_input = ui->password_lineEdit->text();
    if(isrightful(number_input,password_input))
    {
        ui->stackedWidget->setCurrentIndex(2);
    }
    else
    {
        qDebug() << "input error";
    }

}
bool MainWidget::isrightful(QString number,QString password)
{
    return number == m_number && password == m_password;
}

void MainWidget::on_register_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWidget::on_r_return_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
