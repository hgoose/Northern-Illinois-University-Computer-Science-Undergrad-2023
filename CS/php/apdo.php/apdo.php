<?php
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);
?>

<?php
    echo <<<DONE
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>CSCI 466 Assignment 9</title>
        <link rel="stylesheet" href="styles.css">
        <link href='https://unpkg.com/boxicons@2.1.4/css/boxicons.min.css' rel='stylesheet'>
    </head>
    <body>
    <main>
    DONE
?>

<?php
    try {
        $host = "localhost";
        $db = "supp";
        $user = "datura";
        $password = "goose";
        $dsn = "mysql:host=$host;dbname=$db";
        $pdo = new PDO($dsn, $user, $password);
    } catch(PDOException $e) {
        echo $e->getMessage();
    }

    function makeTable($heads, $rows, $classname) {
        echo "<table class=\"$classname\">";

        // Make heads
        echo "<tr>";
        foreach ($heads as $head) {
           echo "<th> $head </th>"; 
        }
        echo "</tr>";

        // Output rows
        foreach($rows as $row) {
            echo "<tr>";
            foreach($row as $item) {
                echo "<td> $item </td>";
            }
            echo "</tr>";
        }

        echo "</table>";
    }

    function displaySelect($pdo, $query) {
        $prepare = $pdo->prepare($query);
        $sucess = $prepare->execute();

        if ($sucess) {
            $result = $prepare->fetchAll(PDO::FETCH_ASSOC);
            $column_names = array_keys($result[0]);
            makeTable($column_names, $result, "stable1");

        }
    }

    echo "<div class=\"buttonTable\">";
    echo <<<END
        <form action="apdo.php" method="POST" class="form1">
            <input type="submit" id="submit" name="sinfo" value="Show supplier info">
            <input type="submit" id="submit" name="pinfo" value="Show Part info">
        </form>

    END;
    
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        // print_r($_POST);
        if (array_key_exists('sinfo', $_POST)) {
            $getallSupplier = "SELECT * FROM S";
            displaySelect($pdo, $getallSupplier);
        }
        if (array_key_exists('pinfo', $_POST)) {
            $getallPart = "SELECT * FROM P";
            displaySelect($pdo, $getallPart);
        }
    }

    function getParts($pdo) {
        try {
            $partQuery = "SELECT DISTINCT P FROM P;";
            $prepare = $pdo->prepare($partQuery);
            $success = $prepare->execute();

            $parts = array();
            if ($success) {
               $result = $prepare->fetchAll(PDO::FETCH_ASSOC); 
               foreach ($result as $row) {
                    $parts[] = $row["P"];
               }
            }
            return $parts;
        } catch (PDOException $e) {
            $e->getMessage();
        }
    }

    function getSuppliers($pdo) {
        try {
            $suppQuery = "SELECT DISTINCT S FROM S;";
            $prepare = $pdo->prepare($suppQuery);
            $success = $prepare->execute();

            $supps = array();
            if ($success) {
               $result = $prepare->fetchAll(PDO::FETCH_ASSOC); 
               foreach ($result as $row) {
                    $supps[] = $row["S"];
               }
            }
            return $supps;
        } catch (PDOException $e) {
            $e->getMessage();
        }
    }

    echo "</div>";

    echo "<div class=\"querys\">";

    echo "<div class=\"query1\">";
        echo <<<END
            <form action="apdo.php" method="POST" class="form2">
                <!-- <input type="text" id="queryPart" name="queryPart" placeholder="Enter a part to query" style="color:black; text-align:center"> -->
                <select name="partSelect">
        END;
    $parts = getParts($pdo);

    foreach ($parts as $part) {
        echo "<option> $part </option>";
    }

    echo <<<END
        </select>
            <input type="submit" id="submit_extend1" value="Query Part">
    END;

    function queryPart($pdo, $part) {
        $query = 
            "SELECT S.SNAME,P.P,SP.QTY, P.COLOR, P.WEIGHT 
                FROM S,P,SP 
                    WHERE S.S = SP.S 
                        AND P.P = SP.P 
                        AND P.P=\"$part\";";

        $prepare = $pdo->prepare($query);
        $success = $prepare->execute();

        if ($success) {
            $result = $prepare->fetchAll(PDO::FETCH_ASSOC);
            $column_names = array_keys($result[0]);
            makeTable($column_names, $result, "ptable1");
        }
    }


    if ($_SERVER["REQUEST_METHOD"] === "POST") {
        if (isset($_POST["partSelect"])) {
            $part = $_POST["partSelect"];
            queryPart($pdo, $part);
        }

    }
    // End query1
    echo "</form> </div>";

    echo "<div class=\"query2\">";
             echo <<<END
            <form action="apdo.php" method="POST" class="form2">
                <select name="suppSelect">
        END;
    $supps = getSuppliers($pdo);

    foreach ($supps as $supp) {
        echo "<option> $supp </option>";
    }

    echo <<<END
        </select>
            <input type="submit" id="submit_extend1" value="Query Supplier">
    END;

    function querySupplier($pdo, $supp) {
        $query = 
        "SELECT S.S, S.SNAME, City, Status, P.P, P.Pname, Color, Weight, Qty 
            FROM S, P, SP 
            WHERE S.S = SP.S 
                AND P.P = SP.P 
                AND S.S = \"$supp\";";
        $prepare = $pdo->prepare($query);
        $success = $prepare->execute();

        if ($success) {
            $result = $prepare->fetchAll(PDO::FETCH_ASSOC);
            if (!sizeof($result)) {
                echo "&#8709"; // \varnothing 
                return;
            }
            $column_names = array_keys($result[0]);
            makeTable($column_names, $result, "stable2");
        }
    }


    if ($_SERVER["REQUEST_METHOD"] === "POST") {
        if (isset($_POST["suppSelect"])) {
            $supp = $_POST["suppSelect"];
            querySupplier($pdo, $supp);
        }
    }
    // End query2
    echo "</div>";

    echo "<div class=\"purchaseHead\"> <h1> Purchase Parts </h1> </div>";

    echo <<<END
        <div class="purchase">
        <form action="apdo.php" method="POST" class="form3">
    END;

    echo "<select name=\"partSelect2\" id=\"buySelect\" style=\"color: black;\">";
    foreach ($parts as $part) {
        echo "<option style=\"color: black\"> $part </option>"; 
    }
    echo "</select>";

    echo "<select name=\"suppSelect2\" id=\"buySelect\" style=\"color: black;\">";
    foreach ($supps as $supp) {
        echo "<option style=\"color: black\"> $supp </option>"; 
    }
    echo "</select>";

    echo "<input type=\"number\" name=\"partQty\" id=\"buySelect2\" style=\"color: black; text-align: center\" placeholder=\"Enter Quantity\">";
    echo "<input type=\"submit\" value=\"Purchase\" id=\"buySelect\" style=\"color:black;\">";


    echo "</form></div>";

    function runDmlQuery($pdo, $query)  {
        try {
            $prepared = $pdo->prepare($query);
            $success = $prepared->execute();
        } catch (PDOException $e) {
            return;
        }
    }

    if ($_SERVER["REQUEST_METHOD"] === "POST") {
        if (isset($_POST["suppSelect2"]) && isset($_POST["partSelect2"]) && isset($_POST["partQty"])) {
            $part = $_POST["partSelect2"];
            $supplier = $_POST["suppSelect2"];
            $amount = $_POST["partQty"];

            $query = "UPDATE SP SET QTY=QTY-$amount WHERE S=\"$supplier\" AND P=\"$part\";";
            runDmlQuery($pdo, $query);
        }
    }

    echo "<div class=\"addPartHead\" style=\"text-align: center; margin-top: 5%;\"> <h1> Add parts </h1> </div>";
    
    echo "<div class=\"addPart\"> ";
    echo "<form action=\"apdo.php\" method=\"POST\" class=\"form4\">";
    echo "<select name=\"partSelect2\" id=\"buySelect\" style=\"color: black;\">";
    foreach ($parts as $part) {
        echo "<option style=\"color: black\"> $part </option>"; 
    }
    echo "</select>";

    echo <<<END
        <input type="number" name="addPartAmount" id="buySelect2" placeholder="Enter amount to add" style="color: black; text-align: center;">
        <input type="submit" id="buySelect" style="color: black">
        </form>
    END;

    if ($_SERVER["REQUEST_METHOD"] === "POST") {
        // print_r($_POST);
        // if (isset($_POST["suppSelect2"]) && isset($_POST["partSelect2"]) && isset($_POST["partQty"])) {
        //     $part = $_POST["partSelect2"];
        //     $supplier = $_POST["suppSelect2"];
        //     $amount = $_POST["partQty"];
        //
        //     $query = "UPDATE SP SET QTY=QTY-$amount WHERE S=\"$supplier\" AND P=\"$part\";";
        //     runDmlQuery($pdo, $query);
        // }
    }

    echo "</div>";


    // End query div
    echo "</div>";

    

?>

<?php
    echo <<<END
        <style>
            * {
                margin: 0;
                color: white;
            }

            body {
                background-color: #282828;
            }

            #submit {
                padding: 15px 30px; 
                font-size: 18px;    
                height: 60px;       
                border: none;       
                border-radius: 5px; 
                background-color: #4CAF50; 
                color: white;       
                cursor: pointer;    
            }
            #submit_extend1 {
                padding: 15px 30px; 
                font-size: 18px;    
                height: 60px;       
                border: none;       
                border-top-right-radius: 10px; 
                border-bottom-right-radius: 10px; 
                background-color: #4CAF50; 
                color: white;       
                cursor: pointer;    
            }

            #submit:hover {
                background-color: blue; 
            }

            main {
                width: 100vw;
                height: 100vh;
                display: flex;
            }
            .form1 {
                display: flex;
                flex-wrap: wrap;
                flex-direction: column;
                justify-content: center;
                align-items: center;
                width: 98%;
                height: 15%;
                padding: 5px;
            }

            .form1 input {
                margin-bottom: 10px;
                margin-right: 10px;
                width: 100%;
            }

            .stable1 {
               width: 100%; 
               height: 50%;
               border: 1px solid white;
               text-align: center;
            }

            .stable1 th, td {
                border: 1px solid white;
                padding: 5px;
            }

            .stable1 tr:hover {
                background-color: red;
            }

            .buttonTable {
                overflow-x: auto;
                -webkit-overflow-scrolling: touch;
                display: flex;
                flex-direction: column;
                flex-wrap: wrap;
                width: 25%;
                height: 100%;
                background-color: #1e1e1e;
            }

            .querys {
                display: flex;
                flex-direction: column;
                width: 100%;
                height: 100%;
            }

            .query1 {
                width: 100%;
                height: 20%;
                display: flex;
                flex-wrap: wrap;
                justify-content: center;
                align-items: center;
            }

            .form2 {
                display: flex;
                justify-content: center;
                align-items: center;
                width: 100%;
                height: 100%;
            }

            .form2 select {
                width: 30%;
                height: 30%;
                border-top-left-radius: 10px;
                border-bottom-left-radius: 10px;
                outline: none;
                border: 0px;
                color: black;
            }
            .form2 select option {
               color: black; 
            }

            .query2 {
                width: 100%;
                height: 20%;
            }

            .purchaseHead {
                display: flex;
                justify-content: center;
                margin-top: 5%;
                width: 100%;
                height: 5%;
            }

            .purchase {
                display: flex;
                justify-content: center;
                width: 100%;
                height: 3%;
            }

            #buySelect {
                outline: none;
                border: none;
                height: 100%; 
                width: 15%;
            }

            #buySelect:hover {
                background-color: aqua;
            }

            #buySelect2 {
                outline: none;
                border: none;
            }

            .addPart{
                display: flex;
                justify-content: center;
                width: 100%;
                height: 3%;
                background-color: red;
                margin-top: 5%;
            }
            
           

        </style>
    END;
    echo "</main></body> </html>";
?>
