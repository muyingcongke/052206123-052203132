#include "datastruct.h"

void Project::setData(int id, const QString& name, const QString& publisher,
                      const QString& profile, const QString& demand)
{
    s_id = id;
    s_name = name;
    s_publisher = publisher;
    s_profile = profile;
    s_demand = demand;
    s_participators.append(publisher);//将发布者作为参与者第一人
}

void UserInformation::setData(const QString& number,const QString& password,const QString& name,
                              const QString& introduction,const QString& status)
{
    s_number = number;
    s_password = password;
    s_name = name;
    s_introduction = introduction;
    s_status = status;
}
