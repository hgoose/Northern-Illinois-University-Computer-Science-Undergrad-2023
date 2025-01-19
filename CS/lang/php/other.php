<?php 
    function uTrim($str) { if (preg_match("/^\s*(\w+)\s*/", $str, $cs))  { return $cs[1]; } }
?>

<?php
    echo <<<END
        <table>
            <tr>
                <td> 1 2 3 4 5 </td>
            </tr>
        </table>
    END;
?>
