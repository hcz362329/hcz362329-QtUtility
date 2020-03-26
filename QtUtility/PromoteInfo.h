#ifndef PromoteInfo_h
#define PromoteInfo_h


//玩家积分 stat17 重新设定代表大段晋级部分的定义
//100大段晋级中  110大段晋级第一场胜利 120大段晋级第一场失败 111 大段晋级第一场胜利第二场胜利 
//100代表大段晋级:十位第一场,个位第二场 0代表还没打,1胜利,2失败
enum ERankState
{
	eRankStateNormal						= 0,//普通
	eRankStateLargePromotion				= 100,//大段晋级中
	eRankStateLarge110						= 110,//大段晋级1胜
	eRankStateLarge120						= 120,//大段晋级第一场失败
	eRankStateLarge112						= 112,//大段晋级第一场胜利第二场失败
	eRankStateLarge121						= 121,//大段晋级第一场失败第二场胜利
	eRankStateSmallPromotion				= 200,//小段晋级中
	eRankStateAvoidRelegation				= 300,//保级赛中
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