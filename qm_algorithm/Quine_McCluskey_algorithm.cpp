/*
 * @Author: lmy
 * @Date: 2022-03-02 23:05:33
 * @LastEditors: lmy
 * @LastEditTime: 2022-03-03 12:46:19
 * @FilePath: \c++\Quine_McCluskey_algorithm.cpp
 * @Description: 
 */
#include <bits/stdc++.h>
using namespace std;
int n;
int leftcnt;
ostream& operator << (ostream& out,vector<int>& vi){
    out<<"the context is: ";
    for(auto it=vi.begin();it!=vi.end();++it){
        out<<*it<<" ";
    }
    out<<endl;
    return out;
};
struct min_item{
    int binary[32];
    int changed;
    vector<int> min_group;
    min_item(int k){
        changed=0;
        min_group.push_back(k);
        for (int i=0;i<n;++i){
            binary[i]=k&1;
            k/=2;
        }
    }
    int cnt_of_one(){
        int cntone=0;
        for (int i=0;i<n;++i){
            if (binary[i]==1)++cntone;
        }
        return cntone;
    }
    min_item& operator =(min_item item){
        this->min_group=item.min_group;
        for (int i=0;i<n;++i){
            this->binary[i]=item.binary[i];
        }
        return *this;
    }
    bool operator ==(min_item item){
        for (int i=0;i<n;++i){
            if (binary[i]!=item.binary[i])return false;
        }
        return true;
    };
    /*~min_item(){
        delete[] binary;
    }*/
    friend ostream& operator <<(ostream& out,min_item item);
    friend bool combine(min_item i1,min_item i2,min_item& tmp);
};
bool combine(min_item i1,min_item i2,min_item& tmp){
    bool changed=false;
    int difcnt=0;int loc;
    for (int i=0;i<n;++i){
        if (i1.binary[i]==2&&i2.binary[i]!=2||i2.binary[i]==2&&i1.binary[i]!=2){
            return false;
        }
        if (i1.binary[i]==0&&i2.binary[i]==1||i1.binary[i]==1&&i2.binary[i]==0){
            ++difcnt;
            loc=i;
        }
    }
    if (difcnt==1){
        for (int i=0;i<n;++i){
            if (i==loc){
                tmp.binary[loc]=2;
                continue;
            }
            tmp.binary[i]=i1.binary[i];
        }
        tmp.min_group=i1.min_group;
        vector<int> tmpv=i2.min_group;
        for (auto it=tmpv.begin();it!=tmpv.end();++it){
            tmp.min_group.push_back(*it);
        }
        changed=true;
    }
    return changed;
};
ostream& operator <<(ostream& out,min_item item){
    out<<" min_group";
    for (int i=0;i<item.min_group.size();++i){
        out<<item.min_group[i]<<" ";
    }
    out<<"binary=";
    for (int i=n-1;i>=0;--i){
        out<<item.binary[i];
    }
    out<<" changed="<<item.changed;
    out<<endl;
    return out;
}
bool iscomplete(unordered_map<int,int> mp){
    for (auto it=mp.begin();it!=mp.end();++it){
        if (it->second<1){
            return false;
        }
    }
    return true;
}
vector<int> tobinary(int k,int ps){
    vector<int> an;
    for (int i=0;i<ps;++i){
        an.push_back(k&1);
        k>>=1;
    }
    return an;
}
int cnt_binary(vector<int> f){
    int cnt=0;
    for (int i=0;i<f.size();++i){
        if (f[i]==1)++cnt;
    }
    return cnt;
}
int main(){
    int inputopt,inputmax;//变量个数
    vector<int> m,d;
    printf("请输入变量个数：\n");
    scanf("%d",&n);
    inputmax=pow(2,n)-1;
    printf("1.输入最小项 2.输入最大项 请输入1或2\n");
    scanf("%d",&inputopt);
    switch(inputopt){
        case 1:{
            printf("请输入最小项（0到%d之间），以空格隔开，-1结束\n",inputmax);
            int inp;
            while(cin>>inp){
                if (inp==-1)break;
                else{
                    m.push_back(inp);
                }
            }
            sort(m.begin(),m.end());
            break;
        }
        case 2:{
            printf("请输入最大项（0到%d之间），以空格隔开，-1结束\n",inputmax);
            int* rest_m=new int[inputmax+1];
            for (int i=0;i<=inputmax;++i){rest_m[i]=0;}
            int inp;
            while(cin>>inp){
                if (inp==-1)break;
                else{
                    rest_m[inp]=1;
                }
            }
            for (int i=0;i<=inputmax;++i){
                if (rest_m[i]==0){
                    m.push_back(i);
                }
            }
            delete[] rest_m;
            break;
        }
        default:break;
    }
    sort(d.begin(),d.end());
    cout<<m<<endl;
    vector<min_item> emp;
    vector<vector<min_item>> group(n+1,emp);
    for (int i=0;i<m.size();++i){
        int k=m[i];
        min_item kitem(k);
        int cnt=kitem.cnt_of_one();
        group[cnt].push_back(kitem);
    }
    /*cout<<"the initial group is:\n";
    for (int i=0;i<=n;++i){
        cout<<"group"<<i<<":\n";
        for (int j=0;j<group[i].size();++j){
            cout<<group[i][j];
        }
    }*/
    bool change=1;
    min_item tmp(0);
    while(change){//合并
        change=0;
        for (int i=0;i<n;++i){
            for (int j=0;j<group[i].size();++j){
                for (int k=0;k<group[i+1].size();++k){
                    if (combine(group[i][j],group[i+1][k],tmp)){
                        min_item newit=tmp;
                        //newit.changed=0;
                        
                        group[i][j].changed=1;
                        group[i+1][k].changed=1;
                        //cout<<"warning:"<<group[i][j]<<"and"<<group[i+1][k]<<"changed to"<<newit<<endl;
                        int newcnt=newit.cnt_of_one();
                        bool flag=0;
                        for (int l=0;l<group[newcnt].size();++l){
                            if (group[newcnt][l]==newit){
                                flag=1;
                                break;
                            }
                        }
                        if (!flag){
                            group[newcnt].push_back(newit);
                            change=1;
                        }
                        
                    }
                }
            }
        }
    }
    cout<<"the changed group is:\n";
    vector<min_item> prime;
    for (int i=0;i<=n;++i){
        for(int j=0;j<group[i].size();++j){
            if (group[i][j].changed==0){
                prime.push_back(group[i][j]);
            }
        }
    }
    for (auto it=prime.begin();it!=prime.end();++it){
        cout<<*it;
    }//质蕴含项
    change=1;
    vector<min_item> ans;
    while(change){
        change=0;
        unordered_map<int,int> list;
        for (auto it=prime.begin();it!=prime.end();++it){
            vector<int> tmp=it->min_group;
            for (auto i=tmp.begin();i!=tmp.end();++i){
                list[*i]++;
            }
        }
        vector<int> mark;
        for (auto it=list.begin();it!=list.end();++it){
            if (it->second==1){
                mark.push_back(it->first);
            }
        }
        for (auto it=prime.begin();it!=prime.end();++it){
            vector<int> tmp=it->min_group;
            auto i=tmp.begin();
            for (i=tmp.begin();i!=tmp.end();++i){
                auto j=mark.begin();
                for (j=mark.begin();j!=mark.end();++j){
                    if (*i==*j){
                        break;
                    }
                }
                if (j!=mark.end()){
                    break;
                }
            }
            if (i!=tmp.end()){
                ans.push_back(*it);
                it=prime.erase(it);
                --it;
                continue;
            }
        }
    }
    //cout<<"ans="<<endl;
    unordered_map<int,int> min_included,leftover;
    for (auto it=ans.begin();it!=ans.end();++it){
        //cout<<*it;
        for (auto j=it->min_group.begin();j!=it->min_group.end();++j){
            min_included[*j]++;
        }
    }
    cout<<"curr="<<endl;
    for (int i=0;i<prime.size();++i){
        cout<<prime[i];
    }
    cout<<"map:\n";
    for (auto it=min_included.begin();it!=min_included.end();++it){
        cout<<"inc["<<it->first<<"]="<<it->second<<endl;
    }
    //cout<<"left="<<endl;
    for (auto it=prime.begin();it!=prime.end();++it){
        auto i=it->min_group.begin();
        for (;i!=it->min_group.end();++i){
            if (min_included[*i]==1){
                break;
            }
        }
        if (i!=it->min_group.end()){
            //test
            //ans.push_back(*it);
            //endtest
            it=prime.erase(it);
            --it;
            continue;
        }
    }
    for (auto it=prime.begin();it!=prime.end();++it){
        //cout<<*it;
        auto i=it->min_group.begin();
        for (;i!=it->min_group.end();++i){
            if (min_included[*i]>0)continue;
            leftover[*i]=0;
        }
    }
    int ps=prime.size();
    leftcnt=leftover.size();
    cout<<"leftcnt="<<leftcnt<<endl;
    vector<int> flg(ps,0);
    int scnt=pow(2,ps);
    int cntofb=2147483647;
    vector<min_item> tt;
    /*cout<<"curr="<<endl;
    for (int i=0;i<prime.size();++i){
        cout<<prime[i];
    }*/
    for (int i=0;i<scnt;++i){
        flg=tobinary(i,ps);
        unordered_map<int,int> mp=leftover;
        for (int j=0;j<ps;++j){
            if (flg[j]==1){
                vector<int> tmp=prime[j].min_group;
                for (auto it=tmp.begin();it!=tmp.end();++it){
                    ++mp[*it];
                }
            }
        }
        if (iscomplete(mp)){
            if (cnt_binary(flg)<cntofb){
                cntofb=cnt_binary(flg);
                vector<min_item> k;
                for (int j=0;j<ps;++j){
                    if (flg[j]==1){
                       k.push_back(prime[j]); 
                    }
                }
                tt=k;
            }
        }
    }
    //cout<<"tt=\n";
    for (auto it=tt.begin();it!=tt.end();++it){
        //cout<<*it;
        ans.push_back(*it);
    }
    cout<<"the final answer is:\n";
    for (auto it=ans.begin();it!=ans.end();++it){
        cout<<*it;
    }
    return 0;
}
