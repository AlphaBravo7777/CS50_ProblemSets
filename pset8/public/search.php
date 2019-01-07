<?php
    require(__DIR__ . "/../includes/config.php");

    $substrings = preg_split("/[\s,]+/", $_GET["geo"]);
    foreach ($substrings as $i => $substring)
        $substrings[$i] = "+(".$substring."*)";

    $_GET["geo"] = implode (" ", $substrings);
    $places = CS50::query("SELECT * FROM places WHERE MATCH(postal_code, place_name, admin_name1) AGAINST (? IN BOOLEAN MODE)", $_GET["geo"]);

    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));
?>