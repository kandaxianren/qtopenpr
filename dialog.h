#ifndef MYCAMERADIALOG_H
#define MYCAMERADIALOG_H

#include <QDialog>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QLabel>
#include <QPushButton>
#include "easypr.h"
#include "easypr/core/plate.hpp"
#include "easypr/util/switch.hpp"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTime>

using namespace easypr;
using namespace cv;

class MyCameraDialog : public QDialog
{
    Q_OBJECT

public:
    MyCameraDialog(QWidget *parent = 0);
    QString Recognize(std::string path);
    QSqlDatabase CreatDatabase();
    void WriteInToDatabase(QSqlDatabase database,int id,QString text,QString time);
    QString GetCurrentTime();
    void Delaymsec(int msec);
    float CheckDistance();
    bool CheckRepeat(QSqlDatabase database,int id,QString text);
    ~MyCameraDialog();

private slots:
    void CaptureAndRecognize();
    void saveBtnResponded();
    void exitBtnResponded();
    void SaveAndDisplay(int id, QImage image);

private:

    QCamera *camera;

    QCameraViewfinder *cameraViewFinder;

    QCameraImageCapture *cameraImageCapture;


    QPushButton *saveBtn;
    QPushButton *exitBtn;
    QPushButton *startRecognize;
    QLabel *displayLabel;
    QLabel *resultLabel;
    void translateLanguage();
};

#endif // MYCAMERADIALOG_H
