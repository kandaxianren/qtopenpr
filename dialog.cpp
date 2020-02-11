#include "dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

MyCameraDialog::MyCameraDialog(QWidget *parent)
    : QDialog(parent)
{
    this->setFixedSize(700, 400);

    camera = new QCamera();
    cameraViewFinder = new QCameraViewfinder();
    cameraImageCapture = new QCameraImageCapture(camera);

    startRecognize = new QPushButton();
    saveBtn = new QPushButton();
    exitBtn = new QPushButton();
    //startRecognize = new QPushButton();

    displayLabel = new QLabel();
    displayLabel->setFixedSize(160, 120);
    displayLabel->setScaledContents(true);
    resultLabel =new QLabel("Result Of Recognize",this);
    resultLabel->setFixedSize(160,50);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(displayLabel);
    rightLayout->addStretch();
    rightLayout->addWidget(resultLabel);
    rightLayout->addWidget(startRecognize);
    rightLayout->addWidget(saveBtn);
    rightLayout->addWidget(exitBtn);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(cameraViewFinder);
    mainLayout->addLayout(rightLayout);

    connect(startRecognize, SIGNAL(clicked()), this, SLOT(CaptureAndRecognize()));
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(saveBtnResponded()));
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(exitBtnResponded()));
    connect(cameraImageCapture, SIGNAL(imageCaptured(int,QImage)), this, SLOT(SaveAndDisplay(int,QImage)));

    cameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->setViewfinder(cameraViewFinder);
    camera->start();

    this->setLayout(mainLayout);
    this->translateLanguage();

}

MyCameraDialog::~MyCameraDialog()
{

}

void MyCameraDialog::translateLanguage()
{
    this->setWindowTitle(tr("CarPlateRecognize"));

    saveBtn->setText(tr("save"));
    exitBtn->setText(tr("exit"));
    startRecognize->setText(tr("start"));
}

void MyCameraDialog::CaptureAndRecognize()
{
    /*
    std::cout<<"start"<<endl;
    this->Delaymsec(5000);
    std::cout<<"close"<<endl;
    */
  //  QSqlDatabase database=this->CreatDatabase();
  //  int plateid=0;
    std::string path="/root/Desktop/h/h.jpg";
  //  while(1)
 //   {
 //       if(this->CheckDistance()<7)
  //      {
            cameraImageCapture->capture();

            QString text=this->Recognize(path);
  //          QString time=this->GetCurrentTime();
            resultLabel->setText(text);
            //std::cout<<text.length()<<endl;

  //              if(text.length()==10&&this->CheckRepeat(database,plateid,text)==1)
  //                  {
   //                     plateid+=1;
   //                     this->WriteInToDatabase(database,plateid,text, time);
   //                 }
     //   }

//    }

}

void MyCameraDialog::saveBtnResponded()
{
    const QPixmap *pixmap = displayLabel->pixmap();
    if(pixmap) {pixmap->save("/root/Desktop/h/a.jpg");}
}

void MyCameraDialog::exitBtnResponded()
{
    camera->stop();
    this->close();
}

void MyCameraDialog::SaveAndDisplay(int id, QImage image)
{

    displayLabel->setPixmap(QPixmap::fromImage(image));
    const QPixmap *pixmap = displayLabel->pixmap();
    if(pixmap) {pixmap->save("/root/Desktop/h/h.jpg");}

}

QString MyCameraDialog::Recognize(std::string path){
    CPlateRecognize pr;
    QString l;
    pr.setDetectType(PR_DETECT_CMSER|PR_DETECT_COLOR);
    vector<CPlate> plateVec;
    Mat src=imread(path);// /root/Desktop/h/c.jpg
    pr.setResultShow(false);
    pr.setLifemode(true);
    int result=pr.plateRecognize(src,plateVec);
    //std::cout<<plateVec.empty()<<endl;

   if(plateVec.empty())
    {
        l="There Is No Plate";
        return l;
    }
    else
    {

        CPlate plate=plateVec.at(0);
        String license=plate.getPlateStr();
        l=QString::fromLocal8Bit(license.c_str());
        return l;
    }
}

QSqlDatabase MyCameraDialog::CreatDatabase()
{
    QSqlDatabase database;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("CarPlate.db");
        database.setUserName("KanDaXianRen");
        database.setPassword("123456");
        database.open();
        QSqlQuery sql_query;
        QString create_sql = "create table CarPlate (id int primary key, plate vchar(30), time vchar(30))";
        sql_query.prepare(create_sql);
        sql_query.exec();
        //if(!sql_query.exec()){std::cout<<"no create"<<endl;}
        database.close();
    }

    return database;
}

void MyCameraDialog::WriteInToDatabase(QSqlDatabase database,int id,QString text,QString time)
{
    database.open();
    QString insert_sql = "insert into CarPlate values (?, ?, ?)";
    QSqlQuery sql_query;
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(id);
    sql_query.addBindValue(text);
    sql_query.addBindValue(time);
    if(!sql_query.exec())
    {
        std::cout<<"no instert"<<endl;
    }
    database.close();
}

QString MyCameraDialog::GetCurrentTime()
{
    QTime thetime;
    QString time;
    time=thetime.currentTime().toString("hh:mm:ss");
    return time;
}

bool MyCameraDialog::CheckRepeat(QSqlDatabase database,int id,QString text)
{
    if(id<3)
    {
        return 1;
    }
    database.open();
    QSqlQuery sql_query;
    QString select_sql = "select plate from CarPlate where id=";
    QString s = QString::number(id-1, 10);
    select_sql+=s;
    sql_query.exec(select_sql);
    QString lastone;
    QString lasttwo;

    if(sql_query.first())
    {
        lastone = sql_query.value(0).toString();

    }


    select_sql = "select plate from CarPlate where id=";
    s = QString::number(id-2, 10);
    select_sql+=s;
    sql_query.exec(select_sql);
    if(sql_query.first())
    {
        lasttwo = sql_query.value(0).toString();
    }

    database.close();
    if(text==lastone||text==lasttwo)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void MyCameraDialog::Delaymsec(int msec)
{

    QTime n=QTime::currentTime();

    QTime now;
    do{
      now=QTime::currentTime();
    }while (n.msecsTo(now)<=msec);

}

float MyCameraDialog::CheckDistance()
{

}
