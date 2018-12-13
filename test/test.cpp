
#include "moFileReader.h"
#include "gtest/gtest.h"

using namespace moFileLib;
#define _LC(ctx,str) moFileReaderSingleton::GetInstance().LookupWithContext(ctx,str)

auto testMo = "test.mo";

TEST(moFileReader, setup)
{
	EXPECT_EQ(moFileReaderSingleton::GetInstance().ReadFile(testMo), moFileLib::moFileReader::EC_SUCCESS);
}

TEST(moFileReader, Lookup)
{
    moFileReaderSingleton::GetInstance ().ReadFile (testMo);
    /* This is the first comment. */
    EXPECT_EQ ("Text Nederlands Een", _ ("String English One"));
    /* This is the second comment. */
    EXPECT_EQ ("Text Nederlands Twee", _ ("String English Two"));
    /* This is the third comment.  */
    EXPECT_EQ ("Text Nederlands Drie", _ ("String English Three"));
}


TEST (moFileReader, LookupWithContext)
{
    moFileReaderSingleton::GetInstance ().ReadFile (testMo);
    /* This is the first comment. */
    EXPECT_EQ ("Text Nederlands Een", _LC ("TEST|String|1", "String English"));
    /* This is the second comment. */
    EXPECT_EQ ("Text Nederlands Twee", _LC ("TEST|String|2", "String English"));
    /* This is the third comment.  */
    EXPECT_EQ ("Text Nederlands Drie", _LC ("TEST|String|3", "String English"));
}