#include<iostream>
#include<bits/stdc++.h>

using namespace std;

int MaxConsecOnes(vector<int> arr, int n){
    int maxi = 0, cnt = 0;
    for(int i = 0; i<n; i++){
        if(arr[i] == 1){
            cnt++;
            maxi = max(maxi, cnt);
        }
        else{
            cnt = 0;
        }
    }
    return maxi;
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
    cout << "max number of ones are " << MaxConsecOnes(arr, x);
    return 0;
}
