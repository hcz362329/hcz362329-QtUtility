#include "music.h"

#include "musicmanager.h"
#include <QPushButton>
#include <QLineEdit>
#include <QSound>
#include <QVariant>
#include <string>
#include <Windows.h>
#include <QComboBox>
#include <QTextEdit>
#include <QListView>
#include <QLabel>
#include <QDir>
#include <QMessageBox>
#include "Iphlpapi.h"
#pragma comment( lib, "ws2_32.lib")
#pragma comment(lib, "Iphlpapi.lib")

#include "TopHintDialog.h"
BOOL IsNetOK()
{
	BOOL bNetOK = FALSE;
	DWORD dwRetVal = 0;
	PIP_ADAPTER_INFO pInfo = NULL;
	ULONG uOutLen = 0;
	pInfo = (IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));
	uOutLen = sizeof(IP_ADAPTER_INFO);

	dwRetVal = GetAdaptersInfo(pInfo, &uOutLen);
	if(dwRetVal == ERROR_BUFFER_OVERFLOW)
	{
		free(pInfo);
		pInfo = (IP_ADAPTER_INFO *)malloc(uOutLen);
		dwRetVal = GetAdaptersInfo(pInfo, &uOutLen);
	}
	if(dwRetVal == NO_ERROR)
	{
		PIP_ADAPTER_INFO pAdapter = pInfo;
		while(pAdapter)
		{
			IP_ADDR_STRING Ip = pAdapter->IpAddressList;
			while(1)
			{
				if(inet_addr(Ip.IpAddress.String) != 0)
				{
					bNetOK = TRUE;
					break;
				}
				if(!Ip.Next)
				{
					break;
				}
				Ip = *(Ip.Next);
			}
			pAdapter = pAdapter->Next;
			if(bNetOK)
			{
				break;
			}
		}
	}
	free(pInfo);
	return bNetOK;
}


int Replace(char* src,const char need_replace,const char replace_to );
void TestEnum();
void playEnterSound()
{
	if (!MusicManager::Instance()->isPlaying(MusicManager::eTypeSelectHeroBg))
	{
		
		MusicManager::Instance()->play(MusicManager::eTypeSelectHeroBg);
	}

	if (!MusicManager::Instance()->isPlaying(MusicManager::eTypeEnterSelectHero))
	{
		MusicManager::Instance()->play(MusicManager::eTypeEnterSelectHero, 1);
	}
}

void stopSelectHeroSound()
{
	MusicManager::Instance()->stop(MusicManager::eTypeSelectHeroBg);
}

static void playLobbyBg()
{
	if (!MusicManager::Instance()->isPlaying(MusicManager::eTypeLobbyBg))
	{
		MusicManager::Instance()->play(MusicManager::eTypeLobbyBg);
	}
}

static void stopLobbyBg()
{
	if ( MusicManager::Instance()->isPlaying(MusicManager::eTypeLobbyBg) )
	{
		MusicManager::Instance()->stop(MusicManager::eTypeLobbyBg);
	}
}

void stopSound()
{
	MusicManager::Instance()->stop(MusicManager::eTypeSelectHeroBg);
	MusicManager::Instance()->stop(MusicManager::eTypeEnterSelectHero);
	MusicManager::Instance()->stop(MusicManager::eTypeCountdown);
}

void playCountdownSound()
{
	if (!MusicManager::Instance()->isPlaying(MusicManager::eTypeCountdown))
	{
		MusicManager::Instance()->play(MusicManager::eTypeCountdown);
	}
}

void playBtnSound()
{
	if (MusicManager::Instance()->isPlaying(MusicManager::eTypeButton))
	{
		MusicManager::Instance()->stop(MusicManager::eTypeButton);
	}
	if (!MusicManager::Instance()->isPlaying(MusicManager::eTypeButton))
	{
		QVariant v(QString("btn_mus_login.wav"));
		MusicManager::Instance()->play(MusicManager::eTypeButton,1,v);
	}
}

void StopAll()
{
	MusicManager::Instance()->stopAll();
}

static int hero_id = 0;

void playHeroVoice()
{
	if ( hero_id == 0 )
	{
		return;
	}

	if (MusicManager::Instance()->isPlaying(MusicManager::eTypeHeroVoice))
	{
		QVariant var = MusicManager::Instance()->getAddtionArg(MusicManager::eTypeHeroVoice);
		int nVar = var.toInt();
		if (nVar != hero_id)
		{
			MusicManager::Instance()->play(MusicManager::eTypeHeroVoice,1,QVariant::fromValue(hero_id));
		}
	}
	else
	{
		MusicManager::Instance()->play(MusicManager::eTypeHeroVoice,1,QVariant::fromValue(hero_id));
	}
}



void stopCountdownSound()
{
	MusicManager::Instance()->stop(MusicManager::eTypeCountdown);
}

enum ECommonSoundType
{
	eCommonSoundNone					= 0,
	eCommonSoundDropDown				= 1,//下拉菜单
	eCommonSoundHighlighting			= 2,//高亮音效
	eCommonSoundCheck					= 3,//勾选音效
	eCommonSoundEnterBattle				= 4,//进入战场
	eCommonSoundReceiveAward			= 5,//领取奖励
	eCommonSoundConfirm					= 6,//确定音效
	eCommonSoundInformationTips			= 7,//信息提示
	eCommonSoundRidingTurntable			= 8,//转盘跑马
};

static void PlayCommonSound(ECommonSoundType eSoundType)
{
	
	if (MusicManager::Instance()->isPlaying(MusicManager::eTypeButton))
	{
		MusicManager::Instance()->stop(MusicManager::eTypeButton);
	}
	QString strSound;
	switch(eSoundType)
	{
	case eCommonSoundDropDown://菜单下拉
		strSound = QString("dropdown.wav");
		break;
	case eCommonSoundHighlighting://高亮音效
		strSound = QString("Highlighting.wav");
		break;
	case eCommonSoundCheck://勾选音效
		strSound = QString("CheckSound.wav");
		break;
	case eCommonSoundEnterBattle://进入战场
		strSound = QString("EnterBattle.wav");
		break;
	case eCommonSoundReceiveAward://领取奖励
		strSound = QString("ReceiveAward.wav");
		break;
	case eCommonSoundConfirm://确定音效
		strSound = QString("Confirm.wav");
		break;
	case eCommonSoundInformationTips://信息提示
		strSound = QString("InformationTips.wav");
		break;
	case eCommonSoundRidingTurntable://转盘跑马
		strSound = QString("RidingTurntable.wav");
		break;
	}
	if (!strSound.isEmpty())
	{
		if (!MusicManager::Instance()->isPlaying(MusicManager::eTypeButton))
		{
			QVariant v(strSound);
			MusicManager::Instance()->play(MusicManager::eTypeButton,1,v);
		}
	}
}

music::music(QWidget *parent)
	: QWidget(parent)
{
	
	resize(650,600);
	
	QPushButton * btn1=new QPushButton("select hero",this);
	btn1->setGeometry(0,0,100,20);

	

	connect(btn1,&QPushButton::clicked,this,[=]{
		
		playEnterSound();
		//playLobbyBg();
	});

	QPushButton * btn2=new QPushButton("stop select hero",this);
	btn2->setGeometry(110,0,150,20);
	connect(btn2,&QPushButton::clicked,this,[=]{
		stopSelectHeroSound();
		//stopLobbyBg();
	});

	QPushButton * btn3=new QPushButton("Countdown",this);
	btn3->setGeometry(0,50,100,20);

	connect(btn3,&QPushButton::clicked,this,[=]{playCountdownSound();});

	QPushButton * btn4=new QPushButton("stop Countdown",this);
	btn4->setGeometry(110,50,150,20);
	connect(btn4,&QPushButton::clicked,this,[=]{stopCountdownSound();});

	QPushButton * btn5=new QPushButton("play hero ",this);
	btn5->setGeometry(0,100,100,20);
	

	QLineEdit* heroInput = new QLineEdit(this);
	heroInput->setPlaceholderText("hero id,input number");
	heroInput->setGeometry(110,100,200,20);
	connect(btn5,&QPushButton::clicked,this,[=]{
		if ( !heroInput->text().isEmpty() )
		{
			hero_id = heroInput->text().toInt();
			playHeroVoice();
		}
	});

	QPushButton * btn6=new QPushButton("play btn ",this);
	btn6->setGeometry(0,150,100,20);
	connect(btn6,&QPushButton::clicked,this,[=]{playBtnSound();});

	QPushButton * btn7=new QPushButton("stop all ",this);
	btn7->setGeometry(110,150,100,20);
	connect(btn7,&QPushButton::clicked,this,[=]{StopAll();});

	

	QPushButton * btn8=new QPushButton("play guide sound",this);
	btn8->setGeometry(0,200,200,20);

	QLineEdit* sound_guide = new QLineEdit(this);
	sound_guide->setPlaceholderText("guide step,input number");
	sound_guide->setGeometry(210,200,200,20);
	connect(btn8,&QPushButton::clicked,this,[=]{
		if ( !sound_guide->text().isEmpty() )
		{
			int step = sound_guide->text().toInt();
			QString strSound = QString("./sound/newguide/%1.wav").arg(step);
			QSound::play(strSound);
		}
	});

	QPushButton * btn9=new QPushButton("guide step block",this);
	btn9->setGeometry(0,250,200,20);

	QLineEdit* sound_guide2 = new QLineEdit(this);
	sound_guide2->setPlaceholderText("guide step block,input number");
	sound_guide2->setGeometry(210,250,200,20);
	connect(btn9,&QPushButton::clicked,this,[=]{
		if ( !sound_guide2->text().isEmpty() )
		{
			int step = sound_guide2->text().toInt();
			if ( MusicManager::Instance()->isPlaying(MusicManager::eTypeEffects) )
			{
				MusicManager::Instance()->stop(MusicManager::eTypeEffects);
			}
			if ( !MusicManager::Instance()->isPlaying(MusicManager::eTypeEffects) )
			{
				QVariant v(QString("newguide/%1.wav").arg(step));
				MusicManager::Instance()->play(MusicManager::eTypeEffects,1,v);
			}
		}
	});

	QPushButton * btn10=new QPushButton("string ip",this);
	btn10->setGeometry(0,300,200,20);

	QLineEdit* replace_ = new QLineEdit(this);
	replace_->setPlaceholderText("replace ip");
	replace_->setGeometry(210,300,200,20);

	QLineEdit* replace_2 = new QLineEdit(this);
	replace_2->setPlaceholderText("replace to encode");
	replace_2->setGeometry(420,300,200,20);
	connect(btn10,&QPushButton::clicked,this,[=](){
		char szText[32]={0};
		strncpy_s(szText,replace_->text().toLocal8Bit(),_countof(szText)-1);
		Replace(szText,'0','a');
		Replace(szText,'1','b');
		Replace(szText,'2','c');
		Replace(szText,'3','d');
		Replace(szText,'4','e');
		Replace(szText,'5','f');
		Replace(szText,'6','g');
		Replace(szText,'7','h');
		Replace(szText,'8','i');
		Replace(szText,'9','j');
		Replace(szText,'.','k');
		replace_2->setText(QString::fromLocal8Bit(szText));
	});

	QPushButton * btn70=new QPushButton("Font",this);
	btn70->setGeometry(0,350,200,20);
	static int n = 1000;
	connect(btn70,&QPushButton::clicked,this,[&](){
		TopHintDialog w(this);
		w.exec();
	});

	QPushButton* sount_volume = new QPushButton("sound_volume",this);
	sount_volume->setGeometry(0,400,200,20);
	QLineEdit* num_edit = new QLineEdit(this);
	num_edit->setGeometry(420,400,200,20);
	
	connect(sount_volume,&QPushButton::clicked,this,[=](){
		if ( num_edit && !num_edit->text().isEmpty() )
		{
			QString num_ = num_edit->text();
			int num = num_.toInt();
			if ( num>0)
			{
				MusicManager::Instance()->SetVolumn(MusicManager::eTypeEffects,num);
			}
		}
		
	});

	QPushButton* common_sound = new QPushButton("common_sound",this);
	common_sound->setGeometry(0,450,200,20);
	QLineEdit* ncommon_sound_edit = new QLineEdit(this);
	ncommon_sound_edit->setGeometry(420,450,200,20);

	connect(common_sound,&QPushButton::clicked,this,[=](){
		if ( ncommon_sound_edit && !ncommon_sound_edit->text().isEmpty() )
		{
			QString num_ = ncommon_sound_edit->text();
			int num = num_.toInt();
			if ( num>0)
			{
				PlayCommonSound((ECommonSoundType)num);
			}
		}

	});

	QComboBox* comboBox = new QComboBox(this);
	comboBox->setGeometry(0,500,100,30);
	comboBox->addItem(QString::fromWCharArray(L"全部"),0);
	comboBox->addItem(QString::fromWCharArray(L"战士"),1);
	comboBox->addItem(QString::fromWCharArray(L"法师"),2);
	comboBox->addItem(QString::fromWCharArray(L"射手"),3);
	comboBox->addItem(QString::fromWCharArray(L"肉盾"),4);
	comboBox->addItem(QString::fromWCharArray(L"刺客"),5);
	comboBox->addItem(QString::fromWCharArray(L"辅助"),6);
	comboBox->setView(new QListView(this));

	connect(comboBox, SIGNAL(activated(int)), this, SLOT(OnTypeActivated(int)));

	connect(comboBox, SIGNAL(highlighted(int)), this, SLOT(OnTypeHighLighted(int)));
}

music::~music()
{

}

void music::OnTypeActivated(int index)
{

}

void music::OnTypeHighLighted(int index)
{

}

int Replace(char* src,const char need_replace,const char replace_to )
{
	int n = 0;
	for (int i=0;i<strlen(src);++i)
	{
#if 0
		if (src[i]==replace_to)
		{
			src[i]=need_replace;
			n++;
		}
#else
		if (src[i]==need_replace)
		{
			src[i]=replace_to;
			n++;
		}
#endif
		
	}
	return n;
}

void TestEnum()
{
	
}