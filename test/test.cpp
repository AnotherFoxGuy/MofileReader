
#include "moFileReader.h"
#include "gtest/gtest.h"

#define _L(str) moFileLib::moFileReaderSingleton::GetInstance().Lookup(str)

auto testMo = "test.mo";

TEST(moFileReader, setup)
{
	EXPECT_EQ(moFileLib::moFileReaderSingleton::GetInstance().ReadFile(testMo), moFileLib::moFileReader::EC_SUCCESS);
}

TEST(moFileReader, Lookup)
{
	moFileLib::moFileReaderSingleton::GetInstance().ReadFile(testMo);
	EXPECT_EQ("Text Nederlands Een", _L("String English One"));
	EXPECT_EQ("Text Nederlands Twee", _L("String English Two"));
	EXPECT_EQ("Text Nederlands Drie", _L("String English Three"));
}