#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_xxx.h"
#include "arditipo.h"

char *devuelve_clave (const void *a){

	return(((struct hash_xxx_typo*)a)->clave);
}

void main(){

	struct hash_xxx_typo dato;
	int tam_cubeta,n,i,num;
	int tama,opcion;
	disperso t;
	char cad[12];

	printf("Introduce el numero de cubetas.\n");
	scanf("%d",&tama);
	printf("Introduce el tama¤o de las cubetas.\n");
	scanf("%d", &tam_cubeta);
	printf("Introduce el nombre del fichero.\n");
	scanf("%s",cad);
	t= hash_xxx_nuev(cad,tama,tam_cubeta,devuelve_clave);
	do {
	 printf("1 .- Insertar.\n");
	 printf("2 .- Borra.\n");
	 printf("3 .- Consulta.\n");
	 printf("Cualquier otra para salir.\n");
	 printf("Introduce una opcion.\n");
	 scanf("%d",&opcion);
	 switch(opcion) {
		case 1:
		  printf("Dime el numero de elementos que quieres introducir.\n");
		  scanf("%d",&num);
		  for (i=0; i!=num; i++){
			 printf("Introduce una clave.\n");
			 scanf("%s",dato.clave);
			 printf("Introduce un valor.\n");
			 scanf("%d",&dato.val);
			 hash_xxx_inserta(t,&dato,devuelve_clave);
		  }
		  break;
		case 2:
		  printf("Introduce una clave.\n");
		  scanf("%s",dato.clave);
		  hash_xxx_borrar(t,&dato,devuelve_clave);
		  break;
		case 3:
		  printf("Introduce una clave.\n");
		  scanf("%s",dato.clave);
		  if (hash_xxx_consulta(t,&dato,devuelve_clave)){
			 printf("La clave es:   %s.\n", dato.clave);
			 printf("El valor es:   %d.\n", dato.val);
		  }
		  break;
	 }
	} while ((opcion==1) || (opcion==2) || (opcion==3));
   hash_xxx_dest(&t);
}
