
/*@ <answer>
 *
 * Nombre y Apellidos: Enrique Juan Gamboa
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

#include "bintree_eda.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

bool inEquil(bintree<int> const& tree, int& height, int min, int max) {

    if (!tree.empty()) {
        int lHei, rHei;

        bool lEq, rEq;

        lEq = inEquil(tree.left(), lHei, min, tree.root());
        rEq = inEquil(tree.right(), rHei, tree.root(), max);

        if (lHei < rHei) height = rHei;
        else height = lHei;
        height++;

        return (lEq && rEq &&
            (tree.root() < max) && (tree.root() > min) &&
            abs(lHei - rHei) <= 1);
    }

    height = 0;
    return true;
}

void resuelveCaso() {

    


    // leer los datos de la entrada
    int n;
    bintree<int> tree;

    tree = leerArbol(-1);
    // resolver el caso posiblemente llamando a otras funciones

    // escribir la soluci�n
    int iteration = 0;
    bool isEquil = inEquil(tree, iteration, INT_MIN, INT_MAX);
    cout << (isEquil ? "SI" : "NO") << endl;

}

//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
