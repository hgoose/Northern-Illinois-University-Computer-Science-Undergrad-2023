<?php
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);
?>

<?php
$username = "datura";
$password = "goose";
$db = "app";
$host = "localhost";

try { 
    $dsn = "mysql:host=$host;dbname=$db";
    $pdo = new PDO($dsn, $username, $password);
}
catch(PDOexception $e) { 
    echo "Connection to database failed: " . $e->getMessage();
}

?>
