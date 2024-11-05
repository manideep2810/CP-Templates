#include<bits/stdc++.h>
using namespace std;
#define int long long int

vector<int> manchester_odd(string s){
    int n = s.length();
    s = "$" + s + "^";
    vector<int> p(n+2,0);
    int l = 1 , r = 1;
    for(int i = 1 ; i <= n ; i++){
        p[i] = max(0ll,min(r-i,p[l+(r-i)]));
        while(s[i-p[i]]==s[i+p[i]]){
            p[i]++;
        }
        if(i+p[i] > r){
            l = i - p[i] , r = i + p[i];
        }
    }

    return vector<int>(p.begin()+1,p.end()-1);
}

vector<int> manchester_split(string s){
    int n = s.length();
    string t;
    for(int i = 0 ; i < n ; i++){
        t = t + "#" + s[i];
    }
    t = t + "#";
    vector<int> res = manchester_odd(t); 
    return res;
}

vector<int> manchester(string s){
    int n = s.length();
    vector<int> d = manchester_split(s);
    vector<int> ans(n);
    for(int i = 0 ; i < n ; i++){
        ans[i] = max(d[2*i+1]/2 , (d[2*i]-1)/2);
    }
    return ans;
}

signed main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    t = 1;
    while(t--)
    {
        string s = "abababc";
        vector<int> res = manchester(s);
        for(auto i:res){
            cout << i << " ";
        }
    }
    return 0;
}