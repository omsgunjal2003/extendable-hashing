#include <bits/stdc++.h>

using namespace std;

class bnode{
    public:
        vector<long long int> v;
        long long int data_node;
        vector<bnode *> vptr;
        long long int num_values;
        bnode * par;
};

int main()
{
    bnode* root=nullptr;
    long long int i;
    long long int d,t;
    long long int k;
    cin >> d;
    cin >> t;
    long long int x;
    long long int m;
    bnode* mptr;
    long long int val;
    long long int ndata,nindex;
    ndata=0;
    nindex=0;
    vector<long long int> tmp;
    vector<bnode *> tmpptr;
    x=2;
    while(x==1 || x==2){
        cin >> x;
        if(x==1){
            cin >> val;
            if(nindex==0){
                if(ndata==0){
                    bnode* bnode_var=new bnode;
                    root=bnode_var;
                    (root->v).push_back(val);
                    ndata++;
                    root->data_node=1;
                    root->num_values=1;
                    root->par=nullptr;
                }
                else{
                    if(root->num_values<2*d){
                        (root->v).push_back(val);
                        root->num_values++;
                    }
                    else{
                        (root->v).push_back(val);
                        root->num_values++;
                        sort((root->v).begin(),(root->v).end());
                        for(i=0;i<=d;i++){
                            tmp.push_back((root->v)[d+i]);
                        }
                        for(i=0;i<=d;i++){
                            (root->v).pop_back();
                        }
                        root->num_values=d;
                        bnode* bnode_var=new bnode;
                        root->par=bnode_var;
                        (bnode_var->vptr).push_back(root);
                        root=bnode_var;
                        root->par=nullptr;
                        nindex++;
                        root->data_node=0;
                        bnode* bnode_var2=new bnode;
                        bnode_var2->data_node=1;
                        ndata++;
                        (root->vptr).push_back(bnode_var2);
                        k=tmp[0];
                        for(i=0;i<=d;i++){
                            (bnode_var2->v).push_back(tmp[i]);
                        }
                        tmp.clear();
                        bnode_var2->num_values=d+1;
                        bnode_var2->par=root;
                        (root->v).push_back(k);
                        root->num_values=1;
                    }
                }
            }
            else{
                bnode* bnode_var=root;
                while(bnode_var->data_node!=1){
                    if(val<(bnode_var->v)[0]){
                        bnode_var=(bnode_var->vptr)[0];
                    }
                    else if(val>(bnode_var->v)[(bnode_var->v).size()-1]){
                        bnode_var=(bnode_var->vptr)[(bnode_var->v).size()];
                    }
                    else{
                        for(auto j=0;j<(bnode_var->v).size()-1;j++){
                            if(val>(bnode_var->v)[j] && val<(bnode_var->v)[j+1]){
                                bnode_var=(bnode_var->vptr)[j+1];
                            }
                        }
                    }
                }
                if(bnode_var->num_values<2*d){
                    (bnode_var->v).push_back(val);
                    (bnode_var->num_values)++;
                }
                else{
                    (bnode_var->v).push_back(val);
                    sort((bnode_var->v).begin(),(bnode_var->v).end());
                    for(i=d;i<=2*d;i++){
                        tmp.push_back((bnode_var->v)[i]);
                    }
                    for(i=d;i<=2*d;i++){
                        (bnode_var->v).pop_back();
                    }
                    bnode_var->num_values=d;
                    k=tmp[0];
                    bnode* bnode_var2=new bnode;
                    ndata++;
                    bnode_var2->data_node=1;
                    for(i=0;i<=d;i++){
                        (bnode_var2->v).push_back(tmp[i]);
                    }
                    tmp.clear();
                    bnode_var2->num_values=d+1;
                    bnode_var2->par=bnode_var->par;
                    while(bnode_var!=root && (bnode_var->par)->num_values==2*t+1){
                        if(k<((bnode_var->par)->v)[0]){
                            m=((bnode_var->par)->v)[((bnode_var->par)->v).size()-1];
                            for(i=((bnode_var->par)->v).size()-1;i>0;i--){
                                ((bnode_var->par)->v)[i]=((bnode_var->par)->v)[i-1];
                            }
                            ((bnode_var->par)->v)[0]=k;
                            ((bnode_var->par)->num_values)++;
                            ((bnode_var->par)->v).push_back(m);
                            mptr=((bnode_var->par)->vptr)[((bnode_var->par)->vptr).size()-1];
                            for(i=((bnode_var->par)->vptr).size()-1;i>1;i--){
                                ((bnode_var->par)->vptr)[i]=((bnode_var->par)->vptr)[i-1];
                            }
                            ((bnode_var->par)->vptr)[1]=bnode_var2;
                            ((bnode_var->par)->vptr).push_back(mptr);
                        }
                        else if(k>((bnode_var->par)->v)[((bnode_var->par)->v).size()-1]){
                            ((bnode_var->par)->v).push_back(k);
                            ((bnode_var->par)->num_values)++;
                            ((bnode_var->par)->vptr).push_back(bnode_var2);
                        }
                        else{
                            for(auto j=0;j<((bnode_var->par)->v).size()-1;j++){
                                if(k>((bnode_var->par)->v)[j] && k<((bnode_var->par)->v)[j+1]){
                                    //((bnode_var->par)->num_values)++;
                                    m=((bnode_var->par)->v)[((bnode_var->par)->v).size()-1];
                                    for(i=((bnode_var->par)->v).size()-1;i>j+1;i--){
                                        ((bnode_var->par)->v)[i]=((bnode_var->par)->v)[i-1];
                                    }
                                    ((bnode_var->par)->v)[j+1]=k;
                                    ((bnode_var->par)->num_values)++;
                                    ((bnode_var->par)->v).push_back(m);
                                    mptr=((bnode_var->par)->vptr)[((bnode_var->par)->vptr).size()-1];
                                    for(i=((bnode_var->par)->vptr).size()-1;i>j+2;i--){
                                        ((bnode_var->par)->vptr)[i]=((bnode_var->par)->vptr)[i-1];
                                    }
                                    ((bnode_var->par)->vptr)[j+2]=bnode_var2;
                                    ((bnode_var->par)->vptr).push_back(mptr);
                                }
                            }
                        }
                        //cout << "broke" << endl;
                        bnode* bnode_var3=new bnode;
                        k=((bnode_var->par)->v)[t];
                        bnode_var3->data_node=0;
                        nindex++;
                        bnode_var3->num_values=t+1;
                        (bnode_var->par)->num_values=t;
                        for(i=t+1;i<=2*t + 1;i++){
                            tmp.push_back(((bnode_var->par)->v)[i]);
                        }
                        for(i=t;i<=2*t + 1;i++){
                            ((bnode_var->par)->v).pop_back();
                        }
                        for(i=0;i<=t;i++){
                            (bnode_var3->v).push_back(tmp[i]);
                        }
                        tmp.clear();
                        //cout << "broke" << endl;
                        for(i=t+1;i<=2*t + 2;i++){
                            tmpptr.push_back(((bnode_var->par)->vptr)[i]);
                        }
                        for(i=t+1;i<=2*t + 2;i++){
                            ((bnode_var->par)->vptr).pop_back();
                        }
                        for(i=0;i<=t+1;i++){
                            (bnode_var3->vptr).push_back(tmpptr[i]);
                        }
                        tmpptr.clear();
                        //cout << "broke" << endl;
                        bnode_var3->par=(bnode_var->par)->par;
                        for(i=0;i<=t;i++){
                            (((bnode_var->par)->vptr)[i])->par=bnode_var->par;
                        }
                        bnode_var=(bnode_var)->par;
                        for(i=0;i<=t+1;i++){
                            ((bnode_var3->vptr)[i])->par=bnode_var3;
                        }
                        //cout << "broke" << endl;
                        bnode_var2=bnode_var3;
                        //cout << "broke" << endl;
                    }
                    if(bnode_var==root){
                        bnode* bnode_var4=new bnode;
                        //cout << "broke" << endl;
                        nindex++;
                        bnode_var4->num_values=1;
                        (bnode_var4->v).push_back(k);
                        bnode_var4->data_node=0;
                        bnode_var4->par=nullptr;
                        bnode_var4->vptr.push_back(bnode_var);
                        bnode_var4->vptr.push_back(bnode_var2);
                        bnode_var->par=bnode_var4;
                        bnode_var2->par=bnode_var4;
                        root=bnode_var4;
                    }
                    else{
                        if(k<((bnode_var->par)->v)[0]){
                            m=((bnode_var->par)->v)[((bnode_var->par)->v).size()-1];
                            for(i=((bnode_var->par)->v).size()-1;i>0;i--){
                                ((bnode_var->par)->v)[i]=((bnode_var->par)->v)[i-1];
                            }
                            ((bnode_var->par)->v)[0]=k;
                            ((bnode_var->par)->num_values)++;
                            ((bnode_var->par)->v).push_back(m);
                            mptr=((bnode_var->par)->vptr)[((bnode_var->par)->vptr).size()-1];
                            for(i=((bnode_var->par)->vptr).size()-1;i>1;i--){
                                ((bnode_var->par)->vptr)[i]=((bnode_var->par)->vptr)[i-1];
                            }
                            ((bnode_var->par)->vptr)[1]=bnode_var2;
                            ((bnode_var->par)->vptr).push_back(mptr);
                        }
                        else if(k>((bnode_var->par)->v)[((bnode_var->par)->v).size()-1]){
                            ((bnode_var->par)->v).push_back(k);
                            ((bnode_var->par)->num_values)++;
                            ((bnode_var->par)->vptr).push_back(bnode_var2);
                        }
                        else{
                            for(auto j=0;j<((bnode_var->par)->v).size()-1;j++){
                                if(k>((bnode_var->par)->v)[j] && k<((bnode_var->par)->v)[j+1]){
                                    //((bnode_var->par)->num_values)++;
                                    m=((bnode_var->par)->v)[((bnode_var->par)->v).size()-1];
                                    for(i=((bnode_var->par)->v).size()-1;i>j+1;i--){
                                        ((bnode_var->par)->v)[i]=((bnode_var->par)->v)[i-1];
                                    }
                                    ((bnode_var->par)->v)[j+1]=k;
                                    ((bnode_var->par)->num_values)++;
                                    ((bnode_var->par)->v).push_back(m);
                                    mptr=((bnode_var->par)->vptr)[((bnode_var->par)->vptr).size()-1];
                                    for(i=((bnode_var->par)->vptr).size()-1;i>j+2;i--){
                                        ((bnode_var->par)->vptr)[i]=((bnode_var->par)->vptr)[i-1];
                                    }
                                    ((bnode_var->par)->vptr)[j+2]=bnode_var2;
                                    ((bnode_var->par)->vptr).push_back(mptr);
                                }
                            }
                        }
                    }
                }
            }
        }
        if(x==2){
            cout << nindex << " " << ndata << " ";
            if(root!=nullptr){
                if(root->data_node==1){
                    sort((root->v).begin(),(root->v).end());
                }
                for(auto j=(root->v).begin();j<(root->v).end();j++){
                    cout << *j << " ";
                }
            }
            cout << endl;
        }
    }
    return 0;
}