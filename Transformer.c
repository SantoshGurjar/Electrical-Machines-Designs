// Overall Design of transformer
#include <stdio.h>
#include <conio.h>
#include <math.h>
float Hw, Ww, ratio, W_hv, W_lv, H_lv, H_hv;
float Vhv, Vlv, Tlv, Thv, Alv, Ahv, Ilv, Ihv;
float pi = 3.14, res = 0.000000021;
float mu = (0.0000004 * 3.1416);

//------------------Main function-------------------
int main()
{
//------------variable declarations--------------
    float Q, Vp, Vs, Ip, Is, K, Kw, F, B, i;
    float Aw, Agi, Ai, Ac, D, d, Ap, As, E, a, b;
    float Li, Gi, Gc, gi, Pi, p_iron, P_tot;
    float Rp, Pc, Pc_lv, Pc_hv, R_lv, R_hv, Xp;
    float pu_res, pu_react, pu_imp;
    float Ay, Hy, Dy, Hf, Wf, T;
    float in_major_wdg, in_major_lv, in_major_hv, clearance;
    float Awextra, Woccupy, Wextra, Hextra_lv, Hextra_hv, Hextra;
    float Lmt_lv, Lmt_hv, Lmt, Lc;
    float lv_mean, hv_mean, lv_in, lv_out, hv_in, hv_out;
    float eff, regln;
    float Ht, Lt, Wt, St, xt, Trise;
    float Ltube, Atube, Dtube, spacing, Nfl;
    char app, type, stl;
    int ph, Tp, Ts, f, Tm, x, y;
    int Ntube, N_length, N_width, Ne;
    char steel[15];
    void helical(float, float, float), cylindrical(float, float, float);
    
//---------------specifications-------------------


    f = 50;
    ph = 1;
    printf("PROGRAM FOR %d PHASE TRANSFORMER DESIGN\n\n", ph);
    printf("enter the rating of transformer in kVA:");
    scanf("%f", &Q);
    printf("\nenter the primary voltage in volts:");
    scanf("%f", &Vp);
    printf("\nenter the secondary voltage in volts:");
    scanf("%f", &Vs);
    if (Vp > Vs)
    {
        Vhv = Vp;
        Vlv = Vs;
    }
    else
    {
        Vhv = Vs;
        Vlv = Vp;
    }
    fflush(stdin);
    printf("\nenter p for power type,d for distribution type:");
    scanf("%c", &app);
    fflush(stdin);
    printf("\nenter c for core type,s for shell type:");
    scanf("%c", &type);
    printf("\nenter the max allowed mean temperature rise in degree celsius:");
    scanf("%d", &Tm);
    fflush(stdin);
    printf("\nenter c for crgo steel,h for hot rolled steel:");
    scanf("%c", &stl);
    fflush(stdin);
    printf("\nenter the grade and other specifications of steel used for laminations:");
    fgets(steel,15,stdin);
    
//------------------------------------------------------
    if (type == 'c')
        K = 0.8;
    else
        K = 1.1;
    E = K * sqrt(Q);
    printf("\n\nemf per turn E= %f", E);
    F = E / (4.44 * f);
    printf("\n\nflux in core F= %f", F);
    
//-------------------CHOOSING FLUX DENSITY------------------
    printf("\n\n-----------choosing flux density---------");
    printf("\n       HOT ROLLED SILICON STEEL");
    printf("\n\tdistribution trf       -1.1  to 1.35");
    printf("\n\tpower trf              -1.25 to 1.45");
    printf("\n           COLD ROLLED GRAIN ORIENTED STEEL");
    printf("\n\tupto 132kV             -1.55");
    printf("\n\tfor 275kV          -1.6");
    printf("\n\tfor 400kV          -1.7");
    printf("\n\nenter the value of flux density assumed:");
    scanf("%f", &B);
    
//-------------------CHOOSING CURRENT DENSITY----------------
    printf("\n\n-----------choosing current density---------------");
    printf("\nfor distribution and power trfs upto 50kVA take i=1.1 to 2.3A/mm^2");
    printf("\nfor large distribution trfs take i=2.2 to 3.2 A/mm^2");
    printf("\n\nenter the value of current density assumed:");
    scanf("%f", &i);
    
//------------------core dimensions-------------------------
    Ai = F / B;
    printf("\na TWO STEPPED CRUCIFORM core is used");
    d = sqrt(Ai / 0.56);
    a = 0.85 * d;
    b = 0.53 * d;
    printf("\nDIMENSIONS OF LAMINATIONS:\ta=%f,\tb=%f", a, b);
    Agi = (2 * a * b) - (b * b);
    Ai = 0.9 * Agi;
    B = F / Ai;
    
//--------------------window dimensions---------------------
    Kw = 9 / (30 + (Vhv / 1000));
    Aw = (Q * 1000) / (2.22 * f * B * i * Kw * Ai);
    printf("\nWINDOW DIMENSIONS:");
    printf("\t   window area,Aw=%f", Aw);
    printf("\nratio of Hw to Ww should lie btw 2-4");
    ratio = 3.2;
    printf("\nsay ratio=%f(initially)", ratio);
    Ww = sqrt(Aw / ratio);
    Hw = Aw / Ww;
    D = d + Ww;
    printf("\n\t   height, Hw=%f", Hw);
    printf("\t   width, Ww=%f", Ww);
    printf("\n\t   distance btw adjacent limbs , D=%f", D);
    
//-------------------yoke design------------------------
    if (stl == 'c')
        Ay = Agi;
    else
        Ay = 1.2 * Agi;
    Dy = a;
    Hy = Ay / Dy;
    printf("\nYOKE DIMENSIONS:");
    printf("\tarea=%f", Ay);
    printf("\n\theight=%f", Hy);
    printf("\tdepth=%f", Dy);
    
//---------------------frame design----------------------
    Hf = Hw + (2 * Hy);
    Wf = D + a;
    printf("\nFRAME DIMENSIONS:");
    printf("\theight=%f", Hf);
    printf("\twidth=%f", Wf);


    
//--------------------WINDING DESIGN-----------------------
    
//-----no of turns--------
    T = Vp / E;
    Tp = Vp / E;
    if (T > (Tp + 0.5))
        Tp = Tp + 1;
    T = Vs / E;
    Ts = Vs / E;
    if (T > (Ts + 0.5))
        Ts = Ts + 1;


    
//-------currents----------
    Ip = Q * 1000 / Vp;
    Is = Q * 1000 / Vs;


    
//-------areas of cross-section--------
    Ap = Ip / i;
    As = Is / i;


    printf("\n\nThe various winding specifications are");
    printf("\n\nTp=%d\tIp=%f\tAp=%f", Tp, Ip, Ap);
    printf("\n\nTs=%d\tIs=%f\tAs=%f", Ts, Is, As);
    if (Vp == Vhv)
    {
        Thv = Tp;
        Ihv = Ip;
        Ahv = Ap;
        Tlv = Ts;
        Ilv = Is;
        Alv = As;
    }
    else
    {
        Tlv = Tp;
        Ilv = Ip;
        Alv = Ap;
        Thv = Ts;
        Ihv = Is;
        Ahv = As;
    }
    printf("\nspecify the type of winding to use:");
    printf("\t1=cylindrical\t2=helical");
    printf("\nfor primary winding,choose 1 or 2:");
    scanf("%d", &x);
    if (x == 1)
        cylindrical(Ap, Tp, Vp);
    else
        helical(Ap, Tp, Vs);
    printf("\nfor secondary winding,choose 1 or 2:");
    scanf("%d", &x);
    if (x == 1)
        cylindrical(As, Ts, Vs);
    else
        helical(As, Ts, Vs);


    
//-------adjusting winding and window dimensions for optimal design
    in_major_wdg = 0.012;
    in_major_lv = 0.005;
    in_major_hv = 0.02;
    clearance = 0.01;
    Woccupy = 2 * (W_hv + in_major_wdg + W_lv + in_major_lv) + clearance;
    Wextra = Ww - Woccupy;
    if (Wextra > .005)
    {
        ratio = 4;
        Ww = Hw / 4;
        Wextra = Ww - Woccupy;
        in_major_lv = in_major_lv + .001;
        in_major_wdg = in_major_wdg + 0.003;
        clearance = clearance + 0.006;
        Woccupy = 2 * (W_hv + in_major_wdg + W_lv + in_major_lv) + clearance;
        Wextra = Ww - Woccupy;
    }
    in_major_lv = 0.005;
    Aw = Ww * Hw;
    Ac = Aw * Kw;
    
// removing the extra height common to hv and lv
    Hextra_lv = Hw - (H_lv + 2 * in_major_lv);
    Hextra_hv = Hw - (H_hv + 2 * in_major_hv);
    if (Hextra_lv <= Hextra_hv)
        Hextra = Hextra_lv;
    else
        Hextra = Hextra_hv;
    Hw = Hw - Hextra;
    Ww = Ww - Wextra;
    ratio = (Hw / Ww);
    
// maintaining the value of Hw/Ww
    if (ratio < 2)
        Hw = Hw + 0.005;
    if (ratio > 4)
        Ww = Ww + 0.005;
    Awextra = Hextra * Wextra;
    Aw = Aw - Awextra;
    
// adjusting the extra ht remaining as insulation
    if (Hextra_lv >= Hextra_hv)
    {
        Hextra_lv = Hextra_lv - Hextra;
        in_major_lv = in_major_lv + Hextra_lv / 2;
    }
    else
    {
        Hextra_hv = Hextra_hv - Hextra;
        in_major_hv = in_major_hv + Hextra_hv / 2;
    }
    
// total window width finally used
    Woccupy = 2 * (W_hv + in_major_wdg + W_lv + in_major_lv) + clearance;
    D = d + Ww;
    
//------------------------------------------------------
    printf("\n\n----------WINDOW DIMENSIONS----------------");
    printf("\nHw=%f", Hw);
    printf("\tWw=%f", Ww);
    
//---------------------frame redesign----------------------
    Hf = Hw + (2 * Hy);
    Wf = d + Ww + a;
    printf("\n\n----------FRAME DIMENSIONS--------");
    printf("\n\theight=%f", Hf);
    printf("\n\twidth=%f", Wf);


    
//--------------RESISTANCE------------------
    
// lv winding
    lv_in = d + 2 * in_major_lv;
    lv_out = lv_in + 2 * W_lv;
    lv_mean = (lv_in + lv_out) / 2;
    Lmt_lv = pi * lv_mean;
    R_lv = res * Tlv * Lmt_lv / Alv;


    
// hv winding
    hv_in = d + 2 * (in_major_lv + W_lv + in_major_wdg);
    hv_out = hv_in + 2 * W_hv;
    hv_mean = (hv_in + hv_out) / 2;
    Lmt_hv = pi * hv_mean;
    R_hv = res * Thv * Lmt_hv / Ahv;
    
// losses
    Pc_lv = Ilv * Ilv * R_lv;
    Pc_hv = Ihv * Ihv * R_hv;
    Pc = 1.1 * (Pc_lv + Pc_hv); 
// including 10% stray losses
    Rp = Pc / (Ip * Ip);
    pu_res = Ip * Rp / Vp;
    printf("\n\nR_hv=%f\tR_lv=%f\n\tpu resistance=%f", R_hv, R_lv, pu_res);


    
//----------------------LEAKAGE REACTANCE-----------------
    Lmt = (lv_in + hv_out) * pi / 2;
    Lc = Hw;
    Xp = 2 * pi * f * mu * Tp * Tp * Lmt * (in_major_wdg + (W_hv + W_lv) / 3) / Lc;
    pu_react = Xp * Ip / Vp;
    printf("\n\tpu reactance=%f", pu_react);
    pu_imp = sqrt(pu_res * pu_res + pu_react * pu_react);
    printf("\npu impedance=%f", pu_imp);


    
//-----------------LOSSES---------------
    Li = 2 * (Hw + D + a);
    p_iron = 1.16; 
// specific iron loss
    gi = 7650;     
// specific weight of iron
    Gi = Li * gi * Ai;
    Pi = 1.2 * p_iron * Gi; 
// making 20%allowance for joints
    P_tot = Pi + Pc;
    printf("\ntotal losses=%f", P_tot);


    
//-----------------EFFICIENCY---------------
    eff = Q * 100 / (Q + P_tot / 1000); 
// at full load and unity power factor
    printf("\nthe efficiency at full load,unity pf=%f", eff);


    
//----------------VOLTAGE REGULATION---------------
    regln = ((pu_res * 0.8) + (pu_react * 0.6)) * 100;
    printf("\nthe voltage regulation at full load and 0.8 pf=%f%", regln);


    
//----------------TANK DESIGN----------------------


    Ht = Hf + .050 + .250 + .300; 
// allowing .05 for base,.25 for oil,.3 for leads etc.
    Lt = D + hv_out + 0.160;      
// allowing clearance of .08 on each side
    Wt = hv_out + 0.200;          
// allowing .2 for accomodation of taps


    
// loss dissipating surface
    St = 2 * (Lt + Wt) * Ht;
    
// temperature rise
    Trise = P_tot / (12.5 * St);
    
// if temp rise exceeds allowable limit,add tubes
    if (Trise > Tm)
    {
        xt = (P_tot / (Tm * St) - 12.5) / 8.8;
        Atube = xt * St;
        Dtube = 0.050;
        spacing = 0.075;
        Ltube = Hf + 0.290; 
// length slightly less than oil level
        Ntube = Atube / (pi * Dtube * Ltube);
        Ntube = Ntube + 1;
        N_length = (Lt - 0.150) / spacing;
        if (Ntube <= (2 * N_length))
        {
            N_length = Ntube / 2;
            N_width = 0;
        }
        else
        {
            Ne = Ntube - 2 * N_length;
            Nfl = Ne;
            N_width = Ne / 2;
            if (Nfl / 2 > Ne / 2)
                N_width++;
        }
        printf("\ntubes=%d,t_lth=%d,t_wth=%d,Trise=%f", Ntube, N_length, N_width, Trise);
    }
    printf("\nHt=%f,Lt=%f,Wt=%f", Ht, Lt, Wt);


    getch();
}



//------------HELICAL WINDING DESIGN--------------
void helical(float A, float T, float V)
{
    
//------------declarations------------
    int N, Nh, Nw, t, y, no_layer, tLayer, tLayer2;
    float l, w, wCond, lCond, arB, lB, wB, in_minor, x;
    float in_major_core, fl, fll;


    printf("\n\n--------helical winding design---------");
    printf("\nenter no. of strips in the conductor:");
    scanf("%d", &N);
    printf("\nno of strips along the height:");
    scanf("%d", &Nh);
    Nw = N / Nh; 
// no of strips along width
    arB = A / N; 
// area of bare strip
    printf("\ngive std dimensions of strip for area=%f", arB);
    printf("\nl=");
    scanf("%f", &lB);
    printf("\nb=");
    scanf("%f", &wB);
    in_minor = .0005; 
// minor insulation
    
// dimensions including minor insulation
    l = lB + in_minor;
    w = wB + in_minor;
    
// total width and length occupied by complete conductor
    wCond = Nw * w;
    lCond = Nh * l;
    
// finding no of turns on each leg
    t = (T / 2);
    fl = T;
    x = (fl / 2);
    if (x > t)
        t = t + 2;
    else
        t = t + 1;
    
// major insulation btw core and wdg
    if (V == Vhv)
        in_major_core = 0.02;
    else
        in_major_core = 0.005;
    
// tLayer= no of turns along the height
    tLayer = (Hw - 2 * in_major_core) / lCond;
    tLayer2 = tLayer; 
// to accomodate unequal no of turns


    
// finding total no of layers
    y = t / tLayer;
    fl = t;
    fll = tLayer;
    x = (fl / fll);
    if (x == y)
        no_layer = y;
    else
    {
        no_layer = y + 1;
        tLayer = t / (y + 1);
        if (tLayer * (y + 1) != t)
            tLayer2 = t - (tLayer * (y + 1));
        else
            tLayer2 = tLayer;
    }


    
// width occupied by the wdg
    x = no_layer * wCond;
    if (V == Vhv)
    {
        H_hv = tLayer2 * lCond;
        W_hv = x;
        printf("\n\n\t HV WINDING");
    }
    else
    {
        H_lv = tLayer2 * lCond;
        W_lv = x;
        printf("\n\n\t LV WINDING");
    }


    
// outputting the arrangement
    printf("\n\nthe helical wdg is arrangred in %d layer(s) having ", no_layer);
    for (y = 1; y < no_layer; y++)
        printf("%d,", tLayer);
    printf("%d", (tLayer2 - 1));
    printf(" conductors");
}



//--------------------CYLINDRICAL WINDING DESIGN---------------------
void cylindrical(float A, float T, float V)
{
    
//--------------declarations----------------
    float x, dB, d, in_minor, in_major_core, fl, fll;
    int t, y, no_layer, tLayer, tLayer2;


    printf("\n\n----------cylindrical winding design-------------");
    
// finding no of turns on each leg
    t = (T / 2);
    fl = T;
    x = (fl / 2);
    if (x > t)
        t = t + 1;
    dB = sqrt(4 * A / pi); 
// diameter of bare conductor
    printf("\n paper insulation is used for minor insulation");
    in_minor = 0.00035;
    d = dB + in_minor; 
// diameter including insulation


    
// major insulation btw core and wdg
    if (V == Vhv)
        in_major_core = 0.02;
    else
        in_major_core = 0.005;


    
// tLayer= no of turns along the height
    tLayer = (Hw - 2 * in_major_core) / d;
    tLayer2 = tLayer; 
// to accomodate unequal no of turns


    
// finding total no of layers
    y = t / tLayer;
    fl = t;
    fll = tLayer;
    x = (fl / fll);
    if (x == y)
        no_layer = y;
    else
    {
        no_layer = y + 1;
        tLayer = t / (y + 1);
        if (tLayer * (y + 1) != t)
            tLayer2 = tLayer + t - (tLayer * (y + 1));
        else
            tLayer2 = tLayer;
    }
    
// width occupied by the wdg
    x = no_layer * d;
    if (V == Vhv)
    {
        H_hv = tLayer2 * d;
        W_hv = x;
        printf("\n\n\t HV WINDING");
    }
    else
    {
        H_lv = tLayer2 * d;
        W_lv = x;
        printf("\n\n\t LV WINDING");
    }
    
// outputting the arrangement
    printf("\n\nthe cylindrical wdg is arrangred in %d layer(s) having ", no_layer);
    for (y = 1; y < no_layer; y++)
        printf("%d,", tLayer);
    printf("%d", tLayer2);
    printf(" conductors");
}