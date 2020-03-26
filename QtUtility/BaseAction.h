#ifndef BASEACTION_H
#define BASEACTION_H

class BaseAction
{
public:
	//信号槽连接
	virtual void InitConnections() = 0;
	//初始化一张或多张样式表
	virtual void InitStyleSheets() = 0;
	//加载国际化语言
	virtual void LoadTranslator()  = 0;
	//模块化设置：UI模块设置
	virtual void InitModules() = 0;
	//加载图片资源
	virtual void InitPixmap() = 0;
	//控件初始化
	virtual void InitCtrls() = 0;
	//初始化窗口设置
	virtual void InitWindowFlags() = 0;

};

#endif