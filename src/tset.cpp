// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(mp), MaxPower(mp)
{
    if (mp < 0)
    {
        throw out_of_range("Error: TSet::TSet(int mp) -> TSet index out of range");
    }
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower)
{

}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength())
{

}

TSet::operator TBitField()
{
    return BitField;
    //return FAKE_BITFIELD;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
    //return FAKE_INT;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
    //return FAKE_INT;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (&s != this)
    {
        MaxPower = s.MaxPower;
        BitField = s.BitField;
    }
    return *this;
    //return FAKE_SET;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower != s.MaxPower)
    {
        return 0;
    }
    return (BitField == s.BitField);
    //return FAKE_INT;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (this->operator==(s))
    {
        return 0;
    }
    return 1;
    //return FAKE_INT;
}
//int MaxPower;       // максимальная мощность множества
//TBitField BitField; // битовое поле для хранения характеристического вектора

TSet TSet::operator+(const TSet &s) // объединение
{
    int DopPower = (MaxPower > s.MaxPower) ? MaxPower : s.MaxPower;
    TSet DopSet(DopPower);
    DopSet.BitField = BitField | s.BitField;
    return DopSet;
    //return FAKE_SET;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem < 0 || Elem >= MaxPower)
    {
        throw out_of_range("Error: TSet::operator+(const int Elem) -> Element index out of range");
    }
    TSet DopSet(*this);
    DopSet.InsElem(Elem);
    return DopSet;
    //return FAKE_SET;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem < 0 || Elem >= MaxPower)
    {
        throw out_of_range("Error: TSet::operator+(const int Elem) -> Element index out of range");
    }
    TSet DopSet(*this);
    DopSet.DelElem(Elem);
    return DopSet;
    //return FAKE_SET;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    int DopPower = (MaxPower > s.MaxPower) ? MaxPower : s.MaxPower;
    TSet DopSet(DopPower);
    DopSet.BitField = BitField & s.BitField;
    return DopSet;
    //return FAKE_SET;
}

TSet TSet::operator~(void) // дополнение
{
    TSet DopSet(MaxPower);
    DopSet.BitField = ~BitField;
    return DopSet;
    //return FAKE_SET;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    for (int i = 0; i < s.GetMaxPower(); i++) {
        int el;
        istr >> el;
        s.InsElem(el);
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    for (int i = 0; i < s.GetMaxPower(); i++) {
        if (s.IsMember(i)) ostr << i << " ";
    }
    return ostr;
}