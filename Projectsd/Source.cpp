#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>    

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

    friend std::ostream& operator<<(std::ostream os, const Card& card) {
        if (card.position)
            os << "XX";
        else
            os << card.card_suits << ' ' << card.card_denomination << '\n';

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
class GenericPlayer : public Hand
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

    friend std::ostream& operator<<(std::ostream os, const GenericPlayer& genericPlayer) {
        os << genericPlayer.name << ' ' << genericPlayer.sum << '\n';
    }
};
class Player : public GenericPlayer
{
public:
    virtual bool IsHitting() {
        std::cout << "do you need one more card" << '\n' << "0 == no, 1 == yes";
        std::cin >> needCard;

        if (std::cin.fail())
        {
            std::cerr << "enter correct answer" << std::endl;
            std::cin.clear();
            std::cin.ignore(32767, '\n');
        }
        if (needCard)
            return true;
        else
            return false;
    }
    void Win()  //мне немного непонятно, но наверное чуть позже функция будет переделана 
    {
        if (sum == defeatValue)  std::cout << name << " YOU WIN!";
    }
    void Lose() {
        if (sum > defeatValue) std::cout << name << "YOU LOSE (((";
    }
    void Push() {
        //я понятия не имею как писать ничью, если мы не знаем значения карт у диллера(
    }
protected:
    bool needCard; // 0 нет 1 да  
};

class House : public GenericPlayer
{
public:
    virtual bool IsHitting()
    {
        if (sum < defeatValue) return true;
        else return false;
        if (sum <= HouseValue) return true;
        else return false;
    }
    void FlipFirstCard()
    {
        std::vector<Card*>::iterator it = cards.begin();
        for (it; cards.at(1); it++) {
            (*it)->flip();
        }
    }

protected:
    int HouseValue;
};

std::ostream& endll(std::ostream& os) { // task 2
    return std::cout << '\n' << '\n' << std::flush;
}

int main() {
    std::cout << 56 << endll << 54 << '\n';

    while (true)
    {
        std::cout << "Enter a int value: ";
        int a;
        std::cin >> a;

        if (std::cin.fail())
        {
            std::cerr << "enter correct value" << std::endl;
            std::cin.clear();
            std::cin.ignore(32767, '\n');
        }
        else
            std::cout << a << std::endl;
    };
    return 0;
}
