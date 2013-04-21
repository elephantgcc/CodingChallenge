/**
 * Coding challenge for Apertium GSOC2013 
 * of idea "Sliding-window part-of-speech tagger":
 *
 * Reverting the ApertiumFilter's output back to the original format
 *
 * Example input line:
 * I.prn.subj.p1.mf.sg have.vbhaver.inf 
 * output:
 * ^I<prn><subj><p1><mf><sg>$ ^have<vbhaver><inf>$
 *
 * 2013-04-21 by Gang Chen
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
using namespace std;

void revert() {
    string line;
    string word;
    while (getline(cin, line)) {
        cout << "^";
        bool first_dot_flag = true;
        for (size_t i = 0 ; i < line.size(); ++i) {
            if (line[i] == '.') {
                if (first_dot_flag) {
                    if ( (i + 1 < line.size()) && line[i + 1] == '.') {
                        cout << '.';
                    } else {
                        cout << "<";
                        first_dot_flag = false;
                    }
                } else {
                    cout << "><";
                }
            } else if (line[i] == ' ') {
                cout << ">$ ^";
                first_dot_flag = true;
            } else {
                cout << line[i];
            }
        }
        cout << ">$\n";
    }
} 


int main(int argc, char * argv[]) {
    if (argc == 1) {
        revert();
    } else if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)){
        cout << "ApertiumRevertor: Revert ApertiumFilter's output back into original format."
             << "usage: exe < input > output";
    } else {
        cerr << "error: invalid cmd/option!\n"
             << "try `./NaiveReformatter -h or --help' for more information.\n";
        exit(1);
    }
}
