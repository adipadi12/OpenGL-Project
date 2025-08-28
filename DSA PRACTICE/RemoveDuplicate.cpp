#include<iostream>
#include<bits/stdc++.h>

using namespace std;

void removeDuplic(int arr[], int n){
    // set<int> st;
    // for(int i = 0; i<n; i++){
    //     st.insert(arr[i]);
    // }
    // int index = 0;
    // for(auto it: st){
    //     arr[index] = it;
    //     index++;
    // }
    // cout<<"Array after removing duplicates: ";
    // for(int i = 0; i<index; i++){
    //     cout<<arr[i]<<endl;;  
    // }
    /*brute force approach with set*/
    int i = 0;
    for (int j = 1; j < n; j++)
    {
        if(arr[j] != arr[i]){
            arr[i+1] = arr[j]; //if element in front not equal to current elemtn then then make the next element
            i++;
        }
    }
    cout << "this is size of new array " << i+1 << endl;
}
int main(){
    int arr[5];
    cout<<"Enter 5 elements in the array: ";
    for(int i=0; i<5; i++){
        cin>>arr[i];
    }
    int n = sizeof(arr)/sizeof(arr[0]);
    removeDuplic(arr, n);
    return 0;
}
