#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "moFileReader.hpp"

using namespace moFileLib;
#define _L(str) moFileReaderSingleton::GetInstance().Lookup(str)
#define _LC(ctx, str) moFileReaderSingleton::GetInstance().LookupWithContext(ctx, str)

TEST_CASE("Load mo-file", "[ReadFile]")
{
    CHECK(moFileReaderSingleton::GetInstance().ReadFile("test.mo") == moFileLib::moFileReader::EC_SUCCESS);
}

TEST_CASE("Load not existing mo-file", "[ReadFile-fail]")
{
    CHECK(moFileReaderSingleton::GetInstance().ReadFile("e621.mo") == moFileLib::moFileReader::EC_FILENOTFOUND);
}

TEST_CASE("Lookup string", "[Lookup]")
{
    moFileReaderSingleton::GetInstance().ReadFile("test.mo");
    /* This is the first comment. */
    CHECK("Text Nederlands Een" == _L("String English One"));
    /* This is the second comment. */
    CHECK("Text Nederlands Twee" == _L("String English Two"));
    /* This is the third comment.  */
    CHECK("Text Nederlands Drie" == _L("String English Three"));
}

TEST_CASE("Lookup string with context", "[LookupWithContext]")
{
    moFileReaderSingleton::GetInstance().ReadFile("test.mo");
    /* This is the first comment. */
    CHECK("Text Nederlands Een" == _LC("TEST|String|1", "String English"));
    /* This is the second comment. */
    CHECK("Text Nederlands Twee" == _LC("TEST|String|2", "String English"));
    /* This is the third comment.  */
    CHECK("Text Nederlands Drie" == _LC("TEST|String|3", "String English"));
}

TEST_CASE("Lookup not existing strings", "[Lookup-fail]")
{
    moFileReaderSingleton::GetInstance().ReadFile("test.mo");
    CHECK("No match" == moFileReaderSingleton::GetInstance().Lookup("No match"));
    CHECK("Can't touch this" == moFileReaderSingleton::GetInstance().Lookup("Can't touch this"));
}

TEST_CASE("Lookup not existing strings with context", "[LookupWithContext-fail]")
{
    moFileReaderSingleton::GetInstance().ReadFile("test.mo");
    CHECK("String English" == _LC("Nope", "String English"));
    CHECK("Not this one" == _LC("TEST|String|1", "Not this one"));
}