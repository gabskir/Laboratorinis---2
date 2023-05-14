#include "pch.h"
#include "..//funkcijos.h"

TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(TaipArNeTest, ReturnsTrueForValidInput) {
	char validInput = 't';
	bool result = taipArNe(validInput);
	ASSERT_TRUE(result);
}

TEST(TaipArNeTest, ReturnsFalseForInvalidInput) {
	char invalidInput = 'x';
	bool result = taipArNe(invalidInput);
	ASSERT_FALSE(result);
}