#include <iostream>
#include <cstdlib>
#include <iomanip>

class TItem{
public:
    int numeric = 0;
    char key[3]={'A','A','A'};
    char value[65] = "";
    void printer(){
        std::cout << key[0] << " ";
        std::cout << std::setfill('0') << std::setw(3);
        std::cout << numeric << " ";
        std::cout << key[1] << key[2] << "\t" ;
        std::cout << value << "\n";
    }
    bool operator<(const TItem &op2) const{
        if(this->key[0] < op2.key[0])   {return true;}
        if(this->key[0] > op2.key[0])   {return false;}
        if(this->numeric < op2.numeric) {return true;}
        if(this->numeric > op2.numeric) {return false;}
        if(this->key[1] < op2.key[1])   {return true;}
        if(this->key[1] > op2.key[1])   {return false;}
	if(this->key[2] < op2.key[2])   {return true;}
        if(this->key[2] > op2.key[2])   {return false;}
        return false;
    }

};

template <typename T>
class TVector{
private:
    T* Data;
    int Capacity; //Вместимость
    int CurSize; //Текущее кол-во занятых ячеек

    void Extend(){      //Увеличиваем количество памяти, выделенное под вектор
        Data = (T*)realloc(Data, 2 * Capacity * sizeof(T));
        Capacity *= 2;
    }

public:
    TVector(){
        Data = (T*)calloc(64, sizeof(T));
        Capacity = 16;
        CurSize = 0;
    }

    TVector(int size){
        Data = (T*)calloc(size, sizeof(T));
        Capacity = size;
        CurSize = size;
    }

    ~TVector(){
        free(Data);
    }

    int Size(){
        return CurSize;
    }

    void PushBack(T elem){
        if (CurSize == Capacity){
            Extend();
        }

        Data[CurSize] = elem;
        CurSize++;
    }

    T& operator[] (int i){
        return Data[i];
    }

    T* Begin(){
	return &Data[0];
    }

    T* End(){
	return &Data[CurSize];
    }

};

void SortChar(TVector <TItem>& data, TVector <TItem>& result, int j){
    int counter[26] = {0};      //Cоздали счётчики и проинициализировали нулями

    for(int i = 0; i < data.Size(); i++){   // Заполнили счётчики
        counter[ (int)data[i].key[j] - 65 ]++;
    }

    for(int i = 1; i < 26; i++){    // Суммируем с суммой предыдущих
        counter[i] += counter[i-1];
    }

    for(int i = data.Size() - 1; i > -1; i--){
        result[ counter[(int)data[i].key[j] - 65] - 1] = data[i];
        counter[(int)data[i].key[j] - 65]--;
    }
}

void SortInteger(TVector <TItem>& data, TVector <TItem>& result){
    int counter[1000] = {0};

    for(int i = 0; i < data.Size(); i++){
        counter[data[i].numeric]++;
    }

    for(int i = 1; i < 1000; i++){
        counter[i] += counter[i-1];
    }

    for(int i = data.Size() - 1; i > -1; i--){
        result[ counter[data[i].numeric] -1] = data[i];
        counter[data[i].numeric]--;
    }

}

void RadixSort(TVector <TItem>& data, TVector <TItem>& result){
    SortChar(data, result, 2);
    SortChar(result, data, 1);
    SortInteger(data, result);
    SortChar(result, data, 0);
}

