#include<iostream>
#include<bits/stdc++.h>
using namespace std;

bool isSorted(int arr[], int n){
    for(int i = 0; i<n-1; i++){
        if(arr[i]<arr[i+1]){
        }
        else{
            return false;
        }
    }
    return true;
}

int main(){
    int arr[4];
    cout<<"Enter 4 elements in the array: ";
    for(int i=0; i<4; i++){
        cin>>arr[i];
    }
    int n = sizeof(arr)/sizeof(arr[0]);
    cout<<"Is the array sorted? "<<(isSorted(arr, n) ? "Yes" : "No")<<endl;
    return 0;
}