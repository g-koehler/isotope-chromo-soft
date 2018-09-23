#!/usr/bin/perl
 

################################################################
#	LGR data processor that finds peaks in water 
#       integrates the peaks and spits out the data -
#	input is a simplified LGR data file recuded with the shell
#	script "peak_reduce"
#	Arguments are the input file name and threshold value
#	outputs to stdout
#	G. Koehler 2011
#################################################################
 open (FILE, $ARGV[0]);
printf ("***************************************\nfile = %s\n", $ARGV[0]);
$threshold = $ARGV[1];
printf ("Integration threshold = %s\n***************************************\n", $threshold);
$refD = -135;$refO = -16.9;   # get reference isotopic values 


$D_sum =0;			#dD sum for average		|
$HO_sum =0;			#d18O sum for average		| average of entire reference pulse
$O18_sum=0;
$peakno=0;
$foundpeak = 0;
$datapoints = 0;

printf("peak size    H/D        18O/16O       DeltaD  Delta18O   DeltaD (SMOW)\n");
printf("---------------------------------------------------------------------\n");
 while (<FILE>) {				#open file
 	chomp;
 	($nh2_16O, $nH2_18O, $nD2O) = split(",");
	#print $ref;
	#find first peak - anthything over 1000 ppm H2O
	if ($nh2_16O > $threshold) {
		$foundpeak = 1; 		
		$HO_sum += $nh2_16O;
		#$Dex = 2.28e-10 * (($nh2_16O)^2);
		$Dex = 0.00001 * $nh2_16O;
		$D_sum = $D_sum + $nD2O + $Dex;
		$O18_sum += $nH2_18O;
		$datapoints ++;
		#printf ("%f %f\n", $nh2_16O, $Dex);
		
		
				
	}
	elsif ($foundpeak == 1) {  #Found first peak
			$peakno++;
			if ($peakno == 1) {  #its the reference
				$DHref = $D_sum / $HO_sum;
				$O1816ref = $O18_sum/$HO_sum;
			}
			$deltaD = ((($D_sum / $HO_sum)/$DHref)-1)*1000;
			$deltaO = ((($O18_sum / $HO_sum)/$O1816ref)-1)*1000;
			$deltaD_SMOW = $deltaD + $refD;
			printf(" %5d  %3d  %f  %f %10.1f  %10.2f %10.1f\n", $peakno, $datapoints, $D_sum / $HO_sum, 
				$O18_sum/$HO_sum, $deltaD, $deltaO, $deltaD_SMOW);
			#printf(" D-ex = %e\n", $Dex);
			$D_sum =0;			
			$HO_sum =0;			
			$O18_sum=0;
			
			$foundpeak = 0;
			$datapoints = 0;
			#print "fred"; 	
	}
	

}
printf("---------------------------------------------------------------------\n");




























































































































 close (FILE);
 exit;

	
		
	

