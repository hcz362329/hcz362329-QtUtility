#ifndef data_h
#define data_h
#include <QMetaType>
typedef struct tagNode
{
	int group_id;
	bool IsGroup;
	int node_id;
	std::wstring strGroupName;
	std::wstring strName;
	std::wstring strPath;
	int total;
	int online;
	int state;
	tagNode()
	{
		group_id = 0;
		node_id = 0;
		total = 0;
		online = 0;
		state = 0;
		IsGroup = false;
		strGroupName = L"Ä¬ÈÏ·Ö×é";
	}
}STNode;
Q_DECLARE_METATYPE(STNode);
#endif