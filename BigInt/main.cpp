#include "BigInt.h"
#include <chrono>

    using namespace std;
    using namespace std::chrono;

    int main() {

        BigInt num1("49e8fbc709682fd27b5374521000a9f7a84c1e31156eaf661db2cef3e738e9a05ed540487a805dd5098d19b5dd1eed610cff655279e2be39fb520c7713eb41258886210005a46e6de9311231b85da6d4f32c028847aa64bc04458861be442512db2056bae4a1d44d10d7013ddb5f8dcab1cc17f535d080974a219d4b0177fbf9");
        BigInt num2("3e3d9a7f43698b6057bf789e640c2b779a6990ca3b323b89fba7297f5e9c86e635ec6b5f859c1a6144066ed009e884d7db0c82d79c306fc3745240ff8a31240923c8db248f05a4003ec9ef8e579636c2ad9561f24d2328d0ffbe3b3c66bd003d8150fee34de21a037af10fa5cd66042294404c3fcd5eac9eee462611cf479df7");
        BigInt modulus("eb37815d31c58266b4b80eec480567a24cc323e765f48e2b763918f434e108fa0699ac65a3340ebcb23dac90a4b750a70ed92018522c11e84d9b1190a35cc0a3db844ed8823e212bb50992a45692e8abc27f1d7e84f7217afe640b624dc4291d5c28536eebbf264b0b257ecb6b5dc77635dba985cb41db91b6c4a69a9b0aef85");
       
        //LAB2
        
        cout << "gcd - "<< num1.GCD(num2).toHexString() << endl;
        cout << "\t" << endl;
        cout << "lcm - "<< num1.LCM(num2).toHexString() << endl;
        cout << "\t" << endl;
        cout << "add - "<<num1.addWithModulo(num2, modulus).toHexString() << endl;
        cout << "\t" << endl;
        cout << "sub - "<<num1.subWithModulo(num2, modulus).toHexString() << endl;
        cout << "\t" << endl;
        cout <<"mult - "<< num1.multWithModulo(num2, modulus).toHexString() << endl;
        cout << "\t" << endl;
        cout << "sq - " << num1.toSquareWithModulo(modulus).toHexString() << endl;
        cout << "\t" << endl;
        cout << "power - " << num1.powerModulo(num2, modulus).toHexString() << endl;


        //LAB1
        /*
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
        */
        
        cout << "\t" << endl;
        cout << "\t" << endl;

        cout << "Test time:" << endl;

        BigInt a("0a69fc4d57");
        BigInt b("07b06f577");
        BigInt c("01dffd61e");
        BigInt n("01dffd61a1");


        BigInt result1_1 = ((a + b).multWithModulo(c, n)).toHexString(); 
        BigInt result1_2 = (c.multWithModulo(a + b, n)).toHexString(); 
        BigInt result1_3 = (a.multWithModulo(c, n) + b.multWithModulo(c, n)).toHexString() ;

        cout << "Test 1: (a + b) * c = c * (a + b) = a * c + c * d (mod n) - "; 
        if (result1_1 == result1_2 && result1_2 == result1_3) { 
            cout << "Passed" << endl; 
        }
        else {
            cout << "Failed" << endl; 
        }


        //Test 2
        int t = 150;
        BigInt amult = a.multWithModulo(t, n);
        BigInt sum_a; 
        for (int i = 0; i < t; i++) {
            sum_a = sum_a.addWithModulo(a, n); 
        }
        BigInt sum = sum_a;
        cout << "Test 2: a*t (mod n) = a + a + ... + a (mod n) -  ";
        if (sum == amult) {
            cout << "Passed" << endl;
        }
        else {
            cout << "Failed" << endl;
            
        }

        //Test 3
        BigInt k("2");
        BigInt m = BigInt("3").Pow(k);
        BigInt phi_m = BigInt("2") * BigInt("3").Pow(k - BigInt("1"));

        BigInt phi_result = a.Pow(phi_m) % m;

        if (phi_result == BigInt("0")) {
            cout << "Test 3: a is divisible by 3" << endl;
        }
        else if (phi_result == BigInt("1")) {
            cout << "Test 3: Passed - a^phi(m) = 1 (mod m)" << endl;
        }
        else {
            cout << "Test 3: Failed" << endl;
        }


        //Test addWithModulo
        BigInt addResult = (a.addWithModulo(b, n)).toHexString();
        BigInt expected("185105aa9");
        if (addResult == expected) {
            cout << "Test addWithModulo - Passed \n ";
        }
        else {
            cout << "Test addWithModulo - Failed \n ";
        }


        //Test subWithModulo
        BigInt subResult = (a.subWithModulo(b, n)).toHexString();
        BigInt expected1("8f026fbb");
        if (subResult == expected1) {
            cout << "Test subWithModulo - Passed \n ";
        }
        else {
            cout << "Test subWithModulo - Failed \n ";
        }

        //Test multWithModulo
        BigInt multResult = (a.multWithModulo(b, n)).toHexString(); 
        BigInt expected2("79b2ac57");
        if (multResult == expected2) {
            cout << "Test multWithModulo - Passed \n ";
        }
        else {
            cout << "Test multWithModulo - Failed \n ";
        }

        //Test toSquareWithModulo
        BigInt squareResult = (a.toSquareWithModulo(n)).toHexString(); 
        BigInt expected3("d709145c");
        if (squareResult == expected3) {
            cout << "Test toSquareWithModulo - Passed \n ";
        }
        else {
            cout << "Test toSquareWithModulo - Failed \n ";
        }

        //Test GCD
        BigInt gcdResult = (a.GCD(b)).toHexString();
        BigInt expected4("1");
        if (gcdResult == expected4) {
            cout << "Test GCD - Passed \n ";
        }
        else {
            cout << "Test GCD - Failed \n ";
        }

        //Test LCM
        BigInt lcmResult = (a.LCM(b)).toHexString();
        BigInt expected5("50134b15857563671");
        if (lcmResult == expected5) {
            cout << "Test LCM - Passed \n ";
        }
        else {
            cout << "Test LCM - Failed \n ";
        }
        
    
        //LAB 1
        /*
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
        */

        return 0;
    }
