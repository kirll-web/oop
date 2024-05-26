#pragma once
#include "Utils.h"
#include "CUrlParsingError.h"
#include <string>
//#include <regex>
#include <algorithm>
class CHttpUrl
{
public:
    // выполн€ет парсинг строкового представлени€ URL-а, в случае ошибки парсинга
    // выбрасывает исключение CUrlParsingError, содержащее текстовое описание ошибки
    CHttpUrl(std::string const& url);

    /* инициализирует URL на основе переданных параметров.
        ѕри недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        ≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol = Protocol::HTTP);

    /* инициализирует URL на основе переданных параметров.
        ѕри недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        ≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol,
        unsigned short port);

    // возвращает строковое представление URL-а. ѕорт, €вл€ющийс€ стандартным дл€
    // выбранного протокола (80 дл€ http и 443 дл€ https) в эту строку
    // не должен включатьс€
    std::string GetURL()const;

    // возвращает доменное им€
    std::string GetDomain()const;

    /*
        ¬озвращает им€ документа. ѕримеры:
            /
            /index.html
            /images/photo.jpg
    */
    std::string GetDocument()const;

    // возвращает тип протокола
    Protocol GetProtocol()const;

    // возвращает номер порта
    unsigned short GetPort()const;
private:
    unsigned int m_port;
    Protocol m_protocol;
    std::string m_document;
    std::string m_domain;
    static std::string s_PROTOCOL_PATTERN;
    static std::string s_DOMAIN_PATTERN;
    static std::string s_DOCUMENT_PATTERN;
    static std::string s_PORT_PATTERN;
    static std::string s_URL_PATTERN;
    static const unsigned s_MIN_PORT = 1;
    static const unsigned s_MAX_PORT = 65535;
    void ParseDomain(const std::string& domain);
    void ParseProtocol(const std::string& protocol);
    void ParseProtocol(const Protocol protocol);
    static bool IsCorrectPort(const unsigned& port);
    void ParsePort(const unsigned& port);
    void ParsePort(const std::string& portStr);
    void ParseDocument(const std::string& document);
    static std::string ParseUrlPart(const std::string& part, std::string reg, std::string errorMessage) ;
    static std::string AddSlashToDocument(std::string const& document);
    static std::string s_INVALID_PORT_ERROR_MESSAGE;
    static std::string s_INVALID_PROTOCOL_ERROR_MESSAGE;
    static std::string s_INVALID_DOCUMENT_ERROR_MESSAGE;
    static std::string s_INVALID_DOMAIN_ERROR_MESSAGE;
    static std::string s_INVALID_URL_ERROR_MESSAGE;
    static const unsigned s_HTTP_PORT = 80;
    static const unsigned s_HTTPS_PORT = 443;
};