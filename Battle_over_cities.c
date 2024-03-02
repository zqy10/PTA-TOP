#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAXN 500
#define INF 1e7

typedef struct{
	int x;
	int y;
	int cost;
	int status;
}edge;

int pre[MAXN+1];
void init(int n){
	int i;
	for(i=1;i<=n;i++){
		pre[i]=i;
	}
}

int find(int x){
	if(pre[x] == x) return x;
	else return pre[x]=find(pre[x]);
}

int check(int x,int y){
	return find(x)==find(y);
}

int join(int x,int y){
	int xroot=find(x),yroot=find(y);
	if (xroot == yroot) return 0;
	else pre[yroot]=xroot;
	return 1;
}

//cmp in qsort
int cmp(const void *x,const void *y){
	return (*(edge*)x).cost - (*(edge*)y).cost;
}

int main(){
	int n,m;  //n cities, m roads
	scanf("%d %d",&n,&m);
	edge road[m],repair[m],temp;
	int i,j,road_p=0,repair_p=0;  
	for(i=0;i<m;i++){
		scanf("%d %d %d %d",&temp.x,&temp.y,&temp.cost,&temp.status);
		if(temp.status){
			road[road_p++] = temp;
		}else{
			repair[repair_p++] = temp;
		}
	}
	if(repair_p){
		//sort by repair cost
		qsort(repair,repair_p,sizeof(repair[0]),cmp);
	}
	int cost[MAXN+1]={0};
	int maxcost=0;
	
	//simulate every city's destruction
	for(i=1;i<=n;i++){
		init(n);
		
		//connect every useful road
		for(j=0;j<road_p;j++){
			if(road[j].x != i && road[j].y != i) join(road[j].x,road[j].y);
		}
		
		//simulate every solution
		for(j=0;j<repair_p;j++){
			//no need to repair the roads leading to the destroyed city
			if(repair[j].x != i && repair[j].y != i){
				if(check(repair[j].x,repair[j].y) == 0){ //if not connected
					join(repair[j].x,repair[j].y);
					cost[i]+=repair[j].cost;
				}
			}
		}
		
		int flag=0;
		for(j=1;j<=n;j++){
			if(pre[j]==j && j!=i){  //detect a map
				if(flag==0) flag=1;
				else if(flag==1){   //detect another map
					flag=2;
					break;
				}
			}
		}
		if(flag==2) cost[i]=INF; //cost infinite
		
		maxcost = (cost[i]>maxcost)?cost[i]:maxcost;
	}
	
	//output
	if(maxcost==0){
		printf("0");
		return 0;
	}
	int ans[50];
	int ans_p=0;
	for(i=1;i<=n;i++){
		if(cost[i]==maxcost){
			ans[ans_p++] = i;
		}
	}
	for(i=0;i<ans_p;i++){
		printf("%d%c",ans[i],(i==ans_p-1)?'\0':' ');
	} 
	return 0;
}








