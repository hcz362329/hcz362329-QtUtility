#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include <QObject>
#include <QtMultimedia/QMediaPlayer>

//平台音效管理类
class  MusicManager : public QObject
{
	Q_OBJECT

public:
	enum EMusicType
	{
		eMusicTypeNone = 0,
		//大厅背景音乐
		eTypeLobbyBg=1,
		//选英雄背景音乐
		eTypeSelectHeroBg,
		//进入选英雄界面音乐
		eTypeEnterSelectHero,
		//选英雄倒计时音乐
		eTypeCountdown,
		//选英雄每个英雄的台词
		eTypeHeroVoice,
		//按钮音效
		eTypeButton,
		//某些特殊音效（如开宝箱等）
		eTypeEffects
	};

public:
	~MusicManager();

	static MusicManager *Instance();
	static void deleteInstance();

	//nLoopCount=-1表示无限循环
	void play(MusicManager::EMusicType type, int nLoopCount = -1, QVariant var = QVariant());
	void stop(MusicManager::EMusicType type);
	void pause(MusicManager::EMusicType type);
	void stopAll();
	bool isPlaying(MusicManager::EMusicType type);
	QVariant getAddtionArg(MusicManager::EMusicType type);
	void setBgMusicMute(bool bMute);//设置背景音乐是否静音
	void SetVolumn(MusicManager::EMusicType type,int num);
	private Q_SLOTS:
		void onError(QMediaPlayer::Error);
		void onStateChanged(QMediaPlayer::State);

private:
	MusicManager(QObject *parent = 0);
	void initMediaPlayer();
	void addMediaPlayer(MusicManager::EMusicType type, int nLoopCount = -1);

private:
	static MusicManager *m_sInstance;
	QMap<EMusicType, QMediaPlayer *> m_mapPlayer;
	QMap<EMusicType, int> m_mapLoopCount;
	QMap<EMusicType, QVariant> m_mapVariantArg;
	QList<EMusicType> m_lstMutableType; //可以设置静音的类型
	bool m_bPlayBgSound;
};

#endif // MUSICMANAGER_H
