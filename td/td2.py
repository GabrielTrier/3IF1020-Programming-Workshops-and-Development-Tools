"""
 Cursus CentraleSupélec - Dominante Informatique et numérique - Campus de Paris-Saclay
 3IF1020 – Ateliers de programmation et outils de développement - TD n°2
 https://wdi.centralesupelec.fr/3IF1020/ProgTD2

 python3 td2.py 10000
"""

# Écrire un script Python contenant une fonction factorial() calculant itérativement
# la factorielle d'un argument donné sur la ligne de commande.

import sys


def factorial( n ):
    print( "TODO" )
    return 0

if __name__ == "__main__":
    if len( sys.argv ) > 1:
        n = int( sys.argv[1] )
        print( str( n ) + "! =", factorial( n ))
    else:
        print( "Donner un nombre sur la ligne de commande" )
