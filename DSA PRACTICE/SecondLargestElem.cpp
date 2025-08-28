#include<iostream>
#include<bits/stdc++.h>

using namespace std;

void secondLargest(int arr[], int n){
    // if(n<=0){
    //     cout<<"Array is empty";
    //     return;
    // }

    // int largest = arr[0];

    // for(int i = 0; i<n; i++){
    //     if(arr[i]>largest){
    //         largest = arr[i];
    //     }
    // }

    // int secondLargest = -1;
    // for(int i = 0; i<n; i++){
    //     if(arr[i]>secondLargest && arr[i]!=largest){
    //         secondLargest = arr[i];
    //     }
    // }
    // cout<<"The second largest element in the array is: "<<secondLargest;
    /*above is the O(2N) method*/
    int largest = arr[0];
    int secondLargest = -1;
    for(int i = 0; i<n; i++){
        if(arr[i] > largest){
            secondLargest = largest;
            largest = arr[i];
        }
        else if(arr[i] > secondLargest && arr[i] != largest){
            secondLargest = arr[i];
        }
    }
    cout<<"The second largest element in the array is: "<<secondLargest<<endl;
}

void secondSmallest(int arr[], int n){
    int smallest = arr[0];
    int secondSmallest = INT_MAX;
    for(int i = 0; i<n; i++){
        if(arr[i] < smallest){
            secondSmallest = smallest;
            smallest = arr[i];
        }
        else if(arr[i] < secondSmallest && arr[i] != smallest){
            secondSmallest = arr[i];
        }
    }
    cout<<"The second smallest element in the array is: "<<secondSmallest<<endl;
}

int main(){
    int arr[10];
    cout<<"Enter 10 elements in the array: ";
    for(int i=0; i<10; i++){
        cin>>arr[i];
    }
    int n = sizeof(arr)/sizeof(arr[0]);
    secondLargest(arr, n);
    secondSmallest(arr, n);
    return 0;
}
