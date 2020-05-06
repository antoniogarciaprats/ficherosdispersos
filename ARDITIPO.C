/***************************************************************/
/*                                                             */
/*    Modulo en C para uso de objetos en una estructura de     */
/*                                                             */
/*                         ARRAY DINAMICO                      */
/*                                                             */
/***************************************************************/
/*                                                             */
/*              INSTRUCCIONES PARA LA COMPILACION              */
/*                                                             */
/*        1.- Sustituye char por palabra significativa.        */
/*                                                             */
/***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arditipo.h"

struct ardi_tipo_cubeta {
	int tamal;
	int tamar;
	int borrado;
	struct hash_xxx_typo *arr;
};

/********************************************************************/
/***************   PROCEDIMIENTOS Y FUNCIONES PRIVADOS   ************/
/********************************************************************/

/* Crea el vector con un tama¤o determinado. */

struct hash_xxx_typo	*ardi_tipo_aloarr(int tamano) {

	struct hash_xxx_typo *arr;

	if (!tamano) return(NULL);
	else {
		arr=(	struct hash_xxx_typo *)malloc(sizeof(struct hash_xxx_typo)*tamano);
		if (!arr) {
			fprintf(stderr,"ardi_tipo_aloarr: no hay memoria.\n");
			exit(2);
		}
		return(arr);
	}
}

/********************************************************************/

/* Destruye el vector. */

void ardi_tipo_daloarr(struct hash_xxx_typo *arr) {

	if (arr) free(arr);
}

/********************************************************************/

/* Crea la cabecera del ardi, con un vector de tama¤o indicado. */

ardi_tipo ardi_tipo_alo(int tamano) {

	ardi_tipo p;

	p=(ardi_tipo)malloc(sizeof(struct ardi_tipo_cubeta));
	if (!p) {
		fprintf(stderr,"ardi_tipo_alo: no hay memoria.\n");
		exit(2);
	}
	p->tamal=0;
	p->tamar=tamano;
	p->borrado=0;
	p->arr=ardi_tipo_aloarr(tamano);
	return(p);
}


/********************************************************************/

/* Detruye el vector junto con la cabecera. */

void ardi_tipo_dalo(ardi_tipo *p) {

	if (*p!=NULL) {
		ardi_tipo_daloarr((*p)->arr);
		free(*p);
		*p=NULL;
	}
}

/********************************************************************/
/*************  PROCEDIMIENTOS Y FUNCIONES PUBLICOS   ***************/
/********************************************************************/

ardi_tipo ardi_tipo_const(int tama, struct hash_xxx_typo valorinicial){

	int i;
	ardi_tipo x;
	struct hash_xxx_typo *array;

	if (tama<1) {
		fprintf(stderr, "ardi_tipo_const: tama < 1.\n");
		exit(1);
	}
	x=ardi_tipo_alo(tama);
	for (i=0;i<tama;i++)
		x->arr[i]= valorinicial;
	return (x);
}
/********************************************************************/

/* Te devuelve el tama¤o logico del vector. */

int ardi_tipo_tama(ardi_tipo a) {

	if (!a) {
		fprintf(stderr,"ardi_tipo_tama: el argumento no ha sido creado.\n");
		exit(3);
	}
	return(a->tamal);
}

/********************************************************************/

int ardi_tipo_borrado(ardi_tipo a) {

	if (!a) {
		fprintf(stderr,"ardi_tipo_borrado: el argumento no ha sido creado.\n");
		exit(3);
	}
	return(a->borrado);
}

/********************************************************************/

void ardi_tipo_dismlogico(ardi_tipo a) {

	if (!a) {
		fprintf(stderr,"ardi_tipo_dismlogico: el argumento no ha sido creado.\n");
		exit(3);
	}
	a->tamal--;
}

/********************************************************************/

void ardi_tipo_aumlogico(ardi_tipo a) {

	if (!a) {
		fprintf(stderr,"ardi_tipo_dismlogico: el argumento no ha sido creado.\n");
		exit(3);
	}
	a->tamal++;
}

/********************************************************************/


void ardi_tipo_modborrado(ardi_tipo a) {

	if (!a) {
		fprintf(stderr,"ardi_tipo_modborrado: el argumento no ha sido creado.\n");
		exit(3);
	}
	a->borrado=1;
}

/********************************************************************/

/* Obtienes en *e el valor que se encuentra en la posicion i. La posicion
 * esta dentro del rango de los indices del vector. */

void ardi_tipo_obti(ardi_tipo a, int i, struct hash_xxx_typo *e) {

	if (!a) {
		fprintf(stderr,"ardi_tipo_obti: el argumento no ha sido creado.\n");
		exit(3);
	}
	if (i<0 || i>a->tamar) {
		fprintf(stderr,"ardi_tipo_obti: indice fuera de rango.\n");
		exit(4);
	}
	*e=a->arr[i];
}

/********************************************************************/

/* Asigna el valor de e en la posicion i del vector. i esta dentro del rango. */

void ardi_tipo_asig(ardi_tipo a, int i, struct hash_xxx_typo e) {

	if (!a) {
		fprintf(stderr,"ardi_tipo_asig: el argumento no ha sido creado.\n");
		exit(3);
	}
	if (i<0 || i>a->tamar) {
		fprintf(stderr,"ardi_tipo_asig: indice fuera de rango.\n");
		exit(4);
	}
	a->arr[i]=e;
}

/********************************************************************/

void ardi_tipo_copiafich(ardi_tipo a,  FILE *f){

	 int i;

	 fwrite(&a->tamal, sizeof(int),1,f);
	 fwrite(&a->tamar, sizeof(int),1,f);
	 fwrite(&a->borrado, sizeof(int),1,f);
	 for(i=0; i<a->tamar; i++)
		 fwrite(&a->arr[i], sizeof(struct hash_xxx_typo),1, f);

}

/*******************************************************************/

void ardi_tipo_leefich(ardi_tipo a,  FILE *f){

	 int i;

	 fread(&a->tamal, sizeof(int),1,f);
	 fread(&a->tamar, sizeof(int),1,f);
	 fread(&a->borrado, sizeof(int),1,f);
	 for(i=0; i<a->tamar; i++)
		 fread(&a->arr[i], sizeof(struct hash_xxx_typo),1, f);

}
/*******************************************************************/

/* Destruye el vector dinamico. */

void ardi_tipo_dest(ardi_tipo *a) {

	if (!*a) {
		fprintf(stderr,"ardi_tipo_dest: el argumento no ha sido creado.\n");
		exit(3);
	}
	ardi_tipo_dalo(a);
}

/********************************************************************/
