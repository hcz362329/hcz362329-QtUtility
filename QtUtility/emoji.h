#ifndef EMOJI_H
#define EMOJI_H
#include <QTextEdit>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
class Emoji : public QWidget {
	Q_OBJECT
public:
	Emoji(QWidget* parent = 0);
	~Emoji();

public slots:
	void OnBtnClicked();
	void OnTextChanged();
private:
	QPushButton* pBtn;
	QLabel* pEmoji;
	QTextEdit* pEmojiText;
	QTextEdit* pText;
	QPushButton* btn;
};

#endif // !emoji_h
