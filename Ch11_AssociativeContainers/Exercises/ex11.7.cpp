// ex11.7.cpp
/*Define a  map for which the key is the family’s last name
and the value is a  vector of the children’s names. Write code to add new
families and to add new children to an existing family.*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
using std::cout;
using std::string;
using std::vector;
using std::map;
using std::pair;


int main()
{
    map<string, vector<string>> families
        {
            {"Lastname1", {"Firstname1", "Firstname2", "Firstname3"}}
           ,{"Lastneme2", {"Fname1", "Fname2", "Fname3", "Fname4"}}
        };
    

    families["Lastname3"] = vector<string>({"Some", "More", "Kids", "Names"});
    pair<map<string,vector<string>>::iterator, bool> insres = 
                        families.insert(std::make_pair("Lastname4",
                        vector<string>({"Fourth", "Family", "Last", "Names"})));

    if(insres.second){
        cout << "family 'Lastname4' succesfuly inserted.\n";
    }
    else{
        cout << "family 'Lastname4 already present in the map.\n";
    }
    cout << "'Lastname4' family's kids: ";
    for( vector<string>::const_iterator it=insres.first->second.cbegin();
         it != insres.first->second.cend(); )
         cout << *it++ << ", ";
    cout << std::endl;

    for( const pair<string, vector<string>>& f : families){
        cout << "Family last name: " << f.first
             << "\n\tKids: ";
        for( const string& name : f.second)
            cout << name << ", ";
        cout << std::endl;
    }
}
