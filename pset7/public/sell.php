<?php
    require("../includes/config.php");

    $rows = CS50::query("SELECT * FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
    $shares = [];
    $symbols = [];

    foreach ($rows as $row)
    {
        $shares[] = $row["shares"];
        $symbols[] = $row["symbol"];
    }

    if ($_SERVER["REQUEST_METHOD"] == "GET")
        render ("sell_form.php", ["symbols" => $symbols, "title" => "Sell"]);

    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $key = array_search($_POST["symbol"], $symbols, TRUE);

        if (empty($_POST["symbol"]))
            apologize("Missing symbol.");
        else if (empty($_POST["shares"]))
            apologize("Missing shares.");
        else if ($_POST["shares"] > $shares[$key])
            apologize("Too many shares.");

        if ($_POST["shares"] === $shares[$key])
            CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        else
            CS50::query("UPDATE portfolios SET shares = shares - ? WHERE user_id = ? AND symbol = ?", $_POST["shares"], $_SESSION["id"], $_POST["symbol"]);

        $stock = lookup($_POST["symbol"]);
        CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $stock["price"] * $_POST["shares"], $_SESSION["id"]);
        CS50::query("INSERT INTO histories (user_id, symbol, shares, price, transacted) VALUES(?, ?, -?, ?, ?)", $_SESSION["id"], $stock["symbol"], $_POST["shares"], $stock["price"], date("Y-m-d H:i:s"));

        redirect("/");
    }
?>