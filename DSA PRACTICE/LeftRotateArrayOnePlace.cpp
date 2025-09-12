#include<iostream>
#include<bits/stdc++.h>

using namespace std;

void largestElem(vector<int> arr, int n){

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
    int x;
    cout << "Enter size of array: ";
    cin >> x;
    vector<int> arr(x);
    cout<<"Enter 10 elements in the array: ";
    for(int i=0; i<x; i++){
        cin>>arr[i];
    }
    largestElem(arr, x);
    return 0;
}
