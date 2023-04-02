// @FileName:     palindrome.cpp
// @CreateTime:   2023/04/02 10:55:47
// @Author:       Rainbow River

// 给出一个字符串S，求S的最长回文子串的长度

#include <iostream>
#include <string>
using namespace std;
bool judge_ok(int i, int j);
void palindrome(int& mxl);
string iptstr;
// 暴力搜索
void palindrome(int& mxl){
    for(int i=0; i<iptstr.length(); i++){
        for(int j=i; j<iptstr.length(); j++){
            if(judge_ok(i, j))
                mxl = (j-i+1) > mxl ? (j-i+1) : mxl;
        }
        cout << "i = " << i << ", mxl = " << mxl << endl;
    }
}

// if a string is a palindrome
bool judge_ok(int i, int j){
    while(i<=j){
        if(iptstr[i]==iptstr[j]){
            ++i;
            --j;
        }else return false;
    }
    return true;
}

int main(){
    cin >> iptstr;
    int mxl = 0;
    palindrome(mxl);
    cout << mxl;
    return 0;
}

/*
PATZJUJZTACCBCC

*/