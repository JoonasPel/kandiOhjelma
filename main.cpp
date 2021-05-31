#include <iostream>
#include <string>
#include <chrono>
#include <bignumlib.h>
#include <NumbersForTesting.h>

using namespace std;

void testAsymptotic(int numberCount);

int main()
{
    BigNumLib Calculator;

    //Käytettävät numerot
    string number1 = "2875394687287539468";
    string number2 = "98668976999866897";

    cout << "Press ENTER to calculate";
    cin.get();
    cout << "\nCalculating...\n\n";

    //Aloittaa ajanoton
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    //Haluttu laskentaoperaatio. sum/substraction/multiply
    string answer = Calculator.sum(number1, number2);

    //Tulostaa vastauksen
    cout << "Answer: " << answer << "\n\n";

    //Lopettaa ajanoton ja ilmoittaa kuluneen ajan
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Elapsed time: " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "ns / " <<
            chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms\n\n";

    //Suorittaa tulon n*n eri kokoisille luvuille.
    //Parametria voi muokata. maksimi kahdeksan(8), jolloin n=12800 suurimmillaan.
    testAsymptotic(6);

    return 0;
}

void testAsymptotic(int numberCount)
{
    if(numberCount > 8) {numberCount = 8;}
    if(numberCount < 1) {numberCount = 1;}
    int LOOPSIZE = numberCount;

    std::cout << "test asymptotic, executing n*n(karatsuba) with different n sizes:\n\n";
    BigNumLib Calc;
    int tempTime = 0;
    int timeMilli;
    int numberSize = 100;

    for(int i=0; i<LOOPSIZE; i++)
    {
        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        auto diffLib = Calc.multiplyFast(numberList[i], numberList[i]);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        timeMilli = chrono::duration_cast<chrono::milliseconds>(end - begin).count();


        cout << "(n=" << numberSize << ") actual time: " << timeMilli <<
                "ms / theoretical time: ";
        if(tempTime == 0) {
            cout << "-\n\n";
        } else {
            cout << tempTime*3 <<"ms\n\n";
        }

        tempTime = timeMilli;
        numberSize *= 2;
    }
}
