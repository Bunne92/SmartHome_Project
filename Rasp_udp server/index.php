<html>
<head>
    <title></title>
</head>

<body>
Hello world!<br/>
<form action="" method="post">
    <button type="submit" name="sub" value="1 HELLO!">HELLO!</button>
</form>

<form action="" method="post">
    <button type="submit" name="view_file" value="">sensor1.txt!</button>
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
    socket_sendto($sock, $msg, $len, 0, '192.168.1.69', 8888);
    //echo sendmessage($_POST['sub']);
}

if(isset($_POST['view_file']))
{
  $f = fopen("sensor1.txt", "r");
  // Read line from the text file and write the contents to the client
  while(($row = fgets($f, filesize("sensor1.txt"))) !== false) {
      echo $row."<br>";
  }
  // echo fgets($f, filesize("sensor1.txt"));
  fclose($f);
}

socket_close($sock);

?>
