#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <time.h>
long long int Iteration;
void vruchnu(float **mass1,int n,int m);
void random(float **mass1,int n,int m);
void blur(float **mass1,int n,int m,float **mass2,int r);
void vyvid(float **mass1,int n,int m);
void vyvid_blur(float **mass2,int n,int m);
using namespace std;
int main(){
	int n,m;
	int r;
	char vidp;
	system("chcp 1251 & cls");
	do{
		cout << "Введіть розмірність матриці n=";
		cin >> n;
		cout << "m=";
		cin >> m;
		float **mass1= new float*[n];
		for(int ind=0;ind<n;ind++){
			mass1[ind]=new float[m];
		}
		float **mass2= new float*[n];
		for(int ind=0;ind<n;ind++){
			mass2[ind]=new float[m];
		}
		cout << "Введіть радіус r=";
		cin >> r;
		cout << "Задайте спосіб заповнення (vruchnu-вручну або random-випадково)";
		fflush(stdin);
		vidp=getchar();
		fflush(stdin);
		if(vidp=='V' || vidp=='v') vruchnu(mass1,n,m);
		else{random(mass1,n,m);
		/*vyvid(mass1,n,m);*/}
		blur(mass1,n,m,mass2,r);
		//vyvid_blur(mass2,n,m);
		cout << "\nОбробляти новий масив? (Yes-так)";
		fflush(stdin);
		vidp=getchar();
		cout << "\n";
		fflush(stdin);
		for(int ind=0;ind<n;ind++){
			delete [] mass1[ind];
		}
		for(int ind=0;ind<n;ind++){
			delete [] mass2[ind];
		}
	}
	while(vidp=='Y' || vidp=='y');
	system("pause");
	return 0;
}
void vruchnu(float **mass1,int n,int m){
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			cin >> mass1[i][j];
}
void random(float **mass1,int n,int m){
	int i,j;
	srand(time (0));
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			mass1[i][j]=rand()%100;
}
void blur(float **mass1,int n,int m,float **mass2,int r){
	int i,j,kil,max1,max2,max3,max4,seredne,x,y;
	double sum,clocks;
	clock_t start, end;
	start = clock();
	Iteration=0;
	if(r>=n && r>=m){ //радіус більше за розмір матриці
		sum=0;
		kil=0;
		for(x=0;x<n;x++){Iteration++;
			for(y=0;y<m;y++){
				sum+=mass1[x][y];kil++; Iteration++;
			}
		}
		seredne=sum/kil;
		for(i=0;i<n;i++){Iteration++;
			for(j=0;j<m;j++){
				mass2[i][j]=seredne; Iteration++;
			}
		}
	}
	else{
		//радіус менше за розмір матриці
		for(i=0;i<n;i++){
			for(j=0;j<m;j++){
				if(i-r<0){ //крайній рядок радіусу лежить поза матрицею
					max1=0;
					if(j-r<0){ //крайній стовпчик радіусу лежить поза матрицею
						max2=0;
						sum=0;
						kil=0;
						max3=i+r;
						max4=j+r;
						for(x=max1;x<=max3,x<n;x++){Iteration++;
							if(x>=0){
								for(y=max2;y<=max4;y++){
									if(y>=0 && y<m){sum+=mass1[x][y]; kil++;} Iteration++;
								}
							}
						}
						mass2[i][j]=sum/kil;
					}
					else{ //крайній стовпчик радіусу лежить всередині матриці
						sum=0;
						kil=0;
						max2=j-r;
						max3=i+r;
						max4=j+r;
						for(x=max1;x<=max3,x<n;x++){Iteration++;
							if(x>=0){
								for(y=max2;y<=max4;y++){
									if(y>=0 && y<m) {sum+=mass1[x][y];kil++;} Iteration++;
								}
							}
						}
						mass2[i][j]=sum/kil;
					}
				}
				else{ //крайній рядок радіусу лежить всередині матриці
					if(j-r<0){ //крайній стовпчик радіусу лежить поза матрицею
						max2=0;
						sum=0;
						kil=0;
						max1=i-r;
						max3=i+r;
						max4=j+r;
						for(x=max1;x<=max3,x<n;x++){Iteration++;
							if(x>=0){
								for(y=max2;y<=max4;y++){
									if(y>=0 && y<m) {sum+=mass1[x][y];kil++;} Iteration++;
								}
							}
						}
						mass2[i][j]=sum/kil;
					}

					else{ //стандартний випадок
						sum=0;
						kil=0;
						max1=i-r;
						max2=j-r;
						max3=i+r;
						max4=j+r;
						for(x=max1;x<=max3,x<n;x++){
							Iteration++;
							if(x>=0){
								for(y=max2;y<=max4;y++){
									if(y>=0 && y<m) {sum+=mass1[x][y];kil++;} Iteration++;
								}
							}
						}
						mass2[i][j]=sum/kil;
					}
				}
			}
		}
	}
	end = clock();
	printf("The above code block was executed in %.4f second(s)\n", ((double) end - start) / ((double) CLOCKS_PER_SEC));
	clocks= end - start;
	printf("Clocks=%.4f\n",clocks); 
	printf("Iterations=%.4lld\n",Iteration);
	cout << endl;
}
void vyvid(float **mass1,int n,int m){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++)
			printf("%5f ",mass1[i][j]);
		if(j==m) cout << "\n";
	}
}
void vyvid_blur(float **mass2,int n,int m){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			printf("%5f ",mass2[i][j]);
		}
		if(j==m) cout << "\n";
	}
}