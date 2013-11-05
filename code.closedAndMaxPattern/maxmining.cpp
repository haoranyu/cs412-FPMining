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
#define MAX_SIZE 999999

struct pattern {  
    string str;  
    int freq;  
};  

int cmp(pattern a, pattern b)  {  
    return a.freq > b.freq;  
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
bool hasMaxParent(map<string,int> dict, map<string,int>::iterator aim){
	for (map<string,int>::iterator it=dict.begin(); it!=dict.end(); it++){
		if(inTrans(aim->first, it->first) && (aim->first != it->first)){
			return true;
		}
	}
	return false;
}

string getPattern(string line){
	unsigned int left = line.find("[") +1;
	unsigned int right = line.find("]");
	return  line.substr(left, right-left);
}
int getCount(string line){
	unsigned int left = line.find(" ") ;
	return  atoi(line.substr(0, left).c_str());
}
int main(int argc,char *argv[]){
	argc = argc;
	string file_idx = (string)argv[1];
	string file_in = "pattern-"+file_idx+".txt";
	string file_out = "max-"+file_idx+".txt";
	string line;
	map<string,int> dict;

	ifstream fin(file_in.c_str());
	ofstream fout(file_out.c_str());

	while(getline(fin,line, '\n')){
		dict[getPattern(line)] = getCount(line);
	}
	for (map<string,int>::iterator it=dict.begin(); it!=dict.end();){
			if(hasMaxParent(dict, it)){
				map<string,int>::iterator temp = it++;
				dict.erase (temp);
				cout<<"reduce one pattern"<<endl;
			}
			else	{
				++it;
			}
	}
	list<pattern> pList; 
	pattern tmp;
	for (map<string,int>::iterator it=dict.begin(); it!=dict.end(); ++it){
        tmp.str = it->first;  
        tmp.freq = it->second;  
        pList.push_back(tmp);  
    }  
	pList.sort(cmp);  
	for (list<pattern>::iterator it=pList.begin(); it!=pList.end(); ++it){
		fout<<it->freq<<" ["<<it->str<<"]"<<endl;
	}
}
