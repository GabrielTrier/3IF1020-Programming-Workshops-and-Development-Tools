/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°4
 * Dominique Marcadet - 2022 - CC BY-SA
 *
 * Forme_v2.cpp
 *
 * Compilation :
 *     c++ -std=c++20 -o Forme_v2 Forme_v2.cpp
 * Exécution :
 *     ./Forme_v2
 */


#include <iostream>

class Point {
public:
    Point( int x, int y ) : x_{ x }, y_{ y } {}
    //virtual ~Point() {}
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
    virtual ~Forme() { std::cout << "Forme::~Forme( " << centre_ << ")\n"; }

    void deplace( Point nouveau_centre ) { centre_ = nouveau_centre; }
    virtual void dessine() { std::cout << "Forme::dessine()\n"; }

protected:
    Point centre_;
};

class Cercle : public Forme {
public:
    explicit Cercle( Point centre, int rayon ) : Forme{ centre }, rayon_{ rayon } {
            std::cout << "Cercle::Cercle( " << rayon << " )\n";
    }
    ~Cercle() { std::cout << "Cercle::~Cercle( " << rayon_ << " )\n"; }

    void dessine() override { std::cout << "Cercle::dessine( " << rayon_ << " )\n"; }

private:
    int rayon_;
};

int main()
{
    Cercle c( Point( 1, 1), 1 );
    c.deplace( Point( 2, 2 ));
    c.dessine();

    Forme * pf = &c;
    pf->dessine();
    
    pf = new Cercle( Point( 3, 3), 3 );
    pf->dessine();
    delete pf;
    
    std::cout << "sizeof( Point ) = " << sizeof( Point ) << "\n";
}
