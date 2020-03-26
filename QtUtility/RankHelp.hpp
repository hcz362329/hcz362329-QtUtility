#ifndef RankHelp_hpp
#define RankHelp_hpp
#include<windows.h>
#include <string.h>
namespace HD
{
	enum ERankLevel
	{
		eRankLevelNone						= 0,//新手

		eRankLevelSoldierV					= 1,//兵卒5 I II III IV V
		eRankLevelSoldierIV					= 2,//兵卒4
		eRankLevelSoldierIII				= 3,//兵卒3
		eRankLevelSoldierII					= 4,//兵卒2
		eRankLevelSoldierI					= 5,//兵卒1

		eRankLevelCorporalV					= 6,//伍长5
		eRankLevelCorporalIV				= 7,//伍长4
		eRankLevelCorporalIII				= 8,//伍长3
		eRankLevelCorporalII				= 9,//伍长2
		eRankLevelCorporalI					= 10,//伍长1


		eRankLevelDecurionV					= 11,//什长5
		eRankLevelDecurionIV				= 12,//什长4
		eRankLevelDecurionIII				= 13,//什长3
		eRankLevelDecurionII				= 14,//什长2
		eRankLevelDecurionI					= 15,//什长1

		eRankLevelCenturionV				= 16,//百夫长5
		eRankLevelCenturionIV				= 17,//百夫长4
		eRankLevelCenturionIII				= 18,//百夫长3
		eRankLevelCenturionII				= 19,//百夫长2
		eRankLevelCenturionI				= 20,//百夫长1

		eRankLevelChiliarchV				= 21,//千夫长5
		eRankLevelChiliarchIV				= 22,//千夫长4
		eRankLevelChiliarchIII				= 23,//千夫长3
		eRankLevelChiliarchII				= 24,//千夫长2
		eRankLevelChiliarchI				= 25,//千夫长1

		eRankLevel10000V					= 26,//万夫长5
		eRankLevel10000IV					= 27,//万夫长4
		eRankLevel10000III					= 28,//万夫长3
		eRankLevel10000II					= 29,//万夫长2
		eRankLevel10000I					= 30,//万夫长1

		eRankLevelImperatorV				= 31,//大将军5
		eRankLevelImperatorIV				= 32,//大将军4
		eRankLevelImperatorIII				= 33,//大将军3
		eRankLevelImperatorII				= 34,//大将军2
		eRankLevelImperatorI				= 35,//大将军1

		eRankLevelFamousLeader				= 36,//绝世名将
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
				strName = L"新手";
				break;
			case eRankLevelSoldierV:
				strName = L"兵卒V";
				break;
			case eRankLevelSoldierIV:
				strName = L"兵卒IV";
				break;				
			case eRankLevelSoldierIII:
				strName = L"兵卒III";
				break;								
			case eRankLevelSoldierII:
				strName = L"兵卒II";
				break;							
			case eRankLevelSoldierI:
				strName = L"兵卒I";
				break;						
			case eRankLevelCorporalV:
				strName = L"伍长V";
				break;
			case eRankLevelCorporalIV:
				strName = L"伍长IV";
				break;
			case eRankLevelCorporalIII:
				strName = L"伍长III";
				break;
			case eRankLevelCorporalII:
				strName = L"伍长II";
				break;
			case eRankLevelCorporalI:
				strName = L"伍长I";
				break;

			case eRankLevelDecurionV:
				strName = L"什长V";
				break;
			case eRankLevelDecurionIV:
				strName = L"什长IV";
				break;
			case eRankLevelDecurionIII:
				strName = L"什长III";
				break;
			case eRankLevelDecurionII:
				strName = L"什长II";
				break;
			case eRankLevelDecurionI:
				strName = L"什长I";
				break;

			case eRankLevelCenturionV:
				strName = L"百夫长V";
				break;
			case eRankLevelCenturionIV:
				strName = L"百夫长IV";
				break;
			case eRankLevelCenturionIII:
				strName = L"百夫长III";
				break;
			case eRankLevelCenturionII:
				strName = L"百夫长II";
				break;
			case eRankLevelCenturionI:
				strName = L"百夫长I";
				break;

			case eRankLevelChiliarchV:
				strName = L"千夫长V";
				break;
			case eRankLevelChiliarchIV:
				strName = L"千夫长IV";
				break;
			case eRankLevelChiliarchIII:
				strName = L"千夫长III";
				break;
			case eRankLevelChiliarchII:
				strName = L"千夫长II";
				break;
			case eRankLevelChiliarchI:
				strName = L"千夫长I";
				break;

			case eRankLevel10000V:
				strName = L"万夫长V";
				break;
			case eRankLevel10000IV:
				strName = L"万夫长IV";
				break;
			case eRankLevel10000III:
				strName = L"万夫长III";
				break;
			case eRankLevel10000II:
				strName = L"万夫长II";
				break;
			case eRankLevel10000I:
				strName = L"万夫长I";
				break;

			case eRankLevelImperatorV:
				strName = L"大将军V";
				break;
			case eRankLevelImperatorIV:
				strName = L"大将军IV";
				break;
			case eRankLevelImperatorIII:
				strName = L"大将军III";
				break;	
			case eRankLevelImperatorII:
				strName = L"大将军II";
				break;	
			case eRankLevelImperatorI:
				strName = L"大将军I";
				break;	

			case eRankLevelFamousLeader:
				strName = L"绝世名将";
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