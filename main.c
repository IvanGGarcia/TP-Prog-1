#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char nombre_ingrediente [20];
    float cantidad;                      /// en kg o en litro
    char tipo [20];                      /// "liquido" o "solido "
    float costo;                         /// costo por kg o por litro
} stockIngrediente;

typedef struct
{
    char nombre_preparacion[20];
    int cantidad;                        ///por unidad, no hay por peso
} Preparacion;

typedef struct
{
    char nombre_ingrediente[20];
    float cantidad;                     ///puede ser en litro o en kg
} IngredienteXReceta;

typedef struct
{
    char nombre_preparacion[20];
    IngredienteXReceta ingredientes[20]; ///Puede tener hasta 20 ingredientes
    int cantIngredientes;                ///los validos de ingredientes
} Receta;


typedef struct
{
    char nombre_preparacion[20];
    int cantidad; ///por unidad, no hay por peso
} PreparacionVenta;

typedef struct
{
    char nombre_preparacion[20];
    int cantidad;
} PedidoPreparacion;

typedef struct
{
    int idVenta;
    PedidoPreparacion items_pedido[20]; ///puedo pedir hasta 20 items
    int cantItems; ///los validos del arreglo de items_pedido
    float valor_total; ///valor total a pagar
    int cancelado;
} Venta;

typedef struct
{
    char nombre_preparacion[20];
    float precio_venta; ///precio por unidad
} PrecioPreparacion;




///prototipado
void lecturaIngredientes (stockIngrediente [], int *);
void muestraIngredientes (stockIngrediente [], int );
void muestraDemanda (Preparacion [], int );
void lecturaPreparacion (Preparacion [], int *);
void lecturaRecetas (Receta [], int *, IngredienteXReceta[]);
void muestraRecetas (Receta[],IngredienteXReceta[], int, stockIngrediente [], float []);
void descuentaIngredientes (Receta[], IngredienteXReceta  [], int, Preparacion [],stockIngrediente[], int  []);
void cantPreparados (Preparacion  [], int validos, int [], PreparacionVenta[]);
void modificaArchivoIngredientes (stockIngrediente [], int);
void traerStock (PreparacionVenta [], int * );
void muestraStock (PreparacionVenta [], int );
int cantStock ();
void muestraVentas(Venta [], int );
void traerVenta (Venta [], int * );
float calculoVenta (Venta[], int );
int cantVentas ();
float calculoCostos (float [], Venta[], int, stockIngrediente []);
void CargarPrecios (PrecioPreparacion  [], Receta [], int );
void muestraPrecios (PrecioPreparacion  [], int );
void persistenciaPrecios (PrecioPreparacion [], int );
void CambioPrecio (PrecioPreparacion [], Receta [], int );
void NuevaVenta (PreparacionVenta [], Venta [], PrecioPreparacion[], int *, int );
void MuestraVentas (Venta[], int );
void CancelaVenta (Venta[], int );
void MuestraCanceladas (Venta[], int);






int main()
{
    ///variables
    int validos, validosV = 0;
    int validosStock = 0;
    int validosVentas = 0;
    float ingreso, costo, ganancia;


    int opcionMenu;
    char continuar;

    int cantMaxPedido [30][30];
    float costoRecetas [30];

    stockIngrediente listaIngredientes [30];
    IngredienteXReceta ingXRece [30];
    Preparacion demanda [30];
    Receta recetas [30];
    PreparacionVenta preparaciones [30];
    Venta ventas [30];
    PrecioPreparacion Precios [20];





    ///menu
    do
    {
        printf("\n\n\t----------------------------------------------------------------\n");
        printf("\t\t\tBIENVENID@ A LA PANADERIA DEL BARRIO!\n\t\t\t    Atendida por sus propietarios:\n\t\t\t\t Dominguez, Axel.\n\t\t\t\t Garcia, Ivan.\n");
        printf("\t----------------------------------------------------------------\n\n\n");
        printf("\n\nQue parte del proceso desea ver?\n\n1.INGRESO DE MATERIA PRIMA.\n2.COCINANDO LOS PREPARADOS.\n3.VENTA AL PUBLICO.\n4.RESUMEN DEL DIA.\n5.SALIR\n");
        scanf("%i", &opcionMenu);
        system("cls");

        switch (opcionMenu)
        {
        case  1 :
            printf("\n\n\t\tINGRESO DE MATERIA PRIMA.\n");
            printf("Esta es su lista de ingredientes.");
            lecturaIngredientes(listaIngredientes, &validos);
            muestraIngredientes(listaIngredientes, validos);
            system ("pause");
            system("cls");
            break;
        case  2 :
            do
            {
                printf("\n\n\t--------------------------------\n");
                printf("\n\t   COCINANDO LOS PREPARADOS");
                printf("\n\n\t--------------------------------\n");
                printf("\n\nQue parte del proceso desea ver?\n\n1.PEDIDOS.\n2.RECETAS.\n3.DETALLE DE CADA PEDIDO.\n4.PEDIDOS PREPARADOS.\n5.REMANENTE DE INGREDIENTES.\n6.SALIR\n");
                scanf("%i", &opcionMenu);
                system("cls");
                switch (opcionMenu)
                {
                case 1:
                    lecturaIngredientes(listaIngredientes, &validos);
                    lecturaPreparacion (demanda, &validos);
                    muestraDemanda (demanda,validos);
                    system ("pause");
                    system("cls");
                    break;
                case 2 :
                    printf ("Ahora, las recetas!");
                    lecturaRecetas (recetas, &validos, ingXRece);
                    muestraRecetas (recetas, ingXRece, validos, listaIngredientes, costoRecetas);
                    system ("pause");
                    system("cls");
                    break;
                case 3:
                    descuentaIngredientes (recetas, ingXRece, validos, demanda, listaIngredientes, cantMaxPedido );
                    system("pause");
                    system ("cls");
                    break;
                case 4 :
                    cantPreparados (demanda, validos, cantMaxPedido, preparaciones);
                    persistenciaPreparados (validos, preparaciones);
                    system ("pause");
                    system("cls");
                    break;
                case 5:
                    muestraIngredientes(listaIngredientes, validos);
                    modificaArchivoIngredientes (listaIngredientes, validos);
                    system ("pause");
                    system("cls");
                    break;
                }
            }
            while (opcionMenu != 6);
            break;
        case 3:
            do
            {

            printf("\n\n\t--------------------------------\n");
            printf("\n\t             ventas");
            printf("\n\n\t--------------------------------\n");
            printf("\n\nQue parte del proceso desea ver?\n\n1.ASIGNACION DE PRECIOS.\n2.MUESTRA LISTA DE PRECIOS.\n3.CAMBIO DE PRECIOS.\n4.NUEVA VENTA.\n5.DEVOLUCION\n7.SALIR\n");
            scanf("%i", &opcionMenu);
            system("cls");
            switch (opcionMenu)
            {
            case 1:
                CargarPrecios(Precios, recetas, validos);
                persistenciaPrecios(Precios, validos);
                system ("pause");
                system("cls");
                break;
            case 2:
                muestraPrecios (Precios,validos);
                system ("pause");
                system("cls");
                break;
            case 3:
                CambioPrecio(Precios, recetas, validos);
                persistenciaPrecios (Precios, validos);
                system ("pause");
                system("cls");
                break;
            case 4:
                NuevaVenta(preparaciones, ventas, Precios, &validosV, validos);
                MuestraVentas (ventas, validosV);
                persistenciaVentas (ventas, validosV);
                persistenciaPreparados(validos, preparaciones);
                system ("pause");
                system("cls");
                break;
            case 5:
                CancelaVenta(ventas, validosVentas);
                MuestraCanceladas (ventas, validosVentas);
                persistenciaVentas (ventas, validosV);
                system ("pause");
                system("cls");
                break;
            }
            break;
            }while (opcionMenu != 7);

        case 4:
            do
            {
                printf("\n\n\t--------------------------------\n");
                printf("\n\t   FIN DEL DIA");
                printf("\n\n\t--------------------------------\n");
                printf("\n\nQue parte del proceso desea ver?\n\n1.REMANENTE STOCK.\n2.PREPARADOS EN VENTA.\n3.INGRESO DEL DIA..\n4.GANANCIA TOTAL.\n0.SALIR\n");
                scanf("%i", &opcionMenu);
                system("cls");
                switch (opcionMenu)
                {
                case 1:
                    lecturaIngredientes(listaIngredientes, &validos);
                    muestraIngredientes(listaIngredientes, validos);
                    system ("pause");
                    system("cls");
                    break;
                case 2:
                    traerStock(preparaciones, &validosStock);
                    muestraStock(preparaciones, validosStock);
                    system ("pause");
                    system("cls");
                    break;
                case 3:
                    traerVenta(ventas, &validosVentas);
                    muestraVentas(ventas, validosVentas);
                    ingreso = calculoVenta(ventas, validosVentas);
                    printf("\n\n\t--------------------------------\n");
                    printf ("El ingreso total fue de %.2f", ingreso);
                    printf("\n\n\t--------------------------------\n");
                    system ("pause");
                    system("cls");
                    break;
                case 4:
                    ingreso = calculoVenta(ventas, validosVentas);
                    costo = calculoCostos(costoRecetas, ventas, validos, listaIngredientes);
                    ganancia = ingreso - costo;
                    printf("\n\n\t--------------------------------\n");
                    printf("La ganancia total fue de %.2f", ganancia);
                    printf("\n\n\t--------------------------------\n");
                    system ("pause");
                    system("cls");
                    break;
                }

            }
            while (opcionMenu != 0);

        }


    }
    while (opcionMenu != 5);
    return 0;
}


///implementacion

///PASO 1
void lecturaIngredientes (stockIngrediente  listaIngredientes [], int * validos)  /// lectura de ingredientes desde archivo y guardado en estructura.
{
    FILE * fp;
    fp = fopen("stockingredientes.bin", "rb");
    int i = 0;
    if (fp != NULL)
    {
        while (fread(&listaIngredientes[i], sizeof(stockIngrediente), 1, fp ) > 0 )
        {
            i++;
        }

        *validos = i;
        fclose (fp);
    }

    else
    {
        printf("ups. Algo malio sal.");
    }
}

///muestra de ingredientes en stock.

void muestraIngredientes (stockIngrediente listaIngredientes [], int validos)
{
    printf("\n\n\t\t\tINGREDIENTES.\n");

    int cant = cantIngredientes();
    int i;
    printf ("cantidad de ingredientes : %i\n", cant );

    for (i = 0; i < validos ; i++)
    {
        printf("\nIngrediente %i", i+1);
        printf ("\n------------------------------\n");
        printf("nombre : %s\n", listaIngredientes[i].nombre_ingrediente);
        if (strcmpi (listaIngredientes[i].tipo,"liquido" ) == 0)
        {
            printf ("cantidad : %.2f litros \n", listaIngredientes[i].cantidad);
            printf("costo: $ %.2f por litro\n", listaIngredientes[i].costo);
        }
        else
        {
            printf ("cantidad : %.2f kilos\n", listaIngredientes[i].cantidad);
            printf("costo: $ %.2f por kilo\n", listaIngredientes[i].costo);
        }
        printf("tipo: %s\n", listaIngredientes[i].tipo);

        printf ("------------------------------\n");

    }
}

/// cantidad de ingredientes.
int cantIngredientes()
{
    FILE* fp;
    int cant=0;
    fp = fopen("stockingredientes.bin", "rb");
    if (fp != NULL)
    {
        fseek(fp,0,SEEK_END);
        cant = ftell(fp)/sizeof(stockIngrediente);
    }
    return cant;
}


///PASO 2

///traido de demanda
void lecturaPreparacion (Preparacion demanda [], int * validos)
{
    FILE * fp;
    fp = fopen ("demanda.bin", "rb");
    int i = 0;
    if (fp != NULL)
    {
        while (fread(&demanda[i], sizeof(Preparacion), 1, fp ) > 0 )
        {
            i++;
        }

        *validos = i;
        fclose (fp);
    }
    else
    {
        printf("ups! algo malio sal.");
    }
}

void muestraDemanda (Preparacion demanda [], int validos)
{
    printf("\n\n\t\t\tDEMANDA.\n");

    int cant = cantDemanda();
    int i;
    printf ("cantidad de demanda : %i\n", cant );

    for (i = 0; i < validos ; i++)
    {
        printf("\nPedido %i", i+1);
        printf ("\n------------------------------\n");
        printf("nombre : %s\n", demanda[i].nombre_preparacion);
        printf ("cantidad : %i  unidades\n", demanda[i].cantidad);
        printf ("------------------------------\n");
    }


}

/// cantidad de demanda.
int cantDemanda()
{
    FILE* fp;
    int cant=0;
    fp = fopen("demanda.bin", "rb");
    if (fp != NULL)
        fseek(fp,0,SEEK_END);
    cant = ftell(fp)/sizeof(Preparacion);

    return cant;
}

///recetas
void lecturaRecetas (Receta recetas[], int * validos, IngredienteXReceta ingXRece[])
{
    FILE * fp;
    fp = fopen ("recetas.bin", "rb");
    int i = 0;
    if (fp != NULL)
    {
        while (fread(&recetas[i], sizeof(Receta), 1, fp ) > 0)
        {
            i++;
        }

        *validos = i;
        fclose (fp);
    }
    else
    {
        printf("ups, algo malio sal.");
    }
}

void muestraRecetas (Receta recetas [], IngredienteXReceta ingXRece [], int validos, stockIngrediente listaIngredientes [], float  costoRecetas[])
{
    printf("\n\n\t\t\tRECETAS.\n");

    int cant = cantDemanda();
    int i;
    int j;

    printf ("cantidad de  : %i \n", cant);

    for (i = 0; i < validos ; i++)
    {
        printf("\nReceta %i : [%s]", i+1, recetas[i].nombre_preparacion);
        printf ("\n------------------------------\n");
        printf ("cantidad de ingredientes : %i \n", recetas[i].cantIngredientes);
        int max = recetas[i].cantIngredientes;
        for (j = 0 ; j < max ; j++)
        {
            printf ("Nombre del ingrediente : %s \n", recetas[i].ingredientes[j].nombre_ingrediente);
            printf ("Cantidad de ingrediente : %.2f \n", recetas[i].ingredientes[j].cantidad);

        }
        printf ("------------------------------\n");
    }
}

float costoReceta (Receta recetas [], IngredienteXReceta ingXRece [], int validos, stockIngrediente listaIngredientes [], float  costoRecetas[])
{
    printf("\n\n\t\t\tRECETAS.\n");

    int cant = cantDemanda();
    int i;
    int j;

    printf ("cantidad de  : %i \n", cant);

    for (i = 0; i < validos ; i++)
    {
        printf("\nReceta %i : [%s]", i+1, recetas[i].nombre_preparacion);
        printf ("\n------------------------------\n");
        printf ("cantidad de ingredientes : %i \n", recetas[i].cantIngredientes);
        int max = recetas[i].cantIngredientes;
        for (j = 0 ; j < max ; j++)
        {
            printf ("Nombre del ingrediente : %s \n", recetas[i].ingredientes[j].nombre_ingrediente);
            printf ("Cantidad de ingrediente : %.2f \n", recetas[i].ingredientes[j].cantidad);
            for (int k = 0 ; k < 20; k++)
            {
                if (strcmpi(recetas[i].ingredientes[j].nombre_ingrediente,listaIngredientes[k].nombre_ingrediente) == 0)
                {
                    costoRecetas[i] = costoRecetas[i] + (recetas[i].ingredientes[j].cantidad * listaIngredientes[k].costo);
                }
            }
        }
        printf ("------------------------------\n");
        printf ("COSTO POR RECETA %.2f:\n", costoRecetas[i]);
        printf ("------------------------------\n");
    }
}


void descuentaIngredientes (Receta recetas[], IngredienteXReceta ingXRece [], int validos, Preparacion demanda [], stockIngrediente listaIngredientes[], int   cantMaxPedido[])
{
    printf("\t\t\n\nAhora, vamos a calcular cuantos ingredientes descontamos!\n\n");
    float descontada, total, descontada2;
    int k,i,l,j;
    int m = 0;
    int n = 0;


    for (i = 0; i < validos; i++)   /// recorro pedidos
    {
        printf("\n\nPedido %i : [%s]", i+1, recetas[i].nombre_preparacion );
        printf ("\n----------------------------------------------------------------\n");
        int max = recetas[i].cantIngredientes;
        int cantMaxi [30][max];

        for ( j = 0 ; j < max ; j++)  /// recorro por cantidad de ingredientes
        {
            printf ("\nNombre del ingrediente : %s \n", recetas[i].ingredientes[j].nombre_ingrediente);
            printf ("Cantidad de ingrediente por cantidad de pedido : %.2f  x %i\n", recetas[i].ingredientes[j].cantidad, demanda[i].cantidad );
            descontada =  recetas[i].ingredientes[j].cantidad * demanda[i].cantidad;    /// cantidad que hay que descontar del ingrediente
            printf("Cantidad del ingrediente a descontar: %.2f\n", descontada);

            for (k = 0; k < 19 ; k++)        /// dentro de cada ingrediente
            {
                if (stricmp(recetas[i].ingredientes[j].nombre_ingrediente, listaIngredientes[k].nombre_ingrediente) == 0)
                {

                    if (listaIngredientes[k].cantidad > descontada)   /// si la cantidad que pide alcanza
                    {

                        printf ("TENEMOS %.2f:\n", listaIngredientes[k].cantidad );
                        listaIngredientes[k].cantidad = listaIngredientes[k].cantidad - descontada;
                        printf ("NOS QUEDAN %.2f:", listaIngredientes[k].cantidad );
                        l++;
                        printf ("\n-------------------------------------------------------------\n");
                    }
                    else          /// si la cantidad que pide la receta no alcanza
                    {
                        cantMaxi [i][j] = listaIngredientes[k].cantidad / recetas[i].ingredientes[j].cantidad;     ///cantidad maxima que puedo hacer por este ingrediente
                        descontada2 =  recetas[i].ingredientes[j].cantidad * cantMaxi[i][j];
                        printf("NO ALCANZA EL INGREDIENTE PARA REALIZAR EL PEDIDO COMPLETO.\n");
                        printf ("TENEMOS %.2f:", listaIngredientes[k].cantidad );
                        printf("\nLa cantidad maxima que se puede descontar es %i\n", cantMaxi[i][j]);
                        listaIngredientes[k].cantidad = listaIngredientes[k].cantidad - descontada2;
                        printf ("NOS QUEDAN %.2f:", listaIngredientes[k].cantidad);
                        printf ("\n-------------------------------------------------------------\n");
                        if (cantMaxi[i][j] == 0)
                        {
                            m++;
                        }
                        else
                        {
                            n++;
                        }
                    }
                }
            }
        }

        for (j = 1 ; j < max ; j++)
        {
            cantMaxPedido[i] = demanda[i].cantidad;
            if (cantMaxi [i][j-1] < cantMaxi [i][j])
            {
                cantMaxPedido[i] =  cantMaxi [i][j-1];

            }
            if (n == max)
            {
                cantMaxPedido[i] = demanda[i].cantidad;
            }
        }
        if (m != 0)
        {
            printf ("El pedido NO se puede preparar.");
            printf ("\n-------------------------------------------------------------\n");
            m= 0;
            n = 0;
        }
        else
        {
            printf ("El pedido SI se puede preparar. La cantidad MAXIMA ES DE %i", cantMaxPedido[i]);
            printf ("\n-------------------------------------------------------------\n");
            m= 0;
            n = 0;
        }
    }

}


void cantPreparados (Preparacion demanda [], int validos, int cantMaxPedido[], PreparacionVenta preparaciones [])
{
    printf("\n\n\t\t\tCANTIDAD DE PREPARADOS TOTALES.\n");

    int i;

    for (i = 0; i < validos ; i++)
    {
        printf("\nPedido %i", i+1);
        printf ("\n------------------------------\n");
        printf("nombre : %s\n", demanda[i].nombre_preparacion);
        strcpy(preparaciones[i].nombre_preparacion, demanda[i].nombre_preparacion);
        printf ("cantidad  preparada : %i \n", cantMaxPedido[i]);
        preparaciones[i].cantidad = cantMaxPedido[i];
        printf ("------------------------------\n");
    }

}

void persistenciaPreparados (int validos, PreparacionVenta preparaciones [])
{
    FILE *fp;
    fp = fopen ("stockventa.bin", "wb");

    int i ;
    if (fp != NULL)
    {
        for (i = 0; i < validos; i++)
        {

            fwrite(preparaciones, sizeof(PreparacionVenta), 1, fp);
        }
        fclose(fp);
        printf("\n---------------------------------------------\n");
        printf("EL ARCHIVO SE HA MODIFICADO CORRECTAMENTE.\n");
        printf("--------------------------------------------\n");
    }
    else
    {
        printf("Ups, algo malio sal.");
    }
}


void modificaArchivoIngredientes (stockIngrediente listaIngredientes [], int validos)
{
    FILE *fp;
    fp = fopen ("stockingredientes2.bin", "wb");
    if (fp != NULL)
    {
        for (int i = 0; i < validos ; i++)
        {
            fwrite(listaIngredientes, sizeof(stockIngrediente), 1, fp);
        }
        fclose(fp);
        printf("\n---------------------------------------------\n");
        printf("EL ARCHIVO SE HA MODIFICADO CORRECTAMENTE.\n");
        printf("--------------------------------------------\n");
    }
    else
    {
        printf("ups. Algo malio sal.");
    }

}


///paso 3.
///CARGAR LOS PRECIOS.
void CargarPrecios (PrecioPreparacion  Precios [], Receta recetas [], int validos)
{
    int i ;
    printf("Vamos a ponerle precios a los preparados!\n");
    for (i = 0; i < 13 ; i++)
    {
        printf ("\nPreparado %i : %s ", i+1, recetas[i].nombre_preparacion);
        scanf("%f", &Precios[i].precio_venta);
        strcpy(Precios[i].nombre_preparacion, recetas[i].nombre_preparacion);
        validos = i;
    }
}
void muestraPrecios (PrecioPreparacion Precios [], int validos)
{
    printf ("Ahora vamos a ver los precios:");
    for (int i  = 0; i < validos ; i++)
    {
        printf ("Preparado %i : %s", i+1, Precios[i].nombre_preparacion);
        printf ("precio : $ %.2f\n", Precios[i].precio_venta);
    }
}

void persistenciaPrecios (PrecioPreparacion Precios[], int validos)
{
    int i;
    FILE *fp;
    fp = fopen("precios.bin", "wb");
    if (fp != NULL)
    {
        for (i = 0; i < validos; i++)
        {
            fwrite(Precios, sizeof(PrecioPreparacion), 1, fp);
        }
        fclose(fp);
    }
    else
    {
        printf("ups, algo malio sal.");
    }
}

///CAMBIO PRECIO.
void CambioPrecio (PrecioPreparacion Precios[], Receta recetas[], int validos)
{

char continuar;
int flag = 0;


   printf ("\n---Productos: ");
for (int i = 0; i<13; i++)
{
    printf ("\n--%i - %s--", i+1, Precios[i].nombre_preparacion);
}

   do
   {
char nombre[20];
printf ("Ingrese el nombre del producto cuyo precio desea modificar:\n");
fflush (stdin);
gets (nombre);

 for (int i = 0; i<validos; i++)
 {
     if (strcmp(nombre, Precios[i].nombre_preparacion) == 0)
     {
        printf ("\nIngrese el nuevo precio:");
        scanf ("%f", &Precios[i].precio_venta);
        flag = 1;
     }

 }
 if (flag == 0)
 {
     printf ("\nNo se ingresó bien el nombre del producto. No se puede modificar el precio.");
 }

 printf ("\nDesea modificar otro precio? s/n");
 fflush (stdin);
 scanf ("%c", &continuar);

} while (continuar == 's');


}

void NuevaVenta (PreparacionVenta preparaciones[30], Venta ventas[30], PrecioPreparacion Precios[], int *validosV, int validos)
{

        char cont;
        char produc[30];
        int canti;
        int VentaN = 0;
        char sigue;
        PedidoPreparacion Items [20];
        int l = 0;

         printf ("\n---Productos: ");
for (int i = 0; i<13; i++)
{
    printf ("\n--%i - %s--", i+1, Precios[i].nombre_preparacion);
}

        do
        {
        int j = 0;
        VentaN++;

        do
        {

        printf ("\nIngrese el nombre del producto y la cantidad que desea el cliente:  ");
        fflush (stdin);
        gets (produc);
        printf ("----------------------------------");
        scanf ("%i", &canti);
        int exist = 0;


       for (int i = 0; i<validos; i++)
       {


            if (strcmp (produc,preparaciones[i].nombre_preparacion) == 0)
            {
                exist = 1;

        if (canti <= preparaciones[i].cantidad)
        {
            strcpy (Items[j].nombre_preparacion, produc);
            Items[j].cantidad = canti;
            ventas[l].idVenta = VentaN;
            ventas[l].cancelado = 0;
            preparaciones[i].cantidad = preparaciones[i].cantidad - canti;
            ventas[l].valor_total = ventas[l].valor_total + (Precios[i].precio_venta*canti);
            ventas[l].items_pedido[l] = Items[j];
            j++;
        }
        else
        {
            printf ("\nNo hay stock suficiente de ese producto. Intente con menor cantidad.\n");
        }
            }
       }
       if (exist == 0)
       {
           printf ("\nNombre de producto mal ingresado, intente nuevamente.\n");
       }


        printf ("Desea mas productos? s/n\n");
        fflush (stdin);
        scanf ("%c", &cont);
        } while (cont == 's');

        ventas[l].cantItems = j;

        printf ("\n Asi queda conformada la venta:\n");
        printf ("\n----Venta %i----\n", VentaN);
        printf ("--ID: %i\n", ventas[l].idVenta);
        printf ("--Items: %i\n", ventas[l].cantItems);
        printf ("--Valor Total: %.2f\n", ventas[l].valor_total);

        printf ("\nDesea ingresar otra venta?");
        fflush (stdin);
        scanf ("%c", &sigue);
        l++;
        *validosV = l;
    } while (sigue == 's');

}

void MuestraVentas (Venta ventas[], int validosV)
{
   printf ("El total de ventas es de: %i\n", validosV);

   printf ("Así quedan conformadas las ventas:\n");


   for (int i = 0; i<validosV; i++)
   {

   printf ("----Venta %i------\n", i+1);
   printf ("---Cantidad Items: %i\n", ventas[i].cantItems);
    printf ("---Valor Total: %.2f\n", ventas[i].valor_total);
    printf ("---ID: %i\n", ventas[i].idVenta);
   if (ventas[i].cancelado == 1)
   {

    printf ("---Cancelada: Sí\n");
   }
   else
   {
       printf ("---Cancelada: No\n");
   }
   }
  printf ("\n\n");
}


void CancelaVenta (Venta ventas[], int validosV)
{

   int cancel;

    printf ("--Ingrese el ID de la compra que desea cancelar: ");
    scanf ("%i", &cancel);

    for (int i = 0; i<validosV; i++)
    {
        if (cancel == ventas[i].idVenta)
        {
            ventas[i].cancelado = 1;
            printf ("\nLa venta %i fue cancelada", ventas[i].idVenta);
        }
    }


}

void MuestraCanceladas (Venta ventas[], int validosV)
{
    printf ("\n----Las ventas canceladas son las siguientes:----");

    for (int i = 0; i<validosV; i++)
    {
        if (ventas[i].cancelado == 1)
        {
            printf ("\n Numero %i", ventas[i].idVenta);
        }
    }



}
///PASO 4

///traer archivo de preparaciones en stock que quedaron despues de la venta.
void traerStock (PreparacionVenta preparaciones[], int * validosStock)
{
    FILE * fp;
    fp = fopen ("stockventa.bin", "rb");
    int i = 0;
    if (fp != NULL)
    {
        while (fread(preparaciones, sizeof(PreparacionVenta), 1, fp ) > 0 )
        {
            i++;
        }

        *validosStock = i;
        fclose (fp);
    }
    else
    {
        printf("ups! algo malio sal.");
    }
}

///mostrar stock remanente ready pa la venta
void muestraStock (PreparacionVenta preparaciones [], int validosStock)
{
    printf("\n\n\t\t\tPREPARADOS EN STOCK READY PARA SER VENDIDOS.\n");

    int cant = cantStock();
    int i;
    printf ("cantidad de preparados para la venta : %i\n", cant );

    for (i = 0; i < validosStock ; i++)
    {
        printf ("\n------------------------------\n");
        printf("nombre preparacion : %s\n", preparaciones[i].nombre_preparacion);
        printf ("cantidad : %i  unidades\n", preparaciones[i].cantidad);
        printf ("------------------------------\n");
    }

}

///cantidad de elementos en stock
int cantStock ()
{
    FILE* fp;
    int cant=0;
    fp = fopen("stockventa.bin", "rb");
    if (fp != NULL)
    {
        fseek(fp,0,SEEK_END);
        cant = ftell(fp)/sizeof(PreparacionVenta);
    }
    else
    {
        printf("ups. Algo malio sal.");
    }
    return cant;
}


///traer archivo de ventas
void traerVenta (Venta ventas[], int * validosVentas)
{
    FILE * fp;
    fp = fopen ("ventas.bin", "rb");
    int i = 0;
    if (fp != NULL)
    {
        while (fread(&ventas[i], sizeof(Venta), 1, fp ) > 0 )
        {
            i++;
        }

        *validosVentas = i;
        fclose (fp);
    }
    else
    {
        printf("ups! algo malio sal.");
    }
}

///mostrar ventas

void muestraVentas(Venta ventas [], int validosVentas)
{
    printf("\n\n\t\t\tVENTAS.\n");

    int cant = cantVentas();
    int i;
    printf ("cantidad de ventas efectuadas : %i\n", cant );

    for (i = 0; i < validosVentas ; i++)
    {
        printf("\n idVenta %i", i+1);
        printf ("\n------------------------------\n");
        for (int j =0 ; j < ventas[i].cantItems; j++)
        {
            printf("nombre preparacion : %s\n", ventas[i].items_pedido[j].nombre_preparacion);
            printf ("cantidad : %i  unidades\n", ventas[i].items_pedido[j].cantidad);
        }
        printf("valor total : %.2f", ventas[i].valor_total);

        printf ("------------------------------\n");
    }

}

int cantVentas ()
{
    FILE* fp;
    int cant=0;
    fp = fopen("ventas.bin", "rb");
    if (fp != NULL)
    {
        fseek(fp,0,SEEK_END);
        cant = ftell(fp)/sizeof(Venta);
    }
    else
    {
        printf("ups. Algo malio sal.");
    }
    return cant;
}

float calculoVenta (Venta ventas[], int validosVentas)

{
    printf("\n\n\t\t\tTOTAL DE INGRESO.\n");
    int i;
    float totalVentas;
    for (i = 0; i < validosVentas ; i++)
    {
        totalVentas = totalVentas + ventas[i].valor_total;
    }
    return totalVentas;
}

float calculoCostos (float costoRecetas[], Venta ventas [], int validos, stockIngrediente listaIngredientes [])
{
    printf("\n\n\t\t\tTOTAL DE COSTOS.\n");
    int i;
    float totalCostos;
    for (i = 0; i < validos; i++ )
    {
        for (int j = 0 ; j < 20; j++ )
        {
            for (int k = 0 ; k < 19 ; k++)
            {
                if (strcmp(ventas[i].items_pedido[j].nombre_preparacion,listaIngredientes[k].nombre_ingrediente ) == 0)
                {
                    totalCostos = totalCostos + costoRecetas[i];
                }
            }
        }
    }

    return totalCostos;
}


void persistenciaVentas (Venta ventas[], int validosV)
{
    FILE * fp;
    fp = fopen ("ventas.bin", "wb");
    if (fp != NULL)
    {
        for (int i = 0; i<validosV; i++)
        {
            fwrite (&ventas[i], sizeof(Venta), 1, fp);
        }

    }
    else
    {
      printf ("Algo salio mal");
    }


     fclose(fp);
        printf("\n---------------------------------------------\n");
        printf("EL ARCHIVO SE HA MODIFICADO CORRECTAMENTE.\n");
        printf("--------------------------------------------\n");


}




