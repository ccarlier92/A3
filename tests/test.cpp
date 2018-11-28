#include "../src/base.h"
#include "../src/parser.h"
#include "../src/command.cpp"
#include "../src/connector.cpp"
#include "../src/and.cpp"
#include "../src/or.cpp"
#include "../src/semiColon.cpp"

#include "gtest/gtest.h"

TEST(Parser,SingleCommand)
{
  	std::string input = "echo hello";
  	std::ostringstream oss;
	std::streambuf* p_cout_streambuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());

	Base * result = Parse(input);
  	result->print_args();

	std::cout.rdbuf(p_cout_streambuf);

	assert(oss && oss.str() == input );
	std::cout << oss.str();
}


TEST(Parser,MultiCommand)
{
        std::string input = "echo hello && ls -m || exit ; echo end";
        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        Base * result = Parse(input);
        result->print_args();

        std::cout.rdbuf(p_cout_streambuf);

        assert(oss && oss.str() == input);
        std::cout << oss.str();
}

TEST(Parser,Comments)
{
        std::string input = "echo hello #comments";
        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        Base * result = Parse(input);
        result->print_args();

        std::cout.rdbuf(p_cout_streambuf);

        assert(oss && oss.str() == "echo hello");
        std::cout << oss.str();
}

TEST(SingleCommand,True)
{
	std::string input = "echo hello world";
	Base* resultat = Parse(input);
	EXPECT_EQ(true, resultat->execute());
}

TEST(SingleCommand,False)
{
        std::string input = "hello world";
        Base* resultat = Parse(input);
        EXPECT_EQ(false, resultat->execute());
}


TEST(And,BothTrue)
{
	std::string input = "echo hello && echo world";
	Base* resultat = Parse(input);
	EXPECT_EQ(true, resultat->execute());
}

TEST(And,BothFalse)
{
        std::string input = "hello && world";
        Base* resultat = Parse(input);
        EXPECT_EQ(false, resultat->execute());
}

TEST(And,TrueFalse)
{
        std::string input = "echo hello && world";
        Base* resultat = Parse(input);
        EXPECT_EQ(false, resultat->execute());
}
TEST(And,FalseTrue)
{
        std::string input = "hello && echo world";
        Base* resultat = Parse(input);
        EXPECT_EQ(false, resultat->execute());
}

TEST(Or,BothFalse)
{
        std::string input = "hello || world";
        Base* resultat = Parse(input);
        EXPECT_EQ(false, resultat->execute());
}
TEST(Or,BothTrue)
{
        std::string input = "echo hello || echo  world";
        Base* resultat = Parse(input);
        EXPECT_EQ(false, resultat->execute());
}

TEST(Or,FalseTrue)
{
        std::string input = "hello || echo world";
        Base* resultat = Parse(input);
        EXPECT_EQ(true, resultat->execute());
}

TEST(SemiColon,FalseTrue)
{
        std::string input = "hello ; echo world";
        Base* resultat = Parse(input);
        EXPECT_EQ(true, resultat->execute());
}

TEST(SemiColon,BothTrue)
{
        std::string input = "echo hello ; echo world";
        Base* resultat = Parse(input);
        EXPECT_EQ(true, resultat->execute());
}

TEST(SemiColon,BothFalse)
{
        std::string input = "hello ;  world";
        Base* resultat = Parse(input);
        EXPECT_EQ(false, resultat->execute());
}

TEST(SemiColon,TrueFalse)
{
        std::string input = "echo hello ; world";
        Base* resultat = Parse(input);
        EXPECT_EQ(false, resultat->execute());
}

TEST(AllConnectors,True)
{
        std::string input = "echo hello &&  echo world || echo not ok ; echo end";
        Base* resultat = Parse(input);
        EXPECT_EQ(true, resultat->execute());
}

TEST(AllConectors,False)
{
        std::string input = "echo hello &&  echo world ; echo end || echo not ok";
        Base* resultat = Parse(input);
        EXPECT_EQ(false, resultat->execute());
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
