#include<bits/stdc++.h>
using namespace std;
/* lazy propagation 
1. update the node when you visit it
2. once you update ,propagate the updates downwards
*/
vector<int>a;

int marge(int x,int y){
    return x+y;
}
class seglaz{
    vector<int>seg,lazy;
    public:
    seglaz(int n) {
        seg.resize(4*n+1);
        lazy.resize(4*n+1);
    }
    void buildseg(int ind,int low,int high){
        if(low==high){
            seg[ind]=a[low];
            return ;
        }
        int mid=(low+high)/2;
        buildseg(2*ind+1,low,mid);
        buildseg(2*ind+2,mid+1,high);
        seg[ind]=marge(seg[ind*2+1],seg[ind*2+2]);
    }
    void update(int ind,int low,int high,int l,int r,int val){
        // update the previous remaining updates
        // and propagate downwords
        if(lazy[ind]!=0){
            seg[ind]+=(high-low+1)*lazy[ind];
            //propagates the lazy update downwords //for the remaining nodes to get updated
            if(low!=high){
                lazy[ind*2+1]+=lazy[ind];
                lazy[ind*2+2]+=lazy[ind];
            }
            lazy[ind]=0;
        }
        if(high<l or r<low) return; // no overlap,we don't anything and return // low high l r or l r low high
        if(low>=l && high<=r) { // complete overlap, l low high r
            seg[ind]+=(high-low+1)*val;
            // if a leaf node, it will have childrens
            if(low!=high){
                lazy[ind*2+1]+=val;
                lazy[ind*2+2]+=val;
            }
            return;
        }
        int mid=(low+high)/2;
        update(2*ind+1,low,mid,l,r,val);
        update(2*ind+2,mid+1,high,l,r,val);
        seg[ind]=marge(seg[ind*2+1],seg[ind*2+2]);
    }
    int query(int ind,int low,int high,int l,int r){
        // no overlap
        if(l>high || r<low) return 0;
        //complete overlap
        if(l>=low && r<=high) return seg[ind];
        // paritial overlap
        int mid =(low+high)>>1;
        int left =query(2*ind+1,low ,mid ,l,r);
        int right = query(2*ind+2,mid+1,high,l,r);
        return marge(left,right);
    }
};


int main(){

}