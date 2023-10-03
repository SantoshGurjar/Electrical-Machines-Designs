// Stator Design of 3-phase Induction motor
#include <stdio.h>
#include <math.h>
int main()
{
    const double pi = 3.14;
    printf("Given data : 3 ph Slip - ring motor, star connected, best power factor desired");
    printf("\nEnter KW rating of Induction machine: ");
    double KW;
    scanf("%lf", &KW); // KW rating
    printf("\nEnter VOLTAGE rating of machine: ");
    double V;
    scanf("%lf", &V); // voltage rating
    printf("\nEntER FREQUENCY of machine: ");
    double f;
    scanf("%lf", &f); 
    printf("\nEnter POLES of machine: ");
    double P;
    scanf("%lf", &P); 
    printf("\nEnter Power factor of machine: ");
    double pf;
    scanf("%lf", &pf); 
    printf("\nEnter avrage gap density of machine: ");
    double Bav;
    scanf("%lf", &Bav);
    printf("\nSlot loading <= 500 A");
    double Kw = 0.96; // winding factor
    printf("\nwinding factor = % lf", Kw);
    double Ac = 25000; // Electric loading (ac/m)
    printf("\nElectric loading = % lf", Ac);
    double eff = 0.9; // efficiency
    printf("\nefficiency = % lf", eff);
    double Q = (KW / eff) / pf; // input KVA
    printf("\ninput KVA = % lf", Q);
    double C0 = 11 * Bav * Ac * Kw * 0.001; // Output coefficient
    printf("\nOutput coefficient = % lf", C0);
    double ns = (2 * f) / P; // synchronous speed in rps
    printf("\nsynchronous speed in rps = % lf", ns);
    double x = Q / (C0 * ns);
    printf("\nFor best power T = sqrt(0.18L)");
    double y = (0.18 * P * P) / (pi * pi);
    double L = sqrt(x / y);
    printf("\nLength = % lf", L);
    double D = sqrt(y * L);
    printf("\nDiameter = % lf", D);
    double Et = V / (sqrt(3));
    printf("\nEmf per turn = % lf", Et);
    double Fm = (Bav * pi * D * L) / P;
    printf("\nMax flux per pole = % lf", Fm);
    double Ts = round(Et / (4.44 * f * Fm * Kw));
    printf("\nNumber of turns in stator = % lf", Ts);
    printf("\nStator slot pitch should lie between 15-25 mm ");
    double SS1 = round((pi * D) / (0.015));
    double SS2 = round((pi * D) / (0.025));
    printf("\nstator slots Ss should lie between values of SS1 to SS2");
    printf("\nSS1 = % lf \n SS2 = % lf", SS1, SS2);
    printf("\nWhen qs = 2");
    double Ss2 = 3 * P * 2;
    printf("\nSs2 = % lf", Ss2);
    printf("\nWhen qs = 3");
    double Ss3 = 3 * P * 3;
    printf("\nSs3 = % lf", Ss3);
    printf("\nWhen qs = 4");
    double Ss4 = 3 * P * 4;
    printf("\nSs4 = % lf", Ss4);
    printf("\nWhen qs = 5");
    double Ss5 = 3 * P * 5;
    printf("\nSs5 = % lf", Ss5);

    printf("\nValue of Ss for q=3 and q=4 lie between specified limits");
    printf("\ncheck : ");
    double Iph = (Q * 1000) / (sqrt(3) * V);
    printf("\nFor star connection Iph = IL = % lf", Iph);
    printf("\nWhen Ss = % lf", Ss3);
    double Zss3 = round((6 * Ts) / Ss3);
    printf("\nZss3 = % lf", Zss3);
    double SL3 = Zss3 * Iph;
    printf("\nWhen Ss = % lf", Ss4);
    double Zss4 = round((6 * Ts) / Ss4);
    printf("\nZss4 = % lf", Zss4);
    double SL4 = Zss4 * Iph;
    printf("\nThe slot loading for q=4 that is Ss=Ss3 exceeds 500 and is rejected");
    double Sc = Zss4 * Ss4;
    printf("\nSc = % lf", Sc);
    double Tsm = round((Zss4 * Ss4) / 6);
    printf("\nTsm = % lf", Tsm);
    return 0;
}