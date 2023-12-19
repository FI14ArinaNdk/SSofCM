#include "BigInt.h"
#include <chrono>

    using namespace std;
    using namespace std::chrono;

    int main() {

        BigInt num1("658ec5e5d8f126d692936c196bc1be68fdbc7483d7f1035c8e636c36ed5d4d0f0f69a0fa8158f4d0967e3ebd23aa4081f14540fb4f4724140e38ab2a40d33e807028b2f40b1e5362c392348d7cd81dde9ec6a79e1f4abb8b706ea0d63d30f0663a2ca1ff673d8889bc315853fca663a2c05f46c87657f0fea4ec2aafe8bbf3ac");
        BigInt num2("f5aa1bd307eedf96db133a218aa605a0edb6de4fa9d43d100cd75990b3c9b72347ff83796c2f886b4a58f312b8bdbdbcaf500790eee9add7165837032d2bd268e9a73cb50dca7a065abb515a18f8783c9f1bdaa5400a2b2f06cc42a2b38f41599d5bab219aaff407f6c283d479de944f8d039233709e21e30aa380b98026ac33");
        BigInt modulus("5bffd2ad88c901a224caba35ba09c26ae6be9c06dae976a0fc91b7e6f5076559813cb94d2b33e86c9bf1afabc4598e769fd3e7c27bc45bbeab5e78ce48fabe89ef514ff65c64da6e6858a91600de5b4091b219b88ff502fd166ea1ef805e37bc0695d17348823898c0a7bfe217d7980ca93b724b2aecec6c4f0165e9b30002e2");
       
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
        

        cout << "\t" << endl;
        cout << "\t" << endl;


        /*
       vector<int> lenght = { 130 };
       for (const auto lenght : lenght) {
           double GCDTime = 0.0;
           double LCMTime = 0.0;
           double ADDTime = 0.0;
           double SUBTime = 0.0;
           double MULTTime = 0.0;
           double SQTime = 0.0;
           double POWERTime = 0.0;

           for (int i = 0; i < 50; i++) {
                   BigInt random_num1 = BigInt::generateRandomHEXNumber(lenght);
               BigInt random_num2 = BigInt::generateRandomHEXNumber(lenght/2);
               BigInt random_modulus = BigInt::generateRandomHEXNumber(lenght);

               auto GCDStartTime = high_resolution_clock::now();
               BigInt resultGCD = random_num1.GCD(random_num2).toHexString();
               auto GCDEndTime = high_resolution_clock::now();
               GCDTime += duration_cast<milliseconds>(GCDEndTime - GCDStartTime).count();

               auto LCMStartTime = high_resolution_clock::now();
               BigInt resultLCM = random_num1.LCM(random_num2).toHexString();
               auto LCMEndTime = high_resolution_clock::now();
               LCMTime += duration_cast<milliseconds>(LCMEndTime - LCMStartTime).count();

               auto ADDStartTime = high_resolution_clock::now();
               BigInt resultADD = random_num1.addWithModulo(random_num2, random_modulus).toHexString();
               auto ADDEndTime = high_resolution_clock::now();
               ADDTime += duration_cast<milliseconds>(ADDEndTime - ADDStartTime).count();

               auto SUBStartTime = high_resolution_clock::now();
              BigInt resultSUB = random_num1.subWithModulo(random_num2, random_modulus).toHexString();
               auto SUBEndTime = high_resolution_clock::now();
              SUBTime += duration_cast<milliseconds>(SUBEndTime - SUBStartTime).count();

               auto MULTStartTime = high_resolution_clock::now();
               BigInt resultMULT = random_num1.multWithModulo(random_num2, random_modulus).toHexString();
               auto MULTEndTime = high_resolution_clock::now();
               MULTTime += duration_cast<milliseconds>(MULTEndTime - MULTStartTime).count();

               auto SQStartTime = high_resolution_clock::now();
               BigInt resultSQ = random_num1.toSquareWithModulo(random_modulus).toHexString();
               auto SQEndTime = high_resolution_clock::now();
               SQTime += duration_cast<milliseconds>(SQEndTime - SQStartTime).count();

               auto POWERStartTime = high_resolution_clock::now();
               BigInt resultPOWER = random_num1.powerModulo(random_num2, random_modulus).toHexString();
               auto POWEREndTime = high_resolution_clock::now();
               POWERTime += duration_cast<milliseconds>(POWEREndTime - POWERStartTime).count();

           }

           double AverGCDTime = GCDTime / 50.0;
           double AverLCMTime = LCMTime / 50.0;
           double AverADDTime = ADDTime / 50.0;
           double AverSUBTime = SUBTime / 50.0;
           double AverMULTTime = MULTTime / 50.0;
           double AvarSQTime = SQTime / 50.0;
           double AvarPOWERTime = POWERTime / 50.0;

           cout << "Average GCD Time: " << AverGCDTime << " milliseconds" << endl;
           cout << "Average LCM Time: " << AverLCMTime << " milliseconds" << endl;
           cout << "Average ADD Time: " << AverADDTime << " milliseconds" << endl;
           cout << "Average SUB Time: " << AverSUBTime << " milliseconds" << endl;
           cout << "Average MULT Time: " << AverMULTTime << "milliseconds" << endl;
           cout << "Average SQ Time: " << AvarSQTime << "milliseconds" << endl;
           cout << "Average POWER Time: " << AvarPOWERTime << "milliseconds" << endl;
           cout << "\t" << endl;
       }
       */
    
        return 0;
    }
