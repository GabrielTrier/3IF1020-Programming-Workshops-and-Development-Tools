    /*
    * Cursus CentraleSupélec - Dominante Informatique et numérique
    * 3IF1020 - Concepts des langages de programmation - TP n°2
    *
    * Number.hpp
    */

    #ifndef NUMBER_HPP_INCLUDED
    #define NUMBER_HPP_INCLUDED

    #include <cctype>
    #include <iostream>
    #include <stdexcept>
    #include <string>
    #include <utility>

    class Number {
    public:
        Number( unsigned long l ); // Constructeur à partir d'un entier
        Number( const Number & other ); // Constructeur de copie
        Number( std::string s );  // Constructeur de signature
        Number(Number&& other) noexcept; // Constructeur par déplacement
        ~Number(); // Destructeur
    
        void print( std::ostream & out ) const; // Affichage

        Number & operator=(Number other ); // Opérateur d'affectation
        
        Number operator+(const Number& other) const;
        Number operator*(const Number& other) const;
        Number& operator+=(unsigned int i); 
        Number& operator*=(unsigned int i);

        static Number factorial(unsigned int i); // Factoriel 
    private:
        using DigitType = unsigned int;
        // Un seul chiffre décimal par maillon : l'objectif ici n'est pas la performance
        static const DigitType number_base{ 10u };

        // Classe interne pour les maillons de la liste chaînée
        struct Digit {
            Digit(DigitType digit = 0, Digit* next = nullptr)
                : digit_(digit), next_(next) {}

            Digit(std::string s) : digit_(0), next_(nullptr) {
                if (s.empty()) {
                    throw std::invalid_argument("Chaîne vide!");
                }
                // Traite chaque chiffre en partant du dernier
                Digit* current = this;
                for (auto it = s.rbegin(); it != s.rend(); ++it) {
                    if (!std::isdigit(*it)) {
                        throw std::invalid_argument("Caractère non décimal!");
                    }
                    // Convertit le caractère en chiffre et affecte au Digit actuel
                    current->digit_ = static_cast<unsigned int>(*it - '0');
                    // Crée le maillon suivant sauf pour le dernier chiffre
                    if (it + 1 != s.rend()) {
                        current->next_ = new Digit();
                        current = current->next_;
                    }
                }
            }
            ~Digit() {delete next_;}

            void print(std::ostream& out) const {
                if (next_) {
                    next_->print(out);
                }
                out << digit_;
            }
            // Méthode swap pour échanger les valeurs de deux objets Digit
            void swap(Digit &other)
            {
                // Échanger les valeurs des membres digit_ et next_
                std::swap(digit_, other.digit_);
                std::swap(next_, other.next_);
            }
            //Remplacement par surcharge
            Digit& operator+=(unsigned int i) {
                digit_ += i;
                if (digit_ >= number_base) {
                    unsigned int carry = digit_ / number_base;
                    digit_ %= number_base;
                    if (next_) {
                        next_->operator+=(carry);
                    } else {
                        next_ = new Digit(carry);
                    }
                }
                return *this;
            }
            //Remplacement par surcharge
            Digit& operator*=(unsigned int i) {
                unsigned int product = digit_ * i;
                unsigned int carry = product / number_base;
                digit_ = product % number_base;

                if (next_) {
                    next_->operator*=(i);
                    next_->operator+=(carry);
                } else if (carry > 0) {
                    next_ = new Digit(carry);
                }
                return *this;
            }

            DigitType digit_;
            Digit* next_;
        };
        Digit* first_;
    };

    inline std::ostream& operator<<(std::ostream& out, const Number& n) {
        n.print(out);
        return out;
    }

    std::istream &operator>>(std::istream &in, Number &n);

    #endif
