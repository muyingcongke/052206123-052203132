#ifndef PROJECTITEM_H
#define PROJECTITEM_H

#include <QWidget>

namespace Ui {
class ProjectItem;
}

class ProjectItem : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectItem(const QString& pjname,const QString& profile,QWidget *parent = nullptr);
    ~ProjectItem();

private:
    Ui::ProjectItem *ui;

};

#endif // PROJECTITEM_H
