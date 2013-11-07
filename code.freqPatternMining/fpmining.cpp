#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <set>
#include <map>
#include <list>

using namespace std;
#define VOCAB_SIZE 12220
#define PAPER_SIZE 30796

struct pattern {  
    string str;  
    int freq;  
};  

string paper[PAPER_SIZE];
string vocab[ VOCAB_SIZE];

int cmp(pattern a, pattern b)  {  
    return a.freq > b.freq;  
}  
int countPaper(){
	int count=0;
	for(int i = 0; i < PAPER_SIZE; i++){
		if(paper[i]!="")	count++;
	}
	return count;
}
int countLength(string key){
	int count = 0;
	while(1){
		unsigned int next_point = key.find(" ");
		if(next_point != string::npos){ 
			count++;
			key = key.substr(next_point + 1, key.length());
		}
		else {
			break;
		}
	}
	return count+1;
}
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
bool isParentfreq(map<string,int> curr,string key){
	int count = 0;
	for (map<string,int>::iterator it=curr.begin(); it!=curr.end(); ++it){
		if(inTrans(it->first, key) == true) count ++;
	}
	if(countLength(key) == count)
		return true;
	else
		return false;
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
					if(isParentfreq(curr,(string)temp)){
						int freq = countFreq((string)temp);
						if(freq >= threshold) {
							next[temp] = freq;
						}
					}
					multiset.insert((string)temp);
				}
			}
		}
		//cout<<it->first<<":"<<it->second<<endl;
	}
	return next;
}
string retPattern(string str){
	string word;
	char temp[1000] = "";
	unsigned int next_point;
	string key_2;
	while(1){
		next_point = str.find(" ");
		if(next_point != string::npos){ 
			word =  str.substr(0, next_point);
			str = str.substr(next_point + 1, str.length());
			key_2 = vocab[atoi(word.c_str())];
			if((string)temp != ""){
				sprintf(temp, "%s %s", temp, key_2.c_str());
			}
			else{
				sprintf(temp, "%s%s", temp, key_2.c_str());
			}
		//	cout<<temp<<endl;
		}
		else{
			word =  str;
			key_2 = vocab[atoi(word.c_str())];
			if((string)temp != ""){
				sprintf(temp, "%s %s", temp, key_2.c_str());
			}
			else{
				sprintf(temp, "%s%s", temp, key_2.c_str());
			}
			cout<<temp<<endl;
			break;
		}
	}
	return (string)temp;
}
int main(int argc,char *argv[]){
	argc = argc;
	string file_idx = (string)argv[1];
	string file_in = "../topic-"+file_idx+".txt";
	string file_out = "../patterns/pattern-"+file_idx+".txt";
	string line;
	map<string,int> dict;
	map<string,int> curr;
	
	ifstream voc( "../code.preprocessing/generateDict/vocab.txt");
	ifstream fin(file_in.c_str());
	ofstream fout(file_out.c_str());
	
	for(int i = 0; i < VOCAB_SIZE; ++i){
		getline(voc,line, '\n');
		vocab[i] = line;
	}
	cout<<"Finish loading the vocab list"<<endl;
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
				//word = vocab[atoi(word.c_str())]; 
				line =  line.substr(next_point + 1,  line.length());
				std::pair<std::map<string,int>::iterator,bool> ret = dict.insert(pair<string,int>(word,1));
				if(ret.second == false){ dict[word] += 1;}
			}
			else{
				break;
			}
		}
	}
	int threshold = atof(argv[2]) * countPaper();
	cout << "threshold " <<threshold<<endl;
	cout << "Run level 1"<< endl;
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
	cout << "Run level 2"<< endl;
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
			//	cout<<key<<":\t"<<freq<<" > "<<threshold<<" => STAY"<<endl;
			}
			else{
			//	cout<<key<<":\t"<<freq<<" < "<<threshold<<" => OUT"<<endl;
			}
		}
	}
	/*for (map<string,int>::iterator it=curr.begin(); it!=curr.end(); ++it){
		test<<it->first<<":"<<it->second<<endl;
	}*/
	
	//multi iter
	int level = 3;
	while(1){
		cout << "Run level "<<level<< endl;
		map<string,int> sth = composeNext(curr, threshold);
		if(sth.empty()) {
			cout<<"Finish"<<endl;
			break;
		}
		for (map<string,int>::iterator it=sth.begin(); it!=sth.end(); ++it){
			dict[it->first] = it->second;
		}
		curr = sth;
		level ++;
	}
	cout << "Print"<< endl;

	list<pattern> pList; 
	pattern tmp;
	for (map<string,int>::iterator it=dict.begin(); it!=dict.end(); ++it){
        tmp.str = it->first;  
        tmp.freq = it->second;  
        pList.push_back(tmp);  
    }  
	pList.sort(cmp);  
	for (list<pattern>::iterator it=pList.begin(); it!=pList.end(); ++it){
		fout<<it->freq<<" ["<<retPattern(it->str)<<"]"<<endl;
	}
	return 0;
}
