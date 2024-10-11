#include "mainwidget.h"


bool MainWidget::openDb()
{
    if(m_db.open())
    {
        return true;
    }
    else
    {
        return false;
    }
}


void MainWidget::createTableUser()
{
    // 用于执行sql语句的对象
    QSqlQuery query(m_db);
    // 构建创建数据库的sql语句字符串
    QString createSql = QString("CREATE TABLE user (\
                          number TEXT PRIMARY KEY NOT NULL,\
                          password TEXT NOT NULL,\
                          name TEXT NOT NULL,\
                          introduction TEXT ,\
                          status TEXT)");
    query.prepare(createSql);
    // 执行sql语句
    if(!query.exec())
    {
        qDebug() << "Error: Fail to create table:User. " << query.lastError();
    }
    else
    {
        qDebug() << "Table:User created!";
    }
}

void MainWidget::createTableProject()
{
    // 用于执行sql语句的对象
    QSqlQuery query(m_db);
    // 构建创建数据库的sql语句字符串
    QString createSql = QString("CREATE TABLE project (\
                          id INTEGER PRIMARY KEY NOT NULL,\
                          Pname TEXT NOT NULL,\
                          number TEXT NOT NULL,\
                          profile TEXT ,\
                          demand TEXT)");
    query.prepare(createSql);
    // 执行sql语句
    if(!query.exec())
    {
        qDebug() << "Error: Fail to create table:Project. " << query.lastError();
    }
    else
    {
        qDebug() << "Table:Project created!";
    }
}

void MainWidget::createTablePParticipation()
{
    // 用于执行sql语句的对象
    QSqlQuery query(m_db);
    // 构建创建数据库的sql语句字符串
    QString createSql = QString("CREATE TABLE pparticipation (\
                          id INTEGER  NOT NULL,\
                          number TEXT NOT NULL,\
                          PRIMARY KEY(id,number),\
                          FOREIGN KEY(id) REFERENCES project(id))");
    query.prepare(createSql);
    // 执行sql语句
    if(!query.exec())
    {
        qDebug() << "Error: Fail to create table:PParticipation. " << query.lastError();
    }
    else
    {
        qDebug() << "Table:PParticipation created!";
    }
}

bool MainWidget::isTableExist(QString& tableName)
{
    QSqlQuery query(m_db);
    QString sql = QString("select * from sqlite_master where name='%1'").arg(tableName);
    query.exec(sql);
    return query.next();
}

void MainWidget::insertUser(const QString &number, const QString &password) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO user (number, password, name) VALUES (:number, :password, :name)");
    query.bindValue(":number", number);
    query.bindValue(":password", password);
    query.bindValue(":name", number);
    if(!query.exec())
    {
        qDebug()<<"Error: Fail to insert. ";
    }
}

void MainWidget::insertProject(const struct Project& project) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO project (id, Pname, number, profile, demand) \
                   VALUES (:id, :Pname, :number, :profile, :demand)");
    query.bindValue(":id", project.s_id);
    query.bindValue(":Pname", project.s_name);
    query.bindValue(":number", project.s_publisher);
    query.bindValue(":profile", project.s_profile);
    query.bindValue(":demand", project.s_demand);
    if(!query.exec())
    {
        qDebug()<<"Error: Fail to insert project. ";
    }

}

void MainWidget::insertPParticipation(const int& id, const QString& participator)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO pparticipation (id, number) \
                   VALUES (:id, :number)");
    query.bindValue(":id", id);
    query.bindValue(":number", participator);
    if(!query.exec())
    {
        qDebug()<<"Error: Fail to insert PParticipation. ";
    }
}

//调试专用查询函数
void MainWidget::queryAllUser() {
    QString sql = "SELECT * FROM user" ; // 组装sql语句
    QSqlQuery query(m_db);                               // [1] 传入数据库连接
    query.exec(sql);                                   // [2] 执行sql语句
    while (query.next()) {                             // [3] 遍历查询结果
        qDebug() << QString("number: %1, password: %2, "
                            "name: %3, introduction: %4")
                    .arg(query.value("number").toString())
                    .arg(query.value("password").toString())
                    .arg(query.value("name").toString())
                    .arg(query.value("introduction").toString());
    }

    sql = "SELECT * FROM project" ;
    query.exec(sql);
    while (query.next()) {
        qDebug() << QString("id: %1, Pname: %2, "
                            "number: %3, profile: %4, demand: %5")
                    .arg(query.value("id").toString())
                    .arg(query.value("Pname").toString())
                    .arg(query.value("number").toString())
                    .arg(query.value("profile").toString())
                    .arg(query.value("demand").toString());
    }

    sql = "SELECT * FROM pparticipation" ;
    query.exec(sql);
    while (query.next()) {
        qDebug() << QString("id: %1, number: %2 ")
                    .arg(query.value("id").toString())
                    .arg(query.value("number").toString());
    }

    sql = "SELECT * FROM pparticipation WHERE id=6981" ;
    query.exec(sql);
    while (query.next())
    {
        qDebug() << QString("id: %1, number: %2 ")
                    .arg(query.value("id").toString())
                    .arg(query.value("number").toString()) << "another";
    }

}


