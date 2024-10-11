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
    ui->listWidget_2->setResizeMode(QListView::Adjust);
    ui->listWidget_2->setViewMode(QListView::ListMode);
    ui->listWidget_2->setDragEnabled(false);
    //设置鼠标左键拖动
    QScroller::grabGesture(ui->listWidget, QScroller::LeftMouseButtonGesture);
    QScroller::grabGesture(ui->listWidget_2, QScroller::LeftMouseButtonGesture);
    ui->stackedWidget->setCurrentIndex(0);

    //数据库连接
    if (QSqlDatabase::contains("ProjectPartner"))
    {
        m_db = QSqlDatabase::database("ProjectPartner");
        qDebug() << "link";
    }
    else
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE","ProjectPartner");// 建立和SQlite数据库的连接
        m_db.setDatabaseName("ProjectPartner.db");// 设置数据库文件的名字
        qDebug() << "create";
    }
    if (!m_db.open())
    {
        qDebug() << "Error: Failed to open database." ;
    }
    else
    {
        qDebug() << "open succeed!";
    }

}

MainWidget::~MainWidget()
{
    m_db.close();
    delete ui;
}

void MainWidget::init()
{
    QString str = "user";

    if(!isTableExist(str))
    {
        //创建user表-个人信息
        createTableUser();
    }
    else
    {
        qDebug() << "skip create user";
    }
    str = "project";
    if(!isTableExist(str))
    {
        //创建project表-项目信息
        createTableProject();
    }
    else
    {
        qDebug() << "skip create project";
    }
    str = "pparticipation";
    if(!isTableExist(str))
    {
        //创建pparticipation表- 项目-参与者
        createTablePParticipation();
    }
    else
    {
        qDebug() << "skip create pparticipation";
    }
}

void MainWidget::addPjItemToMain(const struct Project& project)
{
    QListWidgetItem* newItem = new QListWidgetItem;//新建项
    newItem->setData(Qt::UserRole, QVariant::fromValue(project));//设置项的数据
    newItem->setSizeHint(QSize(250,250));
    ui->listWidget->addItem(newItem);//添加至列表
    ProjectItem* pjItem = new ProjectItem(project.s_name,project.s_profile);//创建项的视图
    ui->listWidget->setItemWidget(newItem,pjItem);//绑定项与视图
}

void MainWidget::addPjItemToProject(const struct Project& project)
{
    QListWidgetItem* newItem = new QListWidgetItem;//新建项
    newItem->setData(Qt::UserRole, QVariant::fromValue(project));//设置项的数据
    newItem->setSizeHint(QSize(400,400));
    ui->listWidget_2->addItem(newItem);//添加至列表
    ProjectItem* pjItem = new ProjectItem(project.s_name,project.s_profile);//创建项的视图
    ui->listWidget_2->setItemWidget(newItem,pjItem);//绑定项与视图
}

void MainWidget::addParticipatorItemProject(const struct UserInformation& user)
{
    QListWidgetItem* newItem = new QListWidgetItem;//新建项
    newItem->setData(Qt::UserRole, QVariant::fromValue(user));//设置项的数据
    newItem->setSizeHint(QSize(200,200));
    ui->pj_participators_listWidget->addItem(newItem);//添加至列表
    UserItem* userItem = new UserItem(user.s_name,user.s_introduction);
    ui->pj_participators_listWidget->setItemWidget(newItem,userItem);//绑定项与视图
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
        m_number = number_input;
        m_password = password_input;
        MainPJLoad();
        MyPJLoad();
        ui->stackedWidget->setCurrentIndex(2);
    }
    else
    {
        qDebug() << "input error";
    }

}

void MainWidget::MainPJLoad()
{
    QSqlQuery query(m_db);
    QString sql = "SELECT * FROM project";
    if(!query.exec(sql))
    {
        qDebug() << "load to main error";
    }
    struct Project project;
    while(query.next())
    {
        int id = query.value("id").toInt();
        QString Pname = query.value("Pname").toString();
        QString publisher = query.value("number").toString();
        QString profile = query.value("profile").toString();
        QString demand = query.value("demand").toString();
        project.setData(id,Pname,publisher,profile,demand);
        addPjItemToMain(project);
    }
}


void MainWidget::MyPJLoad()
{
    QSqlQuery query(m_db);
    QString sql = QString("SELECT * FROM project WHERE number='%1'").arg(m_number);
    query.prepare(sql);
    if(!query.exec(sql))
    {
        qDebug() << "load to mypjload error" ;
    }
    struct Project project;
    while(query.next())
    {
        int id = query.value("id").toInt();
        QString Pname = query.value("Pname").toString();
        QString publisher = query.value("number").toString();
        QString profile = query.value("profile").toString();
        QString demand = query.value("demand").toString();
        project.setData(id,Pname,publisher,profile,demand);
        addPjItemToProject(project);
    }

}

bool MainWidget::isrightful(QString number,QString password)
{//查数据库
    QString sql = "SELECT number, password FROM user" ;
    QSqlQuery query(m_db);
    query.exec(sql);
    while (query.next())
    {
        QString rightNumber= query.value("number").toString();
        QString rightpassword= query.value("password").toString();
        if(rightNumber == number && rightpassword == password)
        {
            return true;
        }
    }
    return false;
}

void MainWidget::on_register_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWidget::on_r_return_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//项目item展示需要完善
void MainWidget::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->pj_participators_listWidget->clear();
    QVariant variant = item->data(Qt::UserRole);  // 获取用户数据
    struct Project project = variant.value<struct Project>();
    QSqlQuery query(m_db);
    QString str = QString("SELECT * "
                          "FROM pparticipation INNER JOIN user ON pparticipation.number=user.number "
                          "WHERE pparticipation.id='%1'").arg(project.s_id);

    qDebug() << str;
    query.prepare(str);
    if(query.exec())
    {
        while(query.next())
        {
            struct UserInformation user;
            QString name = query.value("name").toString();
            QString number = query.value("number").toString();
            QString password = query.value("password").toString();
            QString introduction = query.value("introduction").toString();
            QString status = query.value("status").toString();
            user.setData(number,password,name,introduction,status);
            addParticipatorItemProject(user);
        }
    }
    else
    {
        qDebug() << "friend error";
    }
    ui->pj_name_lineEdit->setText(project.s_name);
    ui->pj_profile_textBrowser->setText(project.s_profile);
    ui->pj_demand_textBrowser->setText(project.s_demand);
    ui->publisher_linelabel->setText(project.s_publisher);
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWidget::on_returnTOmain_btn_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWidget::on_launch_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWidget::on_l_returnTOmain_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(1);

}

//项目数据库补充
void MainWidget::on_l_launch_btn_clicked()
{
    struct Project project;
    QString Pname = ui->l_pj_name_lineEdit->text();
    QString profile = ui->pj_profile_textEdit->toPlainText();
    QString demand = ui->pj_demand_textEdit->toPlainText();

    QSqlQuery query(m_db);
    QString sql = "SELECT id FROM Project";
    if(!query.exec(sql))
    {
        qDebug() << "select id error";
    }
    QVector<int> idList;
    while(query.next())
    {
        idList << query.value("id").toInt();
    }
    int id = 0;
    int running = 1;
    while(running)
    {
        id = QRandomGenerator::global()->bounded(PJID_MIN, PJID_MAX);
        int i = 0;
        for(i = 0;i<idList.size();i++)
        {
            if(id == idList.at(i))
            {
                break;
            }
        }
        if(i == idList.size())
        {
            running = 0;
        }
    }
    project.setData(id,Pname,m_number,profile,demand);
    insertProject(project);//上传到数据库
    insertPParticipation(id,m_number);//launch中insert,发布者是m_number
    addPjItemToMain(project);
    addPjItemToProject(project);
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(1);
}

bool isNumber(const QString& str){
    QByteArray ba = str.toLatin1();//QString 转换为 char*
     const char *s = ba.data();

    while(*s && *s>='0' && *s<='9') s++;

    if (*s)
    { //不是纯数字
        return false;
    }
    else
    { //纯数字
        return true;
    }
}

void MainWidget::on_r_register_btn_clicked()
{
    QString number = ui->r_number_lineEdit->text();
    QString password = ui->r_password_lineEdit->text();
    QString rpPassword = ui->rp_password_lineEdit->text();
    if(isNumber(number) == false)
    {
        qDebug() << "number error";
        return;
    }
    if(number.length() != 9)
    {
        qDebug() << "length error";
        return;
    }
    QString sql = "SELECT number FROM user" ;
    QSqlQuery query(m_db);
    query.exec(sql);
    while (query.next())
    {
        QString existedNumber= query.value("number").toString();
        if(existedNumber == number)
        {
            qDebug() << "number existed";
            return;
        }
    }
    if(password.length() < 8 || password.length() > 16)
    {
        qDebug() << "password error";
        return;
    }
    if(password != rpPassword)
    {
        qDebug() << "repeat error";
        return;
    }
    insertUser(number,password);
    ui->number_lineEdit->setText(number);
    //ui->password_lineEdit->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWidget::on_myinfo_btn_clicked()
{
    QString sql = QString("SELECT number,name,introduction FROM user WHERE number='%1'")
            .arg(m_number);
    QSqlQuery query(m_db);
    query.exec(sql);
    if(query.next())
    {
        ui->d_name_lineEdit->setText(query.value("name").toString());
        ui->d_number_lineEdit->setText(query.value("number").toString());
        ui->d_myprofile_textBrowser->setText(query.value("introduction").toString());
    }
    else
    {
        qDebug() << "info load failed";
    }
    ui->stackedWidget_2->setCurrentIndex(3);
}

void MainWidget::on_d_edit_btn_clicked()
{
    ui->e_name_lineEdit->setText(ui->d_name_lineEdit->text());
    ui->e_number_lineEdit->setText(ui->d_number_lineEdit->text());
    ui->e_myprofile_textEdit->setText(ui->d_myprofile_textBrowser->toPlainText());
    ui->stackedWidget_2->setCurrentIndex(4);
}

void MainWidget::on_update_btn_clicked()
{
    QString newName = ui->e_name_lineEdit->text();
    QString newProfile = ui->e_myprofile_textEdit->toPlainText();
    QString number = ui->e_number_lineEdit->text();
    QString sql = "UPDATE user set name=:name,introduction=:introduction WHERE number=:number";
    QSqlQuery query(m_db);
    query.prepare(sql);
    query.bindValue(":name",newName);
    query.bindValue(":introduction",newProfile);
    query.bindValue(":number",number);
    if(!query.exec())
    {
        qDebug() << "update failed";
        return;
    }
    sql = "SELECT name,introduction FROM user WHERE number=:number";
    query.prepare(sql);
    query.bindValue(":number",number);
    if(query.exec())
    {
        if(query.next())
        {
            ui->d_name_lineEdit->setText(query.value("name").toString());
            ui->d_myprofile_textBrowser->setText(query.value("introduction").toString());
        }
    }
    else
    {
        qDebug() << "select failed";
        return;
    }
    ui->stackedWidget_2->setCurrentIndex(3);
}
