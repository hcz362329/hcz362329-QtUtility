#ifndef QTHELPER_H
#define QTHELPER_H
#include <QImage>
#include <Windows.h>
#include <QPainter>
#include <algorithm>
#include <QVector>
#include <QLinearGradient>
#include <QDebug>
#include "qpainterex.h"
struct STHSLV
{
	int hue;
	int saturation;
	int light;
	int value;
	int gray;//可不填,不填时会填充默认值
	int contrast;//对比度
	int type;//type:0 亮度 type:1 明度 type:2 置灰
	STHSLV()
	{
		hue=0;
		saturation=0;
		light=0;
		value=0;
		gray=0;
		contrast=0;
		type=0;
	}
};

class QtHelper
{
public:
	static QImage GetGrayPixmap(const QString & strPath)
	{
		QImage image;
		bool bLoad = image.load(strPath);
		if ( bLoad )
		{
			int nWidth  = image.width();
			int nHeight = image.height();
			QImage imgGray(nWidth,nHeight,QImage::Format_ARGB32);
			for (int i = 0 ; i < nWidth ; i++)
			{
				for ( int j = 0; j < nHeight ; j++)
				{
					QRgb pixel = image.pixel(i,j);
					int gray = qGray(pixel);
					int nAlpha = qAlpha(pixel);
					QRgb grayPixel = qRgba(gray,gray,gray,nAlpha);
					imgGray.setPixel(i,j,grayPixel);
				}
			}
			return imgGray;
		}
		else
		{
			MessageBoxA(0,"image load failed",0,0);
		}
		return image;
	}

	static QPixmap GetRedPixmap(int w,int h)
	{
		QPixmap pixmap = QPixmap(w, h);
		pixmap.fill(Qt::transparent);
		QPainter painter;
		painter.begin(&pixmap);

		painter.setBrush(QColor("#FF3600"));
		painter.drawRect(QRect(0,0,w,h));

		painter.end();
		return pixmap;
	}

	static QPixmap GetRoundPixmapByColor(int radius,QColor color)
	{
		QPixmap pixmap = QPixmap(radius*2, radius*2);
		pixmap.fill(Qt::transparent);
		QPainter painter;
		painter.begin(&pixmap);
		painter.setRenderHint(QPainter::Antialiasing,true);
		painter.setBrush(color);
		painter.drawEllipse(QRect(0,0,radius*2,radius*2));

		painter.end();
		return pixmap;
	}

	//通过颜色值获得对称性透明度图片
	static QPixmap GetSymmetryGradientTransparencyPixmap(int r, int g, int b,int width,int height)
	{
		QPixmap pixmap = QPixmap(width, height);
		pixmap.fill(Qt::transparent);
		QPainter painter;
		painter.begin(&pixmap);
		// 反走样
		painter.setRenderHint(QPainter::Antialiasing, true);

		QLinearGradient linearGradient(0,0,width-1,0);


		linearGradient.setColorAt(0,QColor(r,g,b,0));
		linearGradient.setColorAt(0.5,QColor(r,g,b,255));
		linearGradient.setColorAt(1,QColor(r,g,b,0));
		linearGradient.setSpread(QGradient::PadSpread);


		painter.setPen(QColor(230,193,93,0));
		painter.setBrush(linearGradient);
		painter.drawRect(0,0,width,height);

		painter.end();
		return pixmap;
	}
	

	static QPixmap GetGradientPixmap(int w,int h)
	{
		QPixmap pixmap = QPixmap(w, h);
		pixmap.fill(Qt::transparent);
		QPainter painter;
		painter.begin(&pixmap);

		// 反走样
		painter.setRenderHint(QPainter::Antialiasing, true);

		// 设置渐变色
		QLinearGradient linear(QPointF(0, 0), QPointF(w-1, h-1));
		linear.setColorAt(0, QColor("#F5A238"));
		linear.setColorAt(1, QColor("#E6C15D"));

		// 设置显示模式
		linear.setSpread(QGradient::PadSpread);

		//// 设置画笔颜色、宽度
		//painter.setPen(QPen(QColor(0, 160, 230), 2));

		// 设置画刷填充
		painter.setBrush(linear);

		// 绘制椭圆
		painter.drawRect(QRect(0, 0, w, h));
		painter.end();
		return pixmap;
	}

	static QPixmap GetPartPixmap(const QString strPath,int x,int y,int w,int h)
	{
		QPixmap srcPix;
		QPixmap pixmap = QPixmap(w, h);
		bool bLoad = srcPix.load(strPath);
		if ( bLoad )
		{
			pixmap.fill(Qt::transparent);
			QPainter painter;
			pixmap = srcPix.copy(x,y,w,h);
			painter.begin(&pixmap);
			painter.end();
		}
		return pixmap;
	}

	static QPixmap GetPixmapByColor(QColor color,int w,int h)
	{
		
		QPixmap pixmap = QPixmap(w, h);
		//pixmap.fill(Qt::transparent);
		QPainter painter;
		//painter.setPen(color);
		painter.setBrush(color);
		painter.begin(&pixmap);
		painter.drawRect(QRect(0, 0, w-1, h-1));
		painter.end();
		return pixmap;
	}

	static QPixmap GetPixmapHalfOpacity()
	{
		QPixmap pixmap = QPixmap(1280, 768);
		pixmap.fill(Qt::transparent);
		QPainter painter;
		painter.begin(&pixmap);
		painter.setRenderHint(QPainter::Antialiasing,true);

		painter.setBrush(QColor(0,0,0,0.5*255));
		painter.drawRect(QRect(0,0,1280,768));

		painter.end();
		pixmap.save("./halfopacity.png");
		return pixmap;
	}

	static QPixmap GetTrumpetPixmap2()
	{
		QPixmap pixmap = QPixmap(102, 26);
		pixmap.fill(Qt::transparent);
		QPainter painter;
		painter.begin(&pixmap);
		painter.setRenderHint(QPainter::Antialiasing,true);
		
		painter.setBrush(QColor(34,33,36,0.95*255));
		painter.drawRect(QRect(0,0,102,26));
		
		QPen pen(QColor("#786F56"));
		pen.setWidth(2);
		painter.setPen(pen);
		painter.drawRect(QRect(0,0,102,26));

		painter.end();
		pixmap.save("./trumpet2.png");
		return pixmap;
	}

	static QPixmap GetNormalPixmap()
	{
		QPixmap pixmap = QPixmap(1280, 720);
		pixmap.fill(Qt::transparent);
		QPainter painter;
		painter.begin(&pixmap);
		painter.setRenderHint(QPainter::Antialiasing, true);
		painter.setOpacity(0.1);
		painter.setBrush(QColor(36, 35, 40, 0.1 * 255));
		painter.drawRect(QRect(0, 0, 1279, 719));

		QPen pen(QColor(36, 35, 40));
		pen.setWidth(1);
		painter.setPen(pen);
		painter.drawRect(QRect(0, 0, 1279, 719));

		painter.end();
		pixmap.save("./normal.png");
		return pixmap;
	}


	static QPixmap createtext1()
	{
		QPixmap pixmap = QPixmap(130, 20);
		pixmap.fill(Qt::transparent);
		QPainter painter;
		painter.begin(&pixmap);
		painter.setRenderHint(QPainter::Antialiasing,true);
		QPen pen(QColor(242,221,186, 255));
		painter.setPen(pen);
		QFont font;
		font.setPixelSize(16);
		painter.setFont(font);
		QString strText = QString::fromWCharArray(L"充值金额：6元");
		painter.drawText(QRect(0,0,130,20),Qt::AlignLeft|Qt::AlignVCenter,strText);

		painter.end();
		pixmap.save("./text1.png");
		return pixmap;
	}
	static QPixmap createtext2()
	{
		QPixmap pixmap = QPixmap(130, 20);
		pixmap.fill(Qt::transparent);
		QPainter painter;
		painter.begin(&pixmap);
		painter.setRenderHint(QPainter::Antialiasing,true);
		QPen pen(QColor(242,221,186, 255));
		painter.setPen(pen);
		QFont font;
		font.setPixelSize(16);
		painter.setFont(font);
		QString strText = QString::fromWCharArray(L"充值金额：25元");
		painter.drawText(QRect(0,0,130,20),Qt::AlignLeft|Qt::AlignVCenter,strText);

		painter.end();
		pixmap.save("./text2.png");
		return pixmap;
	}
	static QPixmap createtext3()
	{
		QPixmap pixmap = QPixmap(130, 20);
		pixmap.fill(Qt::transparent);
		QPainter painter;
		painter.begin(&pixmap);
		painter.setRenderHint(QPainter::Antialiasing,true);
		QPen pen(QColor(242,221,186, 255));
		painter.setPen(pen);
		QFont font;
		font.setPixelSize(16);
		painter.setFont(font);
		QString strText = QString::fromWCharArray(L"充值金额：78元");
		painter.drawText(QRect(0,0,130,20),Qt::AlignLeft|Qt::AlignVCenter,strText);

		painter.end();
		pixmap.save("./text3.png");
		return pixmap;
	}
	static QPixmap createtext4()
	{
		QPixmap pixmap = QPixmap(130, 20);
		pixmap.fill(Qt::transparent);
		QPainter painter;
		painter.begin(&pixmap);
		painter.setRenderHint(QPainter::Antialiasing,true);
		QPen pen(QColor(242,221,186, 255));
		painter.setPen(pen);
		QFont font;
		font.setPixelSize(16);
		painter.setFont(font);
		QString strText = QString::fromWCharArray(L"充值金额：158元");
		painter.drawText(QRect(0,0,130,20),Qt::AlignLeft|Qt::AlignVCenter,strText);

		painter.end();
		pixmap.save("./text4.png");
		return pixmap;
	}
	static QPixmap createtext5()
	{
		QPixmap pixmap = QPixmap(130, 20);
		pixmap.fill(Qt::transparent);
		QPainter painter;
		painter.begin(&pixmap);
		painter.setRenderHint(QPainter::Antialiasing,true);
		QPen pen(QColor(242,221,186, 255));
		painter.setPen(pen);
		QFont font;
		font.setPixelSize(16);
		painter.setFont(font);
		QString strText = QString::fromWCharArray(L"充值金额：258元");
		painter.drawText(QRect(0,0,130,20),Qt::AlignLeft|Qt::AlignVCenter,strText);

		painter.end();
		pixmap.save("./text5.png");
		return pixmap;
	}
	static QPixmap createtext6()
	{
		QPixmap pixmap = QPixmap(130, 20);
		pixmap.fill(Qt::transparent);
		QPainter painter;
		painter.begin(&pixmap);
		painter.setRenderHint(QPainter::Antialiasing,true);
		QPen pen(QColor(242,221,186, 255));
		painter.setPen(pen);
		QFont font;
		font.setPixelSize(16);
		painter.setFont(font);
		QString strText = QString::fromWCharArray(L"充值金额：518元");
		painter.drawText(QRect(0,0,130,20),Qt::AlignLeft|Qt::AlignVCenter,strText);

		painter.end();
		pixmap.save("./text6.png");
		return pixmap;
	}
	static QPixmap createtext7()
	{
		QPixmap pixmap = QPixmap(140, 20);
		pixmap.fill(Qt::transparent);
		QPainter painter;
		painter.begin(&pixmap);
		painter.setRenderHint(QPainter::Antialiasing,true);
		QPen pen(QColor(242,221,186, 255));
		painter.setPen(pen);
		QFont font;
		font.setPixelSize(16);
		painter.setFont(font);
		QString strText = QString::fromWCharArray(L"充值金额：1288元");
		painter.drawText(QRect(0,0,140,20),Qt::AlignLeft|Qt::AlignVCenter,strText);

		painter.end();
		pixmap.save("./text7.png");
		return pixmap;
	}
	static QPixmap createtext8()
	{
		QPixmap pixmap = QPixmap(140, 20);
		pixmap.fill(Qt::transparent);
		QPainter painter;
		painter.begin(&pixmap);
		painter.setRenderHint(QPainter::Antialiasing,true);
		QPen pen(QColor(242,221,186, 255));
		painter.setPen(pen);
		QFont font;
		font.setPixelSize(16);
		painter.setFont(font);
		QString strText = QString::fromWCharArray(L"充值金额：2888元");
		painter.drawText(QRect(0,0,140,20),Qt::AlignLeft|Qt::AlignVCenter,strText);

		painter.end();
		pixmap.save("./text8.png");
		return pixmap;
	}

	static QPixmap createtext9()
	{
		QPixmap pixmap = QPixmap(130, 20);
		pixmap.fill(Qt::transparent);
		QPainter painter;
		painter.begin(&pixmap);
		painter.setRenderHint(QPainter::Antialiasing,true);
		QPen pen(QColor(255,0,0, 255));
		painter.setPen(pen);
		QFont font;
		font.setPixelSize(16);
		painter.setFont(font);
		QString strText = QString::fromWCharArray(L"正在创建订单...");
		painter.drawText(QRect(0,0,130,20),Qt::AlignLeft|Qt::AlignVCenter,strText);

		painter.end();
		pixmap.save("./text9.png");
		return pixmap;
	}

	static QImage GrayScale(QImage  origin,int gray_value =0)
	{
		QImage image_ = QImage(origin.width(), origin.height(), QImage::Format_ARGB32);

		QColor oldColor;

		for(int x = 0; x<image_.width(); x++)
		{
			for(int y = 0; y<image_.height(); y++)
			{
				oldColor = QColor(origin.pixel(x,y));
				int average = 0;
				if ( gray_value == 0 )
				{
					average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
				}
				else
				{
					average = ((float)gray_value)/100*(oldColor.red()+oldColor.green()+oldColor.blue());
				}
				image_.setPixel(x,y,qRgba(average,average,average,qAlpha(origin.pixel(x,y))));
			}
		}
		return image_;
	}

	static void CreatePurchaseBg(int w,int h)
	{
		QPixmap pixmap;
		bool bLoad = pixmap.load("./bg.jpg");
		QPixmap pixmap2 = pixmap.scaled(QSize(w,h),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
		bool bSave = pixmap2.save("./bg2.jpg");
		if (bSave)
		{
			qDebug()<<"1";
		}
	}

	static void CreatePurchaseClose()
	{
		QPixmap pixmap;
		bool bLoad = pixmap.load("./btn_monolaye_close.png");
		QPixmap pixmap1 = pixmap.copy(QRect(0,0,16,16));
		QPixmap pixmap2 = pixmap.copy(QRect(0,16,16,16));
		QPixmap pixmap3 = pixmap.copy(QRect(0,16,16,16));
		bool bSave = pixmap1.save("./close-1.png");
		bSave = pixmap2.save("./close-2.png");
		bSave = pixmap3.save("./close-3.png");
		if (bSave)
		{
			qDebug()<<"1";
		}
	}

	static void CreatePurchaseBuy()
	{
		QPixmap pixmap;
		bool bLoad = pixmap.load("./btn_qrcz.png");
		QPixmap pixmap1 = pixmap.copy(QRect(0,0,218,81));
		QPixmap pixmap2 = pixmap.copy(QRect(0,81,218,81));
		QPixmap pixmap3 = pixmap.copy(QRect(0,162,218,81));
		bool bSave = pixmap1.save("./btn_qrcz-1.png");
		bSave = pixmap2.save("./btn_qrcz-2.png");
		bSave = pixmap3.save("./btn_qrcz-3.png");
		if (bSave)
		{
			qDebug()<<"1";
		}
	}

	static QPixmap GetPixmapBySmallBg2(QString path,int title,int border,int w,int h)
		{
			QPixmap pixmap = QPixmap(w, h);
			pixmap.fill(Qt::transparent);
			QPainter painter;
			painter.begin(&pixmap);
			painter.setRenderHint(QPainter::Antialiasing, true);
			QPixmap tmp;
			tmp.load(path);
			int pixW = tmp.width();
			int pixH = tmp.height();
			QPixmap pix1,pix2,pix3,pix4,pix5,pix6,pix7,pix8,pix9;
			pix1 = tmp.copy(0,0,border,title);
			pix2 = tmp.copy(border,0,pixW-border*2,title);
			pix3 = tmp.copy(pixW-border,0,border,title);

			pix4 = tmp.copy(0,title,border,pixH-border-title);
			pix5 = tmp.copy(border,title,pixW-border*2,pixH-border-title);
			pix6 = tmp.copy(pixW-border,title,border,pixH-border-title);

			pix7 = tmp.copy(0,pixH-border,border,border);
			pix8 = tmp.copy(border,pixH-border,pixW-border*2,border);
			pix9 = tmp.copy(pixW-border,pixH-border,border,border);

	
			//pix2 = pix2.scaled(w-border*2,title,Qt::IgnoreAspectRatio);//保持高度拉宽
			//pix4 = pix4.scaled(border,h-title-border,Qt::IgnoreAspectRatio);//保持宽度拉高
			pix5 = pix5.scaled(w-border*2,h-title-border);
			//pix6 = pix6.scaled(border,h-title-border,Qt::IgnoreAspectRatio);//保持宽度拉高
			//pix8 = pix8.scaled(w-border*2,border);//保持高度拉宽

			painter.drawPixmap(0,0,pix1);
			if (pixW-border*2 > 0 )
			{
				int xn= (w-border*2)/(pixW-border*2);
				int xPos = border;
				for ( int i = 0 ; i < xn;++i)
				{
					painter.drawPixmap(xPos,0,pix2);
					xPos+=(pixW-border*2);
				}
				if ( (w-border*2)%(pixW-border*2)!=0)
				{
					QPixmap xtemp;
					int xLast = w-border-xPos;
					xtemp = tmp.copy(border,0,xLast,title);
					painter.drawPixmap(xPos,0,xtemp);
					xPos+=xLast;
				}
			}
			painter.drawPixmap(w-border,0,pix3);
			/*
			painter.drawPixmap(w-border,0,pix3);
			if (pixH-title-border > 0 )
			{
				int yn= (h-title-border)/(pixH-title-border);
				int ypos = title;
				for ( int i = 0 ; i < yn;++i)
				{
					painter.drawPixmap(0,ypos,pix8);
					ypos+=(pixH-title-border);
				}
				if ( (h-title-border)%(pixH-title-border)!=0)
				{
					pix8 = pix8.scaled(h-title-border-ypos,title,Qt::IgnoreAspectRatio);
					painter.drawPixmap(0,ypos,pix8);
				}
			}
			//painter.drawPixmap(0,title,pix4);
	

			painter.drawPixmap(w-border,title,pix6);

	
			*/

			if (pixH-title*2 > 0 )
			{
				int xn= (h-title*2)/(pixH-title*2);
				int yPos = border;
				for ( int i = 0 ; i < xn;++i)
				{
					painter.drawPixmap(0,yPos,pix4);
					yPos+=(pixH-title*2);
				}
				if ( (h-title*2)%(pixH-title*2)!=0)
				{
					QPixmap xtemp;
					int yLast = h-title-yPos;
					xtemp = tmp.copy(0,title,border,yLast);
					painter.drawPixmap(0,yPos,xtemp);
					yPos+=yLast;
				}
			}
			painter.drawPixmap(border,title,pix5);
			if (pixH-title*2 > 0 )
			{
				int xn= (h-title*2)/(pixH-title*2);
				int yPos = border;
				for ( int i = 0 ; i < xn;++i)
				{
					painter.drawPixmap(w-border,yPos,pix6);
					yPos+=(pixH-title*2);
				}
				if ( (h-title*2)%(pixH-title*2)!=0)
				{
					QPixmap xtemp;
					int yLast = h-title-yPos;
					xtemp = tmp.copy(pixW-border,title,border,yLast);
					painter.drawPixmap(w-border,yPos,xtemp);
					yPos+=yLast;
				}
			}

			painter.drawPixmap(0,h-border,pix7);
			if (pixW-border*2 > 0 )
			{
				int xn= (w-border*2)/(pixW-border*2);
				int xPos = border;
				for ( int i = 0 ; i < xn;++i)
				{
					painter.drawPixmap(xPos,h-title,pix8);
					xPos+=(pixW-border*2);
				}
				if ( (w-border*2)%(pixW-border*2)!=0)
				{
					QPixmap xtemp;
					int xLast = w-border-xPos;
					xtemp = tmp.copy(border,pixH-border,xLast,title);
					painter.drawPixmap(xPos,h-title,xtemp);
					xPos+=xLast;
				}
			}
			painter.drawPixmap(w-border,h-border,pix9);

			painter.end();
			return pixmap;
		}

	static QImage * warm(int delta, QImage * origin)
	{
		QImage *newImage = new QImage(origin->width(), origin->height(), QImage::Format_ARGB32);

		QColor oldColor;
		int r,g,b;

		for(int x=0; x<newImage->width(); x++){
			for(int y=0; y<newImage->height(); y++){
				oldColor = QColor(origin->pixel(x,y));

				r = oldColor.red() + delta;
				g = oldColor.green() + delta;
				b = oldColor.blue();

				//we check if the new values are between 0 and 255
				r = qBound(0, r, 255);
				g = qBound(0, g, 255);

				newImage->setPixel(x,y, qRgb(r,g,b));
			}
		}

		return newImage;
	}

	static QPixmap GetPurchasePixmap_()
	{
		QPixmap pix1 ;
		pix1.load("./bg_title_all.png");
		QPixmap pix2=GetPixmapBySmallBg2("./public_bg_tc.png",9,9,454,335);

		QPixmap pixmap = QPixmap(454,335);
		pixmap.fill(Qt::transparent);
		QPainter painter;
		painter.begin(&pixmap);
		painter.setRenderHint(QPainter::Antialiasing, true);
		painter.drawPixmap(0,0,pix2);
		painter.drawPixmap(8,9,pix1);

		/*QString strName1 = QString::fromWCharArray(L"汉仪小隶书简");
		QFont font(strName1);
		font.setPixelSize(20);
		font.setBold(true);
		painter.setFont(font);
		painter.drawText(QRect(17,9,100,33),Qt::AlignLeft | Qt::AlignVCenter,QString::fromWCharArray(L"充值提示"));*/

		painter.end();
		pixmap.save("./charge.png");
		return pixmap;
	}

	static QImage *cool(int delta, QImage * origin)
	{
		QImage *newImage = new QImage(origin->width(), origin->height(), QImage::Format_ARGB32);

		QColor oldColor;
		int r,g,b;

		for(int x=0; x<newImage->width(); x++){
			for(int y=0; y<newImage->height(); y++){
				oldColor = QColor(origin->pixel(x,y));

				r = oldColor.red();
				g = oldColor.green();
				b = oldColor.blue()+delta;

				//we check if the new value is between 0 and 255
				b = qBound(0, b, 255);

				newImage->setPixel(x,y, qRgb(r,g,b));
			}
		}

		return newImage;
	}

	static QImage  hue(int delta, QImage  origin)
	{
		QImage  image_ = QImage(origin.width(), origin.height(), QImage::Format_ARGB32);

		QColor oldColor;
		QColor newColor;
		int h,s,l;

		for(int x=0; x<image_.width(); x++)
		{
			for(int y=0; y<image_.height(); y++)
			{
				oldColor = QColor(origin.pixel(x,y));

				newColor = oldColor.toHsl();
				h= newColor.hue()+delta;
				s = newColor.saturation();

				l = newColor.lightness();

				newColor.setHsl(h, s, l);

				image_.setPixel(x, y, qRgba(newColor.red(), newColor.green(), newColor.blue(),qAlpha(origin.pixel(x,y))));
			}
		}

		return image_;
	}

	static QImage  saturation(int delta, QImage  origin)
	{
		QImage  image_ = QImage(origin.width(), origin.height(), QImage::Format_ARGB32);

		QColor oldColor;
		QColor newColor;
		int h,s,l;

		for(int x=0; x<image_.width(); x++)
		{
			for(int y=0; y<image_.height(); y++)
			{
				oldColor = QColor(origin.pixel(x,y));

				newColor = oldColor.toHsl();
				h = newColor.hue();

				s= newColor.saturation()+delta;
				
				l = newColor.lightness();

				//we check if the new value is between 0 and 255
				s = qBound(0, s, 255);

				newColor.setHsl(h, s, l);

				image_.setPixel(x, y, qRgba(newColor.red(), newColor.green(), newColor.blue(),qAlpha(origin.pixel(x,y))));
			}
		}

		return image_;
	}

	static QImage  light(int delta, QImage  origin)
	{
		QImage  image_ = QImage(origin.width(), origin.height(), QImage::Format_ARGB32);

		QColor oldColor;
		QColor newColor;
		int h,s,l;

		for(int x=0; x<image_.width(); x++)
		{
			for(int y=0; y<image_.height(); y++)
			{
				oldColor = QColor(origin.pixel(x,y));

				newColor = oldColor.toHsl();
				h = newColor.hue();

				s = newColor.saturation();

				l= newColor.lightness()+delta;
				

				newColor.setHsl(h, s, l);

				image_.setPixel(x, y, qRgba(newColor.red(), newColor.green(), newColor.blue(),qAlpha(origin.pixel(x,y))));
			}
		}

		return image_;
	}

	static QImage * sharpen(QImage * origin)
	{
		QImage * newImage = new QImage(* origin);

		int kernel [3][3]= {{0,-1,0},
		{-1,5,-1},
		{0,-1,0}};
		int kernelSize = 3;
		int sumKernel = 1;
		int r,g,b;
		QColor color;

		for(int x=kernelSize/2; x<newImage->width()-(kernelSize/2); x++){
			for(int y=kernelSize/2; y<newImage->height()-(kernelSize/2); y++){

				r = 0;
				g = 0;
				b = 0;

				for(int i = -kernelSize/2; i<= kernelSize/2; i++){
					for(int j = -kernelSize/2; j<= kernelSize/2; j++){
						color = QColor(origin->pixel(x+i, y+j));
						r += color.red()*kernel[kernelSize/2+i][kernelSize/2+j];
						g += color.green()*kernel[kernelSize/2+i][kernelSize/2+j];
						b += color.blue()*kernel[kernelSize/2+i][kernelSize/2+j];
					}
				}

				r = qBound(0, r/sumKernel, 255);
				g = qBound(0, g/sumKernel, 255);
				b = qBound(0, b/sumKernel, 255);

				newImage->setPixel(x,y, qRgb(r,g,b));

			}
		}
		return newImage;
	}

	static QImage GetImageByHSL(QImage origin,int hue_,int saturation_,int light_,int c)
	{
		QImage  image_ = QImage(origin.width(), origin.height(), QImage::Format_ARGB32);

		QColor oldColor;
		QColor newColor;
		int h,s,l;

		for(int x=0; x<image_.width(); x++)
		{
			for(int y=0; y<image_.height(); y++)
			{
				oldColor = QColor(origin.pixel(x,y));
				
				newColor = oldColor.toHsl();
				h = newColor.hue()+hue_;

				s = newColor.saturation()+saturation_;

				l = newColor.lightness()+light_;

				//we check if the new value is between 0 and 255
				s = qBound(0, s, 255);

				newColor.setHsl(h, s, l);

				image_.setPixel(x, y, qRgba(newColor.red(), newColor.green(), newColor.blue(),qAlpha(origin.pixel(x,y))));
			}
		}
		
		if ( c > 0)
		{
			QImage  image = AdjustContrast(c,image_);
			return image;
		}
		else
		{
			return image_;
		}
		

		return image_;
	}

	static QImage GetImageByHSV(QImage origin,int hue_,int saturation_,int value_,int c)
	{
		QImage  image_ = QImage(origin.width(), origin.height(), QImage::Format_ARGB32);

		QColor oldColor;
		QColor newColor;
		int h,s,v;

		for(int x=0; x<image_.width(); x++)
		{
			for(int y=0; y<image_.height(); y++)
			{
				oldColor = QColor(origin.pixel(x,y));

				newColor = oldColor.toHsv();
				h = newColor.hue()+hue_;

				s = newColor.saturation()+saturation_;

				v = newColor.value()+value_;

				s = qBound(0, s, 255);

				newColor.setHsv(h, s, v);

				image_.setPixel(x, y, qRgba(newColor.red(), newColor.green(), newColor.blue(),qAlpha(origin.pixel(x,y))));
			}
		}

		if ( c > 0)
		{
			QImage  image = AdjustContrast(c,image_);
			return image;
		}
		else
		{
			return image_;
		}


		return image_;
	}

	static QImage AdjustContrast(int iContrastValue,QImage Img)
	{
		QImage  image_ = QImage(Img);
		int pixels = image_.width() * image_.height();
		unsigned int *data = (unsigned int *)image_.bits();

		int red, green, blue, nRed, nGreen, nBlue;

		if (iContrastValue > 0 && iContrastValue < 100)
		{
			float param = 1 / (1 - iContrastValue / 100.0) - 1;

			for (int i = 0; i < pixels; ++i)
			{
				nRed = qRed(data[i]);
				nGreen = qGreen(data[i]);
				nBlue = qBlue(data[i]);

				red = nRed + (nRed - 127) * param;
				red = (red < 0x00) ? 0x00 : (red > 0xff) ? 0xff : red;
				green = nGreen + (nGreen - 127) * param;
				green = (green < 0x00) ? 0x00 : (green > 0xff) ? 0xff : green;
				blue = nBlue + (nBlue - 127) * param;
				blue = (blue < 0x00) ? 0x00 : (blue > 0xff) ? 0xff : blue;

				data[i] = qRgba(red, green, blue, qAlpha(data[i]));
			}
		}
		else
		{
			for (int i = 0; i < pixels; ++i)
			{
				nRed = qRed(data[i]);
				nGreen = qGreen(data[i]);
				nBlue = qBlue(data[i]);

				red = nRed + (nRed - 127) * iContrastValue / 100.0;
				red = (red < 0x00) ? 0x00 : (red > 0xff) ? 0xff : red;
				green = nGreen + (nGreen - 127) * iContrastValue / 100.0;
				green = (green < 0x00) ? 0x00 : (green > 0xff) ? 0xff : green;
				blue = nBlue + (nBlue - 127) * iContrastValue / 100.0;
				blue = (blue < 0x00) ? 0x00 : (blue > 0xff) ? 0xff : blue;

				data[i] = qRgba(red, green, blue, qAlpha(data[i]));
			}
		}

		return image_;
	}

	static void GetMaskImage(const QPixmap &src, QPixmap& dst, const QPixmap &mask,int x,int y,int width,int height)
	{
		QImage resultImage(mask.size(),QImage::Format_ARGB32_Premultiplied);
		QPainter painter(&resultImage);
		painter.setCompositionMode(QPainter::CompositionMode_Source);
		painter.fillRect(resultImage.rect(), Qt::transparent);
		painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
		painter.drawPixmap(0, 0, mask);
		painter.setCompositionMode(QPainter::CompositionMode_SourceIn);

		QPixmap pixmapSrc2 = src.copy(x,y,width,height);
		painter.drawPixmap(0, 0, pixmapSrc2.scaled(mask.size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
		painter.end();
		dst = QPixmap::fromImage(resultImage);
	}

	static QImage GetPixmapByVLVector(const QImage & origin,const QVector<STHSLV> & vec)
	{
		QImage image_(origin.width(),origin.height()*vec.size(),QImage::Format_ARGB32_Premultiplied);
		QPainter painter(&image_);
		painter.fillRect(image_.rect(), Qt::transparent);
		int yPos = 0;
		for ( int i = 0 ; i < vec.size(); ++i )
		{
			QImage img_;
			if ( vec[i].type==0)
			{
				img_ = GetImageByHSL(origin,vec[i].hue,vec[i].saturation,vec[i].light,vec[i].contrast);
			}
			else if(vec[i].type==1)
			{
				img_ = GetImageByHSL(origin,vec[i].hue,vec[i].saturation,vec[i].value,vec[i].contrast);
			}
			else
			{
				img_ = GrayScale(origin,vec[i].gray);
			}
			painter.drawImage(0,yPos+i*origin.height(),img_.scaled(QSize(origin.width(),origin.height()),Qt::KeepAspectRatio,Qt::SmoothTransformation));
		}
		painter.end();
		return image_;
	}
	//保存文件至本地 filename="./Images/example.png";
	static bool SaveImageToNative(const QImage & origin,const QVector<STHSLV> & vec,const QString & filename)
	{
		QImage img = GetPixmapByVLVector(origin,vec);
		bool bSave = false;
		bSave = img.save(filename);
		return bSave;
	}
	static QPixmap GetHeroSkilledPixmap()
	{
		QPixmap pixmap = QPixmap(209, 48);
		pixmap.fill(Qt::transparent);
		QPainter painter;
		painter.begin(&pixmap);
		painter.setRenderHint(QPainter::Antialiasing,true);
		QPen pen(QColor("#524C3B"));
		pen.setStyle(Qt::SolidLine);
		pen.setWidth(3);
		painter.setPen(pen);

		painter.setBrush(QColor("#1C1615"));
		painter.drawRect(0, 0, 209, 48);
		painter.end();
		return pixmap;
	}

	static QPixmap GetTrumpetPixmap(int w,int h)
	{
		QPixmap pixmap = QPixmap(w, h);
		pixmap.fill(Qt::transparent);
		QPainter painter;
		painter.begin(&pixmap);
		painter.setRenderHint(QPainter::Antialiasing,true);
		QPen pen(QColor(28, 22, 21, 255));
		pen.setStyle(Qt::SolidLine);
		pen.setWidth(2);
		painter.setPen(pen);

		painter.setBrush(QColor(34,33,36,0.95*255));
		painter.drawRect(0, 0, w, h);
		painter.end();
		return pixmap;
	}
};
#endif