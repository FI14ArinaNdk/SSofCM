#include "BigInt.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {

    BigInt num1("cbe75e23d145c3dc78d76739b63d337cc33268e08ce4ea7319c38b7d057b1747d59010759f3b015858dc5a9d05ddbbd3ef41a368ba1ca6d8a6d967f2fed6b7033e7f56d46beae7c259cce870e0879f49849c956b6b6810be90d0c50c54daaef41b2b1c6e3c7b2ed35da549a7c95fd551841ea90e4196e8272b42ea3dba7cdcef");
    BigInt num2("d0a166bef0f8cd687a755ce64c4736e2621fe749af3c4170354c55a2728037612cf3b134550036e2de888e049ee782ab82ab99ba3442a3b4b8eb21c9f79778cff4ce0c2109a02fd18163e5155146d156b92176c03ba2b87ee53ba78217529616eea6e8432b0f736b09e30e89f3ceeaea11fb94dacd994e1fd8a6059cc14a58b2");

    BigInt sum = num1 + num2;
    cout << "num1 + num2 = " << sum.toHexString() << endl;
    cout << "\t" << endl;
    BigInt difference = num1 - num2;
    cout << "num1 - num2 = " << difference.toHexString() << endl;
    cout << "\t" << endl;
    BigInt product = num1 * num2;
    cout << "num1 * num2 = " << product.toHexString() << endl;
    cout << "\t" << endl;
    BigInt quotient = num1 / num2;
    cout << "num1 / num2 = " << quotient.toHexString() << endl;
    cout << "\t" << endl;
    BigInt remainder = num1 % num2;
    cout << "num1 mod num2 = " << remainder.toHexString() << endl;
    cout << "\t" << endl;
    BigInt squared = num1.Square();
    cout << "num1 ^ 2 = " << squared.toHexString() << endl;
    cout << "\t" << endl;
    BigInt power = num1.Pow(9);
    cout << "num1 ^ 9 = " << power.toHexString() << endl;

    cout << "\t" << endl;
    cout << "\t" << endl;

    vector<int> lenght = { 2, 50 };
        for (const auto lenght : lenght) {
            double AdditionTime = 0.0;
            double SubtractionTime = 0.0;
            double MultiplicationTime = 0.0;
            double DivisionTime = 0.0;
            double ModTime = 0.0;
            double SquareTime = 0.0;
            double PowTime = 0.0;

            for (int i = 0; i < 150; i++) {
                BigInt num1;
                BigInt num2;
                num1.generateRandomHEXNumber(lenght);
                num2.generateRandomHEXNumber(lenght);

                auto AdditionStartTime = high_resolution_clock::now();
                BigInt resultAdd = num1 + num2;
                auto AdditionEndTime = high_resolution_clock::now();
                AdditionTime += duration_cast<nanoseconds>(AdditionEndTime - AdditionStartTime).count();

                auto SubtractionStartTime = high_resolution_clock::now();
                BigInt resultSub = num1 - num2;
                auto SubtractionEndTime = high_resolution_clock::now();
                SubtractionTime += duration_cast<nanoseconds>(SubtractionEndTime - SubtractionStartTime).count();

                auto MultiplicationStartTime = high_resolution_clock::now();
                BigInt resultMul = num1 * num2;
                auto MultiplicationEndTime = high_resolution_clock::now();
                MultiplicationTime += duration_cast<nanoseconds>(MultiplicationEndTime - MultiplicationStartTime).count();

                auto DivisionStartTime = high_resolution_clock::now();
                BigInt resultDiv = num1 / num2;
                auto DivisionEndTime = high_resolution_clock::now();
                DivisionTime += duration_cast<nanoseconds>(DivisionEndTime - DivisionStartTime).count();

                auto ModStartTime = high_resolution_clock::now();
                BigInt resultMod = num1 % num2;
                auto ModEndTime = high_resolution_clock::now();
                ModTime += duration_cast<nanoseconds>(ModEndTime - ModStartTime).count();

                auto SquareStartTime = high_resolution_clock::now();
                BigInt resultSquare = num1.Square();
                auto SquareEndTime = high_resolution_clock::now();
                SquareTime += duration_cast<nanoseconds>(SquareEndTime - SquareStartTime).count();

                auto PowStartTime = high_resolution_clock::now();
                BigInt resultPow = num1.Pow(9);
                auto PowEndTime = high_resolution_clock::now();
                PowTime += duration_cast<nanoseconds>(PowEndTime - PowStartTime).count();

            }
             
            double AverAdditionTime = AdditionTime / 150.0;
            double AverSubtractionTime = SubtractionTime / 150.0;
            double AverMultiplicationTime = MultiplicationTime / 150.0;
            double AverDivisionTime = DivisionTime / 150.0;
            double AverModTime = ModTime / 150.0;
            double AvarSquareTime = SquareTime / 150.0;
            double AvarPowTime = PowTime / 150.0;

            cout << "Lenght " << lenght << endl;
            cout << "Average Addition Time: " << AverAdditionTime << " nanoseconds" << endl;
            cout << "Average Subtraction Time: " << AverSubtractionTime << " nanoseconds" << endl;
            cout << "Average Multiplication Time: " << AverMultiplicationTime << " nanoseconds" << endl;
            cout << "Average Division Time: " << AverDivisionTime << " nanoseconds" << endl;
            cout << "Avarange Mod Time: " << AverModTime << "nanoseconds" << endl;
            cout << "Avarange Square Time: " << AvarSquareTime << "nanoseconds" << endl;
            cout << "Avarange Pow Time: " << AvarPowTime << "nanoseconds" << endl;
            cout << "\t" << endl;
        }

    cout << "\t" << endl;
    cout << "\t" << endl;

    cout << "Test time:" << endl;

    BigInt A("0a69fc4d5736a49d9b2a40c7a08c569a1607007d5174b5f222909b5d39afbad90b5");  
    BigInt B("07b06f577de31599e535a552ba0b9c1c7a46a8c9e8d660f9277f3907129a");
    BigInt C("01dffd61a19751e050cb66e88545d59da1a9825ac2019f5b256c63545a812a9d0bde");

    BigInt result1 = (A + B) * C;
    BigInt result2 = C * (A + B);
    BigInt result3 = A * C + B * C;

    if (result1 == result2 && result2 == result3) {
       cout << "Test 1: (A + B) * C = C * (A + B) = A * C + B * C is passed.\n";
    }
    else {
       cout << "Test 1: (A + B) * C = C * (A + B) = A * C + B * C is failed.\n";
    }

    int n = 100;
    BigInt res1 = A * n;
    BigInt res2("0");
    for (int i = 0; i < n; i++) {
        res2 = res2 + A;
    }
    if (res1 == res2) {
        cout << "Test 2: n * A = A + A + ... + A (n times) is passed.\n";
    }
    else {
        cout << "Test 2: n * A = A + A + ... + A (n times) is failed.\n";
    }

    BigInt Add = A + B;
    BigInt expected1("a69fc4dd23d9a15795b9a65f3e6abc5b6c0c244f5df4290aff6aaefb1a34b4a34f"); 
    if (Add == expected1) {
        cout << "Test 3: Add (A + B) works correctly.\n";
    }
    else {
        cout << "Test 3: Addition (A + B) test failed.\n";
    }

    BigInt Sub = A - B;
    BigInt expected2("a69fc4cdc2faf25bcf8e7294d32016e754d3eb5ad0a2953952a8bcac1bc2a67e1b");
    if (Sub == expected2) {
        cout << "Test 4: Sub (A - B) works correctly.\n";
    }
    else {
        cout << "Test 4: Sub (A - B) test failed.\n";
    }

    BigInt Mult = A * B;
    BigInt expected3("50134b1617b8384112403aabeb651846c957c6bb57289fe1c1320927126f37dca4a65e907a69af02942d7a34558ecdce692efa2d2a712d7bc14afdc88c6e2");
    if (Mult == expected3) {
        cout << "Test 5: Multiplication (A * B) works correctly.\n";
    }
    else {
        cout << "Test 5: Multiplication (A * B) test failed.\n";
    }


    BigInt Div = B / C;
    BigInt expected4("0");  
    if (Div == expected4) {
        cout << "Test 6: Division (B / C) works correctly.\n";
    }
    else {
        cout << "Test 6: Division (B / C) test failed.\n";
    }

    BigInt result = C % A;
    BigInt expected5("92bdd7f6b07d4c9d661ecf91344aca5ee8a24b17d3089ce11a4fe8b34b3341ea74");
    if (result == expected5) {
        cout << "Test 7: Mod (C % A) works correctly.\n";
    }
    else {
        cout << "Test 7: Mod (C % A) test failed.\n";
    }

    return 0;
}
