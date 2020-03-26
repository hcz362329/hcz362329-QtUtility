#include "musicmanager.h"
#include <QDebug>
#include <QMessageBox>
#include<QDir>
MusicManager *MusicManager::m_sInstance = NULL;

MusicManager::MusicManager(QObject *parent)
	: QObject(parent)
	, m_bPlayBgSound(true)
{
	initMediaPlayer();
}

MusicManager::~MusicManager()
{
	foreach(QMediaPlayer *player, m_mapPlayer)
	{
		player->stop();
		player->deleteLater();
	}
	m_mapPlayer.clear();
	m_mapLoopCount.clear();
	m_mapVariantArg.clear();
	m_lstMutableType.clear();
	//parent析构时，为了防止单例对象指针变成野指针
	m_sInstance = NULL;
}

MusicManager* MusicManager::Instance()
{
	if (m_sInstance == NULL)
	{
		m_sInstance = new MusicManager();
	}
	return m_sInstance;
}

void MusicManager::deleteInstance()
{
	m_sInstance->deleteLater();
}

void MusicManager::initMediaPlayer()
{
	addMediaPlayer(eTypeLobbyBg);
	addMediaPlayer(eTypeSelectHeroBg);
	addMediaPlayer(eTypeEnterSelectHero, 1);
	addMediaPlayer(eTypeCountdown, 1);
	addMediaPlayer(eTypeHeroVoice, 1);
	addMediaPlayer(eTypeButton, 1);
	addMediaPlayer(eTypeEffects, 1);

	m_lstMutableType.append(eTypeLobbyBg);
	m_lstMutableType.append(eTypeSelectHeroBg);
}

void MusicManager::addMediaPlayer(MusicManager::EMusicType type, int nLoopCount)
{
	if (!m_mapPlayer.contains(type))
	{
		QMediaPlayer *player = new QMediaPlayer;
		connect(player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(onError(QMediaPlayer::Error)));
		connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(onStateChanged(QMediaPlayer::State)));

		m_mapPlayer.insert(type, player);
		m_mapLoopCount.insert(type, nLoopCount);
		m_mapVariantArg.insert(type, QVariant());

		QString strFile;
		switch (type)
		{
		case eTypeLobbyBg:
			strFile = QDir::currentPath() + "/Sound/mus_lobbyBg.wav";
			break;
		case eTypeSelectHeroBg:
			strFile = QDir::currentPath() + "/Sound/mus_selectheroBg.wav";
			break;
		case eTypeEnterSelectHero:
			strFile = QDir::currentPath() + "/Sound/mus_enterselecthero.wav";
			break;
		case eTypeCountdown:
			strFile = QDir::currentPath() + "/Sound/mus_countdown.wav";
			break;
		case eTypeHeroVoice:
		case eTypeButton:
		case eTypeEffects:
			break;
		default:
			break;
		}

		if (!strFile.isEmpty() && QFile::exists(strFile))
		{
			QUrl url = QUrl::fromLocalFile(strFile);
			if (url.isValid())
			{
				QMediaContent mc(url);
				if (!mc.isNull())
				{
					player->setMedia(mc);
				}
			}
		}
	}
}

void MusicManager::play(MusicManager::EMusicType type, int nLoopCount, QVariant var)
{
	QString strFile;
	bool bResValid = false;
	switch (type)
	{
	case eTypeLobbyBg:
	case eTypeSelectHeroBg:
	case eTypeEnterSelectHero:
		if (!m_bPlayBgSound )
		{
			return;
		}
		bResValid = true;
		break;
	case eTypeCountdown:
		bResValid = true;
		break;
	case eTypeHeroVoice:
		strFile = QString("%1/Sound/%2_vo_xuan.wav").arg(QDir::currentPath()).arg(var.toInt());
		break;
	case eTypeButton:
		strFile = QString("%1/Sound/%2").arg(QDir::currentPath()).arg(var.toString());
		break;
	case eTypeEffects:
		strFile = QString("%1/Sound/%2").arg(QDir::currentPath()).arg(var.toString());
		break;
	default:
		break;
	}
	QMediaPlayer *player = m_mapPlayer.value(type);
	if (player != nullptr)
	{
		if (!strFile.isEmpty() && QFile::exists(strFile))
		{
			QUrl url = QUrl::fromLocalFile(strFile);
			if (url.isValid())
			{
				QMediaContent mc(url);
				if (!mc.isNull())
				{
					
					player->setMedia(mc);
					bResValid = true;
				}
			}
		}
		if (bResValid && player->availability() == QMultimedia::Available)
		{
			m_mapLoopCount[type] = nLoopCount;
			m_mapVariantArg[type] = var;
			player->play();
			if ( type == eTypeSelectHeroBg || type == eTypeEnterSelectHero)
			{
				//player->setVolume(30);
			}
		}
		else
		{
			qDebug()<<"bResValid: "<< bResValid<< "; QMultimedia::Available: "<< player->availability();
		}
	}
}

void MusicManager::stop(MusicManager::EMusicType type)
{
	m_mapLoopCount[type] = 0;
	QMediaPlayer *player = m_mapPlayer.value(type);
	if (player != nullptr)
	{
		player->stop();
	}
}

void MusicManager::pause(MusicManager::EMusicType type)
{
	QMediaPlayer *player = m_mapPlayer.value(type);
	if (player != nullptr)
	{
		player->pause();
	}
}

void MusicManager::stopAll()
{
	foreach(QMediaPlayer *player, m_mapPlayer)
	{
		player->stop();
	}
}

bool MusicManager::isPlaying(MusicManager::EMusicType eType)
{
	QMediaPlayer *player = m_mapPlayer.value(eType);
	if (player != nullptr)
	{
		return (player->state() == QMediaPlayer::PlayingState);
	}
	return false;
}

void MusicManager::SetVolumn(MusicManager::EMusicType type,int num)
{

	if ( MusicManager::eMusicTypeNone == type)
	{
		foreach(QMediaPlayer *player, m_mapPlayer)
		{
			if ( num > 0 )
			{
				player->setVolume(num);
			}
		}
	}
	else
	{
		m_mapPlayer[eTypeLobbyBg]->setVolume(num);
		m_mapPlayer[eTypeSelectHeroBg]->setVolume(num);
		m_mapPlayer[eTypeEnterSelectHero]->setVolume(num);

		m_mapPlayer[eTypeCountdown]->setVolume(num);
		m_mapPlayer[eTypeHeroVoice]->setVolume(num);
		m_mapPlayer[eTypeEffects]->setVolume(num);

		m_mapPlayer[type]->setVolume(num);
	}
}

QVariant MusicManager::getAddtionArg(MusicManager::EMusicType type)
{
	if (m_mapVariantArg.contains(type))
	{
		return m_mapVariantArg[type];
	}
	return QVariant();
}

void MusicManager::setBgMusicMute(bool bMute)
{
	foreach (EMusicType type, m_lstMutableType)
	{
		QMediaPlayer *player = m_mapPlayer.value(type);
		if (player != nullptr)
		{
			player->setMuted(bMute);
		}
	}
}

void MusicManager::onStateChanged(QMediaPlayer::State state)
{
	if (state == QMediaPlayer::StoppedState)
	{
		QMediaPlayer *player = qobject_cast<QMediaPlayer *>(sender());
		if (player != nullptr)
		{
			EMusicType eType = m_mapPlayer.key(player);
			int nLoopCount = m_mapLoopCount.value(eType);
			//0:正常次数播放完或者调了MusicManager::stop()方法
			if (nLoopCount != 0)
			{
				if (-1 == nLoopCount)
				{
					player->play();
					if ( eType == eTypeSelectHeroBg )
					{
						//player->setVolume(30);
					}
				}
				else
				{
					nLoopCount--;
					m_mapLoopCount[eType] = nLoopCount;

					if (nLoopCount > 0)//继续循环
					{
						player->play();
						qDebug() << "QMediaPlayer::StoppedState - EMusicType" << eType << "nLoopCount" << nLoopCount;
					}
				}
			}
		}
	}
}

void MusicManager::onError(QMediaPlayer::Error error)
{
	QMediaPlayer *player = qobject_cast<QMediaPlayer *>(sender());
	if (player != nullptr)
	{
		qDebug() << "MusicManager::onError - " << player->errorString();
		qDebug()<<"QMediaPlayer error: " << player->errorString();
	}
}
