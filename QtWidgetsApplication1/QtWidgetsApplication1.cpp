#include "QtWidgetsApplication1.h"

int speed,engine_state,cruise_onoff_state;

QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    speed = 60;
    ui.gaugeColor->setValue(0);
    ui.gaugeColor_2->setValue(0);
    engine_state = 0;

}
void QtWidgetsApplication1::on_sbEngine_checkedChanged(bool value)
{
    if (ui.sbEngine->getChecked())
    {
        ui.gaugeColor_2->setValue(speed);
        ui.gaugeColor->setValue(1900);
        engine_state = 1;
    }
        
    else
    {
        ui.gaugeColor_2->setValue(0);
        ui.gaugeColor->setValue(0);
        engine_state = 0;
    }
}

void QtWidgetsApplication1::on_cbDIST_clicked(void)
{
    if (ui.sbEngine->getChecked() == false)
    {
        return;
    }
}


void QtWidgetsApplication1::on_cbLIM_clicked(void)
{
    if (ui.sbEngine->getChecked() == false)
    {
        return;
    }
}
void QtWidgetsApplication1::on_cbRES_clicked(void)
{
    if (ui.sbEngine->getChecked() == false)
    {
        return;
    }
}
void QtWidgetsApplication1::on_cbSET_clicked(void)
{
    if (ui.sbEngine->getChecked() == false)
    {
        return;
    }
}
void QtWidgetsApplication1::on_cbCruise_clicked(void)
{
    if (ui.sbEngine->getChecked() == false)
    {
        return;
    }
}
void QtWidgetsApplication1::on_cbup_clicked(void)
{
    if (ui.sbEngine->getChecked() == false)
    {
        return;
    }
    if(speed < 150)
        speed += 5;

    ui.gaugeColor_2->setValue(speed);
}
void QtWidgetsApplication1::on_cbdown_clicked(void)
{
    if (ui.sbEngine->getChecked() == false)
    {
        return;
    }
    if (speed > 4)
        speed -= 5;
    ui.gaugeColor_2->setValue(speed);
}