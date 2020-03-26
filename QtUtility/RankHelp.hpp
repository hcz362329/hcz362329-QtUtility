#ifndef RankHelp_hpp
#define RankHelp_hpp
#include<windows.h>
#include <string.h>
namespace HD
{
	enum ERankLevel
	{
		eRankLevelNone						= 0,//����

		eRankLevelSoldierV					= 1,//����5 I II III IV V
		eRankLevelSoldierIV					= 2,//����4
		eRankLevelSoldierIII				= 3,//����3
		eRankLevelSoldierII					= 4,//����2
		eRankLevelSoldierI					= 5,//����1

		eRankLevelCorporalV					= 6,//�鳤5
		eRankLevelCorporalIV				= 7,//�鳤4
		eRankLevelCorporalIII				= 8,//�鳤3
		eRankLevelCorporalII				= 9,//�鳤2
		eRankLevelCorporalI					= 10,//�鳤1


		eRankLevelDecurionV					= 11,//ʲ��5
		eRankLevelDecurionIV				= 12,//ʲ��4
		eRankLevelDecurionIII				= 13,//ʲ��3
		eRankLevelDecurionII				= 14,//ʲ��2
		eRankLevelDecurionI					= 15,//ʲ��1

		eRankLevelCenturionV				= 16,//�ٷ�5
		eRankLevelCenturionIV				= 17,//�ٷ�4
		eRankLevelCenturionIII				= 18,//�ٷ�3
		eRankLevelCenturionII				= 19,//�ٷ�2
		eRankLevelCenturionI				= 20,//�ٷ�1

		eRankLevelChiliarchV				= 21,//ǧ��5
		eRankLevelChiliarchIV				= 22,//ǧ��4
		eRankLevelChiliarchIII				= 23,//ǧ��3
		eRankLevelChiliarchII				= 24,//ǧ��2
		eRankLevelChiliarchI				= 25,//ǧ��1

		eRankLevel10000V					= 26,//���5
		eRankLevel10000IV					= 27,//���4
		eRankLevel10000III					= 28,//���3
		eRankLevel10000II					= 29,//���2
		eRankLevel10000I					= 30,//���1

		eRankLevelImperatorV				= 31,//�󽫾�5
		eRankLevelImperatorIV				= 32,//�󽫾�4
		eRankLevelImperatorIII				= 33,//�󽫾�3
		eRankLevelImperatorII				= 34,//�󽫾�2
		eRankLevelImperatorI				= 35,//�󽫾�1

		eRankLevelFamousLeader				= 36,//��������
	};

	class RankHelp
	{
	public:

		static ERankLevel GetLevelByScore(int score)
		{
			ERankLevel eRankLevel=eRankLevelNone;
			if (score<0)
			{
				eRankLevel=eRankLevelSoldierV;
			}
			else if(score>=21000)
			{
				eRankLevel = eRankLevelFamousLeader;
			}
			else
			{
				eRankLevel =(ERankLevel)(score/600 +1) ;
			}
			return eRankLevel;
		}

		static ERankLevel GetNextLevel(ERankLevel eRank)
		{
			ERankLevel eRankNext = eRankLevelNone;
			if ( eRank >= eRankLevelFamousLeader)
			{
				eRankNext = eRankLevelFamousLeader;
			}
			else
			{
				eRankNext = ERankLevel(eRank + 1);
			}
			return eRankNext;
		}

		static std::wstring GetNextRankNameByScore(int score)
		{
			std::wstring strName;
			ERankLevel eRankLevel = GetLevelByScore(score);
			ERankLevel eRankNextLevel = GetNextLevel(eRankLevel);
			strName = GetNameByLevel(eRankNextLevel);
			return strName;
		}

		static std::wstring GetNameByLevel(int level)
		{
			std::wstring strName;
			switch (level)
			{
			case eRankLevelNone:
				strName = L"����";
				break;
			case eRankLevelSoldierV:
				strName = L"����V";
				break;
			case eRankLevelSoldierIV:
				strName = L"����IV";
				break;				
			case eRankLevelSoldierIII:
				strName = L"����III";
				break;								
			case eRankLevelSoldierII:
				strName = L"����II";
				break;							
			case eRankLevelSoldierI:
				strName = L"����I";
				break;						
			case eRankLevelCorporalV:
				strName = L"�鳤V";
				break;
			case eRankLevelCorporalIV:
				strName = L"�鳤IV";
				break;
			case eRankLevelCorporalIII:
				strName = L"�鳤III";
				break;
			case eRankLevelCorporalII:
				strName = L"�鳤II";
				break;
			case eRankLevelCorporalI:
				strName = L"�鳤I";
				break;

			case eRankLevelDecurionV:
				strName = L"ʲ��V";
				break;
			case eRankLevelDecurionIV:
				strName = L"ʲ��IV";
				break;
			case eRankLevelDecurionIII:
				strName = L"ʲ��III";
				break;
			case eRankLevelDecurionII:
				strName = L"ʲ��II";
				break;
			case eRankLevelDecurionI:
				strName = L"ʲ��I";
				break;

			case eRankLevelCenturionV:
				strName = L"�ٷ�V";
				break;
			case eRankLevelCenturionIV:
				strName = L"�ٷ�IV";
				break;
			case eRankLevelCenturionIII:
				strName = L"�ٷ�III";
				break;
			case eRankLevelCenturionII:
				strName = L"�ٷ�II";
				break;
			case eRankLevelCenturionI:
				strName = L"�ٷ�I";
				break;

			case eRankLevelChiliarchV:
				strName = L"ǧ��V";
				break;
			case eRankLevelChiliarchIV:
				strName = L"ǧ��IV";
				break;
			case eRankLevelChiliarchIII:
				strName = L"ǧ��III";
				break;
			case eRankLevelChiliarchII:
				strName = L"ǧ��II";
				break;
			case eRankLevelChiliarchI:
				strName = L"ǧ��I";
				break;

			case eRankLevel10000V:
				strName = L"���V";
				break;
			case eRankLevel10000IV:
				strName = L"���IV";
				break;
			case eRankLevel10000III:
				strName = L"���III";
				break;
			case eRankLevel10000II:
				strName = L"���II";
				break;
			case eRankLevel10000I:
				strName = L"���I";
				break;

			case eRankLevelImperatorV:
				strName = L"�󽫾�V";
				break;
			case eRankLevelImperatorIV:
				strName = L"�󽫾�IV";
				break;
			case eRankLevelImperatorIII:
				strName = L"�󽫾�III";
				break;	
			case eRankLevelImperatorII:
				strName = L"�󽫾�II";
				break;	
			case eRankLevelImperatorI:
				strName = L"�󽫾�I";
				break;	

			case eRankLevelFamousLeader:
				strName = L"��������";
				break;
			}
			return strName;
		}

		static QPixmap GetPixmapByScore(int score)
		{
			QPixmap pixmap;
			ERankLevel eLevel = GetLevelByScore(score);
			pixmap = GetPixmapByLevel(eLevel);
			return pixmap;
		}

		static QPixmap GetPixmapByLevel(int level)
		{
			QPixmap pixmap;

			char szPath[MAX_PATH]={0};
			
			sprintf(szPath,"%s","./NewWxLv.png");
			
			QPixmap pixWX;
			bool bLoad = pixWX.load(QString::fromStdString(szPath));
			if (bLoad)
			{
				int iHeight = pixWX.height() / 40;
				int iWidth = pixWX.width();
				int pixmap_index = (level-1) >= 0 ? (level-1) : 0;
				pixmap = pixWX.copy(0,pixmap_index * iHeight, iWidth, iHeight);
			}
			return pixmap;
		}

		static float GetPercentOfLevel(int score)
		{
			score = score >=0 ? score : 0;
			float fValue = 0.0;
			int nLevel = GetLevelByScore(score);
			int score_ = score - (nLevel-1)*600;
			score_ = score_ >=0 ? score_ : 0;
			fValue = ((float)(score_))/600;
			return fValue>1?1:fValue;
		}
	};
}

#endif