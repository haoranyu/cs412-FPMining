#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <set>
#include <vector>
#include <map>
#include <cmath>
#include <list>
#include <algorithm> 

using namespace std;
#define MAX_SIZE 999999

struct pattern {  
    string str; 
	int freq;
    double purity;  
};  

int cmp(pattern a, pattern b)  {  
    if(a.purity > b.purity){
		return true;
	}	
	else if(a.purity == b.purity){
		if(a.freq > b.freq)
				return true;
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
vector<string> unionSet(vector<string> v1, vector<string> v2){
	vector<string> ret(50000);
	vector<string>::iterator retEndPos;
	retEndPos = set_union (v1.begin(), v1.end(), v2.begin(), v2.end(), ret.begin());
	ret.resize( retEndPos - ret.begin() ) ;
	return ret;
}
int main(int argc,char *argv[]){
	argc = argc;
	string file_idx = (string)argv[1];
	string file_out = "../purity/purity-"+file_idx+".txt";
	string line;
	map<string,int> topic0; 	map<string,int> topic1; 	map<string,int> topic2; 	map<string,int> topic3; 	map<string,int> topic4;
	map<string,int> topic_curr;
	map<string,double> topic_curr_pure;
	vector<string> t0; 	vector<string> t1; 	vector<string> t2; 	vector<string> t3;	vector<string> t4;
	
	ifstream ptn0("../patterns/pattern-0.txt");
	ifstream ptn1("../patterns/pattern-1.txt");
	ifstream ptn2("../patterns/pattern-2.txt");
	ifstream ptn3("../patterns/pattern-3.txt");
	ifstream ptn4("../patterns/pattern-4.txt");
	ifstream tpc0("../topic-0.txt");
	ifstream tpc1("../topic-1.txt");
	ifstream tpc2("../topic-2.txt");
	ifstream tpc3("../topic-3.txt");
	ifstream tpc4("../topic-4.txt");
	ofstream fout(file_out.c_str());

	while(getline(ptn0,line, '\n')){
		topic0[getPattern(line)] = getCount(line);
		if(atoi(file_idx.c_str()) == 0){
			topic_curr[getPattern(line)] = getCount(line);
		}
	}
	while(getline(ptn1,line, '\n')){
		topic1[getPattern(line)] = getCount(line);
		if(atoi(file_idx.c_str()) == 1){
			topic_curr[getPattern(line)] = getCount(line);
		}
	}
	while(getline(ptn2,line, '\n')){
		topic2[getPattern(line)] = getCount(line);
		if(atoi(file_idx.c_str()) == 2){
			topic_curr[getPattern(line)] = getCount(line);
		}
	}
	while(getline(ptn3,line, '\n')){
		topic3[getPattern(line)] = getCount(line);
		if(atoi(file_idx.c_str()) == 3){
			topic_curr[getPattern(line)] = getCount(line);
		}
	}
	while(getline(ptn4,line, '\n')){
		topic4[getPattern(line)] = getCount(line);
		if(atoi(file_idx.c_str()) == 4){
			topic_curr[getPattern(line)] = getCount(line);
		}
	}
	cout<<"Finish Load patterns"<<endl;
	while(getline(tpc0,line, '\n')){
		if(line!="")	t0.push_back(line);
	}
	while(getline(tpc1,line, '\n')){
		if(line!="")	t1.push_back(line);
	}
	while(getline(tpc2,line, '\n')){
		if(line!="")	t2.push_back(line);
	}
	while(getline(tpc3,line, '\n')){
		if(line!="")	t3.push_back(line);
	}
	while(getline(tpc4,line, '\n')){
		if(line!="")	t4.push_back(line);
	}
	cout<<"Finish count rows"<<endl;
	cout<<"> D(t0) have "<<t0.size()<<" rows"<<endl;
	cout<<"> D(t1) have "<<t1.size()<<" rows"<<endl;
	cout<<"> D(t2) have "<<t2.size()<<" rows"<<endl;
	cout<<"> D(t3) have "<<t3.size()<<" rows"<<endl;
	cout<<"> D(t4) have "<<t4.size()<<" rows"<<endl;
	

	double Dt;
	double Dtt[5];

	if(atoi(file_idx.c_str()) == 0){
		Dt =  (double)t0.size();
		Dtt[1] = (double)(unionSet(t0,t1).size());
		Dtt[2] = (double)(unionSet(t0,t2).size());
		Dtt[3] = (double)(unionSet(t0,t3).size());
		Dtt[4] = (double)(unionSet(t0,t4).size());
	}
	else if(atoi(file_idx.c_str()) == 1){
		Dt =  (double)t1.size();
		Dtt[0] = (double)(unionSet(t1,t0).size());
		Dtt[2] = (double)(unionSet(t1,t2).size());
		Dtt[3] = (double)(unionSet(t1,t3).size());
		Dtt[4] = (double)(unionSet(t1,t4).size());
	}
	else if(atoi(file_idx.c_str()) == 2){
		Dt =  (double)t2.size();
		Dtt[0] = (double)(unionSet(t2,t0).size());
		Dtt[1] = (double)(unionSet(t2,t1).size());
		Dtt[3] = (double)(unionSet(t2,t3).size());
		Dtt[4] = (double)(unionSet(t2,t4).size());
	}
	else if(atoi(file_idx.c_str()) == 3){
		Dt =  (double)t3.size();
		Dtt[0] = (double)(unionSet(t3,t0).size());
		Dtt[1] = (double)(unionSet(t3,t1).size());
		Dtt[2] = (double)(unionSet(t3,t2).size());
		Dtt[4] = (double)(unionSet(t3,t4).size());
	}
	else if(atoi(file_idx.c_str()) == 4){
		Dt =  (double)t4.size();
		Dtt[0] = (double)(unionSet(t4,t0).size());
		Dtt[1] = (double)(unionSet(t4,t1).size());
		Dtt[2] = (double)(unionSet(t4,t2).size());
		Dtt[3] = (double)(unionSet(t4,t3).size());
	}



	for (map<string,int>::iterator it=topic_curr.begin(); it!=topic_curr.end(); it++){
		double purity_part1 = log( ((double)(it->second)) / Dt);
		double purity_part2_max = -999999.0;
		for(int i = 0; i < 5; i++){
			if(atoi(file_idx.c_str()) != i){
				float other_freq;
				map<string,int>::iterator other_find;
				if(i == 0){
					other_find = topic0.find(it->first);
					if(other_find!=topic0.end()){
						other_freq = other_find->second;
					}
					else{
						other_freq  = 0;
					}
				}
				else if(i == 1){
					other_find = topic1.find(it->first);
					if(other_find!=topic1.end()){
						other_freq = other_find->second;
					}
					else{
						other_freq  = 0;
					}
				}
				else if(i == 2){
					other_find = topic2.find(it->first);
					if(other_find!=topic2.end()){
						other_freq = other_find->second;
					}
					else{
						other_freq  = 0;
					}
				}
				else if(i == 3){
					other_find = topic3.find(it->first);
					if(other_find!=topic3.end()){
						other_freq = other_find->second;
					}
					else{
						other_freq  = 0;
					}
				}
				else if(i == 4){
					other_find = topic4.find(it->first);
					if(other_find!=topic4.end()){
						other_freq = other_find->second;
					}
					else{
						other_freq  = 0;
					}
				}
				double temp = ((double)(it->second + other_freq) / Dtt[i]);
				if(purity_part2_max < temp)
						purity_part2_max = temp;
			}
		}
		double purity_part2 = log(purity_part2_max);
		topic_curr_pure[it->first] = purity_part1 - purity_part2;

	}
	cout<<"Finish calcuate purity"<<endl;

	list<pattern> pList; 
	pattern tmp;
	for (map<string,double>::iterator it=topic_curr_pure.begin(); it!=topic_curr_pure.end(); ++it){
        tmp.str = it->first;  
        tmp.purity = it->second; 
		map<string,int>::iterator queryit;
		queryit = topic_curr.find(it->first);
		tmp.freq = queryit->second;
        pList.push_back(tmp);  
    }  
	pList.sort(cmp);  
	for (list<pattern>::iterator it=pList.begin(); it!=pList.end(); ++it){
		fout<<it->purity<<" ["<<it->str<<"]"<<endl;
	}	
	cout<<"Finish output"<<endl;
}
