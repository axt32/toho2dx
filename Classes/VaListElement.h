#pragma once
#include "cocos2d.h"
USING_NS_CC;

enum VAELEMENT_TYPE
{
	VA_NOT_ASSIGNED = 0,
	VA_INT,
	VA_FLOAT,
	VA_BOOL,
	VA_STRING
};

//�������ڸ� �迭�� ��� Ŭ����. �Ƹ��� ��ȿ�����̶� �����ȴ�.
class VaListElement
{
public:
	VaListElement();
	VaListElement(VAELEMENT_TYPE IN_Type, void * IN_pValue);
	~VaListElement();

	VAELEMENT_TYPE m_va_type;
	void * m_value;
};