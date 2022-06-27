


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
   float precio_venta; ///precio por unidad
 }PrecioPreparacion;

typedef struct
{
  char nombre_preparacion[20];
  int cantidad;
}PedidoPreparacion;

typedef struct
{
  int idVenta;
  PedidoPreparacion items_pedido[20]; ///puedo pedir hasta 20 items
  int cantItems; ///los validos del arreglo de items_pedido
  float valor_total; ///valor total a pagar
  int cancelado; /// 0 para no, 1 para sí
}Venta;



///prototipado
void lecturaIngredientes (stockIngrediente [], int *);
void muestraIngredientes (stockIngrediente [], int );
void muestraDemanda (Preparacion [], int );
void lecturaPreparacion (Preparacion [], int *);
void lecturaRecetas (Receta [],IngredienteXReceta[], int * , int *);
void muestraRecetas (Receta[],IngredienteXReceta[], int );






int main()
{
    ///variables
    int validos = 0;
    int validos2 = 0;
    int opcionMenu, opcionMenu2;
    char continuar;
    char Nombres[20];
    stockIngrediente listaIngredientes [30];
    IngredienteXReceta ingXRece [30];
    Preparacion demanda [30];
    Receta recetas [30];
    PrecioPreparacion Precios [20];
    Preparacion Preparaciones [20];
    Venta Ventas[30];
    int Venta


/// header
    printf("\n\n\t----------------------------------------------------------------\n");
    printf("\t\t\tBIENVENID@ A LA PANADERIA DEL BARRIO!\n\t\t\t    Atendida por sus propietarios:\n\t\t\t\t Dominguez, Axel.\n\t\t\t\t Framinan, Tomas\n\t\t\t\t Garcia, Ivan.\n");
    printf("\t----------------------------------------------------------------\n\n\n");
    ///menu
    do
    {
        printf("\n\nQue parte del proceso desea ver?\n\n1.INGRESO DE MATERIA PRIMA.\n2.COCINANDO LOS PREPARADOS.\n3.VENTA AL PUBLICO.\n4.RESUMEN DEL DIA.\n5.SALIR\n");
        scanf("%i", &opcionMenu);

        switch (opcionMenu)
        {
        case  1 :
            printf("\n\n\t\tINGRESO DE MATERIA PRIMA.\n");
            printf("Esta es su lista de ingredientes.");
            lecturaIngredientes(listaIngredientes, &validos);
            muestraIngredientes(listaIngredientes, validos);
            break;
        case  2 :
            printf("\n\n\t\tCOCINANDO LOS PREPARADOS");
            lecturaPreparacion (demanda , &validos);
            muestraDemanda (demanda,validos);
            system("pause");
            printf ("Ahora, las recetas!");
            lecturaRecetas (recetas, ingXRece , &validos , &validos2);
            muestraRecetas (recetas, ingXRece, validos);
            break;
        case 3 :
            printf ("Ingrese 1 para establecer los precios. Ingrese 2 para modificar precios ya establecidos. Ingrese 3 para ingresar una nueva venta.\n Ingrese 4 para cancelar una venta.");
            scanf ("%i", &opcionMenu2);
            switch (opcionMenu2)
            {
            case 1:
                CargarPrecios (Precios, Nombres, validos2);
                break;
            case 2:
                CambioPrecio (Precios, validos2);
                break;
            case 3:
                NuevaVenta (Preparaciones, Ventas);
                break;
            case 4:
                CancelaVenta (Ventas);
                break;
            }



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
            printf("costo: %.2f por litro\n", listaIngredientes[i].costo);
        }
        else
        {
            printf ("cantidad : %.2f kilos\n", listaIngredientes[i].cantidad);
            printf("costo: %.2f por kilo\n", listaIngredientes[i].costo);
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
        printf ("cantidad : %i \n", demanda[i].cantidad);
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
void lecturaRecetas (Receta recetas[], IngredienteXReceta ingXRece [] , int * validos, int * validos2)
{
    FILE * fp;
    fp = fopen ("recetas.bin", "rb");
    int i = 0;
    int j = 0;
    if (fp != NULL)
    {
        while (fread(&recetas[i], sizeof(Receta), 1 , fp ) > 0)
        {
            i++;
        }
        *validos = i;

        while (fread(&ingXRece[i], sizeof(IngredienteXReceta), 1 , fp ) > 0 )
        {
            j++;
        }
        *validos2 = j;
        fclose(fp);
    }
    else
    {
        printf("ups! algo malio sal.");
    }
}

void muestraRecetas (Receta recetas [], IngredienteXReceta ingXRece [], int validos)
{
    printf("\n\n\t\t\tRECETAS.\n");

    int cant = cantDemanda();
    int i;
    printf ("cantidad de demanda : %i\n", cant );

    for (i = 0; i < validos ; i++)
    {
        printf("\nPedido %i", i+1);
        printf ("\n------------------------------\n");
        printf("nombre : %s\n", recetas[i].nombre_preparacion);
        printf ("Cantidad de ingrediente DISPONIBLE : %.2f \n", ingXRece[i].cantidad);
        printf ("Nombre del ingrediente : %s \n", ingXRece[i].nombre_ingrediente);
        printf ("cantidad de ingredientes NECESARIA: %i \n", recetas[i].cantIngredientes);
        printf ("------------------------------\n");
    }

}

/// Paso 3:

void CargarPrecios (PrecioPreparacion Precios [20], Preparacion Nombres[20], int validos2)
{



FILE * fp;

int i = 0;
fp = fopen ("recetas.bin", "rb");

if (fp != NULL)
{
  while (fread(&Nombres[i], sizeof(Preparacion), 1, fp ) > 0 )
  {
    i++;
  }

}
else
{
    printf ("Hubo un error.");
    fclose (fp);
}
fclose (fp);


fp = fopen ("Precios.bin", "wb");

if (fp != NULL)
{
    for (i  = 0; i<validos2; i++)
    {
  Printf ("\nIngrese el precio de la preparacion %s:", Nombres[i].nombre_preparacion);
  scanf ("%f", &Precios[i].precio_venta);
  [Precios[i]].nombre_preparacion = [Nombres[i]].nombre_preparacion;
    }
    i = 0;
    while (fwrite(&Precios[i], sizeof(PrecioPreparacion), 1, fp ) > 0 )
  {
    i++;
  }


}
else
{
    printf ("Hubo un error.");
}
fclose (fp);

}

void CambioPrecio (PrecioPreparacion Precios[20] int validos2)
{

char continuar;
char nombre[20];
FILE * fp;
fp = fopen ("Precios.bin", "r+b");
if (fp != NULL)
{
   do
   {

printf ("Ingrese el nombre del producto cuyo precio desea modificar:\n");
fflush (stdin);
gets (nombre);

 for (int i = 0; i<validos2; i++)
 {
     if (nombre == Precios[i].nombre_preparacion)
     {
        printf ("Ingrese el nuevo precio:");
        scanf ("%f", &Precios[i].precio_venta);
        fseek ();
        fwrite ();
     }
 }
 printf ("Desea modificar otro precio? s/n");
 fflush (stdin);
 scanf ("%c", &continuar);

} while (continuar == 's');

}
else
{
    printf ("Hubo un error");
    fclose (fp)
}
fclose (fp);
}

void NuevaVenta (Preparacion Preparaciones[20], Venta Ventas[30])
{
    FILE * fp;
    fp = fopen ("stockventa.bin", "rb");
    if (fp != NULL)
    {
       fseek(fp,0,SEEK_END);
    int stock = ftell(fp)/sizeof(Preparacion);
    rewind (fp);

    for (int i = 0; i<stock; i++)
    {
        fread (&Preparaciones[20], sizeof (Preparacion), 1, fp);
    }

    }
    else
    {
        printf ("Hubo un error");
    }

    fclose (fp);

    FILE * fp;
    fp = fopen ("Ventas.bin", "r+b");

    fseek(fp,0,SEEK_END);
    int VentaN = ftell(fp)/sizeof(Preparacion);

    PedidoPreparacion PrepaVenta;
    Venta IngVenta;

    if (fp != NULL)
    {
        char cont;
        char produc[];
        int canti;
        do
        {

        printf ("Ingrese el nombre del producto y la cantidad que desea el cliente:");
        fflush (stdin);
        scanf ("%s", &produc);
        scanf ("%i", &canti);
        VentaN++;

        for (int i = 0; i<stock; i++)
        {
            if (produc == Preparaciones[i].nombre_preparacion)
            {

        if (canti <= Preparaciones[i].cantidad)
        {
            PrepaVenta.cantidad = canti;
            PrepaVenta.nombre_preparacion = produc;

            IngVenta.items_pedido[i] = PrepaVenta;
            IngVenta.idVenta = VentaN;
            IngVenta.cancelado = 0;
            IngVenta.cantItems = i+1;
            IngVenta.valor_total = ;
            Ventas[VentaN] = IngVenta;
        }
        else
        {
            printf ("No hay stock suficiente de ese producto. Intente con menor cantidad.")
        }
            }
        }

        printf ("Desea ingresar otra venta? s/n");
        fflush (stdin);
        scanf ("%c", &cont);
        } while (cont == 's');
    }
    else
    {
        printf ("Hubo un error");
    }

}


void CancelaVenta (Venta Ventas[30])
{
    FILE * fp;
    fp = fopen ("Ventas.bin", "r+b");

    if (fp != NULL)
    {

    fseek(fp,0,SEEK_END);
    int VentasCant = ftell(fp)/sizeof(Venta);
    rewind (fp);
    int cancel = 0;

    printf ("Ingrese el ID de la venta que desea cancelar:");
    scanf ("%i", &cancel);

    for (int i = 0; i<VentasCant; i++)
    {
        if (cancel == Ventas[i].idVenta)
        {
            Ventas[i].cancelado = 1;
            printf ("La venta %i ha sido cancelada", cancel);
        }
    }
    for (int i = 0; i<VentasCant; i++)
    {
    fwrite (&Ventas[i], sizeof (Venta), 1, fp);
    }
    }
    fclose (fp);
}







