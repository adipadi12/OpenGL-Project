#include<iostream>
#include<bits/stdc++.h>

using namespace std;

void largestElem(int arr[], int n){

    if(n<=0){
        cout<<"Array is empty";
        return;
    }

    int largest = arr[0];

    for(int i = 0; i<n; i++){
        if(arr[i]>largest){
            largest = arr[i];
        }
    }
    cout<<"The largest element in the array is: "<<largest;

}
int main(){
    int arr[10];
    cout<<"Enter 10 elements in the array: ";
    for(int i=0; i<10; i++){
        cin>>arr[i];
    }
    int n = sizeof(arr)/sizeof(arr[0]);
    largestElem(arr, n);
    return 0;
}
