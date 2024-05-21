#include "MulOnMinimalElement.h"
#include <vector>


void MulOnMinimalElement(std::vector<double>& numbers)
{
	std::vector<double>::iterator itrMinELement = std::min_element(numbers.begin(), numbers.end()); 
	// �������� �������� �� end-��������
	double minElem = *itrMinELement; 

	if (itrMinELement != numbers.end())
	{
		for (std::vector<double>::iterator it = numbers.begin(); it != numbers.end(); ++it)
		{
			*it *= minElem; // ������ ������ ������� �� ������ � �������� ��� �� ����������� ������� � �������
		}
	}
}
