#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>    

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

    friend std::ostream& operator<<(std::ostream os, const Card& card) {
        if (card.position)
            os << "XX";
        else
            os << card.card_suits << ' ' << card.card_denomination << '\n';

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
class GenericPlayer : public Hand
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
    void Win()  //��� ������� ���������, �� �������� ���� ����� ������� ����� ���������� 
    {
        if (sum == defeatValue)  std::cout << name << " YOU WIN!";
    }
    void Lose() {
        if (sum > defeatValue) std::cout << name << "YOU LOSE (((";
    }
    void Push() {
        //� ������� �� ���� ��� ������ �����, ���� �� �� ����� �������� ���� � �������(
    }
protected:
    bool needCard; // 0 ��� 1 ��  
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
