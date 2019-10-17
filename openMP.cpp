#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


using namespace std;

int **m1;
int **m2;
int **r;
int i,j,k;

void multiplicacion_openMP(int TAM){

    omp_set_num_threads(4);

    #pragma omp parallel for private(i,j,k)
    for(int i=0; i<TAM; i++){
        for(int j=0; j<TAM; j++){
            *(*(r+i)+j) = 0;
            for(int k=0; k<TAM; k++){
                    *(*(r+i)+j) += *(*(m1+i)+k)  * *(*(m2+k)+j) ;
            }
        }
    }
}

void imprimir_matrices(int TAM){

    for (int i=0; i<TAM; i++){

        for (int j=0; j<TAM; j++){
            cout<<m1[i][j]<<"\t";
        }
        cout<<endl;
    }

    
    cout<<endl;
    for (int i=0; i<TAM; i++){

        for (int j=0; j<TAM; j++){
            cout<<m2[i][j]<<"\t";
        }
        cout<<endl;
    }

}

void imprimir_paralelo(int TAM){
    cout << endl
         << "Multiplicacion por hilos" << endl;
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++)
            cout << *(*(r+i)+j)  << " ";
        cout << endl;
    }
}

int main (int argc, char **argv)
{

  // argc es 3 = argv[0]nombre del programa,argv[1]TAM
    int TAM;
    TAM = strtol(argv[1], NULL, 10);

    


    //reservar memoria para la matriz dinamica
    m1 = new int*[TAM];//reservando memoria para las filas
    for (int i=0;i<TAM;i++){
        m1[i]= new int[TAM];//reservando memoria para las columnas
    }

    //reservar memoria para la matriz dinamica
    m2 = new int*[TAM];//reservando memoria para las filas
    for (int i=0;i<TAM;i++){
        m2[i]= new int[TAM];//reservando memoria para las columnas
    }

    //reservar memoria para la matriz dinamica
    r = new int*[TAM];//reservando memoria para las filas
    for (int i=0;i<TAM;i++){
        r[i]= new int[TAM];//reservando memoria para las columnas
    }

        //llenado
    for (int i=0; i<TAM; i++){

        for (int j=0; j<TAM; j++){
            *(*(m1+i)+j) =rand() % 10 + 1;
            *(*(m2+i)+j) =rand() % 10 + 1;
        }
    }

   double start_time = omp_get_wtime();

    //multiplicacion openMP
    multiplicacion_openMP(TAM);

    double time = omp_get_wtime()-start_time;
    cout<<endl<<time;
    int hilos = omp_get_num_threads();
    cout<<endl<<"NUMERO DE HILOS: "<<hilos<<endl;

    // imprimir_matrices(TAM);
    //imprimir_paralelo(TAM);
}
