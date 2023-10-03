// Main dimension of DC machine

#include <stdio.h>
#include <math.h>
int main()
{
    // Main dimensions of dc machine
    double const pi = 3.14;
    printf("Enter KW rating of DC machine: ");
    double Pa ;
    scanf("%lf",&Pa);     // KW rating
    printf("\nEnter VOLTAGE rating of DC machine: ");
    double V;
    scanf("%lf", &V);  // voltage rating
    printf("\nEnter POLES of DC machine: ");
    double P;
    scanf("%lf", &P); // number of poles of the machine
    printf("\nEnter SPECIFIC MAGNETIC LOADING of DC machine: ");
    double Bav;
    scanf("%lf", &Bav); // specific magnetic loading (Wb/m^2)
    printf("\nEnter SPECIFIC ELECRICAL LOADING of DC machine: ");
    double ac;
    scanf("%lf", &ac); // specific electrical loading (A/m)
    printf("\nEnter speed of DC machine: ");
    double N;
    scanf("%lf", &N); // speed of machine
    printf("\nEnter RATIO OF CORE LENGTH TO POLE PITCH of DC machine: ");
    double Rap;
    scanf("%lf", &Rap); // ratio of core length to pole pitch                    
    double ns = N / 60;                      // speed in rps
    double Co = (pi * pi * Bav * ac) / 1000; // output coefficient
    double D2L = Pa / (Co * ns);             // volume= D*D*L
    double RLD = pi * Rap / P;               // Value of L/D
    double D = cbrt(D2L / RLD);              // Value of D
    double L = RLD * D;                      // Value of L
    printf("\nThe values of D and L are % lf and % lf", D, L);
    double va = pi * D * ns; // Peripheral velocity
    printf("\nPeripheral velocity is % lf", va);
    if (va <= 30)
        printf("\nPeripheral velocity is within permissible limit of 30 m / s");
    else
        printf("\nVa exceeds limit");
    double Ia = Pa * (1e3) / V; // armature current
    printf("\narmature current = % lf", Ia);
    double Iz = Ia / 2; // current per parallel path
    printf("\nCurrent per parallel path = % lf", Iz);
    if (Iz < 200)
        printf("\nSimplex winding can be used");
    else
    {
        printf("\nCurrent limit of 200 A / path was exceeded.Simplex winding cant be used");
        Iz = Ia / P; // new current per path
        if (Iz < 200)
            printf("\nRather LAP winding can be used");
    }
    double Ez = Bav * L * va; // average induced emf/conductor
    double X = V / Ez;
    X = X / 10;
    X = round(X);
    double Zc = X * 10; // armature conductors per path rounded to nearest 10
    double Z = Zc * P;  // Total no. of conductors
    printf("\nTotal no.of conductors = % lf", Z);
    printf("\nCondn 1: Slot pitch varies from 2.5 to 3.5 cm...");
    double Smin1 = round(pi * D / 0.035);
    double Smax1 = round(pi * D / 0.025);
    printf("\nCondn 2: ratio of no.of slots to pole varies from 9 to 16.");
    double Smin2 = P * 9;
    double Smax2 = P * 16;
    double Smin, Smax;
    if (Smin1 > Smin2)
        Smin = Smin1;
    else
        Smin = Smin2;
    if (Smax1 < Smax2)
        Smax = Smax1;
    else
        Smax = Smax2;
    printf("\nFinal Lower & Higher bounds of no.of slots: % lf - % lf", Smin, Smax);
    double A, B[100], C[100];
    printf("\nCondn 3: for lap winding no. of slots are a multiple of pole pair 3");
    Smin = ceil(Smin * 2 / P) * P / 2; // recalibrating initial value to multiple of P/2
    printf("\nCond 4: to reduce flux pulsations Slots / pole must be equal to integer + 0.5");
    printf("\nThese are the possible values of no.of slots");
    int j = 0;
    for (A = Smin; A < (Smax + 1); A = A + 3)
    {
        if (A / P == floor(A / P) + 0.5)
        {
            B[j] = A;
            printf("\n % lf", B[j]);
            j = j + 1;
        }
        for (int i = 0; i < j; i++)
        {
            B[i] = B[i] * Rap / P;
            C[i] = B[i] - floor(B[i]); // finding element with min fractional part
            B[i] = B[i] * P / Rap;
        }
}
printf("\nChoosing S which is nearly an integer");
int pos;
double min = C[0];
for (int i = 0; i < j; i++)
{
    if (C[i] < min)
        pos = i;
    min = C[i];
} // position of optimal value in array
double S = B[pos];
printf("\nNumber of slots = % lf", B[pos]);
double Zps = Z / S;
printf("\nNo.of conductors per slot = % lf", Zps);
Zps = round(Zps);
printf("\nAs Zs must be an even integer, the revised no.of conductors is = % lf", Zps);
double Zrev = S * Zps;
double Sload = Iz * Zps;
printf("\nSlot loading = % lf", Sload);
if (Sload < 1500)
    printf("\nSlot loading is within the permissible limit");
double NC = Zrev / 2; // no. of coils
printf("\nNo.of commutator segments: % lf", NC);
double PC = 0.7 * D * pi / NC * 1000; // pitch of coils (in mm)
printf("\nPitch of commutator segments: % lf", PC);
if (4 < PC && PC < 9)
    printf("\nPitch of coils is well within the permissible limits of(4, 9)");
}