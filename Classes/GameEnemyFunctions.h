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

		virtual void InitCustomFunction();
		virtual void Run();
	};
}

