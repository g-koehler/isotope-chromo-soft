/* lsqs.f -- translated by f2c (version 20090411).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

/*<       SUBROUTINE LSQS (RDATA,N,SDATA,NN,IDEG,NPTS,IDER,DX)               >*/
/* Subroutine */ int lsqs_(real *rdata, integer *n, real *sdata, integer *nn, 
	integer *ideg, integer *npts, integer *ider, real *dx)
{
    /* Initialized data */

    static integer nsst = 1;
    static integer n1st = 145;
    static integer n2st = 361;
    static integer ncs = 72;
    static struct {
	real e_1[504];
	} equiv_10 = { 17.f, 12.f, -3.f, 35.f, 7.f, 6.f, 3.f, -2.f, 21.f, 
		59.f, 54.f, 39.f, 14.f, -21.f, 231.f, 89.f, 84.f, 69.f, 44.f, 
		9.f, -36.f, 429.f, 25.f, 24.f, 21.f, 16.f, 9.f, 0.f, -11.f, 
		143.f, 167.f, 162.f, 147.f, 122.f, 87.f, 42.f, -13.f, -78.f, 
		1105.f, 43.f, 42.f, 39.f, 34.f, 27.f, 18.f, 7.f, -6.f, -21.f, 
		323.f, 269.f, 264.f, 249.f, 224.f, 189.f, 144.f, 89.f, 24.f, 
		-51.f, -136.f, 2261.f, 329.f, 324.f, 309.f, 284.f, 249.f, 
		204.f, 149.f, 84.f, 9.f, -76.f, -171.f, 3059.f, 0.f, 0.f, 0.f,
		 1.f, 131.f, 75.f, -30.f, 5.f, 231.f, 179.f, 135.f, 30.f, 
		-55.f, 15.f, 429.f, 143.f, 120.f, 60.f, -10.f, -45.f, 18.f, 
		429.f, 677.f, 600.f, 390.f, 110.f, -135.f, -198.f, 110.f, 
		2431.f, 11063.f, 10125.f, 7500.f, 3755.f, -165.f, -2937.f, 
		-2860.f, 2145.f, 46189.f, 883.f, 825.f, 660.f, 415.f, 135.f, 
		-117.f, -260.f, -195.f, 195.f, 4199.f, 1393.f, 1320.f, 1110.f,
		 790.f, 405.f, 18.f, -290.f, -420.f, -255.f, 340.f, 7429.f, 
		44003.f, 42120.f, 36660.f, 28190.f, 17655.f, 6378.f, -3940.f, 
		-11220.f, -13005.f, -6460.f, 11628.f, 260015.f, 0.f, -1.f, 
		-2.f, 10.f, 0.f, -1.f, -2.f, -3.f, 28.f, 0.f, -1.f, -2.f, 
		-3.f, -4.f, 60.f, 0.f, -1.f, -2.f, -3.f, -4.f, -5.f, 110.f, 
		0.f, -1.f, -2.f, -3.f, -4.f, -5.f, -6.f, 182.f, 0.f, -1.f, 
		-2.f, -3.f, -4.f, -5.f, -6.f, -7.f, 280.f, 0.f, -1.f, -2.f, 
		-3.f, -4.f, -5.f, -6.f, -7.f, -8.f, 408.f, 0.f, -1.f, -2.f, 
		-3.f, -4.f, -5.f, -6.f, -7.f, -8.f, -9.f, 570.f, 0.f, -1.f, 
		-2.f, -3.f, -4.f, -5.f, -6.f, -7.f, -8.f, -9.f, -10.f, 770.f, 
		0.f, -8.f, 1.f, 12.f, 0.f, -58.f, -67.f, 22.f, 252.f, 0.f, 
		-126.f, -193.f, -142.f, 86.f, 1188.f, 0.f, -296.f, -503.f, 
		-532.f, -294.f, 300.f, 5148.f, 0.f, -832.f, -1489.f, -1796.f, 
		-1578.f, -660.f, 1133.f, 24024.f, 0.f, -7506.f, -13843.f, 
		-17842.f, -18334.f, -14150.f, -4121.f, 12922.f, 334152.f, 0.f,
		 -358.f, -673.f, -902.f, -1002.f, -930.f, -643.f, -98.f, 
		748.f, 23256.f, 0.f, -2816.f, -5363.f, -7372.f, -8574.f, 
		-8700.f, -7481.f, -4648.f, 68.f, 6936.f, 255816.f, 0.f, 
		-29592.f, -56881.f, -79564.f, -95338.f, -101900.f, -96947.f, 
		-78176.f, -43284.f, 10032.f, 84075.f, 3634092.f, 0.f, 0.f, 
		0.f, 1.f, 0.f, -45.f, 9.f, -1.f, 60.f, 0.f, -2879.f, -2269.f, 
		1381.f, -254.f, 8580.f, 0.f, -3084.f, -3774.f, -1249.f, 
		2166.f, -573.f, 17160.f, 0.f, -31380.f, -45741.f, -33511.f, 
		-12.f, 27093.f, -9647.f, 291720.f, 0.f, -175125.f, -279975.f, 
		-266401.f, -130506.f, 65229.f, 169819.f, -78351.f, 2519400.f, 
		0.f, -23945.f, -40483.f, -43973.f, -32306.f, -8671.f, 16679.f,
		 24661.f, -14404.f, 503880.f, 0.f, -332684.f, -583549.f, 
		-686099.f, -604484.f, -348823.f, 9473.f, 322378.f, 349928.f, 
		-255102.f, 9806280.f, 0.f, -15977360.f, -28754150.f, 
		-35613830.f, -34807910.f, -26040030.f, -10949940.f, 6402438.f,
		 19052990.f, 16649360.f, -15033070.f, 63740820.f, -2.f, -1.f, 
		2.f, 7.f, -4.f, -3.f, 0.f, 5.f, 42.f, -20.f, -17.f, -8.f, 7.f,
		 28.f, 462.f, -10.f, -9.f, -6.f, -1.f, 6.f, 15.f, 429.f, 
		-14.f, -13.f, -10.f, -5.f, 2.f, 11.f, 22.f, 1001.f, -56.f, 
		-53.f, -44.f, -29.f, -8.f, 19.f, 52.f, 91.f, 6188.f, -24.f, 
		-23.f, -20.f, -15.f, -8.f, 1.f, 12.f, 25.f, 40.f, 3876.f, 
		-30.f, -29.f, -26.f, -21.f, -14.f, -5.f, 6.f, 19.f, 34.f, 
		51.f, 6783.f, -110.f, -107.f, -98.f, -83.f, -62.f, -35.f, 
		-2.f, 37.f, 82.f, 133.f, 190.f, 33649.f, -90.f, 48.f, -3.f, 
		36.f, -70.f, -19.f, 67.f, -13.f, 132.f, -370.f, -211.f, 151.f,
		 371.f, -126.f, 1716.f, -190.f, -136.f, 1.f, 146.f, 174.f, 
		-90.f, 1716.f, -3780.f, -3016.f, -971.f, 1614.f, 3504.f, 
		2970.f, -2211.f, 58344.f, -45780.f, -38859.f, -19751.f, 
		6579.f, 31856.f, 44495.f, 29601.f, -31031.f, 1108536.f, 
		-2820.f, -2489.f, -1557.f, -207.f, 1256.f, 2405.f, 2691.f, 
		1443.f, -2132.f, 100776.f, -38940.f, -35288.f, -24867.f, 
		-9282.f, 8792.f, 25610.f, 36357.f, 35148.f, 15028.f, -32028.f,
		 1961256.f, -14322.f, -13224.f, -10061.f, -5226.f, 626.f, 
		6578.f, 11451.f, 13804.f, 11934.f, 3876.f, -12597.f, 980628.f 
		};


    /* System generated locals */
    integer i__1, i__2;

    /* Local variables */
#define c__ ((real *)&equiv_10)
    static integer i__, j, m;
#define d12 ((real *)&equiv_10 + 144)
#define d14 ((real *)&equiv_10 + 216)
#define d23 ((real *)&equiv_10 + 360)
#define d16 ((real *)&equiv_10 + 288)
#define d44 ((real *)&equiv_10 + 274)
#define c55 ((real *)&equiv_10 + 134)
#define d25 ((real *)&equiv_10 + 432)
#define d55 ((real *)&equiv_10 + 483)
#define d66 ((real *)&equiv_10 + 345)
    static integer kj;
#define cs3 ((real *)&equiv_10)
#define cs5 ((real *)&equiv_10 + 72)
    static integer mid, jmp, jtr;
    static real sum;
    static integer midm, midp, jpls;
    static real cnorm;
    static integer ismth, inorm;


/*  LSQS 2.0        JUNE 1975                                            LSQS   3 */
/*  COPYRIGHT (C) 1972, 1975 DARRELL D. WOODARD AND J. P. CHANDLER       LSQS   4 */
/*                                                                       LSQS   5 */
/*  LSQS USES LEAST SQUARES SMOOTHING TO ESTIMATE A FUNCTION OR ITS      LSQS   6 */
/*  FIRST OR SECOND DERIVATIVES.                                         LSQS   7 */
/*  THE ABSCISSAE OF THE DATA MUST BE UNIFORMLY SPACED.                  LSQS   8 */
/*                                                                       LSQS   9 */
/*  METHOD...  LEAST SQUARES SMOOTHING USING CONVOLUTING FUNCTIONS.      LSQS  10 */
/*  THE DEGREE OF THE LEAST SQUARES POLYNOMIAL IS TWO THROUGH FIVE.      LSQS  11 */
/*  THE NUMBER OF POINTS PER POLYNOMIAL VARIES FROM FIVE TO TWENTY-ONE.  LSQS  12 */
/*                                                                       LSQS  13 */
/*  REFERENCE...  A. SAVITSKY AND M.J.E. GOLAY, ANAL. CHEM. 36 (1964)    LSQS  14 */
/*       PAGE 1627  (BUT SEE CORRECTIONS IN REFERENCE CITED BELOW)       LSQS  15 */
/*                                                                       LSQS  16 */
/*     PARAMETERS...                                                     LSQS  17 */
/*     RDATA          ARRAY CONTAINING THE RAW DATA                      LSQS  18 */
/*     N              NUMBER OF RAW DATA POINTS                          LSQS  19 */
/*     SDATA          ARRAY WHERE SMOOTHED DATA/DERIVATIVES WILL BE      LSQS  20 */
/*                    RETURNED                                           LSQS  21 */
/*     NN             NUMBER OF SMOOTHED POINTS RETURNED (N-NPTS+1)      LSQS  22 */
/*     IDEG           DEGREE OF INTERPOLATING POLYNOMIAL (2-5).          LSQS  23 */
/*     NPTS           NUMBER OF BASE POINTS DESIRED (5-21 IN INCREMENTS  LSQS  24 */
/*                    OF 2).  FOR POLY OF DEGREE 6, NPTS MUST BE AT      LSQS  25 */
/*                    LEAST 7.                                           LSQS  26 */
/*     IDER           =0  SMOOTH                                         LSQS  27 */
/*                    =1  FIRST DERIVATIVE                               LSQS  28 */
/*                    =2  SECOND DERIVATIVE                              LSQS  29 */
/*     DX             INTERVAL SPACING USED TO COLLECT RAW DATA.         LSQS  30 */
/*                                                                       LSQS  31 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * LSQS  32 */
/*                                                                       LSQS  33 */
/*  REVISION TO LSQS....                                                 LSQS  34 */
/*                                                                       LSQS  35 */
/*  GARY A. GILLEAN, COMPUTER SCIENCE DEPT., OKLAHOMA STATE UNIVERSITY   LSQS  36 */
/*  DECEMBER 1972                                                        LSQS  37 */
/*  REFERENCE...  J. STEINIER, Y. TERMONIA, AND J. DELTOUR,              LSQS  38 */
/*                ANALYTICAL CHEMISTRY 44 (1972) 1909                    LSQS  39 */
/*                                                                       LSQS  40 */
/*  ERRORS IN THE COEFFICIENTS GIVEN BY SAVITSKY AND GOLAY HAVE BEEN     LSQS  41 */
/*  CORRECTED ACCORDING TO THE ARTICLE BY STEINIER ET AL.                LSQS  42 */
/*  ALL VALUES NOW SEEM TO CHECK EXACTLY.                                LSQS  43 */
/*                                                                       LSQS  44 */
/*  THE DATA ORDINATES, RDATA( ), ARE ASSUMED TO CORRESPOND TO DATA      LSQS  45 */
/*  POINTS HAVING ABSCISSA VALUES WHICH ARE UNIFORMLY SPACED AND         LSQS  46 */
/*  STRICTLY INCREASING.                                                 LSQS  47 */
/*  THE SMOOTHED VALUES AND DERIVATIVES CANNOT BE EVALUATED AT THE       LSQS  48 */
/*  FIRST OR LAST (NPTS-1)/2 POINTS...   SDATA(1) RETURNS THE SMOOTHED   LSQS  49 */
/*  VALUE OR DERIVATIVE CORRESPONDING TO RDATA((NPTS+1)/2).              LSQS  50 */
/*                                                                       LSQS  51 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * LSQS  52 */
/*                                                                       LSQS  53 */
/*<       DIMENSION RDATA(N),SDATA(NN)                                       >*/
/*<       DIMENSION CS3(72),CS5(62),C55(10)                                  >*/
/*<       DIMENSION D12(72),D14(58),D44(14),D16(57),D66(15)                 >*/
/*<       DIMENSION D23(72),D25(51),D55(21)                                 >*/
/*<       DIMENSION C(504)                                                   >*/
/*                            POINTERS INTO CONVOLUTE ARRAY C....        LSQS  59 */
/*<       EQUIVALENCE (CS3(1),C(1)),(CS5(1),C(73)),(C55(1),C(135))          >*/
/*<       EQUIVALENCE (D12(1),C(145)),(D14(1),C(217)),(D44(1),C(275))        >*/
/*<       EQUIVALENCE (D16(1),C(289)),(D66(1),C(346))                       >*/
/*<       EQUIVALENCE (D23(1),C(361)),(D25(1),C(433)),(D55(1),C(484))       >*/
/*<       DATA NSST/1/,N1ST/145/,N2ST/361/,NCS/72/                          >*/
    /* Parameter adjustments */
    --rdata;
    --sdata;

    /* Function Body */
/*                                                                       LSQS  65 */
/*  THE FOLLOWING DATA STATEMENTS ARE NOT IN A.N.S.I. STANDARD FORTRAN.  LSQS  66 */
/*                                                                       LSQS  67 */
/*                            CONVOLUTES FROM SAVITZKY AND GOLAY....     LSQS  68 */
/*             SMOOTHING - TABLE 1  QUADRATIC - CUBIC POLYNOMIAL         LSQS  69 */
/*                  5 - 21 BASE POINTS                                   LSQS  70 */
/*<        >*/
/*                                                                       LSQS  77 */
/*             SMOOTHING - TABLE 2  QUARTIC - QUINTIC POLYNOMIAL         LSQS  78 */
/*                  5 - 21 BASE POINTS                                   LSQS  79 */
/*<        >*/
/*<        >*/
/*                                                                       LSQS  88 */
/*             FIRST DERIVATIVE - TABLE 3  QUADRATIC POLYNOMIAL          LSQS  89 */
/*                  5 - 21 BASE POINTS                                   LSQS  90 */
/*<        >*/
/*                                                                       LSQS  97 */
/*             FIRST DERIVATIVE - TABLE 4  CUBIC - QUARTIC POLYNOMIAL    LSQS  98 */
/*                  5 - 21 BASE POINTS                                   LSQS  99 */
/*<        >*/
/*<        >*/
/*                                                                       LSQS 108 */
/*             FIRST DERIVATIVE TABLE 5  QUINTIC - SEXTIC POLYNOMIAL     LSQS 109 */
/*                  7 - 21 BASE POINTS                                   LSQS 110 */
/*<        >*/
/*                                                                       LSQS 117 */
/* ROUNDED VALUES FOR CONVOLUTES FOR 21 BASE POINTS....                  LSQS 118 */
/*<        >*/
/*                                                                       LSQS 122 */
/* EXACT VALUES FOR CONVOLUTES FOR 21 BASE POINTS....                    LSQS 123 */
/*     DATA D66/ 349928.,-255102.,9806280.,0.,-15977364.,-28754154.,     LSQS 124 */
/*    1 -35613829.,-34807914.,-26040033.,-10949942.,6402438.,19052988.,  LSQS 125 */
/*    2 16649358.,-15033066.,637408200./                                 LSQS 126 */
/*                                                                       LSQS 127 */
/*             SECOND DERIVATIVE TABLE 6  QUADRATIC - CUBIC POLYNOMIAL   LSQS 128 */
/*                  5 - 21 BASE POINTS                                   LSQS 129 */
/*<        >*/
/*                                                                       LSQS 136 */
/*             SECOND DERIVATIVE TABLE 7   QUARTIC - QUINTIC POLYNOMIAL  LSQS 137 */
/*                  5 - 21 BASE POINTS                                   LSQS 138 */
/*<        >*/
/*<        >*/
/*                                                                       LSQS 148 */
/*                            INITIALIZE.                                LSQS 149 */
/*<       ISMTH=NPTS/2                                                      >*/
    ismth = *npts / 2;
/*<       M=N-NPTS+1                                                         >*/
    m = *n - *npts + 1;
/*                            SET JTR TO DESIRED CONVOLUTES.             LSQS 152 */
/*<       IF(IDER-1)10,30,60                                               >*/
    if ((i__1 = *ider - 1) < 0) {
	goto L10;
    } else if (i__1 == 0) {
	goto L30;
    } else {
	goto L60;
    }
/*                            SMOOTH                                     LSQS 154 */
/*<    10 CNORM=1.                                                         >*/
L10:
    cnorm = 1.f;
/*<       JMP=1                                                             >*/
    jmp = 1;
/*<       JTR=NSST                                                         >*/
    jtr = nsst;
/*<       IF(IDEG-3)80,80,20                                              >*/
    if (*ideg - 3 <= 0) {
	goto L80;
    } else {
	goto L20;
    }
/*<    20 JTR=JTR+NCS                                                     >*/
L20:
    jtr += ncs;
/*<       GO TO 80                                                           >*/
    goto L80;
/*                            FIRST DERIVATIVES                          LSQS 161 */
/*<    30 CNORM=DX                                                         >*/
L30:
    cnorm = *dx;
/*<       JMP=2                                                           >*/
    jmp = 2;
/*<       JTR=N1ST                                                         >*/
    jtr = n1st;
/*                            IF((IDEG-1)/2-1)80,50,40                   LSQS 165 */
/*<       GO TO (80,80,50,50,40,40),IDEG                                    >*/
    switch (*ideg) {
	case 1:  goto L80;
	case 2:  goto L80;
	case 3:  goto L50;
	case 4:  goto L50;
	case 5:  goto L40;
	case 6:  goto L40;
    }
/*<    40 JTR=JTR+NCS                                                      >*/
L40:
    jtr += ncs;
/*<    50 JTR=JTR+NCS                                                       >*/
L50:
    jtr += ncs;
/*<       GO TO 80                                                         >*/
    goto L80;
/*                            SECOND DERIVATIVES                         LSQS 170 */
/*<    60 CNORM=DX*DX                                                       >*/
L60:
    cnorm = *dx * *dx;
/*<       JMP=1                                                             >*/
    jmp = 1;
/*<       JTR=N2ST                                                          >*/
    jtr = n2st;
/*<       IF(IDEG-3)80,80,70                                                 >*/
    if (*ideg - 3 <= 0) {
	goto L80;
    } else {
	goto L70;
    }
/*<    70 JTR=JTR+NCS                                                       >*/
L70:
    jtr += ncs;
/*                            MODIFY JTR BASED ON NPTS REQUESTED.        LSQS 176 */
/*<    80 IF(NPTS-5)110,110,90                                              >*/
L80:
    if (*npts - 5 <= 0) {
	goto L110;
    } else {
	goto L90;
    }
/*<    90 KJ=ISMTH+1                                                       >*/
L90:
    kj = ismth + 1;
/*<       DO 100 I=4,KJ                                                      >*/
    i__1 = kj;
    for (i__ = 4; i__ <= i__1; ++i__) {
/*<   100 JTR=JTR+I                                                         >*/
/* L100: */
	jtr += i__;
    }
/*                            FIND NORMALIZER, MODIFY BY INTERVAL SIZE.  LSQS 181 */
/*<   110 INORM=JTR+ISMTH+1                                                 >*/
L110:
    inorm = jtr + ismth + 1;
/*<       CNORM=C(INORM)*CNORM                                              >*/
    cnorm = c__[inorm - 1] * cnorm;
/*<       GO TO (120,150),JMP                                                >*/
    switch (jmp) {
	case 1:  goto L120;
	case 2:  goto L150;
    }
/*                                                                       LSQS 185 */
/*                            SMOOTHING LOOP-SMOOTH OR EVEN DERIVATIVES  LSQS 186 */
/*                            CONVOLUTES SYMMETRIC                       LSQS 187 */
/*<   120 DO 140 I=1,M                                                      >*/
L120:
    i__1 = m;
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<       MID=I+ISMTH                                                       >*/
	mid = i__ + ismth;
/*                            EVALUATE CENTER POINT.                     LSQS 190 */
/*<       SUM=C(JTR)*RDATA(MID)                                           >*/
	sum = c__[jtr - 1] * rdata[mid];
/*                            WORK OUT FROM CENTER.                      LSQS 192 */
/*<       DO 130 J=1,ISMTH                                                >*/
	i__2 = ismth;
	for (j = 1; j <= i__2; ++j) {
/*<       JPLS=JTR+J                                                        >*/
	    jpls = jtr + j;
/*<       MIDP=MID+J                                                       >*/
	    midp = mid + j;
/*<       MIDM=MID-J                                                        >*/
	    midm = mid - j;
/*<   130 SUM=SUM+C(JPLS)*(RDATA(MIDM)+RDATA(MIDP))                         >*/
/* L130: */
	    sum += c__[jpls - 1] * (rdata[midm] + rdata[midp]);
	}
/*                                                                       LSQS 198 */
/*                            NORMALIZE.                                 LSQS 199 */
/*<   140 SDATA(I)=SUM/CNORM                                                 >*/
/* L140: */
	sdata[i__] = sum / cnorm;
    }
/*<       RETURN                                                           >*/
    return 0;
/*                            LOOP FOR ODD DERIVATIVES....               LSQS 202 */
/*                            CONVOLUTES NOT SYMMETRIC                   LSQS 203 */
/*<   150 DO 170 I=1,M                                                     >*/
L150:
    i__1 = m;
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<       MID=I+ISMTH                                                        >*/
	mid = i__ + ismth;
/*<       SUM=C(JTR)*RDATA(MID)                                            >*/
	sum = c__[jtr - 1] * rdata[mid];
/*<       DO 160 J=1,ISMTH                                                   >*/
	i__2 = ismth;
	for (j = 1; j <= i__2; ++j) {
/*<       JPLS=JTR+J                                                        >*/
	    jpls = jtr + j;
/*<       MIDP=MID+J                                                       >*/
	    midp = mid + j;
/*<       MIDM=MID-J                                                        >*/
	    midm = mid - j;
/*<   160 SUM=SUM+C(JPLS)*(RDATA(MIDM)-RDATA(MIDP))                         >*/
/* L160: */
	    sum += c__[jpls - 1] * (rdata[midm] - rdata[midp]);
	}
/*<   170 SDATA(I)=SUM/CNORM                                                >*/
/* L170: */
	sdata[i__] = sum / cnorm;
    }
/*<       RETURN                                                            >*/
    return 0;
/*                                                                       LSQS 214 */
/* END LSQS.                                                             LSQS 215 */
/*<       END                                                               >*/
} /* lsqs_ */

#undef cs5
#undef cs3
#undef d66
#undef d55
#undef d25
#undef c55
#undef d44
#undef d16
#undef d23
#undef d14
#undef d12
#undef c__


