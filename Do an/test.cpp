#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#define max 20
void DocFile(char *tenfile, int a[max][max], int &n){
	ifstream fin (tenfile);
	int i,j,s;
	fin>>n;
	for(i=1;i<=n;i++)
	for(j=1;j<=n;j++)
	{
		fin>>s;
		 a[i][j]=s;
	}
	
	fin.close();
}
void InMTK(int a[max][max], int n){
	cout<<"\n*Ma tran ke:"<<endl;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout<<a[i][j]<<" ";
		}
   		cout<<endl;
	}
}
/*void dfs(int a[max][max],int s, int t,int n)
{
	int stack[max],u,v,top,truoc[max];
	top=-1;
	for (int i=1;i<=n;i++)
	{
		stack[i]=0;
		truoc[i]=0;
	}
	stack[top++]=s;
	while (top!=-1)
	{
		u=stack[--top];
		tham[i]=0;
		for(int i=1;i<=n;i++)
		{
			if(a[u][i]!=0&&tham[i]==0)
			{
				stack[top++]=i;
				tham[i]=1;
			}
		}
	}
}
/*int f=0;
void DFS1(int i,int a[max][max],int tham[], int n,int b[]){
	cout<<i<<" ";
	
	f++;
	b[f]=i;
	tham[i]=1;
	for(int j=1;j<=n;j++)
		if(a[i][j]!=0&&tham[j]==0) DFS1(j,a,tham,n,b);
}
void DFS(int a[max][max], int n){
	int tham[max],i,k,b[max];
	for(i=1;i<=n;i++) tham[i]=0;
	//for(i=1;i<=n;i++)
	DFS1(1,a,tham,n,b);
	cout<<endl;
	/*if(tham[i]==0) */
	/*{
	for(k=1;k<=n;k++) tham[k]=0;
	DFS1(i,a,tham,n);
	cout<<endl;
	}
	for(int i=1;i<=n;i++)
	{
		cout<<b[i]<<" ";
	}
}*/

/*void BFS(int a[max][max],int n, int t, int s)
{

	int queue[max],d,c,tham[max],truoc[max],cd;
	cd=d=c=0;
	int u,v;
	for(int i=1;i<=max;i++)tham[i]=0;
	queue[c++]=s;//tham[1]=1;
	while(d!=c)
	{
		u=queue[d++];tham[u]=0;
		//tham[s]=1;
		//cout<<u<<" ";
		for(v=1;v<=n;v++)
		{
			if(a[u][v]!=0&&tham[v]==0)
			{
				tham[v]=1;
				truoc[v]=u;
				//cout<<truoc[v]<<" "<<v<<endl;
				cd=cd+a[u][v];
				tham[v]=1;
				queue[c++]=v;
				if(v==t)
				{
					int stack[max],top,k;
					k=t;
					top=-1;
					stack[top++]=k;
					do 
					{
						tham[k]=0;
						k=truoc[k];
						//tham[k]=0;
						stack[top++]=k;
					} while(k!=s);
					while(top!=-1)
					{
						cout<<stack[--top]<<"  ";
					}
					cout<<endl;
				}
			}
		}
	}
	//cout<<cd;
}*/
/*void BFS1(int i,int n, int a[max][max], int tham[]){  
	int queue[max],d,c;
	d=c=0; queue[c++]=i; tham[i]=1;
	while( d!=c) {
		i=queue[d++]; cout<<i;
		for( int j=1;j<=n;j++)
			if (tham[j]==0&&a[i][j]==1){  
				queue[c++]=j; 
				tham[j]=1;
			}
	}
}
int tham[max];
void BFS(int a[max][max],int n){
	for (int i=1;i<=n;i++)  tham[i]=0;
	for (int i=1;i<=n;i++)	if (tham[i]==0)  
		BFS1(i,n,a,tham);
}*/
/*void xdeny(int a[max][max],int s, int t, int n)
{
	int d,c,queue[max],v,u,tham[max];
	int truoc[max]={0};
	tham[max]={0};
	d=c=0;
	queue[c++]=s;
	while(c!=d)
	{
		u=queue[d++]; tham[u]=1;
		for(v=1;v<=n;v++)
		{
			if(a[u][v]!=0&&tham[v]==0)
			{
				queue[c++]=v;
				truoc[v]=u;
				cout<<u<<" "<<v<<"\n";
			
				/*if(u==t)
				{
					int stack[max],top;
					top=-1;
					do 
					{
						u=truoc[u];
						stack[top++]=u;
					} while(u!=s);
					while(top!=-1)
					{
						cout<<stack[top--]<<"  ";
					}
					cout<<endl;
				}
			}
		}
	}
}*/
/*int tratruoc(int i,int truoc[max])
{
	if(truoc[i]==0) 
	{	
		return i;
	}
	tratruoc(truoc[i],truoc);
}
void dfsxdeny(int a[max][max], int s, int t,int n)
{
	int stack[max],top,u,v,tham[max],truoc[max];
	for(int j=1;j<=max;j++) 
	{
		tham[j]=0;
		truoc[j]=0;
	}

	top=-1;
	stack[top++]=s;
	while(top!=-1)

	{
	
		u=stack[--top]; tham[u]=1;
	//	cout<<u;
		for (int i=n;i>=0;i--)
		{
			if(a[u][i]!=0&&tham[i]==0)
			{
				stack[top++]=i;
				truoc[i]=u;
				cout<<i<<" "<<truoc[i]<<endl;
				if(tratruoc(5,truoc)==1)
				{
					cout<<"1"<<endl;
				}
				/*if(i==t)
				{
					int m=i;
					int stack1[max];
					int stop=-1;
					while(m!=0)
					{
						stack1[stop++]=m;
						m=truoc[m];
					}
					while(stop!=-1)
					{
						cout<<stack1[--stop]<<" ";
					}
					

					cout<<endl;
				}
				//a[u][i]=0;
			
				
			}
		}
		
		//cout<<1;
		tham[u]=0;//phong 3->2->5
		//cout<<endl;
	}
}*/
/*void dfsxy(int a[max][max],int s, int t,int tham[max],int truoc[max], int n)
{
	tham[s]=1;
	for(int i=1;i<=n;i++)
	{
		if(a[s][i]!=0&&tham[i]==0)
		{
			truoc[i]=s;
			dfsxy(a,i,t,tham,truoc,n);
			if(i==t)
			{
				int stack[max],top,u,v;
				top=-1;
				u=i;
				do
				{
					stack[top++]=u;
					u=truoc[u];
				}while(u!=0);
				while(top!=-1)
				{
					cout<<stack[--top]<<" ";
				}
				cout<<endl;
			}
			tham[i]=0;
			
		}
	}
}*/
void DFS1(int i,int tham[],int a[max][max], int n);
int kiemtralienthong(int a[max][max],int n)//kiem tra xem G co 1 thành ph?n hay nhieu tp;
{
	int tham[max],br[max],sxbr[max];
	int stplt=0;
	int temp=0;
	for (int i=1;i<=n;i++)  tham[i]=br[i]=sxbr[i]=0;
	for(int k1=1;k1<=n;k1++)
	{
		sxbr[k1]=k1;
		for(int k2=1;k2<=n;k2++)
		{
			if(a[k1][k2]!=0)
			{
				br[k1]++;
			}
		}
	}
	for(int n1=1;n1<=n;n1++)
	{
		cout<<"br["<<n1<<"]"<<br[n1]<<endl;
	}
	for(int c1=1;c1<=n-1;c1++)
	{
		for(int c2=c1+1;c2<=n;c2++)
		{
			if(br[c1]<br[c2])
			{
				int temp1=br[c1];
                br[c1]=br[c2];
                br[c2]=temp1;
                temp=sxbr[c1];
                sxbr[c1]=sxbr[c2];
                sxbr[c2]=temp;
                //cout<<br[c1]<<" "<<br[c2]<<endl;
                //system("pause");
			}
		}
	}
		for(int n1=1;n1<=n;n1++)
	{
		if(tham[sxbr[n1]]==0)
		{
			for(int j1=1;j1<=n;j1++)
				{
					if(tham[sxbr[j1]]==1&&a[sxbr[n1]][sxbr[j1]]!=0)
					{
						int ltn1[max],ltj1[max];
						for(int t1=1;t1<=n;t1++) ltn1[t1]=ltj1[t1]=0;
						for(int z1=1;z1<=n;z1++)
						{
							if(tham[sxbr[z1]]==1)
							{
								DFS1(sxbr[z1],ltn1,a,n);
								if(ltn1[sxbr[j1]]==1)
								{
									for(int z2=1;z2<=n;z2++)ltn1[z2]=0;
									cout<<sxbr[n1]<<" "<<sxbr[z1]<<" day la 2 dinh chay dfs tim co gap nhau hay ko ";system("pause");
									DFS1(sxbr[n1],ltn1,a,n);ltn1[sxbr[n1]]=0;cout<<"dinh nay loai bo:"<<sxbr[n1];system("pause");
									
									DFS1(sxbr[z1],ltj1,a,n);
									//for(int hk=1;hk<=n;hk++) cout<<ltj1[hk]<<" ";
									//cout<<endl;system("pause");
									//cout<<sxbr[n1]<<" "<<sxbr[z1]<<endl;
									//system("pause");
									int stop=0;
									for(int ss=1;ss<=n;ss++)
										{
											cout<<"kiem tra day: "<<ltn1[ss]<<"<>"<<ltj1[ss]<<endl;
											if(ltn1[ss]!=ltj1[ss])
												{
													stop=1;
													//cout<<stop;
													//system("pause");
													//break;
												}
										
													if(ltn1[ss]==ltj1[ss]&&ltj1[ss]==1)
													{
														
														cout<<"tham["<<ss<<"]"<<"=0"<<endl;
														tham[ss]=0;
													}
										}
									if(stop==0)
										{
											stplt--;
											cout<<"datru 1"<<endl;
											//for(int i=1;i<=n;i++) tham[sxbr[i]]=0;
										}
								}
							}
						}

						
					}
				}
				
			stplt++;
			cout<<sxbr[n1]<<" "<<stplt; system("pause");
			//cout<<sxbr[n1]<<endl;
			DFS1(sxbr[n1],tham,a,n);
		}
	}
	/*int v=1;
	for(v=1;v<=n;v++)
	{
		if(tham[v]==0)
		{
			//DFS1(v,tham,G);
			for(int m=1;m<=n;m++)
			{
				if(tham[m]==1&&a[v][m]!=0)
				{
					for(int j1=1;j1<=n;j1++)
					{
						if(tham[j1]==1&&a[v][j1]!=0)
						{
							stplt--;
						}
					}
						//tham[v]=1;
						//cout<<v;
						for(int i=1;i<=n;i++) tham[i]=0;
						//stplt=0;						
						break;
				}
			}
			stplt++;
			DFS1(v,tham,a,n);
		}
	}*/
return stplt;

}
//xoa 1 dinh
/*int dinhtru1(int a[max][max],int n,int vitri)
{
	int bd=kiemtralienthong(a,n);
	cout<<bd;
	for(int i=1;i<=n;i++)
	{
		if(a[vitri][i]!=0)
		{
			a[vitri][i]==0;
		}
		else {
			if(a[i][vitri]!=0)
			{
				a[i][vitri]==0;
			}
		}
	}
	// cap nhat ten voi tao do lai
	for(int a1=vitri;a1<n;a1++)
	{
		for(int a2=1;a2<=n;a2++)
		{
			a[a1][a2]=a[a1+1][a2];
			//G.MTTS[a2][a1]=G.MTTS[a2][a1+1];
		}
	}
	//thay doi cot
	for(int a1=1;a1<=n;a1++)
	{
		for(int a2=vitri;a2<n;a2++)
		{
			a[a1][a2]=a[a1][a2+1];
			//G.MTTS[a2][a1]=G.MTTS[a2][a1+1];
		}
	}
	n--;
	cout<<kiemtralienthong(a,n);
	InMTK(a,n);
	if(bd<kiemtralienthong(a,n))
	{
		return 1;
	} 
	return 0;
}
//tim dinh tru
void dinhtru(int a[max][max],int n)
{
	int c[max][max],d;
	//d=n;
	for(int m=1;m<=n;m++)
	for(int x=1;x<=n;x++) c[m][x]=a[m][x];
	for(int i=1;i<=n;i++)
	{
		
		for(int m=1;m<=n;m++)
		for(int x=1;x<=n;x++) a[m][x]=c[m][x];
		cout<<dinhtru1(a,n,i)<<endl;
		
	}
}
//kiem tra canh cau
// tim canh cau
void canhcau(int a[max][max],int n)
{
	int ts=0;
	int bd=kiemtralienthong(a,n);
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
		{
			ts=a[i][j];
			a[i][j]=0;
			if(bd<kiemtralienthong(a,n))
			{
				cout<<"canh cau"<<endl;
				cout<<i<<" "<<j<<endl;
			}
			a[i][j]=ts;
		}
	}
}*/
void DFS1(int i,int tham[],int a[max][max], int n){// dung cai nay de kiem tra nhanh n co 1 thanh phan hay nhieu tp
	int top=0;
	int b[max];
	b[top++]=i;
	tham[i]=1;
	while(top!=0)
	{
		i=b[--top];	
	//	cout<<i<<" ";
		for(int k=n;k>=1;k--)
		{
			if(a[i][k]!=0&&tham[k]==0)
			{
				tham[k]=1;
				b[top++]=k;
				//break;
			}
		}
	}
}
/*void Dijkstra(int a[max][max], int n, int s, int t)
{
	int tham[max],truoc[max];
	int d[max];
	for(int k=1;k<=n;k++) tham[k]=0;
	DFS1(t,tham,a,n);
	if (tham[s]==1)
	{
			for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				{
					if (a[i][j]==0)
					{
						a[i][j]=10000;
					}
					tham[i]=0;
				}		
		//khoi tao truoc
		for (int i=1;i<=n;i++)
		{
			d[i]=a[t][i];truoc[i]=t;
		}
		tham[t]=1;
		// duyet tim duong di ngan nhat
		for(int m=1;m<=n-1;m++)
		{
			int temp=10000;
			int c;
			int u=0;
			for (c=1;c<=n;c++)
			{
				if(tham[c]==0&&d[c]<temp)
				{
					u=c;temp=d[c];
				}
			}
			tham[u]=1;
			if(u==s)
			{
				break;
			}
			for (int v=1;v<=n;v++)
			{
				if(tham[v]==0&&d[v]>d[u]+a[u][v])
				{
					d[v]=d[u]+a[u][v];truoc[v]=u;
				}
			}
		}
		// dem duong di nho nhat ra
		int z=s;
		int stack[max];
		int top=-1;
		stack[top++]=s;
		do
		{
			s=truoc[s];
			stack[top++]=s;
		}while(s!=t);
		while(top!=-1)
		{
			cout<<stack[--top];
		}
		cout<<endl;
		cout<<"chieu dai la : "<<d[z];
		
	}
	else  {
		cout<<"KHONG CO DUONG DI TU "<<t<<" den "<<s<<"\n";
	}

}
void xuatEULER(int b[max],int m)
{
	for(int z=1;z<=m;z++)
	{
		cout<<b[m]<<" ";
	}
	cout<<endl;
}
void DDELUER(int a[max][max],int b[max], int m,int n,int i)// thuat toan nay co nhiem vu de quy tim ra duong di euler
{
	int l=0;// co nhiem vu luu lai trong so
	for(int j=1;j<=n;j++)
	{
		if(a[b[i-1]][j]!=0)// tai sao b-1 vi b day co nhiem vu nhu 1 mang truoc nhu stack luu lai cac dinh da qua
		{
			//cout<<b[i-1]<<" "<<j<<" "<<a[b[i-1]][j];
			//system("pause");
			b[i]=j;
			cout<<"b["<<i<<"]"<<"="<<j;
			system("pause");
			l=a[b[i-1]][j];//luu lai trong so lat tra ve nhu cu khi noa quay lui
			a[b[i-1]][j]=0;// danh dau no khi da di qua tuc cho no ve 0
			if(i==m)
			{
				for(int k=0;k<=m;k++)
				{
					cout<<b[k]<<" ";
				}
				a[b[i-1]][j]=l;
				cout<<endl;
			} 
			else {
				DDELUER(a,b,m,n,i+1);// de quy tim dinh ke tiep theo
			 	a[b[i-1]][j]=l;//tra lai trong so neu quay lui				
			}
		}
	}
}
void Euler(int a[max][max],int n)
{
	if(kiemtralienthong(a,n)==1)// kiem tra do thi co 1 thanh phan lien thong moi co the tim euler duoc
	{
		int m=0;// m la so canh cua do thi
		int b[max];
		for(int i=1;i<=n;i++)
		{
			//b[i]=0;
			for(int j=1;j<=n;j++)
				{
					if(a[i][j]!=0)m++;
				}
		}
		for(int u=1;u<=n;u++)
		{
			b[0]=u;
			cout<<b[0];
			system("pause");
			DDELUER(a,b,m,n,1);
		}
	}
	else
	{
		cout<<"/ndo thi khong co do thi euler";
	}
}*/
int main(){
	int a[max][max]; int n;
	DocFile("F:\\dfs.txt",a,n);
	InMTK(a,n);
	/*int tham[max],truoc[max],s,t;
	for (int i=1;i<=max;i++)
	{
		truoc[i]=0;
		tham[i]=0;
	}
	t=4;
	s=2;*/
	
	//dfsxy(a,s,t,tham,truoc,n);
	//xdeny(a,1,2,n);
	//cout<<"Thu tu tham theo BFS:";
	//DFS(a,n);
	//cout<<"\n";
	//BFS(a,n,4,2);
	//dfsxdeny(a,2,4,n);
	//Dijkstra(a,n, 3, 1);
	//cout<<endl;
	system("pause");
	//dinhtru(a,n);
	//canhcau(a,n);
//	Euler(a,n);
cout<<	kiemtralienthong(a,n);
	return 0;
	
}

