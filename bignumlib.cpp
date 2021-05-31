#include "bignumlib.h"
#include <math.h>
#include <algorithm>

BigNumLib::BigNumLib()
{

}

std::string BigNumLib::sum(std::string number1, std::string number2)
{
    bool addMinusSign = false;
    //Tarkistaa onko kyseessä negatiivisia lukuja ja käyttää tarvittaessa
    //substraction funktiota. esim. -5+7 -> 7-5
    if(number1[0] == '-' && number2[0] == '-')
    {
        number1.erase(0,1);
        number2.erase(0,1);
        addMinusSign = true;
    } else if (number1[0] == '-')
    {
        number1.erase(0,1);
        return substraction(number2, number1);
    } else if (number2[0] == '-')
    {
        number2.erase(0,1);
        return substraction(number1, number2);
    }

    int n;
    int d = 0;
    int temp_sum;
    std::string sum;

    int nr1Length = number1.length();
    int nr2Length = number2.length();

    if(nr1Length > nr2Length) {
        n = nr1Length;
        number2.insert(0, n-nr2Length, '0');
        nr2Length = number2.length();
    } else {
        n = nr2Length;
        number1.insert(0, n-nr1Length, '0');
        nr1Length = number1.length();
    }

    //lisää nollilla lyhyemmästä stringistä yhtä pitkä kuin pidempi

    for (int i = 0; i <= n-1; ++i) {

        int a = number1.at(nr1Length-i-1)-48;
        int b = number2.at(nr2Length-i-1)-48;

        temp_sum = a + b + d;
        if(temp_sum > 9) {
            temp_sum -= 10;
            d = 1;
        } else {
            d = 0;
        }

        sum.insert(0, std::to_string(temp_sum));
    }

    //Lisätään 1 summan eteen, jos carry jäi "käyttämättä"
    if(d == 1) {
        sum.insert(0, "1");
    }

    //Lisätään miinus, jos summattiin kaksi negatiivista lukua
    if(addMinusSign)
    {
        sum.insert(0, "-");
    }

    return sum;
}

std::string BigNumLib::substraction(std::string number1, std::string number2, bool minusSign)
{
    //Suoritetaan vähennyslasku toisinpäin jos number1 < number2
    bool swapDone;
    if(isSmaller(number1, number2))
    {
        swap(number1, number2);
        swapDone = true;
    }

    int n;
    int d = 0;
    int temp_sub;
    std::string sub;

    int nr1Length = number1.length();
    int nr2Length = number2.length();
    //lisää nollilla lyhyemmästä stringistä yhtä pitkä kuin pidempi
    if(nr1Length > nr2Length) {
        n = nr1Length;
        number2.insert(0, n-nr2Length, '0');
        nr2Length = number2.length();
    } else {
        n = nr2Length;
        number1.insert(0, n-nr1Length, '0');
        nr1Length = number1.length();
    }

    for (int i = 0; i <= n-1; ++i) {

        int a = number1.at(nr1Length-i-1)-48;
        int b = number2.at(nr2Length-i-1)-48;

        temp_sub = a - b - d;
        if(temp_sub < 0) {
            temp_sub += 10;
            d = 1;
        } else {
            d = 0;
        }

        sub.insert(0, std::to_string(temp_sub));
    }

    // Poistetaan turhat nollat numeron edestä.
    sub.erase(0, sub.find_first_not_of('0'));

    //Lisätään miinus luvun eteen jos tarpeellista
    if(swapDone && minusSign)
    {
        sub.insert(0, "-");
    }

    return sub;
}

std::string BigNumLib::multiplyFast(std::string number1, std::string number2)
{
    if(number1 == "" || number1 == "0" || number2 == "" || number2 == "0")
    {
        return "0";
    } else if ((number1.length() < 2) || (number2.length() < 2))
    {
        return multiplySlow(number1, number2);
    }

    // Lasketaan lukujen koko
    auto m = std::max(ceil(number1.length() / 2), ceil(number2.length() / 2));

    std::string low1, low2, high1, high2;
    if(m >= number1.length())
    {
        low1 = number1;
        high2 = "0";
    } else
    {
        low1 = number1.substr(number1.length()-m, m);
        high1 = number1.substr(0, number1.length()-m);
    }

    if(m >= number2.length())
    {
        low2 = number2;
        high2 = "0";
    } else
    {
        low2 = number2.substr(number2.length()-m, m);
        high2 = number2.substr(0, number2.length()-m);
    }

    std::string c0 = multiplyFast(low1,low2);
    std::string c1 = multiplyFast( sum(low1,high1), sum(low2,high2));
    std::string c2 = multiplyFast(high1,high2);

    std::string appendFirst(m*2, '0');
    std::string appendSecond(m, '0');

    auto c = substraction(c1, c2, false);
    c = c.erase(0, c.find_first_not_of('0'));

    c = substraction(c, c0, false);
    c = c.erase(0, c.find_first_not_of('0'));

    auto first = c2.append(appendFirst);
    auto second = c.append(appendSecond);

    return sum(first, sum(second,c0));
}

std::string BigNumLib::multiplySlow(std::string number1, std::string number2)
{
    long long int temp1;
    long long int temp2;
    long long int temp_multiply;
    std::string temp_multiply_str;
    std::string total = "0";
    unsigned int number1Length = number1.length();
    unsigned int number2Length = number2.length();


    for(unsigned int i = 0; i< number1Length; ++i) {

        temp1 = number1.at(number1Length-i-1) - 48;

        for(unsigned int j = 0; j<number2Length; ++j) {

            temp2 = number2.at(number2Length-j-1) - 48;

            temp_multiply = temp1 * temp2;

            temp_multiply_str = std::to_string(temp_multiply);

            for(unsigned int x = 0; x<(i+j); ++x) {
                temp_multiply_str.push_back('0');
            }
            total = sum(total,temp_multiply_str);
        }
    }
    return total;
}

bool BigNumLib::isSmaller(std::string number1, std::string number2)
{

    int n1 = number1.length();
    int n2 = number2.length();

    if (n1 < n2)
        return true;
    if (n2 < n1)
        return false;

    for (int i = 0; i < n1; i++)
        if (number1[i] < number2[i])
            return true;
        else if (number1[i] > number2[i])
            return false;

    return false;
}
