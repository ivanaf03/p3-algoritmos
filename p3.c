//Iván Álvarez Fernández
//Marcos Gómez Tejón

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

struct nodo{
    int elem;
    int num_repeticiones;
    struct nodo *izq, *der;
};
typedef struct nodo *posicion;
typedef struct nodo *arbol;

static struct nodo *crearNodo(int e){
    struct nodo *p=malloc(sizeof(struct nodo));
    if(p==NULL){
        printf("memoria agotada\n");
        exit(EXIT_FAILURE);
    }
    p->elem=e;
    p->num_repeticiones=1;
    p->izq=NULL;
    p->der=NULL;
    return p;
}

arbol insertar(int e, arbol A){
    if(A==NULL){
        return crearNodo(e);
    } else if(e<A->elem){
        A->izq=insertar(e, A->izq);
    } else if(e>A->elem){
        A->der=insertar(e, A->der);
    } else{
        A->num_repeticiones++;
    }
    return A;
}

arbol crearArbol(){
    return NULL;
}

int esArbolVacio(arbol A){
    if(A==NULL){
        return 1;
    } else{
        return 0;
    }
}

posicion buscar(int i, arbol A){
    if(esArbolVacio(A)==1){
        return NULL;
    } else if(i==A->elem){
        return A;
    } else if(i<A->elem){
        return buscar(i, A->izq);
    } else{
        return buscar(i, A->der);
    }
}

arbol eliminarArbol(arbol A){
    if(esArbolVacio(A)==0){
        eliminarArbol(A->der);
        eliminarArbol(A->izq);
        free(A);
        A=NULL;
    }
    return A;
}

posicion hijoIzquierdo(arbol A){
    if(esArbolVacio(A->izq)==1){
        return NULL;
    } else {
        return A->izq;
    }
}

posicion hijoDerecho(arbol A){
    if(esArbolVacio(A->der)==1){
        return NULL;
    } else {
        return A->der;
    }
}

int elemento(posicion p){
    return p->elem;
}

int numeroRepeticiones(posicion p){
    if(p==NULL){
        return -1;
    } else {
        return p->num_repeticiones;
    }
}

static int max(int a, int b){
    if(a>b){
        return a;
    } else{
        return b;
    }
}

int altura(arbol A){
    if(esArbolVacio(A)==1){
        return -1;
    } else{
        return 1+max(altura(A->izq), altura(A->der));
    }
}

void visualizar(arbol A){
    if(esArbolVacio(A)==0){
        printf(" ( ");
        if(A->izq!=NULL){
            visualizar(A->izq);
        }
        printf("%i", A->elem);
        if(A->der!=NULL){
            visualizar(A->der);
        }
        printf(" ) ");
    } else{
        printf("()");
    }
}

void buscarTest(arbol A){
    int i;
    posicion p;
    for(i=1;i<=6;i++){
        p=buscar(i,A);
        if(p!=NULL) {
            printf("Busco %i y encuentro %i\n", i, elemento(p));
            printf("%i esta repetido %i veces\n", i, numeroRepeticiones(p));
        } else{
            printf("Busco %i y no encuentro nada\n", i);
        }
    }
}

void test(){
    arbol A=crearArbol();
    visualizar(A); printf("\n");
    printf("Inserto 3-1-2-5-4-5\n");
    A=insertar(3, A);
    A=insertar(1, A);
    A=insertar(2, A);
    A=insertar(5, A);
    A=insertar(4,A);
    A=insertar(5,A);
    visualizar(A); printf("\n");
    printf("La altura es %d\n",altura(A));
    printf("Busco 3-1-2-5-4-5\n");
    buscarTest(A);
    A=eliminarArbol(A);
    visualizar(A); printf("\n");
    printf("La altura es %d\n",altura(A));
}


void inicializar_semilla() {
    srand(time(NULL));
}

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return ((double)t.tv_usec + (double)t.tv_sec * 1000000.0);
}

int aleatorio(int n){
    int m=0-n;
    return ((rand()%(n-m+1)+m));
}




void cotas(int in[], int bq[], double vi[], double vb[]){
    int i,n;
    for(i=0, n=1000;n<=256000;i++,n=n*2){
        printf("%12d\t%12.3f\t%12.3f\n", n,vi[i], vb[i]);
    }
    printf("\n");
    printf("INSERCIÓN------------\n");
    for(i=0, n=1000;n<=256000;i++,n=n*2) {
        if (in[i]==1) {
            printf("%12d\t\t-\t\t-\t\t-\t\t-\n",n);
        } else {
            printf("%12d%15.3f%16.6f%16.6f%16.6f\n", n, vi[i], vi[i] /
            (pow(n, 1.12)),vi[i] / (pow(n, 1.26)), vi[i] / (pow(n, 1.5)));
        }
    }
    printf("\n");
    printf("BÚSQUEDA------------\n");
    for(i=0, n=1000;n<=256000;i++,n=n*2) {
        if (bq[i]==1) {
            printf("%12d\t\t-\t\t-\t\t-\t\t-\n",n);          
        } else {
            printf("%12d%15.3f%16.6f%16.6f%16.6f\n", n, vb[i], vb[i] /
             (pow(n, 1.12)), vb[i] / (pow(n, 1.28)), vb[i] / (pow(n, 1.5)));
        }
    }
}

void tiempos(){
    int i,n, m=0,v[256000],in[9],bq[9];
    double t1,t2,tx,t3,t4,ty, vi[9], vb[9];
    arbol A;
    for(n=1000;n<=256000;n=n*2) {
        A=crearArbol();
        for(i=0;i<n;i++){
            v[i]= aleatorio(n);
        }
        t1 = microsegundos();
        for (i=0;i<n;i++) {
            A = insertar(v[i], A);
        }
        t2 = microsegundos(); 
        tx = t2 - t1;
        if(tx<500){
        	in[m]=1;
        }else{
        	in[m]=0;
        }
        vi[m]=tx;
        for(i=0;i<n;i++){
            v[i]= aleatorio(n);
        }
        t3=microsegundos();
        for(i=0;i<n;i++){
            buscar(v[i], A);
        }
        t4=microsegundos();
        ty=t4-t3;
        if(tx<500){
        	bq[m]=1;
        }else{
        	bq[m]=0;
        }
        vb[m]=ty;
        eliminarArbol(A);
        m++;
    }
    cotas(in, bq, vi, vb);
}

int main(){
    inicializar_semilla();
    test();
    printf("\n");
    tiempos();
    return 0;
}



