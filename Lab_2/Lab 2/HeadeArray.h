#pragma once

#include<iostream>
#include <string>

template <typename T>
class ArrayClass final
{
private:
    int a_size; // ðàçìåð ìàññèâà
    int a_capacity; // ïàìÿòü íà 1 ýëåìåíò
    T* a_data;
    const int caparacityMod = 2;

public:
    //Ïîëó÷åíèå ñòàíäàðòíîãî çàïàñà ìàññèâà
    int defaultCapacity() const 
    {
        return 8;
    }
    //Ïîëó÷åíèå àäðåñà ìàññèâà
    T* data() const
    {
        return a_data;
    }
    //Ïîëó÷åíèå ðàçìåðà ìàññèâà
    int size() const
    {
        return a_size;
    }
    //Ïîëó÷åíèå îáúåìà ìàññèâà
    int capacity() const
    {
        return a_capacity;
    }
    //Êîíñòàíñòíûé îïåðàòîð èíäåêñèðîâàíèÿ
    const T& operator[] (int index) const 
    {
        return a_data[index];
    }
    //Îïåðàòîð èíäåêñèðîâàíèÿ
    T& operator[] (int index) 
    {
        return a_data[index];
    }
    //Êîïèðóþùèé êîíñòðóêòîð
    ArrayClass(const ArrayClass& other) 
    {
        a_data = (T*)malloc(sizeof(T) * other.a_capacity);
        for (int i = 0; i < other.a_size; i++) {
            new(a_data + i) T(other.a_data[i]);
        }
        a_size = other.a_size;
        a_capacity = other.a_capacity;
    }
    //Êîïèðóþùèé îïåðàòîð ïðèñâàèâàíèÿ 
    void swap(ArrayClass& other) 
    {
        std::swap(a_data, other.a_data);
        std::swap(a_size, other.a_size);
        std::swap(a_capacity, other.a_capacity);
    }
    ArrayClass& operator = (const ArrayClass& other)
    {
        ArrayClass<T> b_data = other;
        swap(b_data);
        return *this;
    }
    //Ïåðåìåùàþùèé êîíñòðóêòîð
    ArrayClass(ArrayClass&& other) 
    {
        a_data = other.a_data;
        a_size = other.a_size;
        a_capacity = other.a_capacity;
        other.a_data = nullptr;
        other.a_size = 0;
        other.a_capacity = 0;
    }
    //Ïåðåìåùàþùèé îïåðàòîð ïðèñâàèâàíèÿ
    ArrayClass& operator=(ArrayClass&& other)
    {
        if (this != &other) 
        {
            for (int i = 0; i < a_size; i++) 
            {
                a_data[i].~T();
            }
            free(a_data);
            a_data = other.a_data;
            a_size = other.a_size;
            a_capacity = other.a_capacity;
            other.a_data = nullptr;
            other.a_size = 0;
            other.a_capacity = 0;
        }
        return *this;
    }

    ArrayClass() //Êîíñòðóêòîð ïî óìîë÷àíèþ
    {
        a_size = 0;
        a_capacity = 8;
        a_data = (T*)malloc(a_capacity * sizeof(T));
    }

    ArrayClass(int caparacity) // Êîíñòðóêòîð ñî çíà÷åíèåì ïàìÿòè íà îäèí ýëåìåíò
    {
        a_size = 0;
        a_capacity = caparacity;
        a_data = (T*)malloc(a_capacity * sizeof(T));
    }

    ~ArrayClass() // äeñòðóêòîð
    {
        for (int i = 0; i < a_size; ++i)
        {
            a_data[i].~T();
        }
        free(a_data);
    }

    int insert(const T& value) //ïîñëåäíåãî ýëåìåíòà
    {
        if (a_size == a_capacity)
        {
            a_capacity *= caparacityMod;
            T* b_data = (T*)malloc((a_capacity) * sizeof(T));
            for (int i = 0; i < a_size; i++)
            {
                new(b_data + i) T(std::move(a_data[i]));
                a_data[i].~T();
            }
            free(a_data);
            a_data = b_data;
        }
        new(a_data + a_size) T(value);
        a_size += 1;
        return a_size - 1;
    }

    int insert(int index, const T& value) // ïî èíäåêñó
    {
        if (index >= a_size)
        {
            insert(value);
        }
        if (a_size >= a_capacity) // èñïðàâèë == íà >= õîòÿ â òåîðèè ñàéçà áîëüøå êàïàñèòè áûòü íå äîëæíî 
        {
            a_capacity *= caparacityMod;
            T* b_data = (T*)malloc(sizeof(T) * a_capacity);
            for (int i = 0; i < index; i++)
            {
                new (b_data + i) T(std::move(a_data[i]));
            }
            new (b_data + index) T(value);
            for (int i = index + 1; i < a_size + 1; i++)
            {
                new (b_data + i) T(std::move(a_data[i - 1]));
            }
            for (int i = 0; i < a_size; i++)
            {
                a_data[i].~T();
            }
            free(a_data);
            a_data = b_data;
        }
        else // ÄÎäåëàòü
        {
            for (int i = a_size; i > index; i--)
                {
                    new (a_data + i) T(std::move(a_data[i - 1]));
                    a_data[i - 1].~T();
                }
            new (a_data + index) T(value);
        }
        a_size++;
        return index;
    }

    void remove(int index) // Äîäåëàòü
    {
        if ((index >= a_size || a_size == 0 || index < 0) == false)
        {

            for (int i = index; i < a_size - 1; i++)
            {
                a_data[i].~T();
                new (a_data + i) T(std::move(a_data[i + 1]));
            }
            a_data[a_size-1].~T();
            a_size--;
        }
    }

    // Èòåðàòîðû
    class ConstIterator 
    {
    protected:
        ArrayClass<T>* arrayPtr_;
        T* curPtr_;
        bool isReversed_;
        int direction_;
    public:
        ConstIterator(ArrayClass<T>* other, bool isReversed) 
        {
            arrayPtr_ = other;
            isReversed_ = isReversed;
            if (isReversed) 
            {
                direction_ = -1;
                curPtr_ = other->a_data + (other->a_size - 1);
            }
            else {
                direction_ = 1;
                curPtr_ = other->a_data;
            }
        }
        const T& get() const 
        {
            return *curPtr_;
        }
        void next()
        {
            curPtr_ += direction_;
        }
        bool hasCurrent() const 
        {
            return ((curPtr_ >= arrayPtr_->a_data) && (curPtr_ <= arrayPtr_->a_data + (arrayPtr_->a_size - 1)));
        }
    };
    //Èòåðàòîð 
    class Iterator : public ConstIterator
    {
    public:
        Iterator(ArrayClass<T>* other, bool isReversed) : ConstIterator(other, isReversed) {}
        void set(const T& value)
        {
            ConstIterator::curPtr_->~T();
            new (ConstIterator::curPtr_) T(value);
        }
    };
    //Ôóíêöèè ñîçäàíèÿ èòåðàòîðîâ
    Iterator iterator() 
    {
        return Iterator(this, false);
    }
    ConstIterator iterator() const 
    {
        return ConstIterator(this, false);
    }
    Iterator reverseIterator()
    {
        return Iterator(this, true);
    }
    ConstIterator reverseIterator() const 
    {
        return ConstIterator(this, true);
    }
};

int main()
{
    ArrayClass<int> a;
    for (int i = 0; i < 10; ++i)
    {
        a.insert(i + 1);
    }
    for (auto it = a.iterator(); it.hasCurrent(); it.next())
    {
        std::cout << it.get() << std::endl;
    }
    return EXIT_SUCCESS;
}







int insert(int index, const T& value) {

    if (_size == _capacity) {
        _capacity *= _expandCapacityModifier;

        T* p = (T*)malloc((_capacity) * sizeof(T));

        for (int i = 0; i < index; ++i) {
            new(p + i) T(std::move(_data[i]));
        }
        new(p + index) T(value);

        for (int i = index + 1; i < _size + 1; ++i) {
            new(p + i) T(std::move(_data[i - 1]));
        }

        for (int i = 0; i < _size; ++i) {
            _data[i].~T();
        }
        free(_data);

        _data = p;


    }
    else {

        for (int i = index + 1; i < _size + 1; ++i) {
            new(_data + i) T(std::move(_data[i - 1]));
        }
        _data[index].~T();
        new(_data + index) T(value);

    }
    _size += 1;

    return index;
}
