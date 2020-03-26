#include "WinHttpWidget.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "http_define.h"
#include "./winhttp/utility.h"
#include "WinHttpHelper.hpp"
WinHttpWidget::WinHttpWidget(QWidget* parent)
	: QWidget(parent)
{
	resize(400,450);
	QLabel * label1 = new QLabel("option name",this);
	label1->setGeometry(0,0,150,20);

	QLineEdit* name_edit = new QLineEdit(this);
	name_edit->setGeometry(150,0,200,20);
	name_edit->setPlaceholderText("input option name");

	QLabel * user_id = new QLabel("user_id",this);
	user_id->setGeometry(0,50,150,20);

	QLineEdit* user_id_edit = new QLineEdit(this);
	user_id_edit->setGeometry(150,50,200,20);
	user_id_edit->setPlaceholderText("input user_id");

	QLabel * user_mac = new QLabel("user_mac",this);
	user_mac->setGeometry(0,100,150,20);

	QLineEdit* user_mac_edit = new QLineEdit(this);
	user_mac_edit->setGeometry(150,100,200,20);
	user_mac_edit->setPlaceholderText("input user_mac");

	QLabel * user_param = new QLabel("user_param",this);
	user_param->setGeometry(0,150,150,20);

	QLineEdit* user_param_edit = new QLineEdit(this);
	user_param_edit->setGeometry(150,150,200,20);
	user_param_edit->setPlaceholderText("input user_param");

	QPushButton* btn_ = new QPushButton("Statics Send",this);
	btn_->setGeometry(0,200,150,20);
	connect(btn_,&QPushButton::clicked,this,[=](){
		STStatisticData* pData = new STStatisticData;

		if (!name_edit->text().isEmpty())
		{
			strncpy_s(pData->strName,name_edit->text().toLocal8Bit(),_countof(pData->strName)-1);
		}
		if (!user_id_edit->text().isEmpty())
		{
			pData->uiUserId = user_id_edit->text().toLong();
		}
		if (!user_mac_edit->text().isEmpty())
		{
			strncpy_s(pData->strMac,user_mac_edit->text().toLocal8Bit(),_countof(pData->strMac)-1);
		}
		if (!user_param_edit->text().isEmpty())
		{
			strncpy_s(pData->strParam,user_param_edit->text().toLocal8Bit(),_countof(pData->strParam)-1);
		}

		WinHttpHelper::HttpPost(pData);
	});
}

WinHttpWidget::~WinHttpWidget()
{

}