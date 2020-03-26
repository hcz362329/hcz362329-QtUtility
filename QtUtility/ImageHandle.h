#ifndef ImageHandle_h
#define ImageHandle_h
#include <QWidget>
#include <QImage>
#include <QPushButton>
struct STRenderText
{
	QString strRenderText;
	QFont fontText;
	bool is_stroke;
	int stroke_width;
	QColor stroke_color;
	QColor text_color;
	QString strFamilyName;
	int font_size;
	bool bold;
	bool is_TextFlag;
	int flag;
	STRenderText()
	{
		is_stroke = false;
		stroke_width = 0;
	}
};

class QPushButtonEx : public QPushButton
{
	Q_OBJECT
public:
	explicit QPushButtonEx(QWidget* parent=0);
	~QPushButtonEx();

	void SetRenderText(const STRenderText & text);
protected:
	void paintEvent(QPaintEvent *);
	STRenderText m_stRenderText;
};


class ImageHandle : public QWidget
{
	Q_OBJECT
public:
	explicit ImageHandle(QWidget* parent =0);
	~ImageHandle();

protected:
	virtual void paintEvent(QPaintEvent *);
private:
	QImage image;
	QImage gray;
	QImage image_test;
	QImage image_test_combine;
	QPixmap pixmap_transprency_;
	QImage image_combine_;
};
#endif