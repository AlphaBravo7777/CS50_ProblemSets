<?php
    require("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "GET")
        render("quote_form.php", ["title" => "Quote"]);

    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $stock = lookup($_POST["symbol"]);

        if ($stock === false)
            apologize("Invalid symbol");

        render("quoted.php", ["title" => "Quoted", "symbol" => $stock["symbol"], "name" => $stock["name"], "price" => number_format($stock["price"], 4)]);
    }
?>