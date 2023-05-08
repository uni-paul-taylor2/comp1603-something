#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#define MAXSET 1000
using namespace std;


//useless explorative block begin
void bin_READ(ifstream *fin, char *bucket, streamsize L){
	for(streamsize i=0;i<L;i++) (*fin) >>bucket[i];
}
void bin_WRITE(ofstream *fout, char *bucket, streamsize L){
	for(streamsize i=0;i<L;i++) (*fout) <<bucket[i];
}
//useless explorative block end



struct Account{
	int accNumber;
	double balance;
};
struct Node{
	Account *data;
	Node *next;
};
struct NODE{ //2 part C for testing
	int data;
	NODE *next;
};
struct SortedSet{ //3 for testing
	int numElements;
	int *elements;
};
NODE *createNODE(int data){ //2 part C for testing
	NODE *temp=(NODE*)malloc(sizeof(NODE));
	temp->data=data;
	temp->next=NULL;
	return temp;
}
void printList(NODE *top){ //2 part C for testing
	while(top!=NULL){
		cout<<top->data<<endl;
		top=top->next;
	}
	cout<<endl<<endl;
}
void insertionSort(int arr[], int size){ //3 for testing
	int i,j,temp;
	for(i=1;i<size;i++){
		for(j=i;j>0;j--){
			if(arr[j-1]>arr[j]){
				//then swap
				temp=arr[j];
				arr[j]=arr[j-1];
				arr[j-1]=temp;
			}
		}
	}
}
int binarySearch(int arr[], int length, int element){ //3 for testing
    int low=0, high=length-1, middle;
    while(low<=high){
    	middle=(low+high)/2;
        if(element>arr[middle]) low=middle+1;
        else if(element<arr[middle]) high=middle-1;
        else return middle;
    }
    return -1; //returned only if the target is not in the array.
}
void insertSS(SortedSet *ss, int key){ //3 for testing
	if(ss==NULL) return;
	if(ss->numElements>=MAXSET)
		(cerr<<"SortedSet got FULL, overflow\n", exit(1));
	ss->elements[(ss->numElements)++]=key;
	insertionSort(ss->elements,ss->numElements);
}
bool containsSS(SortedSet *ss, int key){ //3 for testing
	return binarySearch(ss->elements,ss->numElements,key)!=-1;
}
void displaySS(SortedSet *ss){
	for(int i=0;i<ss->numElements;i++)
		cout<<ss->elements[i]<<endl;
	cout<<endl;
}
SortedSet *copySS(SortedSet *ss){
	if(ss==NULL) return ss;
	SortedSet *clone=(SortedSet*)malloc(sizeof(SortedSet));
	clone->elements=(int*)malloc(MAXSET*sizeof(int));
	clone->numElements=ss->numElements;
	for(int i=0;i<ss->numElements;i++)
		clone->elements[i]=ss->elements[i];
	return clone;
}
//testing and given functions over



Node *createNode(int accNumber, double balance){ //1 part B i
	Account *a=(Account*)malloc(sizeof(Account));
	Node *n=(Node*)malloc(sizeof(Node));
	a->accNumber=accNumber;
	a->balance=balance;
	n->next=NULL;
	n->data=a;
	return n;
}
Node *insertList(Node *top, int accNumber, double balance){ //1 part B ii for testing
	Node *head=createNode(accNumber,balance);
	head->next=top;
	return head;
}
int sumSequence(int i, int N){ //2 part A
	if(i>N) return 0;
	return i+sumSequence(i+4,N);
}
int biggestChange(int A[], int n, int biggestSoFar){ //2 part B
	if(n<2) return biggestSoFar;
	int temp=A[n-1]-A[n-2];
	if(temp<0) temp*=-1;
	if(temp<biggestSoFar) temp=biggestSoFar;
	return biggestChange(A,n-1,temp);
}
NODE *deleteRange(NODE *top, int m, int n){ //2 part C
	if(top==NULL) return top;
	if(top->data>=m && top->data<=n){
		top->next=deleteRange(top->next,m,n);
		return top;
	}
	NODE *toReturn=deleteRange(top->next,m,n);
	free(top);
	return toReturn;
}
SortedSet *initSortedSet(){ //3 part A
	SortedSet *set=(SortedSet*)malloc(sizeof(SortedSet));
	set->elements=(int*)malloc(MAXSET*sizeof(int));
	set->numElements=0;
	return set;
}
SortedSet *initSortedSetFromFile(char filename[]){ //3 part B
	SortedSet *set=initSortedSet();
	ifstream fin(filename);
	if(!fin.is_open()) (cerr<<"File cannot be opened\n", exit(1));
	int temp;
	while(!fin.eof()){
		fin>>temp;
		if(!containsSS(set,temp)) insertSS(set,temp);
	}
	return set;
}
SortedSet *intersectionSS(SortedSet *ss1, SortedSet *ss2){ //3 part C
	SortedSet *set=initSortedSet();
	for(int i=0;i<ss1->numElements;i++)
		if(containsSS(ss2,ss1->elements[i]))  insertSS(set,ss1->elements[i]);
	return set;
}
SortedSet *unionSS(SortedSet *ss1, SortedSet *ss2){ //3 part D
	SortedSet *set=initSortedSet();
	for(int i=0;i<ss1->numElements;i++)
		if(!containsSS(set,ss1->elements[i]))  insertSS(set,ss1->elements[i]);
	for(int i=0;i<ss2->numElements;i++)
		if(!containsSS(set,ss2->elements[i]))  insertSS(set,ss2->elements[i]);
	return set;
}

int main(){
	char branchData[91]="Branch information goes here..Branch information goes here..Branch information goes here..";
	//above line for number 1 testing
	
	//1 part B ii
	Node *top=NULL;
	top=insertList(top,200,2000);
	top=insertList(top,100,1000);
	
	//1 part B iii
	ofstream fout("Accounts.dat",ios::binary|ios::out);
	if(!fout.is_open()) (cerr<<"File cannot be opened\n", exit(1));
	fout<<branchData; //put back useless bytes 0 through 89
	while(top!=NULL){
		fout.write((char*)&top->data->accNumber,sizeof(int));
		fout.write((char*)&top->data->balance,sizeof(double));
		cout<<top->data->accNumber<<'\t'<<top->data->balance<<endl; //line for testing
		top=top->next;
	}
	cout<<endl<<endl;
	fout.close();
	
	//1 part A
	ifstream fin("Accounts.dat",ios::binary|ios::in);
	if(!fin.is_open()) (cerr<<"File cannot be opened\n", exit(1));
	char *junk=(char*)malloc(90*sizeof(char));
	fin.read(junk,90); //read away useless bytes 0 through 89
	int *count=(int*)malloc(sizeof(int));
	int *acc=(int*)malloc(sizeof(int));
	double *bal=(double*)malloc(sizeof(double));
	*count=0;
	while(!fin.eof()){
		fin.read((char*)acc,sizeof(int));
		fin.read((char*)bal,sizeof(double));
		if(!fin.eof()) *count+=1; //surprisingly NOT redundant and NEEDED
	}
	fin.close();
	cout<<"Amount of accounts: "<<*count<<"\n\n";
	
	//2 part A
	cout<<endl<<sumSequence(1,1001)<<'\t'<<sumSequence(1,101)<<"\n\n";
	
	//2 part B
	int A[7]={90,91,100,120,110,101,95};
	cout<<biggestChange(A,7,0)<<"\n\n";
	
	//testing 2 part C
	NODE *list=createNODE(A[0]), *temp=list;
	for(int i=1;i<7;i++){
		temp->next=createNODE(A[i]);
		temp=temp->next;
	}
	printList(list); //before
	list=deleteRange(list,100,110);
	printList(list); //after
	
	//3 part E
	SortedSet *ss1=initSortedSetFromFile((char*)"SortedSet1.txt");
	SortedSet *ss2=initSortedSetFromFile((char*)"SortedSet2.txt");
	cout<<"Sorted Set 1:\n";
	displaySS(ss1);
	cout<<"Sorted Set 2:\n";
	displaySS(ss2);
	SortedSet *ss3=intersectionSS(ss1,ss2);
	SortedSet *ss4=unionSS(ss1,ss2);
	cout<<"Sorted Set 1 INTERSECT Sorted Set 2:\n";
	displaySS(ss3);
	cout<<"Sorted Set 1 UNION Sorted Set 2:\n";
	displaySS(ss4);
	
	return 0;
}
