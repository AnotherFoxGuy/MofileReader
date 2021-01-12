#include "catch.hpp"
#include "moFileReader.hpp"

using namespace moFileLib;
#define _L(str) moFileReaderSingleton::GetInstance().Lookup(str)
#define _LC(ctx, str) moFileReaderSingleton::GetInstance().LookupWithContext(ctx, str)

void test()
{
    moFileReaderSingleton::GetInstance().ReadFile("test.mo");
    /* This is the first comment. */
    CHECK("Text Nederlands Een" == _L("String English One"));
    /* This is the second comment. */
    CHECK("Text Nederlands Twee" == _L("String English Two"));
    /* This is the third comment.  */
    CHECK("Text Nederlands Drie" == _L("String English Three"));
}