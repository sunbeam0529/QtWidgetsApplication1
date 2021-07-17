#include "QtWidgetsApplication1.h"
#include "qtimer.h"
#include <stdlib.h>
#include <windows.h>
#include "MsgStruct.h"

MSG_0A_TYPE msg_0x0A;
MSG_10_TYPE msg_0x10;
MSG_11_TYPE msg_0x11;
MSG_19_TYPE msg_0x19;
MSG_1A_TYPE msg_0x1A;



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

    //load dll
    HWList = new QList<QString>;
    Display(u8"加载成功");
    int ret = pd.LoadDLL();
    LoadDLLState = 0;
    if (ret == RET_ERR)//加载DLL文件
    {
        Display(u8"PLinApi.dll加载失败");
    }
    else if (ret == RET_OK)
    {
        Display(u8"PLinApi.dll加载成功");
        LoadDLLState = 1;
    }

    //timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeOut01()));
    ui.textBrowser->document()->setMaximumBlockCount(10000);
}

QtWidgetsApplication1::~QtWidgetsApplication1(void)
{
    pd.DoLINDisconnect();//断开连接

}

void QtWidgetsApplication1::onTimeOut01(void)
{
    static uint8_t ScheduleCount=0;
    uint8_t msgid;
    BYTE msgbuffer[8];
    BYTE TxMsg[8] = { 0x00,0x00,0x00,0x00,0x00,0x00 ,0x00 ,0x00 };
    if (pd.isConnect() == RET_ERR)
    {
        Display(u8"硬件未连接");
        timer->stop();
        return;
    }

    ReadMsg(&msgid, msgbuffer);

    ProcessMsg(msgid, msgbuffer);

    switch (ScheduleCount)
    {
    case 0:
        TxMsg[1] = ui.stBacklight->value();
        TxMsg[2] = ui.stPressTh->value();
        TxMsg[3] = ui.stMotorDrvCycle->value();
        TxMsg[4] = ui.stMotorDrvLevel->value();
        TransmitID(0x0A,TxMsg);//
        break;
    case 1:
        TransmitID(0x19);//
        break;
    case 2:
        TransmitID(0x1A);//
        break;
    case 3:
        TransmitID(0x10);//
        break;
    case 4:
        TransmitID(0x11);//
        break;
    default:
        break;
    }
    ScheduleCount++;
    if (ScheduleCount > 4)
    {
        ScheduleCount = 0;
    }
    
}

void QtWidgetsApplication1::ProcessMsg(uint8_t msgid, BYTE msgdata[])
{
    static uint8_t LeftKeyFlag,RightKeyFlag,LeftPressFlag,RightPressFlag;
    uint8_t  flag;
    uint32_t pressVal,times;
    switch (msgid)
    {
    case 0x0A:
        break;
    case 0x10:
        for (int i = 0; i < 8; i++)
        {
            msg_0x10.BYTE[i] = msgdata[i];
        }
        ui.xpb_l_signal0->setValue(msg_0x10.BYTE[0]);
        ui.xpb_l_signal1->setValue(msg_0x10.BYTE[1]);
        ui.xpb_l_signal2->setValue(msg_0x10.BYTE[2]);
        ui.xpb_l_signal3->setValue(msg_0x10.BYTE[3]);
        ui.xpb_l_signal4->setValue(msg_0x10.BYTE[4]);
        ui.xpb_l_signal5->setValue(msg_0x10.BYTE[5]);
        ui.xpb_l_signal6->setValue(msg_0x10.BYTE[6]);
        ui.xpb_l_signal7->setValue(msg_0x10.BYTE[7]);
        break;
    case 0x11:
        for (int i = 0; i < 8; i++)
        {
            msg_0x11.BYTE[i] = msgdata[i];
        }
        ui.xpb_r_signal0->setValue(msg_0x11.BYTE[0]);
        ui.xpb_r_signal1->setValue(msg_0x11.BYTE[1]);
        ui.xpb_r_signal2->setValue(msg_0x11.BYTE[2]);
        ui.xpb_r_signal3->setValue(msg_0x11.BYTE[3]);
        ui.xpb_r_signal4->setValue(msg_0x11.BYTE[4]);
        ui.xpb_r_signal5->setValue(msg_0x11.BYTE[5]);
        ui.xpb_r_signal6->setValue(msg_0x11.BYTE[6]);
        ui.xpb_r_signal7->setValue(msg_0x11.BYTE[7]);
        break;
    case 0x19:
        for (int i = 0; i < 8; i++)
        {
            msg_0x19.BYTE[i] = msgdata[i];
        }
        flag = 0;
        if (msg_0x19.Data.Key_ACC)
        {
            if (LeftKeyFlag == 0)
            {
                ui.cbCruise->clicked();
                LeftKeyFlag = 1;
            }
            flag = 1;
        }
        if (msg_0x19.Data.Key_DIST)
        {
            if (LeftKeyFlag == 0)
            {
                ui.cbDIST->clicked();
                LeftKeyFlag = 1;
            }
            flag = 1;
        }
        if (msg_0x19.Data.Key_LIM)
        {
            if (LeftKeyFlag == 0)
            {
                ui.cbLIM->clicked();
                LeftKeyFlag = 1;
            }
            flag = 1;
        }
        if (msg_0x19.Data.Key_RES)
        {
            if (LeftKeyFlag == 0)
            {
                ui.cbRES->clicked();
                LeftKeyFlag = 1;
            }
            flag = 1;
        }
        if (msg_0x19.Data.Key_SET)
        {
            if (LeftKeyFlag == 0)
            {
                ui.cbSET->clicked();
                LeftKeyFlag = 1;
            }
            flag = 1;
        }
        if (flag == 0)
        {
            LeftKeyFlag = 0;
        }
        pressVal = msg_0x19.Data.ReverseByte5;
        pressVal <<= 8;
        pressVal += msg_0x19.Data.ReverseByte4;
        ui.xpb_l_press->setValue(pressVal);
        if (ui.checkBox_press->isChecked() == true)
        {
            if (LeftPressFlag == 0)
            {
                if (pressVal > 300)
                {
                    LeftPressFlag = 1;
                    times = ui.label_log_pressL->text().toInt();
                    times++;
                    ui.label_log_pressL->setText(QString::number(times));
                }
            }
            else
            {
                if (pressVal < 200)
                {
                    LeftPressFlag = 0;
                }
            }
        }
        break;
    case 0x1A:
        for (int i = 0; i < 8; i++)
        {
            msg_0x1A.BYTE[i] = msgdata[i];
        }
        flag = 0;
        if (msg_0x1A.Data.Key_Menu)
        {
            if (RightKeyFlag == 0)
            {
                ui.cbReturn->clicked();
                RightKeyFlag = 1;
            }
            flag = 1;
        }
        if (msg_0x1A.Data.Key_OK)
        {
            if (RightKeyFlag == 0)
            {
                ui.cbOK->clicked();
                RightKeyFlag = 1;
            }
            flag = 1;
        }
        if (msg_0x1A.Data.Key_SeekPlus)
        {
            if (RightKeyFlag == 0)
            {
                ui.cbSeekPlus->clicked();
                RightKeyFlag = 1;
            }
            flag = 1;
        }
        if (msg_0x1A.Data.Key_SeekReduce)
        {
            if (RightKeyFlag == 0)
            {
                ui.cbSeekMinus->clicked();
                RightKeyFlag = 1;
            }
            flag = 1;
        }
        if (msg_0x1A.Data.Key_Speech)
        {
            if (RightKeyFlag == 0)
            {
                ui.cbPhone->clicked();
                RightKeyFlag = 1;
            }
            flag = 1;
        }
        if (flag == 0)
        {
            RightKeyFlag = 0;
        }
        pressVal = msg_0x1A.Data.ReverseByte5;
        pressVal <<= 8;
        pressVal += msg_0x1A.Data.ReverseByte4;
        if (ui.checkBox_press->isChecked() == true)
        {
            if (RightPressFlag == 0)
            {
                if (pressVal > 300)
                {
                    RightPressFlag = 1;
                    times = ui.label_log_pressR->text().toInt();
                    times++;
                    ui.label_log_pressR->setText(QString::number(times));
                }
            }
            else
            {
                if (pressVal < 200)
                {
                    RightPressFlag = 0;
                }
            }
        }
        ui.xpb_r_press->setValue(pressVal);
        break;
    default:
        break;
    }
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

//Connect 
void QtWidgetsApplication1::Display(string s)
{
    ui.textBrowser->append(QString::fromStdString(s));

}

void QtWidgetsApplication1::on_btnFresh_clicked(void)
{
    //QList<UINT8> datebuf(256);
    int ret;
    ui.cbbSelectChenal->clear();
    if (LoadDLLState == 0)
    {
        Display(u8"未加载dll，请重新启动");
    }
    ret = pd.FreshHW(HWList);//刷新硬件

    if (ret == RET_ERR)
    {
        ui.cbbSelectChenal->addItem("未找到硬件");
    }
    for (int i = 0; i < HWList->count(); i++)
    {
        ui.cbbSelectChenal->addItem((*HWList)[i]);
    }
}


void QtWidgetsApplication1::on_btnConnect_clicked(void)
{
    int ret;
    ret = pd.DoLINConnect(ui.cbbSelectChenal->currentIndex(), 19200);//连接硬件
    if (ret == RET_OK)
    {
        ui.btnStop->setEnabled(TRUE);
        ui.btnConnect->setEnabled(FALSE);
        Display(u8"连接成功");
        timer->start(10);
    }
}

void QtWidgetsApplication1::on_btnStop_clicked(void)
{
    pd.DoLINDisconnect();//断开连接
    ui.btnConnect->setEnabled(TRUE);
    ui.btnStop->setEnabled(FALSE);
    Display(u8"断开连接");
    timer->stop();
}

void QtWidgetsApplication1::on_btnClear_clicked(void)
{
    ui.textBrowser->clear();//清空
}

void QtWidgetsApplication1::TransmitBlock(char* data, int len, int blockid)
{
	BYTE temp[8] = { 0x21,0x10,len + 2,0x36,blockid,0,0,0 };
	int frameid, i = 0;
	temp[5] = data[i++];
	temp[6] = data[i++];
	temp[7] = data[i++];
	Write3C(temp);
	Sleep(10);
	len -= 3;
	frameid = 0x21;
	while (len > 6)
	{
		temp[1] = frameid;
		temp[2] = data[i++];
		temp[3] = data[i++];
		temp[4] = data[i++];
		temp[5] = data[i++];
		temp[6] = data[i++];
		temp[7] = data[i++];
		Write3C(temp);
		Sleep(10);
		if (frameid < 0x2F)frameid++;
		else frameid = 0x20;
		len -= 6;
	}

	temp[1] = frameid;
	int j;
	for (j = 2; len > 0; len--, j++)
	{
		temp[j] = data[i++];
	}
	for (; j < 8; j++)
	{
		temp[j] = 0xff;
	}
	Write3C(temp);
	Sleep(10);
}

void QtWidgetsApplication1::Write3C(BYTE* buf)
{
	TLINMsg msg;
	if (pd.isConnect() == RET_ERR)
	{
		Display(u8"硬件未连接");
		return;
	}
	msg.FrameId = 0x3C;
	msg.Direction = dirPublisher;
	msg.Length = 8;
	msg.ChecksumType = cstClassic;
	for (int i = 0; i < 8; i++)
		msg.Data[i] = buf[i];
	pd.CalculateChecksum(&msg);
	pd.Write(pd.m_hClient, pd.m_hHW, &msg);
}

void QtWidgetsApplication1::TransmitID(int id)
{
	TLINMsg msg;
	if (pd.isConnect() == RET_ERR)
	{
		Display(u8"硬件未连接");
		return;
	}
	msg.FrameId = CalculatePID(id);
	msg.Direction = dirSubscriberAutoLength;//dirPublisher;// 
	msg.Length = 8;
	msg.ChecksumType = cstEnhanced;
	for (int i = 0; i < 8; i++)
		msg.Data[i] = 0;
	pd.CalculateChecksum(&msg);
	pd.Write(pd.m_hClient, pd.m_hHW, &msg);
}

void QtWidgetsApplication1::TransmitID(int id, BYTE* data)
{
	TLINMsg msg;
	if (pd.isConnect() == RET_ERR)
	{
		Display(u8"硬件未连接");
		return;
	}
	msg.FrameId = CalculatePID(id);
	msg.Direction = dirPublisher;// 
	msg.Length = 8;
	msg.ChecksumType = cstEnhanced;
	for (int i = 0; i < 8; i++)
		msg.Data[i] = data[i];
	pd.CalculateChecksum(&msg);
	pd.Write(pd.m_hClient, pd.m_hHW, &msg);
}

int QtWidgetsApplication1::CalculatePID(int ID)
{
	int P0, P1;
	P0 = (ID & 0x01) ^ ((ID & 0x02) >> 1) ^ ((ID & 0x04) >> 2) ^ ((ID & 0x10) >> 4);
	P1 = (((ID & 0x02) >> 1) ^ ((ID & 0x08) >> 3) ^ ((ID & 0x10) >> 4) ^ ((ID & 0x20) >> 5));
	P1 = P1 ^ 0x01;
	ID = ID | (P0 << 6) | (P1 << 7);

	return ID;
}

void QtWidgetsApplication1::Transmit3DHead(void)
{
	TLINMsg msg;
	if (pd.isConnect() == RET_ERR)
	{
		Display(u8"硬件未连接");
		return;
	}
	msg.FrameId = 0x7D;
	msg.Direction = dirSubscriber;
	msg.Length = 8;
	msg.ChecksumType = cstClassic;
	for (int i = 0; i < 8; i++)
		msg.Data[i] = 0;
	pd.CalculateChecksum(&msg);
	pd.Write(pd.m_hClient, pd.m_hHW, &msg);
}

void QtWidgetsApplication1::Read3D(void)
{
	TLINRcvMsg RcvMsg;
	BYTE temp[8], buffer[60] = { 0 }, * pbuffer;
	Transmit3DHead();
	Sleep(10);
	temp[0] = 0x00;
	ReadMsg(temp);
	pbuffer = buffer;
	while (temp[0] == 0x21)
	{
		if (temp[1] == 0x10)
		{
			putdata(temp + 2, pbuffer, 6);
			pbuffer += 6;
		}
		else if (temp[1] >= 0x20)
		{
			putdata(temp + 2, pbuffer, 6);
			pbuffer += 6;
		}
		else if (temp[1] < 7)
		{
			putdata(temp + 1, buffer, temp[1] + 1);

			break;
		}


		Transmit3DHead();
		Sleep(10);
		temp[0] = 0x00;
		ReadMsg(temp);
	}
	ProcessDiag(buffer);
}
void QtWidgetsApplication1::Read3D(BYTE NAD)
{
	TLINRcvMsg RcvMsg;
	BYTE temp[8], buffer[60] = { 0 }, * pbuffer;
	Transmit3DHead();
	Sleep(10);
	temp[0] = 0x00;
	ReadMsg(temp);
	pbuffer = buffer;
	while (temp[0] == NAD && NAD != 0)
	{
		if (temp[1] == 0x10)
		{
			putdata(temp + 2, pbuffer, 6);
			pbuffer += 6;
		}
		else if (temp[1] >= 0x20)
		{
			putdata(temp + 2, pbuffer, 6);
			pbuffer += 6;
		}
		else if (temp[1] < 7)
		{
			putdata(temp + 1, buffer, temp[1] + 1);

			break;
		}


		Transmit3DHead();
		Sleep(10);
		temp[0] = 0x00;
		ReadMsg(temp);
	}
	ProcessDiag(buffer);
}

int QtWidgetsApplication1::Wait3D(BYTE* data, int times)
{
	while (times-- > 0)
	{
		Transmit3DHead();
		Sleep(10);
		data[0] = 0;
		ReadMsg(data);
		if (data[0] == 0x21)
			return 1;
	}
	return 0;//超时

}

void QtWidgetsApplication1::ProcessDiag(BYTE* buffer)
{
	int len = buffer[0];
	int DID = 0;
	if (len == 0)return;
	
}

void QtWidgetsApplication1::putdata(BYTE* src, BYTE* dst, int len)
{
	while (len--)
	{
		*dst++ = *src++;
	}
}

void QtWidgetsApplication1::putdata(QByteArray src, int start, BYTE* dst, int len)
{
	while (len--)
	{
		*dst++ = src[start++];
	}
}


void QtWidgetsApplication1::ReadMsg(void)
{
	TLINRcvMsg RcvMsg;
	TLINError IsEmpty = errOK;
	if (pd.isConnect() == RET_ERR)
	{
		Display(u8"硬件未连接");
		return;
	}

	while (!(IsEmpty & errRcvQueueEmpty))
	{
		IsEmpty = pd.Read(pd.m_hClient, &RcvMsg);
		if (IsEmpty != errOK)
			continue;
		if (RcvMsg.Type != mstStandard)
			continue;
		if (RcvMsg.ErrorFlags != MSG_ERR_OK)
			continue;
		//if (RcvMsg.FrameId != 0x3C && RcvMsg.FrameId != 0x7D)
			//continue;
		QString str = "0x";
		str.append(QString::number(RcvMsg.FrameId & 0x3f, 16));
		str.append(":");
		for (int i = 0; i < RcvMsg.Length; i++)
		{
			//str.append(QString::number(RcvMsg.Data[i], 16));
			str.append("0x");
			str.append(QString("%1").arg(RcvMsg.Data[i], 2, 16, QChar('0')).toUpper());
			str.append(" ");
		}
		//QString strtemp(str.toUpper());
		ui.textBrowser->append(str);

	}
}

void QtWidgetsApplication1::ReadMsg(BYTE* data)
{
	TLINRcvMsg RcvMsg;
	TLINError IsEmpty = errOK;
	if (pd.isConnect() == RET_ERR)
	{
		Display(u8"硬件未连接");
		return;
	}

	while (!(IsEmpty & errRcvQueueEmpty))
	{
		IsEmpty = pd.Read(pd.m_hClient, &RcvMsg);
		if (IsEmpty != errOK)
			continue;
		if (RcvMsg.Type != mstStandard)
			continue;
		if (RcvMsg.ErrorFlags != MSG_ERR_OK)
			continue;
		//if (RcvMsg.FrameId != 0x3C && RcvMsg.FrameId != 0x7D)
			//continue;
		QString str = "0x";
		str.append(QString::number(RcvMsg.FrameId & 0x3f, 16).toUpper());
		str.append(":");
		for (int i = 0; i < RcvMsg.Length; i++)
		{
			//str.append(QString::number(RcvMsg.Data[i], 16));
			str.append("0x");
			str.append(QString("%1").arg(RcvMsg.Data[i], 2, 16, QChar('0')).toUpper());

			str.append(" ");
			if (RcvMsg.FrameId == 0x7D)
				data[i] = RcvMsg.Data[i];
		}
		//QString strtemp(str.toUpper());
		ui.textBrowser->append(str);

	}
}

void QtWidgetsApplication1::ReadMsg(uint8_t *id, BYTE* data)
{
    TLINRcvMsg RcvMsg;
    TLINError IsEmpty = errOK;
    if (pd.isConnect() == RET_ERR)
    {
        Display(u8"硬件未连接");
        return;
    }

    while (!(IsEmpty & errRcvQueueEmpty))
    {
        IsEmpty = pd.Read(pd.m_hClient, &RcvMsg);
        if (IsEmpty != errOK)
            continue;
        if (RcvMsg.Type != mstStandard)
            continue;
        if (RcvMsg.ErrorFlags != MSG_ERR_OK)
            continue;
        //if (RcvMsg.FrameId != 0x3C && RcvMsg.FrameId != 0x7D)
            //continue;
        QString str = "0x";
        str.append(QString::number(RcvMsg.FrameId & 0x3f, 16).toUpper());
        str.append(":");
        for (int i = 0; i < RcvMsg.Length; i++)
        {
            //str.append(QString::number(RcvMsg.Data[i], 16));
            str.append("0x");
            str.append(QString("%1").arg(RcvMsg.Data[i], 2, 16, QChar('0')).toUpper());

            str.append(" ");
            //if (RcvMsg.FrameId == *id)
                data[i] = RcvMsg.Data[i];
        }
        *id = RcvMsg.FrameId & 0x3f;
        //QString strtemp(str.toUpper());
        ui.textBrowser->append(str);

    }
}
