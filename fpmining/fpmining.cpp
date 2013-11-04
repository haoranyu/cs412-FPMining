#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <set>
using namespace std;
#define VOCAB_SIZE 12220
#define PAPER_SIZE 30796
int main(int argc,char *argv[]){
	argc = argc;
	string file_idx = (string)argv[1];
	string file_in = "topic-"+file_idx+".txt";
	string file_out = "pattern-"+file_idx+".txt";
	string line;
	int set_1[VOCAB_SIZE];
	for(int i = 0; i < VOCAB_SIZE; i++){
		set_1[i] = 0;
	}

	ifstream fin(file_in.c_str());
	ofstream fout(file_out.c_str());

	for(int i = 0; i < PAPER_SIZE; ++i){
		getline(fin,line, '\n');
		char * line_c = (char *)(line.c_str());
		char * word = strsep(&line_c, " ");
		cout << word;
		while(word != NULL){
			set_1[atoi(word)]++;
			word = strsep(&line_c, " ");
		}
	}
	
	for(int i = 0; i < VOCAB_SIZE; i++){
		fout<<set_1[i]<<endl;
	}
	return 0;
}
