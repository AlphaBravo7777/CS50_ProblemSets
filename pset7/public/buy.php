<?php
    require("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "GET")
        render ("buy_form.php", ["title" => "Buy"]);

    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $rows = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $stock = lookup($_POST["symbol"]);

        if (empty($_POST["symbol"]) || $stock === false)
            apologize("Missing symbol.");
        else if (empty($_POST["shares"]))
            apologize("Missing shares.");
        else if ($rows[0]["cash"] < $stock["price"] * $_POST["shares"])
            apologize("Can't afford.");

        CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $stock["price"] * $_POST["shares"], $_SESSION["id"]);
        CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $stock["symbol"], $_POST["shares"]);
        CS50::query("INSERT INTO histories (user_id, symbol, shares, price, transacted) VALUES(?, ?, ?, ?, ?)", $_SESSION["id"], $stock["symbol"], $_POST["shares"], $stock["price"], date("Y-m-d H:i:s"));

        redirect("/");
    }
?>