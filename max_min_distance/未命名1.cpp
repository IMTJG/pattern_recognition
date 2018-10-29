#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<ctime>
#include<cmath>
#include<malloc.h>
#define MAX 1000

using namespace std;

int M;
double X[MAX][MAX];
int count;
int point[MAX];
double Dis[MAX][MAX];
double category[MAX];
int point_num=2;

double m[MAX];//所有的最小距离
int minindex[MAX];//各点到某个聚类中心距离最小  

void input(){
	M=2;
	int i=0,j,data;
	cout<<"请输入样本：\"0 0\" "<<endl;
	while(1){
		scanf("%lf%lf",&X[i][1],&X[i][2]);
		if(X[i][1]==999&&X[i][2]==999)
		    break;
		i++;
	}
	count=i;
}

double distance(double a[],double b[]){
	double sum=0;
	int i;
	for(i=1;i<M+1;i++)
	    sum+=(a[i]-b[i])*(a[i]-b[i]);
	sum=sqrt(sum);
	return sum;
}

void max_min(double p){
	
	double Max=0;
    double Min=10000;
	int r;
	int i,j,key,k;
	double D,D12;
	double a[M],b[M],c[M];
	point[0]=0;//选取第一个点作为聚类中心点 
	Max=0;
	for(i=0;i<count;i++){
		if(i!=0){
			for(j=1;j<M;j++){
				a[j]=X[i][j];
				b[j]=X[0][j];
			}
			D=distance(a,b);
			if(D>=Max){
				Max=D;
				key=i;
			}
		}
	}
	point[1]=key;//选出第二个聚类中心 
    D12=Max;
    D=Max;

    //继续寻找聚类中心 
    while(D>p*D12){
	    for(i=0;i<count;i++){
	    	for(k=0;k<point_num;k++){
			    for(r=1;r<M;r++){
		    	    a[r]=X[i][r];
		    	    b[r]=X[point[k]][r];
			    }
			Dis[i][point[k]]=distance(a,b);
            }
           
			Min=10000;
			for(k=0;k<point_num;k++){
		 		if(Dis[i][point[k]]<Min){
		 			Min=Dis[i][point[k]];
		 			minindex[i]=k;
				 }
		    }
		    m[i]=Min;
	    } 
	    
		Max=0;
	    for(i=0;i<count;i++){
	    	if(m[i]>Max){
	    		Max=m[i];
	    		key=i;
			}
		}
		if(Max>p*D12){
			point[point_num]=key;
			point_num++;
		}
		D=Max;   
			
	}
    
	for(i=0;i<count;i++){
		category[i]=minindex[i];
		//cout<<category[i]<<"  ";
	} 
}


void loadData_4k2()//从文件中读取数据
{
	M=3;
	int i=0,j=0; 
	FILE *fp;
	if((fp=fopen("4k2_far.txt","r"))==NULL)    fprintf(stderr,"cannot open data.txt!\n");
	for(i=0;i<MAX;i++){
	    for(j=0;j<M;j++){
		    fscanf(fp,"%lf",&X[i][j]); 
		}
		if(feof(fp))
		    break;
	} //读取数据点		
	count=i;
	
	fclose(fp);
}

void loadData_lris()//从文件中读取数据
{
	M=4;
	int i=0,j=0; 
	char ch1,ch2,ch3,ch4;
	char str[20];
	FILE *fp;
	if((fp=fopen("lris.txt","r"))==NULL)    fprintf(stderr,"cannot open data.txt!\n");
	for(i=0;i<MAX;i++){
		    fscanf(fp,"%lf%c%lf%c%lf%c%lf%c%s",&X[i][1],&ch1,&X[i][2],&ch2,&X[i][3],&ch3,&X[i][4],&ch4,str); 
		    if(str=="Iris-setosa")
		        X[i][0]=1;
		    else if(str=="Iris-versicolor")
		        X[i][0]=2;
		    else if(str=="Iris-virginica")
		        X[i][0]=3;
		    //cout<<X[i][1]<<"   "<<X[i][2]<<"   "<<X[i][3]<<"   "<<X[i][4]<<"   "<<str<<endl;
		if(feof(fp))
		    break;
	} //读取数据点		
	count=i;
	
	fclose(fp);
} 

void loadData_leuk72_3k()//从文件中读取数据
{
	M=40;
	int i=0,j=0; 
	FILE *fp;
	if((fp=fopen("leuk72_3k.txt","r"))==NULL)    fprintf(stderr,"cannot open data.txt!\n");
	for(i=0;i<MAX;i++){
	    for(j=0;j<M;j++){
		    fscanf(fp,"%lf",&X[i][j]); 
		}
		if(feof(fp))
		    break;
	} //读取数据点		
	count=i;
	
	fclose(fp);
} 

void loadData_wine()//从文件中读取数据
{
	M=14;
	int i=0,j=0; 
	FILE *fp;
	char ch;
	if((fp=fopen("wine.txt","r"))==NULL)    fprintf(stderr,"cannot open data.txt!\n");
	for(i=0;i<MAX;i++){
	    for(j=0;j<M;j++){
		    fscanf(fp,"%lf%c",&X[i][j],&ch); 
		    
		    //cout<<X[i][j]<<"   ";
		}
		//cout<<endl;
		if(feof(fp))
		    break;
	} //读取数据点		
	count=i;
	
	fclose(fp);
} 

void output(){
	cout<<"共有"<<count<<"个样本"<<endl;
	cout<<"共分为"<<point_num<<"类"<<endl; 
	int i;
	for(i=0;i<count;i++)
	    cout<<X[i][0]<<"   "<<category[i]+1<<endl;
}

void storeData(char *str,double p){
	FILE *fp;
	if((fp=fopen(str,"w"))==NULL) {
		printf("File cannot be opened/n");
		exit(0);
	}
	fprintf(fp,"参数为：%lf\n",p);	
	fprintf(fp,"共分成%d类\n",point_num);
	int i;
	for(i=0;i<count;i++)
	    fprintf(fp,"%.0lf   %.0lf\n",X[i][0],category[i]+1);//写入文件    
	fclose(fp);
}

int main(){
	double p;
	int i;	
	int choice;
	while(1){
		cout<<endl;
		cout<<"0-----退出"<<endl;
		cout<<"1-----手动输入"<<endl;
		cout<<"2-----读取4k2_far.txt"<<endl;
		cout<<"3-----读取lris.txt"<<endl;
		cout<<"4-----读取leuk72_3k.txt"<<endl;
		cout<<"5-----读取wine.txt"<<endl;
		cout<<endl;
		cin>>choice;
		switch(choice){
			case(0):exit(0);break;
			case(1):input();cout<<"请输入参数：";cin>>p;max_min(p);output();break;
			case(2):loadData_4k2();cout<<"请输入参数：";cin>>p;max_min(p);storeData("4k2_result.txt",p);output();break;
			case(3):loadData_lris();cout<<"请输入参数：";cin>>p;max_min(p);storeData("lris_result.txt",p);output();break;
			case(4):loadData_leuk72_3k();cout<<"请输入参数：";cin>>p;max_min(p);storeData("leuk_result.txt",p);output();break;
			case(5):loadData_wine();cout<<"请输入参数：";cin>>p;max_min(p);storeData("wine_result.txt",p);output();break;
			default:break;
		}
	}
	return 0;
}
