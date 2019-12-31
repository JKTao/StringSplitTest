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
using namespace std;

bool start_with(const char *str, const char *pattern){
    int i = 0;
    while(str[i] == pattern[i] && str[i] != '\0'){
        i++;
    }
    return (pattern[i] == '\0');
}


vector<string> split_line_into_tokens1(const string & line, const string & delimiter){
    regex deli(delimiter);
    sregex_token_iterator terminal;
    vector<string> tokens(sregex_token_iterator(line.begin(), line.end(), deli, -1), sregex_token_iterator());
    return tokens;
}

vector<string> split_line_into_tokens2(const string & line, const string & delimiter){
    vector<string> tokens;
    string token;
    istringstream line_string(line);
    int i = 0;
    while((getline(line_string, token, ' '))){
        tokens.emplace_back(token);
        if(i == 2)
            cout << token << "FUCK";
        i++;
    }
    return tokens;
}
 
vector<string> split_line_into_tokens3(const std::string& str, const std::string & delimiter)
{
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
    return tokens;
}

vector<string> split_line_into_tokens4(const std::string& str, const std::string & delimiter)
{
    vector<string> tokens;
    boost::split(tokens, str, boost::is_any_of("\n "));
    return tokens;
}




vector<string> split_line_into_tokens5(const std::string& str, const std::string & delimiter)
{
    vector<string> tokens_;
    typedef boost::char_separator<char> separator;
    boost::tokenizer<separator> tokens(str, separator(delimiter.c_str()));
    std::copy(tokens.begin(), tokens.end(), std::back_inserter(tokens_)); 
    return tokens_;
}

double time_used(const string &file_content, function<vector<string>(const string & line, const string &delimiter)> func){
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    vector<string> tokens = func(file_content, " ");
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "time used: " << time_used.count() << " seconds" << endl;
    cout << tokens.size() << " ";
    //cout << tokens[100] << " " << tokens[200] << endl;
}


int split_line_into_tokens6(const char* str, char delim, int *starts, int *lengths) {
    const char *p = str;
    unsigned char newstr = 1;
    int tokens = 0;
    while (*p != '\0') {
        if (newstr) {
            newstr = 0;
            starts[tokens] = p - str;
        }
        if (*p == delim || *p == '\0') {
            newstr = 1;
            lengths[tokens] = p - str - starts[tokens];
            ++tokens;
        }
        ++p;
    }
    return tokens;
}

void printstring(const char *str, int len) {
    const char *p = str;
    while (len--) {
        putchar(*p++);
    }
    putchar('\n');
}

int main(){
    cout << start_with("fuck", "fuck you") << endl;
    cout << start_with("fuck", "ffuck you") << endl;
    cout << start_with("fuck you", "fuck you") << endl;
    cout << start_with("fuck", "f") << endl;
    cout << start_with("fuck", "fu") << endl;

    vector<string> tokens;
    ifstream tokens_file("./Watcher.txt");
    stringstream sstr;
    sstr << tokens_file.rdbuf();
    string file_content = sstr.str();

    int *starts = (int*) malloc(sizeof(int) * 30000000);
    int *lengths = (int*) malloc(sizeof(int) * 30000000);

    time_used(file_content, split_line_into_tokens1);
    time_used(file_content, split_line_into_tokens2);
    time_used(file_content, split_line_into_tokens3);
    time_used(file_content, split_line_into_tokens4);
    time_used(file_content, split_line_into_tokens5);


    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    int fangfuck = split_line_into_tokens6(file_content.c_str(), ' ', starts, lengths);
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "time used: " << time_used.count() << " seconds" << endl;
    // int v1, v2, v3;
    // char buffer[100] = "f 9//3 4 3//3";
    // sscanf(buffer, "f %d%*[ ]%d%*[ ]%d", &v1, &v2, &v3);
    // printf("%d %d %d", v1, v2, v3);
    free(starts);
    free(lengths);
    return 0;
}
    


