/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°2
 *
 * TestNumber.cpp
 * c++ -std=c++20 -o TestNumber Number.cpp TestNumber.cpp -lgtest -lpthread
 */

#include <exception>
#include <sstream>
#include <string>
#include <utility>

#include <cstdlib>
#include <ctime>


#include <gtest/gtest.h>

#include "Number.hpp"

 
TEST( TestNumber, TestNumber0 )
{
    Number n{ 0 };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "0" );
}
 
TEST( TestNumber, TestNumber12345678 )
{
    Number n{ 12345678 };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "12345678" );
}
 
TEST( TestNumber, TestNumberBig )
{
    Number n{ 12345123451234512345UL };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "12345123451234512345" );
}

TEST( TestNumber, TestNumberRandom )
{
    auto r{ std::rand() };
    Number n{ static_cast< unsigned long >( r )};
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), std::to_string( r ));
}

TEST(TestNumber, TestCopyConstructor)
{
    Number n1{45678};
    Number n2{n1};
    std::ostringstream os;
    os << n2;
    EXPECT_EQ(os.str(), "45678");
}

TEST(TestNumber, TestAssignmentOperator)
{
    Number n1{45678};
    Number n2 = n1;
    std::ostringstream os;
    os << n2;
    EXPECT_EQ(os.str(), "45678");
}

TEST(TestNumber, TestAdd)
{
    Number n{456};
    n= n + 11;
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "467");
}

TEST(TestNumber, TestAddCarry)
{
    Number n{456};
    n= n + 555;
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "1011");
}

TEST(TestNumber, TestMultiply)
{
    Number n{456};
    n= n * 3;
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "1368");
}

TEST(TestNumber, TestMultiplyCarry)
{
    Number n{456};
    n= n * 11;
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "5016");
}

TEST( TestNumber, TestFactorial123 )
{
    std::ostringstream os;
    os << Number::factorial( 123 );
    EXPECT_EQ( os.str(), "121463043670253296757662432418812958554542170884833823153289181618292"
                         "358923621676688311569606126402021707358352212940477825910915704116514"
                         "72186029519906261646730733907419814952960000000000000000000000000000" );
}

TEST(TestNumber, TestStringConstructorValid) {
    Number n("65438");
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "65438");
}

TEST(TestNumber, TestStringConstructorSingleDigit) {
    Number n("1");
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "1");
}

TEST(TestNumber, TestStringConstructorInvalid) {
    EXPECT_THROW(Number("123a456"), std::invalid_argument);
    EXPECT_THROW(Number(""), std::invalid_argument); 
}

TEST(TestNumber, TestInputStreamOperator) {
    std::istringstream input("  78910xyz");
    Number n("0");
    input >> n;
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "78910");
}

TEST(TestNumber, TestMoveConstructor) {
    Number n1("12345");
    Number n2 = std::move(n1); 
    std::ostringstream os;
    os << n2;
    EXPECT_EQ(os.str(), "12345");
}

TEST(TestNumber, TestMoveAssignment) {
    Number n1("67890");
    Number n2("0");
    n2 = std::move(n1); 
    std::ostringstream os;
    os << n2;
    EXPECT_EQ(os.str(), "67890");
}


int main( int argc, char * argv[] )
{
    std::srand( std::time( nullptr ));
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
