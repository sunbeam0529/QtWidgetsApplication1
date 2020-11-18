#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include <string>
#include "PLinApi.h"
#include "PLIN_Driver.h"


using namespace std;


class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT
private slots:
    void on_sbEngine_checkedChanged(bool value);

    void on_cbDIST_clicked(void);

    void on_cbLIM_clicked(void);

    void on_cbRES_clicked(void);

    void on_cbSET_clicked(void);

    void on_cbCruise_clicked(void);

    void on_cbup_clicked(void);

    void on_cbdown_clicked(void);

    void on_cbMinus_clicked(void);

    void on_cbPlus_clicked(void);

    void on_sb_Phone_checkedChanged(bool value);

    void on_cbSeekPlus_clicked(void);

    void on_cbSeekMinus_clicked(void);

    void on_cbPhone_clicked(void);
    
    void on_cbOK_clicked(void);

    void on_cbReturn_clicked(void);

    void on_cbVolMinus_clicked(void);

    void on_cbVolPlus_clicked(void);

    void on_pbPlay_clicked(void);

    void on_pbSeekMinus_clicked(void);

	void on_pbSeekPlus_clicked(void);

    void on_cbPhone_pressed(void);

    void on_btnFresh_clicked(void);

    void on_btnConnect_clicked(void);

    void on_btnStop_clicked(void);

    void on_btnClear_clicked(void);

    void TransmitBlock(char* data, int len, int blockid);

    void Write3C(BYTE* buf);

    void TransmitID(int id);

    void TransmitID(int id, BYTE* data);

    int CalculatePID(int ID);

    void Transmit3DHead(void);

    void Read3D(void);

    void Read3D(BYTE NAD);

    int Wait3D(BYTE* data, int times);

    void ProcessDiag(BYTE* buffer);

    void putdata(BYTE* src, BYTE* dst, int len);

    void putdata(QByteArray src, int start, BYTE* dst, int len);

    void ReadMsg(void);

    void ReadMsg(BYTE* data);

    void ReadMsg(uint8_t* id, BYTE* data);


    void onTimeOut01(void);

    void ProcessMsg(uint8_t msgid, BYTE msgdata[]);


public:
    QtWidgetsApplication1(QWidget *parent = Q_NULLPTR);

    ~QtWidgetsApplication1(void);
    
    QList<QString>* HWList;

private:
    uint8_t LoadDLLState;
    PLIN_DRIVER pd;
    QTimer* timer;
    Ui::QtWidgetsApplication1 ui;

    void Display(string s);

    
    
};
