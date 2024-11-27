<?php
    // Basic page setup
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
    // Function to make a table given an array of headings, 
    // rows from a db, and a classname for the div
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
        // Close table
        echo "</table>";
    }

    // Function to make a table based on a sql select statement, 
    // calls maketable above
    function displaySelect($pdo, $query) {
        try {
            // Prepare the query
            $prepare = $pdo->prepare($query);
            // Execute
            $sucess = $prepare->execute();

            // If execute was successful, fetch the rows
            if ($sucess) {
                // Fetch the returned rows
                $result = $prepare->fetchAll(PDO::FETCH_ASSOC);
                // Grab the column names
                $column_names = array_keys($result[0]);
                // Generate the html table
                makeTable($column_names, $result, "stable1");
            }
        } catch (PDOException $e) {
            echo "Something went wrong";
        }
    }

    // Returns an array of part names, based on the parts currently in db
    function getParts($pdo) {
        try {
            // Define query, prepare, execute
            $partQuery = "SELECT DISTINCT P FROM P;";
            $prepare = $pdo->prepare($partQuery);
            $success = $prepare->execute();

            // Create an empty array
            $parts = array();
            if ($success) {
                // Grab the rows
               $result = $prepare->fetchAll(PDO::FETCH_ASSOC); 
               // For each row
               foreach ($result as $row) {
                    // Add part name to arary
                    $parts[] = $row["P"];
               }
            }
            return $parts;
        // If something above threw an error, catch and display
        } catch (PDOException $e) {
            $e->getMessage();
        }
    }

    // Same as above, but for suppliers
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

    // select a part and see everyone who supplies that part, 
    // along with how many of that part they have available. (and more)
    function queryPart($pdo, $part) {
        // Define the query
        $query = 
            "SELECT S.SNAME,P.P,SP.QTY, P.COLOR, P.WEIGHT 
                FROM S,P,SP 
                    WHERE S.S = SP.S 
                        AND P.P = SP.P 
                        AND P.P=\"$part\";";

        // Prepare and execute
        try {
            $prepare = $pdo->prepare($query);
            $success = $prepare->execute();
            if ($success) {
                // Fetch the returned rows
                $result = $prepare->fetchAll(PDO::FETCH_ASSOC);
                // Check the arary is nonempty
                if (!sizeof($result)) {
                    echo "&#8709"; // \varnothing 
                    return;
                }
                // Get the column names
                $column_names = array_keys($result[0]);
                // Make the html table
                makeTable($column_names, $result, "ptable1");
            }
        } catch (PDOException $e) {
            echo "Something went wrong";        
        }
    }

    // Same as above, but for supplier information
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

    // Execute a dml statement
    function runDmlQuery($pdo, $query)  {
        try {
            $prepared = $pdo->prepare($query);
            $prepared->execute();
        } catch (PDOException $e) {
            echo $e->getMessage();
            return;
        }
    }

    function queryPartQty($pdo, $part, $supplier) {
        try {
            $query = "SELECT QTY FROM SP WHERE P=\"$part\" AND S=\"$supplier\"";
            $prepare = $pdo->prepare($query);
            $prepare->execute();
            $result = $prepare->fetch(PDO::FETCH_ASSOC);
            return $result["QTY"];
        } catch (PDOException $e) {
            echo "Something went wrong";
        }
    }

    function checkPartExists($pdo, $part) {
        try {
            $query = "SELECT P FROM P WHERE P=\"$part\"";
            $prepare = $pdo->prepare($query);
            $prepare->execute();
            $result = $prepare->fetch(PDO::FETCH_ASSOC);
            return $result["P"];
        } catch (PDOException $e) {
            echo "Something went wrong";
        }
    } 

?>

<?php
    // Try the connection. If it fails, catch and throw an error
    try {
        $host = "courses";
        $db = "z2004109";
        $user = "z2004109";
        $password = "2003Jun26";
        $dsn = "mysql:host=$host;dbname=$db";
        $pdo = new PDO($dsn, $user, $password);
    } catch(PDOException $e) {
        echo $e->getMessage();
    }


    // First form, show part and supplier tables
    echo "<div class=\"buttonTable\">";
    echo <<<END
        <form action="assign9.php" method="POST" class="form1">
            <input type="submit" id="submit" name="sinfo" value="Show supplier info">
            <input type="submit" id="submit" name="pinfo" value="Show Part info">
        </form>

    END;
    
    // If the user requested to view a table, display it for them
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
    echo "</div>";

    // Start main querys
    echo "<div class=\"querys\">";

    // Query information on all parts available
    echo "<div class=\"query1\">";
        echo <<<END
            <form action="assign9.php" method="POST" class="form2">
            <select name="partSelect">
        END;
    // Get the list of parts
    $parts = getParts($pdo);

    // Foreach part, add to above select
    foreach ($parts as $part) {
        echo "<option> $part </option>";
    }

    // End the select and draw the submit button
    echo <<<END
        </select>
        <input type="submit" id="submit_extend1" value="Query Part">
    END;
    
    // If the user selected a part to query, run and display the query for them
    if ($_SERVER["REQUEST_METHOD"] === "POST") {
        if (isset($_POST["partSelect"])) {
            $part = $_POST["partSelect"];
            queryPart($pdo, $part);
        }
    }
    // End query1
    echo "</form> </div>";

    // Same as above, but to query supplier information
    echo "<div class=\"query2\">";
             echo <<<END
            <form action="assign9.php" method="POST" class="form2">
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

    if ($_SERVER["REQUEST_METHOD"] === "POST") {
        if (isset($_POST["suppSelect"])) {
            $supp = $_POST["suppSelect"];
            querySupplier($pdo, $supp);
        }
    }
    // End query2
    echo "</form></div>";

    // Form that allows the user to "purchase" a part, subtracting it from the db
    
    // This is just for the heading
    echo "<div class=\"purchaseHead\"> <h1> Purchase Parts </h1> </div>";

    // Here is the purchase form
    echo <<<END
        <div class="purchase">
        <form action="assign9.php" method="POST" class="form3">
    END;
    
    // Generate select dropdown, for each part in the db
    echo "<select name=\"partSelect2\" id=\"buySelect\" style=\"color: black;\">";
    foreach ($parts as $part) {
        echo "<option style=\"color: black\"> $part </option>"; 
    }
    echo "</select>";

    // Generate select for each supplier in the db

    echo "<select name=\"suppSelect2\" id=\"buySelect\" style=\"color: black;\">";
    foreach ($supps as $supp) {
        echo "<option style=\"color: black\"> $supp </option>"; 
    }
    echo "</select>";

    // Allow the user to input a purchase quantity
    echo "<input type=\"number\" name=\"partQty\" id=\"buySelect2\" style=\"color: black; text-align: center\" min=0 placeholder=\"Enter Quantity\">";
    // Submit
    echo "<input type=\"submit\" value=\"Purchase\" id=\"buySelect\" style=\"color:black;\">";
    echo "</form></div>";

    // If the user wants to purchase a part, run the db query to subtract the quantity they purchased
    if ($_SERVER["REQUEST_METHOD"] === "POST") {
        if (isset($_POST["suppSelect2"]) && isset($_POST["partSelect2"]) && isset($_POST["partQty"]) && $_POST["partQty"] > 0) {
            $part = $_POST["partSelect2"];
            $supplier = $_POST["suppSelect2"];
            $amount = $_POST["partQty"];
            $allowance = queryPartQty($pdo, $part, $supplier);
            $diff = ($allowance - $amount > 0 ? $allowance-$amount : $allowance);

            $query = "UPDATE SP SET QTY=$diff WHERE S=\"$supplier\" AND P=\"$part\";";
            runDmlQuery($pdo, $query);
        }
    }
    // Allow the user to add a part to the db
    
    // This is just the heading
    echo "<div class=\"addPartHead\" style=\"text-align: center; margin-top: 5%;\"> <h1> Add parts </h1> </div>";
    
    // Here is the form
    echo "<div class=\"addPart\"> ";
    echo "<form action=\"assign9.php\" method=\"POST\" class=\"form4\">";

    // Inputs for part, name, color, weight
    echo <<<END
        <input type="text" name="addPart" id="buySelect4" style="color: black; text-align: center;" placeholder="Enter part">
        <input type="text" name="addName" id="buySelect4" style="color: black; text-align: center;" placeholder="Enter part name">
        <input type="text" name="addColor" id="buySelect4" style="color: black; text-align: center;" placeholder="Enter part color">
        <input type="number" name="addPartWeight" id="buySelect3" placeholder="Enter weight" min=0 style="color: black; text-align: center;">
        <input type="submit" id="buySelect4" style="color: black" value="Add part">
        </form>
    END;

    // If the want to add a part, run the query for them
    if ($_SERVER["REQUEST_METHOD"] === "POST") {
        if (isset($_POST["addPart"]) && isset($_POST["addName"]) && isset($_POST["addColor"]) && isset($_POST["addPartWeight"]) && $_POST["addPartWeight"] > 0) {
            try {
                $part = $_POST["addPart"];
                $name = $_POST["addName"];
                $color = $_POST["addColor"];
                $weight = $_POST["addPartWeight"];

                $partExists = checkPartExists($pdo, $part);
                if ($partExists == NULL) {
                    $query = "INSERT INTO P (P, PNAME, COLOR, WEIGHT) VALUES (\"$part\", \"$name\", \"$color\", $weight)";
                    runDmlQuery($pdo, $query);
                }
            } catch (PDOException $e){
               echo "Something went wrong"; 
            }
        }
    }
    echo "</div>";

    // Let the user update part supplier information, same classnames as above for same styles
    echo "<div class=\"addPartHead\" style=\"text-align: center; margin-top: 5%;\"> <h1> Add supplier information </h1> </div>";
    echo "<div class=\"addPart\"> ";

    echo "<form action=\"assign9.php\" method=\"POST\" class=\"form4\">";
    // Generate select for each supplier in db
    echo "<select name=\"infoSupp\" style=\"color:black;\" id=\"buySelect\">";
        foreach ($supps as $supp) {
            echo "<option style=\"color: black;\"> $supp </option>";
        }
    echo "</select>";

    // Generate select for each part in db
    echo "<select name=\"infoPart\" style=\"color:black;\" id=\"buySelect\">";
        foreach ($parts as $part) {
            echo "<option style=\"color: black;\"> $part </option>";
        }
    echo "</select>";
    
    // Let the user enter a number (quantity)
    echo <<<END
        <input type="number" name="addQty" id="buySelect3" placeholder="Enter Quantity" min=0 style="color: black; text-align: center;">
        <input type="submit" id="buySelect4" style="color: black" value="Add part">
        </form>
    END;

    // If the user wants to update part supplier information, run the query for them
    if ($_SERVER["REQUEST_METHOD"] === "POST") {
        if (isset($_POST["infoSupp"]) && isset($_POST["infoPart"]) && isset($_POST["addQty"]) && $_POST["addQty"] > 0) {
            try {
                $infoSupp = $_POST["infoSupp"];
                $infoPart = $_POST["infoPart"];
                $qty = $_POST["addQty"];

                $query = "INSERT INTO SP (S, P, QTY) VALUES (\"$infoSupp\", \"$infoPart\", $qty)";
                runDmlQuery($pdo, $query);
            } catch (PDOException $e) {
                echo "Something went wrong";
            }
        }
    }
    echo "</div>";
    // End query div
    echo "</div>";
?>

<?php
    // Just alot of messy styling
    echo <<<END
        <style>
            * {
                margin: 0;
                color: white;
            }

            body {
                background-color: #282828;
                height: 120vh;
            }

            #submit {
                padding: 15px 30px; 
                font-size: 18px;    
                height: 60px;       
                border: none;       
                border-radius: 5px; 
                background-color: #F08FFD; 
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
                background-color: #F08FFD; 
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
                background-color: #F08FFD;
            }

            #buySelect2 {
                outline: none;
                border: none;
            }

            #buySelect3 {
               outline: none;
                border: none; 
            }
            
            #buySelect4 {
                outline: none;
                border: none;
                width: 10%;
            }

            #buySelect4:hover {
                background-color: #F08FFD;
            }

            .form3 {
                width: 100%;
                display: flex;
                flex-wrap: wrap;
                justify-content: center;
            }

            .form4 {
                display: flex;
                flex-wrap: wrap;
                justify-content: center;
                width: 100%;
                height: 100%;
            }
    

            .addPart{
                display: flex;
                justify-content: center;
                width: 100%;
                height: 3%;
                margin-top: 5%;
            }
        </style>
    END;

    // \end{document}
    echo "</main></body> </html>";
?>
