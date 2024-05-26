
#include "CHttpUrl.h"
#include <boost/regex.hpp>

// выполняет парсинг строкового представления URL-а, в случае ошибки парсинга
// выбрасывает исключение CUrlParsingError, содержащее текстовое описание ошибки

std::string CHttpUrl::s_PROTOCOL_PATTERN = "(http|https)";
std::string CHttpUrl::s_DOMAIN_PATTERN = R"([^ \/:*? <>|]+[a-zA-Zа-бА-Б.]{2,126})";
std::string CHttpUrl::s_DOCUMENT_PATTERN = R"(/[^ \/:*?"<>|]*)";
std::string CHttpUrl::s_PORT_PATTERN = "(\:?[0-9]*)";
std::string CHttpUrl::s_URL_PATTERN = "(http|https)://([^\/ :.]+[a-zA-Zа-бА-Б.]{2,126})(\:[0-9]{0, 5})?(/[^ #?]*)?";
std::string CHttpUrl::s_INVALID_PORT_ERROR_MESSAGE = "Invalid port";
std::string CHttpUrl::s_INVALID_PROTOCOL_ERROR_MESSAGE = "Invalid protocol";
std::string CHttpUrl::s_INVALID_DOCUMENT_ERROR_MESSAGE = "Invalid document";
std::string CHttpUrl::s_INVALID_DOMAIN_ERROR_MESSAGE = "Invalid domain";
std::string CHttpUrl::s_INVALID_URL_ERROR_MESSAGE = "Invalid url";

CHttpUrl::CHttpUrl(std::string const& url)
{
    std::string protocol, domain, port, document, urlToLowerCase = StringToLowerCase(url);
    boost::cmatch partsOfUrl;

    if (boost::regex_match(urlToLowerCase.c_str(), partsOfUrl, boost::regex(s_URL_PATTERN)))
    {
        protocol = std::string(partsOfUrl[1].first, partsOfUrl[1].second);
        domain = std::string(partsOfUrl[2].first, partsOfUrl[2].second);
        port = std::string(partsOfUrl[3].first, partsOfUrl[3].second);
        document = std::string(partsOfUrl[4].first, partsOfUrl[4].second);
    }
    else
    {
        throw CUrlParsingError(s_INVALID_URL_ERROR_MESSAGE);
    }

    try
    {
        ParseProtocol(protocol); 
        ParseDomain(domain);
        if (port == "")
        {
            (m_protocol == Protocol::HTTP) ? m_port = s_HTTP_PORT 
                : (m_protocol == Protocol::HTTPS) ? m_port = s_HTTPS_PORT 
                : (throw CUrlParsingError(s_INVALID_PROTOCOL_ERROR_MESSAGE));
        }
        else 
        {
            ParsePort(port);
        }
        if (document != "")
        {
            ParseDocument(document);
        } 
        else
        {
            m_document = AddSlashToDocument(document);
        }
    }
    catch(const CUrlParsingError & e)
    {
        throw CUrlParsingError(e.GetMessage());
    }
}

/* инициализирует URL на основе переданных параметров.
    При недопустимости входных параметров выбрасывает исключение
    std::invalid_argument
    Если имя документа не начинается с символа /, то добавляет / к имени документа
*/
CHttpUrl::CHttpUrl(
    std::string const& domain,
    std::string const& document,
    Protocol protocol)
{
    try
    {
        ParseProtocol(protocol);
        ParseDomain(domain);
        ParseDocument(document);
    }
    catch (const CUrlParsingError& e)
    {
        throw CUrlParsingError(e.GetMessage());
    }
}

/* инициализирует URL на основе переданных параметров.
    При недопустимости входных параметров выбрасывает исключение
    std::invalid_argument
    Если имя документа не начинается с символа /, то добавляет / к имени документа
*/
CHttpUrl::CHttpUrl(
    std::string const& domain,
    std::string const& document,
    Protocol protocol,
    unsigned short port)
{
    try
    {
        ParseProtocol(protocol);
        ParseDomain(domain);
        ParseDocument(document);
        ParsePort(port);
    }
    catch (const CUrlParsingError& e)
    {
        throw CUrlParsingError(e.GetMessage());
    }
}

std::string CHttpUrl::GetURL()const
{
    std::string url;

    switch(m_protocol)
    {
        case Protocol::HTTP : 
            url += "http://";
            break;
        case Protocol::HTTPS:
            url += "https://";
            break;
        default:
            throw CUrlParsingError(s_INVALID_PROTOCOL_ERROR_MESSAGE);
    }

    if ((m_port == s_HTTP_PORT && m_protocol == Protocol::HTTP) || (m_port == s_HTTPS_PORT && m_protocol == Protocol::HTTPS))
    {
        url += m_domain + m_document;
    }
    else
    {
        url += m_domain + ":" + std::to_string(m_port) + m_document;
    }

    return url;
}

std::string CHttpUrl::GetDomain()const
{
    return m_domain;
}

std::string CHttpUrl::GetDocument()const
{
    return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
    return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
    return m_port;
}

std::string CHttpUrl::ParseUrlPart(const std::string& part, std::string reg, std::string errorMessage)
{
    std::string urlToLowerCase = StringToLowerCase(part);

    boost::cmatch partOfUrl;

    if (boost::regex_match(urlToLowerCase.c_str(), partOfUrl, boost::regex(reg)))
    {
        return std::string(partOfUrl[1].first, partOfUrl[1].second);
    }
    else
    {
        throw CUrlParsingError(errorMessage);
    }
}

void CHttpUrl::ParseDomain(const std::string& domain)
{
    m_domain = ParseUrlPart(domain, s_DOMAIN_PATTERN, s_INVALID_DOMAIN_ERROR_MESSAGE);
}

void CHttpUrl::ParseProtocol(const std::string& protocol)
{
    std::string protocolStr;
    try {
        protocolStr = ParseUrlPart(protocol, s_PROTOCOL_PATTERN, s_INVALID_PROTOCOL_ERROR_MESSAGE);
    }
    catch (CUrlParsingError const& e)
    {
        throw CUrlParsingError(e.GetMessage());
    }

    if (protocolStr == "http")
    {
        m_protocol = Protocol::HTTP;
    }
    else if (protocolStr == "https")
    {
        m_protocol = Protocol::HTTPS;
    }
    else
    {
        throw CUrlParsingError(s_INVALID_PROTOCOL_ERROR_MESSAGE);
    }
}

void CHttpUrl::ParseProtocol(const Protocol protocol)
{
    if (protocol == Protocol::HTTP)
    {
        m_protocol = Protocol::HTTP;
    }
    else if (protocol == Protocol::HTTPS)
    {
        m_protocol = Protocol::HTTPS;
    }
    else
    {
        throw CUrlParsingError(s_INVALID_PROTOCOL_ERROR_MESSAGE);
    }
}

void CHttpUrl::ParsePort(const unsigned& port)
{
    if (IsCorrectPort(port))
    {
        m_port = port;
    }
    else
    {
        throw CUrlParsingError(s_INVALID_PORT_ERROR_MESSAGE);
    }
}

bool CHttpUrl::IsCorrectPort(const unsigned& port)
{
    return  (port >= s_MIN_PORT && port <= s_MAX_PORT) ? true : false;
}

void CHttpUrl::ParsePort(const std::string& portStr)
{
    std::string errorMessage = s_INVALID_PORT_ERROR_MESSAGE;
    std::string portStrNumber;
    try 
    {
        portStrNumber = (portStr[0] == ':') ? portStr.substr(1, portStr.length() - 1) : portStr;
        unsigned port = std::stoi(ParseUrlPart(portStrNumber, s_PORT_PATTERN, s_INVALID_PORT_ERROR_MESSAGE));

        if (IsCorrectPort(port))
        {
            m_port = port;
        }
        else
        {
            throw CUrlParsingError(errorMessage);
        }
    } 
    catch (std::invalid_argument const&)
    {
        throw CUrlParsingError(errorMessage);
    }
    catch (std::out_of_range const&)
    {
        throw CUrlParsingError(errorMessage);
    }
    catch (CUrlParsingError const&)
    {
        throw CUrlParsingError(errorMessage);
    }
}


void CHttpUrl::ParseDocument(const std::string& document)
{
    try
    {
        m_document = ParseUrlPart(AddSlashToDocument(document), s_DOCUMENT_PATTERN, s_INVALID_DOCUMENT_ERROR_MESSAGE);
    }
    catch(const CUrlParsingError & e)
    {
        throw CUrlParsingError(e.GetMessage());
    }
}

std::string CHttpUrl::AddSlashToDocument(std::string const &document)
{
    return (document[0] != '/') ? ("/" + document) : document;
}