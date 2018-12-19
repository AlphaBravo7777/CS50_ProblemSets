<?php
    require("../includes/config.php");

    $rows = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    $cash = $rows[0]["cash"];
    $total = $cash;
    $rows = CS50::query("SELECT * FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
    $positions = [];

    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);

        $positions[] =
        [
            "symbol" => $row["symbol"],
            "name" => $stock["name"],
            "shares" => $row["shares"],
            "price" => number_format($stock["price"], 4),
            "profit" => number_format($stock["price"] * $row["shares"], 4)
        ];

        $total += $stock["price"] * $row["shares"];
    }

    render("portfolio.php", ["cash" => number_format($cash, 4), "total" => number_format($total, 4), "positions" => $positions, "title" => "Portfolio"]);
?>