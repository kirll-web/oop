#include <iostream>
#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <vector>

std::string ProtocolToString(Protocol protocol)
{
	return (protocol == Protocol::HTTP) ? "http" : "https";
}

void PrintUrlInfo(CHttpUrl const& url)
{
	std::cout << "Protocol: " << ProtocolToString(url.GetProtocol()) << std::endl;
	std::cout << "Domain: " << url.GetDomain() << std::endl;
	std::cout << "Port: " << url.GetPort() << std::endl;
	std::cout << "Document: " << url.GetDocument() << std::endl;
	std::cout << "Url: " << url.GetURL() << std::endl << std::endl;

}

int main()
{
	std::vector<CHttpUrl> urlList;

	while (!std::cin.eof() && !std::cin.bad())
	{
		std::cout << "Input url: ";
		std::string inputLine;
		std::cin >> inputLine;
		try
		{
			CHttpUrl url(inputLine);
			urlList.push_back(url);
			PrintUrlInfo(urlList.back());
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl << std::endl;
		}
	}
	return 0;
}
