#include <bits/stdc++.h>

using namespace std;

// ===========================THE BUCKET CLASS================================
class Bucket
{
    public:
        Bucket();
        Bucket(int local_depth,int bucket_size);
        virtual ~Bucket();
        void display();
        int localDepth;
        int capacity;
        multiset<int> values;
        multiset<int> getValues();
        void incrementLocalDepth();
        int creationTime;
    protected:

    private:

};

Bucket::Bucket()
{
    //ctor
}

Bucket::Bucket(int local_depth, int bucket_size)
{
    localDepth = local_depth;
    capacity = bucket_size;
}

multiset<int> Bucket::getValues(){
    return values;
}

void Bucket::display(){
    for(auto i : this->getValues()){
        cout << i << " " ;
    }
    cout << endl;
}

void Bucket::incrementLocalDepth(){
    localDepth++;
}

Bucket::~Bucket()
{
    //dtor
}

// ===========================THE DIRECTORY CLASS================================

class Directory
{
    public:
        Directory();
        Directory(int,int);
        virtual ~Directory();
        int getGlobalDepth();
        void setGlobalDepth(int);
        int currBuckets;
        map<int,Bucket*> buckets;
        vector<Bucket*> vec;
        vector<int> vec1;
        int calculateHash(int,int);
        void rearrangeBucketElements(Bucket);
        void insertElement(int);
        void displayBuckets();
        int handleFull(int);
        bool search_(int);
        void deleteElement(int);
        void deleteAdvanced(int);
        void displayVec();
        int currTime;

    protected:

    private:
        int globalDepth;
        int bucketSize;
};

Directory::Directory()
{
    //ctor
}

Directory::Directory(int global_depth,int bucket_capacity)
{
    currTime = 0;
    globalDepth=global_depth;
    bucketSize = bucket_capacity;
    for(int i=0;i<(1<<globalDepth);i++){
        Bucket * b = new Bucket(global_depth,bucket_capacity) ;
        b->creationTime = currTime++;
        buckets[i] = b;
        vec.push_back(b);
        vec1.push_back(i);
//        buckets.push_back(b);
    //    cout << "the bucket " << i <<  " has time " << buckets[i]->creationTime << " " << buckets[i]->localDepth << endl;
    }
}

int Directory::getGlobalDepth(){
    return globalDepth;
}

void Directory::setGlobalDepth(int n){
    globalDepth=n;
}

int Directory::calculateHash(int val, int depth){
    return val&((1<<depth)-1);
}

void Directory::insertElement(int val){
    int hashValue = calculateHash(val,globalDepth);
    cout << "inserting " << val << " " << hashValue  << endl;
    if(buckets[hashValue]->values.size()<bucketSize){
        buckets[hashValue]->values.insert(val);
        return;
    }

    // if the local depth is less than global depth
    if(buckets[hashValue]->localDepth < globalDepth){
        cout << "case 1 " << endl;
        int local_depth = buckets[hashValue]->localDepth;
        Bucket *A = new Bucket(local_depth+1,bucketSize);
        A->creationTime = currTime++;
        buckets[hashValue]->incrementLocalDepth();
        for(int i : buckets[hashValue]->getValues()){
            if(calculateHash(i,local_depth+1)!=hashValue){
                cout << "erasing " << i << " " << hashValue << endl;
                buckets[hashValue]->values.erase(i);
                A->values.insert(i);
            }
        }
        vec.push_back(A);
        for(int i : A->getValues()){
            cout << i << " " ;
        }
        cout << endl;
        int tmp;
        if(hashValue+(1<<local_depth)<(1<<globalDepth))
        {
            tmp = hashValue + (1<<local_depth);
        }else{
            tmp = hashValue - (1<<local_depth);
        }
        // for(int i=0;i<(1<<globalDepth);i++){
        //     if(calculateHash(i,globalDepth)!=hashValue)continue;
        //     if(calculateHash(i,local_depth+1)==hashValue){
        //         cout << "assigning A to " << i << endl;
        //         buckets[i] = A;
        //     }else if(calculateHash(i,local_depth+1)==tmp){
        //         buckets[i] = buckets[hashValue];
        //     }
        // }
        vec1.push_back((1<<local_depth)+hashValue);
        for(int i=tmp;i<(1<<globalDepth);i+=(1<<(local_depth+1))){
            buckets[i] = A;
        }
        for(int i=tmp;i>=0;i-=(1<<(local_depth+1))){
            buckets[i] = A;
        }
        // for(int i=hashValue;i<(1<<globalDepth);i+=(1<<(local_depth+1))){
        //     buckets[i] = A;
        // }
        // for(int i=hashValue;i>=0;i-=(1<<(local_depth+1))){
        //     buckets[i]=A;
        // }
    }
    else{
        // doubling the directory
        globalDepth++;
        int newHash = hashValue+(1<<(globalDepth-1));
        for(int i=(1<<(globalDepth-1));i<(1<<globalDepth);i++){
            if(i!=newHash){
                buckets[i] = buckets[i%(1<<(globalDepth-1))];
            }
        }
        // split this bucket into two
        Bucket *nH = new Bucket(globalDepth,bucketSize);
        nH->creationTime = currTime++;
        Bucket *hV = new Bucket(globalDepth,bucketSize);
        hV->creationTime = vec[hashValue]->creationTime;
        for(auto i : buckets[hashValue]->getValues()){
            if(calculateHash(i,globalDepth)!=hashValue){
                nH->values.insert(i);
            }else{
                hV->values.insert(i);
            }
        }
        vec[hashValue]=hV;
        vec.push_back(nH);
        vec1.push_back(newHash);
        buckets[hashValue]=hV;
        buckets[newHash]=nH;
    }
    // if(buckets[calculateHash(val,globalDepth)]->values.size()<bucketSize){
    //     buckets[calculateHash(val,globalDepth)]->values.insert(val);
    //     return;
    // }
    insertElement(val);
}

void Directory::displayBuckets(){
    cout << "global depth " << globalDepth<< endl; 
    for(int i=0;i<(1<<globalDepth);i++){
        cout << i << " : " ;
        for(auto j : buckets[i]->getValues()){
            cout << j << " " ;
        }
        cout << " local depth " << buckets[i]->localDepth << endl;
    }
}

bool Directory::search_(int val){
    int hashValue=calculateHash(val,globalDepth);
    for(auto i : buckets[hashValue]->values){
        cout << "checking " << i << endl;
        if(i==val){
            return true;
        }
    }
    return false;
}

void Directory::deleteElement(int val){
    if(search_(val)){
        int hashValue = calculateHash(val,globalDepth);
        buckets[hashValue]->values.erase(buckets[hashValue]->values.find(val));
        cout << "deleting " << val << endl;
    }else{
        cout << "the value " << val << " is not present "<< calculateHash(val,globalDepth) << endl;
    }
}

void Directory::deleteAdvanced(int val){
    if(search_(val)){
        int hashValue = calculateHash(val,globalDepth);
        deleteElement(val);
        if(buckets[hashValue]->values.size()==0){
            int ld = buckets[hashValue]->localDepth;
            if(ld<=1)return;
            if(hashValue<(1<<(globalDepth-1))){
                buckets[hashValue] = buckets[hashValue+(1<<(globalDepth-1))];
            }else{
                buckets[hashValue] = buckets[hashValue-(1<<(globalDepth-1))];
            }
            buckets[hashValue]->localDepth--;
        }
        // check if the directory can be halved
        for(int i=0;i<(1<<(globalDepth-1));i++){
            if(buckets[i]!=buckets[i+(1<<(globalDepth-1))])
            {
                return;
            }
        }
        // now we can halve the directory
        globalDepth--;
    }
}

void Directory::displayVec(){
    // for(int i=0;i<vec.size();i++){
    //     for(int j=i;j<vec.size();j++){
    //         if(buckets[j]->creationTime < buckets[i]->creationTime){
    //             swap(buckets[i],buckets[j]);
    //         }
    //     }
    // }
    cout << globalDepth << endl << vec.size() << endl;
    // for(int i=0;i<vec.size();i++){
    //     cout << vec[i]->getValues().size() << " " << vec[i]->localDepth << " " << vec[i]->creationTime << endl;
    //     for(int j : vec[i]->getValues()){
    //         cout << j << " ";
    //     }
    //     cout << endl;
    // }
    for(int i=0;i<vec1.size();i++){
        cout << vec1[i] << " " <<  buckets[vec1[i]]->getValues().size() << " " << buckets[vec1[i]]->localDepth << endl;
        for(auto j : buckets[vec1[i]]->getValues()){
            cout << j << " " ;
        }
        cout << endl;
    }
}

Directory::~Directory()
{
    //dtor
}

// ===========================THE MAIN PROGRAM================================
int main()
{

    int globalDepth,bucket_cap;
    cin >> globalDepth >> bucket_cap;
    Directory dir(globalDepth,bucket_cap);

    int currOp;
    while(cin >> currOp){
        switch(currOp){
            int number;
            case 1 : {
                dir.displayBuckets();
                break;
            }
            case 2 : {
                cin >> number;
                dir.insertElement(number);
                break;
            }
            case 3: {
                cin >> number;
                if(dir.search_(number)){
                    // cout << number << " is present" << endl;
                }else{
                    // cout << number << " is absent" << endl;
                };
                break;
            }
            case 4: {
                cin >> number;
                dir.deleteElement(number);
                // dir.deleteAdvanced(number);
                break;
            }
            case 5:{
                dir.displayVec();
                break;
            }
            case 6: {
                return 0;
            }
        }
    }
    return 0;
}