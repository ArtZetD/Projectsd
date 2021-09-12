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
enum Card_suits { // ������������ ������ �����
    SPADES, // ���� 
    CLUBS,  // ������ 
    HEARTS, // ����� 
    DIAMONDS // ����
};
enum Card_denomination // ������������ ���������� �����
{
    ACE = 1, // ��� 
    TWO = 2, // ���
    THREE = 3, // ��� 
    FOUR = 4, // ������ 
    FIVE = 5, // ����
    SIX = 6, // �����
    SEVEN = 7, // ���� 
    EIGHT = 8, // ������
    NINE = 9,  // ������
    TEN = 10, // ������
    JACK = 10, // �����
    QUEEN = 10, // ��������
    KING = 10, // ������
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

    void flip() { // ������� ���������� ����
        if (position) {
            position = 0;
            std::cout << "����� �������� ������" << std::endl;
        }
        else {
            position = 1;
            std::cout << "����� �������� ����" << std::endl;
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
    bool position = 0; /* 0 ����� �������� ������
                          1 ����� �������� ���� */

};
class Hand {
public:
    void Add(Card* p_card) { // ��������� ����� � ���� 
        cards.push_back(p_card);
    }

    void clear() { // ������� ���� 
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
    std::vector<Card*> cards; // �������� ������� � ��������� ����
    int sum;

};
class GenericPlayer : Hand
{
public:
    GenericPlayer(std::string __name) : name(__name)
    {}
    bool IsHitting() {
        if (sum == defeatValue) {
            return 0; // �� ����� �����
        }
        else if (sum < defeatValue)
            return 1; // ����� �����
    }

    bool IsBoosted() {
        if (sum > defeatValue) return 1; // ������� 
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
