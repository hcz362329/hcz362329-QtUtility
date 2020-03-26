#include "PromoteTest.h"
#include "PromoteInfo.h"
#include <QPushButton>
#include <QLineEdit>
#include "RankHelp.hpp"
PromoteTest::PromoteTest(QWidget* parent)
	: QWidget(parent)
{
	resize(800,800);
	PromoteInfo *p=new PromoteInfo(this);
	p->setGeometry(0,0,p->width(),p->height());
	
	
	QPushButton* setRank = new QPushButton("Update",this);
	setRank->setGeometry(0,100,100,20);

	QLineEdit* line_rank_score = new QLineEdit(this);
	line_rank_score->setGeometry(100,100,150,20);
	QLineEdit* line_rank_score2 = new QLineEdit(this);
	line_rank_score2->setGeometry(250,100,150,20);

	connect(setRank,&QPushButton::clicked,this,[=]{
		int score_num = line_rank_score->text().toInt();
		int state_num = line_rank_score2->text().toInt();
		p->SetRankInfo(score_num,state_num);
	});



	QPushButton* perTest = new QPushButton("perTest",this);
	perTest->setGeometry(0,150,100,20);

	QLineEdit* perTest_score = new QLineEdit(this);
	perTest_score->setGeometry(100,150,150,20);
	QLineEdit* perTest_score2 = new QLineEdit(this);
	perTest_score2->setGeometry(250,150,150,20);
	QLabel *pLabel = new QLabel(this);
	pLabel->setGeometry(0,200,136,60);

	connect(perTest,&QPushButton::clicked,this,[=]{
		int score = perTest_score->text().toInt();
		float fValue = HD::RankHelp::GetPercentOfLevel(score);
		pLabel->setPixmap(HD::RankHelp::GetPixmapByScore(score));
		perTest_score2->setText(QString::number(fValue));
	});
	QLabel* pLabelPixmap = new QLabel(this);
	pLabelPixmap->setGeometry(0,300,80,80);
	QPixmap pixmap ;
	pixmap.load("./Images/10000_png.png");
	pLabelPixmap->setPixmap(pixmap);

	QLabel* pLabelPixmap2 = new QLabel(this);
	pLabelPixmap2->setGeometry(100,300,38,38);
	QPixmap pixmap2 ;
	pixmap2.load("./Images/10000_png.png");
	pLabelPixmap2->setPixmap(pixmap2.scaled(QSize(38,38),Qt::KeepAspectRatio,Qt::SmoothTransformation));
}

PromoteTest::~PromoteTest()
{

}