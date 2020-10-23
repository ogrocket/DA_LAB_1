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


int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    TItem elem;
    TVector <TItem> data;

     while(std::cin >> elem.key[0] >> elem.numeric >> elem.key[1]>> elem.key[2] >> elem.value)
    {
        data.PushBack(elem);
    }
    TVector <TItem> result(data.Size());
    RadixSort(data, result);

    for (int i = 0; i < data.Size(); i++){
        data[i].printer();
    }
}
