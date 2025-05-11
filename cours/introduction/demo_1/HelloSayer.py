"""
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°1
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * HelloSayer.py
 *
 * Exécution :
 *     python3 HelloSayer.py World
"""

import sys

def hello( world ):
    print( "Hello " + world );

if __name__ == "__main__":
    # sys.argv[0] est le nom du script
    # sys.argv[1] est le premier argument sur la ligne de commande
    if len( sys.argv ) > 1 :
        hello( sys.argv[1] )

