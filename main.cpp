#include <iostream>
#include <queue>
using namespace std;

struct paciente{
    string senha;
    char prioridade;
    int hora,minuto;
};

#include "funcoes.cpp"

int main(){
    queue<paciente>emergencia;
    queue<paciente>urgencia;
    queue<paciente>poucoUrgente;
    queue<paciente>naoUrgente;
    int hora, min, esperah, esperam;
    int V=0,A=0,D=0,B=0,totalAtendido=0;
    int maxFila=0, maxEspera=0;

    paciente aux;
    char tipoAtendimento;
    do{
        menu();
        cin >> tipoAtendimento;
        
        if(tipoAtendimento=='C'){
            chegada(aux, emergencia, urgencia, poucoUrgente, naoUrgente, maxFila);
        }
        else if(tipoAtendimento=='A'){
            atendimento(hora,min, esperah,esperam ,emergencia, urgencia, poucoUrgente, naoUrgente,V,A,D,B, maxEspera);
        }
        else if(tipoAtendimento=='D'){
            consulta(emergencia, urgencia, poucoUrgente, naoUrgente, V, A, D, B);
        }
        else if(tipoAtendimento=='Q'){
            relatorioFinal(V,A,D,B,totalAtendido, maxFila, maxEspera);
        }
    } while(tipoAtendimento != 'Q'); 
}
