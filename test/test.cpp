#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "moFileReader.hpp"

using namespace moFileLib;

#define _L(str) moFR.Lookup(str)
#define _LC(ctx, str) moFR.LookupWithContext(ctx, str)

TEST_CASE("Load mo-file", "[ReadFile]")
{
    moFileReader moFR;
    CHECK(moFR.ReadFile("test.mo") == moFileReader::EC_SUCCESS);
}

TEST_CASE("Load not existing mo-file", "[ReadFile-fail]")
{
    moFileReader moFR;
    CHECK(moFR.ReadFile("e621.mo") == moFileReader::EC_FILENOTFOUND);
}

TEST_CASE("Count number of strings", "[Count]")
{
    moFileReader moFR;
    moFR.ReadFile("test.mo");
    CHECK(7 ==  moFR.GetNumStrings());
}

TEST_CASE("Empties the Lookup-Table", "[Count]")
{
    moFileReader moFR;
    moFR.ReadFile("test.mo");
    CHECK("Text Nederlands Een" == moFR.Lookup("String English One"));
    CHECK(7 ==  moFR.GetNumStrings());
    moFR.ClearTable();
    CHECK("String English One" == moFR.Lookup("String English One"));
    CHECK(0 ==  moFR.GetNumStrings());
}

TEST_CASE("Lookup string", "[Lookup]")
{
    moFileReader moFR;
    moFR.ReadFile("test.mo");
    /* This is the first comment. */
    CHECK("Text Nederlands Een" == _L("String English One"));
    /* This is the second comment. */
    CHECK("Text Nederlands Twee" == _L("String English Two"));
    /* This is the third comment.  */
    CHECK("Text Nederlands Drie" == _L("String English Three"));
}

TEST_CASE("Lookup string with context", "[LookupWithContext]")
{
    moFileReader moFR;
    moFR.ReadFile("test.mo");
    /* This is the first comment. */
    CHECK("Text Nederlands Een" == _LC("TEST|String|1", "String English"));
    /* This is the second comment. */
    CHECK("Text Nederlands Twee" == _LC("TEST|String|2", "String English"));
    /* This is the third comment.  */
    CHECK("Text Nederlands Drie" == _LC("TEST|String|3", "String English"));
}

TEST_CASE("Lookup not existing strings", "[Lookup-fail]")
{
    moFileReader moFR;
    moFR.ReadFile("test.mo");
    CHECK("No match" == moFR.Lookup("No match"));
    CHECK("Can't touch this" == moFR.Lookup("Can't touch this"));
}

TEST_CASE("Lookup not existing strings with context", "[LookupWithContext-fail]")
{
    moFileReader moFR;
    moFR.ReadFile("test.mo");
    CHECK("String English" == _LC("Nope", "String English"));
    CHECK("Not this one" == _LC("TEST|String|1", "Not this one"));
}