#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"

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

public:
    QtWidgetsApplication1(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtWidgetsApplication1 ui;
    
};
