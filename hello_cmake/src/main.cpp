#include <iostream>
#include <ranges>
#include <vector>

int main() {
    std::vector nums{1,2,3,4,5};

    auto even =
        nums
        | std::views::filter([](int x){
            return x % 2 == 0;
        });

    for (int x : even) {
        std::cout << x << '\n';
    }
}