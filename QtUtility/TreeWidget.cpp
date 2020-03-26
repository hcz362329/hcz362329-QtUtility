#include "TreeWidget.h"
#include "CTreeView.h"
#include "Data.h"
#include "StringHelper.hpp"
#include "winhttp/utility.h"
#include <QTextEdit>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLineEdit>
#include "SqlDatabase.h"
TreeWidget::TreeWidget(QWidget *parent )
	: QWidget(parent)
{
	resize(600,800);
	setWindowTitle(QStringLiteral("自定义树控件,树节点-Model"));
	TreeView* tree = new TreeView(this);
	connect(tree,&TreeView::expanded,this,[](const QModelIndex &index)->void{
		STNode & stNode = qvariant_cast<STNode>(index);
		if (stNode.IsGroup )
		{

		}
	});

	tree->setGeometry(300,0,300,800);

	SqlDatabase::GetInstance()->CreateTable("im");
	SqlDatabase::GetInstance()->TestIm();
	std::wstring root_path;

	bool bGet = common_cz::GetProcessFolderPath(&root_path);
#if 1
	QVector<STNode> vec;

	STNode stNode_Group ;
	stNode_Group.IsGroup = true;
	stNode_Group.group_id = 1;
	stNode_Group.node_id = 0;
	stNode_Group.strGroupName = L"关羽";
	vec.push_back(stNode_Group);


	STNode stNode ;
	stNode.IsGroup = false;
	stNode.group_id = 1;
	stNode.node_id = 1;
	stNode.strName =L"Skill1";
	stNode.strPath = root_path+L"/Images/SkillIcon/Hero_guanyu_Skill_01_64.png";
	stNode.state = 1;
	vec.push_back(stNode);
	STNode stNode2 ;
	stNode2.IsGroup = false;
	stNode2.group_id = 1;
	stNode2.node_id = 2;
	stNode2.strName =L"Skill2";
	stNode2.strPath = root_path+L"/Images/SkillIcon/Hero_guanyu_Skill_02_64.png";
	vec.push_back(stNode2);

	STNode stNode3 ;
	stNode3.IsGroup = false;
	stNode3.group_id = 1;
	stNode3.node_id = 3;
	stNode3.strName =L"Skill3";
	stNode3.strPath = root_path+L"/Images/SkillIcon/Hero_guanyu_Skill_03_64.png";

	vec.push_back(stNode3);

	STNode stNode_Group2 ;
	stNode_Group2.IsGroup = true;
	stNode_Group2.group_id = 2;
	
	stNode_Group2.strGroupName = L"关羽2";
	vec.push_back(stNode_Group2);


	STNode stNode21 ;
	stNode21.IsGroup = false;
	stNode21.group_id = 2;
	stNode21.node_id = 4;
	stNode21.strName =L"Skill1";
	stNode21.strPath = root_path+L"/Images/SkillIcon/Hero_guanyu_Skill_01_64.png";
	vec.push_back(stNode21);
	STNode stNode22 ;
	stNode22.IsGroup = false;
	stNode22.group_id = 2;
	stNode22.node_id = 5;
	stNode22.strName =L"Skill2";
	stNode22.strPath = root_path+L"/Images/SkillIcon/Hero_guanyu_Skill_02_64.png";
	vec.push_back(stNode22);

	STNode stNode23 ;
	stNode23.IsGroup = false;
	stNode23.group_id = 2;
	stNode23.strName =L"Skill3";
	stNode23.node_id =6;
	stNode23.state = 1;
	stNode23.strPath = root_path+L"/Images/SkillIcon/Hero_guanyu_Skill_03_64.png";

	vec.push_back(stNode23);


	tree->updateAll(vec);
#else
	QVector<QVariant> vec;

	STNode stNode_Group ;
	stNode_Group.IsGroup = true;
	stNode_Group.group_id = 1;
	stNode_Group.strGroupName = L"关羽";
	QVariant v_;
	v_.setValue(stNode_Group);
	vec.push_back(v_);


	STNode stNode ;
	stNode.IsGroup = false;
	stNode.group_id = 1;
	stNode.strName =L"Skill1";
	stNode.strPath = root_path+L"/Images/SkillIcon/Hero_guanyu_Skill_01_64.png";

	STNode stNode2 ;
	stNode2.IsGroup = false;
	stNode2.group_id = 1;
	stNode2.strName =L"Skill2";
	stNode2.strPath = root_path+L"/Images/SkillIcon/Hero_guanyu_Skill_02_64.png";


	STNode stNode3 ;
	stNode3.IsGroup = false;
	stNode3.group_id = 1;
	stNode3.strName =L"Skill3";
	stNode3.strPath = root_path+L"/Images/SkillIcon/Hero_guanyu_Skill_02_64.png";

	QVariant v1;
	v1.setValue(stNode);
	vec.push_back(v1);

	QVariant v2;
	v2.setValue(stNode2);
	vec.push_back(v2);

	QVariant v3;
	v3.setValue(stNode3);
	vec.push_back(v3);

	tree->updateAll(vec);
#endif
	QPushButton * btn1=new QPushButton("Add Node",this);
	btn1->setGeometry(0,0,100,20);

	QPushButton * btn12=new QPushButton("Update Node",this);
	btn12->setGeometry(105,0,100,20);
	QTextEdit* node_edit = new QTextEdit(this);
	node_edit->setPlaceholderText("input node information");
	node_edit->setGeometry(0,30,300,150);
	node_edit->setText("{\
		\"group_id\": 1,\
		\"node_id\": 1,\
		\"IsGroup\": false,\
		\"strGroupName\": \"UnKown\",\
		\"strName\": \"UnKown\",\
		\"state\": 1,\
		\"strPath\": \"D:/QXHD_NEWPLAT/2019QT55/Win32/Debug/Images/HeroIcon/heroHead_10022_icon.png\"}");

	connect(btn1,&QPushButton::clicked,this,[=]{
		if ( !node_edit->toPlainText().isEmpty() )
		{
			QString strNodeInfo = node_edit->toPlainText();
			QJsonParseError json_error;
			QJsonDocument parse_doucment = QJsonDocument::fromJson(strNodeInfo.toLocal8Bit(), &json_error); 

			if(json_error.error == QJsonParseError::NoError) 
			{  
				if(parse_doucment.isObject())  
				{  
					STNode stNode;
					QJsonObject obj = parse_doucment.object(); 
					if(obj.contains("group_id"))  
					{  
						QJsonValue group_id_value = obj.take("group_id");
						if(group_id_value.isDouble())
						{
							int group_id = group_id_value.toInt();
							stNode.group_id = group_id;
						}
					}
					if(obj.contains("node_id"))  
					{  
						QJsonValue node_id_value = obj.take("node_id");
						if(node_id_value.isDouble())
						{
							int node_id = node_id_value.toInt();
							stNode.node_id = node_id;
						}
					}
					if(obj.contains("IsGroup"))  
					{  
						QJsonValue IsGroup_value = obj.take("IsGroup");
						if(IsGroup_value.isBool())
						{
							bool IsGroup = IsGroup_value.toBool();
							stNode.IsGroup = IsGroup;
						}
					}
					if(obj.contains("strGroupName"))  
					{  
						QJsonValue strGroupName_value = obj.take("strGroupName");
						if(strGroupName_value.isString())
						{
							QString strGroupName = strGroupName_value.toString();
							WCHAR szGroupName[128]={0};
							strGroupName.toWCharArray(szGroupName);
							stNode.strGroupName = std::wstring(szGroupName);
						}
					}
					if(obj.contains("strName"))  
					{  
						QJsonValue strName_value = obj.take("strName");
						if(strName_value.isString())
						{
							QString strName = strName_value.toString();
							WCHAR szName[128]={0};
							strName.toWCharArray(szName);
							stNode.strName = std::wstring(szName);
						}
					}
					if(obj.contains("strPath"))  
					{  
						QJsonValue strPath_value = obj.take("strPath");
						if(strPath_value.isString())
						{
							QString strPath = strPath_value.toString();
							WCHAR szPath[128]={0};
							strPath.toWCharArray(szPath);
							stNode.strPath = std::wstring(szPath);
						}
					}
					if(obj.contains("state"))  
					{  
						QJsonValue state_value = obj.take("state");
						if(state_value.isDouble())
						{
							stNode.state = state_value.toInt();
						}
					}
					tree->AddNode(stNode);
				}
			}
		}
	});

	connect(btn12,&QPushButton::clicked,this,[=]{
		if ( !node_edit->toPlainText().isEmpty() )
		{
			QString strNodeInfo = node_edit->toPlainText();
			QJsonParseError json_error;
			QJsonDocument parse_doucment = QJsonDocument::fromJson(strNodeInfo.toLocal8Bit(), &json_error); 

			if(json_error.error == QJsonParseError::NoError) 
			{  
				if(parse_doucment.isObject())  
				{  
					STNode stNode;
					QJsonObject obj = parse_doucment.object(); 
					if(obj.contains("group_id"))  
					{  
						QJsonValue group_id_value = obj.take("group_id");
						if(group_id_value.isDouble())
						{
							int group_id = group_id_value.toInt();
							stNode.group_id = group_id;
						}
					}
					if(obj.contains("node_id"))  
					{  
						QJsonValue node_id_value = obj.take("node_id");
						if(node_id_value.isDouble())
						{
							int node_id = node_id_value.toInt();
							stNode.node_id = node_id;
						}
					}
					if(obj.contains("IsGroup"))  
					{  
						QJsonValue IsGroup_value = obj.take("IsGroup");
						if(IsGroup_value.isBool())
						{
							bool IsGroup = IsGroup_value.toBool();
							stNode.IsGroup = IsGroup;
						}
					}
					if(obj.contains("strGroupName"))  
					{  
						QJsonValue strGroupName_value = obj.take("strGroupName");
						if(strGroupName_value.isString())
						{
							QString strGroupName = strGroupName_value.toString();
							WCHAR szGroupName[128]={0};
							strGroupName.toWCharArray(szGroupName);
							stNode.strGroupName = std::wstring(szGroupName);
						}
					}
					if(obj.contains("strName"))  
					{  
						QJsonValue strName_value = obj.take("strName");
						if(strName_value.isString())
						{
							QString strName = strName_value.toString();
							WCHAR szName[128]={0};
							strName.toWCharArray(szName);
							stNode.strName = std::wstring(szName);
						}
					}
					if(obj.contains("strPath"))  
					{  
						QJsonValue strPath_value = obj.take("strPath");
						if(strPath_value.isString())
						{
							QString strPath = strPath_value.toString();
							WCHAR szPath[128]={0};
							strPath.toWCharArray(szPath);
							stNode.strPath = std::wstring(szPath);
						}
					}
					if(obj.contains("state"))  
					{  
						QJsonValue state_value = obj.take("state");
						if(state_value.isDouble())
						{
							stNode.state = state_value.toInt();
						}
					}
					tree->UpdateNode(stNode);
				}
			}
		}
	});

	QPushButton * btn2=new QPushButton("Del Node",this);
	btn2->setGeometry(0,180,100,20);
	QLineEdit* del_edit = new QLineEdit(this);
	del_edit->setPlaceholderText("input node id");
	del_edit->setGeometry(0,200,100,20);

	QLineEdit* del_edit2 = new QLineEdit(this);
	del_edit2->setPlaceholderText("input group id");
	del_edit2->setGeometry(110,200,100,20);

	connect(btn2,&QPushButton::clicked,this,[=]{
		STNode stNode;
		stNode.node_id = del_edit->text().toInt();
		stNode.group_id = del_edit2->text().toInt();
		tree->DeleteNode(stNode);
	});

	QPushButton * btn3=new QPushButton("Del Group",this);
	btn3->setGeometry(0,220,100,20);
	QLineEdit* del_edit3 = new QLineEdit(this);
	del_edit3->setPlaceholderText("input group id");
	del_edit3->setGeometry(0,240,100,20);
	connect(btn3,&QPushButton::clicked,this,[=]{
		STNode stNode;
		stNode.group_id = del_edit3->text().toInt();
		tree->DeleteGroup(stNode);
	});


	QPushButton * btn4=new QPushButton("Del Group Save Item",this);
	btn4->setGeometry(0,260,200,20);
	QLineEdit* del_edit4 = new QLineEdit(this);
	del_edit4->setPlaceholderText("input group id");
	del_edit4->setGeometry(0,280,100,20);
	connect(btn4,&QPushButton::clicked,this,[=]{
		STNode stNode;
		stNode.group_id = del_edit4->text().toInt();
		tree->DeleteGroupNodeButSaveChildItem(stNode);
	});

	
}

TreeWidget::~TreeWidget()
{
	/*
	{"content":"内容中文","url":"qxhd://type=changeplattopnav/?nav=2&url=http://pv.7fgame.com/?id=7237","url_content":"点击进入"}
	*/
}