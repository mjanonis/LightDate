#include "LightDate.hpp"
#include "gtest/gtest.h"

TEST(ConstructorTest, ConstructorCreatesValidDate)
{
    Date test{2018, Month::jan, 1};
    ASSERT_EQ(test.getYear(), 2018);
    ASSERT_EQ(test.getMonth(), Month::jan);
    ASSERT_EQ(test.getDay(), 1);
    ASSERT_EQ(test.getWeekday(), Weekday::mon);
}

TEST(ValidDateTest, InvalidDateThrowsException)
{
    try {
        Date invalid{2018, Month::feb, 29};
    }
    catch (std::runtime_error& e) {
        ASSERT_EQ(e.what(), std::string("Invalid date constructed: 2018-2-29"));
    }
    catch (...) {
        FAIL() << "Expected std::runtime_exception";
    }
}

TEST(ConversionTest, CorrectConversionFromTm)
{
    // test_tm represents 2000-02-15
    tm test_tm;
    test_tm.tm_year = 100;
    test_tm.tm_mon = 1;
    test_tm.tm_mday = 15;
    test_tm.tm_wday = 2;

    Date conv(test_tm);

    ASSERT_EQ(conv.getYear(), 2000);
    ASSERT_EQ(conv.getMonth(), Month::feb);
    ASSERT_EQ(conv.getDay(), 15);
    ASSERT_EQ(conv.getWeekday(), Weekday::tue);
}

TEST(ConversionTest, CorrectConversionFromTmNoWeekday)
{
    // test_tm represents 2000-02-15
    tm test_tm;
    test_tm.tm_year = 100;
    test_tm.tm_mon = 1;
    test_tm.tm_mday = 15;

    Date conv(test_tm);

    ASSERT_EQ(conv.getYear(), 2000);
    ASSERT_EQ(conv.getMonth(), Month::feb);
    ASSERT_EQ(conv.getDay(), 15);
    ASSERT_EQ(conv.getWeekday(), Weekday::tue);
}

TEST(PostIncrementTest, AddsOneDay)
{
    Date test{2010, Month::jun, 10};
    test++;
    ASSERT_EQ(test.getYear(), 2010);
    ASSERT_EQ(test.getMonth(), Month::jun);
    ASSERT_EQ(test.getDay(), 11);
}

TEST(PostIncrementTest, CorrectlyHandlesEndOfMonthDates)
{
    Date test{2017, Month::nov, 30};
    test++;
    ASSERT_EQ(test.getYear(), 2017);
    ASSERT_EQ(test.getMonth(), Month::dec);
    ASSERT_EQ(test.getDay(), 1);
    ASSERT_EQ(test.getWeekday(), Weekday::fri);
}

TEST(PostIncrementTest, CorrectlyHandlesEndOfYearDates)
{
    Date test{2017, Month::dec, 31};
    ++test;
    ASSERT_EQ(test.getYear(), 2018);
    ASSERT_EQ(test.getMonth(), Month::jan);
    ASSERT_EQ(test.getDay(), 1);
    ASSERT_EQ(test.getWeekday(), Weekday::mon);
}

TEST(PreIncrementTest, AddsOneDay)
{
    Date test{2010, Month::jun, 10};
    ++test;
    ASSERT_EQ(test.getYear(), 2010);
    ASSERT_EQ(test.getMonth(), Month::jun);
    ASSERT_EQ(test.getDay(), 11);
}

TEST(PreIncrementTest, CorrectlyHandlesEndOfMonthDates)
{
    Date test{2017, Month::nov, 30};
    ++test;
    ASSERT_EQ(test.getYear(), 2017);
    ASSERT_EQ(test.getMonth(), Month::dec);
    ASSERT_EQ(test.getDay(), 1);
    ASSERT_EQ(test.getWeekday(), Weekday::fri);
}

TEST(PreIncrementTest, CorrectlyHandlesEndOfYearDates)
{
    Date test{2017, Month::dec, 31};
    ++test;
    ASSERT_EQ(test.getYear(), 2018);
    ASSERT_EQ(test.getMonth(), Month::jan);
    ASSERT_EQ(test.getDay(), 1);
    ASSERT_EQ(test.getWeekday(), Weekday::mon);
}



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}