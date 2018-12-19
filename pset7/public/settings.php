<?php
    require ("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "GET")
        render ("settings_form.php", ["title" => "Settings"]);

    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $rows = CS50::query("SELECT hash FROM users WHERE id = ?", $_SESSION["id"]);

        if (empty($_POST["oldpass"]))
            apologize("You must enter your old password.");
        else if (!password_verify($_POST["oldpass"], $rows[0]["hash"]))
            apologize("Enter the correct password.");
        else if (empty($_POST["newpass"]))
            apologize("You must enter a new password.");
        else if (strcmp($_POST["newpass"], $_POST["confirmation"]))
            apologize("Passwords don't match.");

        CS50::query("UPDATE users SET hash = ? WHERE id = ?", password_hash($_POST["newpass"], PASSWORD_DEFAULT), $_SESSION["id"]);

        redirect("/");
    }
?>