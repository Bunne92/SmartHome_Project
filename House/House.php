<html>
    <head>
        <title>House</title>
        <meta charset="UTF-8">
        <link rel="stylesheet" href="main.css" type="text/css">
    </head>
    <body>
        <audio autoplay>
            <source src="Horse.mp3" type="audio/mpeg">
        </audio>
        <audio autoplay>
            <source src="petit_poney.mp3" type="audio/mpeg">
        </audio>
        
        <form action="House.php" method="get">
            <input type="submit" value="Uppdatera" id="reload"/>
        </form>
        <form action="House_Med.php" method="get">
           <input type="submit" value="Medelvärdet" id="Med_vard"/> 
        </form>
        
        <input type="submit" value="NO!" onclick="NO()"/>
        <script type="text/javascript">
            function NO() {
                var x = document.getElementById('Gif');
                
                if (x.style.display === 'block') {
                    x.style.display = 'none';
                }else{
                    x.style.display = 'block';
                }
            }
        </script>
        <?php
            $myfile = fopen("Current_Temp.txt", "r") or die("Unable to open file!");
        ?>
        <div id="Gif"></div>
        <div id="Gif2"></div>
        <div id="house">
            <div id="half">
                <div id="liv_room">
                    <h3>Vardagsrum</h3>
                    <?php
                        $Output;
                        $x = 0;
                        print"C°: ";
                        while($x < 8){
                            $Output = fgetc($myfile);    
                                
                                if($x == 2){
                                    print"<br>";
                                }
                                else if($x == 3){
                                    print"Tid: ";
                                }
                                echo($Output); 
                            
                            $x++;
                        }
                    ?>
                </div>
                <div id="kitchen">
                    <h3>Kök</h3>
                    <?php
                        $y = 8;
                    
                        print"C°: ";
                        while($y < 17){
                            $Output = fgetc($myfile);    
                                
                            if($y == 11){
                                print"<br>";
                            }
                            else if($y == 12){
                                print"Tid: ";
                            }
                            echo($Output);
                            
                            $y++;
                        }
                    ?>
                </div>    
            </div>
            <div id="half">
                <div id="bathroom">
                    <h3>Badrum</h3>
                    <?php
                        $z = 17;                
                        
                        print"C°: ";
                        while($z < 26){
                            $Output = fgetc($myfile);    
                                
                            if($z == 20){
                                print"<br>";
                            }
                            else if($z == 21){
                                print"Tid: ";
                            }
                            echo($Output);
                            
                            $z++;
                        }
                    ?>
                </div>
                <div id="bedroom">
                    <h3>Sovrum</h3>
                    <?php
                        $w = 26;
                    
                        print"C°: ";
                        while($w < 35){
                            $Output = fgetc($myfile);    
                            
                            if($w == 29){
                                print"<br>";
                            }
                            else if($w == 30){
                                print"Tid: ";
                            }
                            echo($Output);

                            $w++;
                        }
                        fclose($myfile);
                    ?>
                </div>
            </div>
        </div>
    </body>
</html>