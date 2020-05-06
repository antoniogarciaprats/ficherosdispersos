#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hash_xxx.h"
#include "arditipo.h"

#define MAXLETRAS 32

struct fich_disperso{

	char f[12];
	ardi_tipo cubeta;

};

struct registro0{
	int num_cubeta;
	int tam_cubeta;
};

/*******************************************************************/
/*			MODULO DE PRIMITIVAS PUBLICAS                */
/*******************************************************************/

int dispersion (char *clave, int tamano){

	int i, resultado;

	if (strlen(clave)<2){
		i=0;
		resultado=clave[i]% tamano;
	}
	for (resultado=clave[0], i=1; clave[i]!='\0'; i++)
		resultado=(resultado*MAXLETRAS+clave[i])% tamano;
	return(resultado);

}

/*****************************************************************/

int dispersion2 (char *clave, int tamano){

	int i, resultado;

	if (strlen(clave)<2){
		i=0;
		resultado=clave[i]% tamano;
	}
	for (i=strlen(clave),resultado=clave[i]; i!=0; i--)
		resultado=(resultado*MAXLETRAS+clave[i])% tamano;
	return(resultado);

}


/*******************************************************************/
/*										MODULO DE PRIMITIVAS PUBLICAS								 */
/*******************************************************************/

disperso hash_xxx_nuev(char *fich,int tam, int tam_cubeta,
							 char *(*devuelve_clave) (const void *a)){

	struct registro0 reg0;
	struct hash_xxx_typo dato;
	FILE *f;
	disperso t;
	int i;
	char clave[32];

	strcpy(devuelve_clave(&dato),"");
	t=(disperso)malloc(sizeof(struct fich_disperso));
	if (!t){
		fprintf(stderr, "hash_xxx_nuev: No hay memoria.\n");
		exit(0);
	}
	strcpy(t->f,fich);
	if ((f = fopen(fich, "a+b"))== NULL){
		fprintf(stderr, "Hash_xxx_nuev: No se puede abrir el fichero.\n");
		exit(0);
	}
	reg0.num_cubeta=tam;
	reg0.tam_cubeta=tam_cubeta;
	fwrite(&reg0, sizeof(struct registro0),1,f);
	for (i=0; i!=tam; i++){
		t->cubeta=ardi_tipo_const(tam_cubeta,dato);
		fseek(f,sizeof(struct registro0)+(sizeof(int)*3+
								sizeof(struct hash_xxx_typo)*reg0.tam_cubeta)*i,SEEK_SET);
		ardi_tipo_copiafich(t->cubeta,f);
	}
	fclose(f);
	return t;
}

/********************************************************************/

void hash_xxx_dest (disperso *tabla){

	if (remove((*tabla)->f)){
		fprintf(stderr,"Hash_xxx_dest: El fichero no se puede borrar.\n");
		exit(0);
	}
	ardi_tipo_dest(&(*tabla)->cubeta);
	free(*tabla);
	*tabla=NULL;
}

/*******************************************************************/

void hash_xxx_inserta(disperso tabla,struct hash_xxx_typo *dato,
										 char *(*devuelve_clave) (const void *a)){

	FILE *f;
	int valor, intento=0,tam_cub;
	struct registro0 reg0;
	int i,j;
	struct hash_xxx_typo elem;


	if ((f = fopen(tabla->f, "r+b"))== NULL){
		fprintf(stderr, "Hash_xxx_inserta: No se puede abrir el fichero.\n");
		exit(0);
	}
	fread(&reg0,sizeof(struct registro0),1,f);
	for (i=0; i<reg0.num_cubeta;i++){
		valor=dispersion(devuelve_clave(dato),reg0.num_cubeta)+intento
			 *(dispersion2(devuelve_clave(dato),reg0.num_cubeta)+1);
		fseek(f,sizeof(struct registro0)+(sizeof(int)*3+
								sizeof(struct hash_xxx_typo)*reg0.tam_cubeta)*valor,SEEK_SET);
		ardi_tipo_leefich(tabla->cubeta,f);
		tam_cub=ardi_tipo_tama(tabla->cubeta);
		if (tam_cub<reg0.tam_cubeta){
			for (j=0; j<reg0.tam_cubeta;j++){
				ardi_tipo_obti(tabla->cubeta,j,&elem);
				if (!strcmp(devuelve_clave(&elem),"")){
					ardi_tipo_asig(tabla->cubeta,j,*dato);
					j=reg0.tam_cubeta;
					i=reg0.num_cubeta;
				}
			}
			ardi_tipo_aumlogico(tabla->cubeta);
		}
		else
			intento++;
	}
	fseek(f,sizeof(struct registro0)+(sizeof(int)*3+
							sizeof(struct hash_xxx_typo)*reg0.tam_cubeta)*valor,SEEK_SET);
	ardi_tipo_copiafich(tabla->cubeta,f);
	fclose(f);
}

/**********************************************************************/

void hash_xxx_borrar(disperso tabla,struct hash_xxx_typo *dato,
												char *(*devuelve_clave) (const void *a)){

	FILE *f;
	int valor, intento=0;
	struct registro0 reg0;
	int i,j, encontrado=0;
	struct hash_xxx_typo elem;


	if ((f = fopen(tabla->f, "r+b"))== NULL){
		fprintf(stderr, "Hash_xxx_borrado: No se puede abrir el fichero.\n");
		exit(0);
	}
	fread(&reg0,sizeof(struct registro0),1,f);
	for (i=0; i<reg0.num_cubeta;i++){
		valor=dispersion(devuelve_clave(dato),reg0.num_cubeta)+intento
			 *(dispersion2(devuelve_clave(dato),reg0.num_cubeta)+1);
		fseek(f,sizeof(struct registro0)+(sizeof(int)*3+
								sizeof(struct hash_xxx_typo)*reg0.tam_cubeta)*valor,SEEK_SET);
		ardi_tipo_leefich(tabla->cubeta,f);
		for (j=0; j<reg0.tam_cubeta;j++){
			ardi_tipo_obti(tabla->cubeta,j,&elem);
			if (!strcmp(devuelve_clave(&elem), devuelve_clave(dato))){
				*dato=elem;
				strcpy(devuelve_clave(&elem),"");
				ardi_tipo_asig(tabla->cubeta,j,elem);
				encontrado=1;
				if (ardi_tipo_tama(tabla->cubeta)==reg0.tam_cubeta)
				  ardi_tipo_modborrado(tabla->cubeta);
				j=reg0.tam_cubeta;
				i=reg0.num_cubeta;
			}
			ardi_tipo_dismlogico(tabla->cubeta);
		}
		if (!encontrado){
		  if (ardi_tipo_borrado(tabla->cubeta))
			  intento++;
		  else{
			  printf("El dato no existe. \n");
			  i=reg0.num_cubeta;
		  }
		}
	}
	fseek(f,sizeof(struct registro0)+(sizeof(int)*3+
							sizeof(struct hash_xxx_typo)*reg0.tam_cubeta)*valor,SEEK_SET);
	ardi_tipo_copiafich(tabla->cubeta,f);
	fclose(f);
}

/********************************************************************/

int hash_xxx_consulta(disperso tabla,struct hash_xxx_typo *dato,
												char *(*devuelve_clave) (const void *a)){

	FILE *f;
	int valor, intento=0;
	struct registro0 reg0;
	int i,j, encontrado=0;
	struct hash_xxx_typo elem;


	if ((f = fopen(tabla->f, "r+b"))== NULL){
		fprintf(stderr, "Hash_xxx_consulta: No se puede abrir el fichero.\n");
		exit(0);
	}
	fread(&reg0,sizeof(struct registro0),1,f);
	for (i=0; i<reg0.num_cubeta;i++){
		valor=dispersion(devuelve_clave(dato),reg0.num_cubeta)+intento
			 *(dispersion2(devuelve_clave(dato),reg0.num_cubeta)+1);
		fseek(f,sizeof(struct registro0)+(sizeof(int)*3+
								sizeof(struct hash_xxx_typo)*reg0.tam_cubeta)*valor,SEEK_SET);
		ardi_tipo_leefich(tabla->cubeta,f);
		for (j=0; j<reg0.tam_cubeta;j++){
			ardi_tipo_obti(tabla->cubeta,j,&elem);
			if (!strcmp(devuelve_clave(&elem), devuelve_clave(dato))){
				*dato=elem;
				encontrado=1;
				return 1;
			}
		}
		if (!encontrado){
		  if (ardi_tipo_borrado(tabla->cubeta))
			  intento++;
		  else{
			  printf("El dato no existe. \n");
			  return 0;
		  }
		}
	}
	fclose(f);
}

/********************************************************************/
