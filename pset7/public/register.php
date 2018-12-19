<?php
    require ("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "GET")
        render ("register_form.php", ["title" => "Register"]);

    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["username"]))
            apologize("You must enter your username.");
        else if (empty($_POST["password"]))
            apologize("You must enter your password.");
        else if (strcmp($_POST["password"], $_POST["confirmation"]))
            apologize("Passwords don't match.");

        $rows = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));

        if (empty($rows))
            apologize("User with this name exists.");

        $rows = CS50::query("SELECT LAST_INSERT_ID () AS id");
        $_SESSION["id"] = $rows[0]["id"];

        redirect("/");
    }
?>