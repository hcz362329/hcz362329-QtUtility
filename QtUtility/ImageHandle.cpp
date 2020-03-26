#include "ImageHandle.h"

#include "RotateLabel.h"
#include "Helper/QtHelper.hpp"
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include "Button.h"
#include <QTextEdit>
#include <QMessageBox>
#include "qpainterex.h"
#include "UnNormalShape.h"
#include <QDebug>
#include "QLabelPainter.h"
ImageHandle::ImageHandle(QWidget* parent )
	:QWidget(parent)
{
	/*
	QLabel* rotate = new QLabel(QString::fromWCharArray(L"顺逆旋转"),this);
	rotate->move(0,0);
	RotateLabel * label = new RotateLabel(this,"./Images/RuneBkg.png",2,true);
	label->move(50,10);

	RotateLabel * label_ = new RotateLabel(this,"./Images/RuneBkg.png",2,false);
	label_->move(190,10);*/
	

	QLabel* label_original_text = new QLabel(QString::fromWCharArray(L"原图462*260"),this);
	label_original_text->setGeometry(0,150,100,20);
	QLabel* label_original = new QLabel(this);
	//bool bLoad = image.load("./image_handle1.png");
	bool bLoad = image.load("./test.png");
	label_original->setGeometry(0,170,image.width(),image.height());
	label_original->setPixmap(QPixmap::fromImage(image));
	int interal_height = image.height()+30;
	int internal_width = image.width()+20;
	
	QComboBox* box_handle_image = new QComboBox(this);
	box_handle_image->setGeometry(0,150+interal_height,100,30);
	box_handle_image->addItem(QString::fromWCharArray(L"灰度"),1);
	box_handle_image->addItem(QString::fromWCharArray(L"饱和度"),2);
	box_handle_image->addItem(QString::fromWCharArray(L"亮度"),3);
	box_handle_image->addItem(QString::fromWCharArray(L"色相"),4);
	box_handle_image->addItem(QString::fromWCharArray(L"对比度"),5);

	QLineEdit* value_image_handle = new QLineEdit(this);
	value_image_handle->setGeometry(200,150+interal_height,100,30);


	QLabel* label_gray_level_text = new QLabel(QString::fromWCharArray(L"灰度"),this);
	label_gray_level_text->setGeometry(0,180+interal_height,100,20);
	QLabel* label_gray_level = new QLabel(this);
	gray = QtHelper::GrayScale(image);
	label_gray_level->setGeometry(0,200+interal_height,image.width(),image.height());
	label_gray_level->setPixmap(QPixmap::fromImage(gray));


	QPushButton* btn_image_handle = new QPushButton(QString::fromWCharArray(L"单独设置"),this);
	btn_image_handle->setGeometry(300,150+interal_height,100,30);
	connect(btn_image_handle,&QPushButton::clicked,this,[=]{
		int value = value_image_handle->text().toInt();
		switch(qvariant_cast<int>(box_handle_image->currentData()))
		{
		case 1:
			{
				gray = QtHelper::GrayScale(image,value);
				label_gray_level->setPixmap(QPixmap::fromImage(gray));
				label_gray_level_text->setText(box_handle_image->currentText());
			}
			break;
		case 2:
			{
				gray = QtHelper::saturation(value,image);
				label_gray_level->setPixmap(QPixmap::fromImage(gray));
				label_gray_level_text->setText(box_handle_image->currentText());
			}
			break;
		case 3:
			{
				gray = QtHelper::light(value,image);
				label_gray_level->setPixmap(QPixmap::fromImage(gray));
				label_gray_level_text->setText(box_handle_image->currentText());
			}
			break;
		case 4:
			{
				gray = QtHelper::hue(value,image);
				label_gray_level->setPixmap(QPixmap::fromImage(gray));
				label_gray_level_text->setText(box_handle_image->currentText());
			}
			break;
		case 5:
			{
				gray = QtHelper::AdjustContrast(value,image);
				label_gray_level->setPixmap(QPixmap::fromImage(gray));
				label_gray_level_text->setText(box_handle_image->currentText());
			}
			break;
		default:
			break;
		}
	});


	QString strName1 = QString::fromWCharArray(L"汉仪小隶书简");
	QString strName2 = QString::fromWCharArray(L"经典细隶书简");
	QFont font1(strName1);
	QFont font2(strName2);
	QPushButton* btn_combine = new QPushButton(QString::fromWCharArray(L"组合设置"),this);
	btn_combine->setGeometry(500,100,100,30);
	btn_combine->setFont(font1);
	QLabel* pLabelh = new QLabel(QString::fromWCharArray(L"色相"),this);
	pLabelh->setGeometry(500,130,80,30);
	QLineEdit* value_hue = new QLineEdit(this);
	value_hue->setGeometry(600,130,80,30);
	pLabelh->setFont(font1);

	QLabel* pLabels = new QLabel(QString::fromWCharArray(L"饱和度"),this);
	pLabels->setGeometry(500,160,80,30);

	QLineEdit* value_s = new QLineEdit(this);
	value_s->setGeometry(600,160,80,30);

	QLabel* pLabell = new QLabel(QString::fromWCharArray(L"亮度"),this);
	pLabell->setGeometry(500,190,80,30);
	QLineEdit* value_l = new QLineEdit(this);
	value_l->setGeometry(600,190,80,30);

	QLabel* pLabelv = new QLabel(QString::fromWCharArray(L"明度"),this);
	pLabelv->setGeometry(500,220,80,30);
	QLineEdit* value_v = new QLineEdit(this);
	value_v->setGeometry(600,220,80,30);
	
	
	QLabel* pLabelc = new QLabel(QString::fromWCharArray(L"对比度"),this);
	pLabelc->setGeometry(500,250,80,30);
	QLineEdit* value_c = new QLineEdit(this);
	value_c->setGeometry(600,250,80,30);
	pLabelc->setFont(font2);
	value_c->setFont(font2);


	QLabel* combine_label = new QLabel(this);
	
	//bool bLoad2=image_test.load("./test.png");
	//image_test = image_test.copy(0,42,138,42);
	bool bLoad2=image_test.load("./ttt.png");
	//image_test = image_test.copy(0,42,138,42);
	//lab-bg.png

	combine_label->setGeometry(800,0,image_test.width(),image_test.height());

	connect(btn_combine,&QPushButton::clicked,this,[=]{
		int h,s,l,v;
		h=s=l=v=0;
		h=value_hue->text().toInt();
		s=value_s->text().toInt();
		l=value_l->text().toInt();
		v=value_v->text().toInt();
		int c = value_c->text().toInt();
		if ( l != 0 && v != 0 )
		{
			QMessageBox::information(NULL, "Title", "v l cannot not set at a time", QMessageBox::Yes , QMessageBox::Yes);
		}
		else if (l!=0)
		{
			image_test_combine = QtHelper::GetImageByHSL(image_test,h,s,l,c);
		}
		else if (v!=0)
		{
			image_test_combine = QtHelper::GetImageByHSV(image_test,h,s,v,c);
		}
		else
		{
			image_test_combine = QtHelper::GetImageByHSL(image_test,h,s,l,c);
		}
		
		combine_label->setPixmap(QPixmap::fromImage(image_test_combine));
	});


	QLabel* pixmap_rune = new QLabel(this);
	
	QPixmap pixmap1,pixmap2,pixmap3;
	bool bLoad3= pixmap1.load("./290.png");
	bLoad3= pixmap2.load("./ink.png");
	bLoad3= pixmap3.load("./zhaoyun.jpg");
	QPixmap pixmap4,pixmap5,pixmap6;
	pixmap6.load("./Images/RuneBkg.png");
	QtHelper::GetMaskImage(pixmap3,pixmap4,pixmap2,50,0,500,500);
	pixmap_rune->setGeometry(0,400,pixmap2.width(),pixmap2.height());
	pixmap_rune->setPixmap(pixmap4);

	//pixmap6 = QtHelper::GetRoundPixmapByColor(100,Qt::black);
	pixmap6.load("./circle_black.png");
	QLabel* pixmap_rune2 = new QLabel(this);

	QtHelper::GetMaskImage(pixmap3,pixmap5,pixmap6,0,0,400,400);
	pixmap5=pixmap5.scaled(QSize(100,100),Qt::KeepAspectRatio,Qt::SmoothTransformation);
	pixmap_rune2->setGeometry(pixmap2.width()+20,500,pixmap5.width(),pixmap5.height());
	pixmap_rune2->setPixmap(pixmap5);

	UnNormalShape * shape = new UnNormalShape(pixmap5,pixmap1,this);
	shape->setGeometry(pixmap2.width()+20,700,pixmap5.width(),pixmap5.height());

	

	pixmap_transprency_ = QtHelper::GetSymmetryGradientTransparencyPixmap(230,193,93,500,136);
	bool bSave = pixmap_transprency_.save("./transparency.png");
	if ( bSave )
	{
		qDebug()<<"save ";
	}

	QVector<STHSLV> vec;

	STHSLV stHSLV;stHSLV.type=0;
	vec.push_back(stHSLV);

	STHSLV stHSLV2;stHSLV2.type=0;stHSLV2.hue=0;stHSLV2.saturation=0;stHSLV2.light=10;stHSLV2.contrast=35;
	vec.push_back(stHSLV2);

	STHSLV stHSLV3;stHSLV3.type=0;stHSLV3.hue=0;stHSLV3.saturation=100;stHSLV3.light=10;stHSLV2.contrast=35;
	vec.push_back(stHSLV3);

	STHSLV stHSLV4; stHSLV4.type=2;
	vec.push_back(stHSLV4);
	QImage image("./test.png");
	
	QtHelper::SaveImageToNative(image,vec,QString("./test2.png"));
	image_combine_=QImage("./test2.png");

	QPushButton * btn_ = new QPushButton(this);
	btn_->setGeometry(850,600,130,30);
	QString strSheet = QString("QPushButton{border-width: 0;border-radius: 0;border-image: url(./test2.png) 0 0 0 0 repeat;}\
	QPushButton:hover {border-image: url(./test2.png) 30 0 0 0 repeat;}\
	QPushButton:pressed{border-image: url(./test2.png) 60 0 0 0 repeat;}\
	QPushButton:disabled{border-image: url(./test2.png) 90 0 0 0 repeat;}");
	btn_->setStyleSheet(strSheet);

	QPixmap pixmap_HeroSkilled;
	pixmap_HeroSkilled = QtHelper::GetHeroSkilledPixmap();
	QLabel* pLabel_HeroSkilled = new QLabel(this);
	pLabel_HeroSkilled->setGeometry(850,700,209,48);
	pLabel_HeroSkilled->setPixmap(pixmap_HeroSkilled);

	QPushButtonEx* btn_render_text = new QPushButtonEx(this);
	btn_render_text->setGeometry(850,800,41,97);

	QString strSheet2 = QString("QPushButton{border-width: 0;border-radius: 0;border-image: url(./nav_heroLeft.png) 0 0 0 0 repeat;}\
								QPushButton:hover {border-image: url(./nav_heroLeft.png) 97 0 0 0 repeat;}\
								QPushButton:pressed{border-image: url(./nav_heroLeft.png) 97 0 0 0 repeat;}\
								QPushButton:disabled{border-image: url(./nav_heroLeft.png) 97 0 0 0 repeat;}");
	btn_render_text->setStyleSheet(strSheet2);
	QString strText = QString::fromWCharArray(L"英\n雄");
	QString strFamily = QString::fromWCharArray(L"汉仪小隶书简");
	STRenderText stRenderText;
	stRenderText.is_TextFlag=true;
	stRenderText.fontText.setFamily(strFamily);
	stRenderText.fontText.setPixelSize(22);
	stRenderText.fontText.setBold(false);
	stRenderText.text_color = QColor(187,175,149);
	stRenderText.strRenderText = strText;
	stRenderText.flag = Qt::AlignCenter | Qt::TextWordWrap;
	btn_render_text->SetRenderText(stRenderText);


	QPixmap pix2=QtHelper::GetPixmapBySmallBg2("./public_bg_tc.png",60,60,454,335);
	pix2.save("./public_bg_tc2.png");

	QtHelper::GetPurchasePixmap_();

	/*QLabelPainter * label___ = new QLabelPainter(this);
	stRenderText.strRenderText = QString("<span style='font-size:12px;font-family:Microsoft YaHei;font-weight:400;color:rgba(201,182,150,1);line-height:30px;'>[全平台]<span><a href='4,5000249,huchenzhi' style='font-size:12px;font-family:Microsoft YaHei;font-weight:400;color: #1FC5ED;;line-height:30px;text-decoration:none;'>huchenzhi</a></span>：老司机，请上车！<span style='font-size:12px;font-family:Microsoft YaHei;font-weight:400;color:rgba(234,150,3,1);line-height:30px;'>匹配·5v5模式 (1/5) </span></span><span><a href='2,5000249,huchenzhi' style='font-size:12px;font-family:Microsoft YaHei;color: #1FC5ED;'>立即加入>></a></span>");

	label___->setText(stRenderText.strRenderText);
	label___->setGeometry(850,900,300,40);*/
}

void QPushButtonEx::paintEvent(QPaintEvent *event)
{
	QPushButton::paintEvent(event);
	QPainterEx painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	if ( !m_stRenderText.strRenderText.isEmpty())
	{
		painter.save();

		painter.setFont(m_stRenderText.fontText);
		painter.setPen(m_stRenderText.text_color);
		painter.setStrokePen(QPen(m_stRenderText.stroke_color, m_stRenderText.stroke_width));
		painter.drawText(rect(),Qt::AlignCenter|Qt::TextWordWrap ,m_stRenderText.strRenderText);
		painter.restore();
	}
}

QPushButtonEx::QPushButtonEx(QWidget* parent)
	:QPushButton(parent)
{

}

QPushButtonEx::~QPushButtonEx()
{

}

void QPushButtonEx::SetRenderText(const STRenderText & text)
{
	m_stRenderText = text;
}

ImageHandle::~ImageHandle()
{

}

void ImageHandle::paintEvent(QPaintEvent *)
{
	QPainterEx painter(this);

	

	painter.setRenderHint(QPainter::Antialiasing);
	painter.save();
	QRect rcText(400,0, 500, 60);
	QString strName1 = QString::fromWCharArray(L"汉仪小隶书简");

	QFont font(strName1);

	font.setPixelSize(20);
	font.setBold(true);
	painter.setFont(font);
	painter.setPen(QColor("#AC9369"));
	painter.setStrokePen(QPen(QColor("#000000"), 2));

	painter.drawStrokeText(rcText,QString::fromWCharArray(L"汉仪小隶书简\n。，：？；关羽"), QTextOption(Qt::AlignLeft | Qt::AlignTop));
	
	painter.drawText(QRect(850,240,200,30),Qt::AlignLeft | Qt::AlignVCenter,QString::fromWCharArray(L"英雄,装备,魂玉,觉醒"));
	
	painter.restore();

	painter.save();
	QString strName2 = QString::fromWCharArray(L"经典细隶书简");
	QFont font2(strName2);
	font2.setPixelSize(20);
	font2.setBold(true);
	painter.setFont(font2);
	painter.setPen(QColor("#b9c696"));
	painter.setStrokePen(QPen(QColor("#000000"), 2));
	
	QRect rcText2(400, 40, 500, 30);
	painter.drawStrokeText(rcText2,QString::fromWCharArray(L"经典细隶书简。，：？；\n关羽"), QTextOption(Qt::AlignLeft | Qt::AlignTop));
	QRect rcText3(850, 40, 500, 30);
	painter.drawStrokeText(rcText3,QString::fromWCharArray(L"制作线性渐变带颜色值的透明度图片："), QTextOption(Qt::AlignLeft | Qt::AlignTop));
	painter.restore();
	
	if ( !pixmap_transprency_.isNull() )
	{
		painter.drawPixmap(850,100,pixmap_transprency_);
	}

	if ( !image_combine_.isNull() )
	{
		painter.drawImage(850,285,image_combine_);
	}
	
}