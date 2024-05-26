#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../http/CHttpUrl.h"
#include "../http/CUrlParsingError.h"
#include "../http/Utils.h"


bool TestingExceptionsCHttpUrl(const std::string& urlString)
{
    try
    {
        CHttpUrl url(urlString);
    }
    catch (const CUrlParsingError&)
    {
        return true;
    }
    catch (std::string const&)
    {
        return false;
    }
    return false;
}

SCENARIO("Check if an exception is thrown") {
    CHECK(TestingExceptionsCHttpUrl("http://url.com") == false);
    CHECK(TestingExceptionsCHttpUrl(""));
    CHECK(TestingExceptionsCHttpUrl("chttp://url.com"));
    CHECK(TestingExceptionsCHttpUrl("chttps://url.com"));
    CHECK(TestingExceptionsCHttpUrl("https://url.com") == false);
    CHECK(TestingExceptionsCHttpUrl("http://urlaskdkksakdkaskdkas.com") == false);
    CHECK(TestingExceptionsCHttpUrl("http:///urlaskdkksakdkaskdkas.com"));
    CHECK(TestingExceptionsCHttpUrl("http::///urlaskdkksakdkaskdkas.com/"));
    CHECK(TestingExceptionsCHttpUrl("http:://urlaskdkksakdkaskdkas.com"));
    CHECK(TestingExceptionsCHttpUrl("http://urlaskdkksakdkaskdkas") == false);
    CHECK(TestingExceptionsCHttpUrl("http://.urlaskdkksakdkaskdkas"));
    CHECK(TestingExceptionsCHttpUrl("http://urlaskdkksakdkaskdkas.com:443") == false);
    CHECK(TestingExceptionsCHttpUrl("http://urlaskdkksakdkaskdkas.com:443/") == false);
    CHECK(TestingExceptionsCHttpUrl("http://urlaskdkksakdkaskdkas.com:70000"));
    CHECK(TestingExceptionsCHttpUrl("http://urlaskdkksakdkaskdkas.com:-1"));
    CHECK(TestingExceptionsCHttpUrl("http://urlaskdkksakdkaskdkas.com:443/document.html/"));
    CHECK(TestingExceptionsCHttpUrl("http://urlaskdkksakdkaskdkas.com:443/document.html") == false);
    CHECK(TestingExceptionsCHttpUrl("http://urlaskdkksakdkaskdkas.com:7437743/document.html"));
}

bool TestingExceptionsCHttpProtocolDomainDocument(Protocol protocol, std::string domain, std::string document)
{
    try
    {
        CHttpUrl url(domain, document, protocol);
    }
    catch (const CUrlParsingError&)
    {
        return true;
    }
    catch (std::string const&)
    {
        return false;
    }
    return false;
}


TEST_CASE("check TestingExceptionsCHttpProtocolDomainDocument")
{
    SECTION("check incorrect document ") {
        CHECK(TestingExceptionsCHttpProtocolDomainDocument(Protocol::HTTP, "vc.com", "&*.com"));
        CHECK(TestingExceptionsCHttpProtocolDomainDocument(Protocol::HTTP, "vc.com", "&*"));
        CHECK(TestingExceptionsCHttpProtocolDomainDocument(Protocol::HTTP, "vc.com", "doc") == false);
        CHECK(TestingExceptionsCHttpProtocolDomainDocument(Protocol::HTTP, "vc.com", "/doc.docx") == false);
    }
    SECTION("check incorrect domain") {
        CHECK(TestingExceptionsCHttpProtocolDomainDocument(Protocol::HTTP, "vc.com/", "doc.docx"));
        CHECK(TestingExceptionsCHttpProtocolDomainDocument(Protocol::HTTP, "&*vcasdasd.com", "doc.docx"));
        CHECK(TestingExceptionsCHttpProtocolDomainDocument(Protocol::HTTP, "1.com/", "doc.docx"));
        CHECK(TestingExceptionsCHttpProtocolDomainDocument(Protocol::HTTP, "ab.com", "doc.docx") == false);
        CHECK(TestingExceptionsCHttpProtocolDomainDocument(Protocol::HTTP, "1.com/", "doc.docx"));
    }

    

   
}
