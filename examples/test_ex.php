<?php
declare(strict_types=1);

$b = 1;
$c = 5;
$i = readi();

if ($c < $b) {
    $a = $b/$c;
}

/*
foo(5, 6);

$a = 3;
$b = 4;

$y = foo($a, $b);

function foo(int $i, int $j) : int {
    foo(7, 8);
}
*/
?>