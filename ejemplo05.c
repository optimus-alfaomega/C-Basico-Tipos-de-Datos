/* 
 * C BY 8 EXAMPLES
 * example05.c: punteros de memoria
 * 
 * Copyright (C) 2019 Ignacio Pérez Hurtado de Mendoza
 * http://www.cs.us.es/~ignacio
 * Copyright (C) 2020 Miguel Ángel Martínez del Amor
 * http://www.cs.us.es/~mdelamor
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
 

// BIBLIOTECAS
 #include <stdio.h>
 #include <math.h>
 
 // CONSTANTES
 #define PI 3.14159265358979323846L
 
 // TIPOS (otra forma de definir un struct, más directo)
typedef struct {
	double x;
	double y;
} PUNTO;

// CABECERA DE FUNCIONES (ya veremos que significan esos asteriscos...)
double distanciaEuclidea(PUNTO* a, PUNTO* b);
void intercambia(int* a, int* b);
int* malamente();
int* no_tan_malamente();

// VARIABLES GLOBALES 
int variableGlobal = 101;
 
// FUNCION MAIN 
int main()
{
	// En C existe un tipo especial de datos denominado puntero
	// que sirve para almacenar direcciones de memoria RAM
	
	// Entendemos la RAM como un "casillero" en donde se almacenan
	// datos, cada casilla tiene una dirección 
	
	// DIR    DATO
	// 0x100   x
	// 0x104   y
	
	// La unidad es el byte. En el ejemplo anterior, cada dato es de 4 bytes
	
	// podemos definir una variable de tipo puntero añadiendo el asterisco *
	// al tipo de dato referenciado por el puntero
	
	// por ejemplo:
	
	int* pt1;
	
	// es un puntero para almacenar direcciones de memoria que contienen
	// valores de tipo entero (4 bytes en la mayoria de las máquinas)
	
	double* pt2;
	
	// es un puntero para almacenar direcciones de memoria que contienen
	// valores de tipo double (8 bytes)
	
	// si tenemos una variable 
	int a = 10;
	double b = PI;
	
	// podemos obtener su dirección de memoria mediante el operador &
	
	pt1 = &a; // punteros de tipo int* almacenan direcciones de memoria de variables int
	pt2 = &b; // punteros de tipo double* almacenan direcciones de memoria de variables double
	
	// pt1 ---> a
	// pt2 ---> b
	
	// para imprimir una dirección de memoria podemos usar el siguente formato
	
	printf("La variable a tiene un valor %d y se encuentra en la direccion %p de la memoria RAM\n",a,pt1);
	printf("La variable b tiene un valor %lf y se encuentra en la direccion %p de la memoria RAM\n",b,pt2);
	
	// podemos acceder al valor de la variable apuntada por el puntero mediante el operador *
	
	*pt1 = *pt1 + 2;
	
	// El * en la anterior expresión es un operador unario para obtener el valor de la variable
	// apuntada por el puntero (en el ejemplo, el valor de la variable a). Esto no debe
	// confundirse con la declaración del puntero int* pt1; 
	// Aunque a veces veremos int *pt1; pero eso es porque sintácticamente es posible
	// (al fin y al cabo los espacios no significan nada en C)
	
	// ahora la variable a ha sido modificada
	printf("Nuevo valor de a: %d\n",a);
	
	printf("Tambien podemos consultar la variable usando su puntero: %d\n", *pt1);
	
	// Un puntero no inicializado puede recibir el valor NULL (esto es una buena práctica)
	int *pt3 = NULL;
	
	// que viene bien para chequear precisamente si ha sido inicializado o no
	
	if (pt3 == NULL) {
		printf("El puntero pt3 no está inicializado\n");
	}
	
	// En los ejemplos anteriores hemos visto funciones con argumentos que se pasan por valor,
	// por ejemplo: int esPar(int x) recibe un valor que se copia en la variable local x. 
	// Esto no es recomendable para estructuras de datos o arrays (que veremos mas adelante),
	// ya que la copia consume un tiempo O(n). En esos casos es recomendable pasar los argumentos 
	// por referencia. En C esto se consigue usando punteros. Por ejemplo:
	
	PUNTO u;
	u.x = 10.4;
	u.y = -23.4;
	
	PUNTO v;
	
	v.x = 0;
	v.y = 6.4;
	
	printf("Distancia entre u y v: %lf\n",distanciaEuclidea(&u,&v));
	
	// Por regla general, los tipos de datos simples (char, short, int, long, float, double...)
	// se pasan por valor. Las estructuras y arrays por referencia.
	
	// Ya que podemos modificar una variable mediante su puntero, pasar un argumento a una 
	// función por referencia implica que ese argumento es de entrada/salida. Si lo piensas un
	// momento, verás que en realidad a una función se le pasa los argumentos por valor, pero
	// si le pasas un puntero, ese puntero no se cambia (por valor) pero sí se puede cambiar
	// la posición de memoria a la que apunta.

	// Así que usaremos punteros en las funciones para pasar estructuras y arrays o bien
	// cuando queramos argumentos de entrada/salida. El truco está en usar &.
	
	int x = 42;
	int y = 24;
	
	printf("x vale %d, y vale %d\n",x,y);
	
	intercambia(&x,&y);
	
	printf("x vale %d, y vale %d\n",x,y);
	
	// Las variables en C tienen "vigencia" en su ámbito, por ejemplo: cuerpo de una función,
	// cuerpo de un bucle, cuerpo de un if-else. Un error muy habitual es usar el puntero a una
	// variable que ha salido de su ámbito. Por ejemplo, que una función devuelva como resultado 
	// un puntero a una variable local. Mira la función "malamente". 
	
	// Descomenta la siguiente linea para disfrutar de tu primer "segmentation fault" o "violacion de segmento"
	// int bienvenidos_a_vuestra_primera_violacion_de_segmento = *malamente();
	
	// Una violación de segmento es un error muy habitual en C y suele ocurrir cuando se utiliza un
	// puntero inválido, ya sea porque no se ha inicializado o porque hace referencia a una variable 
	// que ha salido de su ámbito. También puede ocurrir cuando se intenta acceder a zonas de memoria
	// restringidas al usuario, como puede ser la memoria RAM que usa el sistema operativo.
	
	printf("Variable global: %d\n",*no_tan_malamente());
	
	// A continuación una composición de punteros. Quizás pueda sonar loco, pero un puntero puede apuntar
	// otra variable que a su vez es un puntero. Es decir, un puntero que apunta a direcciones de memoria que 
	// contienen punteros que apuntan a direcciones de memoria que contienen valores de tipo entero: 
	int** pt4;
	
	pt4 = &pt1;
	
	// pt4 --> pt1 --> a
	
	printf("El valor de la variable a traves de un puntero doble: %d\n",**pt4);
	
	// Debido a que la memoria esta alineada (en bytes), los punteros simples servirán también para 
	// referenciar la posicion de origen de un vector o array y los punteros 
	// dobles para matrices. Pero lo veremos en el siguiente ejemplo.
	
	// Para leer un valor del teclado, se usa scanf 
	printf("Introduzca un valor numerico: ");
	scanf("%d",&a);
	
	printf("El valor introducido es %d\n",a);
	
	// Observese que scanf es muy parecido a printf, pero scanf trabaja con direcciones de memoria (ya
	// que necesita guardar un valor leído, y eso no es posible a no ser que se pase el puntero a 
	// una posición de memoria)
	
	return 0;
	
}

// RESTO DE FUNCIONES
double distanciaEuclidea(PUNTO* a, PUNTO* b)
{
	return sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
	// cuando tenemos un puntero a una estructura, se puede usar el operador ->  en lugar del operador .
	// por ejemplo: a->x es equivalente a  (*a).x
}

void intercambia(int* a, int* b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

int* malamente()
{
	int x = 42;
	return &x; // MUY MAL! la variable x es local a la función y cuando se termina
	           // se libera memoria y el puntero no es válido (apunta a una posición de memoria que
			   // ya no se controla)
}

int* no_tan_malamente()
{
	return &variableGlobal; // Las variables globales tienen vigencia en todo el programa
}
