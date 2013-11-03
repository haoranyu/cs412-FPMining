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

string volist[VOCAB_SIZE];

char * getTitle(string line){
	char *temp = (char *)line.c_str();
    char *arr;
    arr = strtok(temp, "\t");
    arr = strtok(NULL, "\t");
	return arr;
}
int getWordidx(string word){
	int left, right, middle;
    left = 0, right = VOCAB_SIZE;
    while (left < right){
        middle = (left + right) / 2;
        if (volist[middle] > word){
            right = middle;
        }
        else if (volist[middle] < word){
            left = middle + 1;
        }
        else{
            return middle;
        }
    }
	return -1;
}

int main(){
	ifstream paper("paper.txt");
	ifstream vocab("vocab.txt");
	freopen("title.txt","w",stdout);
	string line[PAPER_SIZE];
	char * title[PAPER_SIZE];
	set<string> s[PAPER_SIZE];
	for(int i = 0; i < PAPER_SIZE; ++i){
		getline(paper,line[i],'\n');
		title[i] = getTitle(line[i]);
		if(i<VOCAB_SIZE){
		getline(vocab,volist[i],'\n');
		}
	}
	for(int i=0;i<PAPER_SIZE;++i){
		int wordcounter[VOCAB_SIZE];
		for(int j = 0; j < VOCAB_SIZE; ++j){
			wordcounter[j] = 0;
		}
		char * word = strtok(title[i], " ");
		while(word != NULL){
			s[i].insert((string)word);
			wordcounter[getWordidx((string)word)]++;
			word = strtok(NULL, " ");
		}
		cout<<s[i].size();
		for(int j = 0; j < VOCAB_SIZE; ++j){
			if(wordcounter[j] != 0){
				cout<<" "<<j<<":"<<wordcounter[j];
			}
		}
		cout<<endl;
	}
}
