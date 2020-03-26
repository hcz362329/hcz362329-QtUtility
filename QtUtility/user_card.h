#pragma once

#include <QWidget>
#include <QLabel>

const QString strTestCommonStyle = QString("QLabel{background:red;}");
const QString strGroupIdStyle = QString("font-size:11px;font-family:PingFangSC-Regular,PingFang SC;font-weight:400;color:rgba(255, 255, 255,255);line-height:16px;");
const QString strUqIdStyle = strGroupIdStyle;
const QString strSignStyle = strUqIdStyle;
const QString strNumStyle = QString("font-size:14px;font - family:PingFangSC - Regular, PingFang SC;font-weight:400;color:rgba(255,255,255,255);line-height:20px;");
const QString strFocusStyle = QString("font - size:10px;font-family:PingFangSC-Regular,PingFang SC;font-weight:400;color:rgba(153,153,153,255);line-height:14px;");
const QString strOpenStyle = QString("width:66px;height:16px;font-size:11px;font-family:PingFangSC-Regular,PingFang SC;font - weight:400;color:rgba(255,255,255,255);line-height:16px;");
const QString strNameStyle = QString("font-size:12px;font-family:PingFangSC-Medium,PingFang SC;font-weight:500;color:rgb(255,255,255);line-height:17px;");
#include "rounded_widget.h"
class UserCard : public RoundedWidget
{
	Q_OBJECT

public:
	UserCard(QWidget *parent = Q_NULLPTR);
	~UserCard();

	void OpenTest();
	QPixmap ScaledPixmap(const QString & strPixmap, QSize size);
private:
	QLabel* pLabelHead;
	QLabel* pLabelName;
	QLabel* pLabelGender;
	QLabel* pLabelYork;//爵位
	QLabel* pLabelLevel;
	QLabel* pFunsGroup;

	QLabel* pLabelGroupId;
	QLabel* pLabelUqid;
	QLabel* pLabelSign;//个人签名

	QLabel* pFocusOnNum;//关注
	QLabel* pFocusOn;


	QLabel* pFunsNum;//粉丝
	QLabel* pFuns;

	QLabel* pGiftsNum;//收礼
	QLabel* pGifts;

	QLabel* pSendGiftsNum;//送礼
	QLabel* pSendGifts;

	QLabel* pSeprateLine;

	QLabel* pOpenRoomTime;
	QLabel* pOpenTime1;
	QLabel* pOpenTime2;
	QLabel* pOpenTime3;
};
