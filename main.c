



void CambioPrecio (PrecioPreparacion Precios[], Receta recetas[], int validos)
{

char continuar;


   do
   {
char nombre;
printf ("Ingrese el nombre del producto cuyo precio desea modificar:\n");
fflush (stdin);
gets (nombre);

 for (int i = 0; i<validos; i++)
 {
     if (strcmp(nombre, Precios[i].nombre_preparacion) == 0)
     {
        printf ("Ingrese el nuevo precio:");
        scanf ("%f", &Precios[i].precio_venta);
     }
 }
 printf ("Desea modificar otro precio? s/n");
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

        do
        {
        int j = 0;
        VentaN++;

        do
        {

        printf ("Ingrese el nombre del producto y la cantidad que desea el cliente:");
        fflush (stdin);
        gets (produc);
        scanf ("%i", &canti);


       for (int i = 0; i<validos; i++)
       {


            if (strcmp (produc,preparaciones[i].nombre_preparacion) == 0)
            {

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
            printf ("No hay stock suficiente de ese producto. Intente con menor cantidad.");
        }
            }
       }


        printf ("Desea mas productos? s/n");
        fflush (stdin);
        scanf ("%c", &cont);
        } while (cont == 's');

        ventas[l].cantItems = j;

        printf ("\nDesea ingresar otra venta?");
        fflush (stdin);
        scanf ("%c", &sigue);
        l++;
        *validosV = l;
    } while (sigue == 's');

}

void MuestraVentas (Venta ventas[30], int validosV)
{
   printf ("Así quedan conformadas las ventas:\n");

   for (int i = 0; i<validosV; i++)
   {

   printf ("----Venta %i------\n", i+1);
   printf ("---Cantidad Items: %i\n", ventas[i].cantItems);
    printf ("---Valor Total: %.2f\n", ventas[i].valor_total);
    printf ("---ID: %i\n", ventas[i].idVenta);
    printf ("---: %i\n");
   }
  printf ("\n\n");
}


void CancelaVenta (Venta ventas[30], int validosV)
{

   int cancel = 0;

    printf ("--Ingrese el ID de la compra que desea cancelar: ");
    scanf ("%i", &cancel);

    for (int i = 0; i<validosV; i++)
    {
        if (cancel == ventas[i].idVenta)
        {
            ventas[i].cancelado = 1;
        }
    }
    printf ("\nLa venta %i fue cancelada", cancel);

}

void MuestraCanceladas (Venta ventas[30], int validosV)
{
    printf ("\n----Las ventas canceladas son las siguientes:----");

    for (int i = 0; i<validosV; i++)
    {
        if (ventas[i].cancelado == 1)
        {
            printf ("\n %i", ventas[i].idVenta);
        }
    }



}

