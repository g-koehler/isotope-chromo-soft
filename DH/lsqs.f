      SUBROUTINE LSQS (RDATA,N,SDATA,NN,IDEG,NPTS,IDER,DX)              
C                                                                       
C  LSQS 2.0        JUNE 1975                                            LSQS   3
C  COPYRIGHT (C) 1972, 1975 DARRELL D. WOODARD AND J. P. CHANDLER       LSQS   4
C                                                                       LSQS   5
C  LSQS USES LEAST SQUARES SMOOTHING TO ESTIMATE A FUNCTION OR ITS      LSQS   6
C  FIRST OR SECOND DERIVATIVES.                                         LSQS   7
C  THE ABSCISSAE OF THE DATA MUST BE UNIFORMLY SPACED.                  LSQS   8
C                                                                       LSQS   9
C  METHOD...  LEAST SQUARES SMOOTHING USING CONVOLUTING FUNCTIONS.      LSQS  10
C  THE DEGREE OF THE LEAST SQUARES POLYNOMIAL IS TWO THROUGH FIVE.      LSQS  11
C  THE NUMBER OF POINTS PER POLYNOMIAL VARIES FROM FIVE TO TWENTY-ONE.  LSQS  12
C                                                                       LSQS  13
C  REFERENCE...  A. SAVITSKY AND M.J.E. GOLAY, ANAL. CHEM. 36 (1964)    LSQS  14
C       PAGE 1627  (BUT SEE CORRECTIONS IN REFERENCE CITED BELOW)       LSQS  15
C                                                                       LSQS  16
C     PARAMETERS...                                                     LSQS  17
C     RDATA          ARRAY CONTAINING THE RAW DATA                      LSQS  18
C     N              NUMBER OF RAW DATA POINTS                          LSQS  19
C     SDATA          ARRAY WHERE SMOOTHED DATA/DERIVATIVES WILL BE      LSQS  20
C                    RETURNED                                           LSQS  21
C     NN             NUMBER OF SMOOTHED POINTS RETURNED (N-NPTS+1)      LSQS  22
C     IDEG           DEGREE OF INTERPOLATING POLYNOMIAL (2-5).          LSQS  23
C     NPTS           NUMBER OF BASE POINTS DESIRED (5-21 IN INCREMENTS  LSQS  24
C                    OF 2).  FOR POLY OF DEGREE 6, NPTS MUST BE AT      LSQS  25
C                    LEAST 7.                                           LSQS  26
C     IDER           =0  SMOOTH                                         LSQS  27
C                    =1  FIRST DERIVATIVE                               LSQS  28
C                    =2  SECOND DERIVATIVE                              LSQS  29
C     DX             INTERVAL SPACING USED TO COLLECT RAW DATA.         LSQS  30
C                                                                       LSQS  31
C * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * LSQS  32
C                                                                       LSQS  33
C  REVISION TO LSQS....                                                 LSQS  34
C                                                                       LSQS  35
C  GARY A. GILLEAN, COMPUTER SCIENCE DEPT., OKLAHOMA STATE UNIVERSITY   LSQS  36
C  DECEMBER 1972                                                        LSQS  37
C  REFERENCE...  J. STEINIER, Y. TERMONIA, AND J. DELTOUR,              LSQS  38
C                ANALYTICAL CHEMISTRY 44 (1972) 1909                    LSQS  39
C                                                                       LSQS  40
C  ERRORS IN THE COEFFICIENTS GIVEN BY SAVITSKY AND GOLAY HAVE BEEN     LSQS  41
C  CORRECTED ACCORDING TO THE ARTICLE BY STEINIER ET AL.                LSQS  42
C  ALL VALUES NOW SEEM TO CHECK EXACTLY.                                LSQS  43
C                                                                       LSQS  44
C  THE DATA ORDINATES, RDATA( ), ARE ASSUMED TO CORRESPOND TO DATA      LSQS  45
C  POINTS HAVING ABSCISSA VALUES WHICH ARE UNIFORMLY SPACED AND         LSQS  46
C  STRICTLY INCREASING.                                                 LSQS  47
C  THE SMOOTHED VALUES AND DERIVATIVES CANNOT BE EVALUATED AT THE       LSQS  48
C  FIRST OR LAST (NPTS-1)/2 POINTS...   SDATA(1) RETURNS THE SMOOTHED   LSQS  49
C  VALUE OR DERIVATIVE CORRESPONDING TO RDATA((NPTS+1)/2).              LSQS  50
C                                                                       LSQS  51
C * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * LSQS  52
C                                                                       LSQS  53
      DIMENSION RDATA(N),SDATA(NN)                                      
      DIMENSION CS3(72),CS5(62),C55(10)                                 
      DIMENSION D12(72),D14(58),D44(14),D16(57),D66(15)                
      DIMENSION D23(72),D25(51),D55(21)                                
      DIMENSION C(504)                                                  
C                            POINTERS INTO CONVOLUTE ARRAY C....        LSQS  59
      EQUIVALENCE (CS3(1),C(1)),(CS5(1),C(73)),(C55(1),C(135))         
      EQUIVALENCE (D12(1),C(145)),(D14(1),C(217)),(D44(1),C(275))       
      EQUIVALENCE (D16(1),C(289)),(D66(1),C(346))                      
      EQUIVALENCE (D23(1),C(361)),(D25(1),C(433)),(D55(1),C(484))      
      DATA NSST/1/,N1ST/145/,N2ST/361/,NCS/72/                         
C                                                                       LSQS  65
C  THE FOLLOWING DATA STATEMENTS ARE NOT IN A.N.S.I. STANDARD FORTRAN.  LSQS  66
C                                                                       LSQS  67
C                            CONVOLUTES FROM SAVITZKY AND GOLAY....     LSQS  68
C             SMOOTHING - TABLE 1  QUADRATIC - CUBIC POLYNOMIAL         LSQS  69
C                  5 - 21 BASE POINTS                                   LSQS  70
      DATA CS3/17.,12.,-3.,35.,7.,6.,3.,-2.,21.,59.,54.,39.,14.,-21.,  
     *         231.,89.,84.,69.,44.,9.,-36.,429.,25.,24.,21.,16.,9.,0., 
     *         -11.,143.,167.,162.,147.,122.,87.,42.,-13.,-78.,1105.,   
     *         43.,42.,39.,34.,27.,18.,7.,-6.,-21.,323.,269.,264.,249., 
     *         224.,189.,144.,89.,24.,-51.,-136.,2261.,329.,324.,309., 
     *         284.,249.,204.,149.,84.,9.,-76.,-171.,3059./             
C                                                                       LSQS  77
C             SMOOTHING - TABLE 2  QUARTIC - QUINTIC POLYNOMIAL         LSQS  78
C                  5 - 21 BASE POINTS                                   LSQS  79
      DATA CS5/0.,0.,0.,1.,131.,75.,-30.,5.,231.,179.,135.,30.,-55.,15.,
     *         429.,143.,120.,60.,-10.,-45.,18.,429.,677.,600.,390.,   
     *         110.,-135.,-198.,110.,2431.,11063.,10125.,7500.,3755.,   
     *         -165.,-2937.,-2860.,2145.,46189.,883.,825.,660.,415.,    
     *         135.,-117.,-260.,-195.,195.,4199.,1393.,1320.,1110.,790.,
     *         405.,18.,-290.,-420.,-255.,340.,7429.,44003.,42120./     
      DATA C55/36660.,28190.,17655.,6378.,-3940.,-11220.,-13005.,-6460.,
     *         11628.,260015./                                          
C                                                                       LSQS  88
C             FIRST DERIVATIVE - TABLE 3  QUADRATIC POLYNOMIAL          LSQS  89
C                  5 - 21 BASE POINTS                                   LSQS  90
      DATA D12/0.,-1.,-2.,10.,0.,-1.,-2.,-3.,28.,0.,-1.,-2.,-3.,-4.,60.,
     *         0.,-1.,-2.,-3.,-4.,-5.,110.,0.,-1.,-2.,-3.,-4.,-5.,-6.,  
     *         182.,0.,-1.,-2.,-3.,-4.,-5.,-6.,-7.,280.,0.,-1.,-2.,-3., 
     *         -4.,-5.,-6.,-7.,-8.,408.,0.,-1.,-2.,-3.,-4.,-5.,-6.,-7., 
     *         -8.,-9.,570.,0.,-1.,-2.,-3.,-4.,-5.,-6.,-7.,-8.,-9.,     
     *         -10.,770./                                              
C                                                                       LSQS  97
C             FIRST DERIVATIVE - TABLE 4  CUBIC - QUARTIC POLYNOMIAL    LSQS  98
C                  5 - 21 BASE POINTS                                   LSQS  99
      DATA D14/0.,-8.,1.,12.,0.,-58.,-67.,22.,252.,0.,-126.,-193.,-142.,
     *         86.,1188.,0.,-296.,-503.,-532.,-294.,300.,5148.,0.,-832.,
     *         -1489.,-1796.,-1578.,-660.,1133.,24024.,0.,-7506.,       
     *         -13843.,-17842.,-18334.,-14150.,-4121.,12922.,334152.,   
     *         0.,-358.,-673.,-902.,-1002.,-930.,-643.,-98.,748.,23256.,
     *         0.,-2816.,-5363.,-7372.,-8574.,-8700.,-7481.,-4648.,68./
      DATA D44/6936.,255816.,0.,-29592.,-56881.,-79564.,-95338.,-101900.
     *,        -96947.,-78176.,-43284.,10032.,84075.,3634092./          
C                                                                       LSQS 108
C             FIRST DERIVATIVE TABLE 5  QUINTIC - SEXTIC POLYNOMIAL     LSQS 109
C                  7 - 21 BASE POINTS                                   LSQS 110
      DATA D16/0.,0.,0.,1.,0.,-45.,9.,-1.,60.,0.,-2879.,-2269.,1381.,   
     *-254.,8580.,0.,-3084.,-3774.,-1249.,2166.,-573.,17160.,0.,-31380.,
     * -45741.,-33511.,-12.,27093.,-9647.,291720.,0.,-175125.,-279975.,
     * -266401.,-130506.,65229.,169819.,-78351.,2519400.,0.,-23945.,    
     * -40483.,-43973.,-32306.,-8671.,16679.,24661.,-14404.,503880.,0., 
     * -332684.,-583549.,-686099.,-604484.,-348823.,9473.,322378. /     
C                                                                       LSQS 117
C ROUNDED VALUES FOR CONVOLUTES FOR 21 BASE POINTS....                  LSQS 118
      DATA D66/349928.,-255102.,9806280.,0.,-1597736.E1,-2875415.E1,   
     * -3561383.E1,-3480791.E1,-2604003.E1,-1094994.E1,6402438.,        
     * 1905299.E1,1664936.E1,-1503307E1,6374082.E1/                    
C                                                                       LSQS 122
C EXACT VALUES FOR CONVOLUTES FOR 21 BASE POINTS....                    LSQS 123
C     DATA D66/ 349928.,-255102.,9806280.,0.,-15977364.,-28754154.,     LSQS 124
C    1 -35613829.,-34807914.,-26040033.,-10949942.,6402438.,19052988.,  LSQS 125
C    2 16649358.,-15033066.,637408200./                                 LSQS 126
C                                                                       LSQS 127
C             SECOND DERIVATIVE TABLE 6  QUADRATIC - CUBIC POLYNOMIAL   LSQS 128
C                  5 - 21 BASE POINTS                                   LSQS 129
      DATA D23/-2.,-1.,2.,7.,-4.,-3.,0.,5.,42.,-20.,-17.,-8.,7.,28.,    
     *         462.,-10.,-9.,-6.,-1.,6.,15.,429.,-14.,-13.,-10.,-5.,2., 
     *         11.,22.,1001.,-56.,-53.,-44.,-29.,-8.,19.,52.,91.,6188., 
     *         -24.,-23.,-20.,-15.,-8.,1.,12.,25.,40.,3876.,-30.,-29.,  
     *         -26.,-21.,-14.,-5.,6.,19.,34.,51.,6783.,-110.,-107.,-98.,
     *         -83.,-62.,-35.,-2.,37.,82.,133.,190.,33649./             
C                                                                       LSQS 136
C             SECOND DERIVATIVE TABLE 7   QUARTIC - QUINTIC POLYNOMIAL  LSQS 137
C                  5 - 21 BASE POINTS                                   LSQS 138
      DATAD25/-90.,48.,-3.,36.,-70.,-19.,67.,-13.,132.,-370.,-211.,151.,
     * 371.,-126.,1716.,-190.,-136.,1.,146.,174.,-90.,1716.,-3780.,     
     * -3016.,-971.,1614.,3504.,2970.,-2211.,58344.,-45780.,-38859.,    
     * -19751.,6579.,31856.,44495.,29601.,-31031.,1108536.,-2820.,      
     * -2489.,-1557.,-207.,1256.,2405.,2691.,1443.,-2132.,100776.,      
     * -38940.,-35288./                                                
      DATA D55/ -24867.,-9282.,8792.,25610.,36357.,35148.,15028.,       
     * -32028.,1961256.,-14322.,-13224.,-10061.,-5226.,626.,6578.,      
     * 11451.,13804.,11934.,3876.,-12597.,980628./                     
C                                                                       LSQS 148
C                            INITIALIZE.                                LSQS 149
      ISMTH=NPTS/2                                                     
      M=N-NPTS+1                                                        
C                            SET JTR TO DESIRED CONVOLUTES.             LSQS 152
      IF(IDER-1)10,30,60                                              
C                            SMOOTH                                     LSQS 154
   10 CNORM=1.                                                        
      JMP=1                                                            
      JTR=NSST                                                        
      IF(IDEG-3)80,80,20                                             
   20 JTR=JTR+NCS                                                    
      GO TO 80                                                          
C                            FIRST DERIVATIVES                          LSQS 161
   30 CNORM=DX                                                        
      JMP=2                                                          
      JTR=N1ST                                                        
C                            IF((IDEG-1)/2-1)80,50,40                   LSQS 165
      GO TO (80,80,50,50,40,40),IDEG                                   
   40 JTR=JTR+NCS                                                     
   50 JTR=JTR+NCS                                                      
      GO TO 80                                                        
C                            SECOND DERIVATIVES                         LSQS 170
   60 CNORM=DX*DX                                                      
      JMP=1                                                            
      JTR=N2ST                                                         
      IF(IDEG-3)80,80,70                                                
   70 JTR=JTR+NCS                                                      
C                            MODIFY JTR BASED ON NPTS REQUESTED.        LSQS 176
   80 IF(NPTS-5)110,110,90                                             
   90 KJ=ISMTH+1                                                      
      DO 100 I=4,KJ                                                     
  100 JTR=JTR+I                                                        
C                            FIND NORMALIZER, MODIFY BY INTERVAL SIZE.  LSQS 181
  110 INORM=JTR+ISMTH+1                                                
      CNORM=C(INORM)*CNORM                                             
      GO TO (120,150),JMP                                               
C                                                                       LSQS 185
C                            SMOOTHING LOOP-SMOOTH OR EVEN DERIVATIVES  LSQS 186
C                            CONVOLUTES SYMMETRIC                       LSQS 187
  120 DO 140 I=1,M                                                     
      MID=I+ISMTH                                                      
C                            EVALUATE CENTER POINT.                     LSQS 190
      SUM=C(JTR)*RDATA(MID)                                          
C                            WORK OUT FROM CENTER.                      LSQS 192
      DO 130 J=1,ISMTH                                               
      JPLS=JTR+J                                                       
      MIDP=MID+J                                                      
      MIDM=MID-J                                                       
  130 SUM=SUM+C(JPLS)*(RDATA(MIDM)+RDATA(MIDP))                        
C                                                                       LSQS 198
C                            NORMALIZE.                                 LSQS 199
  140 SDATA(I)=SUM/CNORM                                                
      RETURN                                                          
C                            LOOP FOR ODD DERIVATIVES....               LSQS 202
C                            CONVOLUTES NOT SYMMETRIC                   LSQS 203
  150 DO 170 I=1,M                                                    
      MID=I+ISMTH                                                       
      SUM=C(JTR)*RDATA(MID)                                           
      DO 160 J=1,ISMTH                                                  
      JPLS=JTR+J                                                       
      MIDP=MID+J                                                      
      MIDM=MID-J                                                       
  160 SUM=SUM+C(JPLS)*(RDATA(MIDM)-RDATA(MIDP))                        
  170 SDATA(I)=SUM/CNORM                                               
      RETURN                                                           
C                                                                       LSQS 214
C END LSQS.                                                             LSQS 215
      END                                                              
