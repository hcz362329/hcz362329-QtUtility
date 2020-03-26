#include "TopHintDialog.h"

TopHintDialog::TopHintDialog(QWidget* parent/* =0 */)
	:QDialog(parent)
{
	setAttribute(Qt::WA_TranslucentBackground);	
	setWindowFlags(Qt::WindowStaysOnTopHint | /*Qt::FramelessWindowHint |*/ Qt::Tool );
	resize(300,400);
}

TopHintDialog::~TopHintDialog()
{

}