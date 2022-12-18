#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
using namespace std;
basic_string <char>::size_type size, length;

int roll(string st)
{
    string data = "";                                                       
    int num = 0, diceType = 0, mod = 1, sum = 0, pos = 0;
    bool Modificate = false;

    while (pos < st.size())
    {
        if (st[pos] == 'd') // Если есть d, то берём число слева - количество костей и записываем в num
        {
            data = st[pos - 1];
            num = stoi(data);
            data = st[pos+1]; // Далее все числа правее d, берём как тип куба
            if (st[pos + 2] == '0') // Если 6, то не заходит, иначе прибавляем к строке data 0 справа
            {
                data += st[pos + 2];
            }
            diceType = stoi(data); // запоминает тип куба
        }
        if (st[pos] == '+' || st[pos] == '-') // Если есть модификатор добавляем его в переменную mod
        {
            data = st[pos + 1];
            mod = stoi(data);
            Modificate = true; // в конце у суммы прибавляем или вычитаем число 
            if (st[pos] == '-')
            {
                mod = -1*mod;
            }
        }
        pos++;
    }
    for (int i = 0; i < num; i++)
    {
        sum += rand() % diceType + 1;
    }
    if (Modificate)
    {
        sum += mod;
    }
    return sum;
}

int NumDice(string st)
{
    string data = "";
    int num = 0, pos = 0;
    while (pos < st.size())
    {
        if (st[pos] == 'd')
        {
            data = st[pos - 1];
            num = stoi(data);
        }
        pos++;
    }
    return num;
}

int DiceType(string st)
{
    string data = "";
    int DiceType = 0, pos = 0;
    while (pos < st.size())
    {
        if (st[pos] == 'd') 
        {
            data = st[pos + 1]; 
            if (st[pos + 2] == '0') 
            {
                data += st[pos + 2];
            }
            DiceType = stoi(data); 
        }
        pos++;
    }
    return DiceType;
}

int main()
{
    string Dice = "2d10";
    cout << Dice << endl;
    int MinDice = NumDice(Dice);
    int MaxDice = MinDice * DiceType(Dice);
    int ArrayDice[30];
    for (int j = 0; j < 30; j++)
    {
        ArrayDice[j] = 0;
    }
    ofstream result; 
    result.open("result.txt");
    srand(static_cast<unsigned int>(time(0))); 
    for (int i = 0; i < 10000; i++)
    {
        int n = roll(Dice);
        result << n << endl;
        ArrayDice[n-1] += 1;
    }
    result << "ArrayDice" << endl;
    for (int j = MinDice-1; j < MaxDice; j++)
    {
        result << ArrayDice[j] << endl;
    }
    cout << "Open result.txt in the path programm" << endl;
    return 0;
}