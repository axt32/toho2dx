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

	class Stage1_Pattern1 : public GameCustomFunction
	{
	public:
		Stage1_Pattern1();
		~Stage1_Pattern1();

		int m_iMinimumDuration;
		int m_iMaximumDuration;
		//int m_iBulletType;

		virtual void InitCustomFunction();
		virtual void Run();
	};

}

