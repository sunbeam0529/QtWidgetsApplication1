#include "QtWidgetsApplication1.h"
#include "qtimer.h"

#define CRUISE_OFF      0
#define CRUISE_ON       1
#define CRUISE_START    2

int speed,engine_state, cruisespeed,lastcruisespeed;
int distval,menuid;
bool phonestate,voicestate,playstate,menustate;
QTimer *timer1;
int cruise_state;
QString menuarr[] = { u8"菜单-导航.jpg",u8"菜单-电话.jpg", u8"菜单-音乐.jpg", u8"菜单-电台.jpg", };
QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    speed = 60;
    ui.gaugeColor->setValue(0);
    ui.gaugeColor_2->setValue(0);
    engine_state = 0;
    ui.lb_cruiseicon->hide();
    ui.lb_CruiseSpeed->hide();
    ui.lb_DistIcon->hide();
    ui.bv_DistVal->hide();
    ui.lb_PhoneImage->hide();
    ui.lb_VoiceIcon->hide();
    cruise_state = CRUISE_OFF;
    distval = 1;
    menuid = 0;
    menustate = true;
}
void QtWidgetsApplication1::on_sbEngine_checkedChanged(bool value)
{
    if (ui.sbEngine->getChecked())
    {
        ui.gaugeColor_2->setAnimationStep(0.5);
        ui.gaugeColor_2->setValue(speed);
        ui.gaugeColor->setValue(1900);
        engine_state = 1;
    }
        
    else
    {
        speed = 60;
        ui.gaugeColor->setValue(0);
        ui.gaugeColor_2->setValue(0);
        engine_state = 0;
        ui.lb_cruiseicon->hide();
        ui.lb_CruiseSpeed->hide();
        ui.lb_DistIcon->hide();
        ui.bv_DistVal->hide();
        cruise_state = CRUISE_OFF;
        distval = 1;
        
    }
}


////////////////////////////////Left//////////////////////////////
void QtWidgetsApplication1::on_cbDIST_clicked(void)
{
    if (ui.sbEngine->getChecked() == false)
    {
        return;
    }
    distval++;
    if (distval > 4)
    {
        distval = 1;
    }
    ui.bv_DistVal->setValue(distval);
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
    if (cruise_state == CRUISE_OFF)
    {
        return;
    }
    if (lastcruisespeed == 0)
    {
        return;
    }
    cruise_state = CRUISE_START;
    cruisespeed = lastcruisespeed;
    ui.lb_CruiseSpeed->setText(QString::number(cruisespeed) + QString("Km/h"));
    ui.lb_CruiseSpeed->show();
    speed = lastcruisespeed;
    ui.gaugeColor_2->setAnimationStep(0.05);
    ui.gaugeColor_2->setValue(speed);

}
void QtWidgetsApplication1::on_cbSET_clicked(void)
{
    if (ui.sbEngine->getChecked() == false)
    {
        return;
    }
    if (cruise_state == CRUISE_OFF)
    {
        return;
    }
    cruise_state = CRUISE_START;
    cruisespeed = speed;
    lastcruisespeed = cruisespeed;
    ui.lb_CruiseSpeed->setText(QString::number(cruisespeed) + QString("Km/h"));
    ui.lb_CruiseSpeed->show();
    
}
void QtWidgetsApplication1::on_cbCruise_clicked(void)
{
    if (ui.sbEngine->getChecked() == false)
    {
        return;
    }
    switch (cruise_state)
    {
    case CRUISE_OFF:
        cruise_state = CRUISE_ON;
        break;
    case CRUISE_ON:
        cruise_state = CRUISE_OFF;
        break;
    case CRUISE_START:
        cruise_state = CRUISE_OFF;
        break;
    default:
        break;
    }

    if (cruise_state != CRUISE_OFF)
    {
        ui.lb_cruiseicon->show();
        ui.lb_CruiseSpeed->hide();
        ui.lb_DistIcon->show();
        ui.bv_DistVal->show();
    }
    else
    {
        ui.lb_cruiseicon->hide();
        ui.lb_CruiseSpeed->hide();
        ui.lb_DistIcon->hide();
        ui.bv_DistVal->hide();
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
    ui.gaugeColor_2->setAnimationStep(0.5);
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
    ui.gaugeColor_2->setAnimationStep(0.5);
    ui.gaugeColor_2->setValue(speed);
    ui.lb_CruiseSpeed->hide();
    if (cruise_state == CRUISE_START)
        cruise_state = CRUISE_ON;
}

void QtWidgetsApplication1::on_cbMinus_clicked(void)
{
    if (ui.sbEngine->getChecked() == false)
    {
        return;
    }
    if (cruise_state != CRUISE_START)
    {
        return;
    }
    if (cruisespeed > 30)
        cruisespeed -= 5;
    ui.lb_CruiseSpeed->setText(QString::number(cruisespeed) + QString("Km/h"));
    speed = cruisespeed;
    ui.gaugeColor_2->setAnimationStep(0.05);
    ui.gaugeColor_2->setValue(speed);
    lastcruisespeed = cruisespeed;
}

void QtWidgetsApplication1::on_cbPlus_clicked(void)
{
    if (ui.sbEngine->getChecked() == false)
    {
        return;
    }
    if (cruise_state != CRUISE_START)
    {
        return;
    }
    if (cruisespeed < 180)
        cruisespeed += 5;
    ui.lb_CruiseSpeed->setText(QString::number(cruisespeed) + QString("Km/h"));
    speed = cruisespeed;
    ui.gaugeColor_2->setAnimationStep(0.05);
    ui.gaugeColor_2->setValue(speed);
    lastcruisespeed = cruisespeed;
}


////////////////////////////////Right//////////////////////////////

void QtWidgetsApplication1::on_sb_Phone_checkedChanged(bool value)
{
    if (value)
    {
        ui.lb_PhoneImage->show();
        QString imagefile = QString(u8":/image/来电.jpg");
        ui.lb_PhoneImage->setPixmap(QPixmap(imagefile));
    }
    else
    {
        ui.lb_PhoneImage->hide();
    }
}

QString MusicArr[] = { u8"胡歌-六月的雨",u8"薛之谦-丑八怪" };
int musicid;
void QtWidgetsApplication1::on_cbSeekPlus_clicked(void)
{
    if (menustate == true)
    {
        menuid++;
        if (menuid > 3)menuid = 0;
        QString imagefile = QString(":/image/") + menuarr[menuid];
        ui.lb_menu->setPixmap(QPixmap(imagefile));
    }
    else
    {
        musicid = !musicid;
        ui.lb_MusicName->setText(MusicArr[musicid]);
        QString imagefile = QString(":/music_pic/") + MusicArr[musicid] + QString(".jpg");
        ui.lb_MusicIcon->setPixmap(QPixmap(imagefile));
    }
    
}

void QtWidgetsApplication1::on_cbSeekMinus_clicked(void)
{
    if (menustate == true)
    {
        if (menuid == 0)menuid = 4;
        menuid--;
        
        QString imagefile = QString(":/image/") + menuarr[menuid];
        ui.lb_menu->setPixmap(QPixmap(imagefile));
    }
    else
    {
        musicid = !musicid;
        ui.lb_MusicName->setText(MusicArr[musicid]);
        QString imagefile = QString(":/music_pic/") + MusicArr[musicid] + QString(".jpg");
        ui.lb_MusicIcon->setPixmap(QPixmap(imagefile));
    }
    
}

void QtWidgetsApplication1::on_cbPhone_pressed(void)
{
    if (!timer1)
    {
        timer1 = new QTimer();
        connect(timer1, &QTimer::timeout, this, &QtWidgetsApplication1::on_cbPhone_clicked);
    }
    timer1->start(100);
}

void QtWidgetsApplication1::on_cbPhone_clicked(void)
{
    if (ui.sb_Phone->getChecked() == true)
    {
        //来电
        if (phonestate == false)
        {
            //接听
            phonestate = true;
            QString imagefile = QString(u8":/image/接听.jpg");
            ui.lb_PhoneImage->setPixmap(QPixmap(imagefile));
        }
        else
        {
            //挂断
            ui.lb_PhoneImage->hide();
            phonestate = false;
            ui.sb_Phone->setChecked(false);
        }
    }
    else
    {
        //语音
        voicestate = !voicestate;
        if (voicestate == true)
        {
            ui.lb_VoiceIcon->show();
        }
        else
        {
            ui.lb_VoiceIcon->hide();
        }
            
    }
}

void QtWidgetsApplication1::on_cbOK_clicked(void)
{
    if (menustate == true && menuid == 2)
    {
        menustate = false;
        ui.lb_menu->hide();
    }
}

void QtWidgetsApplication1::on_cbReturn_clicked(void)
{
    if (menustate == false)
    {
        menustate = true;
        ui.lb_menu->show();
    }
}

void QtWidgetsApplication1::on_cbVolMinus_clicked(void)
{
    int val;
    val = ui.ptVolBar->getValue();
    if (val > 0)val--;
    ui.ptVolBar->setValue(val);
    ui.hsVolBar->setValue(val);
}

void QtWidgetsApplication1::on_cbVolPlus_clicked(void)
{
    int val;
    val = ui.ptVolBar->getValue();
    if (val < 20)val++;
    ui.ptVolBar->setValue(val);
    ui.hsVolBar->setValue(val);
}

void QtWidgetsApplication1::on_pbPlay_clicked(void)
{
    playstate = !playstate;
    if (playstate == true)
    {
        QString imagefile = QString(u8"image: url(:/icon/暂停.png);background-color: rgba(255, 0, 0, 0%);");
        ui.pbPlay->setStyleSheet(imagefile);
    }
    else
    {
        QString imagefile = QString(u8"image: url(:/icon/播放.png);background-color: rgba(255, 0, 0, 0%);");
        ui.pbPlay->setStyleSheet(imagefile);
    }

}

void QtWidgetsApplication1::on_pbSeekMinus_clicked(void)
{
    on_cbSeekMinus_clicked();
}

void QtWidgetsApplication1::on_pbSeekPlus_clicked(void)
{
    on_cbSeekMinus_clicked();
}