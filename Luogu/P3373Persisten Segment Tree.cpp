#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1e5+10;
int n,q,m;
int a[N];
int tot=0;
struct node{
	int l,r,sum,add,mult,ls=-1,rs=-1;
}tree[32*N];
int history[N];
int cnt=0;
int copy_node(int p){
	tree[++tot]=tree[p];
	return tot;
}
int new_node(int l,int r){
	++tot;
	tree[tot].l=l,tree[tot].r=r;
	tree[tot].add=0;
	tree[tot].mult=1;
	tree[tot].ls=-1;
	tree[tot].rs=-1;
	return tot;
}
void build(int p,int l,int r){
	int mid=(l+r)/2;
	tree[p].ls=new_node(l,mid);
	tree[p].rs=new_node(mid+1,r);
}
void down(int p){
	int i=tree[p].add%m;
	if(tree[p].l==tree[p].r){
		tree[p].add=0,tree[p].mult=1;
		return;
	}
	if(tree[p].ls==-1){
		build(p,tree[p].l,tree[p].r);
	}
	int ls=tree[p].ls,rs=tree[p].rs;
	tree[ls].sum=(tree[p].mult*tree[ls].sum)%m;
	tree[rs].sum=(tree[p].mult*tree[rs].sum)%m;
	tree[ls].add=(tree[p].mult*tree[ls].add+i)%m;
	tree[rs].add=(tree[p].mult*tree[rs].add+i)%m;
	tree[ls].mult=(tree[p].mult*tree[ls].mult)%m;
	tree[rs].mult=(tree[p].mult*tree[rs].mult)%m;
	tree[ls].sum+=i*(tree[ls].r-tree[ls].l+1)%m;
	tree[rs].sum+=i*(tree[rs].r-tree[rs].l+1)%m;
	tree[p].add=0;
	tree[p].mult=1;
}
int up_mult(int p,int l,int r,int k){
	k%=m;
	p=copy_node(p);
	if(tree[p].l>=l&&tree[p].r<=r){
		tree[p].sum=(tree[p].sum*k)%m;
		tree[p].mult=(tree[p].mult*k)%m;
		tree[p].add=(tree[p].add*k)%m;
		return p;
	}
	down(p);
	int ls=tree[p].ls,rs=tree[p].rs;
	int mid=(tree[p].l+tree[p].r)/2;
	if(l<=mid) tree[p].ls=up_mult(ls,l,r,k);
	if(r>mid) tree[p].rs=up_mult(rs,l,r,k);
	ls=tree[p].ls,rs=tree[p].rs;
	tree[p].sum=(tree[ls].sum+tree[rs].sum)%m;
	return p;
}
int up_add(int p,int l,int r,int k){
	k%=m;
	p=copy_node(p);
	if(tree[p].l>=l&&tree[p].r<=r){
		tree[p].sum=(tree[p].sum+(k*(tree[p].r-tree[p].l+1))%m)%m;
		tree[p].add=(tree[p].add+k)%m; 
		return p;
	}
	down(p);
	int ls=tree[p].ls,rs=tree[p].rs;
	int mid=(tree[p].l+tree[p].r)/2;
	if(l<=mid) tree[p].ls=up_add(ls,l,r,k);
	if(r>mid) tree[p].rs=up_add(rs,l,r,k);
	ls=tree[p].ls,rs=tree[p].rs;
	tree[p].sum=(tree[ls].sum+tree[rs].sum)%m;
	
	//cout<<p<<' '<<tree[p].l<<' '<<tree[p].r<<' '<<k<<' '<<tree[p].sum<<endl;
	
	return p;
}
int ask(int p,int l,int r){
	if(tree[p].l>=l&&tree[p].r<=r){
		return (tree[p].sum)%m;
	}
	down(p);
	int mid=(tree[p].l+tree[p].r)/2;
	int ans=0;
	int ls=tree[p].ls,rs=tree[p].rs;
	if(l<=mid) ans=(ans+ask(ls,l,r))%m;
	if(r>mid) ans=(ans+ask(rs,l,r))%m;
	return ans;
}
signed main(){
	cin>>n>>q>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	history[++cnt]=new_node(1,n);
	for(int i=1;i<=n;i++){
		int qq=up_add(history[cnt],i,i,a[i]);
		history[++cnt]=qq;
	}
	while(q--){
		int op,x,y,k;
		cin>>op;
		if(op==1){
			cin>>x>>y>>k;
			int qq=up_mult(history[cnt],x,y,k);
			history[++cnt]=qq;
		}else if(op==2){
			cin>>x>>y>>k;
			int qq=up_add(history[cnt],x,y,k);
			history[++cnt]=qq;
		}else{
			cin>>x>>y;
			cout<<ask(history[cnt],x,y)<<"\n";
		}
	}
	return 0;
}
