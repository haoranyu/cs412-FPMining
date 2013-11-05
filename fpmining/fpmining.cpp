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

string paper[PAPER_SIZE];
bool inTrans(string aim, string trans){

	set<string> trans_set;
	
	unsigned int next_point;
	string word;
	
	while(1){
		next_point = trans.find(" ");
		if(next_point != string::npos){ 
			word =  trans.substr(0, next_point);
			trans = trans.substr(next_point + 1, trans.length());
			trans_set.insert(word);
		}
		else{
			word =  trans;
			trans_set.insert(word);
			break;
		}
	}

	while(1){
		next_point = aim.find(" ");
		bool flag_in = false;
		if(next_point != string::npos){ 
			word =  aim.substr(0, next_point);
			aim = aim.substr(next_point + 1, aim.length());
			for (set<string>::iterator it=trans_set.begin(); it!=trans_set.end(); ++it){
				if(*it == word){
					flag_in = true;
					break;
				}
			}
			if(flag_in==false) {
				return false;
			}
		}
		else{
			word = aim;
			for (set<string>::iterator it=trans_set.begin(); it!=trans_set.end(); ++it){
				if(*it == word){
					flag_in = true;
					break;
				}
			}
			if(flag_in==false) {
				return false;
			}
			break;
		}
	}
	return true;
}
bool sameKey(string query, string key){
	return (inTrans(query, key) && inTrans(key, query));
}
bool existKey(set<string> multiset, string key){
	for (set<string>::iterator it=multiset.begin(); it!=multiset.end(); ++it){
		if(sameKey(*it, key))	return true;
	}
	return false;
}

int countFreq(string aim){
	int ct = 0;
	for(int i = 0; i < PAPER_SIZE; i++) {
		 if(inTrans(aim, paper[i])){
			ct++;
		 }
	}
	return ct;
}
set<string> map2set(map<string,int> curr){
	set<string> temp;
	for (map<string,int>::iterator it=curr.begin(); it!=curr.end(); ++it){
		string str = it->first;
		unsigned int next_point;
		string word;
		while(1){
			next_point = str.find(" ");
			if(next_point != string::npos){ 
				str = str.substr(next_point + 1, str.length());
				word =  str.substr(0, next_point);
				temp.insert(word);
			}
			else{
				word =  str;
				temp.insert(word);
				break;
			}
		}
	}
	return temp;
}
bool isParentfreq(map<string,int> curr, key){
	
}

map<string,int> composeNext(map<string,int> curr, int threshold){

	set<string> singleset =  map2set(curr);
	set<string> multiset;
	map<string,int> next;
	for (map<string,int>::iterator it=curr.begin(); it!=curr.end(); ++it){
		string key_1 =it->first ;

		for (set<string>::iterator it_in=singleset.begin(); it_in!=singleset.end(); ++it_in){
			string key_2 = *it_in;
			if(!inTrans(key_2, key_1)){
				char temp[100];
				sprintf(temp, "%s %s", key_1.c_str(), key_2.c_str());
				//cout<<existKey(multiset, (string)temp)<<endl;
				if(!existKey(multiset, (string)temp)){
					int freq = countFreq(temp);
					if(freq >= threshold) {
						next[temp] = freq;
					}
					multiset.insert((string)temp);
				}
			}
		}
		//cout<<it->first<<":"<<it->second<<endl;
	}
	return next;
}
int main(int argc,char *argv[]){
	argc = argc;
	int threshold = atof(argv[2]) * PAPER_SIZE;
	string file_idx = (string)argv[1];
	string file_in = "topic-"+file_idx+".txt";
	string file_out = "pattern-"+file_idx+".txt";
	string line;
	map<string,int> dict;
	map<string,int> curr;
	
	ifstream fin(file_in.c_str());
	ofstream fout(file_out.c_str());
	ofstream test("test.txt");
	cout << "threshold " <<threshold <<endl;
	// first iter to count single words
	for(int i = 0; i < PAPER_SIZE; ++i){
		getline(fin,line, '\n');
		paper[i] = line;
		string word;
		unsigned int next_point;
		while(1){
			next_point =  line.find(" ");
			if(next_point != string::npos){ 
				word =  line.substr(0, next_point);
				line =  line.substr(next_point + 1,  line.length());
				std::pair<std::map<string,int>::iterator,bool> ret = dict.insert(pair<string,int>(word,1));
				if(ret.second == false){ dict[word] += 1;}
			}
			else{
				break;
			}
		}
	}
	
	for (map<string,int>::iterator it=dict.begin(); it!=dict.end();){
		if(it->first == "" || (it->second) < threshold) {
			map<string,int>::iterator temp = it++;
			dict.erase (temp);
		}
		else{
			++it;  
		}
	}
	
	
	// second iter to count single words
	for (map<string,int>::iterator it=dict.begin(); it!=dict.end();){
		string key_1 = it->first;
		for (map<string,int>::iterator it_2 = ++it; it_2 != dict.end(); it_2++){
			string key_2 = it_2->first;	
			char key[50];
			sprintf(key, "%s %s", key_1.c_str(), key_2.c_str());
			int freq = countFreq(key);
			if(freq >= threshold) {
				dict[key] = freq;
				curr[key] = freq;
			}
		}
	}
	/*for (map<string,int>::iterator it=curr.begin(); it!=curr.end(); ++it){
		test<<it->first<<":"<<it->second<<endl;
	}*/
	
	//multi iter
	map<string,int> sth = composeNext(curr, threshold);
	for (map<string,int>::iterator it=sth.begin(); it!=sth.end(); ++it){
		test<<it->first<<":"<<it->second<<endl;
	}

	return 0;
}
