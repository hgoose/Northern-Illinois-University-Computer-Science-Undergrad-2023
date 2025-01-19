<?php
    ini_set('display_errors', 1);
    ini_set('display_startup_errors', 1);
    error_reporting(E_ALL);
?>

<?php
    echo <<<END
    <!DOCTYPE html>
    <html lang="en">
    
    <head>
        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Test PHP PDO</title>
        <link rel="stylesheet" href="styles.css">
        <link href='https://unpkg.com/boxicons@2.1.4/css/boxicons.min.css' rel='stylesheet'>
    </head>
    
    <body>
    END;
?>

<?php
    try {
        $host = "localhost";
        $username = "datura";
        $password = "goose";
        $db = "test";
        $dsn = "mysql:host=$host;dbname=$db";
        $pdo = new PDO($dsn, $username, $password);
    } catch (PDOException $e) {
        echo "Connection failed";
        echo $e->getMessage();
    }

    try {
        $affectedRows = $pdo->exec("ALTER TABLE users ADD lastname VARCHAR(50);");
    } catch (PDOException $e) {
        echo $e->getMessage() . "<br/>";
    }

    $statement = "UPDATE users SET lastname=:name WHERE id=:id";
    try {
        $p = $pdo->prepare($statement);
        $p->bindValue(':name', "Appleseed");
        $p->bindValue(':id', "2");
        $s = $p->execute();
    } catch (PDOException $e) { echo "noop"; }


    $s1 = "SELECT * from users";
    // Builds prepared object
    $prepared = $pdo->prepare($s1);
    // Executes query, storing in prepared
    $success = $prepared->execute();

    if ($success) {
        $result = $prepared->fetchAll(PDO::FETCH_ASSOC);
    }

    foreach ($result as $item) {
        echo "<br/>";

        foreach($item as $entry) {
            echo $entry . "\t";
        }
        echo "<br/>";
    }
    




?>

<?php
    echo <<<END
        </body></html>
    END;
    
?>
