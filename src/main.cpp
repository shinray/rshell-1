#include <iostream>
#include <string>
#include <alloca.h>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <vector>
//#include <src/main.h>
using namespace std;
//.h doesn't work, so delaration here for the moment
string CleanString(string);
vector<string> Split(string);

int main(int argc, char ** argv){
//cout<<"EXXXXTERMINATEEE! --- love, a lonely DALEK"<<endl;
string in;
vector<string> arg;
bool hashtag = false;
while (in !="quit"){
    cout<<"$ ";
    std::getline(cin,in);
    arg=Split(in);
    //conversion zone
    char * argFinal[arg.size()];
    for(int i=0; i<arg.size();i++){
    //	if(arg[i][0] == '#')
    //	{
    //		string argBis = "echo "+arg[i]; 
    //		argFinal[i] =(char *)argBis.c_str();// we add the echo 
    //	}
    //	else{
            argFinal[i] = (char*)arg[i].c_str();
      //  }
    }
    argFinal[arg.size()]=NULL; //last arg must be null
    int pid = fork(); // for the process to be able to do the execvp 
    if(pid ==1){
        perror("fork failed");//if the fork failed
    }
    else if(pid==0){
    	//child process
        if(execvp(argFinal[0],argFinal) !=0 && in != "quit"){
        	perror("error in execvp");
        }
        else if(in =="quit")
        {
            exit(0);//quit the process if quit is typed
        }
    }
    else{
    //parent process
    wait(NULL);//wait till the child is finished
    }
}
return 0;
}

vector<string> Split(string input){
input.push_back(' ');//to be able to go in the if for the end of the text
vector <string> arg;
char currentChar;
string splitedPiece;
bool testHashtag = false;
for(string::iterator it = input.begin(); it != input.end();++it)
{
    currentChar =*it;
    if(currentChar==' '&&splitedPiece.size()>1 )//if the it arrives to a space and the size of the piece of string if greater than 2 char
    {
        arg.push_back(splitedPiece);//add this piece of text to the vector
       // cout<<splitedPiece<<endl;
        splitedPiece.clear();//clean the piece to do another one to fill it again
    }
    if(currentChar==' ' && splitedPiece.size() <= 1&& it != input.end()-1)
    {
    	//cout<<"space here that we want removed"<<endl;
        //if there is a lonely space
        // we go into that if so we dont go into the else, so the space is not taken in the arg, so this is what I want. I'm sad to let an if empty.
    }
    /*else if(currentChar ='#'){
        testHashtag = true;
    }*/
   /* else if(testHashtag && it == input.end())//if we are at the end of the string, afte #
    {
    	arg.push_back(" echo "); 
        arg.push_back(splitedPiece);
    }*/
    else{
        splitedPiece.push_back(*it);//add the current char to the plited piece of tex to make an arg, between two spaces => it s an arg we are filling
    }
}

return arg;
}

string CleanString(string input){
string finalInput = new char[input.size()];
finalInput = input;
finalInput.erase(remove(finalInput.begin(),finalInput.end(),' '),finalInput.end());
return finalInput;
//remove the " of the input, avoiding injections
}