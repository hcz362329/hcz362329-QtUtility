#ifndef __WIDGET_ZHAOYUN_H__
#define __WIDGET_ZHAOYUN_H__

#include <QWidget>
#include <QLabel>

class CWidgetZhaoYun : public QWidget
{
    Q_OBJECT
public:
    explicit CWidgetZhaoYun(QWidget *parent = 0);
    ~CWidgetZhaoYun();

    void showInkImage();
    void showCircleImage();

protected:
    void resizeEvent(QResizeEvent *e);
    QPixmap pixmapToRound(const QPixmap &src, int radius);
    QPixmap getRoundImage(QPixmap &src, QPixmap &dst, int x, int y);
    void getRoundPixmap(QPixmap &src, const QPixmap &mask, const QSize &size);

private:
    void hideAllImage();

private:
    QLabel *m_pLblInk;
    QLabel *m_pLblCircle;
    QLabel *m_pLblCircleZY;
};

#endif // __WIDGET_ZHAOYUN_H__

