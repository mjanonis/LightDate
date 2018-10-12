#include "LightDate.hpp"
#include "gtest/gtest.h"

// Constructor tests

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
        FAIL() << "Expected std::runtime_error";
    }
}

// Setter tests

TEST(SetterTest, SetYearSetsAValidDate)
{
    Date test{2010, Month::jan, 1};
    test.setYear(2000);
    ASSERT_EQ(test.getYear(), 2000);
}

TEST(SetterTest, SetMonthSetsAValidDate)
{
    Date test{2010, Month::jan, 1};
    test.setMonth(Month::mar);
    ASSERT_EQ(test.getMonth(), Month::mar);
}

TEST(SetterTest, SetMonthThrowsExceptionOnInvaldDate)
{
    Date test{2004, Month::feb, 29};
    try {
        test.setMonth(Month::mar);
    }
    catch (std::runtime_error& e) {
        ASSERT_EQ(e.what(), std::string("Invalid month set"));
    }
    catch (...) {
        FAIL() << "Expected std::runtime_error";
    }
}

TEST(SetterTest, SetDaySetsAValidDay)
{
    Date test{2010, Month::jan, 1};
    test.setDay(20);
    ASSERT_EQ(test.getDay(), 20);
}

TEST(SetterTest, SetDayThrowsExceptionOnInvalidDate)
{
    Date test{2010, Month::jan, 1};
    try {
        test.setDay(50);
    }
    catch (std::runtime_error& e) {
        ASSERT_EQ(e.what(), std::string("Invalid day set"));
    }
    catch (...) {
        FAIL() << "Expected std::runtime_error";
    }
}

// Conversion tests

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

// Increment tests

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

// Compound asignment addition tests

TEST(CompoundAssignmentAddition, Addition)
{
    Date test{2010, Month::jan, 1};
    test += 10;
    ASSERT_EQ(test.getYear(), 2010);
    ASSERT_EQ(test.getMonth(), Month::jan);
    ASSERT_EQ(test.getDay(), 11);
}

TEST(CompoundAssignmentAddition, AdditionRollOverMonth)
{
    Date test{2010, Month::jan, 31};
    test += 10;
    ASSERT_EQ(test.getYear(), 2010);
    ASSERT_EQ(test.getMonth(), Month::feb);
    ASSERT_EQ(test.getDay(), 10);
}

TEST(CompoundAssignmentAddition, AdditionRollOverYear)
{
    Date test{2010, Month::dec, 31};
    test += 10;
    ASSERT_EQ(test.getYear(), 2011);
    ASSERT_EQ(test.getMonth(), Month::jan);
    ASSERT_EQ(test.getDay(), 10);
}

// Compound asignment subtraction tests

TEST(CompoundAssignmentSubtraction, Subtraction)
{
    Date test{2010, Month::jan, 11};
    test -= 10;
    ASSERT_EQ(test.getYear(), 2010);
    ASSERT_EQ(test.getMonth(), Month::jan);
    ASSERT_EQ(test.getDay(), 1);
}

TEST(CompoundAssignmentSubtraction, SubtractionRollOverMonth)
{
    Date test{2010, Month::feb, 1};
    test -= 10;
    ASSERT_EQ(test.getYear(), 2010);
    ASSERT_EQ(test.getMonth(), Month::jan);
    ASSERT_EQ(test.getDay(), 22);
}

TEST(CompoundAssignmentSubtraction, SubtractionRollOverYear)
{
    Date test{2010, Month::jan, 1};
    test -= 10;
    ASSERT_EQ(test.getYear(), 2009);
    ASSERT_EQ(test.getMonth(), Month::dec);
    ASSERT_EQ(test.getDay(), 22);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}