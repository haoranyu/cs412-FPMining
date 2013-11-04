#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <set>
#include <map>

using namespace std;
#define VOCAB_SIZE 12220
#define PAPER_SIZE 30796
int main(int argc,char *argv[]){
	argc = argc;
	int threshold = atof(argv[2]) * PAPER_SIZE;
	string file_idx = (string)argv[1];
	string file_in = "topic-"+file_idx+".txt";
	string file_out = "pattern-"+file_idx+".txt";
	string line;
	map<string,int> map_1;
	
	ifstream fin(file_in.c_str());
	ofstream fout(file_out.c_str());
	ofstream test("test.txt");
	cout << "threshold" <<threshold <<endl;
	// first iter to count single words
	for(int i = 0; i < PAPER_SIZE; ++i){
		getline(fin,line, '\n');
		char * line_c = (char *)(line.c_str());
		char * word = strsep(&line_c, " ");
		
		while(word != NULL){
			std::pair<std::map<string,int>::iterator,bool> ret = map_1.insert(pair<string,int>(((string)word),1));
			if(ret.second == false){
				map_1[(string)word] += 1;
			}
			word = strsep(&line_c, " ");
		}
	}
	
	for (map<string,int>::iterator it=map_1.begin(); it!=map_1.end();){
		if(it->first == "" || (it->second) < threshold) {
			map<string,int>::iterator temp = it++;
			map_1.erase (temp);
		}
		else{
			++it;  
		}
	}

	for (map<string,int>::iterator it=map_1.begin(); it!=map_1.end(); ++it){
		fout<<it->first<<":"<<it->second<<endl;
	}

	return 0;
}
