#ifndef PromoteInfo_h
#define PromoteInfo_h


//��һ��� stat17 �����趨�����ν������ֵĶ���
//100��ν�����  110��ν�����һ��ʤ�� 120��ν�����һ��ʧ�� 111 ��ν�����һ��ʤ���ڶ���ʤ�� 
//100�����ν���:ʮλ��һ��,��λ�ڶ��� 0����û��,1ʤ��,2ʧ��
enum ERankState
{
	eRankStateNormal						= 0,//��ͨ
	eRankStateLargePromotion				= 100,//��ν�����
	eRankStateLarge110						= 110,//��ν���1ʤ
	eRankStateLarge120						= 120,//��ν�����һ��ʧ��
	eRankStateLarge112						= 112,//��ν�����һ��ʤ���ڶ���ʧ��
	eRankStateLarge121						= 121,//��ν�����һ��ʧ�ܵڶ���ʤ��
	eRankStateSmallPromotion				= 200,//С�ν�����
	eRankStateAvoidRelegation				= 300,//��������
};

#include "BaseWidget.h"
#include <QLabel>
class PromoteInfo : public BaseWidget
{
	Q_OBJECT
public:
	explicit PromoteInfo(QWidget* parent=0);
	~PromoteInfo();
	void SetRankInfo(int score,int state);
private:
	void SetRankState(ERankState eState);
	void SetScore(int score);
protected:
	void paintEvent(QPaintEvent *);
private:
	QPixmap m_pixBG;
	QPixmap m_pixWin;
	QPixmap m_pixDefeat;
	QPixmap m_pixDoubt;
	QLabel* m_pLabelTip;
	QLabel* m_pLabel1;
	QLabel* m_pLabel2;
	QLabel* m_pLabel3;
	QString m_strRankInfo;
	QString m_strRankName;
};

#endif