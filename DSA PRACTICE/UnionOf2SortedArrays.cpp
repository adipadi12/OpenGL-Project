#include<iostream>
#include<bits/stdc++.h>

using namespace std;

void UnionOf2SortedArrays(vector<int> arr1, vector<int> arr2, int n, int n2){
    vector<int> unionArr;
    //using set to avoid duplicates
    set<int> s;
    for(int i = 0; i<n; i++){
        s.insert(arr1[i]);
    }
    for (int i = 0; i < n2; i++)
    {
        s.insert(arr2[i]);
    }

    cout<<"The union of the 2 sorted arrays is: ";
    for(auto it : s)
    {
        unionArr.push_back(it);
        cout<<it<<endl;
    }
}

void UnionOf2SortedArraysOptimal(vector<int> arr1, vector<int> arr2, int n, int n2){
    vector<int> unionArr;
    //using set to avoid duplicates
    int i = 0, j = 0;
    while(i < n && j < n2){
        if(arr1[i] <= arr2[j]){
            if(unionArr.size() == 0 || unionArr.back() != arr1[i]) //to avoid duplicates
                unionArr.push_back(arr1[i]);
            i++;
        }
        else{
            if(unionArr.size() == 0 || unionArr.back() != arr2[j]) //to avoid duplicates along with checking if unionArr is empty
                unionArr.push_back(arr2[j]);
            j++;
        }
        
    }
    while (j<=n2)
        {
            if(unionArr.size() == 0 || unionArr.back() != arr2[j]) //to avoid duplicates
                unionArr.push_back(arr2[j]);
            j++;
        }
        while (i<=n)
        {
            if(unionArr.size() == 0 || unionArr.back() != arr1[i]) //to avoid duplicates
                unionArr.push_back(arr1[i]);
            i++;
        }
    cout << "The union of the 2 sorted arrays is: ";
    for(auto it : unionArr){
        cout<<it<<endl;}
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

    int y;
    cout << "Enter size of array2: ";
    cin >> y;
    vector<int> arr2(y);
    cout<<"Enter 10 elements in the array: ";
    for(int i=0; i<y; i++){
        cin>>arr2[i];
    }
    UnionOf2SortedArrays(arr, arr2, x, y);
    return 0;
}
