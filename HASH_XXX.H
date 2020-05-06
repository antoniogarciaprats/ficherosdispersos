#ifndef HASH_XXX_TYPO
#define HASH_XXX_TYPO

typedef struct fich_disperso *disperso;

disperso hash_xxx_nuev(char *fich,int tam, int tam_cubeta,
							 char *(*devuelve_clave) (const void *a));
void hash_xxx_dest (disperso *tabla);
void hash_xxx_inserta(disperso tabla,struct hash_xxx_typo *dato,
				  char *(*devuelve_clave) (const void *a));
void hash_xxx_borrar(disperso tabla,struct hash_xxx_typo *dato,
				  char *(*devuelve_clave) (const void *a));
int hash_xxx_consulta(disperso tabla,struct hash_xxx_typo *dato,
				  char *(*devuelve_clave) (const void *a));
#endif
