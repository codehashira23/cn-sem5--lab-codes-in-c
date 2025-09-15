// C program to implement Checksum 
 
#include<stdio.h>
#include<math.h>
 
int sender(int arr[10],int n)
{
    int checksum,sum=0,i;
    printf("\n---------SENDER SIDE---------\n");
    
    for(i=0;i<n;i++) sum+=arr[i];
    
    printf("SUM IS: %d",sum);
    checksum=~sum;    
    printf("\nCHECKSUM IS:%d",checksum);
    return checksum;
}

int reciever(int arr[10],int n , int sender_checksum){
    int checksum,sum=0,i;
    printf("\n---------Receciver's side --------\n");
    
    for(i=0;i<n;i++) sum+=arr[i];
    
    printf("sum is %d",sum);
    sum = sum + sender_checksum;
    checksum =~sum;
    printf("\nchecksum is %d\n",checksum);
}

 
void main()
{
    int n,sender_checksum,reciever_checksum;
    printf("\nENTER SIZE OF THE STRING:");
    scanf("%d",&n);
    int arr[n];
    printf("ENTER THE ELEMENTS OF THE ARRAY TO CALCULATE CHECKSUM:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    sender_checksum=sender(arr,n);
    reciever(arr,n,sender_checksum);
}