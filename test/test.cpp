#include "catch.hpp"
#include "moFileReader.hpp"

using namespace moFileLib;

#define MO_TEST_FILE "languages/nl.mo"

#define _L(str) moFR.Lookup(str)
#define _LC(ctx, str) moFR.LookupWithContext(ctx, str)

TEST_CASE("Load mo-file", "[ReadFile]")
{
    moFileReader moFR;
    CHECK(moFR.ReadFile(MO_TEST_FILE) == moFileReader::EC_SUCCESS);
}

TEST_CASE("Load not existing mo-file", "[ReadFile-fail]")
{
    moFileReader moFR;
    CHECK(moFR.ReadFile("e621.mo") == moFileReader::EC_FILENOTFOUND);
}

TEST_CASE("Count number of strings", "[Count]")
{
    moFileReader moFR;
    moFR.ReadFile(MO_TEST_FILE);
    CHECK(11 ==  moFR.GetNumStrings());
}

TEST_CASE("Empties the Lookup-Table", "[Count]")
{
    moFileReader moFR;
    moFR.ReadFile(MO_TEST_FILE);
    CHECK("Text Nederlands Een" == moFR.Lookup("String English One"));
    CHECK(11 ==  moFR.GetNumStrings());
    moFR.ClearTable();
    CHECK("String English One" == moFR.Lookup("String English One"));
    CHECK(0 ==  moFR.GetNumStrings());
}

TEST_CASE("Lookup string", "[Lookup]")
{
    moFileReader moFR;
    moFR.ReadFile(MO_TEST_FILE);
    /* This is the first comment. */
    CHECK("Text Nederlands Een" == _L("String English One"));
    /* This is the second comment. */
    CHECK("Text Nederlands Twee" == _L("String English Two"));
    /* This is the third comment.  */
    CHECK("Text Nederlands Drie" == _L("String English Three"));
}

TEST_CASE("Lookup string with unicode", "[LookupUnicode]")
{
    moFileReader moFR;
    moFR.ReadFile(MO_TEST_FILE);
    CHECK("Omrop Fryslân maakt radio en televisie in het Fries, daarmee is de omroep de enige zender van Nederland die niet in het Nederlanders uitzendt"
          == _L("Omrop Fryslân makket radio en telefyzje yn it Frysk, dêrmei is de omrop de ienige stjoerder fan Nederlân dy’t net yn it Nederlânsk útstjoert"));
    CHECK("De namme ‘Omrop Fryslân’ hâldt yn: regionaal werkenber, aktueel, ûnôfhinklik, betrouber, tagonklik, ûnderhâldend en divers"
          == _L("De naam 'Omrop Fryslân' houdt in: Regionaal herkenbaar, actueel, onafhankelijk, betrouwbaar, toegankelijk, vermakelijk en divers"));
    CHECK("Bûter, brea en brûne sûker" == moFR.Lookup("Bûter, brea en brûne sûker"));
    CHECK("veranderd ß" == _L("geändert ß"));
    CHECK("Ik 💚 Friesland" == _L("I 💚 Fryslân"));
}

TEST_CASE("Lookup string with context", "[LookupWithContext]")
{
    moFileReader moFR;
    moFR.ReadFile(MO_TEST_FILE);
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
    moFR.ReadFile(MO_TEST_FILE);
    CHECK("No match" == moFR.Lookup("No match"));
    CHECK("Can't touch this" == moFR.Lookup("Can't touch this"));
}

TEST_CASE("Lookup not existing strings with context", "[LookupWithContext-fail]")
{
    moFileReader moFR;
    moFR.ReadFile(MO_TEST_FILE);
    CHECK("String English" == moFR.LookupWithContext("Nope", "String English"));
    CHECK("Not this one" == moFR.LookupWithContext("TEST|String|1", "Not this one"));
}