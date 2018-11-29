#include "../src/base.h"
#include "../src/parser.h"
#include "../src/command.cpp"
#include "../src/connector.cpp"
#include "../src/and.cpp"
#include "../src/or.cpp"
#include "../src/semiColon.cpp"
#include "../src/testCommand.cpp"
#include "../src/parenthesis.cpp"
#include <algorithm>
#include "gtest/gtest.h"

TEST(Parser,SingleCommand)
{
  	std::string input = "echo hello";
  	std::ostringstream oss;
	std::streambuf* p_cout_streambuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());
	
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#()");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
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

       typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#()");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
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

        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#()");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
        result->print_args();

        std::cout.rdbuf(p_cout_streambuf);

        assert(oss && oss.str() == "echo hello");
        std::cout << oss.str();
}

TEST(SingleCommand,True)
{
	std::string input = "echo hello world";
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#()");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
	EXPECT_EQ(true, result->execute());
}

TEST(SingleCommand,False)
{
        std::string input = "hello world";
	
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> delimiters(" ","&|;#()");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
	EXPECT_EQ(false, result->execute());
}


TEST(And,BothTrue)
{
	std::string input = "echo hello && echo world";
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#()");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
	EXPECT_EQ(true, result->execute());
}

TEST(And,BothFalse)
{
        std::string input = "hello && world";
       typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#()");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
        EXPECT_EQ(false, result->execute());
}

TEST(And,TrueFalse)
{
        std::string input = "echo hello && world";
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#()");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
        EXPECT_EQ(false, result->execute());
}
TEST(And,FalseTrue)
{
        std::string input = "hello && echo world";
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#()");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
        EXPECT_EQ(false, result->execute());
}

TEST(Or,BothFalse)
{
        std::string input = "hello || world";
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#()");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
        EXPECT_EQ(false, result->execute());
}
TEST(Or,BothTrue)
{
        std::string input = "echo hello || echo  world";
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#()");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
        EXPECT_EQ(true, result->execute());
}

TEST(Or,FalseTrue)
{
        std::string input = "hello || echo world";
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#()");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
	EXPECT_EQ(true, result->execute());
}

TEST(SemiColon,FalseTrue)
{
        std::string input = "hello ; echo world";
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#()");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
        EXPECT_EQ(true, result->execute());
}

TEST(SemiColon,BothTrue)
{
        std::string input = "echo hello ; echo world";
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#()");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
        EXPECT_EQ(true, result->execute());
}

TEST(SemiColon,BothFalse)
{
        std::string input = "hello ;  world";
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#()");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
        EXPECT_EQ(false, result->execute());
}

TEST(SemiColon,TrueFalse)
{
        std::string input = "echo hello ; world";
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#()");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
        EXPECT_EQ(false, result->execute());
}

TEST(AllConnectors,True)
{
        std::string input = "echo hello &&  echo world || echo not ok ; echo end";
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#()");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
        EXPECT_EQ(true, result->execute());
}
TEST(TestCommand,Flag_e){
	
	std::string input = "test -e ./src/main.cpp";
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#()[]");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
        EXPECT_EQ(true, result->execute());
}

TEST(TestCommand,Flag_d){
	
	std::string input = "test -d ./src";
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#()[]");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
        EXPECT_EQ(true, result->execute());
}
TEST(TestCommand,Flag_f){
	
	std::string input = "test -f ./src/main.cpp";
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#()[]");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
        EXPECT_EQ(true, result->execute());
}
TEST(TestCommand, No_Flag){
	
	std::string input = "test ./src/main.cpp";
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#()[]");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
        EXPECT_EQ(true, result->execute());
}

TEST(TestCommand,Symbolic_version){
	
	std::string input = "[-e ./src/main.cpp]";
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#()[]");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
        EXPECT_EQ(true, result->execute());
}

TEST(Parenthesis,simpleCommand){
	
	std::string input = "(echo A && echo B) || (echo C && echo D)";
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	
	boost::char_separator<char> delimiters(" ","&|;#()[]");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
	
	EXPECT_EQ(true, result->execute());
	
}

TEST(Parenthesis,multiple_parenthesis){
	
	std::string input = "((echo A && echo B) || (echo C && echo D)) && echo C";
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	
	boost::char_separator<char> delimiters(" ","&|;#()[]");	 
	tokenizer tokens(input,delimiters);
	Base * result = Parse(tokens,tokens.begin(),false);
	EXPECT_EQ(true, result->execute());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
