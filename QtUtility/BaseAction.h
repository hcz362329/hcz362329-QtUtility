#ifndef BASEACTION_H
#define BASEACTION_H

class BaseAction
{
public:
	//�źŲ�����
	virtual void InitConnections() = 0;
	//��ʼ��һ�Ż������ʽ��
	virtual void InitStyleSheets() = 0;
	//���ع��ʻ�����
	virtual void LoadTranslator()  = 0;
	//ģ�黯���ã�UIģ������
	virtual void InitModules() = 0;
	//����ͼƬ��Դ
	virtual void InitPixmap() = 0;
	//�ؼ���ʼ��
	virtual void InitCtrls() = 0;
	//��ʼ����������
	virtual void InitWindowFlags() = 0;

};

#endif