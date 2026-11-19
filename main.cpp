#include<iostream>
using namespace std;
template <class T>
class List{
T arr[50];
int n;
public:
List(){
n=0;
}
void insert(T value){
if(n==50){
cout<<"List is full"<<endl;
return;
}
arr[n]=value;
n++;
}
void remove(T key){
int i;
for(i=0;i<n;i++){
if(arr[i]==key)
break;
}
if(i==n){
cout<<key<<" not found in list"<<endl;
return;
}
for(int j=i;j<n-1;j++){
arr[j]=arr[j+1];
}
n--;
cout<<key<<" deleted"<<endl;
}
void display(){
if(n==0){
cout<<"List is empty"<<endl;
return;
}
for(int i=0;i<n;i++)
cout<<arr[i]<<" ";
cout<<endl;
}
};
int main(){
cout<<"Aditya Raj"<<endl;
List<int> l1;
l1.insert(10);
l1.insert(20);
l1.insert(30);
cout<<"Int list : ";
l1.display();
l1.remove(20);
cout<<"Int list : ";
l1.display();
List<float> l2;
l2.insert(1.5);
l2.insert(2.5);
l2.insert(3.5);
cout<<"Float list : ";
l2.display();
l2.remove(2.5);
cout<<"Float list : ";
l2.display();
List<char> l3;
l3.insert('a');
l3.insert('b');
l3.insert('c');
cout<<"Char list : ";
l3.display();
l3.remove('d');
l3.remove('a');
cout<<"Char list : ";
l3.display();
}
