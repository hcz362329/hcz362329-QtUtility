#include "widget_zhaoyun.h"
#include "common_define.h"
#include <QPainter>
#include <QResizeEvent>
#include <QBitmap>

CWidgetZhaoYun::CWidgetZhaoYun(QWidget *parent) :
    QWidget(parent),
    m_pLblInk(nullptr),
    m_pLblCircle(nullptr),
    m_pLblCircleZY(nullptr)
{

}

CWidgetZhaoYun::~CWidgetZhaoYun()
{

}

void CWidgetZhaoYun::showInkImage()
{
    hideAllImage();
    if(m_pLblInk)
    {
        m_pLblInk->show();
    }
}

void CWidgetZhaoYun::showCircleImage()
{
    hideAllImage();
    if(m_pLblCircleZY)
    {
        m_pLblCircleZY->show();
    }
    if(m_pLblCircle)
    {
        m_pLblCircle->show();
    }
}

void CWidgetZhaoYun::resizeEvent(QResizeEvent *e)
{
    QPixmap pixmapInk(QString("%0/ink.png").arg(EXE_PATH));
    QPixmap pixmapZY(QString("%0/zhaoyun.jpg").arg(EXE_PATH));
    QPixmap pixmapCircle(QString("%0/circle.png").arg(EXE_PATH));
    QPixmap pixmapCircle3(QString("%0/circle_black.png").arg(EXE_PATH));
    if(!m_pLblInk)
    {
        m_pLblInk = new QLabel(this);
        m_pLblInk->setObjectName("lblZhaoYun");
        m_pLblInk->setScaledContents(true);

        QPixmap tmp = getRoundImage(pixmapInk, pixmapZY, -45, 34);

        m_pLblInk->setPixmap(tmp);
        m_pLblInk->setFixedSize(e->size());
        m_pLblInk->move(0, 0);
        m_pLblInk->hide();
    }
    int x = 120, y = 120;
    if(!m_pLblCircleZY)
    {
        m_pLblCircleZY = new QLabel(this);
        m_pLblCircleZY->setObjectName("lblCircleZY");
        m_pLblCircleZY->setScaledContents(true);

        int iOffset = 0;
        QPixmap pixmapZY2 = pixmapZY.scaled(290, 387, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QPixmap tmp = getRoundImage(pixmapCircle3, pixmapZY2, 0, 0);
        //QPixmap tmp = pixmapToRound(pixmapZY, pixmapCircle2.width() / 2 - 1);

        m_pLblCircleZY->setPixmap(tmp);
        m_pLblCircleZY->setFixedSize(tmp.size());
        m_pLblCircleZY->move(x + iOffset, y + iOffset);
        m_pLblCircleZY->hide();
    }
    if(!m_pLblCircle)
    {
        m_pLblCircle = new QLabel(this);
        m_pLblCircle->setObjectName("lblCircle");
        m_pLblCircle->setScaledContents(true);

        /******ÉèÖÃÍ¼Æ¬Í¸Ã÷***************/
        /*
        QPixmap tempCircle2(pixmapCircle.size());
        tempCircle2.fill(Qt::transparent);

        QPainter painter(&tempCircle2);
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.drawPixmap(0, 0, pixmapCircle);
        painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
        painter.fillRect(tempCircle2.rect(), QColor(0, 0, 0, 255));
        painter.end();
        QPixmap pixmapCircleTransparent = tempCircle2;
        */
        /********************************/

        m_pLblCircle->setPixmap(pixmapCircle);
        m_pLblCircle->setFixedSize(pixmapCircle.size());
        m_pLblCircle->move(x, y);
        m_pLblCircle->hide();
    }
}

QPixmap CWidgetZhaoYun::pixmapToRound(const QPixmap &src, int radius)
{
    QPixmap pixmapTmp = src.copy(0, 0, src.width(), src.width());

    if (pixmapTmp.isNull()) {
        return QPixmap();
    }

    QSize size(2*radius, 2*radius);
    QBitmap mask(size);
    mask.fill(Qt::transparent);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), radius, radius);

    QPixmap image = pixmapTmp.scaled(size);
    image.setMask(mask);
    return image;
}

QPixmap CWidgetZhaoYun::getRoundImage(QPixmap &src, QPixmap &dst, int x, int y)
{
    QImage resultImage(src.size(),QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&resultImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawPixmap(0, 0, src);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawPixmap(x, y, dst);
    painter.end();
    QPixmap tmp = QPixmap::fromImage(resultImage);
    return tmp;
}

void CWidgetZhaoYun::getRoundPixmap(QPixmap &src, const QPixmap &mask, const QSize &size)
{
    QImage resultImage(size,QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&resultImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawPixmap(0, 0, mask);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOut);
    painter.drawPixmap(0, 0, src.scaled(size));
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter.end();
    src = QPixmap::fromImage(resultImage);
}

void CWidgetZhaoYun::hideAllImage()
{
    if(m_pLblInk)
    {
        m_pLblInk->hide();
    }
    if(m_pLblCircle)
    {
        m_pLblCircle->hide();
    }
    if(m_pLblCircleZY)
    {
        m_pLblCircleZY->hide();
    }
}
