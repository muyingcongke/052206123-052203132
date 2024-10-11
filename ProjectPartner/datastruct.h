#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#endif // DATASTRUCT_H
#include <QString>
#include <QMetaType>
#include <QList>

#define S_TEXT_LEN 128
#define S_NAME_LEN 128
#define S_PROFILE_LEN 256

#define PJID_MIN 0
#define PJID_MAX 10000


struct Project
{
   int s_id;
   QString s_name;
   QString s_publisher;//发布者（User）的s_number
   QString s_profile;
   QString s_demand;
   QList<QString> s_participators;
   void setData(int id, const QString& name, const QString& publisher,
                const QString& profile, const QString& demand);
};


struct UserInformation
{
    QString s_number;
    QString s_password;
    QString s_name;
    QString s_introduction;
    QString s_status;
    void setData(const QString& number,const QString& password,const QString& name,
                 const QString& introduction,const QString& status);
};

Q_DECLARE_METATYPE(UserInformation)
Q_DECLARE_METATYPE(Project)
