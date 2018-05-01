#Command: C:\Strawberry\perl\bin\perl.exe C:\Users\dblood.VALPO\Desktop\LedPostProcessingScript.pl "[output_filepath]"
#!/usr/bin/perl -i
use strict;
use warnings;
use Math::Round;
my $pin=2;
my $totalFilament=0;
my $currentFilament=0;
my $record=0;
my $file = $ARGV[0];
$^I = '.bak';
open (FILE, '<', $file) || die ("File not found");
while (<FILE>){
  # a regular expression for the G0/G1 commmand
  if(/^G[01](\h+X(-?\d*\.?\d+))?(\h+Y(-?\d*\.?\d+))?(\h+Z(-?\d*\.?\d+))?(\h+E(-?\d*\.?\d+))?(\h+F(\d*\.?\d+))?(\h*;\h*([\h\w_-]*)\h*)?/){
    # the match variables, just readable
    my $X=$2, my $Y=$4, my $Z=$6, my $E=$8, my $F=$10, my $verbose=$12;
    if($E){
      # tracking how much filament we're using
      $totalFilament+=$E;
    }
 }
}
close FILE;
$^I = '.bak';
while (<>){
   if(/^G[01](\h+X(-?\d*\.?\d+))?(\h+Y(-?\d*\.?\d+))?(\h+Z(-?\d*\.?\d+))?(\h+E(-?\d*\.?\d+))?(\h+F(\d*\.?\d+))?(\h*;\h*([\h\w_-]*)\h*)?/){
	# the match variables, just readable
	my $X=$2, my $Y=$4, my $Z=$6, my $E=$8, my $F=$10, my $verbose=$12;
	if($E){
	  # tracking how much filament we're using
	  $currentFilament+=$E;
	}if($Z){
	  #Change the pwm speed of the fan
	  print "\nM106 P2 S".round(($currentFilament/$totalFilament)*170 + 30)."\n";
	}
 }
 print;
}
