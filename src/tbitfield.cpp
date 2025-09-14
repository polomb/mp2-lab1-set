// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len < 0)
    {
        throw out_of_range("Error: Bit index out of range");
    }
    BitLen = len;
    if ((len % (sizeof(TELEM) * 8)) == 0)
    {
        MemLen = (len / (sizeof(TELEM) * 8));
    }
    else
    {
        MemLen = (len / (sizeof(TELEM) * 8)) + 1;
    }
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen; 
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n < 0 || n >= BitLen)
    {
        throw out_of_range("Error: Bit index out of range");
    }
    return n / (sizeof(TELEM) * 8);
    //return FAKE_INT;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0 || n >= BitLen)
    {
        throw out_of_range("Error: Bit index out of range");
    }
    TELEM bitPos = n % (sizeof(TELEM) * 8);
    return  1 << bitPos;
    //return FAKE_INT;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
    //return FAKE_INT;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n >= BitLen)
    {
        throw out_of_range("Error: Bit index out of range");
    }
    pMem[this->GetMemIndex(n)] |= this->GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n >= BitLen)
    {
        throw out_of_range("Error: Bit index out of range");
    }
    pMem[this->GetMemIndex(n)] &= ~this->GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n >= BitLen)
    {
        throw out_of_range("Error: Bit index out of range");
    }
    int REAL_INT = ((pMem[this->GetMemIndex(n)] & this->GetMemMask(n)) != 0);
    return REAL_INT;
    //return FAKE_INT;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (&bf != this) {
        delete[] pMem;
        BitLen = bf.BitLen;  
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (unsigned int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
    return *this;
    //return FAKE_BITFIELD;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
    {
        return 0;
    }
    for (int i = 0; i < MemLen; i++)
    {
        if (pMem[i] != bf.pMem[i])
        {
            return 0;
        }
    }
    return 1;
    //return FAKE_INT;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (this->operator==(bf))
    {
        return 0;
    }
    return 1;
    //return FAKE_INT;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int DopLen = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
    TBitField DopField(DopLen);

    DopLen = (MemLen < DopField.MemLen) ? MemLen : DopField.MemLen;
    for (int i = 0; i < DopLen; i++)
    {
        DopField.pMem[i] = pMem[i];
    }

    DopLen = (bf.MemLen < DopField.MemLen) ? bf.MemLen : DopField.MemLen;
    for (int i = 0; i < DopLen; i++)
    {
        DopField.pMem[i] |= bf.pMem[i];
    }

    return DopField;
    //return FAKE_BITFIELD;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int DopLen = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
    TBitField DopField(DopLen);

    DopLen = DopField.MemLen;
    for (int i = 0; i < DopLen; i++)
    {
        DopField.pMem[i] = pMem[i] & bf.pMem[i];
    }

    return DopField;
    //return FAKE_BITFIELD;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField DopField(BitLen);

    for (int i = 0; i < MemLen; i++)
    {
        DopField.pMem[i] = ~pMem[i];
    }

    int DopBits = BitLen % (sizeof(TELEM) * 8);
    if (DopBits > 0)
    {
        TELEM maska = (1 << DopBits) - 1;
        DopField.pMem[MemLen - 1] &= maska;
    }

    return DopField;
    //return FAKE_BITFIELD;
}

//int  BitLen; // длина битового поля - макс. к-во битов
//TELEM* pMem; // память для представления битового поля
//int  MemLen; // к-во эл-тов Мем для представления бит.поля

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    string input;
    istr >> input;

    for (int i = 0; i < bf.BitLen; i++)
    {
        bf.ClrBit(i);
    }

    for (int i = 0; i < input.length() && i < bf.BitLen; i++)
    {
        char c = input[input.length() - 1 - i];
        if (c == '1')
        {
            bf.SetBit(i);
        }
    }

    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = bf.BitLen - 1; i >= 0; i--)
    {
        ostr << (bf.GetBit(i) ? '1' : '0');

        if (i != 0 && i % 8 == 0)
        {
            ostr << ' ';
        }
    }
    return ostr;
}
