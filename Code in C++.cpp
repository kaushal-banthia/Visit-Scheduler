#include <stdio.h>
#include <stdlib.h>

void schedule_visits(int arr[], int size, int a[], int b[], int good_array[], int *max_l, int max_b);
void swap(int *a, int *b);
void permute(int *arr, int start, int finish, int a[], int b[], int good_array[], int *max_l, int max_b);



int main()
{
    int max_l = 0, max_b = 0;

    FILE *f = fopen("input1.txt", "r");
    if (f == NULL)
        return -1;

    int n;
    fscanf(f, "%d", &n);//number of persons

    int a[n];
    int b[n];
    for (int i = 0; i < n; i++)
    {
        fscanf(f, "%d", &a[i]);
        fscanf(f, "%d", &b[i]);
        max_b = max_b>b[i]?max_b:b[i];
    }
    max_b*=60;
    for (int i = 0; i < n; i++)
    {
        a[i]*=60;
        b[i]*=60;
    }

    int arr[n];//for permuting the people
    for (int i = 0; i < n; i++)
    {
        arr[i] = i;
    }
    int good_array[n];
    permute(arr, 0, n-1, a, b, good_array, &max_l, max_b);

    FILE *writer = fopen("output1.txt", "w");

    int minute = max_l/60;
    int second = max_l%60;

    if (second < 10)
        fprintf(writer, "%d:0%d\n", minute, second);
    else
        fprintf(writer, "%d:%d\n", minute, second);

    for (int i = 0; i < n; i++)
    {
        fprintf(writer, "%d ", good_array[i]);
    }

    fclose(writer);
    fclose(f);
}

void schedule_visits(int arr[], int size, int a[], int b[], int good_array[], int *max_l, int max_b)
{
    //I have an array that has a predefined order
    int L[max_b];
    int max_l_for_this_pass = 0;
    for (int i = 0; i < max_b+1; i++)
    {
        L[i] = i;
    }

    //do binary search on L;

    int lb = 0;
    int ub = max_b;
    while(lb <= ub)
    {
        int flag = 1;
        int mid = (lb+ub)/2;
        //if L[mid] is answer then good and search for bigger values as well
        int start = a[arr[0]];
        for (int i = 1; i < size; i++)
        {
            start = a[arr[i]]>(start+L[mid])?a[arr[i]]:(start+L[mid]);
            if (start > b[arr[i]])
            {
                //this L doesnt work
                ub = mid-1;
                flag = 0;
                break;
            }
        }
        if (flag == 0)
        {
            continue;
        }
        else
        {
            max_l_for_this_pass = L[mid];
            lb = mid+1;
            continue;
        }
    }

    if (max_l_for_this_pass > *max_l)
    {
        *max_l = max_l_for_this_pass;
        for (int i = 0; i < size; i++)
        {
            good_array[i] = arr[i];
        }
    }
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

//permutation function
void permute(int *arr, int start, int finish, int a[], int b[], int good_array[], int *max_l, int max_b)
{
    if(start==finish)
    {
        schedule_visits(arr, finish+1, a, b, good_array, max_l, max_b);
        return;
    }
    for(int i = start; i <= finish; i++)
    {
        swap((arr+i), (arr+start));
        permute(arr, start+1, finish, a, b, good_array, max_l, max_b);
        swap((arr+i), (arr+start));
    }
}
