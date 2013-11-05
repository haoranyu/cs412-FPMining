#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cstring>
#include<set>
using namespace std;

char * getTitle(string line){
	char *temp = (char *)line.c_str();
    char *arr;
    arr = strtok(temp, "\t");
    arr = strtok(NULL, "\t");
	return arr;
}

int main(){
    freopen("paper.txt","r",stdin);
	freopen("vocab.txt","w",stdout);
    string line;
	char * title;
	set<string> s;
	while(getline(cin,line)){
		title = getTitle(line);
		char * word = strtok(title, " ");
		while(word != NULL){
			s.insert((string)word);
			word = strtok(NULL, " ");
		}
	}
	for(set<string>::const_iterator i = s.begin(); i != s.end(); ++i){
		cout << *i << '\n';
	}
    return 0;
}
