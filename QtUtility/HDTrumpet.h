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
		QPushButtonEx* m_pCompositeBtn;	//�ۺ�Ƶ����ť
		QPushButtonEx* m_pFullServiceBtn;	//ȫ��Ƶ����ť
		QPushButtonEx* m_pSystemBtn;		//ϵͳƵ����ť
		QPushButtonEx* m_pTeamBtn;		//����Ƶ����ť
		
		QPushButtonEx* m_pShrinkBtn;		//������ť
		QPushButtonEx* m_pTeamInviteBtn;	//������밴ť
		QPushButtonEx* m_pSendBtn;		//���Ͱ�ť

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