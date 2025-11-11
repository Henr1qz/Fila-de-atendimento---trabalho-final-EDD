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

    paciente aux;
    char tipoAtendimento;
    do{
        menu();
        cin >> tipoAtendimento;
        
        if(tipoAtendimento=='C'){
            chegada(aux, emergencia, urgencia, poucoUrgente, naoUrgente);
        }
        else if(tipoAtendimento=='A'){
            // Adicionar lógica para atender
        }
        else if(tipoAtendimento=='D'){
            // Adicionar lógica para exibir filas
        }
    } while(tipoAtendimento != 'Q');  // Continua até pressionar 'Q'
}