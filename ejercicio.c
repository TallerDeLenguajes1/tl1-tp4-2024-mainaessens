#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea{
    int tareaID; //numerico autoincremental comenzando en 1000
    char *descripcion; 
    int duracion; //entre 10 - 100
} typedef Tarea;

typedef struct Nodo{
    Tarea T; //dato
    struct Nodo *siguiente; //puntero al siguiente
}Nodo;

void insertarNodo(Nodo **Start, Tarea tarea); //AGREGAR TAREA
void cargarTareas(Nodo **tareas, int *proximoID);
void mostrarTareas(Nodo *lista, const char *titulo); 
void transferirTarea(Nodo **tareaPendiente, Nodo **tareaRealizada, int id);
void buscarNodo(Nodo *tareaPendiente, Nodo *tareaRealizada, int idBuscado);
void listarTareasPorPalabraClave(Nodo *tareaPendiente, Nodo *tareaRealizada, char *palabra); 
void eliminarNodo(Nodo *Start);
/*void insertarAlFinal(Nodo *Start, Nodo *nuevoNodo){
    Nodo *aux = Start; 
    while(aux->siguiente){
        aux = aux->siguiente;
    }
    aux->siguiente = nuevoNodo; 
}*/
/*void eliminarNodo(Nodo **Start, Tarea T){
    Nodo ** aux = Start; 
    //iteramos sobre la lista hasta encontrar el dato o alcanzar el final de la lista. 
    while (*aux != NULL && (*aux)->T != T){
        aux = &(*aux)->siguiente; 
    }
    //si encontramos el nodo con el dato especificado, lo eliminamos. 
    if(*aux){
        Nodo *temp = *aux; //guardamos el nodo a eliminar en una variable temporal. 
        *aux = (*aux)->siguiente; //desvinculamos el nodo de la lista. 
        free(temp); //liberamos la memoria ocupada por el nodo.
    }
}*/
/*Nodo quitarNodoPorID(Nodo **start, int ID){
    Nodo *actual = *start; 
    Nodo *anterior = *start; 

    while(actual != NULL && actual->T.tareaID != ID){
        anterior = actual; 
        actual = actual->siguiente; 
    }
    return *actual; 
}*/
/*void quitarNodo(Nodo **start, Nodo *nodoQuitar){
    Nodo ** aux = start; //iteramos sobre la lista hasta encontrar el dato o alcanzar el final de la lista. 
    while (*aux != NULL && (*aux)->T.tareaID != nodoQuitar->T.tareaID){
        aux = &(*aux)->siguiente; 
    } //si encontramos el nodo con el dato especificado, lo eliminamos. 
    if(*aux){
        Nodo *temp = *aux; //guardamos el nodo a eliminar en una variable temporal. 
        *aux = (*aux)->siguiente; //desvinculamos el nodo de la lista. 
        free(temp); //liberamos la memoria ocupada por el nodo.
    }
}*/
/*void InsertarNodos(Nodo **start, Nodo *nuevoNodo){
    nuevoNodo->siguiente = *start;
    *start = nuevoNodo; 
}*/

int main(){
    Nodo *tareaPendiente = NULL;
    Nodo *tareaRealizada = NULL; 

    int proximoID = 1000; 
    int opcion;
    int id, id2; 
    char *palabra;
    palabra = (char*)malloc(100*sizeof(char)); 

    printf("///////////////MODULO TO-DO///////////////"); 
    do {
        printf("\nMENU:\n");
        printf("1. Cargar tareas pendientes\n");
        printf("2. Transferir tarea de pendientes a realizadas\n");
        printf("3. Listar tareas pendientes y realizadas\n");
        printf("4. Consultar tarea por ID\n");
        printf("5. Consultar tarea por palabra clave\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                cargarTareas(&tareaPendiente,&proximoID);
                break;
            case 2:
                printf("\nINGRESE EL ID DE LA TAREA A TRANSFERIR: "); 
                scanf("%d",&id); 
                transferirTarea(&tareaPendiente,&tareaRealizada,id);
                //Nodo nodoQuitado = quitarNodoPorID(&tareaPendiente, id); 
                //InsertarNodos(&tareaRealizada,&nodoQuitado); 
                //quitarNodo(&tareaPendiente,&nodoQuitado); 
                break;
            case 3:
                mostrarTareas(tareaPendiente, "Tareas Pendientes");
                mostrarTareas(tareaRealizada, "Tareas Realizadas");
                break;
            case 4:
                printf("\nINGRESE EL ID DE LA TAREA A BUSCAR:"); 
                scanf("%d",&id2); 
                buscarNodo(tareaPendiente,tareaRealizada,id2);
                break;
            case 5:
                fflush(stdin); 
                printf("\nINGRESE LA PALABRA CLAVE A BUSCAR EN LA DESCRIPCION DE LAS TAREAS: ");
                fgets(palabra,100,stdin); 
                palabra[strcspn(palabra, "\n")] = 0; // Eliminar el salto de línea
                listarTareasPorPalabraClave(tareaPendiente,tareaRealizada,palabra);
                free(palabra); 
                break;
            case 6:
                break;
            default:
                printf("Opcion no valida. Por favor, seleccione una opcion valida.\n");
        }
    } while (opcion != 6);

    //libero memoria en estructuras (elimino nodos)
    eliminarNodo(tareaPendiente); 
    eliminarNodo(tareaRealizada); 

    return 0; 
}

void insertarNodo(Nodo **Start, Tarea tarea){ //AGREGAR TAREA
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo)); 
    nuevoNodo->T = tarea; 
    nuevoNodo->siguiente = *Start; 
    *Start = nuevoNodo; 
}

void cargarTareas(Nodo **tareas, int *proximoID){
    char opcion; 
    do {
        fflush(stdin); 
        Tarea nuevaTarea; 
        nuevaTarea.tareaID = (*proximoID)++; //incremento el valor almacenado en proximoID
        
        char buff[100]; 
        printf("\nIngrese la descripcion de la tarea: "); 
        fgets(buff,100,stdin);
        nuevaTarea.descripcion = (char *)malloc((strlen(buff) + 1) * sizeof(char)); 
        strcpy(nuevaTarea.descripcion, buff);

        do {
            printf("\nIngrese la duracion de la tarea (entre 10 y 100): "); 
            scanf("%d",&nuevaTarea.duracion); 
        } while (nuevaTarea.duracion < 10 || nuevaTarea.duracion > 100 );

        insertarNodo(tareas, nuevaTarea); 

        printf("¿Desea ingresar otra tarea? (s/n): "); 
        fflush(stdin); 
        scanf("%c", &opcion); 
    }while (opcion == 's' || opcion == 'S'); 
}

void mostrarTareas(Nodo *lista, const char *titulo){
    printf("\n%s: \n", titulo); 
    Nodo *actual = lista; 
    while (actual != NULL){ 
        printf("ID: %d, DESCRIPCION: %s, DURACION: %d\n", actual->T.tareaID,actual->T.descripcion,actual->T.duracion); 
        actual = actual->siguiente; 
    }
}

void transferirTarea(Nodo **tareaPendiente, Nodo **tareaRealizada, int id) {
    Nodo *actual = *tareaPendiente;
    Nodo *anterior = NULL;

    while (actual != NULL && actual->T.tareaID != id) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual != NULL) {
        Nodo *nodoTransferir = actual;

        if (anterior != NULL) {
            anterior->siguiente = actual->siguiente;
        } else {
            *tareaPendiente = actual->siguiente;
        }

        nodoTransferir->siguiente = *tareaRealizada;
        *tareaRealizada = nodoTransferir;
    } else {
        printf("No se encontro una tarea con ese ID en la lista de tareas pendientes");
    }
}

void buscarNodo(Nodo *tareaPendiente, Nodo *tareaRealizada, int idBuscado){
    Nodo *aux = tareaPendiente; 
    while(aux && aux->T.tareaID != idBuscado){
        aux = aux->siguiente;
    }
    if(aux != NULL){
        printf("Tarea encontrada en la lista de tareas pendientes: \n"); 
        printf("ID: %d, DESCIPCION: %s, DURACION: %d\n", aux->T.tareaID,aux->T.descripcion,aux->T.duracion);
    }else {
        aux = tareaRealizada; 
        while(aux && aux->T.tareaID != idBuscado){
        aux = aux->siguiente;
        }

        if(aux != NULL){
            printf("Tarea encontrada en la lista de tareas realizadas: \n"); 
            printf("ID: %d, DESCIPCION: %s, DURACION: %d\n", aux->T.tareaID,aux->T.descripcion,aux->T.duracion);
        }else {
            printf("No se encontro una tarea con ese ID. \n"); 
        }
    }
}

void listarTareasPorPalabraClave(Nodo *tareaPendiente, Nodo *tareaRealizada, char *palabra){
    Nodo *actual = tareaPendiente; 
    while (actual != NULL){
        if(strstr(actual->T.descripcion, palabra) != NULL){ //funcion para comparar si una palabra coincide con una frase
            printf("Tarea encontrada en la lista de tareas pendientes: \n"); 
            printf("ID: %d, Descripcion: %s, Duracion: %d\n", actual->T.tareaID, actual->T.descripcion, actual->T.duracion);
        }
        actual = actual->siguiente; 
    }

    actual = tareaRealizada; 
    while (actual != NULL){
        if(strstr(actual->T.descripcion, palabra) != NULL){ //funcion para comparar si una palabra coincide con una frase
            printf("Tarea encontrada en la lista de tareas realizadas: \n"); 
            printf("ID: %d, Descripcion: %s, Duracion: %d\n", actual->T.tareaID, actual->T.descripcion, actual->T.duracion);
        }
        actual = actual->siguiente; 
    }
}

void eliminarNodo(Nodo *Start){
    Nodo *aux = Start;  
    while (aux != NULL){
        Nodo *temp = aux; //guardamos el nodo a eliminar en una variable temporal. 
        aux = aux->siguiente; //desvinculamos el nodo de la lista. 
        free(temp->T.descripcion); //liberamos la memoria ocupada del puntero descripcion 
        free(temp); //liberamos la memoria ocupada por el nodo.
    }
}