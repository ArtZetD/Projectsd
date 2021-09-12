#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>    
/////////////////////////////////////////////////TASK 1\////////////////////////////

template<class  T>
class Pair1
{
public:
    Pair1(T _val, T _secVal) : value_first(_val), value_second(_secVal)
    {
    }

    const T first() {
        return value_first;
    }

    const  T second() {
        return value_second;
    }

protected:
    T value_first;
    T value_second;
};
/////////////////////////////////////////////////TASK 2\////////////////////////////
template<class  T, class _T>
class Pair
{
public:
    Pair(T _val, _T _secVal) : value_first(_val), value_second(_secVal)
    {
    }

    const T first() const {
        return value_first;
    }

    const  _T second() const {
        return value_second;
    }



protected:
    T value_first;
    _T value_second;
};

template<typename U>
class StringValuePair : public Pair<std::string, U>
{
public:
    StringValuePair(std::string _first, U _second)
        :Pair<std::string, U>(_first, _second) {}
};












///////////////////////////////////////////////TASK 3\////////////////////////////////
enum Card_suits { // перечисление мастей карты
    SPADES, // ПИКИ 
    CLUBS,  // КРЕСТИ 
    HEARTS, // ЧЕРВИ 
    DIAMONDS // БУБЫ
};
enum Card_denomination // перечисление достоинств карты
{
    ACE = 1, // ТУЗ 
    TWO = 2, // ДВА
    THREE = 3, // ТРИ 
    FOUR = 4, // ЧЕТЫРЕ 
    FIVE = 5, // ПЯТЬ
    SIX = 6, // ШЕСТЬ
    SEVEN = 7, // СЕМЬ 
    EIGHT = 8, // ВОСЕМЬ
    NINE = 9,  // ДЕВЯТЬ
    TEN = 10, // ДЕСЯТЬ
    JACK = 10, // ВАЛЕТ
    QUEEN = 10, // КОРОЛЕВА
    KING = 10, // КОРОЛЬ
};

class Card
{
public:
    Card(Card_suits _suits, Card_denomination _denomination)
        :card_suits(_suits), card_denomination(_denomination)
    {

    }
    int  getValue() {
        return card_denomination;
    }

    void flip() { // функция переворота карт
        if (position) {
            position = 0;
            std::cout << "карта рубашкой наверх" << std::endl;
        }
        else {
            position = 1;
            std::cout << "карта рубашкой вниз" << std::endl;
        }
    }
    bool operator< (const Card& _card)
    {
        return card_denomination < _card.card_denomination;
    }
    bool operator> (const Card& _card)
    {
        return card_denomination > _card.card_denomination;
    }
    bool operator<= (const Card& _card)
    {
        return card_denomination <= _card.card_denomination;
    }
    bool operator>= (const Card& _card)
    {
        return card_denomination >= _card.card_denomination;
    }
    bool operator== (const Card& _card)
    {
        return card_denomination == _card.card_denomination;
    }
    bool operator!= (const Card& _card)
    {
        return card_denomination != _card.card_denomination;
    }
    Card operator^ (const Card& _card) const
    {
        Card C1(card_suits, card_denomination);
        C1.card_denomination = static_cast<Card_denomination>(C1.card_denomination ^ _card.card_denomination);
        return C1;
    }

protected:
    Card_suits card_suits;
    Card_denomination card_denomination;
    bool position = 0; /* 0 карта рубашкой наверх
                          1 карта рубашкой вниз */

};
class Hand {
public:
    void Add(Card* p_card) { // добавляет карту в руку 
        cards.push_back(p_card);
    }

    void clear() { // очищает руку 
        std::vector<Card*>::const_iterator it = cards.cbegin();
        cards.erase(it, cards.end());
    }
    int GetValue() {
        sum = 0;
        std::vector<Card*>::const_iterator it = cards.cbegin();
        while (it != cards.end()) {
            int Value = (*it)->getValue();
            if (sum <= 10) {
                if (Value == 1) {
                    sum += 11;
                }
                else {
                    sum += Value;

                }
            }
            else {
                sum += Value;

            }
            ++it;
        }

        return  sum;
    }

public:
    void print() {
        std::vector<Card*>::iterator it = cards.begin();
        for (it; it != cards.end(); it++) {
            std::cout << (*it)->getValue() << ' ';
        }

        std::cout << '\n';

    };
protected:
    std::vector<Card*> cards; // создание вектора с обьектами карт
    int sum;

};
class GenericPlayer : Hand
{
public:
    GenericPlayer(std::string __name) : name(__name)
    {}
    bool IsHitting() {
        if (sum == defeatValue) {
            return 0; // не нужна карта
        }
        else if (sum < defeatValue)
            return 1; // нужна карта
    }

    bool IsBoosted() {
        if (sum > defeatValue) return 1; // перебор 
    }

    void Boost() {
        std::cout << name << IsBoosted() << std::endl;
    }
protected:
    std::string name;
    int defeatValue = 21;


};

int main() {

    Pair1<int> p1(6, 9);
    std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    Pair1<double> p2(3.4, 7.8);
    std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    StringValuePair<int> svp("Amazing", 7);
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

    return 0;
}
