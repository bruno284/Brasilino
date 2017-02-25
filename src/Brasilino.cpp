/*
 * Brasilino.cpp
 * 
 * Biblioteca de tradução e facilitação de funções para Arduino em PT-BR
 *
 * Criado em 7 Julho 2016
 * Por Otacilio Neto (github: @OtacilioN | Email: contato@otacilio.me), Thiago Augusto (github: @ThiagoAugustoSM | email: martinsthiagoaugusto@gmail.com)
 * Modificado em 24 Fevereiro 2017
 * Por Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 * 
 * Publicado na Licença GPL-3.0
 */

#include "Brasilino.h"
#include <math.h>

void iniciarSerial(void) {
	Serial.begin(9600);
}

void iniciarSerial(int baud) {
	Serial.begin(baud);
}

dobro temperatura(inteiro valorAnalogico) {
	dobro temp;
	temp = log(10000.0 * (1024.0 / valorAnalogico - 1));
	temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp * temp )) * temp);
	temp = temp - 273.15;
	retorne temp;
}

/* ULTRASSOM */
Ultrassom::Ultrassom(int tp, int ep) {
	saida(tp);
	entrada(ep);
	trig_pino = tp;
	echo_pino = ep;
	tempo_limite = 3000;  // 3000 µs = 50cm // 30000 µs = 5 m // Configurado para funcionar ate 50 cm.
}

long Ultrassom::Temporizando() {
	desligar(trig_pino);
	delayMicroseconds(2);
	ligar(trig_pino);
	delayMicroseconds(10);
	desligar(trig_pino);
	
	duracao = pulseIn(echo_pino, HIGH, tempo_limite);
	
	se(duracao == 0)
		duracao = tempo_limite;

	retorne duracao;
}

long Ultrassom::Medir() {
	Temporizando();
	distancia = duracao / 29 / 2;
	retorne distancia;
}
// Não apagar antes disso
