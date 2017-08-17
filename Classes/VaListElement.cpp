#include "VaListElement.h"

VaListElement :: VaListElement()
{
	m_va_type = VA_NOT_ASSIGNED;
	m_value = nullptr;
}

VaListElement :: VaListElement(VAELEMENT_TYPE IN_Type, void * IN_pValue)
{
	m_va_type = IN_Type;
	m_value = IN_pValue;
}

VaListElement :: ~VaListElement()
{
	CCLOG("VaListElement Deleted");
	if (m_value != nullptr)
	{
		if (m_va_type != VA_NOT_ASSIGNED)
		{
			switch (m_va_type)
			{
			case VA_INT:
				delete (int *)m_value;
				break;
			case VA_FLOAT:
				delete (float *)m_value;
				break;
			case VA_BOOL:
				delete (bool *)m_value;
				break;
			case VA_STRING:
				delete (String *)m_value;
				break;
			default:
				break;
			}
		}
	}
}