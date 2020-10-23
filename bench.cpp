#include "lib.hpp"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iomanip>

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    TItem elem;
    TVector <TItem> data;

    while(std::cin >> elem.key[0] >> elem.numeric >> elem.key[1]>> elem.key[2] >> elem.value){
        data.PushBack(elem);
    }
    TVector <TItem> result(data.Size());
    TVector <TItem> data2(data.Size());
    for (int i = 0; i < data.Size(); i++){
	data2[i] = data[i];
    }

    auto start = std::chrono::system_clock::now();
    RadixSort(data, result);
    auto finish = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << " :RadixSort Time in ms\n";

    auto start_2 = std::chrono::system_clock::now();
    std::stable_sort(data2.Begin(), data2.End());
    auto finish_2 = std::chrono::system_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish_2 - start_2).count() << " :STL Sort Time in ms\n";

    std::cout << "Number of lines in test " << data.Size() << " \n";


	return 0;
}

