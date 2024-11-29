<?php
    try {
        $user = "datura";
        $password = "goose";
        $host = "localhost";
        $db = "app";
        $dsn = "mysql:host=$host;dbname=$db";
        $pdo = new PDO($dsn, $user, $password);
    } catch (PDOexception $e) {
        echo "Error: " . $e->getMessage();
    }
?>

