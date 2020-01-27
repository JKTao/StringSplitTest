#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <vector>
#include <regex>
#include <chrono>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <tic_toc.h>
using namespace std;

bool start_with(const char *str, const char *pattern){
    int i = 0;
    while(str[i] == pattern[i] && str[i] != '\0'){
        i++;
    }
    return (pattern[i] == '\0');
}


vector<string> split_line_into_tokens1(const string & line, const string & delimiter){
    TicToc timer;
    regex delimiter_regex(delimiter);
    sregex_token_iterator begin_(line.begin(), line.end(), delimiter_regex, -1), end_;
    vector<string> tokens(begin_, end_);
    cout << "Tokenize with regex cost " << timer.toc() << " ms" << endl;
    return tokens;
}

vector<string> split_line_into_tokens2(const string & line, const string & delimiter){
    TicToc timer;
    vector<string> tokens;
    string token;
    istringstream line_string(line);
    while((getline(line_string, token, ' '))){
        tokens.emplace_back(token);
    }
    cout << "Tokenize with stream getline cost " << timer.toc() << " ms" << endl;
    return tokens;
}
 
vector<string> split_line_into_tokens3(const std::string& str, const std::string & delimiter)
{
    TicToc timer;
    std::size_t current, previous = 0;
    vector<string> tokens;
    current = str.find_first_of(delimiter);
    while (current != std::string::npos) {
        tokens.emplace_back(str.substr(previous, current - previous));
        str.substr(previous, current - previous);
        previous = current + 1;
        current = str.find_first_of(delimiter, previous);
    }
    tokens.emplace_back(str.substr(previous, current - previous));
    cout << "Tokenize with string find_first_of cost " << timer.toc() << " ms" << endl;
    return tokens;
}

vector<string> split_line_into_tokens4(const std::string& str, const std::string & delimiter)
{
    TicToc timer;
    vector<string> tokens;
    boost::split(tokens, str, boost::is_any_of("\n "));
    cout << "Tokenize with boost split cost " << timer.toc() << " ms" << endl;
    return tokens;
}




vector<string> split_line_into_tokens5(const std::string& str, const std::string & delimiter)
{
    TicToc timer;
    vector<string> tokens_;
    typedef boost::char_separator<char> separator;
    boost::tokenizer<separator> tokens(str, separator(delimiter.c_str()));
    std::copy(tokens.begin(), tokens.end(), std::back_inserter(tokens_)); 
    cout << "Tokenize with boost tokenizer cost " << timer.toc() << " ms" << endl;
    return tokens_;
}

double check_result(const string &file_content, function<vector<string>(const string & line, const string &delimiter)> func){
    vector<string> tokens = func(file_content, " ");
    cout << tokens.size() << endl;
    //cout << tokens[100] << " " << tokens[200] << endl;
}


int split_line_into_tokens6(const char* str, char delim, int *starts, int *lengths) {
    TicToc timer;
    const char *p = str;
    unsigned char newstr = 1;
    int tokens_number = 0;
    while (*p != '\0') {
        if (newstr) {
            newstr = 0;
            starts[tokens_number] = p - str;
        }
        if (*p == delim || *p == '\0') {
            newstr = 1;
            lengths[tokens_number] = p - str - starts[tokens_number];
            ++tokens_number;
        }
        ++p;
    }
    cout << "Tokenize with C split cost " << timer.toc() << " ms" << endl;
    return tokens_number;
}

void printstring(const char *str, int len) {
    const char *p = str;
    while (len--) {
        putchar(*p++);
    }
    putchar('\n');
}

int main(){
    cout << ">>>> test for starts with" << endl;
    cout << "expected 1, " << start_with("hello", "hello world") << endl;
    cout << "expected 0, " << start_with("hello", "h") << endl;
    cout << "expected 1, " << start_with("hello world", "hello world") << endl;
    cout << ">>>> " << endl;

    cout << ">>>> test for string split test" << endl;
    vector<string> tokens;
    ifstream tokens_file("tokens.txt");

    stringstream sstr;
    sstr << tokens_file.rdbuf();
    string file_content = sstr.str();

    int *starts = (int*) malloc(sizeof(int) * 30000000);
    int *lengths = (int*) malloc(sizeof(int) * 30000000);

    check_result(file_content, split_line_into_tokens1);
    check_result(file_content, split_line_into_tokens2);
    check_result(file_content, split_line_into_tokens3);
    check_result(file_content, split_line_into_tokens4);
    check_result(file_content, split_line_into_tokens5);


    int tokens_number = split_line_into_tokens6(file_content.c_str(), ' ', starts, lengths);
    cout << tokens_number << endl;
    // int v1, v2, v3;
    // char buffer[100] = "f 9//3 4 3//3";
    // sscanf(buffer, "f %d%*[ ]%d%*[ ]%d", &v1, &v2, &v3);
    // printf("%d %d %d", v1, v2, v3);
    free(starts);
    free(lengths);
    return 0;
}
    


