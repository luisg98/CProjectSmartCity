#ifndef MEIO_H
#define MEIO_H
#define SIZE 50


typedef struct localizacao{
    float latitude;
    float longitude;
} Local;


typedef struct meio
{int codigo; // código do meio de mobilidade elétrica
 char tipo[SIZE];
 float bateria;
 float autonomia;
 Local localizacao;
 struct meio* seguinte;
} Meio;


int existeMeio(Meio **inicio, int cod);
bool inserirMeio(Meio ** meios, int cod, char tipo[], float bat, float aut);
bool removerMeio(Meio** inicio, int cod);
void listarMeios(Meio * inicio);


#endif
