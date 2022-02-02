//
//  main.cpp
//  poj3487
//
//  Created by 李超予 on 2021/8/28.
//

#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<string>
#include<queue>
#include<algorithm>
using namespace std;

int T,n;
int m[30],f[30]; //male & female
int ml[30][30],fl[30][30]; //malelike[male number][female number];femalelike[female number][male number]. It's a rank.
int mc[30],fc[30]; //malechoice[male number];femalechoice[female number]. It stands for male[i] choose which female
char s[100];
queue<int> fm;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for (int i=0; i<n; i++)
        {
            scanf("%s",s);
            m[i]=(int)(s[0]-'a');
            fm.push(m[i]);
        }
        //cout<<m<<endl;
        for (int i=0; i<n; i++)
        {
            scanf("%s",s);
            f[i]=(int)(s[0]-'A');
        }
        sort(m,m+n);
        for (int i=0; i<n; i++)
        {
            scanf("%s",s);
            for (int j=0; j<n; j++)
                ml[i][j]=s[j+2]-'A';
        }
        for (int i=0; i<n; i++)
        {
            scanf("%s",s);
            for (int j=0; j<n; j++)
                fl[i][int(s[j+2]-'a')]=j; //fl[i][k] is smaller stand for fl[i] more like k.
            fl[i][n]=n;
        }
        memset(mc,0,sizeof(mc));
        for (int i=0; i<n; i++)
            fc[i]=n;
//      G-S algorithm
        while (!fm.empty())
        {
            int male=fm.front();
            int female=ml[male][mc[male]];
            if (fl[female][male]<fl[female][fc[female]])
            {
                fm.pop();
                if (fc[female]!=n)
                {
                    fm.push(fc[female]);
                    mc[fc[female]]++;
                }
                fc[female]=male;
            }
            else
                mc[male]++;
        }
//      End
        for (int i=0; i<n; i++)
            printf("%c %c\n",m[i]+'a',ml[m[i]][mc[m[i]]]+'A');
        printf("\n");
    }
    return 0;
}
