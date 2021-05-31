#ifndef BIGNUMLIB_H
#define BIGNUMLIB_H

#include <string>

class BigNumLib
{
public:
    BigNumLib();

    std::string sum(std::string number1, std::string number2);
    //Negatiivisen vastauksen edessä "-", jos minusSign true (default = true)
    std::string substraction(std::string number1, std::string number2, bool minusSign = true);
    //fast = Karatsuba, slow = schoolbook
    std::string multiplyFast(std::string number1, std::string number2);
    std::string multiplySlow(std::string number1, std::string number2);

private:

    //Palauttaa totuusarvon, onko number1 pienempi kuin number2.
    bool isSmaller(std::string number1, std::string number2);
};

#endif // BIGNUMLIB_H
