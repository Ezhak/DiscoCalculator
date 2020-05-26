// Calculadora Disco.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "rlutil.h"
#include <iomanip>
#include <math.h>

using namespace rlutil;
using namespace std;

int main(){
	setColor(COLORES::BLUE); setBackgroundColor(COLORES::GREY); cls();
	int rpm = 0; int carasUtilizables = 0; int pistasPorCara = 0; int sectoresPorPista = 0; float pasoDeCilindro = 0; int modoActual = 0; int modoObjetivo = 0;
	int puntoActual = 0; int peticion = 0;
	float seekTime = 0; float searchTime = 0; float accessTime = 0; float accesTime = 0;
	int sectoresPorCilindro = 0; int sectorActual = 0; int cilindroActual; int sectorObjetivo = 0; int cilindroObjetivo = 0;
	int restaAuxiliar = 0; float msAuxiliar = 60000;
	float vueltaPorMs = 0; int sectoresPorSeekTime = 0;  int secAux = 0;
	int sectorQueCai = 0; int caraEquivalencia = 0; int sectorEquivalencia = 0; int caraEquivalenciaVoy = 0; int sectorEquivalenciaVoy = 0;
	int sectoresMoverse = 0; int sectorObjetivoAuxiliar = 0; float vueltaSector = 0;
// Access Time = Seek Time + Search Time

	for (int i = 2; i < 60; i++) {
		gotoxy(i, 1); printf("%c", 205);
		gotoxy(i, 30); printf("%c", 205);
	};
	for (int i = 2; i < 30; i++) {
		gotoxy(1, i); printf("%c", 186);
		gotoxy(60, i); printf("%c", 186);
	};
	gotoxy(1, 1); printf("%c", 201);
	gotoxy(1, 30); printf("%c", 200);
	gotoxy(60, 1); printf("%c", 187);
	gotoxy(60, 30); printf("%c", 188);
	gotoxy(2, 2);
	cout << "Ingrese las RPM: " << endl;gotoxy(19, 2);cin >> rpm;
	gotoxy(2, 3);
	cout << "Ingrese las Caras Utilizables: " << endl;gotoxy(33, 3);cin >> carasUtilizables;
	gotoxy(2, 4);
	cout << "Ingrese las Pistas por Cara: " << endl;gotoxy(31, 4); cin >> pistasPorCara;
	gotoxy(2, 5);
	cout << "Ingrese los Sectores por Pista: " << endl; gotoxy(34, 5); cin >> sectoresPorPista;
	gotoxy(2, 6);
	cout << "Ingrese el Paso de Cilindro: " << endl;gotoxy(31, 6); cin >> pasoDeCilindro;
	gotoxy(2, 7);
	cout << "------------------------------" << endl;
	gotoxy(2, 8);
	cout << "Ingrese el punto actual: " << endl; gotoxy(27, 8); cin >> puntoActual;
	gotoxy(2, 9);
	cout << "Ingrese la peticion: " << endl; gotoxy(23, 9); cin >> peticion;
	gotoxy(2, 10);
	cout << "------------------------------" << endl;
// Calculo de Seek Time - Se debe calcular los sectores por cilindro
	sectoresPorCilindro = carasUtilizables * sectoresPorPista;
// Calculo de cilindro y sector correspondientes al punto actual y al punto objetivo
	cilindroActual = puntoActual / sectoresPorCilindro;
	sectorActual = puntoActual % sectoresPorCilindro;
	cilindroObjetivo = peticion / sectoresPorCilindro;
	sectorObjetivo = peticion % sectoresPorCilindro;
		if (cilindroActual > cilindroObjetivo) {
			restaAuxiliar = cilindroActual - cilindroObjetivo;
		}
		else {
			if (cilindroObjetivo > cilindroActual) {
				restaAuxiliar = cilindroObjetivo - cilindroActual;
			}
		}
// Calculo de SeekTime
	seekTime = restaAuxiliar * pasoDeCilindro;
	gotoxy(61, 2);
	cout << "El SeekTime es de: " << fixed << setprecision(2) << seekTime << "ms" << endl;
// Calculo de SearchTime
	vueltaPorMs = msAuxiliar / rpm;
	gotoxy(61, 3);
	cout << "El disco tarda " << fixed << setprecision(2) << vueltaPorMs << "ms en una vuelta" << endl;
// Calculo de cuantos sectores recorre el Seek Time
	sectoresPorSeekTime = ((seekTime * sectoresPorPista) / (vueltaPorMs))+1;
	secAux = sectoresPorSeekTime;secAux *= 10;ceil(secAux);secAux /= 10;
	sectoresPorSeekTime=secAux;
	gotoxy(61, 4);
	cout << "El SeekTime recorre " << sectoresPorSeekTime << " sectores en " << fixed << setprecision(2) << vueltaPorMs << " ms" << endl;
// 
	sectorQueCai = sectorActual + sectoresPorSeekTime;
//Homologaciones o Equivalencias de Sector y Cara
	caraEquivalencia = sectorQueCai / sectoresPorPista;
	sectorEquivalencia = sectorQueCai % sectoresPorPista;
	gotoxy(61, 5);
	cout << "Sector homologado en el que estoy: " << sectorEquivalencia << endl;
	gotoxy(61, 6);
	cout << "Cara homologada en la que estoy: " << caraEquivalencia << endl;
	caraEquivalenciaVoy = sectorObjetivo / sectoresPorPista;
	sectorEquivalenciaVoy = sectorObjetivo % sectoresPorPista;
	gotoxy(61, 7);
	cout << "Sector homologado al que voy: " << sectorEquivalenciaVoy << endl;
	gotoxy(61, 8);
	cout << "Cara homolagada al que voy: " << caraEquivalenciaVoy << endl;
// Tras homologar, hay que calcular cuantos sectores hay que moverse
		if (sectorEquivalencia > sectorEquivalenciaVoy) {
			sectorObjetivoAuxiliar = sectorEquivalencia - sectorEquivalenciaVoy;
		}
		else {
			if (sectorEquivalenciaVoy > sectorEquivalencia) {
			sectorObjetivoAuxiliar = sectorEquivalenciaVoy - sectorEquivalencia;
			}
		}
		if (sectorObjetivoAuxiliar > sectoresPorPista) {
			sectoresMoverse = sectorObjetivoAuxiliar - sectoresPorPista;
		}
		else {
			if (sectoresPorPista > sectorObjetivoAuxiliar) {
				sectoresMoverse = sectoresPorPista - sectorObjetivoAuxiliar;
			}
		}
	gotoxy(61, 9);
	cout << "Hay que moverse: " << sectoresMoverse << " sectores" << endl;
// Calculo del disco en que tarda recorrer un solo sector
	vueltaSector = vueltaPorMs / sectoresPorPista;
	gotoxy(61, 10);
	cout << "El tiempo en que tarda recorrer un sector es de " << fixed << setprecision(3) << vueltaSector << " ms" << endl;
// Calculo de Search Time
	searchTime = sectoresMoverse * vueltaSector;
	gotoxy(61, 11);
	cout << "El SearchTime es de: " << fixed << setprecision(2) << searchTime << " ms" << endl;
// Calculo de AccesTime
	accesTime = seekTime + searchTime;
	gotoxy(61, 12);
	cout << "El Access Time es de: " << fixed << setprecision(2) << accesTime << " ms" << endl;
	anykey();
	return 0;
}
