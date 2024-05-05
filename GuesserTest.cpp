/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

TEST(GuesserTest, strings_match)
{
    string secret = "match";
	string guess = "match";
    Guesser guesser(secret);
    ASSERT_TRUE(guesser.match(guess));
}

TEST(GuesserTest, strings_dont_match)
{
    string secret = "match";
	string guess = "nomatch";
    Guesser guesser(secret);
    ASSERT_FALSE(guesser.match(guess));
}

TEST(GuesserTest, case_dont_match)
{
    string secret = "match";
	string guess = "Match";
    Guesser guesser(secret);
    ASSERT_FALSE(guesser.match(guess));
}

TEST(GuesserTest, symbols_match)
{
    string secret = "!@#$";
	string guess = "!@#$";
    Guesser guesser(secret);
    ASSERT_TRUE(guesser.match(guess));
}

TEST(GuesserTest, truncates_over_32characters)
{
    string secret = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
	string guess =  "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    Guesser guesser(secret);
    ASSERT_TRUE(guesser.match(guess));
}

TEST(GuesserTest, start_with_3attempts)
{
    string secret = "test";
    Guesser guesser(secret);
	unsigned int attempts = guesser.remaining();
	ASSERT_EQ(3, attempts);
}

TEST(GuesserTest, three_attempts)
{
    string secret = "test";
	string guess = "tes";
    Guesser guesser(secret);
	guesser.match(guess);
	guesser.match(guess);
	guesser.match(guess);
	ASSERT_EQ(0, guesser.remaining());
}

TEST(GuesserTest, lock_after_3attmpts)
{
    string secret = "test";
	string guess = "tes";
    Guesser guesser(secret);
	guesser.match(guess);
	guesser.match(guess);
	guesser.match(guess);
    ASSERT_FALSE(guesser.match(secret));
}

TEST(GuesserTest, attempts_reset)
{
    string secret = "test";
	string guess = "tes";
    Guesser guesser(secret);
	guesser.match(guess);
	guesser.match(guess);
	guesser.match(secret);
	ASSERT_EQ(3, guesser.remaining());
}

TEST(GuesserTest, locks_with_bruteforce)
{
    string secret = "test";
	string guess = "t";
    Guesser guesser(secret);
	guesser.match(guess);
    ASSERT_FALSE(guesser.match(secret));
}

TEST(GuesserTest, distance_not_exceed_secret)
{
    string secret = "t";
	string guess = "test";
    Guesser guesser(secret);
	guesser.match(guess);
    ASSERT_TRUE(guesser.match(secret));
}
