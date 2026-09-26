#include <iostream>
#include <vector>
using namespace std;

//sample solution not optimased
int main(){
    int n;
    cin >> n;

    vector<string> words;

    for(int i=0;i<n;i++){
        string word;
        cin >> word;
        words.push_back(word);
    }

    for(int i=0;i<n;i++){
        string word = words[i];
        vector<string> acronym;
        acronym.clear();
        for(int j=0;j<word.length();j++){
            char letter = word[j];
            bool flag = false;

            for(int k=0;k<n;k++){
                //can be used to acronym
                if(words[k][0] == letter){
                    flag = true;
                    acronym.push_back(words[k]);
                    break;
                }
            }

            if(!flag)
                break;
        }

        //acronym was created
        if(acronym.size() == word.length()){
            cout << acronym.size() << "\n";
            for(int j=0;j<acronym.size();j++){
                cout << acronym[j] << " ";
            }
            return 0;
        }
    }
    cout << -1;
    return 0;
}