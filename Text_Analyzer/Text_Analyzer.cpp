#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include <iostream>

std::vector<std::string> read_file(std::ifstream& );//X
std::pair<std::string,int> word_analyzer (std::vector<std::string>& );//X
std::pair<char,int> letter_analyzer (std::vector<std::string>& );//X
int find_count_of_sentences(std::ifstream& );//X
int find_count_of_words(std::vector<std::string>& );//X
int find_count_of_letters(std::vector<std::string>&, std::map<char,int>&);//X
std::string often_identified_word(std::vector<std::string>&);//X
char often_identified_letter (std::map<char,int>&);//X
void reset_cursor (std::ifstream& , std::string& path);//X
void print_info(std::pair<std::string,int> , std::pair<char,int>, int );
void store_text_info (std::pair<std::string,int> , std::pair<char,int>, int , std::string);

int main(){
    std::ifstream fin_text;
    std::string path;
    std::cout << "Plese input only name (don't input .txt) of file. Its must be located in same folder where was created our C++ file " << std::endl; 
    std::cin >> path;
    fin_text.open(path + ".txt");
    int sent_count = find_count_of_sentences(fin_text);
    reset_cursor(fin_text, path);
    std::vector<std::string> all_words(read_file(fin_text)); 
    std::pair<std::string,int> word_info = word_analyzer(all_words);
    std::pair<char,int> letter_info = letter_analyzer(all_words);
    print_info(word_info,letter_info,sent_count);
    store_text_info(word_info,letter_info,sent_count,path);

    fin_text.close();
    return 0;
}

int find_count_of_sentences(std::ifstream& fin){
    std::string str;
    int count = 0;
    while(getline(fin,str)){
        count ++;
        for (int i = str.find('.',0); i != -1; i = str.find('.',i+1))
        {
            if ( i+1 < str.size() && str[i+1] == ' ' ){
                count++;
            }else if (i+1 < str.size() && str[i+1] != ' ' ){ 
                continue;
            }
        }
    }
    return count;
}

void reset_cursor(std::ifstream& fin , std::string& path){
    fin.close();
    fin.open(path+".txt");
}

std::vector<std::string> read_file (std::ifstream& fin){
    std::vector<std::string> words ;
    while(!fin.eof()){
        std::string tmp = "";
        fin >> tmp ;
        words.push_back(tmp);
    }   
    return words;
}

int find_count_of_words(std::vector<std::string>& words){
    return words.size();
}

std::string often_identified_word(std::vector<std::string>& words){
    std::map <std::string, int> word_count;
    for(int i = 0 ; i< words.size();i++){
        word_count[words[i]]++;
    }
    int max = 1;
    for(std::map<std::string,int>::iterator it = word_count.begin(); it != word_count.end();it++){
        if(max < it->second){
            max = it->second;
        }
    }
    std::string max_word="";
    if(max==1){
        return max_word;
    }
    for (std::map<std::string,int>::iterator it = word_count.begin(); it != word_count.end();it++)
    {
        if (it->second == max )
        {
            max_word = it->first;
        }
    }
    return max_word;
}

std::pair<std::string,int> word_analyzer (std::vector<std::string>& words){
    std::pair<std::string,int> tmp;
    int word_count = find_count_of_words(words);
    std::string reap_word = often_identified_word(words);
    tmp = make_pair(reap_word,word_count);
    return tmp;
}

std::pair<char,int> letter_analyzer (std::vector<std::string>& words){
    
    std::map<char,int> letters_count;
    int letter_count = find_count_of_letters(words,letters_count);
    char reap_letter = often_identified_letter(letters_count);
    std::pair<char,int> tmp(reap_letter,letter_count);
    return tmp;
}


int find_count_of_letters(std::vector<std::string>& words, std::map<char,int>& letters){
    for(int i = 0 ; i < words.size();i++){
        for (int j = 0; j < words[i].size(); j++)
        {
            if((words[i][j] >= 'A' && words[i][j] <= 'Z') || (words[i][j] >= 'a' && words[i][j] <= 'z') ){
                letters[words[i][j]]++;
            }
        }
    }
    int letters_count=0;
    for (std::map<char,int>::iterator it = letters.begin(); it != letters.end();it++)
    {
        letters_count += it->second;
    }
    return letters_count;
}

char often_identified_letter(std::map<char,int>& letter){
    int max = 0;
    for(std::map<char,int>::iterator it = letter.begin(); it != letter.end();it++){
        if(max < it->second){
            max = it->second;
        }
    }
    char max_letter = '\0';
    if(max==1){
        return max_letter;
    }
    for (std::map<char,int>::iterator it = letter.begin(); it != letter.end();it++)
    {
        if (it->second == max )
        {
            max_letter = it->first;
        }
    }
    return max_letter;
}


void print_info(std::pair<std::string,int> word_info, std::pair<char,int> letter_info, int sentence_count){
    std::cout << "All information about this text. " << std::endl;
    std::cout << "Sentances Count is: " << sentence_count << std::endl;
    std::cout << "Words Count is: " << word_info.second << std::endl;
    std::cout << "Letters Count is: " << letter_info.second << std::endl;
    std::cout << "Most Repeated Word is: " << word_info.first << std::endl;
    std::cout << "Most Repeated letter is: " << letter_info.first << std::endl;
}

void store_text_info (std::pair<std::string,int> word_info, std::pair<char,int> letter_info, int sentence_count , std::string path){
    std::ofstream fout ;
    fout.open(path+ "_info.txt");
    fout << "All information about this text. " << std::endl;
    fout << "Sentances Count is: " << sentence_count << std::endl;
    fout << "Words Count is: " << word_info.second << std::endl;
    fout << "Letters Count is: " << letter_info.second << std::endl;
    fout << "Most Repeated Word is: " << word_info.first << std::endl;
    fout << "Most Repeated letter is: " << letter_info.first << std::endl;
    fout.close();
}