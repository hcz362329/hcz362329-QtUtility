#include "imageprocess.h"
#include "ui_imageprocess.h"
#include <QStyleOption>
#include <QPainter>

const int g_imageIndex = 1;
const int g_imageIndex2 = 2;

CImageProcess::CImageProcess(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wdgImageProcess)
{
    ui->setupUi(this);
    initComboBoxData();
}

CImageProcess::~CImageProcess()
{
    delete ui;
}

void CImageProcess::showEvent(QShowEvent *)
{
    SLOT_imageIndexChanged(0);
}

void CImageProcess::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void CImageProcess::SLOT_imageIndexChanged(int index)
{
    int imageIndex = ui->cmbImage->itemData(index).toInt();
    if(imageIndex == g_imageIndex)
    {
        ui->wdgBg->showInkImage();
    }
    else if(imageIndex == g_imageIndex2)
    {
        ui->wdgBg->showCircleImage();
    }
}

void CImageProcess::initComboBoxData()
{
    ui->cmbImage->addItem(tr("ink"), g_imageIndex);
    ui->cmbImage->addItem(tr("circle"), g_imageIndex2);

    connect(ui->cmbImage, SIGNAL(currentIndexChanged(int)), this, SLOT(SLOT_imageIndexChanged(int)));
}
