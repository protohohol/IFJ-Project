<?php
declare(strict_types=1);
$a = (3.1+1.1/3.3)/2.0;
$a = ($a + 2.0/$a)/2.0;
$b = 3/$a;

while($a>0){
    $a = $a - 1;
}

$txt = "PHP";

?>