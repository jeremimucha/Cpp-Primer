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
    families.insert(std::make_pair("Lastname4",
            vector<string>({"Fourth", "Family", "Last", "Names"})));

    for( const pair<string, vector<string>>& f : families){
        cout << "Family last name: " << f.first
             << "\n\tKids: ";
        for( const string& name : f.second)
            cout << name << ", ";
        cout << std::endl;
    }
}
