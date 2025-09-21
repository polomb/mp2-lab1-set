#include <gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//#include "tset.h"
//int SieveOfEratosthenes(int n)
//{
//    TSet resheto(n + 1);
//    for (int i = 2; i <= n; i++)
//    {
//        resheto.InsElem(i);
//    }
//    for (int p = 2; p * p <= n; p++)
//    {
//        if (resheto.IsMember(p))
//        {
//            for (int i = p * p; i <= n; i += p)
//            {
//                resheto.DelElem(i);
//            }
//        }
//    }
//    cout << resheto;
//    return 1;
//}
//int main()
//{
//	SieveOfEratosthenes(100);
//    return 1;
//}