#include "BigInt.h"
#include <ctime>

int main() {

    BigInt num1("a9694988354c96530b1a58f8ad59569af0d402ab53d275ddb5cb393f47c6b098977f181ab889d3c5ceb96b9f3c0702c947856481d654c691d0f736fa2ef7aa0fbec62224e467f741e53edf8c8fe82c13fb90ac66eee37a975f16dd9faafd213c538711bbea34fbfd8b4330e17409d5c35313743d5dea5a82d34d99a10ac9223b");
    BigInt num2("cbe75e23d145c3dc78d76739b63d337cc33268e08ce4ea7319c38b7d057b1747d59010759f3b015858dc5a9d05ddbbd3ef41a368ba1ca6d8a6d967f2fed6b7033e7f56d46beae7c259cce870e0879f49849c956b6b6810be90d0c50c54daaef41b2b1c6e3c7b2ed35da549a7c95fd551841ea90e4196e8272b42ea3dba7cdcef");

    clock_t start_time, end_time;

    start_time = clock();
    BigInt sum = num1 + num2;
    end_time = clock();
    double duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1e9;
    cout << "num1 + num2 = " << sum.toHexString() << endl;
    cout << "Time for Addition: " << duration << " nanoseconds" << endl;
    
    cout << "\t" << endl;

    start_time = clock();
    BigInt difference = num1 - num2;
    end_time = clock();
    duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1e9;
    cout << "num1 - num2 = " << difference.toHexString() << endl;
    cout << "Time for Subtraction: " << duration << " nanoseconds" << endl;

    cout << "\t" << endl;

    start_time = clock();
    BigInt product = num1 * num2;
    end_time = clock();
    duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1e9;
    cout << "num1 * num2 = " << product.toHexString() << endl;
    cout << "Time for Multiplication: " << duration << " nanoseconds" << endl;
    
    cout << "\t" << endl;

    start_time = clock();
    BigInt quotient = num1 / num2;
    end_time = clock();
    duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1e9;
    cout << "num1 / num2 = " << quotient.toHexString() << endl;
    cout << "Time for Division: " << duration << " nanoseconds" << endl;

    cout << "\t" << endl;

    start_time = clock();
    BigInt remainder = num1 % num2;
    end_time = clock();
    duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1e9;
    cout << "num1 mod num2 = " << remainder.toHexString() << endl;
    cout << "Time for Mod: " << duration << " nanoseconds" << endl;

    cout << "\t" << endl;

    start_time = clock();
    BigInt squared = num1.Square();
    end_time = clock();
    duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1e9;
    cout << "num1 ^ 2 = " << squared.toHexString() << endl;
    cout << "Time for Squared: " << duration << " nanoseconds" << endl;

    cout << "\t" << endl;

    start_time = clock();
    BigInt power = num1.Pow(9);
    end_time = clock();
    duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1e9;
    cout << "num1 ^ 9 = " << power.toHexString() << endl;
    cout << "Time for Power: " << duration << " nanoseconds" << endl;

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
