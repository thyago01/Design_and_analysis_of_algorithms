#include <cmath>
#include <cstdlib>
#include <iostream>
#include <locale>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <ctype.h>

using namespace std;

vector<long> v_internal;
bool entropy = false;

long partition(vector<long>* v, long left, long right)
{

    long pivot = v->at(right);
    long aux;
    long i = left;

    for(long j = left; j < right; ++j)
    {

        if(v->at(j) <= pivot)
        {

            aux = v->at(j);
            v->at(j) = v->at(i);
            v->at(i) = aux;
            i++;

        }

    }

    v->at(right) = v->at(i);
    v->at(i) = pivot;

    return i;
}

void quicksort(vector<long>* v, long left, long right)
{

    if(left < right)
    {   

        long p = partition(v, left, right);
        quicksort(v, left, p-1);
        quicksort(v, p+1, right);

    }

}

void maxHeapify(vector<long>* v, int heapSize, long index)
{

    long left = (index+1) * 2 - 1;
    long right = (index+1)*2;
    long largest = 0;

    if(left < heapSize && v->at(left) > v->at(index))
    {
        largest = left;
    }
    else
    {
        largest = index;
    }

    if(right < heapSize && v->at(right) > v->at(largest))
        largest = right;

    if(largest != index)
    {

        long aux = v->at(index);
        v->at(index) = v->at(largest);
        v->at(largest) = aux;

        maxHeapify(v, heapSize, largest);
    }
}

void heapsort(vector<long>* v, int size)
{

    int heapSize = size;

    for(int i = (heapSize-1)/2; i >=0; --i)
        maxHeapify(v, heapSize, i);

    for(int i = size-1; i > 0; --i)
    {

        long aux = v->at(i);
        v->at(i) = v->at(0);
        v->at(0) = aux;

        --heapSize;
        maxHeapify(v, heapSize, 0);
    }
}

void insertionSort(vector<long>* v, int size)
{

    for(int i = 1; i < size; ++i)
    {
        int j = i;
        while(j > 0)
        {
            if(v->at(j-1) > v->at(j))
            {

                v->at(j-1) ^= v->at(j);
                v->at(j) ^= v->at(j-1);
                v->at(j-1) ^= v->at(j);

                --j;

            }
            else
            {
                break;
            }
        }
    }
}

void introsort(vector<long>* v, int size)
{

    long part_size = partition(v, 0, size-1);

    if(part_size < 16)
    {
        insertionSort(v, size);
    }
    else if(part_size > (2*log(size)))
    {
        heapsort(v, size);
    }
    else
    {
        quicksort(v, 0, size-1);
    }

}

void radixSort_num(vector<long>* v, int size)
{
    int j;
    long* v_aux = new long[size];

    for(long sft = 63; sft > -1; --sft)
    {

        j = 0;

        for(int i = 0; i < size; ++i)
        {

            bool mv = (v->at(i) << sft) >= 0;

            if(sft == 0 ? !mv : mv)
            {
                v->at(i-j) = v->at(i);
            }
            else
            {
                v_aux[j++] = v->at(i);
            }

        }
        for(int i = 0; i < j; i++)
        {
            v->at( (size-j)+i ) = v_aux[i];
        }
    }
    delete v_aux;
}

void countingSort(vector<long>* v, int size)
{
    int z = 0;
    int min = *min_element(v->begin(), v->end());
    int max = *max_element(v->begin(), v->end());
    int len = max - min + 1;

    int* v_aux = (int*)calloc(len, sizeof(int));

    for(int i = 0; i < size; i++)
        v_aux[ v->at(i) - min ]++;

    for(int i = min; i <= max; i++)
    {
        while(v_aux[i-min]-- > 0)
        {
            v->at(z) = i;
            ++z;
        }
    }
    delete v_aux;
}

size_t getMax(vector<string>* arr, int n)
{
    size_t max = arr->at(0).size();
    for (int i = 1; i < n; i++){
        if (arr->at(i).size()>max)
            max = arr->at(i).size();
    }
    return max;
}

void countSort(vector<string>* a, int size, size_t k)
{
    string *b = NULL; int *c = NULL;
    b = new string[size];
    c = new int[257];

    for (int i = 0; i <257; i++){
        c[i] = 0;
    }
    for (int j = 0; j <size; j++){
        c[k < a->at(j).size() ? (int)(unsigned char)a->at(j)[k] + 1 : 0]++;
    }

    for (int f = 1; f <257; f++){
        c[f] += c[f - 1];
    }

    for (int r = size - 1; r >= 0; r--){
        b[c[k < a->at(r).size() ? (int)(unsigned char)a->at(r)[k] + 1 : 0] - 1] = a->at(r);
        c[k < a->at(r).size() ? (int)(unsigned char)a->at(r)[k] + 1 : 0]--;
    }

    for (int l = 0; l < size; l++){
        a->at(l) = b[l];
    }

    delete[] b;
    delete[] c;
}

void radixSort(vector<string>* b, int r)
{
    size_t max = getMax(b, r);
    for (size_t digit = max; digit > 0; digit--)
    { 
        countSort(b, r, digit - 1);
    }
}

void Verifica_Ordena(vector<string>* v, int size)
{
    int sort = 0;
    int aux;
    v_internal.reserve(size);
 
    for(int i = 0; i < size; i++)
    {
       
        v_internal.push_back(atol(v->at(i).c_str()));
 
        if(i == size-1)
            break;
 
        if(atol(v->at(i).c_str()) <= atol(v->at(i+1).c_str()))
        {
            sort++;
        }
 
    }
    if(((float)sort/size)*100 > 80)
        entropy = true;
}

int main(void)
{
    int tam;
    string temp;
    cin >> tam;
    int a;
    vector<string> data;
    data.reserve(tam);
    while(cin>>temp)
    {
        data.push_back(temp);
    }
    Verifica_Ordena(&data, tam);
    
    set<long> conjunto (v_internal.begin(),v_internal.end());
    a = conjunto.size();
    float b = 100*(float)a/tam;
    if(isalpha(data[0][0])){
        radixSort(&data, tam);
        for (int i= 0; i < tam; i++) {
            cout<<data[i]<<endl;
            }
    }
    else{
        if(tam<=22)
        {
            insertionSort(&v_internal,tam);
            for (int i= 0; i < tam; i++) {
            cout<<v_internal[i]<<endl;
            }
            return -1;
        }
        else
        {
            if(b<=50)
            {
            countingSort(&v_internal,tam);
            for (int i= 0; i < tam; i++) {
            cout<<v_internal[i]<<endl;
            }
            return -1;
            }
            else
            {
                if(entropy==true)
                {
                    introsort(&v_internal,tam);
                    for (int i= 0; i < tam; i++) {
                    cout<<v_internal[i]<<endl;
                    }
                    return -1;
                }
                else
                {
                    radixSort_num(&v_internal,tam);
                    for (int i= 0; i < tam; i++) {
                    cout<<v_internal[i]<<endl;
                    }
                    return -1;
                }
            }
        }
    
    }
}
