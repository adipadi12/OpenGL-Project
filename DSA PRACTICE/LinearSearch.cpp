#include<iostream>
#include<bits/stdc++.h>

using namespace std;

void LinearSearch(vector<int> arr, int n){
    int x;
    cout << "Enter element to search: ";
    cin >> x;
    for(int i = 0; i<n; i++){
        if(arr[i] == x){
            cout<<"Element found at index "<<i<<endl;
            return;
        }
    }
    cout<<"Element not found"<<endl;
}

int main(){
    int x;
    cout << "Enter size of array: ";
    cin >> x;
    vector<int> arr(x);
    cout<<"Enter 10 elements in the array: ";
    for(int i=0; i<x; i++){
        cin>>arr[i];
    }
    LinearSearch(arr, x);
    return 0;
}
