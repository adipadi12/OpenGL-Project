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

void leftRotateDPlaces(vector<int> arr, int n){

    if(n<=0){
        cout<<"Array is empty";
        return;
    }


    cout << "Enter number of places to rotate: ";
    int d;
    cin >> d;
    vector<int> temp;

    for(int i = 0; i<d; i++){
        temp.push_back(arr[i]); //adding 1,2 to temp
    }

    //say d = 2
    // 1,2,34,5,65
    //34,5,65,1,2
    for(int i = d; i<n; i++){
        arr[i - d] = arr[i];
    } //shifting

    for(int i = n-d; i<n; i++){
        arr[i] = temp[i-(n-d)]; //adding 1,2 to end of array
    }    

    cout<<"The elementa in the rotated array are: ";
    for(int i=0; i<n; i++){
        cout<<arr[i]<<endl;
    }
}

void leftRotateDPlacesOptimal(vector<int> arr, int n){

    if(n<=0){
        cout<<"Array is empty";
        return;
    }


    cout << "Enter number of places to rotate: ";
    int d;
    cin >> d;
    vector<int> temp;

    //say d = 2
    // 1,2,34,5,65
    reverse(arr.begin(), arr.begin() + d); //2,1,34,5,65
    reverse(arr.begin() + d, arr.end()); //2,1,65,5,34
    reverse(arr.begin(), arr.end()); //34,5,65,1,

    cout<<"The elementa in the rotated array are: ";
    for(int i=0; i<n; i++){
        cout<<arr[i]<<endl;
    }
}
// reverse without STL
void reverseArray(vector<int> &arr, int start, int end){
    while(start < end){
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
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
    leftRotateDPlacesOptimal(arr, x);
    return 0;
}
