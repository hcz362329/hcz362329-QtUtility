#ifndef QXEQUIPMENTTABLEDELEGATE_H
#define QXEQUIPMENTTABLEDELEGATE_H
#include <QAbstractItemDelegate>
#include "BaseDataDef.h"
class QxEquipmentTableDelegate : public QAbstractItemDelegate
{
	Q_OBJECT
public:
	explicit QxEquipmentTableDelegate(QWidget* parent = NULL);
	~QxEquipmentTableDelegate();
	void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

	//������Ⱦģʽ
	void setETable(ETable eTable);
	//���õ������
	void setPressedItem(const STEquipment & stEquipment);
	void setPressedItem(const STEquipmentLegend & stEquipmentLegend);
	//����Ӣ��ͷ���ͼƬ��Դ
	void setMapId2StrInfo(QMap<DWORD,QString> mapId2Str);
private:
	QPixmap m_pixBG;
	QPixmap m_pixGossipBorder;
	QPixmap m_pixSelect;
	QPixmap m_pixMoneyIconEQ;
	QPixmap m_pixTVLevelBG;
	QPixmap m_pixOwn;
	QPixmap m_pixNotOwn;
	QPixmap m_pixLhsp;
	QPixmap	m_pixMesh; //�ɰ�
	QPixmap m_pixSoulFragment;
	QMap<QString,QPixmap> m_mapEquipmentIcon;
	QMap<int,QPixmap> m_mapLegendIcon;
	ETable m_eTable;
	//�������
	STEquipment m_stEquipment;
	STEquipmentLegend m_stEquipmentLegend;
	QMap<DWORD,QString> m_mapId2Str;
	//��ͷ��
	QMap<DWORD,QPixmap> m_pLegemdBigIconMap;
	QMap<DWORD,QPixmap> m_pLegemdNameIconMap;
	//ӵ�С��������� ����
	//QMap<DWORD,QRect> m_vecRectOwned_Buy;
	QPixmap m_pixBuyNor;
	QPixmap m_pixBuyHorver;
	QPixmap m_pixBuyPressed;
	QPixmap m_pixOwned;
	QPixmap m_pixExample;
	QPixmap m_pixGossipMengBan;
	//PropList
	QPixmap m_pixPropListBorder;
	QPixmap m_pixPropListNormal;
	QPixmap m_pixPropListSelect;
	QPixmap m_pixPropListExample;
	QPixmap m_pixUnOwned;
	QPixmap m_pixMoneyIcon;
	//GossipTV
	QPixmap m_pixGossipTVSelect;
	QPixmap m_pixGossipTVEquip;
	QPixmap m_pixBanShunHuai;
	QPixmap m_pixSunhuai;

	QPixmap m_pixZXIcon;
	QPixmap m_pixJLIcon;
	QPixmap m_pixPTIcon;

	QMap<ECultivateSlotStatus,QPixmap> m_mapType2Item;
};
#endif