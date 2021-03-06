#include<bits/stdc++.h>
using namespace std;
int a;
int b;
main()
{
    int n;
    cin>>n;
    while(n--)
    {
        cin>>a>>b;
        int tong=a*b;
        if(b>=50)
            tong=tong-15*tong/100;
        if(tong<10000000)
            tong+=min(200000,tong/20);
        cout<<tong<<endl;
    }
    // asldkajsdl
}
