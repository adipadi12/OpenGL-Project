#include<iostream>
#include<bits/stdc++.h>

using namespace std;

//Brute
int missingNumbers(vector<int> arr1, int n){
    for (int i = 1; i < n; i++)
    {
        int flag = 0;
        for(int j = 0; j < n-1; j++){
            if(arr1[j] == i){
                flag = 1;
                break;
            }
        }
        if (flag == 0){
            return i;

        }
    }
    
}

//hashmap
int missingNumbersBetter(vector<int> arr1, int n){
    vector<int> hash(n+1, 0);
    for(int i = 0; i < n-1; i++){
        hash[arr1[i]]++;
    }
    for(int i = 1; i <= n; i++){
        if(hash[i] == 0)
            return i;
}}

//optimal
int missingNumbersOptimalSum(vector<int> arr1, int n){
    int sum = (n * (n+1)) / 2;
    int s = 0;
    for(int i = 0; i < n-1; i++){
        s+=arr1[i];
    }
    return (sum - s); 
}

int missingNumbersOptimalXOR(vector<int> arr1, int n){
    int xor1 = 0;
    for(int i = 1; i <= n; i++){
        xor1 = xor1 ^ i;
    }
    int xor2 = 0;
    for(int i = 0; i < n-1; i++){
        xor2 = xor2 ^ arr1[i];
    }
    return (xor1 ^ xor2);
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
    cout << "Brute force missing number found " << missingNumbers(arr, x) << endl;
    cout << "better approach missing number found " << missingNumbersBetter(arr, x) << endl;
    cout << "Optimal approach with sum missing number found " << missingNumbersOptimalSum(arr, x) << endl;
    cout << "Optimal approach with XOR missing number found " << missingNumbersOptimalXOR(arr, x) << endl;


}
