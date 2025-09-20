#include<iostream>
#include<bits/stdc++.h>

using namespace std;

void MoveAllZerosToEnd(vector<int> arr, int n){
    vector<int> temp;
    for(int i = 0; i<n; i++){
        if(arr[i] != 0){
            temp.push_back(arr[i]); //adding non-zero elements to temp
        }
    }
    for(int i = 0; i< temp.size(); i++){
        arr[i] = temp[i]; //making arr elements same as temp
    }
    int non_zero = temp.size();
    for(int i = non_zero; i<n; i++){ //filling remaining elements with 0
        arr[i] = 0;
    }
    cout<<"The elements after moving all zeros to end are: ";
    for(int i=0; i<n; i++){
        cout<<arr[i]<<endl;
    }
}

void MoveAllZerosToEndOptimal(vector<int> arr, int n){
    vector<int> temp;
    //2 pointer approach
    int j = -1;
    for(int i = 0; i<n; i++){
        if(arr[i] == 0){
            j = i;
            break;
        }
    }
    for(int i = j + 1; i<n; i++){
        if(arr[i] != 0){
            swap(arr[i], arr[j]); //j always at a 0 and i iterating
            j++;
        }
    }
    cout<<"The elements after moving all zeros to end are: ";
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
    MoveAllZerosToEndOptimal(arr, x);
    return 0;
}
