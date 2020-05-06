/***************************************************************/
/*                                                             */
/*    Módulo en C para uso de objetos en una estructura de     */
/*                                                             */
/*                  ARRAY DINAMICO                             */
/*                                                             */
/***************************************************************/
/*                                                             */
/*          INSTRUCCIONES PARA LA COMPILACION                  */
/*                                                             */
/*    1.- Define una estructura hash_xxx_typo.                */
/*    2.- Sustituye char por palabra significativa.            */
/*                                                             */
/***************************************************************/

#ifndef ARDI_TIPO_TDA

#define ARDI_TIPO_TDA

struct hash_xxx_typo {

	char clave[32];
	int val;
};

typedef struct ardi_tipo_cubeta  *ardi_tipo;

ardi_tipo ardi_tipo_const(int tama, struct hash_xxx_typo valorinicial);
int ardi_tipo_tama(ardi_tipo a);
int ardi_tipo_borrado(ardi_tipo a);
void ardi_tipo_dismlogico(ardi_tipo a);
void ardi_tipo_aumlogico(ardi_tipo a);
void ardi_tipo_modborrado(ardi_tipo a);
void ardi_tipo_obti(ardi_tipo a, int i, struct hash_xxx_typo *e);
void ardi_tipo_asig(ardi_tipo a, int i, struct hash_xxx_typo e);
void ardi_tipo_copiafich(ardi_tipo a,  FILE *f);
void ardi_tipo_leefich(ardi_tipo a,  FILE *f);
void ardi_tipo_dest(ardi_tipo *a);

#endif

/* Fin del archivo arditipo.h */

