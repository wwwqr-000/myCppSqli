<?php
//Config
$key1 = "123";
$key2 = "321";
$path = "./";
$dbUrl = "localhost";
$dbUser = "root";
$dbPw = "phpmyadminPassword";
$maxFileSize = 10000;
//
session_start();
if (!isset($_FILES["file"]) || $_FILES["file"]["error"] > 4) {
    die("error_1");
}
$file = $_FILES["file"];
$fileName = md5($file["tmp_name"]) . ".txt";
if ($file["type"] != "text/plain" || empty($file["tmp_name"]) || $file["error"] != 0 || $file["size"] > $maxFileSize || !move_uploaded_file($file["tmp_name"], $path . $fileName)) {
    die("error_2");
}
$lineCounter = 0;

function decryptXOR($encrypted, $key) {
    $decrypted = $encrypted;
    $keySize = strlen($key);

    for ($i = 0; $i < strlen($encrypted); ++$i) {
        $decrypted[$i] = $encrypted[$i] ^ $key[$i % $keySize];
    }

    return $decrypted;
}
function encryptXOR($data, $key) {
    $encrypted = '';
    $keyLength = strlen($key);
    $dataLength = strlen($data);

    for ($i = 0; $i < $dataLength; ++$i) {
        $encrypted .= $data[$i] ^ $key[$i % $keyLength];
    }

    return base64_encode($encrypted);
}

$cmd = "";
$db;
$query;
$key1In;
$key2In;
$prepareQuery;
$bindParamKeyStr;
$bindparamArr = [];

$bestand = fopen($path . $fileName, "r");
if (!$bestand) {
    die("error");
}
while (!feof($bestand)) {
    ++$lineCounter;
    $tmpLine = fgets($bestand);
    if ($lineCounter == 1) {
        $cmd = trim($tmpLine);
    }
    if ($cmd == "query") {
        if ($lineCounter == 2) {
            $key1In = trim($tmpLine);
        }
        else if ($lineCounter == 3) {
            $key2In = trim($tmpLine);
        }
        else if ($lineCounter == 4) {
            $db = trim($tmpLine);
        }
        else if ($lineCounter == 5) {
            $query = trim($tmpLine);
        }
    }
    else if ($cmd == "prepare_query") {
        if ($lineCounter == 2) {
            $key1In = trim($tmpLine);
        }
        else if ($lineCounter == 3) {
            $key2In = trim($tmpLine);
        }
        else if ($lineCounter == 4) {
            $db = trim($tmpLine);
        }
        else if ($lineCounter == 5) {
            $prepareQuery = trim($tmpLine);
        }
        else if ($lineCounter == 6) {
            $bindParamKeyStr = trim($tmpLine);
        }
        else if ($lineCounter != 1) {
            if (trim($tmpLine) != "") {
                array_push($bindparamArr, trim($tmpLine));
            }
        }
    }
}
fclose($bestand);
unlink($path . $fileName);

switch($cmd) {
    case "query":
        $conn = new mysqli($dbUrl, $dbUser, $dbPw , $db);
        if ($conn->connect_error) {
            die("$conn error");
        }
        $pull = $conn->query($query);
        $outputArr = [];
        while ($row = $pull->fetch_assoc()) {
            array_unshift($outputArr, $row);
        }
        $conn->close();
        if (json_encode($outputArr) == "[]") {
            die("empty");
        }
        else {
            die(json_encode($outputArr));
        }
    break;
    case "prepare_query":
        $conn = new mysqli($dbUrl, $dbUser, $dbPw, $db);
        if ($conn->connect_error) {
            die("$conn error");
        }
        $jaag = $conn->prepare($prepareQuery);

        $params = [$bindParamKeyStr];
        foreach ($bindparamArr as &$value) {
            $params[] = &$value;
        }

        call_user_func_array([$jaag, 'bind_param'], $params);
        $jaag->execute();
        $result = $jaag->get_result();
        $outputArr = [];
        while ($row = $result->fetch_assoc()) {
            array_unshift($outputArr, $row);
        }
        $conn->close();
        if (json_encode($outputArr) == "[]") {
            die("empty");
        }
        else {
            die(json_encode($outputArr));
        }
    break;
}
?>