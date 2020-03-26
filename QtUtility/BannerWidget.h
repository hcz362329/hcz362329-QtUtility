#ifndef PARA_BANNER_H
#define PARA_BANNER_H

#include <QWidget>
#include <QBasicTimer>

class BannerWidget : public QWidget
{
	Q_OBJECT
public:
	explicit BannerWidget(QWidget *parent = 0);
	~BannerWidget();

	public slots:
		void setText(const QString &text);

protected:
	// �����ı�
	void paintEvent(QPaintEvent *event);
	// ��ʱˢ��
	void timerEvent(QTimerEvent *event);

private:
	QBasicTimer m_timer;
	QString m_strText;
	int m_nStep;
};

#endif