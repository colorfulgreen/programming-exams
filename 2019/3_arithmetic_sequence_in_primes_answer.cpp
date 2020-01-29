#include <iostream>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <list>
#include <math.h>
using namespace std;

namespace test_3 {
    bool is_prime(int n) {
        int m = int(sqrt(n * 1.0f) + 1.f);
        for(int i=2; i<=m; i++) {
            if(n % i == 0) 
                return false;
        }
        return true;
    }

    void test3() {
        int a = 2;
        int b = 50;
        int len = b - a + 1;
        std::vector<int> prime_numbers;
        std::vector<bool> prime_mask(len);
        prime_numbers.reserve(len);
        std::cout << "numbers:" << std::endl;

        for(int i=a; i<b; i++) {
            if(is_prime(i)) {
                prime_numbers.push_back(i);
                std::cout << i << " ";
                prime_mask[i - a] = true;
            } else {
                prime_mask[i - a] = false;
            }
        }
        std::cout << std::endl;

        if(prime_numbers.size() < 2) {
            return;
        }

        std::cout << "arrays:" << std::endl;
        for(int i=0; i<prime_numbers.size(); i++) {
            for(int j=i+1; j < prime_numbers.size(); j++) {
                int int_val = prime_numbers[j] - prime_numbers[i];
                int cur_val = prime_numbers[j] + int_val;
                if(cur_val <= prime_numbers.back() && prime_mask[cur_val-a]) {
                    // avoid duplicated array
                    if(prime_numbers[i] - int_val >= prime_numbers.front() &&
                            prime_mask[prime_numbers[i] - int_val - a])
                        continue;
                }
                std::cout << prime_numbers[i] << " " << prime_numbers[j] << " ";
                while(cur_val <= prime_numbers.back() && prime_mask[cur_val-a]) {
                    std::cout << cur_val << " ";
                    cur_val = cur_val + int_val;
                }
                std::cout << std::endl;
            }
        }
    }
}

int main() 
{
    test_3::test3();
    return 0;
}
