
#include "moFileReader.h"
#include "gtest/gtest.h"

using namespace moFileLib;
#define _L(str) moFileReaderSingleton::GetInstance().Lookup(str)
#define _LC(ctx,str) moFileReaderSingleton::GetInstance().LookupWithContext(ctx,str)

TEST(moFileReader, setup)
{
	EXPECT_EQ(moFileReaderSingleton::GetInstance().ReadFile("test.mo"), moFileLib::moFileReader::EC_SUCCESS);
}

TEST(moFileReader, Lookup)
{
    moFileReaderSingleton::GetInstance ().ReadFile ("test.mo");
    /* This is the first comment. */
    EXPECT_EQ ("Text Nederlands Een", _L ("String English One"));
    /* This is the second comment. */
    EXPECT_EQ ("Text Nederlands Twee", _L ("String English Two"));
    /* This is the third comment.  */
    EXPECT_EQ ("Text Nederlands Drie", _L ("String English Three"));
}


TEST (moFileReader, LookupWithContext)
{
    moFileReaderSingleton::GetInstance ().ReadFile ("test.mo");
    /* This is the first comment. */
    EXPECT_EQ ("Text Nederlands Een", _LC ("TEST|String|1", "String English"));
    /* This is the second comment. */
    EXPECT_EQ ("Text Nederlands Twee", _LC ("TEST|String|2", "String English"));
    /* This is the third comment.  */
    EXPECT_EQ ("Text Nederlands Drie", _LC ("TEST|String|3", "String English"));
}