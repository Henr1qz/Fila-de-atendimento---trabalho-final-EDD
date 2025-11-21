#include <iostream>
#include <queue>
#include <string>

void menu(){
    std::cout<<"Selecione um evento:\n";
    std::cout<<"Digite 'C' para registrar a chegada de um paciente\n";
    std::cout<<"Digite 'A' para atender um paciente\n";
    std::cout<<"Digite 'D' para exibir informacoes sobre o estado das filas\n";
    std::cout<<"Digite 'Q' para sair\n";
}

void calcEspera(int &hora, int &minuto, int &esperah, int &esperam, std::queue<paciente> lista){
    esperah = hora - lista.front().hora;
    esperam = minuto - lista.front().minuto;
    
    if(esperam < 0){
        esperam = esperam + 60;
        esperah = esperah - 1;
    }
    
    if(esperah < 0){
        esperah = esperah + 24;
    }
}

void chegada(paciente &aux, 
            std::queue<paciente> &emergencia, 
            std::queue<paciente> &urgencia, 
            std::queue<paciente> &poucoUrgente, 
            std::queue<paciente> &naoUrgente,
            int &maxFila){

    std::cout<<"Digite a senha do paciente:\n";
    std::cin>>aux.senha;

    std::cout<<"Digite a prioridade:\n";
    std::cin>>aux.prioridade;

    std::cout<<"Digite a hora de chegada:\n";
    std::cin>>aux.hora;

    std::cout<<"Digite o minuto de chegada\n";
    std::cin>>aux.minuto;

    if(aux.prioridade=='V'){
        emergencia.push(aux);
    }else if(aux.prioridade=='A'){
        urgencia.push(aux);
    }else if(aux.prioridade=='D'){
        poucoUrgente.push(aux);
    }else if(aux.prioridade=='B'){
        naoUrgente.push(aux);
    }

    int tamanhoAtual = emergencia.size() + urgencia.size() + poucoUrgente.size() + naoUrgente.size();
    if(tamanhoAtual > maxFila){
        maxFila = tamanhoAtual;
    }
}

void atendimento(int &hora, int &minuto, int &esperah, int &esperam,
            std::queue<paciente> &emergencia, 
            std::queue<paciente> &urgencia, 
            std::queue<paciente> &poucoUrgente, 
            std::queue<paciente> &naoUrgente,
            int &V, int &A, int &D, int &B,
            int &maxEspera){
    
    std::cout<<"Digite o horario do atendimento: "<< "\n";
    std::cin>>hora;
    std::cin>>minuto;
    
    int totalMinutosEspera = 0;

    if(emergencia.empty()&&urgencia.empty()&&poucoUrgente.empty()&&naoUrgente.empty()){
        std::cout<< hora<<" "<<minuto <<" Sem pacientes aguardando atendimento"<<"\n";

    }else if(!emergencia.empty()){
        calcEspera(hora,minuto,esperah, esperam,emergencia);
        
        totalMinutosEspera = (esperah * 60) + esperam;
        if(totalMinutosEspera > maxEspera) maxEspera = totalMinutosEspera;
        
        emergencia.pop();
        V++;
        std::cout<<"o paciente esperou: "<<esperah<<" horas e "<<esperam<<" minutos."<<"\n";

    }else if(emergencia.empty()&&!urgencia.empty()){
        calcEspera(hora,minuto,esperah, esperam,urgencia);

        totalMinutosEspera = (esperah * 60) + esperam;
        if(totalMinutosEspera > maxEspera) maxEspera = totalMinutosEspera;

        urgencia.pop();
        A++;
        std::cout<<"o paciente esperou: "<<esperah<<" horas e "<<esperam<<" minutos."<<"\n";

    }else if(emergencia.empty()&&urgencia.empty()&&!poucoUrgente.empty()){
        calcEspera(hora,minuto,esperah, esperam,poucoUrgente);

        totalMinutosEspera = (esperah * 60) + esperam;
        if(totalMinutosEspera > maxEspera) maxEspera = totalMinutosEspera;

        poucoUrgente.pop();
        D++;
        std::cout<<"o paciente esperou: "<<esperah<<" horas e "<<esperam<<" minutos."<<"\n";

    }else if(emergencia.empty()&&urgencia.empty()&&poucoUrgente.empty()&&!naoUrgente.empty()){
        calcEspera(hora,minuto,esperah, esperam,naoUrgente);

        totalMinutosEspera = (esperah * 60) + esperam;
        if(totalMinutosEspera > maxEspera) maxEspera = totalMinutosEspera;

        naoUrgente.pop();
        B++;
        std::cout<<"o paciente esperou: "<<esperah<<" horas e "<<esperam<<" minutos."<<"\n";
    }
}

void consulta(std::queue<paciente> &emergencia, 
              std::queue<paciente> &urgencia, 
              std::queue<paciente> &poucoUrgente, 
              std::queue<paciente> &naoUrgente,
              int V, int A, int D, int B){
    
    int totalAtendido = V + A + D + B;

    std::cout<<"V:"<<emergencia.size()
             <<" A:"<<urgencia.size()
             <<" D:"<<poucoUrgente.size()
             <<" B:"<<naoUrgente.size()
             <<" | Atendidos:"<<totalAtendido<<"\n";
}

void relatorioFinal(int &V, int &A, int &D, int &B, int &totalAtendido, int maxFila, int maxEspera){
    totalAtendido=V+A+D+B;
    std::cout<<"Total atendidos: "<<totalAtendido<<"\n";
    std::cout<<"Por prioridade: V="<<V<<" A="<<A<<" D="<<D<<" B="<<B<<"\n";
    std::cout<<"Pico de lotação: "<<maxFila<<"\n";
    std::cout<<"Espera máxima: "<<maxEspera<<" minutos\n";
}