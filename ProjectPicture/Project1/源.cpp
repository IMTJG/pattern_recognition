#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<ctime>
#include<cmath>
#include<malloc.h>
#include"seqList.h"
#include "cv.h"
#include "highgui.h"

#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  

#define MAX 1000
#define random(a,b) (rand()%(b-a+1)+a)


using namespace std;
using namespace cv;

struct MyStruct
{
	int type;
	int num;
	double r;
	double g;
	double b;
	friend ostream& operator<<(ostream &out, MyStruct a);

};
ostream& operator<<(ostream &out, MyStruct a)
{
	out << a.num<<"   "<<a.b << "   " << a.g << "   " << a.r;
	return out;
}

CircList<MyStruct> L;

int M=3;
int cnt;
int point[MAX];
int point_num = 2;

Mat image = imread("280.jpg");



double distance(double a[], double b[]) {
	double sum = 0;
	int i;
	for (i = 1; i < M + 1; i++)
		sum += (a[i] - b[i])*(a[i] - b[i]);
	sum = sqrt(sum);
	return sum;
}

void max_min() {

	double Max = 0;
	double Min = 10000;
	int r,chu;
	int i, j, key, k;
	double D, D12;
	double a[MAX], b[MAX], c[MAX];

	//选取第一个聚类中心点 
	srand((unsigned)time(NULL));
	chu = random(0, cnt);
	point[0] = chu;
	MyStruct first;
	L.getData(chu, first);
	b[1] = first.b;
	b[2] = first.g;
	b[3] = first.r;
	first.type = 1;
	first.b = 0;
	first.g = 0;
	first.r = 0;
	L.setData(chu, first);
	cout << "第一个聚类中心：" << chu << endl;

	k = 0;
	//选出第二个聚类中心
	Max = 0;
	CircLinkNode<MyStruct> *h = L.getHead(),*q;
	q = h->link;
	while (q != NULL) {
			if (q->data.num != chu) {
				a[1] = q->data.b;
				a[2] = q->data.g;
				a[3] = q->data.r;
				D = distance(a, b);
				if (D >= Max) {
					Max = D;
					key = q->data.num;
				}
				
		}
			cout << k << endl;
			k++;
			q = q->link;
	}
	MyStruct second;
	L.getData(key, second);
	point[1] = key;
	second.type = 2;
	second.b = 255;
	second.g = 255;
	second.r = 255;
	L.setData(key, second);

	k = 0;
	q = h->link;
	//分类 
	while (q != NULL) {
		int index;
		index = q->data.num;
		MyStruct Third;
		L.getData(index, Third);
		c[1] = q->data.b;
		c[2] = q->data.g;
		c[3] = q->data.r;
		double distance1, distance2;
		distance1 = distance(a, c);
		distance2 = distance(b, c);
		if (distance1 < distance2) {
			Third.type = 2;
			Third.b = 255;
			Third.g = 255;
			Third.r = 255;
		}
		else {
			Third.type = 1;
			Third.b = 0;
			Third.g = 0;
			Third.r = 0;
		}
		L.setData(index, Third);
		q = q->link;
		cout << k << endl;
		k++;
	}	
}


int main() {
	 	
	if (image.empty()) {
		cout << "不能加载图像..." << std::endl;
		return -1;
	}
 	int height = image.rows;	
	int width = image.cols;	
	int channels = image.channels();	
	printf("height=%d,width=%d channels=%d\n", height, width, channels);

	int i, j, k=0;
	MyStruct Data;
	
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			
			Data.num = k;
			Data.type = 0;
			Data.b= image.at<Vec3b>(i, j)[0];
			Data.g = image.at<Vec3b>(i, j)[1];
			Data.r = image.at<Vec3b>(i, j)[2];
			L.inputRear(Data);
			cout << k << endl;
			k++;
		}
	}
	cnt = k;
	max_min();
	k = 0;
	CircLinkNode<MyStruct> *h = L.getHead(), *q;
	q = h->link;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			image.at<Vec3b>(i, j)[0]=q->data.b;
			image.at<Vec3b>(i, j)[1]=q->data.g;
			image.at<Vec3b>(i, j)[2]=q->data.r;
			q = q->link;
			cout << k << endl;
			k++;
		}
	}
	imwrite("src.jpg", image);
	imshow("src", image);
	waitKey(60000);
	return 0;
}
