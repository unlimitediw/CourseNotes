# read file
use feature qw(say);
my $filename = 'apache.txt';
open INFILE,$filename;

# use to check line
my $line;

# Use a hash map to memory the times of success requests.
my %clients;

while ( $line = <INFILE>) {
    chomp($line);
    my ($host,$date,$url_with_method,$status,$size) = $line =~
          m/^(\S+) - - \[(\S+ [\-|\+]\d{4})\] "(\S+ \S+ [^"]+)" (\d{3}) (\d+|-)/;
    $date = substr($date,0,2);
    if(exists($clients{$date})){
        if($status == 200){
            $clients{$date} += 1;
        }
    } else{
        if($status == 200){
            $clients{$date} = 1;
        }
        else{
            $clients{$date} = 0;
        }
    }

    #print '*',$clients{$host},'-', $host, '*';
}

@dataset = values %clients;
# find max values and min values
$max = -1;
$min = ~0;
$sum = 0;
$medianIdx = ($#dataset)/2;
@dataset = sort {$a <=> $b} @dataset;
say $medianIdx
$median = ($dataset[$medianIdx] + $dataset[$medianIdx + 1])/2;
for($index = 0;$index <= $#dataset; $index ++){
    if($dataset[$index] < $min){
        $min = $dataset[$index];
    }
    if($dataset[$index] > $max){
        $max = $dataset[$index];
    }
    $sum += $dataset[$index];
}
$mean = $sum / ($#dataset + 1);


# get standard deviation
$varianceSum = 0;
for($index = 0;$index <= $#dataset; $index ++){
    $varianceSum += ($dataset[$index] - $mean)**2;
}
$std = ($varianceSum/($#dataset + 1))**0.5;
say "max: ",$max;
say "min: ",$min;
say "mean: ",$mean;
say "median: ", $median;
say "std: ", $std;
