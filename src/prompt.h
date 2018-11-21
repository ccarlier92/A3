#include <unistd.h>
#include <stdio.h>
#include <string.h>
void prompt()
{
	 char userName[50] = "";
         char userInfos[100] = "";
         strcat(userInfos,"[rshell ");
         strcat(userInfos,getlogin());
         strcat(userInfos,"@");
         gethostname(userName,50);
         strcat(userInfos,userName);
         strcat(userInfos,"]");
         std::string str(userInfos);
         std::cout<<str<<"$ ";
}
