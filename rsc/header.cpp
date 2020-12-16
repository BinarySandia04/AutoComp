// Aran Roig (c) 2020
// En este archivo se escribe un texto que se pone encima de cada problema, de manera que se tiene todo esto pero extra jajajs
// Para los problemas es recomendable tener esto abierto en otra pestaña para ver que hay aqui, por si no te acuerdas de alguna función
// Puedes cambiar esto a tu gusto, el programa lo único que hara es copiar esto al incio de cada codigo

#include <bits/stdc++.h> // Incluye todas las librerias
#ifdef LOCAL
#include "debug.h"
#include <csignal>
#endif

#define INF (int)1e9
#define EPS 1e-9
#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define SQUARE(n) (n * n)
#define CUBE(n) (n * n * n)
#define endl '\n'
#define IntMax 2147483647
#define IntMin -2147483647
#define UIntMax 4294967295
#define LongMax 9223372036854775807
#define LongMin -9223372036854775807
#define ULongMax 18446744073709551615

typedef std::string string;
typedef long long int ll;
typedef unsigned long long ull;
typedef std::vector<int> vi;
typedef std::vector<vi> m2x2;
typedef std::vector<m2x2> m3x3;
typedef std::vector<char> vc;
typedef std::pair<string, int> psi;

void Main(); // Main sera nuestro nuevo main

void boostdio(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
}

int main(){
	boostdio();
	Main();
}
