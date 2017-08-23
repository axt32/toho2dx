#pragma once
#include "GameCustomFunction.h"

namespace EnemyFunctions
{
	class EnemyFunction_Test : public GameCustomFunction
	{
	public:
		EnemyFunction_Test();
		~EnemyFunction_Test();

		int iTestVal1;
		float fTestVal2;
		bool bTestVal3;

		void InitCustomFunction();
		void Run();
	};

	class Stage1_EnemyPattern1 : public GameCustomFunction
	{
	private:
		int m_iShotBulletCurrentFrame;

	public:
		Stage1_EnemyPattern1();
		~Stage1_EnemyPattern1();

		int m_iMinimumDuration;
		int m_iMaximumDuration;
		//int m_iBulletType;

		int m_iBulletStyle;
		int m_iBulletSubStyle;
		int m_iBulletQuantity;

		int m_iShotBulletDestFrame;		//ภฮลอน๚

		virtual void InitCustomFunction();
		virtual void Run();
	};

}

