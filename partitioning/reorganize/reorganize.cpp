#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <set>
using namespace std;

#define PAPER_SIZE 30796
int main(){
	ifstream paper("word-assignments.dat");
	ofstream tpc0("topic-0.txt");
	ofstream tpc1("topic-1.txt");
	ofstream tpc2("topic-2.txt");
	ofstream tpc3("topic-3.txt");
	ofstream tpc4("topic-4.txt");

	string line;
    for(int i = 0; i < PAPER_SIZE; ++i){
		getline(paper,line, '\n');
		char * line_c = (char *)(line.c_str());
		char * word = strsep(&line_c, " ");
		while(word != NULL){
			if(strstr(word,":00")){
				char * term =  strsep(&word, ":");
				tpc0<<term<<" ";
			}
			else if(strstr(word,":01")){
				char * term =  strsep(&word, ":");
				tpc1<<term<<" ";
			}
			else if(strstr(word,":02")){
				char * term = strsep(&word, ":");
				tpc2<<term<<" ";
			}
			else if(strstr(word,":03")){
				char * term = strsep(&word, ":");
				tpc3<<term<<" ";
			}
			else if(strstr(word,":04")){
				char * term =  strsep(&word, ":");
				tpc4<<term<<" ";
			}
			word = strsep(&line_c, " ");
		}
		tpc0<<endl;
		tpc1<<endl;
		tpc2<<endl;
		tpc3<<endl;
		tpc4<<endl;
		cout<<"Finish the #"<<i<<" line."<<endl;
	}
	
}
