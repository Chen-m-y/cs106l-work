#include <algorithm>
#include <cctype>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <cmath>

using std::cout; using std::endl;
using std::ifstream; using std::string;
using std::vector;

const vector<string> FEATURE_VEC{"a", "about", "above", "after", "again", "against", "all", "am",
"an", "and",
"any", "are", "aren't", "as", "at", "be", "because", "been", "before", "being",
"below", "between", "both", "but", "by", "can't", "cannot", "could", "couldn't",
"did", "didn't", "do", "does", "doesn't", "doing", "don't", "down", "during",
"each", "few", "for", "from", "further", "had", "hadn't", "has", "hasn't", "have",
"haven't", "having", "he", "he'd", "he'll", "he's", "her","here", "here's", "hers",
"herself", "him", "himself", "his", "how", "how's", "i", "i'd", "i'll", "i'm",
"i've", "if", "in", "into", "is", "isn't", "it", "it's", "its", "itself", "let's",
"me", "more", "most", "mustn't", "my", "myself", "no", "nor", "not", "of", "off",
"on", "once", "only", "or", "other", "ought", "our", "ours", "ourselves", "out",
"over", "own", "same", "shan't", "she", "she'd", "she'll", "she's", "should",
"shouldn't", "so", "some", "such", "than", "that", "that's", "the", "their",
"theirs", "them", "themselves", "then", "there", "there's", "these", "they",
"they'd", "they'll", "they're", "they've", "this", "those", "through", "to", "too",
"under", "until", "up", "very", "was", "wasn't", "we", "we'd", "we'll", "we're",
"we've", "were", "weren't", "what", "what's", "when", "when's", "where", "where's",
"which", "while", "who", "who's", "whom", "why", "why's", "with", "won't", "would",
"wouldn't", "you", "you'd", "you'll", "you're", "you've", "your", "yours",
"yourself", "yourselves", "!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+",
",", "-", ".", "/", ":", ";", "<", "=", ">", "?", "@", "[", "\\", "]", "^", "_",
"`", "{", "|", "}", "~"};

double dotProduct(const vector<int>& Vect1, const vector<int>& Vect2);
double mag(const vector<int>& vec);

string filetoString(ifstream& file){
    string line;
    string ret = "";
    while(std::getline(file, line)){
        std::transform(line.begin(), line.end(), line.begin(), tolower);
        ret += line + " ";
    }
    return ret;
}

int countOccurred(const string& target, const string& s){
    //return std::count(s.begin(), s.end(), target);数的是元素（char）
    auto curr = s.begin();
    auto last = s.end();
    int count = 0;
    while(curr != last){
        curr = std::search(curr, last, target.begin(),target.end());
        if(curr == last) break;
        ++count;
        curr = curr + 1; // curr + 1 循环变量永远不变，只是做了1次计算
    }
    return count;
}

vector<int> createVector(const string& s){
    vector<int> result;
    for(const auto& word : FEATURE_VEC){
        string target = " " + word + " ";
        //<regex>
        result.push_back(countOccurred(target, s));
    }
    return result;
}

double getSimilarity(const string& s1, const string& s2){
    vector<int> Vect1 = createVector(s1);
    vector<int> Vect2 = createVector(s2);

    double dotprod = dotProduct(Vect1, Vect2);
    return dotprod / (mag(Vect1) * mag(Vect2));  
}

double dotProduct(const vector<int>& Vect1, const vector<int>& Vect2){
    return std::inner_product(Vect1.begin(), Vect1.end(), Vect2.begin(), 0);
}

double mag(const vector<int>& vec){
    return std::sqrt(dotProduct(vec, vec));
}

int main(){
    ifstream file1("madison.txt");
    if (!file1) {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }
    ifstream file2("hamilton.txt");
    ifstream file3("jj.txt");
    ifstream file4("unknown.txt");

    string f_a = filetoString(file1);
    string f_b = filetoString(file2);
    string f_c = filetoString(file3);
    string f_unk = filetoString(file4);

    cout << "Similarity James Madison <-> unknown:    " << getSimilarity(f_a, f_unk) << endl;
    cout << "Similarity Alexander Hamilton <-> unknown: " << getSimilarity(f_b, f_unk) << endl;
    cout << "Similarity John Jay <-> unknown:      " << getSimilarity(f_c, f_unk) << endl;

    //cout <<"hello,world"<< endl;
    
}