#ifndef GIFT_FLOWLIGHT_MANAGER_H
#define GIFT_FLOWLIGHT_MANAGER_H
#ifndef GET_SET_DEFINE
#define GET_SET_DEFINE(ArgName, Type, Alias) \
const Type Get##Alias() const { return this->##ArgName; }; \
void Set##Alias(const Type& value) { this->##ArgName = value; };
#endif // !
#include <list>
#include <QLabel>
#include <QWidget>
#include <QDialog>
#include <QVariantList>
#include <QPropertyAnimation>
#include <mutex>
#include <string>
using namespace std;
#define SHOW_TIME_COUNT 3
namespace Mgr {
	enum Type {
		TYPE_GEOMETRY =	0,
		TYPE_POS,
	};

	static QPropertyAnimation* GetPropertyAnimation(QWidget* target, QWidget* parent, Type type, QVariantList& list, QVariantAnimation::KeyValues key2value, int time, bool keyAt = false) {
		QPropertyAnimation* animation = nullptr;
		QString property_name;
		switch (type) {
		case Mgr::TYPE_GEOMETRY: {
			property_name = "geometry";
		}break;
		case Mgr::TYPE_POS: {
			property_name = "pos";
		}break;
		default:break;
		}
		animation = new QPropertyAnimation(target, property_name.toLocal8Bit(), parent);
		animation->setDuration(time);
		if (keyAt) {
			animation->setKeyValues(key2value);
		}
		else {
			if (list.size() >= 2) {
				switch (type) {
				case Mgr::TYPE_GEOMETRY: {
					animation->setStartValue(QRect(qvariant_cast<QRect>(list.at(0))));
					animation->setEndValue(QRect(qvariant_cast<QRect>(list.at(1))));
				}break;
				case Mgr::TYPE_POS: {
					animation->setStartValue(QPoint(qvariant_cast<QPoint>(list.at(0))));
					animation->setEndValue(QPoint(qvariant_cast<QPoint>(list.at(1))));
				}break;
				default:break;
				}
			}
		}
		return animation;
	}
	struct FlowLight {
		int num;
		int hit;
		int user_id;
		string user_name;
		string gift_name;
		string icon_path;
	};
	class QlLabel : public QLabel {
		Q_OBJECT
	public:
		QlLabel(QWidget* parent);
		~QlLabel();
		GET_SET_DEFINE(pixmap_, QString, Pixmap);
	protected:
		virtual void resizeEvent(QResizeEvent* event) final;
	private:
		QString pixmap_;
	};
	class ItemWidget : public QWidget{
		Q_OBJECT
	public:
		ItemWidget(QWidget* parent = 0);
		~ItemWidget();
		void Update();
		void InitAnimation();
		GET_SET_DEFINE(free_, bool, Free);
		void InsertFlowLignt(const FlowLight& light);
		void StartAnimation();

		void StartTimer();
		void StopTimer();
		int GetUserId();
	protected:
		virtual void timerEvent(QTimerEvent *e);
	signals:
		void FlowFinish();

		public slots:
		
		void OnFinishAnimation();
	private:
		bool			free_;
		QLabel*			bg_;
		QLabel*			user_head_;
		QLabel*			user_icon_;
		QLabel*			user_name_;
		QLabel*			gift_name_;
		QLabel*			gift_icon_;
		QLabel*			gift_num_;
		
		QlLabel*		gift_hit_;
		QPropertyAnimation* animation_geomtry_;
		FlowLight current_;
		std::list<FlowLight> hitList;
		std::mutex mutex_;
		int count_time;
		int count_timer;
	};
	class GiftFlowLight : public QDialog {
		Q_OBJECT
	public:
		GiftFlowLight(QWidget* parent = 0);
		~GiftFlowLight();
		void Init();
		void AddGift(FlowLight& light);
		ItemWidget * GetFreeItem();
		ItemWidget * GetUserItem(int id);
		void Start();
	public slots:
	void OnFinish();
	void OnTestClick();
	private:
		std::mutex mutex_;
		std::list<FlowLight> flowlights_;
		QPushButton*    test;
		ItemWidget * up_item_;
		ItemWidget * under_item_;
	};
}


#endif // !1
