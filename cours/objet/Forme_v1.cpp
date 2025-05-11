/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°4
 * Dominique Marcadet - 2022 - CC BY-SA
 *
 * Forme_v1.cpp
 *
 * Compilation :
 *     c++ -std=c++20 -o Forme_v1 Forme_v1.cpp
 * Exécution :
 *     ./Forme_v1
 */


#include <iostream>

class Point {
public:
    Point( int x, int y ) : x_{ x }, y_{ y } {}
    int get_x() const { return x_; }
    int get_y() const { return y_; }
private:
    int x_;
    int y_;
};

std::ostream & operator<<( std::ostream & out, const Point & p ) {
    return out << "Point{ " << p.get_x() << ", " << p.get_y() << " }";
}

class Forme {
public:
    explicit Forme( Point centre ) : centre_{ centre } {
        std::cout << "Forme::Forme( " << centre << ")\n";
    }
    ~Forme() { std::cout << "Forme::~Forme( " << centre_ << ")\n"; }
    Forme( const Forme & f ) : centre_{ f.centre_ } {
        std::cout << "Forme::Forme( const Forme & ( " << centre_ << " ))\n";
    }

    // Une forme sait se déplacer
    void deplace( Point nouveau_centre ) { centre_ = nouveau_centre; }

protected:
    Point centre_;
};

// Un Cercle est une Forme
class Cercle : public Forme {
public:
    explicit Cercle( Point centre, int rayon ) : Forme{ centre }, rayon_{ rayon } {
            std::cout << "Cercle::Cercle( " << rayon << " )\n";
    }
    ~Cercle() { std::cout << "Cercle::~Cercle( " << rayon_ << " )\n"; }

    Cercle( const Cercle & c ) : Forme{ c }, rayon_{ c.rayon_ } {
        std::cout << "Cercle::Cercle( const Cercle & ( " << c.rayon_ << " ))\n";
    }

    // Un cercle sait se dessiner
    void dessine() { std::cout << "Cercle::dessine( " << rayon_ << " )\n"; }

private:
    int rayon_;
};

int main()
{
    Forme f{ Point{ 1, 1 }}, * pf{ &f };
    Cercle c{ Point{ 2, 2 }, 2 }, * pc{ &c };
    
    f = c;
    //c = static_cast< Cercle >( f );
    
    pf = pc;
    //pc = pf;
    pc = (Cercle *) pf;
    pc = static_cast<  Cercle * >( pf );
    
    Forme & rf = c;
    
    Cercle c2{ c };
    
    Cercle * c3 = new Cercle{ Point{ 3, 3 }, 3 };
    delete c3;

    pf = new Cercle{ Point{ 4, 4 }, 4 };
    delete pf;

    c.deplace( Point{ 5, 5 });
    pc->dessine();
    //pf->dessine();
}
