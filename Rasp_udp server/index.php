<html>
<head>
    <title></title>
</head>

<body>
Hello world!<br/>
<form action="" method="post">
    <button type="submit" name="sub" value="HELLO!">HELLO!</button>
</form>

</body>
</html>


<!-- PHP post type request -->
<?php
$sock = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);

// function sendmessage($val)
// {
//     // return $val;
// }

if(isset($_POST['sub']))
{
    $msg = $_POST['sub'];
    $len = strlen($msg);
    socket_sendto($sock, $msg, $len, 0, '192.168.0.21', 8888);
    socket_close($sock);
    //echo sendmessage($_POST['sub']);
}



// $f = fopen("data.txt", "r");
//
// // Read line from the text file and write the contents to the client
// echo fgets($f);
//
// fclose($f);


?>
