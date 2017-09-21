<html>
    <head>
        <title>Sensor Hus</title>
        <meta charset="UTF-8">
        <link rel="stylesheet" href="main.css" type="text/css">
    </head>
    <body id="background">
        <audio autoplay>
            <source src="Horse.mp3" type="audio/mpeg">
        </audio>
        <audio autoplay>
            <source src="petit_poney.mp3" type="audio/mpeg">
        </audio>
        <div id="topdiv">
            <div id="title">Sensor Hus</div>
            <input type="submit" value="Temperatur" onclick="Temp()" id="button"/>
            <input type="submit" value="Ljusstyrka" onclick="Ljus()" id="button"/>
            <input type="submit" value="GIF" onclick="GIF()"/>
        </div>
        <script type="text/javascript">
            var b = 0;
            function GIF() {
                var a = document.getElementById('background');
                            
                b++;
                
                if(b == 1){
                    a.style.backgroundImage = "url(200.gif)";
                }else if(b == 2){
                    a.style.backgroundImage = "url(Elefant.gif)";
                }else if(b == 3){
                    a.style.backgroundImage = "url(Rick.gif)";
                }else{
                    b = 0;
                }
            }
            function Temp() {
                var x = document.getElementById('Temp');
                
                if (x.style.display === 'block') {
                    x.style.display = 'none';
                }else{
                    x.style.display = 'block';
                }
            }
            
            function Ljus() {
                var y = document.getElementById('Ljus');
                
                if (y.style.display === 'block') {
                    y.style.display = 'none';
                }else{
                    y.style.display = 'block';
                }
            }
        </script>
        <?php
            $Temp_latest = fopen("sensor2_latest.txt", "r") or die("Unable to open file!");
            $Temp_min = fopen("sensor2_min.txt", "r") or die("Unable to open file!");
            $Temp_all = fopen("sensor2.txt", "r") or die("Unable to open file!");
            $Ljus_latest = fopen("sensor1_latest.txt", "r") or die("Unable to open file!");
            $Ljus_min = fopen("sensor1_min.txt", "r") or die("Unable to open file!");
            $Ljus_all = fopen("sensor1.txt", "r") or die("Unable to open file!");
            
            $output_latest_ljus;
            $output_min_ljus;
            $output_all_ljus;
        ?>
        <div id="main_Div">
            <div id="Temp">
                <?php
                    $output_latest_temp = fgets($Temp_latest);
                    print "Nuvarande Temperatur: $output_latest_temp<br>";
                    
                    $output_min_temp = fgets($Temp_min);
                    print "<br>Medel Temperatur: $output_min_temp<br>";
                    
                    print"<br>Alla mätningar under dagen:<br>";
                    while(!feof($Temp_all)){
                        $output_all_temp = fgets($Temp_all);
                        print "$output_all_temp<br>";
                    }    
                ?>
            </div>
            <div id="Ljus">
                <?php
                    $output_latest_ljus = fgets($Ljus_latest);
                    print "Nuvarande Ljusstyrka: $output_latest_ljus<br>";
                    
                    $output_min_ljus = fgets($Ljus_min);
                    print "<br>Medel Ljusstyrka: $output_min_ljus<br>";
                    
                    print"<br>Alla mätningar under dagen:<br>";
                    while(!feof($Ljus_all)){
                        $output_all_ljus = fgets($Ljus_all);
                        print "$output_all_ljus<br>";
                    }
                    
                    fclose($Temp_latest);
                    fclose($Temp_min);
                    fclose($Temp_all);
                    fclose($Ljus_latest);
                    fclose($Ljus_min);
                    fclose($Ljus_all);
                ?>
            </div>
        </div>
    </body>
</html>