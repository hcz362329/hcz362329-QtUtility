#ifndef HDTrumpet_h
#define HDTrumpet_h
#include <QWidget>
#include "ImageHandle.h"
#include <QButtonGroup>
#include <QTextEdit>
#include <QLineEdit>
namespace HD
{
	enum ETrumpetType
	{
		eTrumpetTypeNone			= 0,
		eTrumpetTypeComposite		= 1,
		eTrumpetTypeFullService		= 2,
		eTrumpetTypeSystem			= 3,
		eTrumpetTypeTeam			= 4,
	};

	enum EShowType 
	{
		eShowType_Unknow = -1, 
		eShowType_HomePage,
		eShowType_AutoMatchRoom,
		eShowType_NormalRoom,
		eShowType_JiangLingRoom, 
		eShowType_ZZSGAutoMatchRoom 
	};

	class HDTrumpet : public QWidget
	{
		Q_OBJECT
	public:
		explicit HDTrumpet(QWidget * parent=0);
		~HDTrumpet();
	public:
		void InitCtrl();
		void SetTrumpetTyle(const ETrumpetType& eTrumpetType);
		ETrumpetType GetTrumpetType();
		void SetShowType(const EShowType & type);
		EShowType GetShowType();
	protected:
		void paintEvent(QPaintEvent *);
	public slots:
		void OnTrumpetTypeClicked(int);
	private:
		QButtonGroup* m_pGroup;
		QPushButtonEx* m_pCompositeBtn;	//综合频道按钮
		QPushButtonEx* m_pFullServiceBtn;	//全服频道按钮
		QPushButtonEx* m_pSystemBtn;		//系统频道按钮
		QPushButtonEx* m_pTeamBtn;		//队伍频道按钮
		
		QPushButtonEx* m_pShrinkBtn;		//收缩按钮
		QPushButtonEx* m_pTeamInviteBtn;	//组队邀请按钮
		QPushButtonEx* m_pSendBtn;		//发送按钮

		ETrumpetType m_eTrumpetType;

		QTextEdit* m_pCompositeTextEdit;
		QTextEdit* m_pFullServiceTextEdit;
		QTextEdit* m_pSystemTextEdit;
		QTextEdit* m_pTeamTextEdit;
		QLineEdit* m_pLineEdit;

		QPixmap m_pixHomePage;
		EShowType m_eShowType;
	};
}
using namespace HD;

#endif