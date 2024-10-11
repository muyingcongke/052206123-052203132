#include "useritem.h"
#include "ui_useritem.h"

UserItem::UserItem(const QString& name, const QString& introduction, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserItem)
{
    ui->setupUi(this);
    ui->user_name_label->setText(name);
    ui->user_profile_label->setText(introduction);
}

UserItem::~UserItem()
{
    delete ui;
}
