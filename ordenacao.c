#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int comparacoes = 0;
int trocas = 0;

void resetContadores(){
    comparacoes = 0;
    trocas = 0;
}

void imprimirVetor(int v[], int n){
    printf("Estrutura atual: ");
    for(int i=0;i<n;i++)
        printf("%d ", v[i]);
    printf("\n");
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
    trocas++;
}

/* ---------------- Bubble Sort ---------------- */

void bubbleSort(int v[], int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            comparacoes++;
            if(v[j] > v[j+1]){
                swap(&v[j], &v[j+1]);
            }
        }
    }
}

/* ---------------- Selection Sort ---------------- */

void selectionSort(int v[], int n){
    for(int i=0;i<n-1;i++){
        int min = i;
        for(int j=i+1;j<n;j++){
            comparacoes++;
            if(v[j] < v[min])
                min = j;
        }
        if(min != i)
            swap(&v[i], &v[min]);
    }
}

/* ---------------- Insertion Sort ---------------- */

void insertionSort(int v[], int n){
    for(int i=1;i<n;i++){
        int chave = v[i];
        int j = i-1;

        while(j>=0){
            comparacoes++;
            if(v[j] > chave){
                v[j+1] = v[j];
                trocas++;
                j--;
            }else{
                break;
            }
        }
        v[j+1] = chave;
    }
}

/* ---------------- Quick Sort ---------------- */

int particiona(int v[], int inicio, int fim){
    int pivo = v[fim];
    int i = inicio-1;

    for(int j=inicio;j<fim;j++){
        comparacoes++;
        if(v[j] < pivo){
            i++;
            swap(&v[i], &v[j]);
        }
    }

    swap(&v[i+1], &v[fim]);
    return i+1;
}

void quickSort(int v[], int inicio, int fim){
    if(inicio < fim){
        int pi = particiona(v,inicio,fim);

        quickSort(v,inicio,pi-1);
        quickSort(v,pi+1,fim);
    }
}

/* ---------------- Merge Sort ---------------- */

void merge(int v[], int l, int m, int r){
    int n1 = m-l+1;
    int n2 = r-m;

    int L[n1], R[n2];

    for(int i=0;i<n1;i++) L[i]=v[l+i];
    for(int j=0;j<n2;j++) R[j]=v[m+1+j];

    int i=0,j=0,k=l;

    while(i<n1 && j<n2){
        comparacoes++;
        if(L[i] <= R[j]){
            v[k]=L[i];
            i++;
        }else{
            v[k]=R[j];
            j++;
        }
        trocas++;
        k++;
    }

    while(i<n1){
        v[k++]=L[i++];
    }

    while(j<n2){
        v[k++]=R[j++];
    }
}

void mergeSort(int v[], int l, int r){
    if(l<r){
        int m = (l+r)/2;

        mergeSort(v,l,m);
        mergeSort(v,m+1,r);
        merge(v,l,m,r);
    }
}

/* ---------------- Shell Sort ---------------- */

void shellSort(int v[], int n){
    for(int gap=n/2; gap>0; gap/=2){
        for(int i=gap;i<n;i++){
            int temp = v[i];
            int j;

            for(j=i; j>=gap; j-=gap){
                comparacoes++;
                if(v[j-gap] > temp){
                    v[j] = v[j-gap];
                    trocas++;
                }else{
                    break;
                }
            }

            v[j] = temp;
        }
    }
}

/* ---------------- Heap Sort ---------------- */

void heapify(int v[], int n, int i){
    int maior = i;
    int esq = 2*i+1;
    int dir = 2*i+2;

    if(esq<n){
        comparacoes++;
        if(v[esq] > v[maior])
            maior = esq;
    }

    if(dir<n){
        comparacoes++;
        if(v[dir] > v[maior])
            maior = dir;
    }

    if(maior != i){
        swap(&v[i], &v[maior]);
        heapify(v,n,maior);
    }
}

void heapSort(int v[], int n){

    for(int i=n/2-1;i>=0;i--)
        heapify(v,n,i);

    for(int i=n-1;i>0;i--){
        swap(&v[0],&v[i]);
        heapify(v,i,0);
    }
}

/* ---------------- MAIN ---------------- */

int main(){

    int vetor[MAX];
    int n=0;
    int total;
    int opcao;

    printf("Escolha o algoritmo:\n");
    printf("1 - Bubble Sort\n");
    printf("2 - Selection Sort\n");
    printf("3 - Insertion Sort\n");
    printf("4 - Quick Sort\n");
    printf("5 - Merge Sort\n");
    printf("6 - Shell Sort\n");
    printf("7 - Heap Sort\n");

    printf("Opcao: ");
    scanf("%d",&opcao);

    printf("\nQuantos valores deseja inserir? ");
    scanf("%d",&total);

    for(int i=0;i<total;i++){

        printf("\nDigite o valor: ");
        scanf("%d",&vetor[n]);
        n++;

        resetContadores();

        switch(opcao){
            case 1: bubbleSort(vetor,n); break;
            case 2: selectionSort(vetor,n); break;
            case 3: insertionSort(vetor,n); break;
            case 4: quickSort(vetor,0,n-1); break;
            case 5: mergeSort(vetor,0,n-1); break;
            case 6: shellSort(vetor,n); break;
            case 7: heapSort(vetor,n); break;
            default: printf("Opcao invalida\n");
        }

        imprimirVetor(vetor,n);

        printf("Comparacoes: %d\n",comparacoes);
        printf("Trocas: %d\n",trocas);
    }

    return 0;
}
