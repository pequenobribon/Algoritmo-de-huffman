//Progrmama de Rojas de la Rosa Carlos Armando
//Algoritmo de cifrado de huffman

#include<iostream>
#include<string>

using namespace std;

string cadena;
string simbolos;
string codigo;
int numeroSimbolos = 0;

//Estructura de tipo nodo para almacenar los caracteres y las incidencias de cada caracter en una lista, después se usará como árbol
class nodo{
    public:
        char simbolo;
        int incidencias=0;
        nodo *siguiente;
        nodo *izq = 0;
        nodo *der = 0;
        string codigo;
}*p,*q,*sig,*arb,*aux;


void contarRepeticiones();
void recorrerLista(nodo *inicio);
void ordenarLista(nodo *inicio);
void llenarArbol(nodo *inicio);
void recorrerArbol(nodo *arbol, char caracter);

int main(){

    //cout<<"Ingresa una cadena:";
    //getline(cin,cadena,'\n');
    cadena = "algoritmo";
    contarRepeticiones();

    delete p;
    delete q;
    delete arb;
    delete sig;
    delete aux;

    return 0;
}

    void contarRepeticiones(){

        string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz .,";
        string frec;
        int contador;
        int i=0, j=0;

            while(i < alfabeto.length()){

                contador = 0;

                while(j < cadena.length()){

                    if(alfabeto[i] == cadena[j]){

                        contador ++;

                    }

                    j++;

                }
                //En esta parte se debe insertar el caracter y su frecuencia en la lista enlazada
                if(contador > 0 && p == 0){
                    simbolos += alfabeto[i];
                    p = new nodo;
                    p->simbolo = alfabeto[i];
                    p->incidencias = contador;
                    p->siguiente = 0;
                    numeroSimbolos++;
                }
                else if(contador > 0 && p != 0){
                    simbolos += alfabeto[i];
                    q = new nodo;
                    q->simbolo = alfabeto[i];
                    q->incidencias = contador;
                    q->siguiente = p;
                    p = q;
                    numeroSimbolos++;
                }

                i++;
                j = 0;
                frec += to_string(contador);
                frec +=" ";

            }

            cout<<"frecuencias"<<endl;
            cout<<frec<<endl;

            for(i = 0; i < alfabeto.length();i++){
                cout<<alfabeto[i]<<" ";
            }
            cout<<endl;


            cout<<"simbolos: "<<simbolos<<endl;
            cout<<"\n";

            ordenarLista(p);
            recorrerLista(p);

            llenarArbol(p);

            cout<<"\nrecorriendo arbol"<<endl;
            //for(int i = 0; i < numeroSimbolos; i++){
                recorrerArbol(q,simbolos[0]);
                cout<<endl;
            //}


    }

    void ordenarLista(nodo*inicio){

        cout<<"Ordenando lista"<<endl;
        q = inicio;
        int n;
        char c;
        aux = new nodo;

        while(q->siguiente != NULL){
            sig = q->siguiente;

            while(sig != NULL){
                if(q->incidencias > sig->incidencias){
                    //Esta parte realiza el movimiento del caracter y su numero de incidencia para ordenarlos
                    n = sig -> incidencias;
                    c = sig ->simbolo;

                    sig -> incidencias = q -> incidencias;
                    sig -> simbolo = q -> simbolo;

                    q -> incidencias = n;
                    q -> simbolo = c;
                    //Esta sección realiza el movimiento de los nodos hijos de la izquierda y la derecha para ordenarlos
                    aux->izq = sig->izq;
                    aux->der = sig->der;


                    sig ->izq = q->izq;
                    sig ->der = q->der;

                    q ->izq = aux->izq;
                    q ->der = aux->der;

                }
                //PRUEBA DE CAMBIO DE LUGAR DEL ÚLTIMO NODO CON EL PENULTIMO ---> si funciona
                if(q->incidencias == sig->incidencias && q->simbolo == '*' &&  sig->simbolo != '*'){
                    n = sig -> incidencias;
                    c = sig ->simbolo;

                    sig -> incidencias = q -> incidencias;
                    sig -> simbolo = q -> simbolo;

                    q -> incidencias = n;
                    q -> simbolo = c;
                    //Esta sección llena los nodos hijos de la izquierda y la derecha
                    aux->izq = sig->izq;
                    aux->der = sig->der;

                    sig ->izq = q->izq;
                    sig ->der = q->der;

                    q ->izq = aux->izq;
                    q ->der = aux->der;
                }
                sig = sig->siguiente;

            }
            q = q->siguiente;
            sig = q->siguiente;

        }

    }

    void recorrerLista(nodo*inicio){
        cout<<"Recorriendo la lista"<<endl;
        q = inicio;
        if(q->siguiente != NULL)
            sig = q->siguiente;
        while (q != 0){
            cout<<"simbolo:"<<q->simbolo<<" aparece:"<<q->incidencias<<endl;
        /*  if(q->simbolo != '*'){
                q->izq=0;
                q->der=0;
            }*/
            if(q->izq != 0){
               cout<<"IZQ:"<<q->izq->incidencias<<q->izq->simbolo<<endl;
            }
            
            if(q->der != 0){
               cout<<"DER:"<<q->der->incidencias<<q->der->simbolo<<endl;
            }

           q = q->siguiente;

        }

    }

    void llenarArbol(nodo *inicio){
        //aquí llenamos la info de los nodos del árbol

            q = inicio;

            while(q->siguiente != NULL){
                cout<<"\nInicial"<<endl;
                cout<<"n Actual:"<<q->incidencias<<endl;
                cout<<"simbolo actual:"<<q->simbolo<<endl;

                sig = new nodo;
                sig=q->siguiente;

                cout<<"Aux"<<endl;
                cout<<"n aux:"<<sig->incidencias<<endl;
                cout<<"simbolo aux:"<<sig->simbolo<<endl;

                arb = new nodo;

                arb->incidencias = q->incidencias + sig->incidencias;
                arb->simbolo = '*';

                if(q->incidencias < sig->incidencias){
                    arb->izq = q;
                    arb->der = sig;
                }
                else{
                    arb->izq = sig;
                    arb->der = q;
                }

                arb->siguiente=sig->siguiente;

                cout<<"Padre"<<endl;
                cout<<"n padre:"<<arb->incidencias<<endl;
              /*  cout<<"simbolo padre:"<<arb->simbolo<<endl;
                cout<<"izq:"<<arb->izq->simbolo<<endl;
                cout<<"der:"<<arb->der->simbolo<<endl;*/
                ordenarLista(arb);
                recorrerLista(arb);
                llenarArbol(arb);
            }
         }

    void recorrerArbol(nodo *arbol, char caracter){

        if(arbol == NULL){

            return;
        }

        else{
            cout<<arbol->simbolo<<"-";
            recorrerArbol(arbol->izq,caracter);
            recorrerArbol(arbol->der,caracter);
        }

    }

