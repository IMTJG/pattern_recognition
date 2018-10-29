#include<iostream>
#include<cstdio>
#define MAX 1000
using namespace std;

double w[MAX][MAX];
double X[MAX][MAX];
int count;
int M;
int category;
int glas[MAX];

void input(){
}

void loadData_4k2()//从文件中读取数据
{
	M=3;
	category=4;
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

void loadData_leuk72()//从文件中读取数据
{
	M=40;
	category=3;
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

void Perceptor(double c){
    int k=0,i,j,r,num=0,cnt;
    int flag;
    double sum;
    i=0;
    while(1){
    		flag=0;
    		cnt=0;
    		for(r=0;r<category;r++){
    			sum=0;
    		    for(j=1;j<M+1;j++){
    		        sum+=w[r][j]*X[i][j];
			    }
			    if(glas[i]==r&&sum<=0){
			    	for(j=1;j<M+1;j++)
			    	    w[r][j]=w[r][j]+c*X[i][j];
			    	cout<<i<<endl;
			    	cnt++;
				}else if(glas[i]!=r&&sum>=0){
					for(j=1;j<M+1;j++)
			    	    w[r][j]=w[r][j]-c*X[i][j];
				}else{
					flag++;
				}
			    
			}
			if(flag==category){
			    num++;
			}
			else
			    num=0;
		cout<<"出错样本数量："<<cnt<<endl;	    
		for(r=0;r<category;r++){
		    for(k=1;k<M+1;k++)
			    cout<<w[r][k]<<"  "; 
			cout<<endl;
		}
		if(num==count)
		    break;
		i=(i+1)%count;
	}
}

int main(){
	int i,j;
	double c;
	
	//loadData_4k2();
	loadData_leuk72();
	 
	//初始化权向量
	for(i=0;i<category;i++)
	    for(j=0;j<M+1;j++)
	        w[i][j]=0;
	        
	//增广
    for(i=0;i<count;i++){
    	glas[i]=(int)X[i][0]-1;
	    X[i][M]=1;
	}
		
	cout<<"请输入参数: ";
	cin>>c;
	 
    Perceptor(c);
	 
	
	return 0;
}
