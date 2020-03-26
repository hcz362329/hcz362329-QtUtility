#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include <QObject>
#include <QtMultimedia/QMediaPlayer>

//ƽ̨��Ч������
class  MusicManager : public QObject
{
	Q_OBJECT

public:
	enum EMusicType
	{
		eMusicTypeNone = 0,
		//������������
		eTypeLobbyBg=1,
		//ѡӢ�۱�������
		eTypeSelectHeroBg,
		//����ѡӢ�۽�������
		eTypeEnterSelectHero,
		//ѡӢ�۵���ʱ����
		eTypeCountdown,
		//ѡӢ��ÿ��Ӣ�۵�̨��
		eTypeHeroVoice,
		//��ť��Ч
		eTypeButton,
		//ĳЩ������Ч���翪����ȣ�
		eTypeEffects
	};

public:
	~MusicManager();

	static MusicManager *Instance();
	static void deleteInstance();

	//nLoopCount=-1��ʾ����ѭ��
	void play(MusicManager::EMusicType type, int nLoopCount = -1, QVariant var = QVariant());
	void stop(MusicManager::EMusicType type);
	void pause(MusicManager::EMusicType type);
	void stopAll();
	bool isPlaying(MusicManager::EMusicType type);
	QVariant getAddtionArg(MusicManager::EMusicType type);
	void setBgMusicMute(bool bMute);//���ñ��������Ƿ���
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
	QList<EMusicType> m_lstMutableType; //�������þ���������
	bool m_bPlayBgSound;
};

#endif // MUSICMANAGER_H
