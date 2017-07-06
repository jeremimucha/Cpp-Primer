// ex11.38
/*Version of the word-transformation program using an unordered_map.*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <cstdlib>
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::string;
using std::unordered_map;
using std::pair;
using std::getline;


void word_transform(ifstream& map_file, ifstream& input_file);
unordered_map<string, string> buildMap(ifstream& map_file);
const string& transform(const string& s, const unordered_map<string, string>& m);


int main(int argc, char* argv[])
{
    if(argc != 3){
        std::cerr << "Usage: " << argv[0] << "word-translation-file file-to-translate\n";
        exit(EXIT_FAILURE);
    }
    ifstream mapfile{argv[1]};
    if(!mapfile.is_open()){
        std::cerr << "Failed to open the file " << argv[1];
        exit(EXIT_FAILURE);
    }
    ifstream infile{argv[2]};
    if(!infile.is_open()){
        std::cerr << "Failed to open the file " << argv[2];
        exit(EXIT_FAILURE);
    }

    word_transform(mapfile, infile);
}


void word_transform(ifstream& map_file, ifstream& input_file)
{
    unordered_map<string, string> trans_map = buildMap(map_file);
    // std::cerr << "The map:\n";
    // for(auto it=trans_map.cbegin(); it!=trans_map.cend();++it){
    //     std::cerr << it->first << " = " << it->second << "\n";
    // }
    string text;
    while( std::getline(input_file, text) ){
        istringstream stream(text);
        string word;
        bool firstword = true;
        while( stream >> word ){
            if( firstword ){         // don't print space before the first word
                firstword = false;
            }else{
                cout << " ";        // print space between words
            }
            // transform returns its first argument or its transformation
            cout << transform(word, trans_map);
        }
        cout << endl;
    }
}

unordered_map<string, string> buildMap(ifstream& map_file)
{
    unordered_map<string, string> trans_map;
    string key;
    string value;
    while( map_file >> key && map_file.get()!='\n' && getline(map_file, value) ){
        // we skip leading space with map_file.get(), no need to check
        // if value.size() > 1, map_file.get()!='\n' check would fail if it was
        // so proceed with assignment
        trans_map[key] = std::move(value);
    }
    return trans_map;
}

const string& transform(const string& s, const unordered_map<string, string>& m)
{
    // the actual map work: this is the heart of the program
    unordered_map<string, string>::const_iterator map_it = m.find(s);
    // auto map_it = m.find(s);
    // if this word is in the transformation map
    if(map_it != m.cend()){
        return map_it->second;  // use the replacement word
    }
    else{
        return s;
    }
}
