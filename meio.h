#ifndef MEIO_H
#define MEIO_H
#define SIZE 50




typedef struct Meio
{int codigo;
 char tipo[SIZE];
 float autonomia;
 char localizacao;
 struct meio* seguinte;
} Meio;


#endif
