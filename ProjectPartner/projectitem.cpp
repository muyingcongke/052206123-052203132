#include "projectitem.h"
#include "ui_projectitem.h"

ProjectItem::ProjectItem(const QString& pjname,const QString& profile,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectItem)
{
    ui->setupUi(this);
    ui->pj_name_label->setText(pjname);
    ui->pj_profile_label->setText(profile);
}

ProjectItem::~ProjectItem()
{
    delete ui;
}
