#include <iostream>
#include <vector>

void generate_combinations(const std::vector<int>& elements, int length, std::vector<int>& current_combination, int start) {
    if (length == 0) {
        // Print or use the combination here
        for (int element : current_combination) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
        return;
    }

    for (int i = start; i < elements.size(); ++i) {
        current_combination.push_back(elements[i]);
        generate_combinations(elements, length - 1, current_combination, i + 1); // Start from the next index to avoid duplicates
        current_combination.pop_back();
    }
}

int main() {
    std::vector<int> elements = {1, 2, 3, 4}; // Example set of elements

    for (int length = 1; length <= elements.size(); ++length) {
        std::vector<int> current_combination;
        generate_combinations(elements, length, current_combination, 0);
    }

    return 0;
}
