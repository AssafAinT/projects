#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>   


using namespace std;
//using namespace ilrd;
int main()
{

    unordered_map<string, size_t> histo_map;
    vector<string> str_vec;

    string str;

    getline(std::cin, str);

    while ("." != str)
    {
        if (histo_map.end() == histo_map.find(str))
        {
            str_vec.push_back(str);
            histo_map[str] = 1;
        }
        else
        {
            int new_val = ++histo_map[str];
            histo_map[str] = new_val;
        }

        getline(std::cin, str);
    }
    cout << endl;

    for (/*vector<string>iterator*/ auto runner = str_vec.begin(); runner < str_vec.end(); ++runner)
    {
        if (1 != histo_map[*runner])
        {
            cout << (histo_map[*runner]) << " x " << *runner << endl;
        }
        else
        {
            cout << *runner << endl;
        }
    }

    return 0;
}
