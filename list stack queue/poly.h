/*
  simple program to calculate polynomial
  accomplish by using linear list
*/

#ifndef POLY_H
#define POLY_H

#include "fatal.h"

#define MaxDegree 100

static int Max( int A, int B)
{
    return A > B ? A : B;
}

/* storage */
typedef struct
{
    int CoeffArray[ MaxDegree + 1 ];
    int HighPower;
} *Polynomial;

/* function declaration */
void ZeroPolynomial( Polynomial Poly );
void AddPolynomial( const Polynomial Poly1,
                    const Polynomial Poly2, Polynomial PolySum );
void MultPolynomial( const Polynomial Poly1,
                    const Polynomial Poly2, Polynomial PolyProd );
void PrintPoly( const Polynomial Poly );

/*                    */
/* function prototype */
/*                    */

void ZeroPolynomial( Polynomial Poly )
{
    int i;
    for( i = 0; i <= MaxDegree; ++i )
        (Poly->CoeffArray)[ i ] = 0;
    Poly->HighPower = 0;
}    /* ZeroPolynomial */

void AddPolynomial( const Polynomial Poly1,
                    const Polynomial Poly2, Polynomial PolySum )
{
    ZeroPolynomial( PolySum );
    PolySum->HighPower = Max( Poly1->HighPower, Poly2->HighPower );

    int i;
    for( i = PolySum->HighPower; i >= 0; --i )
        (PolySum->CoeffArray)[ i ] = (Poly1->CoeffArray)[ i ]
                                    + (Poly2->CoeffArray)[ i ];
}    /* AddPolynomial */

void MultPolynomial( const Polynomial Poly1,
                    const Polynomial Poly2, Polynomial PolyProd )
{
    ZeroPolynomial( PolyProd );
    PolyProd->HighPower = Poly1->HighPower + Poly2->HighPower;

    if ( PolyProd->HighPower > MaxDegree )
        Error( "Exceeded array size" );
    else{
        int i, j;
        for( i = 0; i <= Poly1->HighPower; ++i )
            for( j = 0; j <= Poly2->HighPower; ++j )
                (PolyProd->CoeffArray)[ i + j ] +=
                                        (Poly1->CoeffArray)[ i ]
                                        * (Poly2->CoeffArray)[ j ];
    }
}    /* MultPolynomial */

void PrintPoly( const Polynomial Poly )
{
    int i;
    for( i = Poly->HighPower; i > 0; --i )
        printf( "%dx^%d + ", Poly->CoeffArray[ i ], i );
    printf( "%d\n", Poly->CoeffArray[0] );
}

#endif