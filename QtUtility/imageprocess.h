#ifndef __CIMAGEPROCESS_H__
#define __CIMAGEPROCESS_H__

#include <QWidget>

namespace Ui{
class wdgImageProcess;
}

class CImageProcess : public QWidget
{
    Q_OBJECT
public:
    explicit CImageProcess(QWidget *parent = 0);
    ~CImageProcess();

protected:
    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);

private slots:
    void SLOT_imageIndexChanged(int index);

private:
    void initComboBoxData();

private:
    Ui::wdgImageProcess *ui;
};

#endif // __CIMAGEPROCESS_H__

