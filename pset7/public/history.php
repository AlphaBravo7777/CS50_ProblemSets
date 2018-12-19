<?php
    require("../includes/config.php");

    $rows = CS50::query("SELECT * FROM histories WHERE user_id = ?", $_SESSION["id"]);

    if (empty($rows))
        apologize("Your transaction history is empty.");

    $transactions = [];

    foreach ($rows as $row)
        $transactions[] =
        [
            "symbol" => $row["symbol"],
            "shares" => $row["shares"],
            "price" => number_format($row["price"], 4),
            "transacted" => $row["transacted"]
        ];

    render("history_form.php", ["transactions" => $transactions, "title" => "History"]);
?>