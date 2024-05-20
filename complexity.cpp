#include <iostream>
#include <vector>
#include <limits>

enum class Operation {
	none,
	addition,
	multiplication
};

char printOperation(Operation operation) {
	switch(operation) {
	case Operation::addition:
		return '+';
	case Operation::multiplication:
		return '*';
	}
	return '?';
}

struct Entry {
	uint8_t complexity;
	Operation operation;
	uint64_t a;
	uint64_t b;
	
	Entry(uint8_t complexity, Operation operation, uint64_t a, uint64_t b)
	: complexity{complexity}, operation{operation}, a{a}, b{b} {}
};

int main() {
	std::vector<Entry> entries{
		{0u, Operation::none, 0u, 0u},
		{1u, Operation::none, 0u, 0u}
	};
	
	uint8_t const max = std::numeric_limits<uint8_t>::max();
	
	for (uint64_t i = 2u; i < 10000u; ++i) {
		uint8_t complexity = max;
		Operation operation = Operation::none;
		uint64_t a = 0u;
		uint64_t b = 0u;
		
		for (uint64_t j = 2u; j*j <= i; ++j) {
			if (i % j == 0u) {
				uint64_t k = i / j;
				uint8_t newComplexity = entries[j].complexity + entries[k].complexity;
				if (newComplexity < complexity) {
					complexity = newComplexity;
					operation = Operation::multiplication;
					a = j;
					b = k;
				}
			}
		}
		
		for (uint64_t j = 1u; 2u*j <= i; ++j) {
			uint64_t k = i - j;
			uint8_t newComplexity = entries[j].complexity + entries[k].complexity;
			if (newComplexity < complexity) {
				complexity = newComplexity;
				operation = Operation::addition;
				a = j;
				b = k;
			}
		}
		
		if (true) {
			std::cout << i << ": " << static_cast<int>(complexity) << ", " << a << printOperation(operation) << b << std::endl;
		}
		entries.emplace_back(complexity, operation, a, b);
	}
}