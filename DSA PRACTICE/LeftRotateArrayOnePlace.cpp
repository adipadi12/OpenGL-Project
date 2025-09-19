#include<iostream>
#include<bits/stdc++.h>

using namespace std;

void leftRotateOnePlace(vector<int> arr, int n){

    if(n<=0){
        cout<<"Array is empty";
        return;
    }

    int temp = arr[0];
    // 1,2,34,5,65
    //2,34,5,65,1
    for(int i = 1; i<n; i++){
        arr[i - 1] = arr[i];
    }
    arr[n - 1] = temp;
    
    cout<<"The elementa in the rotated array are: ";
    for(int i=0; i<n; i++){
        cout<<arr[i]<<endl;
    }
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
    leftRotateOnePlace(arr, x);
    return 0;
}
